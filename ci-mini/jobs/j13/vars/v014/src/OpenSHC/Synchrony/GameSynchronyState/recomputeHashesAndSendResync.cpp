#include "../GameSynchronyState.func.hpp"

#include "OpenSHC/Map/Navigation/DirectionAlgorithmState.func.hpp"

#include "OpenSHC/Globals/DAT_AIVState.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_DirectionAlgorithmState.hpp"
#include "OpenSHC/Globals/DAT_EntityState.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_LandscapeState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Synchrony {

    // FUNCTION: STRONGHOLDCRUSADER 0x0048CC90
    void GameSynchronyState::recomputeHashesAndSendResync(int dontSendSyncCommand)
    {
        if (this->DAT_GameHalted != 0) {
            return;
        }
        if (this->DAT_HashCountdown != 0) {
            this->DAT_HashCountdown -= 1;
            return;
        }
        this->HASH_HashTotal[this->currentPlayerSlotID] = 0;
        this->DAT_PlayerMatchTimes[this->currentPlayerSlotID] = DAT_GameCore::instance.mapTimeInTicks;
        {
            int unitSum = 0;
            for (int i = 0; i < 2500; ++i) {
                int const saved41c = DAT_UnitsState::instance.units[i].field_0x41c;
                int const saved420 = DAT_UnitsState::instance.units[i].field_0x420;
                DAT_UnitsState::instance.units[i].field_0x420 = 0;
                DAT_UnitsState::instance.units[i].field_0x41c = 0;
                int const hash = MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::computeHash, DAT_DirectionAlgorithmState::ptr)(1028, (int*)&DAT_UnitsState::instance.units[i].logicalState)
                    + (DAT_UnitsState::instance.units[i].animationLeapTicksTotal + DAT_UnitsState::instance.units[i].animationSpeed + DAT_UnitsState::instance.units[i].animationTicker);
                DAT_UnitsState::instance.units[i].field_0x41c = saved41c;
                unitSum += hash;
                this->HASH_Units[this->currentPlayerSlotID][i] = hash;
                DAT_UnitsState::instance.units[i].field_0x420 = saved420;
            }
            this->HASH_PartialHashPerPlayer.player[this->currentPlayerSlotID].domain[0] = unitSum;
            this->HASH_HashTotal[this->currentPlayerSlotID] += unitSum;
        }
        {
            int buildingSum = 0;
            for (int i = 0; i < 2000; ++i) {
                int const saved = *(short*)DAT_BuildingsState::instance.buildings[i].padding_0x2fc;
                *(short*)DAT_BuildingsState::instance.buildings[i].padding_0x2fc = 0;
                int const hash = MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::computeHash, DAT_DirectionAlgorithmState::ptr)(604, (int*)&DAT_BuildingsState::instance.buildings[i].logicalState) + DAT_BuildingsState::instance.buildings[i].animationIndex
                    + (DAT_BuildingsState::instance.buildings[i].extraAnimationFrame3 + DAT_BuildingsState::instance.buildings[i].extraAnimationFrame2 + DAT_BuildingsState::instance.buildings[i].extraAnimationFrame1
                        + DAT_BuildingsState::instance.buildings[i].campgroundVclock + DAT_BuildingsState::instance.buildings[i].animAdvanceThrottle);
                *(short*)DAT_BuildingsState::instance.buildings[i].padding_0x2fc = saved;
                buildingSum += hash;
                this->HASH_Buildings[this->currentPlayerSlotID][i] = hash;
            }
            this->HASH_PartialHashPerPlayer.player[this->currentPlayerSlotID].domain[1] = buildingSum;
            this->HASH_HashTotal[this->currentPlayerSlotID] += buildingSum;
        }
        {
            int treeSum = 0;
            for (int i = 0; i < 2000; ++i) {
                int const hash = MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::computeHash, DAT_DirectionAlgorithmState::ptr)(88, (int*)&DAT_LandscapeState::instance.trees[i].state);
                treeSum += hash;
                this->HASH_Trees[this->currentPlayerSlotID][i] = hash;
            }
            this->HASH_PartialHashPerPlayer.player[this->currentPlayerSlotID].domain[2] = treeSum;
            this->HASH_HashTotal[this->currentPlayerSlotID] += treeSum;
        }
        {
            int tribeSum = 0;
            for (int i = 0; i < 1250; ++i) {
                int const hash = MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::computeHash, DAT_DirectionAlgorithmState::ptr)(816, (int*)&DAT_TribesState::instance.tribes[i].owner);
                tribeSum += hash;
                this->HASH_Tribes[this->currentPlayerSlotID][i] = hash;
            }
            this->HASH_PartialHashPerPlayer.player[this->currentPlayerSlotID].domain[3] = tribeSum;
            this->HASH_HashTotal[this->currentPlayerSlotID] += tribeSum;
        }
        {
            int playerSum = 0;
            for (int i = 0; i < 9; ++i) {
                int const saved5 = DAT_GameState::instance.playerDataArray[i].someAiCountdown5;
                int const saved4 = DAT_GameState::instance.playerDataArray[i].someAiCountdown4;
                int const saved6 = DAT_GameState::instance.playerDataArray[i].someAiCountdown6;
                int const saved3 = DAT_GameState::instance.playerDataArray[i].someAiCountdown3;
                int const savedIgnition = DAT_GameState::instance.playerDataArray[i].ignitionTime;
                DAT_GameState::instance.playerDataArray[i].ignitionTime = 0;
                DAT_GameState::instance.playerDataArray[i].someAiCountdown6 = 0;
                DAT_GameState::instance.playerDataArray[i].someAiCountdown5 = 0;
                DAT_GameState::instance.playerDataArray[i].someAiCountdown4 = 0;
                DAT_GameState::instance.playerDataArray[i].someAiCountdown3 = 0;
                int const hash = MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::computeHash, DAT_DirectionAlgorithmState::ptr)(14748, (int*)DAT_GameState::instance.playerDataArray[i].padding_0x58);
                playerSum += hash;
                this->HASH_PlayerDatas[this->currentPlayerSlotID][i] = hash;
                DAT_GameState::instance.playerDataArray[i].someAiCountdown4 = saved4;
                DAT_GameState::instance.playerDataArray[i].someAiCountdown3 = saved3;
                DAT_GameState::instance.playerDataArray[i].someAiCountdown5 = saved5;
                DAT_GameState::instance.playerDataArray[i].someAiCountdown6 = saved6;
                DAT_GameState::instance.playerDataArray[i].ignitionTime = savedIgnition;
            }
            this->HASH_PartialHashPerPlayer.player[this->currentPlayerSlotID].domain[4] = playerSum;
            this->HASH_HashTotal[this->currentPlayerSlotID] += playerSum;
        }
        {
            int sectionSum = 0;
            byte* const base = (byte*)&DAT_GameState::instance.mapAndTime.syncedStateBase;
            int i;
            for (i = 0; i < 18; ++i) {
                int const hash = MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::computeHash, DAT_DirectionAlgorithmState::ptr)(14566, (int*)(base + i * 14566));
                sectionSum += hash;
                this->HASH_Section1023[this->currentPlayerSlotID][i] = hash;
            }
            int hash = MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::computeHash, DAT_DirectionAlgorithmState::ptr)(16, (int*)(base + i * 14566));
            sectionSum += hash;
            this->HASH_Section1023[this->currentPlayerSlotID][i] = hash;
            hash = MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::computeHash, DAT_DirectionAlgorithmState::ptr)(816, (int*)&DAT_AIVState::instance.mapExtraInfo.totalWoodAvailable);
            sectionSum += hash;
            this->HASH_Section1023[this->currentPlayerSlotID][19] = hash;
            this->HASH_PartialHashPerPlayer.player[this->currentPlayerSlotID].domain[5] = sectionSum;
            this->HASH_HashTotal[this->currentPlayerSlotID] += sectionSum;
        }
        {
            int tileSum = 0;
            for (int i = 0; i < 128; ++i) {
                {
                    int const hash = MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::computeHash, DAT_DirectionAlgorithmState::ptr)(2512, (int*)&DAT_TileMapState::instance.LogicLayer[i * 628]);
                    this->HASH_LogicalTileMap[this->currentPlayerSlotID].hashDataArray[0].componentArray[i] = hash;
                    tileSum += hash;
                }
            }
            for (int i = 0; i < 64; ++i) {
                this->HASH_LogicalTileMap[this->currentPlayerSlotID].hashDataArray[1].componentArray[i] = 0;
                this->HASH_LogicalTileMap[this->currentPlayerSlotID].hashDataArray[2].componentArray[i] = 0;
                {
                    int const hash = MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::computeHash, DAT_DirectionAlgorithmState::ptr)(2512, (int*)&DAT_TileMapState::instance.OrganismLayer[i * 1256]);
                    this->HASH_LogicalTileMap[this->currentPlayerSlotID].hashDataArray[3].componentArray[i] = hash;
                    tileSum += hash;
                }
                {
                    int const hash = MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::computeHash, DAT_DirectionAlgorithmState::ptr)(2512, (int*)&DAT_TileMapState::instance.BuildingLayer[i * 1256]);
                    this->HASH_LogicalTileMap[this->currentPlayerSlotID].hashDataArray[4].componentArray[i] = hash;
                    tileSum += hash;
                }
                {
                    int const hash = MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::computeHash, DAT_DirectionAlgorithmState::ptr)(2512, (int*)&DAT_TileMapState::instance.UnitLayer[i * 1256]);
                    this->HASH_LogicalTileMap[this->currentPlayerSlotID].hashDataArray[5].componentArray[i] = hash;
                    tileSum += hash;
                }
                {
                    int const hash = MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::computeHash, DAT_DirectionAlgorithmState::ptr)(2512, (int*)&DAT_TileMapState::instance.EntityLayer[i * 1256]);
                    this->HASH_LogicalTileMap[this->currentPlayerSlotID].hashDataArray[6].componentArray[i] = hash;
                    tileSum += hash;
                }
                this->HASH_LogicalTileMap[this->currentPlayerSlotID].hashDataArray[7].componentArray[i] = 0;
                {
                    int const hash = MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::computeHash, DAT_DirectionAlgorithmState::ptr)(2512, (int*)&DAT_TileMapState::instance.PathConnectionLayer[i * 1256]);
                    this->HASH_LogicalTileMap[this->currentPlayerSlotID].hashDataArray[8].componentArray[i] = hash;
                    tileSum += hash;
                }
                this->HASH_LogicalTileMap[this->currentPlayerSlotID].hashDataArray[9].componentArray[i] = 0;
            }
            for (int i = 0; i < 32; ++i) {
                {
                    int const hash = MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::computeHash, DAT_DirectionAlgorithmState::ptr)(2512, (int*)&DAT_TileMapState::instance.DamageLayer[i * 2512]);
                    this->HASH_LogicalTileMap[this->currentPlayerSlotID].hashDataArray[10].componentArray[i] = hash;
                    tileSum += hash;
                }
                this->HASH_LogicalTileMap[this->currentPlayerSlotID].hashDataArray[11].componentArray[i] = 0;
                {
                    int const hash = MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::computeMaskedBitAccumulator, DAT_DirectionAlgorithmState::ptr)(2512, (uint*)&DAT_TileMapState::instance.WallOwnerLayer[i * 2512], 0x7070707);
                    this->HASH_LogicalTileMap[this->currentPlayerSlotID].hashDataArray[12].componentArray[i] = hash;
                    tileSum += hash;
                }
                {
                    int const hash = MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::computeHash, DAT_DirectionAlgorithmState::ptr)(2512, (int*)&DAT_TileMapState::instance.PathLinkageLayer[i * 2512]);
                    this->HASH_LogicalTileMap[this->currentPlayerSlotID].hashDataArray[13].componentArray[i] = hash;
                    tileSum += hash;
                }
                {
                    int const hash = MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::computeHash, DAT_DirectionAlgorithmState::ptr)(2512, (int*)&DAT_TileMapState::instance.OccupancyLayer[i * 2512]);
                    this->HASH_LogicalTileMap[this->currentPlayerSlotID].hashDataArray[14].componentArray[i] = hash;
                    tileSum += hash;
                }
                {
                    int const hash = MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::computeHash, DAT_DirectionAlgorithmState::ptr)(2512, (int*)&DAT_TileMapState::instance.HeightLayer[i * 2512]);
                    this->HASH_LogicalTileMap[this->currentPlayerSlotID].hashDataArray[15].componentArray[i] = hash;
                    tileSum += hash;
                }
                {
                    int const hash = MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::computeHash, DAT_DirectionAlgorithmState::ptr)(2512, (int*)&DAT_TileMapState::instance.AIInfoLayer[i * 2512]);
                    this->HASH_LogicalTileMap[this->currentPlayerSlotID].hashDataArray[16].componentArray[i] = hash;
                    tileSum += hash;
                }
                {
                    int const hash = MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::computeHash, DAT_DirectionAlgorithmState::ptr)(2512, (int*)&DAT_TileMapState::instance.AIZoneLayer[i * 2512]);
                    this->HASH_LogicalTileMap[this->currentPlayerSlotID].hashDataArray[17].componentArray[i] = hash;
                    tileSum += hash;
                }
                {
                    int const hash = MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::computeHash, DAT_DirectionAlgorithmState::ptr)(2512, (int*)&DAT_TileMapState::instance.SEC_TileMap1104[i * 2512]);
                    this->HASH_LogicalTileMap[this->currentPlayerSlotID].hashDataArray[18].componentArray[i] = hash;
                    tileSum += hash;
                }
                {
                    int const hash = MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::computeHash, DAT_DirectionAlgorithmState::ptr)(2512, (int*)&DAT_TileMapState::instance.unitDeathHeatMap[i * 2512]);
                    this->HASH_LogicalTileMap[this->currentPlayerSlotID].hashDataArray[19].componentArray[i] = hash;
                    tileSum += hash;
                }
                {
                    int const hash = MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::computeHash, DAT_DirectionAlgorithmState::ptr)(2512, (int*)&DAT_TileMapState::instance.SEC_PathfindingCostTileMap1105[0][i * 2512]);
                    this->HASH_LogicalTileMap[this->currentPlayerSlotID].hashDataArray[20].componentArray[i] = hash;
                    tileSum += hash;
                }
                {
                    int const hash = MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::computeHash, DAT_DirectionAlgorithmState::ptr)(2512, (int*)&DAT_TileMapState::instance.SEC_PathfindingCostTileMap1105[1][i * 2512]);
                    this->HASH_LogicalTileMap[this->currentPlayerSlotID].hashDataArray[21].componentArray[i] = hash;
                    tileSum += hash;
                }
                {
                    int const hash = MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::computeHash, DAT_DirectionAlgorithmState::ptr)(2512, (int*)&DAT_TileMapState::instance.SEC_PathfindingCostTileMap1105[2][i * 2512]);
                    this->HASH_LogicalTileMap[this->currentPlayerSlotID].hashDataArray[22].componentArray[i] = hash;
                    tileSum += hash;
                }
                {
                    int const hash = MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::computeHash, DAT_DirectionAlgorithmState::ptr)(2512, (int*)&DAT_TileMapState::instance.SEC_PathfindingCostTileMap1105[3][i * 2512]);
                    this->HASH_LogicalTileMap[this->currentPlayerSlotID].hashDataArray[23].componentArray[i] = hash;
                    tileSum += hash;
                }
                {
                    int const hash = MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::computeHash, DAT_DirectionAlgorithmState::ptr)(2512, (int*)&DAT_TileMapState::instance.SEC_PathfindingCostTileMap1105[4][i * 2512]);
                    this->HASH_LogicalTileMap[this->currentPlayerSlotID].hashDataArray[24].componentArray[i] = hash;
                    tileSum += hash;
                }
                {
                    int const hash = MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::computeHash, DAT_DirectionAlgorithmState::ptr)(2512, (int*)&DAT_TileMapState::instance.SEC_PathfindingCostTileMap1105[5][i * 2512]);
                    this->HASH_LogicalTileMap[this->currentPlayerSlotID].hashDataArray[25].componentArray[i] = hash;
                    tileSum += hash;
                }
                {
                    int const hash = MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::computeHash, DAT_DirectionAlgorithmState::ptr)(2512, (int*)&DAT_TileMapState::instance.SEC_PathfindingCostTileMap1105[6][i * 2512]);
                    this->HASH_LogicalTileMap[this->currentPlayerSlotID].hashDataArray[26].componentArray[i] = hash;
                    tileSum += hash;
                }
                {
                    int const hash = MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::computeHash, DAT_DirectionAlgorithmState::ptr)(2512, (int*)&DAT_TileMapState::instance.SEC_PathfindingCostTileMap1105[7][i * 2512]);
                    this->HASH_LogicalTileMap[this->currentPlayerSlotID].hashDataArray[27].componentArray[i] = hash;
                    tileSum += hash;
                }
                {
                    int const hash = MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::computeHash, DAT_DirectionAlgorithmState::ptr)(2512, (int*)&DAT_TileMapState::instance.SEC_PathfindingCostTileMap1105[8][i * 2512]);
                    this->HASH_LogicalTileMap[this->currentPlayerSlotID].hashDataArray[28].componentArray[i] = hash;
                    tileSum += hash;
                }
            }
            this->HASH_PartialHashPerPlayer.player[this->currentPlayerSlotID].domain[6] = tileSum;
            this->HASH_HashTotal[this->currentPlayerSlotID] += tileSum;
        }
        {
            int entitySum = 0;
            for (int i = 25; i < 3000; ++i) {
                short const screenDirection = DAT_EntityState::instance.entityArray[i].screenDirection;
                short const x1 = DAT_EntityState::instance.entityArray[i].x1;
                short const y1 = DAT_EntityState::instance.entityArray[i].y1;
                short const originX = DAT_EntityState::instance.entityArray[i].originX;
                short const originY = DAT_EntityState::instance.entityArray[i].originY;
                int const graphicType2 = DAT_EntityState::instance.entityArray[i].graphicType2;
                short const imageID = DAT_EntityState::instance.entityArray[i].imageID;
                short const be = DAT_EntityState::instance.entityArray[i].field_0xbe;
                short const c0 = DAT_EntityState::instance.entityArray[i].field_0xc0;
                int const displayValue = DAT_EntityState::instance.entityArray[i].displayValue;
                short const c8 = DAT_EntityState::instance.entityArray[i].field_0xc8;
                short const ca = DAT_EntityState::instance.entityArray[i].field_0xca;
                short const cc = DAT_EntityState::instance.entityArray[i].field_0xcc;
                short const ce = DAT_EntityState::instance.entityArray[i].field_0xce;
                DAT_EntityState::instance.entityArray[i].screenDirection = 0;
                DAT_EntityState::instance.entityArray[i].x1 = 0;
                DAT_EntityState::instance.entityArray[i].y1 = 0;
                DAT_EntityState::instance.entityArray[i].originX = 0;
                DAT_EntityState::instance.entityArray[i].originY = 0;
                DAT_EntityState::instance.entityArray[i].graphicType2 = 0;
                DAT_EntityState::instance.entityArray[i].imageID = 0;
                DAT_EntityState::instance.entityArray[i].field_0xce = 0;
                DAT_EntityState::instance.entityArray[i].field_0xcc = 0;
                DAT_EntityState::instance.entityArray[i].field_0xca = 0;
                DAT_EntityState::instance.entityArray[i].field_0xc8 = 0;
                DAT_EntityState::instance.entityArray[i].displayValue = 0;
                DAT_EntityState::instance.entityArray[i].field_0xc0 = 0;
                DAT_EntityState::instance.entityArray[i].field_0xbe = 0;
                int const hash = MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::computeHash, DAT_DirectionAlgorithmState::ptr)(232, (int*)&DAT_EntityState::instance.entityArray[i]);
                DAT_EntityState::instance.entityArray[i].screenDirection = screenDirection;
                DAT_EntityState::instance.entityArray[i].x1 = x1;
                DAT_EntityState::instance.entityArray[i].y1 = y1;
                DAT_EntityState::instance.entityArray[i].originX = originX;
                DAT_EntityState::instance.entityArray[i].originY = originY;
                DAT_EntityState::instance.entityArray[i].graphicType2 = graphicType2;
                DAT_EntityState::instance.entityArray[i].imageID = imageID;
                DAT_EntityState::instance.entityArray[i].field_0xbe = be;
                entitySum += hash;
                DAT_EntityState::instance.entityArray[i].displayValue = displayValue;
                DAT_EntityState::instance.entityArray[i].field_0xc0 = c0;
                DAT_EntityState::instance.entityArray[i].field_0xcc = cc;
                DAT_EntityState::instance.entityArray[i].field_0xc8 = c8;
                DAT_EntityState::instance.entityArray[i].field_0xce = ce;
                DAT_EntityState::instance.entityArray[i].field_0xca = ca;
                this->HASH_Entities[this->currentPlayerSlotID][i] = hash;
            }
            this->HASH_PartialHashPerPlayer.player[this->currentPlayerSlotID].domain[7] = entitySum;
            this->HASH_HashTotal[this->currentPlayerSlotID] += entitySum;
        }
        {
            int moatSum = 0;
            for (int i = 0; i < 16000; i += 100) {
                int const hash = MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::computeHash, DAT_DirectionAlgorithmState::ptr)(1600, (int*)&DAT_TileMapState::instance.moats[i].tile);
                moatSum += hash;
                this->HASH_Moats[this->currentPlayerSlotID][i / 100] = hash;
            }
            this->HASH_PartialHashPerPlayer.player[this->currentPlayerSlotID].domain[8] = moatSum;
            this->HASH_HashTotal[this->currentPlayerSlotID] += moatSum;
        }
        {
            int climbSum = 0;
            for (int i = 0; i < 200; ++i) {
                int const hash = MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::computeHash, DAT_DirectionAlgorithmState::ptr)(516, (int*)&DAT_PathFindingState::instance.climbData[i].canBeUsed);
                climbSum += hash;
                this->HASH_ClimbData[this->currentPlayerSlotID][i] = hash;
            }
            this->HASH_PartialHashPerPlayer.player[this->currentPlayerSlotID].domain[9] = climbSum;
            this->HASH_HashTotal[this->currentPlayerSlotID] += climbSum;
        }
        {
            int ditchSum = 0;
            for (int i = 0; i < 4000; i += 100) {
                int const hash = MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::computeHash, DAT_DirectionAlgorithmState::ptr)(2000, (int*)&DAT_TileMapState::instance.pitchDitches[i].tile);
                ditchSum += hash;
                this->HASH_PitchDitches[this->currentPlayerSlotID][i / 100] = hash;
            }
            this->HASH_PartialHashPerPlayer.player[this->currentPlayerSlotID].domain[10] = ditchSum;
            this->HASH_HashTotal[this->currentPlayerSlotID] += ditchSum;
        }
        for (int i = 0; i < 40; ++i) {
            this->HASH_Unknown2[this->currentPlayerSlotID][i] = 0;
        }
        this->HASH_PartialHashPerPlayer.player[this->currentPlayerSlotID].domain[11] = 0;
        {
            int aivSum = 0;
            for (int i = 0; i < 9; ++i) {
                int const hash = MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::computeHash, DAT_DirectionAlgorithmState::ptr)(28056, (int*)&DAT_AIVState::instance.aivs[i].playerID);
                aivSum += hash;
                this->HASH_AIVS[this->currentPlayerSlotID][i] = hash;
            }
            this->HASH_PartialHashPerPlayer.player[this->currentPlayerSlotID].domain[12] = aivSum;
            this->HASH_HashTotal[this->currentPlayerSlotID] += aivSum;
        }
        {
            int heatSum = 0;
            for (int i = 0; i < 80; ++i) {
                int const hash = MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::computeHash, DAT_DirectionAlgorithmState::ptr)(3840, (int*)&DAT_AIVState::instance.heatMaps[i][0].algorithmIterationNumber);
                heatSum += hash;
                this->HASH_HeatMaps[this->currentPlayerSlotID][i] = hash;
            }
            this->HASH_PartialHashPerPlayer.player[this->currentPlayerSlotID].domain[13] = heatSum;
            this->HASH_HashTotal[this->currentPlayerSlotID] += heatSum;
        }
        if (dontSendSyncCommand == 0) {
            MACRO_CALL_MEMBER(GameSynchronyState_Func::queueCommand, DAT_GameSynchronyState::ptr)(
                OpenSHC::Commands::GCT_ANNOUNCE_PLAYER_INFORMATION_AVAILABLE_AIVSSPECIALTRANSMITLOGIC);
        }
    }

}
}
