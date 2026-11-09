#include "OpenSHC/Map/WildlifeState.func.hpp"
#include "OpenSHC/Map/WildlifeState.hpp"

#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"
#include "OpenSHC/Globals/SEC_RNG.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x0052cfe0
    BOOLEnum WildlifeState::buildRallyPointPathForTribe(int param_1, int param_2)
    {
        int unitId = DAT_TribesState::instance.tribes[param_1].selectionTargetUnitID;
        int x10 = DAT_UnitsState::instance.units[unitId].x / 10;
        int y10 = DAT_UnitsState::instance.units[unitId].y / 10;
        this->casDisRelated = param_2;
        this->candidateIndex = 0;
        this->candidateIndex2 = 1;
        if (this->grid[x10][y10].field_0x50 == 0) {
            return FALSE;
        }

        for (int y = 0; y < 40; ++y) {
            for (int x = 0; x < 40; ++x) {
                this->grid[x][y].casDisRelated2 = 0;
                this->grid[x][y].field_0x3c = 0;
            }
        }

        this->DAT_Y10_Array_Section1034[0] = (short)y10;
        this->DAT_X10_Array_Section1034[0] = (short)x10;
        this->grid[x10][y10].casDisRelated2 = this->grid[x10][y10].field_0x50;
        int startArea = this->grid[x10][y10].separateAreaID;

        while (this->candidateIndex != this->candidateIndex2) {
            int curY = this->DAT_Y10_Array_Section1034[this->candidateIndex];
            int curX = this->DAT_X10_Array_Section1034[this->candidateIndex];
            for (int dir = 0; dir != 8; ++dir) {
                unsigned int const nx
                    = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[dir].int_.xOffset + curX;
                unsigned int const ny
                    = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[dir].int_.yOffset + curY;
                if (nx <= 39 && ny <= 39) {
                    if (this->grid[nx][ny].firstMember > 0 && startArea == this->grid[nx][ny].separateAreaID
                        && this->grid[nx][ny].field_0x50 > 0 && this->grid[nx][ny].casDisRelated2 == 0) {
                        this->grid[nx][ny].casDisRelated2 = this->grid[nx][ny].field_0x50;
                        this->DAT_X10_Array_Section1034[this->candidateIndex2] = (short)nx;
                        this->DAT_Y10_Array_Section1034[this->candidateIndex2] = (short)ny;
                        this->candidateIndex2 += 1;
                        if ((int)this->candidateIndex2 >= 1600) {
                            this->candidateIndex2 = 0;
                        }
                    }
                }
            }
            this->candidateIndex += 1;
            if ((int)this->candidateIndex >= 1600) {
                this->candidateIndex = 0;
            }
        }

        int startDir = SEC_RNG::instance.currentNumber2 & 7;
        DAT_TribesState::instance.tribes[param_1].currentRallyPointIndex = 0;
        DAT_TribesState::instance.tribes[param_1].rallyPointCount = 0;
        this->grid[x10][y10].field_0x3c = 1;
        this->grid[x10][y10].casDisRelated2 = 0;

        int bestVal = param_2;
        while (true) {
            int bestDir = -1;
            for (int i = 0; i < 8; ++i) {
                int dir = startDir + i;
                if (dir >= 8) {
                    dir -= 8;
                }
                int nx = x10 + DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[dir].int_.xOffset;
                int ny = y10 + DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[dir].int_.yOffset;
                if ((uint)nx <= 39 && (uint)ny <= 39) {
                    WildlifeGridElement* nCell = &this->grid[nx][ny];
                    if (nCell->firstMember > 0 && nCell->casDisRelated2 != 0 && nCell->casDisRelated2 > bestVal) {
                        int val = nCell->casDisRelated2;
                        nCell->casDisRelated2 = 0;
                        bestVal = val;
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
                short rpIdx = DAT_TribesState::instance.tribes[param_1].rallyPointCount;
                DAT_TribesState::instance.tribes[param_1].rallyPointArray[rpIdx][0] = (short)(x10 * 10 + 5);
                DAT_TribesState::instance.tribes[param_1]
                    .rallyPointArray[DAT_TribesState::instance.tribes[param_1].rallyPointCount][1]
                    = (short)(y10 * 10 + 5);
                DAT_TribesState::instance.tribes[param_1].rallyPointCount += 1;
            }
        }
        return TRUE;
    }

} // namespace Map
} // namespace OpenSHC
