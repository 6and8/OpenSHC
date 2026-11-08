#include "../EntityState.func.hpp"

#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Map/Navigation/DirectionAlgorithmState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"

#include "OpenSHC/Globals/DAT_DirectionAlgorithmState.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"

#include "math.h"

namespace OpenSHC {
namespace Map {
    namespace Entities {

        // FUNCTION: STRONGHOLDCRUSADER 0x00403FF0
        void EntityState::handleProjectileWallBounce(int entityID)
        {
            int const microX = this->entityArray[entityID].microX;
            int const microY = this->entityArray[entityID].microY;
            int const subY = microY & 7;
            int const subX = microX & 7;
            int targetX = 0;
            int targetY = 0;
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
                    targetY = this->entityArray[entityID].y_2;
                    targetX = this->entityArray[entityID].microX * 2 - this->entityArray[entityID].x_2;
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
                if (first > second) {
                    targetX = this->entityArray[entityID].microX * 2 - this->entityArray[entityID].x_2;
                    targetY = this->entityArray[entityID].y_2;
                } else {
                    targetY = this->entityArray[entityID].microY * 2 - this->entityArray[entityID].y_2;
                    targetX = this->entityArray[entityID].x_2;
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
            MACRO_CALL_MEMBER(Navigation::DirectionAlgorithmState_Func::somethingWithProjectileDistance,
                DAT_DirectionAlgorithmState::ptr)(microX, microY, targetX, targetY);
            this->entityArray[entityID].orientation = DAT_DirectionAlgorithmState::instance.orientation;
            if (microY > targetY) {
                this->entityArray[entityID].pathDeltaY = microY - targetY;
            } else {
                this->entityArray[entityID].pathDeltaY = targetY - microY;
            }
            if (microX > targetX) {
                this->entityArray[entityID].pathDeltaX = microX - targetX;
            } else {
                this->entityArray[entityID].pathDeltaX = targetX - microX;
            }
            this->entityArray[entityID].pathTargetX = targetX;
            this->entityArray[entityID].someMicroX = (microX <= targetX ? 1 : -1);
            this->entityArray[entityID].pathTargetY = targetY;
            this->entityArray[entityID].someMicroY = (microY <= targetY ? 1 : -1);
            short const deltaX = this->entityArray[entityID].pathDeltaX;
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
                short const errorStep = deltaX * 2;
                this->entityArray[entityID].pathErrorStepStraight = errorStep;
                this->entityArray[entityID].pathErrorStepDiagonal
                    = errorStep - this->entityArray[entityID].pathDeltaY * 2;
                this->entityArray[entityID].pathError = errorStep - this->entityArray[entityID].pathDeltaY;
            } else if (this->entityArray[entityID].pathAxisCase == 4) {
                short const errorStep = this->entityArray[entityID].pathDeltaY * 2;
                this->entityArray[entityID].pathErrorStepStraight = errorStep;
                this->entityArray[entityID].pathErrorStepDiagonal = errorStep - deltaX * 2;
                this->entityArray[entityID].pathError = errorStep - deltaX;
            }
            this->entityArray[entityID].startingAngle = this->entityArray[entityID].graphicRotationUnk;
            if (this->entityArray[entityID].startingAngle < -80) {
                this->entityArray[entityID].startingAngle = -80;
            }
            int const startingAngle = this->entityArray[entityID].startingAngle;
            this->entityArray[entityID].speedUnk = 0.0f;
            double const angle = startingAngle * 3.1415926535 / 180.0;
            this->entityArray[entityID].velocityUnk = this->entityArray[entityID].velocityUnk / 8;
            this->entityArray[entityID].startingHeight = this->entityArray[entityID].height;
            this->entityArray[entityID].travelledDistance = 0;
            this->entityArray[entityID].vCos = cos(angle) * this->entityArray[entityID].velocityUnk;
            this->entityArray[entityID].vSin = sin(angle) * this->entityArray[entityID].velocityUnk;
            this->entityArray[entityID].rotationFrameIndex
                = MACRO_CALL_MEMBER(EntityState_Func::angleToRotationFrameIndex, this)(startingAngle);
            this->entityArray[entityID].gmLookupValue = 0;
            MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                this->entityArray[entityID].xPosition, this->entityArray[entityID].yPosition,
                (OpenSHC::DE::SHCDE::eSFX)0x40);
        }

    } // namespace Entities
} // namespace Map
} // namespace OpenSHC
