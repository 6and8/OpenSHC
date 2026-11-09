#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/WildlifeState.func.hpp"
#include "OpenSHC/AI/Tribes/AITribeType.hpp"
#include "OpenSHC/Map/WildlifeState.hpp"

#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"
#include "OpenSHC/Globals/SEC_RNG.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x0052cab0
    void WildlifeState::findAndSetNewRallyPointForDeerAndLions(int tribeID, int always2or3or5, int always0or1)
    {
        int unitId = DAT_TribesState::instance.tribes[tribeID].selectionTargetUnitID;
        int x10 = DAT_UnitsState::instance.units[unitId].x / 10;
        int y10 = DAT_UnitsState::instance.units[unitId].y / 10;
        this->casDisRelated = always2or3or5;
        this->candidateIndex = 0;
        this->candidateIndex2 = 1;

        for (int y = 0; y < 40; ++y) {
            for (int x = 0; x < 40; ++x) {
                this->grid[x][y].casDisRelated2 = 0;
                this->grid[x][y].field_0x3c = 0;
            }
        }

        this->DAT_Y10_Array_Section1034[0] = (short)y10;
        this->DAT_X10_Array_Section1034[0] = (short)x10;
        this->grid[x10][y10].casDisRelated2 = always2or3or5;
        int startArea = this->grid[x10][y10].separateAreaID;

        while (this->candidateIndex != this->candidateIndex2) {
            int curX = this->DAT_X10_Array_Section1034[this->candidateIndex];
            int curY = this->DAT_Y10_Array_Section1034[this->candidateIndex];
            int curVal = this->grid[curX][curY].casDisRelated2;
            this->casDisRelated = curVal;
            if (curVal <= 1) {
                break;
            }
            int nextVal = curVal - 1;
            for (int dir = 0; dir < 8; ++dir) {
                unsigned int const nx
                    = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[dir].int_.xOffset + curX;
                unsigned int const ny
                    = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[dir].int_.yOffset + curY;
                if (nx <= 39 && ny <= 39) {
                    if (this->grid[nx][ny].firstMember > 0 && startArea == this->grid[nx][ny].separateAreaID) {
                        bool ok;
                        if (always0or1 != 0) {
                            ok = (this->grid[nx][ny].unstalkedUnitCount == 0 && this->grid[nx][ny].buildingTiles == 0
                                && this->grid[nx][ny].lionCount == 0);
                        } else {
                            if (this->grid[nx][ny].field_0x34 != 0) {
                                ok = false;
                            } else if (DAT_TribesState::instance.tribes[tribeID].tribeType == 13) {
                                ok = (this->grid[nx][ny].deerCount == 0 && this->grid[nx][ny].lionCount == 0);
                            } else {
                                ok = true;
                            }
                        }
                        if (ok && this->grid[nx][ny].casDisRelated2 < nextVal) {
                            this->grid[nx][ny].casDisRelated2 = nextVal;
                            this->DAT_X10_Array_Section1034[this->candidateIndex2] = (short)nx;
                            this->DAT_Y10_Array_Section1034[this->candidateIndex2] = (short)ny;
                            this->candidateIndex2 += 1;
                            if ((int)this->candidateIndex2 >= 1600) {
                                this->candidateIndex2 = 0;
                            }
                        }
                    }
                }
            }
            this->candidateIndex += 1;
            if ((int)this->candidateIndex >= 1600) {
                Ghidra::undefined4* candidateIndexPtr = &this->candidateIndex;
                *candidateIndexPtr = 0;
            }
        }

        int startDir = SEC_RNG::instance.currentNumber2 & 7;
        DAT_TribesState::instance.tribes[tribeID].currentRallyPointIndex = 0;
        DAT_TribesState::instance.tribes[tribeID].rallyPointCount = 0;
        this->grid[x10][y10].field_0x3c = 1;
        this->grid[x10][y10].casDisRelated2 = 0;

        int bestVal = always2or3or5;
        while (true) {
            int bestDir = -1;
            for (int i = 0; i < 8; ++i) {
                int dir = startDir + i;
                if (dir >= 8) {
                    dir -= 8;
                }
                unsigned int const nx
                    = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[dir].int_.xOffset + x10;
                unsigned int const ny
                    = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[dir].int_.yOffset + y10;
                if (nx <= 39 && ny <= 39) {
                    if (this->grid[nx][ny].firstMember > 0 && this->grid[nx][ny].casDisRelated2 != 0
                        && this->grid[nx][ny].casDisRelated2 < bestVal) {
                        bestVal = this->grid[nx][ny].casDisRelated2;
                        this->grid[nx][ny].casDisRelated2 = 0;
                        bestDir = dir;
                    }
                }
            }
            if (bestDir <= -1) {
                break;
            }
            x10 += DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[bestDir].int_.xOffset;
            y10 += DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[bestDir].int_.yOffset;
            this->grid[x10][y10].field_0x3c = 1;
            int tileX = x10 * 10 + 5;
            int tileY = y10 * 10 + 5;
            if ((uint)tileX <= 399 && (uint)tileY <= 399
                && DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[tileY * 400 + tileX] != 0) {
                MACRO_CALL_MEMBER(Navigation::PathFindingState_Func::pathFindingDeerAndLionsUnk,
                    DAT_PathFindingState::ptr)(tribeID, tileX, tileY);
                short rpIdx = DAT_TribesState::instance.tribes[tribeID].rallyPointCount;
                DAT_TribesState::instance.tribes[tribeID].rallyPointArray[rpIdx][0]
                    = (short)DAT_PathFindingState::instance.climbX;
                DAT_TribesState::instance.tribes[tribeID]
                    .rallyPointArray[DAT_TribesState::instance.tribes[tribeID].rallyPointCount][1]
                    = (short)DAT_PathFindingState::instance.climbY;
                DAT_TribesState::instance.tribes[tribeID].rallyPointCount += 1;
            }
        }
    }

} // namespace Map
} // namespace OpenSHC
