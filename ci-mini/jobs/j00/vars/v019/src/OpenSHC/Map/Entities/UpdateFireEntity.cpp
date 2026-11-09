#include "../Entities.func.hpp"

#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Entities/EntityState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Map/LogicHelpers/Logic1.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_CurrentEntityID.hpp"
#include "OpenSHC/Globals/DAT_EntityDefinedData.hpp"
#include "OpenSHC/Globals/DAT_EntityState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x00405680
    void Entities::UpdateFireEntity()
    {
        if (DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].fireParameter_0xb6 == 5) {
            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].unkMinusOne = 8;
        } else if (DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].fireParameter_0xb6 == 4) {
            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].unkMinusOne = 9;
        } else if (DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].fireParameter_0xb6 == 3) {
            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].unkMinusOne = 12;
        } else if (DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].fireParameter_0xb6 == 2) {
            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].unkMinusOne = 14;
        } else {
            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].unkMinusOne = 16;
        }
        DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].gmID = 118;
        int frameCount;
        if (DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].someTracker < 0) {
            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].unkMinusOne = 32;
            frameCount = 1;
            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].someTracker += 1;
        } else {
            frameCount = 0;
            if (DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].someTracker == 0) {
                if (DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].fireParameter_0xb6 >= 3) {
                    if (DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].rng_1 & 0x80) {
                        frameCount
                            = (char)DAT_EntityDefinedData::instance.FireAnimationFrames3[DAT_EntityState::instance
                                    .entityArray[DAT_CurrentEntityID::instance]
                                    .unknownAnimationFrameRelated];
                    } else {
                        DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].gmID = 144;
                        frameCount
                            = (char)DAT_EntityDefinedData::instance.FireAnimationFrames5[DAT_EntityState::instance
                                    .entityArray[DAT_CurrentEntityID::instance]
                                    .unknownAnimationFrameRelated];
                    }
                } else if (DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].fireParameter_0xb6
                    == 2) {
                    frameCount
                        = DAT_EntityDefinedData::instance
                              .FireAnimationFrames1[DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance]
                                      .unknownAnimationFrameRelated];
                } else {
                    frameCount
                        = DAT_EntityDefinedData::instance
                              .FireAnimationFrames2[DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance]
                                      .unknownAnimationFrameRelated];
                }
            } else if (DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].someTracker == 1) {
                if (DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].fireParameter_0xb6 >= 3) {
                    if (DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].rng_1 & 0x80) {
                        frameCount = DAT_EntityDefinedData::instance.FireAnimationFrames7[DAT_EntityState::instance
                                .entityArray[DAT_CurrentEntityID::instance]
                                .unknownAnimationFrameRelated];
                    } else {
                        DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].gmID = 144;
                        frameCount = DAT_EntityDefinedData::instance.FireAnimationFrames8[DAT_EntityState::instance
                                .entityArray[DAT_CurrentEntityID::instance]
                                .unknownAnimationFrameRelated];
                    }
                } else if (DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].fireParameter_0xb6
                    == 2) {
                    frameCount
                        = DAT_EntityDefinedData::instance
                              .FireAnimationFrames1[DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance]
                                      .unknownAnimationFrameRelated];
                } else {
                    frameCount
                        = DAT_EntityDefinedData::instance
                              .FireAnimationFrames2[DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance]
                                      .unknownAnimationFrameRelated];
                }
            } else if (DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].someTracker == 2) {
                if (DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].fireParameter_0xb6 >= 3) {
                    if (DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].rng_1 & 0x80) {
                        frameCount = DAT_EntityDefinedData::instance.FireAnimationFrames4[DAT_EntityState::instance
                                .entityArray[DAT_CurrentEntityID::instance]
                                .unknownAnimationFrameRelated];
                    } else {
                        DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].gmID = 144;
                        frameCount = DAT_EntityDefinedData::instance.FireAnimationFrames6[DAT_EntityState::instance
                                .entityArray[DAT_CurrentEntityID::instance]
                                .unknownAnimationFrameRelated];
                    }
                } else if (DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].fireParameter_0xb6
                    == 2) {
                    frameCount
                        = DAT_EntityDefinedData::instance
                              .FireAnimationFrames1[DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance]
                                      .unknownAnimationFrameRelated];
                } else {
                    frameCount
                        = DAT_EntityDefinedData::instance
                              .FireAnimationFrames2[DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance]
                                      .unknownAnimationFrameRelated];
                }
            }
            if (frameCount <= 0) {
                DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].unknownAnimationFrameRelated = 0;
                if (DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].someTracker == 0) {
                    DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].someTracker = 1;
                } else if (DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].someTracker == 1) {
                    DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].someCounter_OR_hitGround += 1;
                    if (DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].someCounter_OR_hitGround
                            == 6
                        && DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].fireParameter_0xb6
                            > 2) {
                        DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].fireParameter_0xb6 = 2;
                    }
                    DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].someCounter_OR_hitGround += 1;
                    if (DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].someCounter_OR_hitGround
                        > 8) {
                        DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].someTracker = 2;
                    }
                    if (DAT_TileMapState::instance.BuildingLayer
                                [DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].tile]
                            != 0
                        && MACRO_CALL_MEMBER(Buildings::BuildingsState_Func::getBuildingFlammabilityFactor,
                            DAT_BuildingsState::ptr)(DAT_TileMapState::instance.BuildingLayer
                                [DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].tile])) {
                        if (!(DAT_BuildingsState::instance
                                .buildings[DAT_TileMapState::instance.BuildingLayer
                                        [DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].tile]]
                                .fireDuration
                            != 0)) {
                            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].someTracker = 2;
                        } else {
                            if (DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].fireParameter_0xb6
                                < 3) {
                                DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].fireParameter_0xb6
                                    = 3;
                            }
                            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].someTracker = 1;
                            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance]
                                .someCounter_OR_hitGround = 0;
                        }
                    }
                } else if (DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].someTracker == 2) {
                    DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].logicalState = 3;
                }
                // measured: skipping the shared graphicType2 store with a goto gives 0.91, an if/else 0.75
                goto spread;
            }
        }
        DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].graphicType2 = frameCount;
    spread:
        if (DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].someTracker == 0
            && DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].unknownAnimationFrameRelated == 1) {
            short const spreadDirection
                = DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].field_0xb8;
            int const tileHeight
                = DAT_TileMapState::instance
                      .HeightLayer[DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].tile];
            if (spreadDirection < 4
                && DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].fireParameter_0xb6 > 1) {
                if (spreadDirection == 0) {
                    if (abs(tileHeight
                            - (int)MACRO_CALL_MEMBER(TileMapState_Func::getTotalHeightAtTile, DAT_TileMapState::ptr)(
                                DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].tile - 1))
                        < 25) {
                        MACRO_CALL(Entities_Func::IgniteFireAtMiniTile)(
                            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].owner,
                            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].microX - 8,
                            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].microY,
                            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].height,
                            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].fireParameter_0xb6 - 1,
                            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].fireIntensity);
                    }
                } else if (spreadDirection == 1) {
                    if (abs(tileHeight
                            - (int)MACRO_CALL_MEMBER(TileMapState_Func::getTotalHeightAtTile, DAT_TileMapState::ptr)(
                                DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].tile + 1))
                        < 25) {
                        MACRO_CALL(Entities_Func::IgniteFireAtMiniTile)(
                            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].owner,
                            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].microX + 8,
                            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].microY,
                            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].height,
                            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].fireParameter_0xb6 - 1,
                            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].fireIntensity);
                    }
                } else if (spreadDirection == 2) {
                    if (abs(tileHeight
                            - (int)MACRO_CALL_MEMBER(TileMapState_Func::getTotalHeightAtTile, DAT_TileMapState::ptr)(
                                DAT_ViewportRenderState::instance
                                    .translationMatrix
                                        [DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].yPosition
                                            + 1]
                                    .addXgetTile
                                + DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].xPosition))
                        < 25) {
                        MACRO_CALL(Entities_Func::IgniteFireAtMiniTile)(
                            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].owner,
                            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].microX,
                            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].microY + 8,
                            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].height,
                            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].fireParameter_0xb6 - 1,
                            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].fireIntensity);
                    }
                } else if (spreadDirection == 3) {
                    if (abs(tileHeight
                            - (int)MACRO_CALL_MEMBER(TileMapState_Func::getTotalHeightAtTile, DAT_TileMapState::ptr)(
                                DAT_ViewportRenderState::instance
                                    .translationMatrix
                                        [DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].yPosition
                                            - 1]
                                    .addXgetTile
                                + DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].xPosition))
                        < 25) {
                        MACRO_CALL(Entities_Func::IgniteFireAtMiniTile)(
                            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].owner,
                            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].microX,
                            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].microY - 8,
                            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].height,
                            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].fireParameter_0xb6 - 1,
                            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].fireIntensity);
                    }
                }
                DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].field_0xb8 += 1;
            }
        }
        if (!(DAT_TileMapState::instance
                    .LogicLayer[DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].tile]
                & (LogicHelpers::L_SEA | LogicHelpers::L_BORDER | LogicHelpers::L_BORDER_EDGE | LogicHelpers::L_ROCKY
                    | LogicHelpers::L_WALL_OR_GATEHOUSE | LogicHelpers::L_RIVER | LogicHelpers::L_FORD
                    | LogicHelpers::L_CRENEL_VARIATIONUnk | LogicHelpers::L_FARM_FIELD_HOP
                    | LogicHelpers::L_FARM_FIELD_DAIRY | LogicHelpers::L_KEEP_NON_MANOR_HOUSE | LogicHelpers::L_MARSH
                    | LogicHelpers::L_OIL))) {
            MACRO_CALL_MEMBER(EntityState_Func::processFireDamageToUnitsAtTile, DAT_EntityState::ptr)(
                DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].tile,
                DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].owner,
                DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].fireIntensity);
        }
    }

}
}
