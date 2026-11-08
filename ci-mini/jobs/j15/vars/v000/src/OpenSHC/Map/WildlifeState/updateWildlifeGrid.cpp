#include "OpenSHC/Map/WildlifeState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"
#include "OpenSHC/Map/Trees/TreeType.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"
#include "OpenSHC/Map/WildlifeState.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_LandscapeState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x0052ba10
    void WildlifeState::updateWildlifeGrid(int _y10)
    {
        int yBase = _y10 * 10;
        int playerAreas[8];
        for (int p = 0; p < 8; ++p) {
            playerAreas[p] = -1;
            if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[p + 1] != -1) {
                playerAreas[p] = (short)DAT_TileMapState::instance.PathConnectionLayer
                                     [DAT_GameState::instance.playerDataArray[p + 1].buildingEntryInfos[8].tileEntry];
            }
        }

        if (DAT_GameSynchronyState::instance.currentGameMode != 0) {
            return;
        }

        for (int xBase = 0; xBase < 400; xBase += 10) {
            int x10 = xBase / 10;
            int* firstMemberPtr = &this->grid[x10][_y10].firstMember;
            *firstMemberPtr = 0;
            this->grid[x10][_y10].separateAreaID = 0;
            this->grid[x10][_y10].unclaimedArea = 0;
            this->grid[x10][_y10].buildingTiles = 0;
            this->grid[x10][_y10].keeps = 0;
            this->grid[x10][_y10].wallTiles = 0;
            this->grid[x10][_y10].trees = 0;
            this->grid[x10][_y10].unitCount = 0;
            this->grid[x10][_y10].unstalkedUnitCount = 0;
            this->grid[x10][_y10].stalkedUnitCount = 0;
            this->grid[x10][_y10].camelCount = 0;
            this->grid[x10][_y10].lionCount = 0;
            this->grid[x10][_y10].deerCount = 0;
            this->grid[x10][_y10].rabbitCount = 0;
            this->grid[x10][_y10].marshTiles = 0;
            this->grid[x10][_y10].rockyTiles = 0;
            this->grid[x10][_y10].field_0x48 = 0;
            this->grid[x10][_y10].farmFieldTiles = 0;
            this->grid[x10][_y10].chimps = 0;
            this->grid[x10][_y10].castlebuildings = 0;
            this->grid[x10][_y10].field_0x70 = 0;

            int areaCounts[100][2];
            for (int i = 0; i < 100; ++i) {
                areaCounts[i][0] = -1;
                areaCounts[i][1] = 0;
            }

            for (int dy = 0; dy < 10; ++dy) {
                int y = yBase + dy;
                for (int dx = 0; dx < 10; ++dx) {
                    int x = xBase + dx;
                    if ((uint)x <= 399 && (uint)y <= 399
                        && DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[y * 400 + x] != 0) {
                        this->grid[x10][_y10].firstMember += 1;
                        int tile = DAT_ViewportRenderState::instance.translationMatrix[y].addXgetTile + dx + xBase;
                        int areaId = (short)DAT_TileMapState::instance.PathConnectionLayer[tile];
                        if (areaId == 0) {
                            this->grid[x10][_y10].unclaimedArea += 1;
                        }
                        for (int i = 0; i < 100; ++i) {
                            if (areaCounts[i][0] == areaId) {
                                areaCounts[i][1] += 1;
                                break;
                            }
                            if (areaCounts[i][0] == -1) {
                                areaCounts[i][0] = areaId;
                                areaCounts[i][1] = 1;
                                break;
                            }
                        }
                        if (areaId != 0) {
                            for (int p = 0; p < 8; ++p) {
                                if (areaId == playerAreas[p]) {
                                    this->grid[x10][_y10].chimps += 1;
                                }
                            }
                        }
                        this->grid[x10][_y10].field_0x70 += DAT_TileMapState::instance.HeightLayer[tile];
                        int logic = DAT_TileMapState::instance.LogicLayer[tile];
                        if ((logic & 0x100) != 0) {
                            this->grid[x10][_y10].wallTiles += 1;
                            this->grid[x10][_y10].castlebuildings += 1;
                        }
                        if ((logic & 0x20000000) != 0) {
                            this->grid[x10][_y10].marshTiles += 1;
                        }
                        if ((logic & 0x20000) != 0) {
                            this->grid[x10][_y10].rockyTiles += 1;
                        }
                        if ((logic & 0x80) != 0) {
                            this->grid[x10][_y10].rockyTiles += 1;
                        }
                        if ((logic & 0x40000) != 0) {
                            this->grid[x10][_y10].rockyTiles += 1;
                        }
                        if ((logic & 0x1000000) != 0) {
                            this->grid[x10][_y10].farmFieldTiles += 1;
                        }
                        if ((logic & 0x2000000) != 0) {
                            this->grid[x10][_y10].farmFieldTiles += 1;
                        }
                        int treeId = DAT_TileMapState::instance.OrganismLayer[tile];
                        if (treeId >= 1 && treeId < 2000) {
                            ushort tt = DAT_LandscapeState::instance.trees[treeId].treeType;
                            if (tt == Trees::TT_UNKNOWN_1 || tt == Trees::TT_UNKNOWN_2 || tt == Trees::TT_UNKNOWN_3
                                || tt == Trees::TT_UNKNOWN_4) {
                                this->grid[x10][_y10].trees += 1;
                            }
                        }
                        int bldId = DAT_TileMapState::instance.BuildingLayer[tile];
                        if (bldId != 0) {
                            ushort bt = DAT_BuildingsState::instance.buildings[bldId].buildingType;
                            if (bt == Buildings::BT_MANORHOUSE) {
                                this->grid[x10][_y10].keeps += 1;
                            } else if (bt == Buildings::BT_STONEKEEP) {
                                this->grid[x10][_y10].keeps += 1;
                            } else if (bt == Buildings::BT_STRONGHOLD) {
                                this->grid[x10][_y10].keeps += 1;
                            } else if (bt == Buildings::BT_KEEPFOUR) {
                                this->grid[x10][_y10].keeps += 1;
                            } else if (bt == Buildings::BT_KEEPFIVE) {
                                this->grid[x10][_y10].keeps += 1;
                            } else if (bt == Buildings::BT_CAMPGROUND) {
                                this->grid[x10][_y10].keeps += 1;
                            } else if (bt == Buildings::BT_GATEHOUSELARGE || bt == Buildings::BT_GATEHOUSESMALL
                                || bt == Buildings::BT_WOODGATE1 || bt == Buildings::BT_WOODGATE2
                                || bt == Buildings::BT_DRAWBRIDGE || bt == Buildings::BT_TOWER1
                                || bt == Buildings::BT_TOWER2 || bt == Buildings::BT_TOWER3
                                || bt == Buildings::BT_TOWER4 || bt == Buildings::BT_TOWER5) {
                                this->grid[x10][_y10].castlebuildings += 1;
                            }
                            if (DAT_BuildingsState::instance.buildings[bldId].buildingType != Buildings::BT_SIGNPOST) {
                                this->grid[x10][_y10].buildingTiles += 1;
                            }
                        }
                        int unitId = DAT_TileMapState::instance.UnitLayer[tile];
                        if (unitId != 0) {
                            this->grid[x10][_y10].unitCount += 1;
                            if (DAT_UnitsState::instance.units[unitId].isStalked != 0) {
                                this->grid[x10][_y10].stalkedUnitCount += 1;
                                ushort ut = DAT_UnitsState::instance.units[unitId].unitType;
                                if (ut == Units::UT_ANTELOPESHDEER) {
                                    this->grid[x10][_y10].deerCount += 1;
                                    if (DAT_TribesState::instance.tribes[DAT_UnitsState::instance.units[unitId].tribeID]
                                            .predatorNearby
                                        != 0) {
                                        this->grid[x10][_y10].field_0x48 += 1;
                                    }
                                } else if (ut == Units::UT_RABBIT) {
                                    this->grid[x10][_y10].rabbitCount += 1;
                                } else if (ut == Units::UT_CAMELSHBEAR) {
                                    this->grid[x10][_y10].camelCount += 1;
                                } else if (ut == Units::UT_LIONSHWOLF) {
                                    this->grid[x10][_y10].lionCount += 1;
                                }
                            } else {
                                this->grid[x10][_y10].unstalkedUnitCount += 1;
                                this->grid[x10][_y10].field_0x48 += 1;
                            }
                        }
                    }
                }
            }

            int bestAreaId = 0;
            int bestAreaCount = 0;
            for (int i = 0; i < 100; ++i) {
                if (areaCounts[i][0] == -1) {
                    break;
                }
                if (areaCounts[i][1] > bestAreaCount) {
                    bestAreaId = areaCounts[i][0];
                    bestAreaCount = areaCounts[i][1];
                }
            }
            this->grid[x10][_y10].separateAreaID = bestAreaId;
        }
    }

} // namespace Map
} // namespace OpenSHC
