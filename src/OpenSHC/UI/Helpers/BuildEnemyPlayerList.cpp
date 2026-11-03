#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/UI/Helpers.func.hpp"

#include "OpenSHC/Globals/DAT_EnemyArrayIndex.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_RequestedGoodsByWhoArray.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace UI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004AC650
    void Helpers::BuildEnemyPlayerList()
    {
        int const team
            = DAT_GameState::instance.mapAndTime.playerTeams[DAT_GameSynchronyState::instance.currentPlayerSlotID];
        DAT_EnemyArrayIndex::instance = 0;
        for (int player = 1; player < 9; ++player) {
            if (player == DAT_GameSynchronyState::instance.currentPlayerSlotID) {
                continue;
            }
            if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[player] == -1
                && DAT_GameSynchronyState::instance.currentAIArray[player] == 0) {
                continue;
            }
            if (DAT_GameCore::instance.mapTimeInTicks - (int)DAT_GameCore::instance.section1127 > 400
                && MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::getAliveLordForPlayer, DAT_UnitsState::ptr)(player)
                    == 0) {
                continue;
            }
            if (team == DAT_GameState::instance.mapAndTime.playerTeams[player]) {
                continue;
            }
            DAT_RequestedGoodsByWhoArray::instance[DAT_EnemyArrayIndex::instance + 1] = player;
            DAT_EnemyArrayIndex::instance += 1;
            if ((int)DAT_EnemyArrayIndex::instance >= 6) {
                break;
            }
        }
    }

}
}
