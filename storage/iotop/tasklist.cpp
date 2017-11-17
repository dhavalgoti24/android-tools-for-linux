// Copyright (C) 2015 The Android Open Source Project
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include <map>
#include <memory>
#include <string>
#include <vector>
#include <cstdarg>

#include "tasklist.h"

template<typename Func>
static bool ScanPidsInDir(std::string name, Func f) {
  std::unique_ptr<DIR, decltype(&closedir)> dir(opendir(name.c_str()), closedir);
  if (!dir) {
    return false;
  }

  dirent* entry;
  while ((entry = readdir(dir.get())) != nullptr) {
    if (isdigit(entry->d_name[0])) {
      pid_t pid = atoi(entry->d_name);
      f(pid);
    }
  }

  return true;
}

bool TaskList::Scan(std::map<pid_t, std::vector<pid_t>>& tgid_map) {
  tgid_map.clear();

  return ScanPidsInDir("/proc", [&tgid_map](pid_t tgid) {
    std::vector<pid_t> pid_list;
    if (ScanPid(tgid, pid_list)) {
      tgid_map.insert({tgid, pid_list});
    }
  });
}

static void StringAppendV(std::string* dst, const char* format, va_list ap) {
  // First try with a small fixed size buffer
  char space[1024];

  // It's possible for methods that use a va_list to invalidate
  // the data in it upon use.  The fix is to make a copy
  // of the structure before using it and use that copy instead.
  va_list backup_ap;
  va_copy(backup_ap, ap);
  
  int result = vsnprintf(space, sizeof(space), format, backup_ap);
  va_end(backup_ap);

  if ((result >= 0) && (result < sizeof(space))) {
    // It fit
    dst->append(space, result);
    return;
  }
  int length = sizeof(space);
  while (true) {
    if (result < 0) {
      // Older behavior: just try doubling the buffer size
      length *= 2;
    } else {
      // We need exactly "result+1" characters
      length = result+1;
    }
    char* buf = new char[length];

    // Restore the va_list before we use it again
    va_copy(backup_ap, ap);
    result = vsnprintf(buf, length, format, backup_ap);
    va_end(backup_ap);

    if ((result >= 0) && (result < length)) {
      // It fit
      dst->append(buf, result);
      delete[] buf;
      return;
    }
    delete[] buf;
  }
}

static std::string StringPrintf(const char* format, ...) {
  va_list ap;
  va_start(ap, format);
  std::string result;
  StringAppendV(&result, format, ap);
  va_end(ap);
  return result;
}

bool TaskList::ScanPid(pid_t tgid, std::vector<pid_t>& pid_list) {
  std::string filename = StringPrintf("/proc/%d/task", tgid);

  return ScanPidsInDir(filename, [&pid_list](pid_t pid) {
    pid_list.push_back(pid);
  });
}
