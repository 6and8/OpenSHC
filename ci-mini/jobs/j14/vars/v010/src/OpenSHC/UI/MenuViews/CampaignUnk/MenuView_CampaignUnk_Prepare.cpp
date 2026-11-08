#include "OpenSHC/Rendering.func.hpp"
#include "OpenSHC/UI/Helpers.func.hpp"
#include "OpenSHC/UI/MenuViews/CampaignUnk.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"

#include "OpenSHC/Globals/COL_BLACK.hpp"
#include "OpenSHC/Globals/DAT_00ec02f4.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_MissionDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/INT_00eb9b44.hpp"
#include "OpenSHC/Globals/INT_00eb9b4c.hpp"
#include "OpenSHC/Globals/INT_00ec0838.hpp"
#include "OpenSHC/Globals/INT_00ed2778.hpp"
#include "OpenSHC/Globals/INT_00ed277c.hpp"
#include "OpenSHC/Globals/INT_00ed27b0.hpp"
#include "OpenSHC/Globals/INT_00ed3068.hpp"
#include "OpenSHC/Globals/INT_00ed3110.hpp"
#include "OpenSHC/Globals/INT_ARRAY_00eb9afc.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuViews {
        namespace CampaignUnk {

            using OpenSHC::Game::CampaignInfoStruct1;

            // FUNCTION: STRONGHOLDCRUSADER 0x004DCC90
            void MenuView_CampaignUnk_Prepare()
            {
                MACRO_CALL(UI::Helpers_Func::ColorEntireScreen)(COL_BLACK::instance.shortValue);
                if (INT_00ed3110::instance == 0) {
                    MACRO_CALL(UI::Helpers_Func::ParseCampaignMapHotspotBitmap)();
                }
                int changedCount = 0;
                INT_00ed27b0::instance = 0;
                INT_00eb9b4c::instance = 0;
                INT_00eb9b44::instance = 0;
                if (DAT_GameCore::instance.missionNumber1to20 > 1) {
                    // field_0x28 is the first of one record per mission: compare the last mission's with this one's
                    CampaignInfoStruct1* previous
                        = &(&DAT_MissionDefinedData::instance.field_0x28)[DAT_GameCore::instance.missionNumber1to20 - 2];
                    undefined4* before = &previous->sub.field_0x0;
                    for (int i = 1; i <= 20; ++i) {
                        if (before[i + 21] != before[i - 1]) {
                            INT_ARRAY_00eb9afc::instance[changedCount] = i;
                            changedCount++;
                        }
                    }
                    DAT_00ec02f4::instance.field_0x0 = previous->sub.field_0x0;
                    DAT_00ec02f4::instance.field_0x4 = previous->sub.field_0x4;
                    DAT_00ec02f4::instance.field_0x8 = previous->sub.field_0x8;
                    DAT_00ec02f4::instance.field_0xc = previous->sub.field_0xc;
                    DAT_00ec02f4::instance.field_0x10 = previous->sub.field_0x10;
                    DAT_00ec02f4::instance.field_0x14 = previous->sub.field_0x14;
                    Ghidra::undefined4* field_0x18Ptr = &DAT_00ec02f4::instance.field_0x18;
                    *field_0x18Ptr = previous->sub.field_0x18;
                    DAT_00ec02f4::instance.field_0x1c = previous->sub.field_0x1c;
                    DAT_00ec02f4::instance.field_0x20 = previous->sub.field_0x20;
                    DAT_00ec02f4::instance.field_0x24 = previous->sub.field_0x24;
                    DAT_00ec02f4::instance.field_0x28 = previous->sub.field_0x28;
                    DAT_00ec02f4::instance.field_0x2c = previous->sub.field_0x2c;
                    DAT_00ec02f4::instance.field_0x30 = previous->sub.field_0x30;
                    DAT_00ec02f4::instance.field_0x34 = previous->sub.field_0x34;
                    DAT_00ec02f4::instance.field_0x38 = previous->sub.field_0x38;
                    DAT_00ec02f4::instance.field_0x3c = previous->sub.field_0x3c;
                    DAT_00ec02f4::instance.field_0x40 = previous->sub.field_0x40;
                    DAT_00ec02f4::instance.field_0x44 = previous->sub.field_0x44;
                    DAT_00ec02f4::instance.field_0x48 = previous->sub.field_0x48;
                    DAT_00ec02f4::instance.field_0x4c = previous->sub.field_0x4c;
                    INT_00ed27b0::instance = changedCount;
                } else {
                    DAT_00ec02f4::instance.field_0x0 = DAT_MissionDefinedData::instance.field_0x28.sub.field_0x0;
                    DAT_00ec02f4::instance.field_0x4 = DAT_MissionDefinedData::instance.field_0x28.sub.field_0x4;
                    DAT_00ec02f4::instance.field_0x8 = DAT_MissionDefinedData::instance.field_0x28.sub.field_0x8;
                    DAT_00ec02f4::instance.field_0xc = DAT_MissionDefinedData::instance.field_0x28.sub.field_0xc;
                    DAT_00ec02f4::instance.field_0x10 = DAT_MissionDefinedData::instance.field_0x28.sub.field_0x10;
                    DAT_00ec02f4::instance.field_0x14 = DAT_MissionDefinedData::instance.field_0x28.sub.field_0x14;
                    DAT_00ec02f4::instance.field_0x18 = DAT_MissionDefinedData::instance.field_0x28.sub.field_0x18;
                    DAT_00ec02f4::instance.field_0x1c = DAT_MissionDefinedData::instance.field_0x28.sub.field_0x1c;
                    DAT_00ec02f4::instance.field_0x20 = DAT_MissionDefinedData::instance.field_0x28.sub.field_0x20;
                    DAT_00ec02f4::instance.field_0x24 = DAT_MissionDefinedData::instance.field_0x28.sub.field_0x24;
                    DAT_00ec02f4::instance.field_0x28 = DAT_MissionDefinedData::instance.field_0x28.sub.field_0x28;
                    DAT_00ec02f4::instance.field_0x2c = DAT_MissionDefinedData::instance.field_0x28.sub.field_0x2c;
                    DAT_00ec02f4::instance.field_0x30 = DAT_MissionDefinedData::instance.field_0x28.sub.field_0x30;
                    DAT_00ec02f4::instance.field_0x34 = DAT_MissionDefinedData::instance.field_0x28.sub.field_0x34;
                    DAT_00ec02f4::instance.field_0x38 = DAT_MissionDefinedData::instance.field_0x28.sub.field_0x38;
                    DAT_00ec02f4::instance.field_0x3c = DAT_MissionDefinedData::instance.field_0x28.sub.field_0x3c;
                    DAT_00ec02f4::instance.field_0x40 = DAT_MissionDefinedData::instance.field_0x28.sub.field_0x40;
                    DAT_00ec02f4::instance.field_0x44 = DAT_MissionDefinedData::instance.field_0x28.sub.field_0x44;
                    DAT_00ec02f4::instance.field_0x48 = DAT_MissionDefinedData::instance.field_0x28.sub.field_0x48;
                    DAT_00ec02f4::instance.field_0x4c = DAT_MissionDefinedData::instance.field_0x28.sub.field_0x4c;
                }
                INT_00ed2778::instance = 0;
                if (changedCount == 0) {
                    INT_00eb9b4c::instance = 100;
                    INT_00eb9b44::instance = timeGetTime();
                }
                INT_00ed277c::instance = 0;
                INT_00ed3068::instance = 0;
                INT_00ec0838::instance = 0;
                DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
                MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::loadGfxFile, DAT_TextureRenderCoreObject::ptr)(
                    "campaign_map_england.tgx");
                MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::loadGFX8, DAT_TextureRenderCoreObject::ptr)(
                    "campaign_map_england_01.tgx");
                MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::loadGFX8, DAT_TextureRenderCoreObject::ptr)(
                    "campaign_map_england_02.tgx");
                MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::loadGFX8, DAT_TextureRenderCoreObject::ptr)(
                    "campaign_map_england_03.tgx");
                MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::loadGFX8, DAT_TextureRenderCoreObject::ptr)(
                    "campaign_map_england_04.tgx");
                MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::loadGFX8, DAT_TextureRenderCoreObject::ptr)(
                    "campaign_map_england_05.tgx");
                MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::loadGFX8, DAT_TextureRenderCoreObject::ptr)(
                    "campaign_map_england_06.tgx");
                MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::loadGFX8, DAT_TextureRenderCoreObject::ptr)(
                    "campaign_map_england_07.tgx");
                MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::loadGFX8, DAT_TextureRenderCoreObject::ptr)(
                    "campaign_map_england_08.tgx");
                MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::loadGFX8, DAT_TextureRenderCoreObject::ptr)(
                    "campaign_map_england_09.tgx");
                MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::loadGFX8, DAT_TextureRenderCoreObject::ptr)(
                    "campaign_map_england_10.tgx");
                MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::loadGFX8, DAT_TextureRenderCoreObject::ptr)(
                    "campaign_map_england_11.tgx");
                MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::loadGFX8, DAT_TextureRenderCoreObject::ptr)(
                    "campaign_map_england_12.tgx");
                MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::loadGFX8, DAT_TextureRenderCoreObject::ptr)(
                    "campaign_map_england_13.tgx");
                MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::loadGFX8, DAT_TextureRenderCoreObject::ptr)(
                    "campaign_map_england_14.tgx");
                MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::loadGFX8, DAT_TextureRenderCoreObject::ptr)(
                    "campaign_map_england_15.tgx");
                MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::loadGFX8, DAT_TextureRenderCoreObject::ptr)(
                    "campaign_map_england_16.tgx");
                MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::loadGFX8, DAT_TextureRenderCoreObject::ptr)(
                    "campaign_map_england_17.tgx");
                MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::loadGFX8, DAT_TextureRenderCoreObject::ptr)(
                    "campaign_map_england_18.tgx");
                MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::loadGFX8, DAT_TextureRenderCoreObject::ptr)(
                    "campaign_map_england_19.tgx");
                MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::loadGFX8, DAT_TextureRenderCoreObject::ptr)(
                    "campaign_map_england_20.tgx");
                MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::loadGfxFile, DAT_TextureRenderCoreObject::ptr)(
                    "map_pig.tgx");
                MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::loadGfxFile, DAT_TextureRenderCoreObject::ptr)(
                    "map_rat.tgx");
                MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::loadGfxFile, DAT_TextureRenderCoreObject::ptr)(
                    "map_snake.tgx");
                MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::loadGfxFile, DAT_TextureRenderCoreObject::ptr)(
                    "map_wolf.tgx");
                MACRO_CALL(UI::Helpers_Func::LoadTGX_shc_back)();
                MACRO_CALL(OpenSHC::Rendering_Func::TicksStartCounter)();
            }

        }
    }
}
}
