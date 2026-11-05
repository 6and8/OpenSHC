#include "../LandscapeState.func.hpp"

#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Map/Entities/EntityState.func.hpp"
#include "OpenSHC/Random/RNG.func.hpp"
#include "OpenSHC/Game/Player/Enums/BuildingEntryInfoEnum.hpp"

#include "OpenSHC/Globals/DAT_EntityState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/SEC_RNG.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Game::Player::Enums::BEIE_KEEP;

    // FUNCTION: STRONGHOLDCRUSADER 0x004F3150
    void LandscapeState::spawnCrowFromNearbyTree(int unitID)
    {
        BOOLEnum crowSoundPlayed = FALSE;
        for (int direction = 0; direction < 8; ++direction) {
            int const unitY = DAT_UnitsState::instance.units[unitID].y;
            short const treeID
                = DAT_TileMapState::instance
                      .OrganismLayer[DAT_TileMapState::instance.directionTranslationMatrix[unitY][direction]
                          + DAT_UnitsState::instance.units[unitID].tile];
            if (treeID == 0) {
                continue;
            }
            if (treeID >= this->maxTreeCount) {
                continue;
            }
            if (this->trees[treeID].state != 2) {
                continue;
            }
            if (this->trees[treeID].unknownDistanceRelatedToCrow == 0) {
                continue;
            }
            if (this->trees[treeID].rng200till300 != 0) {
                continue;
            }
            int const owner = DAT_UnitsState::instance.units[unitID].owner;
            int targetX = 0;
            int targetY = 0;
            int closestDistance = 10000;
            for (int playerID = 1; playerID < 9; ++playerID) {
                if (playerID == owner) {
                    continue;
                }
                if (DAT_GameState::instance.playerDataArray[playerID].buildingEntryInfos[BEIE_KEEP].id == 0) {
                    continue;
                }
                int const keepX
                    = DAT_GameState::instance.playerDataArray[playerID].buildingEntryInfos[BEIE_KEEP].xEntry;
                int const keepY
                    = DAT_GameState::instance.playerDataArray[playerID].buildingEntryInfos[BEIE_KEEP].yEntry;
                int const distanceX = abs(DAT_UnitsState::instance.units[unitID].x - keepX);
                int const distanceY = abs(unitY - keepY);
                int distance;
                if (distanceY < distanceX) {
                    distance = distanceX;
                } else {
                    distance = distanceY;
                }
                if (distance < closestDistance) {
                    targetX = SEC_RNG::instance.currentNumber2 % 5 + keepX - 2;
                    targetY = (SEC_RNG::instance.currentNumber2 >> 8) % 5 + keepY - 2;
                    closestDistance = distance;
                }
            }
            if (closestDistance == 10000) {
                targetX = DAT_UnitsState::instance.units[unitID].x + SEC_RNG::instance.currentNumber2 % 100 - 50;
                targetY = unitY + (SEC_RNG::instance.currentNumber2 >> 8) % 100 - 50;
                MACRO_CALL_MEMBER(Random::RNG_Func::nextRandomNumber2, SEC_RNG::ptr)();
            }
            MACRO_CALL_MEMBER(Entities::EntityState_Func::spawnProjectileEntity, DAT_EntityState::ptr)(unitID,
                DAT_UnitsState::instance.units[unitID].owner, 0, this->trees[treeID].xPosition * 8,
                this->trees[treeID].yPosition * 8,
                DAT_TileMapState::instance.HeightLayer[this->trees[treeID].tile] + 30, targetX * 8, targetY * 8, 250,
                Entities::EntityTypeInt__ET_CROW, 0);
            this->trees[treeID].rng200till300 = SEC_RNG::instance.currentNumber2 % 100 + 200;
            if (!crowSoundPlayed) {
                MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                    this->trees[treeID].xPosition, this->trees[treeID].yPosition, DE::SHCDE::FX_CROW);
                crowSoundPlayed = TRUE;
            }
        }
    }

}
}
