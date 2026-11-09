#include "OpenSHC/Map/Entities/EntityState.func.hpp"

namespace OpenSHC {
namespace Map {
    namespace Entities {

        // FUNCTION: STRONGHOLDCRUSADER 0x00402AE0
        void EntityState::updateEntityMicroMovement(int entityID)
        {
            if (this->entityArray[entityID].entityType == 0x1d && this->entityArray[entityID].targetZ == 0
                && this->entityArray[entityID].microX == this->entityArray[entityID].targetX
                && this->entityArray[entityID].microY == this->entityArray[entityID].targetY) {
                return;
            }
            switch (this->entityArray[entityID].pathAxisCase) {
            case 0:
                break;
            case 2:
                this->entityArray[entityID].microX += this->entityArray[entityID].someMicroX;
                break;
            case 1:
                this->entityArray[entityID].microY += this->entityArray[entityID].someMicroY;
                break;
            case 4: {
                short const error = this->entityArray[entityID].pathError;
                this->entityArray[entityID].microX += this->entityArray[entityID].someMicroX;
                if (error > 0) {
                    this->entityArray[entityID].microY += this->entityArray[entityID].someMicroY;
                    this->entityArray[entityID].pathError = error + this->entityArray[entityID].pathErrorStepDiagonal;
                } else {
                    this->entityArray[entityID].pathError = error + this->entityArray[entityID].pathErrorStepStraight;
                }
                break;
            }
            case 3:
                if (this->entityArray[entityID].pathError > 0) {
                    short* microXPtr = &this->entityArray[entityID].microX;
                    *microXPtr += this->entityArray[entityID].someMicroX;
                    this->entityArray[entityID].microY += this->entityArray[entityID].someMicroY;
                    this->entityArray[entityID].pathError += this->entityArray[entityID].pathErrorStepDiagonal;
                } else {
                    this->entityArray[entityID].microY += this->entityArray[entityID].someMicroY;
                    this->entityArray[entityID].pathError += this->entityArray[entityID].pathErrorStepStraight;
                }
                break;
            }
        }

    }
}
}
