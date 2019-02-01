/*
** Copyright 2016, The CyanogenMod Project
**           2017-2018, The LineageOS Project
**
** Licensed under the Apache License, Version 2.0 (the "License");
** you may not use this file except in compliance with the License.
** You may obtain a copy of the License at
**
**     http://www.apache.org/licenses/LICENSE-2.0
**
** Unless required by applicable law or agreed to in writing, software
** distributed under the License is distributed on an "AS IS" BASIS,
** WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
** See the License for the specific language governing permissions and
** limitations under the License.
*/

#include "Utils.h"

#include <fcntl.h>
#include <poll.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fstream>
#include <string>

#include <cutils/sockets.h>

namespace vendor {
namespace lineage {
namespace livedisplay {
namespace V1_0 {
namespace implementation {

using ::android::NO_INIT;
using ::android::OK;
using ::android::status_t;

status_t Utils::readInt(const char* node, int32_t* value) {
    std::string buf;
    status_t ret = OK;
    std::ifstream fin(node);
    if (!fin.good()) {
        return errno;
    }
    fin >> *value;
    if (fin.fail()) {
        ret = errno;
    }
    fin.close();
    return ret;
}

status_t Utils::writeInt(const char* node, int32_t value) {
    status_t ret = OK;
    std::ofstream fout(node);
    if (!fout.good()) {
        return errno;
    }
    fout << value << std::endl;
    if (fout.fail()) {
        ret = errno;
    }
    fout.close();
    return ret;
}
}  // namespace implementation
}  // namespace V1_0
}  // namespace livedisplay
}  // namespace lineage
}  // namespace vendor
