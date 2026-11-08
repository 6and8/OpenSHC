#include "../EntityState.func.hpp"

#include "OpenSHC/Map/TileMapState.func.hpp"

#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Entities {

        // FUNCTION: STRONGHOLDCRUSADER 0x00405DA0
        void EntityState::spawnProjectileImpactDebris(int entityID)
        {
            int const microX = this->entityArray[entityID].microX;
            int const microY = this->entityArray[entityID].microY;
            int const subY = microY & 7;
            int const subX = microX & 7;
            int targetY = 0;
            int targetX = 0;
            int const flags = MACRO_CALL_MEMBER(TileMapState_Func::setBitFlagBasedOnWallTowerGatehouseOrKeep,
                DAT_TileMapState::ptr)(microX / 8, microY / 8);
            int first;
            int second;
            switch (this->entityArray[entityID].orientation) {
            case 61:
                first = subX;
                second = 7 - subY;
                if (first == second) {
                    switch (flags & 10) {
                    case 0:
                    case 8:
                        second = 100;
                        break;
                    case 2:
                        first = 100;
                        break;
                    case 10:
                        goto reverse;
                    }
                }
                if (first > second) {
                    targetX = this->entityArray[entityID].microX * 2 - this->entityArray[entityID].x_2;
                    targetY = this->entityArray[entityID].y_2;
                } else {
                    targetY = this->entityArray[entityID].microY * 2 - this->entityArray[entityID].y_2;
                    targetX = this->entityArray[entityID].x_2;
                }
                break;
            case 62:
                first = subX;
                second = 7 - subY;
                if (first == second) {
                    switch (flags & 10) {
                    case 0:
                    case 8:
                        second = 100;
                        break;
                    case 2:
                        first = 100;
                        break;
                    case 10:
                        goto reverse;
                    }
                }
                if (first > second) {
                    targetX = this->entityArray[entityID].microX * 2 - this->entityArray[entityID].x_2;
                    targetY = this->entityArray[entityID].y_2;
                } else {
                    targetY = this->entityArray[entityID].microY * 2 - this->entityArray[entityID].y_2;
                    targetX = this->entityArray[entityID].x_2;
                }
                break;
            case 63:
                first = subX;
                second = 7 - subY;
                if (first == second) {
                    switch (flags & 10) {
                    case 8:
                        second = 100;
                        break;
                    case 0:
                    case 2:
                        first = 100;
                        break;
                    case 10:
                        goto reverse;
                    }
                }
                if (first > second) {
                    targetX = this->entityArray[entityID].microX * 2 - this->entityArray[entityID].x_2;
                    targetY = this->entityArray[entityID].y_2;
                } else {
                    targetY = this->entityArray[entityID].microY * 2 - this->entityArray[entityID].y_2;
                    targetX = this->entityArray[entityID].x_2;
                }
                break;
            case 65:
                first = subX;
                second = subY;
                if (first == second) {
                    switch (flags & 130) {
                    case 128:
                        first = 100;
                        break;
                    case 0:
                    case 2:
                        second = 100;
                        break;
                    case 130:
                        goto reverse;
                    }
                }
                if (first > second) {
                    targetX = this->entityArray[entityID].microX * 2 - this->entityArray[entityID].x_2;
                    targetY = this->entityArray[entityID].y_2;
                } else {
                    targetY = this->entityArray[entityID].microY * 2 - this->entityArray[entityID].y_2;
                    targetX = this->entityArray[entityID].x_2;
                }
                break;
            case 66:
                first = subX;
                second = subY;
                if (first == second) {
                    switch (flags & 130) {
                    case 128:
                        first = 100;
                        break;
                    case 0:
                    case 2:
                        second = 100;
                        break;
                    case 130:
                        goto reverse;
                    }
                }
                if (first > second) {
                    targetX = this->entityArray[entityID].microX * 2 - this->entityArray[entityID].x_2;
                    targetY = this->entityArray[entityID].y_2;
                } else {
                    targetY = this->entityArray[entityID].microY * 2 - this->entityArray[entityID].y_2;
                    targetX = this->entityArray[entityID].x_2;
                }
                break;
            case 67:
                first = subX;
                second = subY;
                if (first == second) {
                    switch (flags & 130) {
                    case 2:
                        second = 100;
                        break;
                    case 0:
                    case 128:
                        first = 100;
                        break;
                    case 130:
                        goto reverse;
                    }
                }
                if (first > second) {
                    targetX = this->entityArray[entityID].microX * 2 - this->entityArray[entityID].x_2;
                    targetY = this->entityArray[entityID].y_2;
                } else {
                    targetY = this->entityArray[entityID].microY * 2 - this->entityArray[entityID].y_2;
                    targetX = this->entityArray[entityID].x_2;
                }
                break;
            case 69:
                first = 7 - subX;
                second = subY;
                if (first == second) {
                    switch (flags & 160) {
                    case 32:
                        first = 100;
                        break;
                    case 0:
                    case 128:
                        second = 100;
                        break;
                    case 160:
                        goto reverse;
                    }
                }
                if (first > second) {
                    targetX = this->entityArray[entityID].microX * 2 - this->entityArray[entityID].x_2;
                    targetY = this->entityArray[entityID].y_2;
                } else {
                    targetY = this->entityArray[entityID].microY * 2 - this->entityArray[entityID].y_2;
                    targetX = this->entityArray[entityID].x_2;
                }
                break;
            case 70:
                first = 7 - subX;
                second = subY;
                if (first == second) {
                    switch (flags & 160) {
                    case 32:
                        first = 100;
                        break;
                    case 0:
                    case 128:
                        second = 100;
                        break;
                    case 160:
                        goto reverse;
                    }
                }
                if (first > second) {
                    targetX = this->entityArray[entityID].microX * 2 - this->entityArray[entityID].x_2;
                    targetY = this->entityArray[entityID].y_2;
                } else {
                    targetY = this->entityArray[entityID].microY * 2 - this->entityArray[entityID].y_2;
                    targetX = this->entityArray[entityID].x_2;
                }
                break;
            case 71:
                first = 7 - subX;
                second = subY;
                if (first == second) {
                    switch (flags & 160) {
                    case 128:
                        second = 100;
                        break;
                    case 0:
                    case 32:
                        first = 100;
                        break;
                    case 160:
                        goto reverse;
                    }
                }
                if (!(first > second)) {
                    targetY = this->entityArray[entityID].microY * 2 - this->entityArray[entityID].y_2;
                    targetX = this->entityArray[entityID].x_2;
                } else {
                    targetX = this->entityArray[entityID].microX * 2 - this->entityArray[entityID].x_2;
                    targetY = this->entityArray[entityID].y_2;
                }
                break;
            case 73:
                first = 7 - subX;
                second = 7 - subY;
                if (first == second) {
                    switch (flags & 40) {
                    case 8:
                        second = 100;
                        break;
                    case 0:
                    case 32:
                        first = 100;
                        break;
                    case 40:
                        goto reverse;
                    }
                }
                if (first > second) {
                    targetX = this->entityArray[entityID].microX * 2 - this->entityArray[entityID].x_2;
                    targetY = this->entityArray[entityID].y_2;
                } else {
                    targetY = this->entityArray[entityID].microY * 2 - this->entityArray[entityID].y_2;
                    targetX = this->entityArray[entityID].x_2;
                }
                break;
            case 74:
                first = 7 - subX;
                second = 7 - subY;
                if (first == second) {
                    switch (flags & 40) {
                    case 0:
                    case 8:
                        second = 100;
                        break;
                    case 32:
                        first = 100;
                        break;
                    case 40:
                        goto reverse;
                    }
                }
                if (first > second) {
                    targetX = this->entityArray[entityID].microX * 2 - this->entityArray[entityID].x_2;
                    targetY = this->entityArray[entityID].y_2;
                } else {
                    targetY = this->entityArray[entityID].microY * 2 - this->entityArray[entityID].y_2;
                    targetX = this->entityArray[entityID].x_2;
                }
                break;
            case 75:
                first = 7 - subX;
                second = 7 - subY;
                if (first == second) {
                    switch (flags & 40) {
                    case 0:
                    case 8:
                        second = 100;
                        break;
                    case 32:
                        first = 100;
                        break;
                    case 40:
                        goto reverse;
                    }
                }
                if (first > second) {
                    targetX = this->entityArray[entityID].microX * 2 - this->entityArray[entityID].x_2;
                    targetY = this->entityArray[entityID].y_2;
                } else {
                    targetY = this->entityArray[entityID].microY * 2 - this->entityArray[entityID].y_2;
                    targetX = this->entityArray[entityID].x_2;
                }
                break;
            case 60:
            case 64:
            case 68:
            case 72:
            reverse:
                targetY = this->entityArray[entityID].y_2;
                targetX = this->entityArray[entityID].x_2;
                break;
            }
            for (int i = 0; i < this->entityArray[entityID].rng_1 % 8 + 5; ++i) {
                MACRO_CALL_MEMBER(EntityState_Func::spawnProjectileEntity, this)(0, 0, 0, microX, microY,
                    this->entityArray[entityID].height, targetX, targetY, 8, (EntityType)27, 0);
            }
            MACRO_CALL_MEMBER(EntityState_Func::spawnProjectileEntity, this)(0, 0, 0, microX, microY,
                this->entityArray[entityID].height, microX + 1, microY + 1, this->entityArray[entityID].height,
                (EntityType)30, 0);
        }

    } // namespace Entities
} // namespace Map
} // namespace OpenSHC
