#include "OpenSHC/IO/LowLevelMemory.func.hpp"
#include "OpenSHC/Map/WildlifeState.func.hpp"
#include "OpenSHC/Map/WildlifeState.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x0052e120
    void WildlifeState::updateNofFpoints()
    {
        int spIdx = DAT_TroopValueState::instance.attackInfo.field_0x469d4;
        int spX = DAT_GameState::instance.mapAndTime.signpostEntryData[spIdx].x;
        int spY = DAT_GameState::instance.mapAndTime.signpostEntryData[spIdx].y;
        if ((uint)spX > 399 || (uint)spY > 399
            || DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[spY * 400 + spX] == 0) {
            return;
        }
        int spTile = DAT_ViewportRenderState::instance.translationMatrix[spY].addXgetTile + spX;
        int spArea = (short)DAT_TileMapState::instance.PathConnectionLayer[spTile];
        if (DAT_GameSynchronyState::instance.currentGameMode != 0) {
            return;
        }

        MACRO_CALL_MEMBER(WildlifeState_Func::floodFillCasDisFromSignpost, this)();
        DAT_TroopValueState::instance.attackInfo.nof_fpoints = 0;
        for (int i = 0; i != 100; ++i) {
            DAT_TroopValueState::instance.attackInfo.nof_fpointsArray[i][3] = 0;
            DAT_TroopValueState::instance.attackInfo.nof_fpointsArray[i][2] = 0;
            DAT_TroopValueState::instance.attackInfo.nof_fpointsArray[i][1] = 0;
            DAT_TroopValueState::instance.attackInfo.nof_fpointsArray[i][0] = 0;
        }

        for (int y10 = 0; y10 < 40; ++y10) {
            int tileY = y10 * 10 + 5;
            for (int x10 = 0; x10 < 40; ++x10) {
                if (this->grid[x10][y10].field_0x6c != 0 && this->grid[x10][y10].firstMember > 0) {
                    int tileX = x10 * 10 + 5;
                    int tile = DAT_ViewportRenderState::instance.translationMatrix[tileY].addXgetTile + tileX;
                    int areaId = (short)DAT_TileMapState::instance.PathConnectionLayer[tile];
                    if (areaId == spArea && (uint)tileX <= 399 && (uint)tileY <= 399
                        && DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[tileY * 400 + tileX] != 0) {
                        int idx = DAT_TroopValueState::instance.attackInfo.nof_fpoints;
                        DAT_TroopValueState::instance.attackInfo.nof_fpointsArray[idx][0] = (short)tileX;
                        DAT_TroopValueState::instance.attackInfo
                            .nof_fpointsArray[DAT_TroopValueState::instance.attackInfo.nof_fpoints][1] = (short)tileY;
                        DAT_TroopValueState::instance.attackInfo
                            .nof_fpointsArray[DAT_TroopValueState::instance.attackInfo.nof_fpoints][2] = 0;
                        DAT_TroopValueState::instance.attackInfo
                            .nof_fpointsArray[DAT_TroopValueState::instance.attackInfo.nof_fpoints][3] = (short)areaId;
                        DAT_TroopValueState::instance.attackInfo
                            .nof_fpointsArray[DAT_TroopValueState::instance.attackInfo.nof_fpoints][4]
                            = (short)this->grid[x10][y10].field_0x70;
                        DAT_TroopValueState::instance.attackInfo
                            .nof_fpointsArray[DAT_TroopValueState::instance.attackInfo.nof_fpoints][5]
                            = (short)this->grid[x10][y10].casDisRelated2;
                        int curIdx = DAT_TroopValueState::instance.attackInfo.nof_fpoints;
                        DAT_TroopValueState::instance.attackInfo.nof_fpointsArray[curIdx][6]
                            = (short)((DAT_TroopValueState::instance.attackInfo.nof_fpointsArray[curIdx][5] + 4) * 50
                                - DAT_TroopValueState::instance.attackInfo.nof_fpointsArray[curIdx][4]);
                        DAT_TroopValueState::instance.attackInfo.nof_fpoints += 1;
                    }
                }
            }
        }

        int swapped;
        do {
            swapped = 0;
            for (int i = 0; i < DAT_TroopValueState::instance.attackInfo.nof_fpoints - 1; ++i) {
                if (DAT_TroopValueState::instance.attackInfo.nof_fpointsArray[i + 1][6]
                    < DAT_TroopValueState::instance.attackInfo.nof_fpointsArray[i][6]) {
                    swapped = 1;
                    MACRO_CALL_MEMBER(IO::LowLevelMemory_Func::copyData, DAT_LowLevelMemory::ptr)(16,
                        DAT_TroopValueState::instance.attackInfo.nof_fpointsArray[i],
                        DAT_TroopValueState::instance.attackInfo.nof_fpointsArrayCopy);
                    MACRO_CALL_MEMBER(IO::LowLevelMemory_Func::copyData, DAT_LowLevelMemory::ptr)(16,
                        DAT_TroopValueState::instance.attackInfo.nof_fpointsArray[i + 1],
                        DAT_TroopValueState::instance.attackInfo.nof_fpointsArray[i]);
                    MACRO_CALL_MEMBER(IO::LowLevelMemory_Func::copyData, DAT_LowLevelMemory::ptr)(16,
                        DAT_TroopValueState::instance.attackInfo.nof_fpointsArrayCopy,
                        DAT_TroopValueState::instance.attackInfo.nof_fpointsArray[i + 1]);
                }
            }
        } while (swapped != 0);
    }

} // namespace Map
} // namespace OpenSHC
