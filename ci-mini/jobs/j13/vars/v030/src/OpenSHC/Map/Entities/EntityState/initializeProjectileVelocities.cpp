#include "../EntityState.func.hpp"

#include "OpenSHC/Globals/DAT_EntityDefinedData.hpp"

#include "math.h"

namespace OpenSHC {
namespace Map {
    namespace Entities {

        // FUNCTION: STRONGHOLDCRUSADER 0x00403A20
        void EntityState::initializeProjectileVelocities(
            int entityID, int x, int y, int height, int targetX, int targetY, int targetZ)
        {
            if (y > targetY) {
                this->entityArray[entityID].pathDeltaY = y - targetY;
            } else {
                this->entityArray[entityID].pathDeltaY = targetY - y;
            }
            if (targetX < x) {
                this->entityArray[entityID].pathDeltaX = x - targetX;
            } else {
                this->entityArray[entityID].pathDeltaX = targetX - x;
            }
            if (this->entityArray[entityID].height >= this->entityArray[entityID].targetZ) {
                this->entityArray[entityID].pathDeltaZ
                    = this->entityArray[entityID].height - this->entityArray[entityID].targetZ;
            } else {
                this->entityArray[entityID].pathDeltaZ
                    = this->entityArray[entityID].targetZ - this->entityArray[entityID].height;
            }
            short const deltaX = this->entityArray[entityID].pathDeltaX;
            this->entityArray[entityID].pathTargetX = targetX;
            this->entityArray[entityID].pathTargetY = targetY;
            this->entityArray[entityID].someMicroX = (x <= targetX ? 1 : -1);
            this->entityArray[entityID].someMicroY = (y <= targetY ? 1 : -1);
            if (deltaX == 0 && this->entityArray[entityID].pathDeltaY == deltaX) {
                this->entityArray[entityID].pathAxisCase = 0;
            } else if (deltaX == 0) {
                this->entityArray[entityID].pathAxisCase = 1;
            } else if (this->entityArray[entityID].pathDeltaY == 0) {
                this->entityArray[entityID].pathAxisCase = 2;
            } else if (this->entityArray[entityID].pathDeltaY > deltaX) {
                this->entityArray[entityID].pathAxisCase = 3;
            } else {
                this->entityArray[entityID].pathAxisCase = 4;
            }
            if (this->entityArray[entityID].pathAxisCase == 3) {
                int const errorStep = deltaX * 2;
                this->entityArray[entityID].pathErrorStepStraight = errorStep;
                this->entityArray[entityID].pathErrorStepDiagonal = errorStep - this->entityArray[entityID].pathDeltaY * 2;
                this->entityArray[entityID].pathError = errorStep - this->entityArray[entityID].pathDeltaY;
            } else if (this->entityArray[entityID].pathAxisCase == 4) {
                short const errorStep = this->entityArray[entityID].pathDeltaY * 2;
                this->entityArray[entityID].pathErrorStepStraight = errorStep;
                this->entityArray[entityID].pathErrorStepDiagonal = errorStep - deltaX * 2;
                this->entityArray[entityID].pathError = errorStep - deltaX;
            }
            int const curveType
                = DAT_EntityDefinedData::instance.EntityArrayCurveTypeForProjectileType[this->entityArray[entityID].entityType];
            int distance;
            if (curveType == 0) {
                distance = MACRO_CALL_MEMBER(EntityState_Func::computeLineOfSightDistance, this)(
                    x, y, height, targetX, targetY, targetZ, 1);
                this->entityArray[entityID].field_0x94 = distance;
                this->entityArray[entityID].totalFlightDistance = distance;
                this->entityArray[entityID].clearanceStepsRemaining = this->lineOfSightClearanceSteps;
                this->entityArray[entityID].startingAngle = MACRO_CALL_MEMBER(EntityState_Func::math_atan_1, this)(
                    this->entityArray[entityID].entityType, this->entityArray[entityID].velocityUnk, (short)distance, this->entityArray[entityID].heightDifference);
            } else if (curveType == 1) {
                distance = MACRO_CALL_MEMBER(EntityState_Func::computeLineOfSightDistance, this)(
                    x, y, height, targetX, targetY, targetZ, 1);
                this->entityArray[entityID].field_0x94 = distance;
                this->entityArray[entityID].totalFlightDistance = distance;
                this->entityArray[entityID].clearanceStepsRemaining = this->lineOfSightClearanceSteps;
                this->entityArray[entityID].velocityUnk = MACRO_CALL_MEMBER(EntityState_Func::computeVelocity, this)(
                    this->entityArray[entityID].entityType, this->entityArray[entityID].startingAngle, (short)distance, this->entityArray[entityID].heightDifference);
            } else if (curveType == 2) {
                distance = MACRO_CALL_MEMBER(EntityState_Func::computeLineOfSightDistance, this)(
                    x, y, height, targetX, targetY, targetZ, 1);
                this->entityArray[entityID].field_0x94 = distance;
                this->entityArray[entityID].totalFlightDistance = distance;
                this->entityArray[entityID].clearanceStepsRemaining = this->lineOfSightClearanceSteps;
                if (this->entityArray[entityID].height > this->entityArray[entityID].targetZ) {
                    this->entityArray[entityID].startingAngle = 3;
                }
                this->entityArray[entityID].velocityUnk = MACRO_CALL_MEMBER(EntityState_Func::computeVelocity, this)(
                    this->entityArray[entityID].entityType, this->entityArray[entityID].startingAngle, (short)distance, this->entityArray[entityID].heightDifference);
                if (this->entityArray[entityID].velocityUnk <= 0) {
                    this->entityArray[entityID].startingAngle = 15;
                    this->entityArray[entityID].velocityUnk = MACRO_CALL_MEMBER(EntityState_Func::computeVelocity, this)(
                        this->entityArray[entityID].entityType, 15.0, (short)distance, this->entityArray[entityID].heightDifference);
                }
            } else if (curveType == 3) {
                this->entityArray[entityID].startingAngle = (this->entityArray[entityID].rng_1 & 0xf) + 8;
                this->entityArray[entityID].velocityUnk = (this->entityArray[entityID].rng_1 & 7) + 21;
            } else if (curveType == 4) {
                this->entityArray[entityID].startingAngle = this->entityArray[entityID].rng_1 % 20 + 16;
                if ((char)this->entityArray[entityID].rng_1 < 0) {
                    this->entityArray[entityID].startingAngle = -this->entityArray[entityID].startingAngle;
                }
                this->entityArray[entityID].velocityUnk = (this->entityArray[entityID].rng_1 >> 8) % 20 + 16;
                if (this->entityArray[entityID].rng_1 & 0x8000) {
                    this->entityArray[entityID].velocityUnk = -this->entityArray[entityID].velocityUnk;
                }
                return;
            } else if (curveType == 5) {
                this->entityArray[entityID].velocityUnk = 0;
                this->entityArray[entityID].startingAngle = (char)this->entityArray[entityID].rng_1 & 7;
                this->entityArray[entityID].graphicRotationUnk = (this->entityArray[entityID].rng_1 >> 8) & 0x3f;
                return;
            } else if (curveType == 6) {
                distance = MACRO_CALL_MEMBER(EntityState_Func::computeLineOfSightDistance, this)(
                    x, y, height, targetX, targetY, targetZ, 1);
                this->entityArray[entityID].field_0x94 = distance;
                this->entityArray[entityID].totalFlightDistance = distance;
                this->entityArray[entityID].clearanceStepsRemaining = this->lineOfSightClearanceSteps;
                if ((short)distance > 150) {
                    this->entityArray[entityID].velocityUnk = 125;
                }
                this->entityArray[entityID].startingAngle = MACRO_CALL_MEMBER(EntityState_Func::math_atan_1, this)(
                    this->entityArray[entityID].entityType, this->entityArray[entityID].velocityUnk, (short)distance, this->entityArray[entityID].heightDifference);
            } else if (curveType == 7 || curveType == 10) {
                return;
            } else if (curveType == 8) {
                if (this->entityArray[entityID].unitID_OR_seaGullID == 0) {
                    this->entityArray[entityID].startingAngle = this->entityArray[entityID].rng_1 % 60 + 8;
                    this->entityArray[entityID].velocityUnk = ((char)this->entityArray[entityID].rng_1 & 7) + 35;
                } else if (this->entityArray[entityID].unitID_OR_seaGullID == 4) {
                    this->entityArray[entityID].startingAngle = this->entityArray[entityID].rng_1 % 30 + 15;
                    this->entityArray[entityID].velocityUnk = ((char)this->entityArray[entityID].rng_1 & 7) + 15;
                    this->entityArray[entityID]._elapsedTimeOrGravityAccumulator *= 0.75;
                } else if (this->entityArray[entityID].unitID_OR_seaGullID == 5) {
                    this->entityArray[entityID].startingAngle = this->entityArray[entityID].rng_1 % 30 + 45;
                    this->entityArray[entityID].velocityUnk = ((char)this->entityArray[entityID].rng_1 & 7) + 35;
                } else {
                    this->entityArray[entityID].startingAngle = this->entityArray[entityID].rng_1 % 35 + 20;
                    this->entityArray[entityID].velocityUnk = ((char)this->entityArray[entityID].rng_1 & 7) + 25;
                    this->entityArray[entityID]._elapsedTimeOrGravityAccumulator *= 0.75;
                }
            } else if (curveType == 9) {
                this->entityArray[entityID].startingAngle = 0;
            }
            if (this->entityArray[entityID].entityType == 1 || this->entityArray[entityID].entityType == 7) {
                if (height + 54 < targetZ && this->entityArray[entityID].rng_1 % 10 == 5) {
                    this->entityArray[entityID].hasDoneEffectUnk = 1;
                }
            }
            int const startingAngle = this->entityArray[entityID].startingAngle;
            this->entityArray[entityID].speedUnk = 0.0f;
            this->entityArray[entityID].travelledDistance = 0;
            double const angle = startingAngle * 3.1415926535 / 180.0;
            double const velocity = this->entityArray[entityID].velocityUnk;
            this->entityArray[entityID].vCos = cos(angle) * velocity;
            this->entityArray[entityID].vSin = sin(angle) * velocity;
            this->entityArray[entityID].rotationFrameIndex
                = MACRO_CALL_MEMBER(EntityState_Func::angleToRotationFrameIndex, this)(startingAngle);
        }

    }
}
}
