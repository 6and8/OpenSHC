#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/Text/UserTextHandler.func.hpp"
#include "OpenSHC/UI/Helpers.func.hpp"
#include "OpenSHC/string-literals.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_UserTextHandlerState.hpp"

namespace OpenSHC {
namespace UI {

    // FUNCTION: STRONGHOLDCRUSADER 0x00429650
    void Helpers::CallbackSetMultiplayerSpeedLevel()
    {
        MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand, DAT_GameSynchronyState::ptr)(
            Commands::GCT_CHANGE_GAME_INTENSITY_OR_BALANCE);
        DAT_GameSynchronyState::instance.field234_0x1072e8 = -1;
        DAT_GameSynchronyState::instance.field235_0x1072ec = -1;
        MACRO_CALL(OpenSHC::OS_Func::_sprintf)(DAT_GameSynchronyState::instance.receivedChatMessage, s__s__d_005a2284,
            MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(
                DE::SHCDE::TEXT_XPLAY_WAITING_ROOM, 0x52),
            DAT_GameSynchronyState::instance.skirmishGameSpeedLevel);
        MACRO_CALL_MEMBER(Text::UserTextHandler_Func::copyIntoTextArray, DAT_UserTextHandlerState::ptr)(
            DAT_GameSynchronyState::instance.receivedChatMessage);
        for (int player = 0; player < 9; ++player) {
            DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[player] = 1;
        }
        DAT_GameSynchronyState::instance
            .DAT_ChatMessageReceiverArray[DAT_GameSynchronyState::instance.currentPlayerSlotID] = 0;
        DAT_GameSynchronyState::instance.DAT_ChatTauntOrMessage = 10000;
        MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand, DAT_GameSynchronyState::ptr)(
            Commands::GCT_TAUNT_OR_CHAT);
        MACRO_CALL_MEMBER(Text::UserTextHandler_Func::clearEntry, DAT_UserTextHandlerState::ptr)(
            DAT_UserTextHandlerState::instance.textArrayIndex);
    }

}
}
