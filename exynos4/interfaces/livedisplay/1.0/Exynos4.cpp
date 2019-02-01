/*
** Copyright 2016, The CyanogenMod Project
** Copyright (C) 2017-2018 The LineageOS Project
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

#define LOG_NDEBUG 0

#define LOG_TAG "LiveDisplay-Exynos4"

#include "Exynos4.h"
#include "Utils.h"

#include <android-base/logging.h>
#include <errno.h>
#include <fcntl.h>

namespace vendor {
namespace lineage {
namespace livedisplay {
namespace V1_0 {
namespace implementation {

using android::BAD_VALUE;
using android::NO_INIT;
using android::OK;
using android::sp;
using android::status_t;

Exynos4::Exynos4() {
    memset(&mDefaultPictureAdjustment, 0, sizeof(HSIC));

    if (hasFeature(Feature::DISPLAY_MODES)) {
        int32_t id;
        status_t rc = Utils::readInt(DISPLAY_MODE_DEFAULT, &id);
        if (rc != OK || id < 0) {
            Utils::writeInt(DISPLAY_MODE_DEFAULT, DEFAULT_DISPLAY_MODE);
        }

        auto mode = getDefaultDisplayMode();
        if (mode != nullptr) {
            setDisplayMode(mode->id, false);
        }
    }
}

Exynos4::~Exynos4() {
}

status_t Exynos4::getDisplayModes(std::vector<sp<disp_mode>>& profiles) {
    struct d_mode {
        int id;
        char name[10];
    };

    struct d_mode d_mode_profiles[6] = {
	{ 0, "Dynamic" },
        { 1, "Standard" },
        { 2, "Natural" },
        { 3, "Cinema" },
        { 4, "Adaptive" },
        { 5, "Reading" },
    };

    for (uint32_t i = 0; i < getNumDisplayModes(); i++) {
        const sp<disp_mode> m = new disp_mode;
        m->id = d_mode_profiles[i].id;
        m->name = d_mode_profiles[i].name;
        m->privFlags = 0;
        profiles.push_back(m);
    }

    return OK;
}

status_t Exynos4::setDisplayMode(int32_t modeID, bool makeDefault) {
    if (makeDefault) {
        Utils::writeInt(DISPLAY_MODE_DEFAULT, modeID);
    }
    return Utils::writeInt(DISPLAY_MODE, modeID);
}

sp<disp_mode> Exynos4::getCurrentDisplayMode() {
    int32_t id = 0;

    status_t rc = Utils::readInt(DISPLAY_MODE, &id);
    if (rc != OK || id < 0) {
        return nullptr;
    }
    return getDisplayModeById(id);
}

sp<disp_mode> Exynos4::getDefaultDisplayMode() {
    int32_t id = 0;
    status_t rc = Utils::readInt(DISPLAY_MODE_DEFAULT, &id);
    if (rc != OK || id < 0) {
        return getDisplayModeById(1);
    }
    return getDisplayModeById(id);
}

bool Exynos4::hasFeature(Feature feature) {
  return feature == Feature::DISPLAY_MODES;
}

uint32_t Exynos4::getNumDisplayModes() {
    int32_t num = 0;
    status_t rc = Utils::readInt(DISPLAY_MODE_MAX, &num);
    if (rc != OK) {
        return 0;
    }
    return num;
}

sp<disp_mode> Exynos4::getDisplayModeById(int32_t id) {
    std::vector<sp<disp_mode>> profiles;
    status_t rc = getDisplayModes(profiles);
    if (rc == OK) {
        for (const auto& mode : profiles) {
            if (id == mode->id) {
                return mode;
            }
        }
    }

    return nullptr;
}

HSIC Exynos4::getDefaultPictureAdjustment() {
    return mDefaultPictureAdjustment;
}

}  // namespace implementation
}  // namespace V1_0
}  // namespace livedisplay
}  // namespace lineage
}  // namespace vendor
