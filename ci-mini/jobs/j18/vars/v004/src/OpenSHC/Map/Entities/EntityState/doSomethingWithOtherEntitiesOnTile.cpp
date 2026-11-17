#include "../EntityState.func.hpp"

#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Entities {

        // FUNCTION: STRONGHOLDCRUSADER 0x00401460
        void EntityState::doSomethingWithOtherEntitiesOnTile(uint entityID)
        {
            int const tile = this->entityArray[entityID].tile;
            int count = 0;
            if (tile == 0) {
                return;
            }
            int previousID;
            if ((int)entityID < 25) {
                char const EntityLayerLT25Value = DAT_TileMapState::instance.EntityLayerLT25[tile];
                int nextID = (byte)EntityLayerLT25Value;
                if (nextID == entityID) {
                    EntityLayerLT25Value
                        = (char)this->entityArray[entityID].nextEntityOnThisTileByID;
                    this->entityArray[entityID].nextEntityOnThisTileByID = 0;
                    return;
                }
                previousID = nextID;
                for (; nextID != 0;) {
                    if (++count >= 100) {
                        break;
                    }
                    previousID = nextID;
                    nextID = this->entityArray[previousID].nextEntityOnThisTileByID;
                    if (nextID == entityID) {
                        this->entityArray[previousID].nextEntityOnThisTileByID
                            = this->entityArray[entityID].nextEntityOnThisTileByID;
                        this->entityArray[entityID].nextEntityOnThisTileByID = 0;
                        return;
                    }
                    if (nextID == 0) {
                        return;
                    }
                }
            } else {
                int nextID = DAT_TileMapState::instance.EntityLayer[tile];
                if (nextID == entityID) {
                    DAT_TileMapState::instance.EntityLayer[tile] = this->entityArray[entityID].nextEntityOnThisTileByID;
                    this->entityArray[entityID].nextEntityOnThisTileByID = 0;
                    return;
                }
                previousID = nextID;
                for (; nextID != 0;) {
                    if (++count >= 100) {
                        break;
                    }
                    previousID = nextID;
                    nextID = this->entityArray[previousID].nextEntityOnThisTileByID;
                    if (nextID == entityID) {
                        this->entityArray[previousID].nextEntityOnThisTileByID
                            = this->entityArray[entityID].nextEntityOnThisTileByID;
                        this->entityArray[entityID].nextEntityOnThisTileByID = 0;
                        return;
                    }
                    if (nextID == 0) {
                        return;
                    }
                }
            }
            this->entityArray[previousID].nextEntityOnThisTileByID
                = this->entityArray[entityID].nextEntityOnThisTileByID;
            this->entityArray[entityID].nextEntityOnThisTileByID = 0;
        }

    }
}
}
