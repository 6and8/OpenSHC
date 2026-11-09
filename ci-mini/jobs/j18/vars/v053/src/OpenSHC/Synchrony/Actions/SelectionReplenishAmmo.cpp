#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Synchrony/Actions.func.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Synchrony {

    // FUNCTION: STRONGHOLDCRUSADER 0x00465F90
    void Actions::SelectionReplenishAmmo(int playerID, int tribeID)
    {
        for (int i = 0; i < (int)DAT_TribesState::instance.tribes[tribeID].size; ++i) {
            int const unitID = MACRO_CALL_MEMBER(
                Map::Units::TribesState_Func::getUnitIDForIndexInTribe, DAT_TribesState::ptr)(tribeID, i);
            if (DAT_UnitsState::instance.units[unitID].logicalState == 2
                && DAT_UnitsState::instance.units[unitID].dying == 0
                && (DAT_UnitsState::instance.units[unitID].unitType == Map::Units::UT_S_CATAPULT
                    || DAT_UnitsState::instance.units[unitID].unitType == Map::Units::UT_S_TREBUCHET)) {
                int const missing = 20 - DAT_UnitsState::instance.units[unitID].stoneAmmunition;
                if (missing > 0) {
                    int const stoneNeeded = (missing + 1) / 2;
                    if (DAT_GameState::instance.playerDataArray[playerID].currentResources[Game::Resources::RT_STONE]
                        < stoneNeeded) {
                        int const stoneLeft = DAT_GameState::instance.playerDataArray[playerID]
                                                  .currentResources[Game::Resources::RT_STONE];
                        if (stoneLeft > 0) {
                            MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::processResourceLoss,
                                DAT_BuildingsState::ptr)(playerID, Game::Resources::RT_STONE, stoneLeft, 0);
                            DAT_UnitsState::instance.units[unitID].stoneAmmunition += stoneLeft * 2;
                        }
                        return;
                    }
                    MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::processResourceLoss,
                        DAT_BuildingsState::ptr)(playerID, Game::Resources::RT_STONE, stoneNeeded, 0);
                    short* stoneAmmunitionPtr = &DAT_UnitsState::instance.units[unitID].stoneAmmunition;
                    *stoneAmmunitionPtr += missing;
                }
            }
        }
    }

}
}
