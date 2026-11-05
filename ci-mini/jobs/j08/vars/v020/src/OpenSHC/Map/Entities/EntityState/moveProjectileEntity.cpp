#include "../EntityState.func.hpp"

#include <math.h>

#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/DE/SHCDE/eSFX.hpp"
#include "OpenSHC/Globals/DAT_EntityDefinedData.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"
#include "OpenSHC/Map/Entities/EntityType.hpp"

namespace OpenSHC {
namespace Map {
    namespace Entities {

        using OpenSHC::Map::Entities::EntityType;

        // FUNCTION: STRONGHOLDCRUSADER 0x004084A0
        BOOLEnum EntityState::moveProjectileEntity(int entityID)
        {
            double speed = this->entityArray[entityID].speedUnk;
            double vCos = this->entityArray[entityID].vCos;
            double vSin = this->entityArray[entityID].vSin;
            int curHeight = this->entityArray[entityID].height - this->entityArray[entityID].startingHeight;
            int heightStep = 0;
            if (this->entityArray[entityID].someCounter_OR_hitGround != 0) {
                return FALSE;
            }
            if (this->entityArray[entityID].pathAxisCase == 0) {
                this->entityArray[entityID].someCounter_OR_hitGround = 40;
            }
            double horizontal = vCos * speed;
            double vertical = vSin * speed - speed * speed * 4.906;
            int flightDistance = (int)(horizontal * 0.25);
            int targetHeight = (int)(vertical + vertical);
            double angle;
            if (speed != 0.0f) {
                double prevSpeed = speed - this->entityArray[entityID]._elapsedTimeOrGravityAccumulator;
                double prevVertical = vSin * prevSpeed - prevSpeed * prevSpeed * 4.906;
                angle = atan((vertical - prevVertical) / (horizontal - vCos * prevSpeed) * 3.0) * 180.0 / 3.1415926535;
            } else {
                angle = this->entityArray[entityID].startingAngle;
            }
            short* rotationPtr = (short*)&this->entityArray[entityID].graphicRotationUnk;
            *rotationPtr = (int)angle;
            this->entityArray[entityID].speedUnk =
                this->entityArray[entityID]._elapsedTimeOrGravityAccumulator + this->entityArray[entityID].speedUnk;
            int remaining = flightDistance - this->entityArray[entityID].travelledDistance;
            if (remaining != 0) {
                heightStep = (targetHeight - curHeight) / remaining;
            }
            while (this->entityArray[entityID].travelledDistance < flightDistance) {
                this->entityArray[entityID].travelledDistance += 1;
                this->entityArray[entityID].clearanceStepsRemaining -= 1;
                if (entityID != 0) {
                    MACRO_CALL_MEMBER(EntityState_Func::doSomethingWithOtherEntitiesOnTile, this)(entityID);
                }
                MACRO_CALL_MEMBER(EntityState_Func::updateEntityMicroMovement, this)(entityID);
                int curve = DAT_EntityDefinedData::instance
                                .EntityArrayCurveTypeForProjectileType[this->entityArray[entityID].entityType];
                if (curve != 9 && curve != 10) {
                    curHeight += heightStep;
                    MACRO_CALL_MEMBER(EntityState_Func::updateProjectileHeightAndCollision, this)(entityID, curHeight, (int)angle, 1);
                }
                if (MACRO_CALL_MEMBER(EntityState_Func::processEntityHitBuildingOrUnit, this)(entityID) == 0) {
                    MACRO_CALL_MEMBER(EntityState_Func::calculateEntityDrawOffset, this)(entityID);
                    return TRUE;
                }
                MACRO_CALL_MEMBER(EntityState_Func::calculateEntityDrawOffset, this)(entityID);
                if (this->entityArray[entityID].someCounter_OR_hitGround != 0) {
                    break;
                }
            }
            this->entityArray[entityID].travelledDistance = flightDistance;
            int curve = DAT_EntityDefinedData::instance
                            .EntityArrayCurveTypeForProjectileType[this->entityArray[entityID].entityType];
            if (curve == 9) {
                if (this->entityArray[entityID].targetZ > this->entityArray[entityID].height) {
                    this->entityArray[entityID].height += 1;
                    return TRUE;
                }
                if (this->entityArray[entityID].height > this->entityArray[entityID].targetZ) {
                    this->entityArray[entityID].height -= 8;
                    if (this->entityArray[entityID].height <= 0) {
                        this->entityArray[entityID].someMicroY = 0;
                        this->entityArray[entityID].someMicroX = 0;
                        this->entityArray[entityID].height = 0;
                        MACRO_CALL_MEMBER(EntityState_Func::spawnProjectileEntity, this)(0, 0, 0, this->entityArray[entityID].microX,
                            this->entityArray[entityID].microY, 0, this->entityArray[entityID].microX,
                            this->entityArray[entityID].microY, 0, (EntityType)0x1f, 0);
                        MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(this->entityArray[entityID].xPosition,
                            this->entityArray[entityID].yPosition, (OpenSHC::DE::SHCDE::eSFX)0xd5);
                    }
                }
            } else if (curve == 10) {
                this->entityArray[entityID].height += 1;
            } else {
                MACRO_CALL_MEMBER(EntityState_Func::updateProjectileHeightAndCollision, this)(entityID, targetHeight, (int)angle, 0);
            }
            return TRUE;
        }

    }
}
}
