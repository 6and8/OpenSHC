#include "../EntityState.func.hpp"

#include "OpenSHC/Map/Navigation/DirectionAlgorithmState.func.hpp"
#include "OpenSHC/Random/RNG.func.hpp"

#include "OpenSHC/Globals/DAT_CurrentEntityID.hpp"
#include "OpenSHC/Globals/DAT_DirectionAlgorithmState.hpp"
#include "OpenSHC/Globals/DAT_EntityDefinedData.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"
#include "OpenSHC/Globals/SEC_RNG.hpp"

namespace OpenSHC {
namespace Map {
    namespace Entities {

        typedef void(__cdecl* EntityCallback)();

        // FUNCTION: STRONGHOLDCRUSADER 0x00404AE0
        uint EntityState::spawnProjectileEntity(int unitID, undefined4 playerID1, uint ownerColorUnk, int microX,
            int microY, int totalHeight, int targetX, int targetY, int targetZUnk, EntityType entityType, int param_11)
        {
            BOOLEnum markedUnk = FALSE;
            if ((entityType > 43 && entityType < 91) || entityType > 94) {
                return 0;
            }
            int entityID;
            if (entityType != -1) {
                if (entityType >= 40 && entityType <= 47) {
                    entityID = 1;
                    for (; entityID < 25; ++entityID) {
                        if (this->entityArray[entityID].logicalState == 0) {
                            break;
                        }
                        if (entityID >= 24) {
                            return 0;
                        }
                    }
                } else {
                    entityID = this->everyTenTicks;
                    for (; entityID < 3000; ++entityID) {
                        if (this->entityArray[entityID].logicalState == 0) {
                            break;
                        }
                        if (entityID >= 2999) {
                            switch (entityType) {
                            case 1:
                            case 2:
                            case 3:
                            case 4:
                            case 7:
                            case 8:
                            case 22:
                            case 23:
                            case 24:
                            case 25:
                            case 26:
                            case 33:
                            case 34:
                            case 35:
                            case 36:
                            case 37:
                            case 91:
                            case 92:
                            case 93:
                            case 94:
                                this->maxEntityCount = 3000;
                                for (entityID = 25; entityID < 3000; ++entityID) {
                                    if (this->entityArray[entityID].logicalState == 0) {
                                        goto setup;
                                    }
                                    switch (this->entityArray[entityID].entityType) {
                                    case 9:
                                    case 21:
                                    case 27:
                                    case 30:
                                    case 31:
                                        MACRO_CALL_MEMBER(EntityState_Func::deleteEntity, this)(entityID);
                                        goto setup;
                                    }
                                }
                                break;
                            }
                            this->everyTenTicks = 2999;
                            return 0;
                        }
                    }
                    if (entityID >= (int)this->maxEntityCount) {
                        this->maxEntityCount = entityID + 1;
                    }
                    this->everyTenTicks = entityID;
                }
            } else {
                entityID = 0;
                entityType = (EntityType)8;
            }
        // the reclaim loop over a full entity array jumps straight here (the original shares this block)
        setup:
            this->entityArray[entityID].rng_2 = 0;
            if (entityType == 91) {
                markedUnk = TRUE;
                this->entityArray[entityID].rng_2 = 1;
                entityType = (EntityType)1;
            } else if (entityType == ET_FIREBALLISTA) {
                markedUnk = TRUE;
                this->entityArray[entityID].field_0xd0 = 1;
                entityType = (EntityType)ET_BALLISTA;
            } else {
                if (entityType == ET_FIRETHROWER || entityType == ET_FIRETHROWER_UNTARGETED) {
                    markedUnk = TRUE;
                }
                if (entityType == 92) {
                    markedUnk = TRUE;
                    entityType = (EntityType)24;
                    this->entityArray[entityID].rng_2 = 1;
                } else if (entityType == 93) {
                    markedUnk = TRUE;
                    this->entityArray[entityID].rng_2 = 2;
                    entityType = (EntityType)1;
                } else if (entityType == 94) {
                    this->entityArray[entityID].rng_2 = 2;
                    markedUnk = TRUE;
                    entityType = (EntityType)24;
                } else if (entityType == 27) {
                    targetX = SEC_RNG::instance.currentNumber2 % 80 * 4 + targetX - 160;
                    targetY = (SEC_RNG::instance.currentNumber2 >> 8) % 80 * 4 + targetY - 160;
                } else if (entityType == 32) {
                    targetX = SEC_RNG::instance.currentNumber2 % 48 + targetX - 24;
                    targetY = (SEC_RNG::instance.currentNumber2 >> 8) % 48 + targetY - 24;
                }
            }
            switch (entityType) {
            case 1:
            case 2:
            case 3:
            case 4:
            case 7:
            case 20:
            case 23:
            case 24:
            case 25:
            case 27:
            case 32:
            case 33:
            case 34:
            case 35:
            case 36:
            case 37:
            case 91:
            case 92:
            case 93:
            case 94: {
                uint const tileY = microY / 8;
                uint const tileX = microX / 8;
                if (tileX > 399 || tileY > 399
                    || DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[tileY * 400 + tileX] == 0) {
                    return 0;
                }
                uint const targetTileY = targetY / 8;
                uint const targetTileX = targetX / 8;
                if (targetTileX > 399 || targetTileY > 399
                    || DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[targetTileY * 400 + targetTileX]
                        == 0) {
                    return 0;
                }
                break;
            }
            }
            if (entityID < 25) {
                this->entityArray[entityID].uid = 0;
            } else {
                this->entityArray[entityID].uid = DAT_GameCore::instance.uniqueGameObjectTracker;
                DAT_GameCore::instance.uniqueGameObjectTracker += 1;
            }
            this->entityArray[entityID].field_0x34 = DAT_GameCore::instance.mapTimeInTicks;
            this->entityArray[entityID].unitID_OR_seaGullID = unitID;
            this->entityArray[entityID].targetX = targetX;
            this->entityArray[entityID].targetY = targetY;
            this->entityArray[entityID].targetZ = targetZUnk;
            this->entityArray[entityID].heightDifference = targetZUnk - totalHeight;
            this->entityArray[entityID].unitID = param_11;
            this->entityArray[entityID].owner = playerID1;
            this->entityArray[entityID].microX = microX;
            this->entityArray[entityID].x_2 = microX;
            this->entityArray[entityID].microY = microY;
            this->entityArray[entityID].y_2 = microY;
            this->entityArray[entityID].height = totalHeight;
            this->entityArray[entityID].startingHeight_2 = totalHeight;
            this->entityArray[entityID].height_2 = totalHeight;
            this->entityArray[entityID].startingHeight = totalHeight;
            this->entityArray[entityID].logicalState = 1;
            this->entityArray[entityID].unkMinusOne = 0;
            MACRO_CALL_MEMBER(Navigation::DirectionAlgorithmState_Func::somethingWithProjectileDistance,
                DAT_DirectionAlgorithmState::ptr)(microX, microY, targetX, targetY);
            this->entityArray[entityID].orientation = DAT_DirectionAlgorithmState::instance.orientation;
            this->entityArray[entityID].colorUnk = 0;
            if (entityType == 10 || entityType == 11 || entityType == 12 || entityType == 13) {
                this->entityArray[entityID].colorUnk = ownerColorUnk;
            }
            MACRO_CALL_MEMBER(EntityState_Func::setProjectileEntityValues2, this)(entityID, entityType);
            if (this->entityArray[entityID].rng_2 != 0) {
                this->entityArray[entityID].gmID = 145;
            }
            this->entityArray[entityID].field_0x12 = 0;
            this->entityArray[entityID].unknownAnimationFrameRelated = 0;
            if (entityType == ET_DUST_CLOUD) {
                if (param_11 == 1) {
                    this->entityArray[entityID].unknownAnimationFrameRelated = 200;
                }
            } else if (entityType == 8) {
                this->entityArray[entityID].rng_1 = DAT_UnitsState::instance.units[unitID].fixedRng;
                // the original skips the random number setup for type 8 and joins the velocity call
                goto velocities;
            }
            this->entityArray[entityID].rng_1 = SEC_RNG::instance.currentNumber2;
            if (entityID >= 25) {
                MACRO_CALL_MEMBER(Random::RNG_Func::nextRandomNumber2, SEC_RNG::ptr)();
            }
            if (entityType == ET_SEAGULLUnk) {
                this->entityArray[entityID].rng_2 = SEC_RNG::instance.currentNumber2 % 100 + 120;
            } else if (entityType == 31) {
                if (unitID != 0) {
                    this->entityArray[entityID].unkOne_1 = 2;
                }
            } else if (entityType == ET_HEADS_ON_SPIKES) {
                this->entityArray[entityID].rng_2 = SEC_RNG::instance.currentNumber2 % 500 + 300;
                this->entityArray[entityID].rng_1 = ownerColorUnk;
            }
        velocities:
            MACRO_CALL_MEMBER(EntityState_Func::initializeProjectileVelocities, this)(
                entityID, microX, microY, totalHeight, targetX, targetY, targetZUnk);
            if (this->entityArray[entityID].entityType == 24) {
                this->entityArray[entityID].entityType = 1;
            }
            if (this->entityArray[entityID].entityType == 25) {
                this->entityArray[entityID].entityType = 7;
            }
            if (this->entityArray[entityID].entityType == 35) {
                this->entityArray[entityID].entityType = ET_SLINGER;
            }
            if (this->entityArray[entityID].entityType == ET_FIRETHROWER_UNTARGETED) {
                this->entityArray[entityID].entityType = ET_FIRETHROWER;
            }
            if (markedUnk) {
                this->entityArray[entityID].gmLookupValue = 1;
            }
            if (entityID != 0) {
                MACRO_CALL_MEMBER(EntityState_Func::processEntityHitBuildingOrUnit, this)(entityID);
                MACRO_CALL_MEMBER(EntityState_Func::calculateEntityDrawOffset, this)(entityID);
                uint const savedEntityID = DAT_CurrentEntityID::instance;
                DAT_CurrentEntityID::instance = entityID;
                ((EntityCallback)
                        DAT_EntityDefinedData::instance.EntityCallbacks[this->entityArray[entityID].entityType])();
                DAT_CurrentEntityID::instance = savedEntityID;
            }
            return entityID;
        }
    }
}
}
