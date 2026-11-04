#include "../GameSynchronyState.func.hpp"

#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/UI/Helpers.func.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MouseState.hpp"

namespace OpenSHC {
namespace Synchrony {

    // FUNCTION: STRONGHOLDCRUSADER 0x0047E240
    void GameSynchronyState::disconnectDPlay()
    {
        DAT_MouseState::instance.waitCursorToggle = 1;
        MACRO_CALL(UI::Helpers_Func::SetCursorDependingOnProgramState)();
        MACRO_CALL_MEMBER(GameSynchronyState_Func::clearSessionsList, this)();
        for (int provider = 0; provider < this->scrollBarItemCount; ++provider) {
            MACRO_CALL(OS_Func::_free_base)((void*)DAT_GameSynchronyState::instance.providerNames[provider]);
            GlobalUnlock(GlobalHandle(DAT_GameSynchronyState::instance.guids[provider]));
            GlobalFree(GlobalHandle(DAT_GameSynchronyState::instance.guids[provider]));
            DAT_GameSynchronyState::instance.providerNames[provider] = NULL;
            DAT_GameSynchronyState::instance.guids[provider] = NULL;
        }
        this->scrollBarItemCount = 0;
        for (int modem = 0; modem < this->modemScrollbarCount; ++modem) {
            MACRO_CALL(OS_Func::_free_base)(DAT_GameSynchronyState::instance.stringPointerArray[modem]);
        }
        this->modemScrollbarCount = 0;
        if (this->DPLAYX_4A != NULL) {
            this->DPLAYX_4A->CancelMessage(0, 0);
            this->DPLAYX_4A->DestroyPlayer(this->DPLAYX_PlayerHandle);
            this->DPLAYX_4A->Close();
            this->DPLAYX_4A = NULL;
        }
        if (this->DPLAYX_LOBBY != NULL) {
            this->DPLAYX_LOBBY->Release();
            this->DPLAYX_LOBBY = NULL;
        }
        if (this->DPLAYX_Connection != NULL) {
            GlobalUnlock(GlobalHandle(this->DPLAYX_Connection));
            GlobalFree(GlobalHandle(this->DPLAYX_Connection));
            this->DPLAYX_Connection = NULL;
        }
        this->scrollBarItemCount = 0;
        this->currentGameMode = Game::GM_SOLITARY;
        this->DAT_GameHalted = 0;
        this->syncStatus = 0;
        this->flag_0xbec = 0;
        this->useTCPIP = FALSE;
        this->quitGameVoteRelated = 0;
        this->saveRelated = 0;
        DAT_MouseState::instance.waitCursorToggle = 0;
    }

}
}
