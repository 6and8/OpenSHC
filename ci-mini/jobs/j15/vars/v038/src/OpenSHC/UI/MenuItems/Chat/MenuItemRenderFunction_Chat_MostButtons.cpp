#pragma warning(disable : 4996)

#include "../Chat.func.hpp"

#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Rendering/AlphaAndButtonSurface.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Rendering/Colors/ColorsEnum.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"

#include "OpenSHC/Globals/AlphaAndButtonSurfaceObj.hpp"
#include "OpenSHC/Globals/DAT_BlendingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_ButtonCurrentlyInteracting.hpp"
#include "OpenSHC/Globals/DAT_ButtonUnknownZero.hpp"
#include "OpenSHC/Globals/DAT_ButtonW.hpp"
#include "OpenSHC/Globals/DAT_ButtonX.hpp"
#include "OpenSHC/Globals/DAT_ButtonY.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"
#include "OpenSHC/Globals/DAT_RenderingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"

#include <string.h>

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        // FUNCTION: STRONGHOLDCRUSADER 0x0047fd50
        void __cdecl Chat::MenuItemRenderFunction_Chat_MostButtons(int param_1, ...)
        {
            DAT_ButtonUnknownZero::instance = 0;
            if (param_1 < 0) {
                int playerIdx = -param_1;
                int totalWidth = 0;
                if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[playerIdx] != -1) {
                    char nameBuf[100];
                    strncpy(nameBuf, DAT_GameSynchronyState::instance.DAT_PlayerNames[playerIdx], 99);
                    nameBuf[99] = 0;
                    int len = (int)strlen(nameBuf);
                    for (int i = 0; i < len; ++i) {
                        totalWidth += MACRO_CALL_MEMBER(
                            Text::TextManager_Func::getCharWidth, DAT_TextManagerObject::ptr)(nameBuf[i], 18);
                        if (totalWidth > 170) {
                            nameBuf[i] = 0;
                            break;
                        }
                    }
                    DAT_ButtonCurrentlyInteracting::instance
                        = (DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[playerIdx] != 0);
                    MACRO_CALL_MEMBER(UI::Rendering::AlphaAndButtonSurface_Func::renderBasicButton,
                        AlphaAndButtonSurfaceObj::ptr)(0, OpenSHC::Rendering::Enums::RT_CONTEXT_BASED);
                    if (DAT_ButtonCurrentlyInteracting::instance == 0) {
                        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                            nameBuf, DAT_ButtonX::instance + 5, DAT_ButtonY::instance + 7, (Text::TextAlignment)170,
                            DAT_RenderingDefinedData::instance
                                .ColorArray[DAT_BlendingDefinedData::instance.PlayerSlotUnitColor[playerIdx]],
                            18, FALSE, 0);
                    } else {
                        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                            nameBuf, DAT_ButtonX::instance + 5, DAT_ButtonY::instance + 7, (Text::TextAlignment)170,
                            DAT_RenderingDefinedData::instance
                                .ColorArray[DAT_BlendingDefinedData::instance.PlayerSlotUnitColor[playerIdx]],
                            18, FALSE, 0);
                    }
                    if (MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::countPlayersInSameTeam,
                            DAT_GameSynchronyState::ptr)(playerIdx)
                        > 1) {
                        int offsetX = 0;
                        for (int i = 1; i < 9; ++i) {
                            if (DAT_GameState::instance.mapAndTime.playerTeams[i]
                                == DAT_GameState::instance.mapAndTime.playerTeams[playerIdx]) {
                                int x = DAT_ButtonX::instance + offsetX;
                                MACRO_CALL_MEMBER(UI::Rendering::PencilRenderCore_Func::drawColorBox,
                                    DAT_PencilRenderCore::ptr)(x + 4, DAT_ButtonY::instance + 4, x + 12,
                                    DAT_ButtonY::instance + 6,
                                    MACRO_CALL_MEMBER(
                                        UI::Rendering::TextureRenderCore_Func::transformBGR24ToScreenColor,
                                        DAT_TextureRenderCoreObject::ptr)(DAT_RenderingDefinedData::instance
                                            .ColorArray[DAT_BlendingDefinedData::instance.PlayerSlotUnitColor[i]]));
                                offsetX += 7;
                            }
                        }
                    }
                } else {
                    DAT_ButtonUnknownZero::instance = 1;
                    DAT_ButtonCurrentlyInteracting::instance = 0;
                }
            } else {
                MACRO_CALL_MEMBER(UI::Rendering::AlphaAndButtonSurface_Func::renderBasicButton,
                    AlphaAndButtonSurfaceObj::ptr)(0, OpenSHC::Rendering::Enums::RT_CONTEXT_BASED);
                int centerX = DAT_ButtonX::instance + DAT_ButtonW::instance / 2;
                int textY = DAT_ButtonY::instance + 7;
                if (DAT_ButtonCurrentlyInteracting::instance == 0) {
                    MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                        MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                            DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_MULTIPLAYER_CONNECTION, param_1),
                        centerX, textY, Text::TTA_CENTER, 12775659, 18, FALSE, 0);
                } else {
                    MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                        MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                            DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_MULTIPLAYER_CONNECTION, param_1),
                        centerX, textY, Text::TTA_CENTER, OpenSHC::Rendering::Colors::COL_CCFAFF, 18, FALSE, 0);
                }
            }
        }

    } // namespace MenuItems
} // namespace UI
} // namespace OpenSHC
