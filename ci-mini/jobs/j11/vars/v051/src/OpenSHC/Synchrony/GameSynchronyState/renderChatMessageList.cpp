#include "../GameSynchronyState.func.hpp"

#include "OpenSHC/Text/FontSizeClass.func.hpp"
#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"

#include "OpenSHC/Globals/DAT_BlendingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_ButtonBackgroundBlendStrength.hpp"
#include "OpenSHC/Globals/DAT_RenderingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"

namespace OpenSHC {
namespace Synchrony {

    // FUNCTION: STRONGHOLDCRUSADER 0x0047FB50
    void GameSynchronyState::renderChatMessageList(int xPos, int yPos, int param_3)
    {
        this->chatMessageRenderIndex = this->DAT_ChatMessageArrayIndex - param_3;
        if (this->chatMessageRenderIndex < 0) {
            this->chatMessageRenderIndex += 20;
        }
        int lines = 0;
        MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::setScreenMenuSurfaceHeightRange,
            DAT_TextureRenderCoreObject::ptr)(yPos - 0x48, yPos + 0x12);
        DAT_TextManagerObject::instance.field_0x34 = 0x11;
        for (int message = 0; message < 5; ++message) {
            if (this->DAT_ChatEventArray[this->chatMessageRenderIndex].flag == 1) {
                MACRO_CALL_MEMBER(Text::TextManager_Func::renderInGameTextWithShadow, DAT_TextManagerObject::ptr)(
                    this->DAT_ChatMessageSubjectPlayerNameArray[this->chatMessageRenderIndex], xPos, yPos,
                    Text::TTA_LEFT,
                    DAT_RenderingDefinedData::instance.ColorTable1[DAT_BlendingDefinedData::instance
                            .PlayerSlotUnitColor[this->DAT_ChatEventArray[this->chatMessageRenderIndex].subjectPlayer]],
                    0, 0x13, FALSE, ((int)DAT_ButtonBackgroundBlendStrength::instance - 0x20) * 0x20 / 0x20 + 0x20);
                if (MACRO_CALL_MEMBER(Text::FontSizeClass_Func::renderMultilineTextUnk,
                        &DAT_TextManagerObject::instance.fontSizeClassArray[19])(
                        this->DAT_ChatMessageArray[this->chatMessageRenderIndex], 0, 0,
                        494 - DAT_TextManagerObject::instance.currentXOffset_0x0, 0, 0, 1)
                    > 24) {
                    ++lines;
                    yPos -= 0x12;
                    MACRO_CALL_MEMBER(Text::TextManager_Func::renderInGameTextWithShadow, DAT_TextManagerObject::ptr)(
                        this->DAT_ChatMessageSubjectPlayerNameArray[this->chatMessageRenderIndex], xPos, yPos,
                        Text::TTA_LEFT,
                        DAT_RenderingDefinedData::instance
                            .ColorTable1[DAT_BlendingDefinedData::instance.PlayerSlotUnitColor
                                    [this->DAT_ChatEventArray[this->chatMessageRenderIndex].subjectPlayer]],
                        0, 0x13, FALSE, ((int)DAT_ButtonBackgroundBlendStrength::instance - 0x20) * 0x20 / 0x20 + 0x20);
                }
                MACRO_CALL_MEMBER(Text::TextManager_Func::renderMultilineText6Unk, DAT_TextManagerObject::ptr)(
                    this->DAT_ChatMessageArray[this->chatMessageRenderIndex],
                    DAT_TextManagerObject::instance.currentXOffset_0x0 + xPos + 6, yPos,
                    494 - DAT_TextManagerObject::instance.currentXOffset_0x0, 41727, 15974, 0x13,
                    ((int)DAT_ButtonBackgroundBlendStrength::instance - 0x20) * 0x20 / 0x20 + 0x20);
            }
            this->chatMessageRenderIndex -= 1;
            if (this->chatMessageRenderIndex < 0) {
                this->chatMessageRenderIndex = 19;
            }
            yPos -= 0x11;
            ++lines;
            if (lines >= 5) {
                break;
            }
        }
        DAT_TextManagerObject::instance.field_0x34 = 0;
        MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::setScreenMenuSurfaceHeightRangeToResolution,
            DAT_TextureRenderCoreObject::ptr)();
    }

}
}
