#include "OpenSHC/UI/Helpers.func.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace UI {

    // FUNCTION: STRONGHOLDCRUSADER 0x0043E5F0
    int Helpers::SomeGoldRelatedComputation()
    {
        int const gold = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                             .currentResources[OpenSHC::Game::Resources::RT_GOLD];
        if (gold == 0) {
            return 0x1d;
        }
        if (gold >= 1000) {
            return 0x20;
        }
        int const blessed
            = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                  .blessedPeoplePercentage;
        if (blessed >= 80) {
            return 0x17;
        }
        int const inns = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                             .workingInnsCount;
        if (inns >= 3) {
            return 0x1b;
        }
        if (blessed >= 40) {
            return 0x16;
        }
        if (inns == 2) {
            return 0x1a;
        }
        if (gold >= 5000) {
            return 0x1f;
        }
        if (blessed >= 20) {
            return 0x15;
        }
        if (inns == 1) {
            return 0x19;
        }
        if (gold < 500) {
            return 0x1e;
        }
        if (DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                .totalEnemyUnitsCount
            > 4) {
            return 0x24;
        }
        if (DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                .currentPopulation
            == 0) {
            return 0x22;
        }
        if (DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                .currentPopulation
            >= 5) {
            return 0x27;
        }
        return 0x23;
    }

}
}
