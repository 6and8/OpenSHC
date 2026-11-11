#include "../EntityState.func.hpp"

#include "OpenSHC/Map/TileMapState.func.hpp"

#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

#include "stdlib.h"

namespace OpenSHC {
namespace Map {
    namespace Entities {

        // FUNCTION: STRONGHOLDCRUSADER 0x00402E20
        uint EntityState::computeLineOfSightDistance(
            int x, int y, int height, int targetX, int targetY, int targetHeight, int param_7)
        {
            int stillClear = 1;
            int lastTile = -1;
            int buildingID = -1;
            int i = 100000;
            int lastHeight = 0;
            int steps = 0;
            int heightChecked = 0;
            if (height > targetHeight + 54) {
                steps = 100;
            }
            int curX = x;
            int curY = y;
            int const startTileY = y / 8;
            int const startTileX = x / 8;
            int const startTile
                = DAT_ViewportRenderState::instance.translationMatrix[startTileY].addXgetTile + startTileX;
            if (DAT_TileMapState::instance.LogicLayer[startTile] & 0x10000000) {
                height += 10;
            }
            if (DAT_TileMapState::instance.BuildingLayer[startTile] != 0) {
                buildingID = DAT_TileMapState::instance.BuildingLayer[startTile];
            }
            int const distY = y > targetY ? y - targetY : targetY - y;
            int const distX = x > targetX ? x - targetX : targetX - x;
            int const stepX = (x <= targetX) * 2 - 1;
            int const stepY = (y <= targetY) * 2 - 1;
            if (distX == 0) {
                if (distY == 0) {
                    return i;
                }
                if (steps >= 28) {
                    steps = 28;
                }
                this->lineOfSightClearanceSteps = steps;
                int skipSteps = steps / 2;
                for (i = 0; i < 1000; ++i) {
                    curY += stepY;
                    if ((i & 1) != 0 && param_7 == 0) {
                        int const tile
                            = DAT_ViewportRenderState::instance.translationMatrix[curY / 8].addXgetTile + startTileX;
                        if ((DAT_TileMapState::instance.LogicLayer[tile] & 0x400300) == 0) {
                            stillClear = 0;
                            this->lineOfSightClearanceSteps = i;
                        }
                        if (skipSteps != 0) {
                            skipSteps -= 1;
                        } else if (lastTile != tile) {
                            heightChecked = 0;
                            if ((char)DAT_TileMapState::instance.LogicLayer[tile] < 0
                                || (DAT_TileMapState::instance.BuildingLayer[tile] != buildingID
                                    && (stillClear == 0
                                        || (DAT_TileMapState::instance.LogicLayer[tile] & 0x400200) == 0))) {
                                heightChecked = 1;
                                lastHeight = MACRO_CALL_MEMBER(
                                    TileMapState_Func::returnSomeHeight, DAT_TileMapState::ptr)(tile, 1);
                                if (abs(curY - y) * (targetHeight - height) / distY + height < lastHeight) {
                                    return 0;
                                }
                            }
                        } else if (heightChecked != 0) {
                            if (abs(curY - y) * (targetHeight - height) / distY + height < lastHeight) {
                                return 0;
                            }
                        }
                        lastTile = tile;
                    }
                    if (x == targetX && curY == targetY) {
                        return i;
                    }
                }
                return i;
            }
            if (distY != 0) {
                if (distY > distX) {
                    int const errStraight = distX * 2;
                    int err = errStraight - distY;
                    int const errDiagonal = errStraight - distY * 2;
                    if (height > targetHeight && steps != 0) {
                        int scanCount = abs(targetY - y) / 8 - 1;
                        if (scanCount > 4) {
                            scanCount = 4;
                        }
                        for (int k = 1; k < scanCount; ++k) {
                            lastHeight = MACRO_CALL_MEMBER(TileMapState_Func::returnSomeHeight, DAT_TileMapState::ptr)(
                                DAT_ViewportRenderState::instance.translationMatrix[targetY / 8 - k * stepY].addXgetTile
                                    + targetX / 8,
                                1);
                            if (lastHeight > targetHeight) {
                                steps = 28;
                            }
                        }
                    }
                    this->lineOfSightClearanceSteps = steps;
                    int skipSteps = steps / 2;
                    for (i = 0; i < 1000; ++i) {
                        curY += stepY;
                        if (err > 0) {
                            curX += stepX;
                            err += errDiagonal;
                        } else {
                            err += errStraight;
                        }
                        if ((i & 1) != 0 && param_7 == 0) {
                            int const tile
                                = DAT_ViewportRenderState::instance.translationMatrix[curY / 8].addXgetTile + curX / 8;
                            if ((DAT_TileMapState::instance.LogicLayer[tile] & 0x400300) == 0) {
                                stillClear = 0;
                                this->lineOfSightClearanceSteps = i;
                            }
                            if (skipSteps != 0) {
                                skipSteps -= 1;
                            } else if (lastTile != tile) {
                                heightChecked = 0;
                                if ((char)DAT_TileMapState::instance.LogicLayer[tile] < 0
                                    || (DAT_TileMapState::instance.BuildingLayer[tile] != buildingID
                                        && (stillClear == 0
                                            || (DAT_TileMapState::instance.LogicLayer[tile] & 0x400200) == 0))) {
                                    heightChecked = 1;
                                    lastHeight = MACRO_CALL_MEMBER(
                                        TileMapState_Func::returnSomeHeight, DAT_TileMapState::ptr)(tile, 1);
                                    if (abs(curY - y) * (targetHeight - height) / distY + height < lastHeight) {
                                        return 0;
                                    }
                                }
                            } else if (heightChecked != 0) {
                                if (abs(curY - y) * (targetHeight - height) / distY + height < lastHeight) {
                                    return 0;
                                }
                            }
                            lastTile = tile;
                        }
                        if (curX == targetX && curY == targetY) {
                            return i;
                        }
                    }
                    return i;
                }
                int const errStraight = distY * 2;
                int const errDiagonal = errStraight - distX * 2;
                int err = errStraight - distX;
                if (height > targetHeight && steps != 0) {
                    int scanCount = abs(targetX - x) / 8 - 1;
                    if (scanCount > 4) {
                        scanCount = 4;
                    }
                    for (int k = 1; k < scanCount; ++k) {
                        lastHeight = MACRO_CALL_MEMBER(TileMapState_Func::returnSomeHeight, DAT_TileMapState::ptr)(
                            DAT_ViewportRenderState::instance.translationMatrix[targetY / 8].addXgetTile + targetX / 8
                                - k * stepX,
                            1);
                        if (lastHeight > targetHeight) {
                            steps = 28;
                        }
                    }
                }
                int skipSteps = steps / 2;
                this->lineOfSightClearanceSteps = steps;
                for (i = 0; i < 1000; ++i) {
                    curX += stepX;
                    if (!(err > 0)) {
                        err += errStraight;
                    } else {
                        curY += stepY;
                        err += errDiagonal;
                    }
                    if ((i & 1) != 0 && param_7 == 0) {
                        int const tile
                            = DAT_ViewportRenderState::instance.translationMatrix[curY / 8].addXgetTile + curX / 8;
                        if ((DAT_TileMapState::instance.LogicLayer[tile] & 0x400300) == 0) {
                            stillClear = 0;
                            this->lineOfSightClearanceSteps = i;
                        }
                        if (skipSteps != 0) {
                            skipSteps -= 1;
                        } else if (lastTile != tile) {
                            heightChecked = 0;
                            if ((char)DAT_TileMapState::instance.LogicLayer[tile] < 0
                                || (DAT_TileMapState::instance.BuildingLayer[tile] != buildingID
                                    && (stillClear == 0
                                        || (DAT_TileMapState::instance.LogicLayer[tile] & 0x400200) == 0))) {
                                heightChecked = 1;
                                lastHeight = MACRO_CALL_MEMBER(
                                    TileMapState_Func::returnSomeHeight, DAT_TileMapState::ptr)(tile, 1);
                                if (abs(curX - x) * (targetHeight - height) / distX + height < lastHeight) {
                                    return 0;
                                }
                            }
                        } else if (heightChecked != 0) {
                            if (abs(curX - x) * (targetHeight - height) / distX + height < lastHeight) {
                                return 0;
                            }
                        }
                        lastTile = tile;
                    }
                    if (curX == targetX && curY == targetY) {
                        return i;
                    }
                }
                return i;
            }
            if (steps >= 28) {
                steps = 28;
            }
            this->lineOfSightClearanceSteps = steps;
            int skipSteps = steps / 2;
            for (i = 0; i < 1000; ++i) {
                curX += stepX;
                if ((i & 1) != 0 && param_7 == 0) {
                    int const tile
                        = DAT_ViewportRenderState::instance.translationMatrix[startTileY].addXgetTile + curX / 8;
                    if ((DAT_TileMapState::instance.LogicLayer[tile] & 0x400300) == 0) {
                        stillClear = 0;
                        this->lineOfSightClearanceSteps = i;
                    }
                    if (skipSteps != 0) {
                        skipSteps -= 1;
                    } else if (lastTile != tile) {
                        heightChecked = 0;
                        if ((char)DAT_TileMapState::instance.LogicLayer[tile] < 0
                            || (DAT_TileMapState::instance.BuildingLayer[tile] != buildingID
                                && (stillClear == 0
                                    || (DAT_TileMapState::instance.LogicLayer[tile] & 0x400200) == 0))) {
                            heightChecked = 1;
                            lastHeight = MACRO_CALL_MEMBER(TileMapState_Func::returnSomeHeight, DAT_TileMapState::ptr)(
                                tile, 1);
                            if (abs(curX - x) * (targetHeight - height) / distX + height < lastHeight) {
                                return 0;
                            }
                        }
                    } else if (heightChecked != 0) {
                        if (abs(curX - x) * (targetHeight - height) / distX + height < lastHeight) {
                            return 0;
                        }
                    }
                    lastTile = tile;
                }
                if (curX == targetX && y == targetY) {
                    return i;
                }
            }
            return i;
        }

    } // namespace Entities
} // namespace Map
} // namespace OpenSHC
