#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/DisplayElements.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"

#include "OpenSHC/Globals/DAT_BlendingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"
#include "OpenSHC/Globals/DAT_RenderingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"

namespace OpenSHC {
namespace UI {
    namespace DisplayElements {

        // FUNCTION: STRONGHOLDCRUSADER 0x004B0820
        void RenderUnknownDisplayElement25(int posX, int posY, DWORD elementState)
        {
            char name[100];
            int offset = 0;
            for (int player = 1; player != 9; ++player) {
                if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[player] == -1) {
                    continue;
                }
                strncpy(name, DAT_GameSynchronyState::instance.DAT_PlayerNames[player], 99);
                name[99] = 0;
                int length = strlen(name);
                int width = 0;
                for (int i = 0; i < length; ++i) {
                    if (name[i] == '\n') {
                        name[i] = ' ';
                    }
                    width += MACRO_CALL_MEMBER(Text::TextManager_Func::getCharWidth, DAT_TextManagerObject::ptr)(
                        (uchar)name[i], 18);
                    if (width > 170) {
                        char* namePtr = &name[i];
                        *namePtr = 0;
                        break;
                    }
                }
                DAT_PencilRenderCore::instance.surfaceTarget = 1;
                MACRO_CALL_MEMBER(UI::Rendering::PencilRenderCore_Func::drawBlendedBlackBox, DAT_PencilRenderCore::ptr)(
                    posX - 95 + offset, posY - 5, posX - 95 + offset + 190, posY + 50, 16);
                DAT_PencilRenderCore::instance.surfaceTarget = 0;
                MACRO_CALL_MEMBER(Text::TextManager_Func::renderInGameTextWithShadow, DAT_TextManagerObject::ptr)(name,
                    posX - 95 + offset + 95, posY, Text::TTA_CENTER,
                    DAT_RenderingDefinedData::instance
                        .ColorArray[DAT_BlendingDefinedData::instance.PlayerSlotUnitColor[player]],
                    0, 18, FALSE, 0);
                int numberWidth;
                if ((int)DAT_GameSynchronyState::instance.skirmishPoints >= 1000000) {
                    numberWidth = 77;
                } else if ((int)DAT_GameSynchronyState::instance.skirmishPoints >= 100000) {
                    numberWidth = 66;
                } else if ((int)DAT_GameSynchronyState::instance.skirmishPoints >= 10000) {
                    numberWidth = 55;
                } else if ((int)DAT_GameSynchronyState::instance.skirmishPoints >= 1000) {
                    numberWidth = 44;
                } else if ((int)DAT_GameSynchronyState::instance.skirmishPoints >= 100) {
                    numberWidth = 33;
                } else if ((int)DAT_GameSynchronyState::instance.skirmishPoints >= 10) {
                    numberWidth = 22;
                } else {
                    numberWidth = 11;
                }
                BOOL digitShown = FALSE;
                int divisor = 10000000;
                for (int digitIndex = 7; digitIndex >= 0; --digitIndex) {
                    int digit = DAT_GameState::instance.playerDataArray[player].field_0x229c / divisor % 10;
                    if (digit != 0 || digitShown || digitIndex == 0) {
                        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumber2, DAT_TextManagerObject::ptr)(digit,
                            numberWidth / 2 - digitIndex * 11 + offset + posX, posY + 25, (Text::TextAlignment)-1,
                            DAT_RenderingDefinedData::instance
                                .ColorArray[DAT_BlendingDefinedData::instance.PlayerSlotUnitColor[player]],
                            0, 17, FALSE, 0);
                        digitShown = TRUE;
                    }
                    divisor /= 10;
                    if (divisor < 1) {
                        divisor = 1;
                    }
                }
                offset += 200;
            }
        }

    }
}
}
