#include "OpenSHC/Map/Entities/EntityState.func.hpp"

namespace OpenSHC {
namespace Map {
    namespace Entities {

        // FUNCTION: STRONGHOLDCRUSADER 0x004081E0
        void EntityState::updateProjectileHeightAndCollision(
            uint entityID, undefined4 heightDelta, int angle, int skipCollision)
        {
            short* heightPtr = &this->entityArray[entityID].height;
            *heightPtr = this->entityArray[entityID].startingHeight + (short)heightDelta;
            if (this->entityArray[entityID].height <= 2 && skipCollision == 0) {
                MACRO_CALL_MEMBER(EntityState_Func::doSomethingWithOtherEntitiesOnTile, this)(entityID);
                MACRO_CALL_MEMBER(EntityState_Func::processEntityHitBuildingOrUnit, this)(entityID);
            }
            if (this->entityArray[entityID].height > 10000) {
                MACRO_CALL_MEMBER(EntityState_Func::markEntityDestroyed, this)(entityID);
                return;
            }
            this->entityArray[entityID].rotationFrameIndex
                = (short)MACRO_CALL_MEMBER(EntityState_Func::angleToRotationFrameIndex, this)(angle);
            this->entityArray[entityID].height_2 = this->entityArray[entityID].height;
        }

    }
}
}
