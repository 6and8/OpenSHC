#include "OpenSHC/UI/Helpers.func.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace UI {

    // FUNCTION: STRONGHOLDCRUSADER 0x0043E5A0
    undefined4 Helpers::SomeFearFactorComputation()
    {
        OpenSHC::Game::Player::PlayerData* const playerDataPtr = &DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID];
        int const fearFactor
            = playerDataPtr->fearFactorLevel;
        if (fearFactor <= -5) {
            return 0xe;
        }
        if (fearFactor <= -3) {
            return 0xf;
        }
        if (fearFactor <= -1) {
            return 0x10;
        }
        if (fearFactor >= 5) {
            return 0x13;
        }
        if (fearFactor >= 3) {
            return 0x12;
        }
        return 0x11;
    }

}
}
