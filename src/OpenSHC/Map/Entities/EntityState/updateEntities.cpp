#include "../EntityState.func.hpp"

#include "OpenSHC/Random/RNG.func.hpp"

#include "OpenSHC/Globals/DAT_CurrentEntityID.hpp"
#include "OpenSHC/Globals/DAT_EntityDefinedData.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/SEC_RNG.hpp"

namespace OpenSHC {
namespace Map {
    namespace Entities {

        typedef void(__cdecl* EntityCallback)();

        // FUNCTION: STRONGHOLDCRUSADER 0x004087C0
        void EntityState::updateEntities()
        {
            if (DAT_GameState::instance.gameTicksLoadBalancer % 10 == 0) {
                this->everyTenTicks = 25;
            }
            this->totalEntityCount = 0;
            DAT_CurrentEntityID::instance = 1;
            int highestEntityID = 0;
            for (; (int)DAT_CurrentEntityID::instance < (int)this->maxEntityCount; DAT_CurrentEntityID::instance++) {
                if (this->entityArray[DAT_CurrentEntityID::instance].logicalState == 0) {
                    continue;
                }
                this->totalEntityCount += 1;
                highestEntityID = DAT_CurrentEntityID::instance + 1;
                switch (this->entityArray[DAT_CurrentEntityID::instance].logicalState) {
                case 1:
                    this->entityArray[DAT_CurrentEntityID::instance].logicalState = 2;
                    break;
                case 3:
                    MACRO_CALL_MEMBER(EntityState_Func::deleteEntity, this)(DAT_CurrentEntityID::instance);
                    continue;
                case 5:
                    this->entityArray[DAT_CurrentEntityID::instance].logicalState = 6;
                    break;
                case 4:
                    MACRO_CALL_MEMBER(EntityState_Func::activateProjectileEntity, this)(DAT_CurrentEntityID::instance);
                    break;
                case 7:
                    MACRO_CALL_MEMBER(EntityState_Func::tickEntityDecayCounter, this)(DAT_CurrentEntityID::instance);
                    continue;
                case 8:
                    MACRO_CALL_MEMBER(EntityState_Func::tickEntityDecayCounter, this)(DAT_CurrentEntityID::instance);
                    break;
                }
                if (DAT_CurrentEntityID::instance
                    == this->entityArray[DAT_CurrentEntityID::instance].nextEntityOnThisTileByID) {
                    MACRO_CALL_MEMBER(EntityState_Func::deleteEntity, this)(DAT_CurrentEntityID::instance);
                    continue;
                }
                if (this->entityArray[DAT_CurrentEntityID::instance].field_0x12
                    >= this->entityArray[DAT_CurrentEntityID::instance].unkOne_1) {
                    this->entityArray[DAT_CurrentEntityID::instance].unknownAnimationFrameRelated += 1;
                    this->entityArray[DAT_CurrentEntityID::instance].field_0x12 = 0;
                }
                this->entityArray[DAT_CurrentEntityID::instance].field_0x12 += 1;
                if (this->entityArray[DAT_CurrentEntityID::instance].logicalState != 6) {
                    switch (this->entityArray[DAT_CurrentEntityID::instance].entityType) {
                    case 9:
                        break;
                    case 21:
                        if (this->entityArray[DAT_CurrentEntityID::instance].unitID != 2) {
                            if (this->entityArray[DAT_CurrentEntityID::instance].unknownAnimationFrameRelated & 1) {
                                MACRO_CALL_MEMBER(EntityState_Func::doSomethingWithOtherEntitiesOnTile, this)(
                                    DAT_CurrentEntityID::instance);
                                this->entityArray[DAT_CurrentEntityID::instance].height += 1;
                                if (this->entityArray[DAT_CurrentEntityID::instance].startingAngle < 0) {
                                    if (this->entityArray[DAT_CurrentEntityID::instance].unknownAnimationFrameRelated
                                            % this->entityArray[DAT_CurrentEntityID::instance].startingAngle
                                        == 0) {
                                        this->entityArray[DAT_CurrentEntityID::instance].microX -= 1;
                                    }
                                } else if (this->entityArray[DAT_CurrentEntityID::instance]
                                                   .unknownAnimationFrameRelated
                                               % this->entityArray[DAT_CurrentEntityID::instance].startingAngle
                                           == 0) {
                                    this->entityArray[DAT_CurrentEntityID::instance].microX += 1;
                                }
                                if (this->entityArray[DAT_CurrentEntityID::instance].velocityUnk < 0) {
                                    if (this->entityArray[DAT_CurrentEntityID::instance].unknownAnimationFrameRelated
                                            % this->entityArray[DAT_CurrentEntityID::instance].velocityUnk
                                        == 0) {
                                        this->entityArray[DAT_CurrentEntityID::instance].microY -= 1;
                                    }
                                } else if (this->entityArray[DAT_CurrentEntityID::instance]
                                                   .unknownAnimationFrameRelated
                                               % this->entityArray[DAT_CurrentEntityID::instance].velocityUnk
                                           == 0) {
                                    this->entityArray[DAT_CurrentEntityID::instance].microY += 1;
                                }
                                MACRO_CALL_MEMBER(EntityState_Func::processEntityHitBuildingOrUnit, this)(
                                    DAT_CurrentEntityID::instance);
                                MACRO_CALL_MEMBER(EntityState_Func::calculateEntityDrawOffset, this)(
                                    DAT_CurrentEntityID::instance);
                            }
                        } else if (this->entityArray[DAT_CurrentEntityID::instance].unknownAnimationFrameRelated & 1) {
                            MACRO_CALL_MEMBER(EntityState_Func::doSomethingWithOtherEntitiesOnTile, this)(
                                DAT_CurrentEntityID::instance);
                            this->entityArray[DAT_CurrentEntityID::instance].height += 1;
                            if (this->entityArray[DAT_CurrentEntityID::instance].startingAngle < 0) {
                                if (this->entityArray[DAT_CurrentEntityID::instance].unknownAnimationFrameRelated
                                        % this->entityArray[DAT_CurrentEntityID::instance].startingAngle
                                    == 0) {
                                    this->entityArray[DAT_CurrentEntityID::instance].microX -= 1;
                                }
                            } else if (this->entityArray[DAT_CurrentEntityID::instance].unknownAnimationFrameRelated
                                           % this->entityArray[DAT_CurrentEntityID::instance].startingAngle
                                       == 0) {
                                this->entityArray[DAT_CurrentEntityID::instance].microX += 1;
                            }
                            if (this->entityArray[DAT_CurrentEntityID::instance].velocityUnk < 0) {
                                if (this->entityArray[DAT_CurrentEntityID::instance].unknownAnimationFrameRelated
                                        % this->entityArray[DAT_CurrentEntityID::instance].velocityUnk
                                    == 0) {
                                    this->entityArray[DAT_CurrentEntityID::instance].microY -= 1;
                                }
                            } else if (this->entityArray[DAT_CurrentEntityID::instance].unknownAnimationFrameRelated
                                           % this->entityArray[DAT_CurrentEntityID::instance].velocityUnk
                                       == 0) {
                                this->entityArray[DAT_CurrentEntityID::instance].microY += 1;
                            }
                            MACRO_CALL_MEMBER(EntityState_Func::processEntityHitBuildingOrUnit, this)(
                                DAT_CurrentEntityID::instance);
                            MACRO_CALL_MEMBER(EntityState_Func::calculateEntityDrawOffset, this)(
                                DAT_CurrentEntityID::instance);
                        }
                        break;
                    case 26:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                        this->entityArray[DAT_CurrentEntityID::instance].height += 1;
                        break;
                    case 22:
                        this->entityArray[DAT_CurrentEntityID::instance].velocityUnk += 1;
                        if (this->entityArray[DAT_CurrentEntityID::instance].velocityUnk > 30) {
                            MACRO_CALL_MEMBER(EntityState_Func::doSomethingWithOtherEntitiesOnTile, this)(
                                DAT_CurrentEntityID::instance);
                            if (this->entityArray[DAT_CurrentEntityID::instance].velocityUnk != 1000) {
                                this->entityArray[DAT_CurrentEntityID::instance].graphicRotationUnk -= 1;
                                if ((short)this->entityArray[DAT_CurrentEntityID::instance].graphicRotationUnk <= 0) {
                                    this->entityArray[DAT_CurrentEntityID::instance].graphicRotationUnk
                                        = (char)(((byte*)&SEC_RNG::instance.currentNumber2)[1] & 63);
                                    this->entityArray[DAT_CurrentEntityID::instance].startingAngle
                                        = (SEC_RNG::instance.currentNumber2 >> 4) & 7;
                                    MACRO_CALL_MEMBER(OpenSHC::Random::RNG_Func::nextRandomNumber2, SEC_RNG::ptr)();
                                }
                            }
                            this->entityArray[DAT_CurrentEntityID::instance].velocityUnk = 0;
                            switch (this->entityArray[DAT_CurrentEntityID::instance].startingAngle) {
                            case 0:
                                this->entityArray[DAT_CurrentEntityID::instance].microY -= 1;
                                break;
                            case 4:
                                this->entityArray[DAT_CurrentEntityID::instance].microY += 1;
                                break;
                            case 2:
                                this->entityArray[DAT_CurrentEntityID::instance].microX += 1;
                                break;
                            case 6:
                                this->entityArray[DAT_CurrentEntityID::instance].microX -= 1;
                                break;
                            case 7:
                                this->entityArray[DAT_CurrentEntityID::instance].microX -= 1;
                                this->entityArray[DAT_CurrentEntityID::instance].microY -= 1;
                                break;
                            case 1:
                                this->entityArray[DAT_CurrentEntityID::instance].microX += 1;
                                this->entityArray[DAT_CurrentEntityID::instance].microY -= 1;
                                break;
                            case 5:
                                this->entityArray[DAT_CurrentEntityID::instance].microX -= 1;
                                this->entityArray[DAT_CurrentEntityID::instance].microY += 1;
                                break;
                            case 3:
                                this->entityArray[DAT_CurrentEntityID::instance].microX += 1;
                                this->entityArray[DAT_CurrentEntityID::instance].microY += 1;
                                break;
                            }
                            MACRO_CALL_MEMBER(EntityState_Func::processEntityHitBuildingOrUnit, this)(
                                DAT_CurrentEntityID::instance);
                            MACRO_CALL_MEMBER(EntityState_Func::calculateEntityDrawOffset, this)(
                                DAT_CurrentEntityID::instance);
                        }
                        this->entityArray[DAT_CurrentEntityID::instance].height
                            = DAT_TileMapState::instance
                                  .HeightLayer[this->entityArray[DAT_CurrentEntityID::instance].tile]
                            + 20;
                        break;
                    case 10:
                    case 11:
                    case 12:
                    case 13:
                    case 14:
                    case 15:
                        MACRO_CALL_MEMBER(EntityState_Func::doSomethingWithOtherEntitiesOnTile, this)(
                            DAT_CurrentEntityID::instance);
                        MACRO_CALL_MEMBER(EntityState_Func::processEntityHitBuildingOrUnit, this)(
                            DAT_CurrentEntityID::instance);
                        break;
                    default:
                        this->entityArray[DAT_CurrentEntityID::instance].screenDirection
                            = (short)this->entityArray[DAT_CurrentEntityID::instance].orientation - 60;
                        this->entityArray[DAT_CurrentEntityID::instance].screenDirection
                            += -DAT_TileMapState::instance.mapOrientation * 2;
                        if (this->entityArray[DAT_CurrentEntityID::instance].screenDirection < 0) {
                            this->entityArray[DAT_CurrentEntityID::instance].screenDirection += 16;
                        }
                        if (this->entityArray[DAT_CurrentEntityID::instance].speedUnk != 0.0f) {
                            short const effectType = this->entityArray[DAT_CurrentEntityID::instance].gmLookupValue;
                            if (effectType != 0
                                && this->entityArray[DAT_CurrentEntityID::instance].someCounter_OR_hitGround == 0) {
                                Entity* const entity = &this->entityArray[DAT_CurrentEntityID::instance];
                                if (effectType != 3) {
                                    MACRO_CALL_MEMBER(EntityState_Func::spawnEntityEffect2, this)(
                                        entity->microX, entity->microY, entity->height, 5, effectType);
                                } else {
                                    MACRO_CALL_MEMBER(EntityState_Func::spawnEntityEffect1, this)(entity->microX,
                                        entity->microY, entity->height, 6, entity->gmID, entity->graphicType2);
                                }
                            }
                        }
                        if (this->entityArray[DAT_CurrentEntityID::instance].someCounter_OR_hitGround == 0) {
                            MACRO_CALL_MEMBER(EntityState_Func::moveProjectileEntity, this)(
                                DAT_CurrentEntityID::instance);
                        }
                        break;
                    }
                }
                ((EntityCallback)DAT_EntityDefinedData::instance
                        .EntityCallbacks[this->entityArray[DAT_CurrentEntityID::instance].entityType])();
                if (this->entityArray[DAT_CurrentEntityID::instance].entityType == ET_SEAGULLUnk) {
                    MACRO_CALL_MEMBER(EntityState_Func::processSeaGulls, this)(
                        this->entityArray[DAT_CurrentEntityID::instance].unitID_OR_seaGullID);
                }
            }
            this->maxEntityCount = highestEntityID;
        }

    } // namespace Entities
} // namespace Map
} // namespace OpenSHC
