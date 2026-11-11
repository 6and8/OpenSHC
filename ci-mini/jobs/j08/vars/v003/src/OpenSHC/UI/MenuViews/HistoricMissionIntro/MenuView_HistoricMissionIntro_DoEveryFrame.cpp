#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Audio/mss/SoundSystem.func.hpp"
#include "OpenSHC/Game/GameCore.func.hpp"
#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Credits.func.hpp"
#include "OpenSHC/UI/Helpers.func.hpp"
#include "OpenSHC/UI/MenuViews/HistoricMissionIntro.func.hpp"
#include "OpenSHC/UI/Rendering.func.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"

#include "OpenSHC/Globals/DAT_00eb0b20.hpp"
#include "OpenSHC/Globals/DAT_00eb9b28.hpp"
#include "OpenSHC/Globals/DAT_00eb9b2c.hpp"
#include "OpenSHC/Globals/DAT_00eb9b30.hpp"
#include "OpenSHC/Globals/DAT_00eb9b34.hpp"
#include "OpenSHC/Globals/DAT_00eb9b38.hpp"
#include "OpenSHC/Globals/DAT_00eb9b3c.hpp"
#include "OpenSHC/Globals/DAT_00eb9b40.hpp"
#include "OpenSHC/Globals/DAT_00ed2780.hpp"
#include "OpenSHC/Globals/DAT_ArrayOfStoredMenuStrings.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_MissionDefinedData.hpp"
#include "OpenSHC/Globals/DAT_MouseState.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"
#include "OpenSHC/Globals/DAT_SoundSystemState.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"
#include "OpenSHC/Globals/FLOAT_00ec0834.hpp"
#include "OpenSHC/Globals/FLOAT_Between1And5.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuViews {
        namespace HistoricMissionIntro {

            // FUNCTION: STRONGHOLDCRUSADER 0x004DB8B0
            void MenuView_HistoricMissionIntro_DoEveryFrame()
            {
                int blendStrength = 0;
                if (!MACRO_CALL_MEMBER(Audio::MSS::SoundSystem_Func::isSampleOrStreamPlaying,
                        DAT_SoundSystemState::ptr)(Audio::MSS::enums::SND_STR_SFX_1Unk)) {
                    MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playAmbientSoundStreamUnk, DAT_SFXState::ptr)(
                        Audio::SFX::ASFXT_WIND_0);
                }
                if (DAT_MouseState::instance.leftClickStart != 0) {
                    if (DAT_00eb9b28::instance == 0) {
                        DAT_00eb9b28::instance = 1;
                    } else if (DAT_00ed2780::instance == 0) {
                        FLOAT_00ec0834::instance = 0.0f;
                        DAT_00ed2780::instance = 2;
                    } else if (DAT_00ed2780::instance == 1) {
                        FLOAT_00ec0834::instance = 31.0 - FLOAT_00ec0834::instance;
                        DAT_00ed2780::instance = 2;
                    }
                }
                if (MACRO_CALL(UI::Helpers_Func::TicksSinceCounterStart)() == 0) {
                    return;
                }
                MACRO_CALL(UI::Rendering_Func::RenderGfxHelperUnk)(0, 0, 0);
                MACRO_CALL(UI::Rendering_Func::RenderHistoryBookEdgeUnk)();
                if (DAT_00ed2780::instance == 1) {
                    blendStrength = 31 - (int)FLOAT_00ec0834::instance;
                } else if (DAT_00ed2780::instance == 2) {
                    blendStrength = (int)FLOAT_00ec0834::instance;
                } else if (DAT_00ed2780::instance == 0) {
                    MACRO_CALL(UI::Rendering_Func::RenderGfxHelperUnk)(DAT_00eb0b20::instance, 36, 86);
                }
                if (DAT_00ed2780::instance != 0) {
                    MACRO_CALL(UI::Rendering_Func::RenderMenuGfxHelper)(DAT_00eb0b20::instance, 36, 86, blendStrength);
                }
                if (DAT_00ed2780::instance == 2) {
                    MACRO_CALL_MEMBER(Text::TextManager_Func::renderMultilineText5Unk, DAT_TextManagerObject::ptr)(
                        DAT_ArrayOfStoredMenuStrings::instance[DAT_00eb9b2c::instance],
                        DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + DAT_00eb9b30::instance,
                        DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + DAT_00eb9b34::instance,
                        DAT_00eb9b38::instance, DAT_00eb9b3c::instance, DAT_00eb9b40::instance, blendStrength);
                } else if (DAT_00ed2780::instance == 0) {
                    MACRO_CALL(UI::Credits_Func::RenderScrollingCreditsTextFrame)(30.0f);
                }
                MACRO_CALL(UI::Rendering_Func::DrawLoadedMenuStringHelperWithBlending)(
                    0, 350, 170, 400, 0, 17, FALSE, blendStrength);
                MACRO_CALL_MEMBER(Text::TextManager_Func::renderMultilineText5Unk, DAT_TextManagerObject::ptr)(
                    DAT_ArrayOfStoredMenuStrings::instance[1], DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 350,
                    DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 210, 400, 0, 17, blendStrength);
                if (DAT_00ed2780::instance == 0) {
                    return;
                }
                FLOAT_00ec0834::instance += FLOAT_Between1And5::instance;
                if (FLOAT_00ec0834::instance >= 32.0f) {
                    if (DAT_00ed2780::instance == 2) {
                        MACRO_CALL_MEMBER(Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                            UI::Enums::MVT_SCENARIO_DESCRIPTION, 0);
                        FLOAT_00ec0834::instance = 31.0f;
                        MACRO_CALL_MEMBER(Audio::MSS::SoundSystem_Func::endSoundStream, DAT_SoundSystemState::ptr)(
                            Audio::MSS::enums::SND_STR_SFX_1Unk);
                        return;
                    }
                    DAT_00ed2780::instance = 0;
                    int missionIndex = DAT_GameCore::instance.missionNumber1to20 - 1;
                    if (missionIndex < 20) {
                        MACRO_CALL_MEMBER(Audio::MSS::SoundSystem_Func::playSoundOnStream3Unk,
                            DAT_SoundSystemState::ptr)(
                            DAT_MissionDefinedData::instance.HistoricMissionIntroSoundNames[missionIndex], 1);
                    }
                }
            }

        }
    }
}
}
