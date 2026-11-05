#include "../EntityState.func.hpp"

#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Random/RNG.func.hpp"
#include "OpenSHC/Rendering/ViewportRenderState.func.hpp"

#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"
#include "OpenSHC/Globals/SEC_RNG.hpp"

#include "math.h"
#include "stdlib.h"

namespace OpenSHC {
namespace Map {
    namespace Entities {

        // FUNCTION: STRONGHOLDCRUSADER 0x00406900
        void EntityState::processSeaGulls(int seagullID)
        {
            int const entityID = this->seagullArray[seagullID].entityID;
            if (this->seagullArray[seagullID].someCountDown != 0) {
                this->seagullArray[seagullID].someCountDown -= 1;
                if (this->seagullArray[seagullID].someCountDown != 0) {
                    return;
                }
                this->entityArray[entityID].targetX = this->entityArray[entityID].microX;
                this->entityArray[entityID].targetY = this->entityArray[entityID].microY;
                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                    this->entityArray[entityID].xPosition, this->entityArray[entityID].yPosition,
                    (OpenSHC::DE::SHCDE::eSFX)0xd6);
            }
            int const microX = this->entityArray[entityID].microX;
            if (abs(microX - this->entityArray[entityID].targetX) < 3
                && abs(this->entityArray[entityID].microY - this->entityArray[entityID].targetY) < 3) {
                if ((this->seagullArray[seagullID].randomNumber ^ this->entityArray[entityID].rng_1
                        ^ SEC_RNG::instance.currentNumber2)
                        % 500
                    == 123) {
                    int const targetX = microX + this->entityArray[entityID].someMicroX;
                    int const targetY = this->entityArray[entityID].microY + this->entityArray[entityID].someMicroY;
                    int const tileY = targetY / 8;
                    int const tileX = targetX / 8;
                    if (MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::xyAreValid,
                            DAT_ViewportRenderState::ptr)(tileX, tileY)) {
                        int const centerTileY = this->entityArray[entityID].microY / 8;
                        int const centerTileX = this->entityArray[entityID].microX / 8;
                        if (MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::xyAreValid,
                                DAT_ViewportRenderState::ptr)(centerTileX, centerTileY)
                            && (DAT_TileMapState::instance
                                       .LogicLayer[DAT_ViewportRenderState::instance.translationMatrix[tileY].addXgetTile
                                           + tileX]
                                   & 1)
                            && (DAT_TileMapState::instance
                                       .LogicLayer[DAT_ViewportRenderState::instance.translationMatrix[centerTileY]
                                                       .addXgetTile
                                           + centerTileX]
                                   & 1)) {
                            this->seagullArray[seagullID].someCountDown = 160;
                            MACRO_CALL_MEMBER(EntityState_Func::setProjectileTargetPosition, this)(entityID,
                                this->entityArray[entityID].microX, this->entityArray[entityID].microY, 250, targetX,
                                targetY, 0);
                            MACRO_CALL_MEMBER(
                                OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                                this->entityArray[entityID].xPosition, this->entityArray[entityID].yPosition,
                                (OpenSHC::DE::SHCDE::eSFX)0xc9);
                            return;
                        }
                    }
                }
                double angleRadians = (this->seagullArray[seagullID].angle - 180) * 3.1415926535 / 180.0;
                this->seagullArray[seagullID].angle += this->seagullArray[seagullID].someAngle * 20;
                if (this->seagullArray[seagullID].angle >= 360) {
                    MACRO_CALL_MEMBER(OpenSHC::Random::RNG_Func::nextRandomNumber1, SEC_RNG::ptr)();
                    if (SEC_RNG::instance.currentNumber1 % 5 == 1) {
                        MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                            this->entityArray[entityID].xPosition, this->entityArray[entityID].yPosition,
                            (OpenSHC::DE::SHCDE::eSFX)0xc9);
                    }
                    this->seagullArray[seagullID].angle -= 360;
                    if (this->seagullArray[seagullID].field_0x1a < 0) {
                        this->seagullArray[seagullID].unknownCounter_0x16 += 1;
                    } else if (this->seagullArray[seagullID].field_0x1a > 0) {
                        this->seagullArray[seagullID].unknownCounter_0x16 -= 1;
                    }
                    if (this->seagullArray[seagullID].unknownCounter_0x16 < 24) {
                        this->seagullArray[seagullID].unknownCounter_0x16 = 24;
                    }
                    if (this->seagullArray[seagullID].unknownCounter_0x16 > 80) {
                        this->seagullArray[seagullID].unknownCounter_0x16 = 80;
                    }
                    this->seagullArray[seagullID].field_0x1a += 1;
                    if (this->seagullArray[seagullID].field_0x1a >= 20) {
                        this->seagullArray[seagullID].field_0x1a = -20;
                    }
                }
                if (this->seagullArray[seagullID].angle < 0) {
                    this->seagullArray[seagullID].angle += 360;
                    if (this->seagullArray[seagullID].field_0x1a < 0) {
                        this->seagullArray[seagullID].unknownCounter_0x16 += 1;
                    } else if (this->seagullArray[seagullID].field_0x1a > 0) {
                        this->seagullArray[seagullID].unknownCounter_0x16 -= 1;
                    }
                    if (this->seagullArray[seagullID].unknownCounter_0x16 < 24) {
                        this->seagullArray[seagullID].unknownCounter_0x16 = 24;
                    }
                    if (this->seagullArray[seagullID].unknownCounter_0x16 > 80) {
                        this->seagullArray[seagullID].unknownCounter_0x16 = 80;
                    }
                    this->seagullArray[seagullID].field_0x1a += 1;
                    if (this->seagullArray[seagullID].field_0x1a >= 20) {
                        this->seagullArray[seagullID].field_0x1a = -20;
                    }
                }
                int const offsetX = (int)(sin(angleRadians) * this->seagullArray[seagullID].unknownCounter_0x16);
                int const offsetY = (int)(cos(angleRadians) * this->seagullArray[seagullID].unknownCounter_0x16);
                double angleRadians2 = (this->seagullArray[seagullID].angle_2 - 180) * 3.1415926535 / 180.0;
                this->seagullArray[seagullID].angle_2 += this->seagullArray[seagullID].angleStep;
                if (this->seagullArray[seagullID].angle_2 >= 360) {
                    this->seagullArray[seagullID].angle_2 -= 360;
                }
                if (this->seagullArray[seagullID].angle_2 < 0) {
                    this->seagullArray[seagullID].angle_2 += 360;
                }
                this->seagullArray[seagullID].x_2 = (int)(sin(angleRadians2)
                                                        * this->seagullArray[seagullID].numberBetween60And100)
                    + this->seagullArray[seagullID].x;
                this->seagullArray[seagullID].y_2 = (int)(cos(angleRadians2)
                                                        * this->seagullArray[seagullID].numberBetween60And100)
                    + this->seagullArray[seagullID].y;
                MACRO_CALL_MEMBER(EntityState_Func::setProjectileTargetPosition, this)(entityID,
                    this->entityArray[entityID].microX, this->entityArray[entityID].microY,
                    this->entityArray[entityID].height, this->seagullArray[seagullID].x_2 + offsetX,
                    this->seagullArray[seagullID].y_2 + offsetY, 250);
            }
            if ((abs(this->seagullArray[seagullID].x - this->seagullArray[seagullID].x_3) < 2
                    && abs(this->seagullArray[seagullID].y - this->seagullArray[seagullID].y_3) < 2)
                || this->seagullArray[seagullID].pathMajorLength <= 0) {
                if (this->seagullArray[seagullID].rngMax799_countdown > 0) {
                    this->seagullArray[seagullID].rngMax799_countdown -= 1;
                    return;
                }
                this->seagullArray[seagullID].rngMax799_countdown = SEC_RNG::instance.currentNumber2 % 400 + 400;
                MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::findFurthestSeaTile,
                    DAT_PathFindingState::ptr)((SEC_RNG::instance.currentNumber2 >> 4) % 200 + 400,
                    this->seagullArray[seagullID].x / 8, this->seagullArray[seagullID].y / 8);
                this->seagullArray[seagullID].x_3 = DAT_PathFindingState::instance.ALG_ResultX * 8;
                this->seagullArray[seagullID].y_3 = DAT_PathFindingState::instance.ALG_ResultY * 8;
                MACRO_CALL_MEMBER(EntityState_Func::initializeSeagullMovementVector, this)(seagullID,
                    this->seagullArray[seagullID].x, this->seagullArray[seagullID].y,
                    this->seagullArray[seagullID].x_3, this->seagullArray[seagullID].y_3);
                this->seagullArray[seagullID].pathStepDelay = 10;
                return;
            }
            this->seagullArray[seagullID].pathStepDelay -= 1;
            if (this->seagullArray[seagullID].pathStepDelay > 0) {
                return;
            }
            this->seagullArray[seagullID].pathStepDelay = 10;
            this->seagullArray[seagullID].pathMajorLength -= 1;
            if (this->seagullArray[seagullID].pathAxisCase == 0) {
                return;
            }
            if (this->seagullArray[seagullID].pathAxisCase == 2) {
                this->seagullArray[seagullID].x = this->seagullArray[seagullID].pathStepX + this->seagullArray[seagullID].x;
            } else if (this->seagullArray[seagullID].pathAxisCase == 1) {
                this->seagullArray[seagullID].y += this->seagullArray[seagullID].pathStepY;
            } else if (this->seagullArray[seagullID].pathAxisCase == 4) {
                if (this->seagullArray[seagullID].pathError > 0) {
                    this->seagullArray[seagullID].x = this->seagullArray[seagullID].pathStepX + this->seagullArray[seagullID].x;
                    this->seagullArray[seagullID].y += this->seagullArray[seagullID].pathStepY;
                    this->seagullArray[seagullID].pathError =
                        this->seagullArray[seagullID].pathErrorStepDiagonal + this->seagullArray[seagullID].pathError;
                } else {
                    this->seagullArray[seagullID].x = this->entityArray[entityID].someMicroX + this->seagullArray[seagullID].x;
                    this->seagullArray[seagullID].pathError =
                        this->seagullArray[seagullID].pathErrorStepStraight + this->seagullArray[seagullID].pathError;
                }
            } else if (this->seagullArray[seagullID].pathAxisCase == 3) {
                this->seagullArray[seagullID].y += this->seagullArray[seagullID].pathStepY;
                if (!(this->seagullArray[seagullID].pathError > 0)) {
                    this->seagullArray[seagullID].pathError =
                        this->seagullArray[seagullID].pathErrorStepStraight + this->seagullArray[seagullID].pathError;
                } else {
                    this->seagullArray[seagullID].x = this->seagullArray[seagullID].pathStepX + this->seagullArray[seagullID].x;
                    this->seagullArray[seagullID].pathError =
                        this->seagullArray[seagullID].pathErrorStepDiagonal + this->seagullArray[seagullID].pathError;
                }
            }
        }

    }
}
}
