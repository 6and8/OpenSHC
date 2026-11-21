#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingLogicalState.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        using OpenSHC::Map::Buildings::BuildingLogicalState;

        // FUNCTION: STRONGHOLDCRUSADER 0x0040F8A0
        void BuildingsState::applySnoozedStateBasedOnPlayerData()
        {
            // Applies the snoozed settings of the owners and resets the production of buildings whose state changed
            for (int i = 1; i < this->maxBuildingsCount; ++i) {
                if (this->buildings[i].logicalState != BLS_NORMAL) {
                    continue;
                }
                if (this->buildings[i].buildingType >= 91) {
                    this->buildings[i].sleeping = false;
                    continue;
                }
                bool snoozed = DAT_GameState::instance.playerDataArray[this->buildings[i].owner]
                                   .snoozedBuildings[this->buildings[i].buildingType];
                if (this->buildings[i].sleeping == snoozed) {
                    continue;
                }
                OpenSHC::Map::Buildings::Building* const buildingPtr = &this->buildings[i];
                buildingPtr->sleeping = snoozed;
                buildingPtr->currentEmployeeCount = 0;
                buildingPtr->animationIndex = 0;
                buildingPtr->renderAnimation = 0;
                // state/field_0x11a and killingPitField/field_0x11e are cleared as ints
                *(int*)&buildingPtr->state = 0;
                *(int*)&buildingPtr->killingPitField = 0;
                for (int r = 0; r < 25; ++r) {
                    buildingPtr->resources[r] = 0;
                }
                for (int w = 0; w < 4; ++w) {
                    buildingPtr->workerUID[w] = 0;
                    buildingPtr->workerID[w] = 0;
                }
            }
        }

    }
}
}
