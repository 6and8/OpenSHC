#include "OpenSHC/Audio/mss/SoundSystem.func.hpp"
#include "OpenSHC/Input/MouseState.func.hpp"
#include "OpenSHC/Text/FontSizeClass.func.hpp"
#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Helpers.func.hpp"
#include "OpenSHC/UI/MenuViews/ScenarioDescription.func.hpp"
#include "OpenSHC/UI/Rendering.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eGM.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"

#include "OpenSHC/Globals/COL_BLACK.hpp"
#include "OpenSHC/Globals/DAT_00ed2794.hpp"
#include "OpenSHC/Globals/DAT_00ed2798.hpp"
#include "OpenSHC/Globals/DAT_00ed27bc.hpp"
#include "OpenSHC/Globals/DAT_ARRAY_00ed26d0.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_MissionDefinedData.hpp"
#include "OpenSHC/Globals/DAT_MouseState.hpp"
#include "OpenSHC/Globals/DAT_SoundSystemState.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"
#include "OpenSHC/Globals/INT_00ed3130.hpp"
#include "OpenSHC/Globals/INT_00ed3134.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuViews {
        namespace ScenarioDescription {

            using OpenSHC::DE::SHCDE::eTextSections;

            // FUNCTION: STRONGHOLDCRUSADER 0x004DD350
            void MenuView_ScenarioDescription_DoEveryFrame()
            {
                int textY = 0;
                // function-local static in the original: guard bit + start time
                if ((INT_00ed3134::instance & 1) == 0) {
                    INT_00ed3134::instance |= 1;
                    INT_00ed3130::instance = timeGetTime();
                }
                DWORD now = timeGetTime();
                if (MACRO_CALL(UI::Helpers_Func::TicksSinceCounterStart)() == 0) {
                    return;
                }
                MACRO_CALL(UI::Helpers_Func::ColorEntireScreen)(COL_BLACK::instance.shortValue);
                MACRO_CALL(UI::Rendering_Func::DrawOuterMenuBorder)();
                MACRO_CALL(UI::Rendering_Func::RenderGfxHelperUnk)(0, 0, 0);
                if (DAT_00ed2794::instance != 0 && (int)(now - DAT_00ed2794::instance) > 1500) {
                    DAT_00ed2794::instance = 0;
                    int missionIndex = DAT_GameCore::instance.missionNumber1to20 - 1;
                    if (missionIndex < 20) {
                        MACRO_CALL_MEMBER(
                            Audio::MSS::SoundSystem_Func::playSoundOnStream3Unk, DAT_SoundSystemState::ptr)(
                            DAT_MissionDefinedData::instance.MissionSpeechFileNames[missionIndex], 1);
                    }
                }
                int frame = (now - INT_00ed3130::instance) / 250;
                if (frame >= 60) {
                    frame = 0;
                    INT_00ed3130::instance = timeGetTime();
                }
                if (frame < 26) {
                    MACRO_CALL(UI::Rendering_Func::RenderGfxHelperUnk)(
                        DAT_MissionDefinedData::instance.ScenarioDescriptionSpriteIDs[frame] + 1, 0, 0);
                }
                if (DAT_00ed27bc::instance == 1) {
                    DAT_TextManagerObject::instance.field_0x24 = 1;
                    MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                        MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                            DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_MISSION_BUTTONS, 6),
                        DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 30,
                        DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 50, Text::TTA_LEFT, 0xccfaff, 17,
                        FALSE, 0);
                    textY = 40;
                } else {
                    if (DAT_00ed2798::instance == 0) {
                        textY = MACRO_CALL(UI::Rendering_Func::RenderMissionObjectivesUnk)() - 30
                            - DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight;
                    }
                    if (DAT_00ed2798::instance == 1) {
                        MACRO_CALL(UI::Rendering_Func::RenderMissionObjectivesUnk)();
                        return;
                    }
                    if (DAT_00ed2798::instance == 2) {
                        int mission = DAT_GameCore::instance.missionNumber1to20;
                        bool eco = DAT_GameCore::instance.gameMode_2 == Game::GM_ECONOMIC_CAMPAIGN_SH1;
                        int hintCount = eco ? DAT_MissionDefinedData::instance.field_0xae4[mission - 33]
                                            : DAT_MissionDefinedData::instance.MissionHintCounts[mission - 1];
                        int hintSection = eco ? mission + 158 : mission * 4 + 98;
                        int y = DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 50;
                        DAT_TextManagerObject::instance.field_0x24 = 1;
                        MACRO_CALL_MEMBER(Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                            DE::SHCDE::TEXT_HINTS, 1, DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 30, y,
                            Text::TTA_LEFT, 0xccfaff, 17, FALSE);
                        y += 30;
                        MACRO_CALL_MEMBER(Text::TextManager_Func::renderMultilineText2Unk, DAT_TextManagerObject::ptr)(
                            (eTextSections)hintSection, 1, DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 40,
                            y, 720, 0xc2f0eb, 18);
                        y += DAT_TextManagerObject::instance.field_0x4 + 30;
                        if (hintCount > 0) {
                            DAT_TextManagerObject::instance.field_0x24 = 1;
                            if (hintCount == 1) {
                                MACRO_CALL_MEMBER(Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                                    DE::SHCDE::TEXT_HINTS, 3,
                                    DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 30, y, Text::TTA_LEFT,
                                    0xccfaff, 17, FALSE);
                            } else if (hintCount > 1) {
                                MACRO_CALL_MEMBER(Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                                    DE::SHCDE::TEXT_HINTS, 2,
                                    DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 30, y, Text::TTA_LEFT,
                                    0xccfaff, 17, FALSE);
                            }
                            y += 30;
                            char* hintRevealed = (char*)&DAT_GameState::instance.mapAndTime.field43_0xf0;
                            for (int i = 0; i < hintCount; ++i) {
                                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = 0;
                                MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::renderGM,
                                    DAT_TextureRenderCoreObject::ptr)(DE::SHCDE::GM_INTERFACE_ICONS3, 20,
                                    DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 40, y - 2);
                                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = 1;
                                int x = DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 65;
                                if (hintRevealed[i] == 0) {
                                    MACRO_CALL_MEMBER(
                                        Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                                        MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                                            DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_HINTS, 4),
                                        x, y, Text::TTA_LEFT, 0xc2f0eb, 18, FALSE, 0);
                                    if (DAT_MouseState::instance.draggingStopped != FALSE
                                        && MACRO_CALL_MEMBER(
                                            Input::MouseState_Func::isMouseInsideBox, DAT_MouseState::ptr)(
                                            DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 40, y - 2, 19,
                                            19)) {
                                        hintRevealed[i] = 1;
                                    }
                                    break;
                                }
                                MACRO_CALL_MEMBER(
                                    Text::TextManager_Func::renderMultilineText2Unk, DAT_TextManagerObject::ptr)(
                                    (eTextSections)hintSection, i + 2, x, y, 695, 0xc2f0eb, 18);
                                y += DAT_TextManagerObject::instance.field_0x4;
                            }
                        }
                    }
                    if (DAT_00ed2798::instance != 0) {
                        return;
                    }
                }
                int briefingSection;
                int briefingNum;
                if (DAT_GameCore::instance.gameMode_2 == Game::GM_ECONOMIC_CAMPAIGN_SH1) {
                    briefingSection = DE::SHCDE::TEXT_ECO_MISSION_BRIEFINGS;
                    briefingNum = DAT_GameCore::instance.missionNumber1to20 - 32;
                } else {
                    briefingSection = DAT_00ed2798::instance + DAT_GameCore::instance.missionNumber1to20 * 4 + 96;
                    briefingNum = 1;
                }
                int textHeight = MACRO_CALL_MEMBER(Text::FontSizeClass_Func::renderMultilineTextUnk,
                    &DAT_TextManagerObject::instance.fontSizeClassArray[18])(
                    MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(
                        (eTextSections)briefingSection, briefingNum),
                    0, 0, 720, 0, 0, 1);
                if (textHeight + textY + 50 > 420 && DAT_00ed27bc::instance != 1) {
                    DAT_ARRAY_00ed26d0::instance[0].y = 1;
                    return;
                }
                MACRO_CALL_MEMBER(Text::TextManager_Func::renderMultilineText5Unk, DAT_TextManagerObject::ptr)(
                    MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(
                        (eTextSections)briefingSection, briefingNum),
                    DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 40,
                    DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + textY + 50, 720, 0xc2f0eb, 18, 0);
            }

        }
    }
}
}
