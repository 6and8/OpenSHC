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
        int player1Area = -1;
        if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[1] != -1) {
            player1Area
                = DAT_TileMapState::instance
                      .PathConnectionLayer[DAT_GameState::instance.playerDataArray[1].buildingEntryInfos[8].tileEntry];
        }
        int player2Area = -1;
        if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[2] != -1) {
            player2Area
                = DAT_TileMapState::instance
                      .PathConnectionLayer[DAT_GameState::instance.playerDataArray[2].buildingEntryInfos[8].tileEntry];
        }
        int player3Area = -1;
        if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[3] != -1) {
            player3Area
                = DAT_TileMapState::instance
                      .PathConnectionLayer[DAT_GameState::instance.playerDataArray[3].buildingEntryInfos[8].tileEntry];
        }
        int player4Area = -1;
        if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[4] != -1) {
            player4Area
                = DAT_TileMapState::instance
                      .PathConnectionLayer[DAT_GameState::instance.playerDataArray[4].buildingEntryInfos[8].tileEntry];
        }
        int player5Area = -1;
        if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[5] != -1) {
            player5Area
                = DAT_TileMapState::instance
                      .PathConnectionLayer[DAT_GameState::instance.playerDataArray[5].buildingEntryInfos[8].tileEntry];
        }
        int player6Area = -1;
        if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[6] != -1) {
            player6Area
                = DAT_TileMapState::instance
                      .PathConnectionLayer[DAT_GameState::instance.playerDataArray[6].buildingEntryInfos[8].tileEntry];
        }
        int player7Area = -1;
        if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[7] != -1) {
            player7Area
                = DAT_TileMapState::instance
                      .PathConnectionLayer[DAT_GameState::instance.playerDataArray[7].buildingEntryInfos[8].tileEntry];
        }
        int player8Area = -1;
        if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[8] != -1) {
            player8Area
                = DAT_TileMapState::instance
                      .PathConnectionLayer[DAT_GameState::instance.playerDataArray[8].buildingEntryInfos[8].tileEntry];
        }

        if (DAT_GameSynchronyState::instance.currentGameMode != 0) {
            return;
        }

        for (int xBase = 0; xBase < 400; xBase += 10) {
            int x10 = xBase / 10;
            WildlifeGridElement* cell = &this->grid[x10][_y10];
            cell->firstMember = 0;
            cell->separateAreaID = 0;
            cell->unclaimedArea = 0;
            cell->buildingTiles = 0;
            cell->keeps = 0;
            cell->wallTiles = 0;
            cell->trees = 0;
            cell->unitCount = 0;
            cell->unstalkedUnitCount = 0;
            cell->stalkedUnitCount = 0;
            cell->camelCount = 0;
            cell->lionCount = 0;
            cell->deerCount = 0;
            cell->rabbitCount = 0;
            cell->marshTiles = 0;
            cell->rockyTiles = 0;
            cell->field_0x48 = 0;
            cell->farmFieldTiles = 0;
            cell->chimps = 0;
            cell->castlebuildings = 0;
            cell->field_0x70 = 0;

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
                        cell->firstMember += 1;
                        int tile = DAT_ViewportRenderState::instance.translationMatrix[y].addXgetTile + dx + xBase;
                        int areaId = DAT_TileMapState::instance.PathConnectionLayer[tile];
                        if (areaId == 0) {
                            cell->unclaimedArea += 1;
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
                            if (areaId == player1Area) {
                                cell->chimps += 1;
                            }
                            if (areaId == player2Area) {
                                cell->chimps += 1;
                            }
                            if (areaId == player3Area) {
                                cell->chimps += 1;
                            }
                            if (areaId == player4Area) {
                                cell->chimps += 1;
                            }
                            if (areaId == player5Area) {
                                cell->chimps += 1;
                            }
                            if (areaId == player6Area) {
                                cell->chimps += 1;
                            }
                            if (areaId == player7Area) {
                                cell->chimps += 1;
                            }
                            if (areaId == player8Area) {
                                cell->chimps += 1;
                            }
                        }
                        cell->field_0x70 += DAT_TileMapState::instance.HeightLayer[tile];
                        int logic = DAT_TileMapState::instance.LogicLayer[tile];
                        if ((logic & 0x100) != 0) {
                            cell->wallTiles += 1;
                            cell->castlebuildings += 1;
                        }
                        if ((logic & 0x20000000) != 0) {
                            cell->marshTiles += 1;
                        }
                        if ((logic & 0x20000) != 0) {
                            cell->rockyTiles += 1;
                        }
                        if ((logic & 0x80) != 0) {
                            cell->rockyTiles += 1;
                        }
                        if ((logic & 0x40000) != 0) {
                            cell->rockyTiles += 1;
                        }
                        if ((logic & 0x1000000) != 0) {
                            cell->farmFieldTiles += 1;
                        }
                        if ((logic & 0x2000000) != 0) {
                            cell->farmFieldTiles += 1;
                        }
                        int treeId = DAT_TileMapState::instance.OrganismLayer[tile];
                        if (treeId >= 1 && treeId < 2000) {
                            ushort tt = DAT_LandscapeState::instance.trees[treeId].treeType;
                            if (tt == Trees::TT_UNKNOWN_1 || tt == Trees::TT_UNKNOWN_2 || tt == Trees::TT_UNKNOWN_3
                                || tt == Trees::TT_UNKNOWN_4) {
                                cell->trees += 1;
                            }
                        }
                        int bldId = DAT_TileMapState::instance.BuildingLayer[tile];
                        if (bldId != 0) {
                            ushort bt = DAT_BuildingsState::instance.buildings[bldId].buildingType;
                            if (bt == Buildings::BT_MANORHOUSE) {
                                cell->keeps += 1;
                            } else if (bt == Buildings::BT_STONEKEEP) {
                                cell->keeps += 1;
                            } else if (bt == Buildings::BT_STRONGHOLD) {
                                cell->keeps += 1;
                            } else if (bt == Buildings::BT_KEEPFOUR) {
                                cell->keeps += 1;
                            } else if (bt == Buildings::BT_KEEPFIVE) {
                                cell->keeps += 1;
                            } else if (bt == Buildings::BT_CAMPGROUND) {
                                cell->keeps += 1;
                            } else if (bt == Buildings::BT_GATEHOUSELARGE || bt == Buildings::BT_GATEHOUSESMALL
                                || bt == Buildings::BT_WOODGATE1 || bt == Buildings::BT_WOODGATE2
                                || bt == Buildings::BT_DRAWBRIDGE || bt == Buildings::BT_TOWER1
                                || bt == Buildings::BT_TOWER2 || bt == Buildings::BT_TOWER3
                                || bt == Buildings::BT_TOWER4 || bt == Buildings::BT_TOWER5) {
                                cell->castlebuildings += 1;
                            }
                            if (DAT_BuildingsState::instance.buildings[bldId].buildingType != Buildings::BT_SIGNPOST) {
                                cell->buildingTiles += 1;
                            }
                        }
                        int unitId = DAT_TileMapState::instance.UnitLayer[tile];
                        if (unitId != 0) {
                            cell->unitCount += 1;
                            if (DAT_UnitsState::instance.units[unitId].isStalked != 0) {
                                cell->stalkedUnitCount += 1;
                                ushort ut = DAT_UnitsState::instance.units[unitId].unitType;
                                if (ut == Units::UT_ANTELOPESHDEER) {
                                    cell->deerCount += 1;
                                    if (DAT_TribesState::instance.tribes[DAT_UnitsState::instance.units[unitId].tribeID]
                                            .predatorNearby
                                        != 0) {
                                        cell->field_0x48 += 1;
                                    }
                                } else if (ut == Units::UT_RABBIT) {
                                    cell->rabbitCount += 1;
                                } else if (ut == Units::UT_CAMELSHBEAR) {
                                    cell->camelCount += 1;
                                } else if (ut == Units::UT_LIONSHWOLF) {
                                    cell->lionCount += 1;
                                }
                            } else {
                                cell->unstalkedUnitCount += 1;
                                cell->field_0x48 += 1;
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
            cell->separateAreaID = bestAreaId;
        }
    }

} // namespace Map
} // namespace OpenSHC
