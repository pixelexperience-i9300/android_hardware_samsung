/*
** Copyright 2016, The CyanogenMod Project
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

#ifndef VENDOR_LINEAGE_LIVEDISPLAY_V1_0_Exynos4_H
#define VENDOR_LINEAGE_LIVEDISPLAY_V1_0_Exynos4_H

#include "ColorBackend.h"

#define DEFAULT_DISPLAY_MODE 1 // Standard
namespace vendor {
namespace lineage {
namespace livedisplay {
namespace V1_0 {
namespace implementation {

constexpr char DISPLAY_MODE[] = "/sys/class/mdnie/mdnie/mode";
constexpr char DISPLAY_MODE_MAX[] = "/sys/class/mdnie/mdnie/mode_max";
constexpr char DISPLAY_MODE_DEFAULT[] = "/data/misc/.displaymodedefault";

class Exynos4 : public ColorBackend {
  public:
    Exynos4();
    ~Exynos4();

    virtual android::status_t setAdaptiveBacklightEnabled(bool /* enabled */) override {
        return android::NO_INIT;
    }

    virtual bool isAdaptiveBacklightEnabled() override {
        return false;
    }

    virtual android::status_t setOutdoorModeEnabled(bool /* enabled */) override {
        return android::NO_INIT;
    }

    virtual bool isOutdoorModeEnabled() override {
        return false;
    }

    virtual android::status_t getColorBalanceRange(Range& /* range */) override {
        return android::NO_INIT;
    }

    virtual android::status_t setColorBalance(int32_t /* balance */) override {
        return android::NO_INIT;
    }

    virtual int32_t getColorBalance() override {
        return 0;
    }

    virtual android::status_t getPictureAdjustmentRanges(HSICRanges& /* ranges */) override {
        return android::NO_INIT;
    }

    virtual android::status_t getPictureAdjustment(HSIC& /* hsic */) override {
        return android::NO_INIT;
    }

    virtual HSIC getDefaultPictureAdjustment()  override;

    virtual android::status_t setPictureAdjustment(const HSIC& /* hsic */) override {
        return android::NO_INIT;
    }



    virtual android::status_t getDisplayModes(std::vector<android::sp<disp_mode>>& profiles) override;
    virtual android::status_t setDisplayMode(int32_t modeID, bool makeDefault) override;
    virtual android::sp<disp_mode> getCurrentDisplayMode() override;
    virtual android::sp<disp_mode> getDefaultDisplayMode() override;

    virtual bool hasFeature(Feature feature) override;

  private:
    uint32_t getNumDisplayModes();
    android::sp<disp_mode> getDisplayModeById(int32_t id);

    HSIC mDefaultPictureAdjustment;
};

}  // namespace implementation
}  // namespace V1_0
}  // namespace livedisplay
}  // namespace lineage
}  // namespace vendor

#endif  // VENDOR_LINEAGE_LIVEDISPLAY_V1_0_Exynos4_H
