// disable deprecation warnings for strcpy/strcat
#pragma warning(disable : 4996)

#include "../Actions.func.hpp"

#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/AI/AIVState.func.hpp"
#include "OpenSHC/Audio/mss/SoundSystem.func.hpp"
#include "OpenSHC/Game/GameCore.func.hpp"
#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Game/Skirmish/SkirmishLobbySetupStructure.func.hpp"
#include "OpenSHC/IO/FilePackager.func.hpp"
#include "OpenSHC/IO/ResourceManager.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Entities/EntityState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Map/Units/TroopValueState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Map/WildlifeState.func.hpp"
#include "OpenSHC/Random/RNG.func.hpp"
#include "OpenSHC/Rendering/Bink/AIMessageQueue.func.hpp"
#include "OpenSHC/Rendering/ViewportRenderState.func.hpp"
#include "OpenSHC/Synchrony.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/UI/MenuTextInputState.func.hpp"
#include "OpenSHC/string-literals.hpp"

#include "OpenSHC/Globals/DAT_00b960dc.hpp"
#include "OpenSHC/Globals/DAT_00b960f8.hpp"
#include "OpenSHC/Globals/DAT_AICState.hpp"
#include "OpenSHC/Globals/DAT_AIVPlacementFit.hpp"
#include "OpenSHC/Globals/DAT_AIVState.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_EntityState.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MapDefinedData.hpp"
#include "OpenSHC/Globals/DAT_MenuTextInputState.hpp"
#include "OpenSHC/Globals/DAT_MissionDefinedData.hpp"
#include "OpenSHC/Globals/DAT_RenderingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_ResourceManager.hpp"
#include "OpenSHC/Globals/DAT_SoundSystemState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"
#include "OpenSHC/Globals/DAT_UIDragDropDefinedData.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_VideoBikQueue.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"
#include "OpenSHC/Globals/DAT_WildlifeState.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"
#include "OpenSHC/Globals/DWORD_00b95b1c.hpp"
#include "OpenSHC/Globals/FilePackagerObj.hpp"
#include "OpenSHC/Globals/INT_00b960f0.hpp"
#include "OpenSHC/Globals/PTR_005c2a68.hpp"
#include "OpenSHC/Globals/SEC_RNG.hpp"
#include "OpenSHC/Globals/SEC_SkirmishLobbySetupStructure.hpp"
#include "OpenSHC/Globals/TIME_ReceivedMessage_2.hpp"

#include <string.h>

namespace OpenSHC {
namespace UI {
    namespace Actions {

        // FUNCTION: STRONGHOLDCRUSADER 0x00441270
        void __cdecl LaunchSkirmishGame(int whichCastle)
        {
            int* const castles = (int*)whichCastle;
            MACRO_CALL_MEMBER(Game::Skirmish::SkirmishLobbySetupStructure_Func::commitSkirmishSettings,
                SEC_SkirmishLobbySetupStructure::ptr)();
            int const fogOfWar = DAT_GameState::instance.mapAndTime.skirmishFogOfWar;
            int const skirmishPoints = DAT_GameSynchronyState::instance.skirmishPoints;
            int lobby[sizeof(Game::Skirmish::SkirmishLobbySetupStructure) / 4];
            memcpy(lobby, &SEC_SkirmishLobbySetupStructure::instance, sizeof(lobby));
            int const autoSave = DAT_GameSynchronyState::instance.skirmishAutoSaveEveryMinutes;
            int const gameMode = DAT_GameSynchronyState::instance.currentGameMode;
            for (int i = 0; i < 9; i++) {
                DAT_AIVPlacementFit::instance[i] = -10;
            }
            DAT_GameCore::instance.missionNumber1to20 = 1;
            char mapFileName[1000];
            strcpy(mapFileName, DAT_GameSynchronyState::instance.mapName);
            strcat(mapFileName, s__map_005a2294);
            MACRO_CALL_MEMBER(IO::ResourceManager_Func::resolveResourceFileName, DAT_ResourceManager::ptr)(
                (IO::FileResourceType)15, mapFileName);
            MACRO_CALL_MEMBER(Map::TileMapState_Func::setupAllMapSections, DAT_TileMapState::ptr)();
            int maxTeam = 0;
            for (int i = 1; i < 9; i++) {
                char const group = DAT_GameSynchronyState::instance.DAT_PlayerGroupArray[i];
                DAT_GameState::instance.mapAndTime.playerGroupArray[i] = group;
                if (group > 0) {
                    DAT_GameState::instance.mapAndTime.playerTeams[i] = group;
                    if (group > maxTeam) {
                        maxTeam = group;
                    }
                }
            }
            for (int i = 1; i < 9; i++) {
                if (DAT_GameSynchronyState::instance.DAT_PlayerGroupArray[i] == 0) {
                    maxTeam += 1;
                    DAT_GameState::instance.mapAndTime.playerTeams[i] = maxTeam;
                }
            }
            int const playerSlotID = DAT_GameSynchronyState::instance.currentPlayerSlotID;
            int const rngSeed = SEC_RNG::instance.seed;
            int const advantageBalance = DAT_GameSynchronyState::instance.skirmishCurrentAdvantageBalance;
            int const intensityType = DAT_GameSynchronyState::instance.skirmishGameIntensityType;
            int const trailType = DAT_GameCore::instance.currentTrailType;
            int const isSkirmishTrail = DAT_GameCore::instance.isSkirmishTrail;
            int trailProgress = DAT_GameCore::instance.skirmishTrailProgress;
            if (trailType == 1) {
                trailProgress = DAT_GameCore::instance.warchestTrailProgress;
            } else if (trailType == 2) {
                trailProgress = DAT_GameCore::instance.extremeTrailProgress;
            }
            int teams[9];
            int groups[9];
            int ais[9];
            int aiVariations[9];
            int lordTypes[9];
            for (int i = 0; i < 9; i++) {
                teams[i] = DAT_GameState::instance.mapAndTime.playerTeams[i];
                groups[i] = DAT_GameState::instance.mapAndTime.playerGroupArray[i];
                ais[i] = DAT_GameSynchronyState::instance.currentAIArray[i];
                aiVariations[i] = DAT_GameSynchronyState::instance.aiVariationArray[i];
                lordTypes[i] = DAT_GameCore::instance.selectedLordTypes[i];
            }
            Game::Skirmish::SkirmishStatistics const results = DAT_GameSynchronyState::instance.finalResults;
            MACRO_CALL_MEMBER(IO::FilePackager_Func::readMapOrSavFile, FilePackagerObj::ptr)(
                DAT_MapDefinedData::instance.MapSectionAddressArray);
            MACRO_CALL_MEMBER(
                Audio::MSS::SoundSystem_Func::mapLoadingAndLaunchGameRelated1, DAT_SoundSystemState::ptr)();
            DAT_GameSynchronyState::instance.finalResults = results;
            memcpy(&SEC_SkirmishLobbySetupStructure::instance, lobby, sizeof(lobby));
            DAT_GameSynchronyState::instance.skirmishCurrentAdvantageBalance = advantageBalance;
            DAT_GameCore::instance.mapTimeInTicks = 1;
            DAT_GameCore::instance.section1127 = 1;
            DAT_GameCore::instance.currentTrailType = trailType;
            DAT_GameCore::instance.isVictoryOrDefeatUnk = 0;
            DAT_GameSynchronyState::instance.skirmishGameIntensityType = intensityType;
            DAT_GameCore::instance.isSkirmishTrail = isSkirmishTrail;
            if (trailType == 2) {
                DAT_GameCore::instance.extremeTrailProgress = trailProgress;
            } else if (trailType == 1) {
                DAT_GameCore::instance.warchestTrailProgress = trailProgress;
            } else {
                DAT_GameCore::instance.skirmishTrailProgress = trailProgress;
            }
            for (int i = 0; i < 9; i++) {
                if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[i] == -1 && ais[i] != 0) {
                    DAT_GameSynchronyState::instance.aiVariationArray[i] = aiVariations[i];
                }
            }
            MACRO_CALL_MEMBER(AI::AIVState_Func::wipeAIVsAndHeatMaps, DAT_AIVState::ptr)();
            SEC_RNG::instance.seed = rngSeed;
            DAT_GameCore::instance.isTimeHalted = 0;
            DAT_GameCore::instance.section1095 = 0;
            DAT_GameSynchronyState::instance.currentPlayerSlotID = playerSlotID;
            DAT_GameSynchronyState::instance.skirmishAutoSaveEveryMinutes = autoSave;
            MACRO_CALL_MEMBER(Random::RNG_Func::populateRNG1040, SEC_RNG::ptr)();
            DAT_GameSynchronyState::instance.skirmishPoints = skirmishPoints;
            DAT_GameState::instance.mapAndTime.skirmishFogOfWar = fogOfWar;
            for (int i = 0; i < 9; i++) {
                DAT_GameState::instance.mapAndTime.playerTeams[i] = teams[i];
                DAT_GameState::instance.mapAndTime.playerGroupArray[i] = groups[i];
                DAT_GameSynchronyState::instance.currentAIArray[i] = ais[i];
                DAT_GameCore::instance.selectedLordTypes[i] = lordTypes[i];
            }
            DAT_GameCore::instance.gameMode_2 = 3;
            DAT_GameCore::instance.xbowProducible_logic = 1;
            DAT_GameCore::instance.pikeProducible_logic = 1;
            DAT_GameCore::instance.swordProducible_logic = 1;
            DAT_GameCore::instance.bowProducible_logic = 1;
            DAT_GameCore::instance.spearProducible_logic = 1;
            DAT_GameCore::instance.maceProducible_logic = 1;
            DAT_GameState::instance.mapAndTime.unitJesterRelated = 1;
            DAT_GameState::instance.mapAndTime.unitLadyRelated = 0;
            DAT_GameState::instance.mapAndTime.difficulty = 1;
            DAT_GameSynchronyState::instance.skirmishTroopsCostGold = 1;
            DAT_GameCore::instance.missionNumber1to20 = DAT_GameSynchronyState::instance.skirmishTechLevel + 22;
            if (DAT_GameSynchronyState::instance.skirmishTechLevel == 2) {
                DAT_GameCore::instance.swordProducible_logic = 0;
                DAT_GameCore::instance.pikeProducible_logic = 0;
            }
            int keepCount = 0;
            int playerCount = 0;
            int keepPositions[9][2];
            for (int playerID = 1; playerID < 9; playerID++) {
                keepPositions[playerID][0] = -1;
                keepPositions[playerID][1] = -1;
                int const keepID = DAT_GameState::instance.playerDataArray[playerID].buildingEntryInfos[0].id;
                if (keepID != 0) {
                    keepCount += 1;
                    keepPositions[playerID][0] = DAT_BuildingsState::instance.buildings[keepID].x;
                    keepPositions[playerID][1] = DAT_BuildingsState::instance.buildings[keepID].y;
                    DAT_TileMapState::instance.showNoRubbleWhenDestroyingBuilding = 1;
                    MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::destroyBuildingAndLinkedDuplicates,
                        DAT_BuildingsState::ptr)(keepID);
                    DAT_TileMapState::instance.showNoRubbleWhenDestroyingBuilding = 1;
                    MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::destroyBuildingAndLinkedDuplicates,
                        DAT_BuildingsState::ptr)(
                        DAT_GameState::instance.playerDataArray[playerID].buildingEntryInfos[1].id);
                    int const lordID = DAT_GameState::instance.playerDataArray[playerID].lordID;
                    if (lordID != 0) {
                        if (DAT_GameState::instance.playerDataArray[playerID].lordUID
                            == DAT_UnitsState::instance.units[lordID].uid) {
                            MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::deleteUnit, DAT_UnitsState::ptr)(lordID);
                        }
                        DAT_GameState::instance.playerDataArray[playerID].lordID = 0;
                        DAT_GameState::instance.playerDataArray[playerID].lordUID = 0;
                    }
                    DAT_GameState::instance.playerDataArray[playerID].lordKilledByPlayerID = 0;
                }
                if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[playerID] != -1
                    || DAT_GameSynchronyState::instance.currentAIArray[playerID] != 0) {
                    playerCount += 1;
                }
            }
            if (playerCount < keepCount) {
                for (int playerID = 1; playerID < 9; playerID++) {
                    if ((char)DAT_GameSynchronyState::instance.playerPositionsArray[playerID - 1] < 0
                        && keepPositions[playerID][0] != -1) {
                        MACRO_CALL_MEMBER(Game::GameStateStructures_Func::destroyPlayerCompletely, DAT_GameState::ptr)(
                            playerID);
                    }
                }
            }
            int positions[9];
            for (int playerID = 1; playerID < 9; playerID++) {
                positions[playerID] = 0;
                DAT_GameState::instance.playerDataArray[playerID].aiType = 0;
                if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[playerID] != -1
                    || DAT_GameSynchronyState::instance.currentAIArray[playerID] != 0) {
                    positions[playerID] = MACRO_CALL(Synchrony_Func::GetPlayerPosition)(playerID);
                    if (playerID == positions[playerID]) {
                        MACRO_CALL_MEMBER(Game::GameStateStructures_Func::swapOwnership, DAT_GameState::ptr)(
                            playerID, playerID);
                        positions[playerID] = 0;
                    }
                }
            }
            for (int pass = 8; pass != 0; pass--) {
                for (int playerID = 1; playerID < 9; playerID++) {
                    if ((DAT_GameSynchronyState::instance.currentPlayerFullIDArray[playerID] != -1
                            || DAT_GameSynchronyState::instance.currentAIArray[playerID] != 0)
                        && positions[playerID] != 0) {
                        int const position = positions[playerID];
                        MACRO_CALL_MEMBER(Game::GameStateStructures_Func::swapOwnership, DAT_GameState::ptr)(
                            position, playerID);
                        for (int other = 1; other < 9; other++) {
                            if (positions[other] == playerID) {
                                positions[other] = position;
                                break;
                            }
                        }
                        positions[playerID] = 0;
                    }
                }
            }
            MACRO_CALL_MEMBER(AI::AIVState_Func::setAIVFilePresenceByFileHashArray, DAT_AIVState::ptr)();
            for (int playerID = 1; playerID != 9; playerID++) {
                if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[playerID] != -1) {
                    int const position = MACRO_CALL(Synchrony_Func::GetPlayerPosition)(playerID);
                    int const keepY = keepPositions[position][1];
                    int const keepX = keepPositions[position][0];
                    DAT_GameState::instance.playerDataArray[playerID].tacticalPowersBarLevel = 0;
                    DAT_TileMapState::instance.buildingPlacementFail = 0;
                    DAT_TileMapState::instance.clearKeepFootprintOnPlace = 1;
                    DAT_TileMapState::instance.skipPlacementCheck = 1;
                    DAT_GameState::instance.playerDataArray[playerID].field_0x229c
                        = DAT_GameSynchronyState::instance.skirmishPoints;
                    MACRO_CALL_MEMBER(Map::TileMapState_Func::placeBuilding, DAT_TileMapState::ptr)(
                        playerID, keepX, keepY, (Commands::MappersEnum)61, 7, 15);
                    int const height
                        = DAT_TileMapState::instance
                              .DefaultHeightLayer[DAT_ViewportRenderState::instance.translationMatrix[keepY].addXgetTile
                                  + keepX]
                        + 90;
                    MACRO_CALL_MEMBER(Map::Entities::EntityState_Func::spawnProjectileEntity, DAT_EntityState::ptr)(0,
                        playerID, playerID, keepX * 8 + 55, keepY * 8, height, keepX * 8 + 55, keepY * 8, height,
                        (Map::Entities::EntityType)11, 0);
                    if (playerID == DAT_GameSynchronyState::instance.currentPlayerSlotID) {
                        int const keepID = DAT_GameState::instance.playerDataArray[playerID].buildingEntryInfos[0].id;
                        MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::focusOnCoordinate,
                            DAT_ViewportRenderState::ptr)(DAT_BuildingsState::instance.buildings[keepID].x + 2,
                            DAT_BuildingsState::instance.buildings[keepID].y + 2);
                    }
                } else if (DAT_GameSynchronyState::instance.currentAIArray[playerID] != 0) {
                    int const position = MACRO_CALL(Synchrony_Func::GetPlayerPosition)(playerID);
                    DAT_GameState::instance.playerDataArray[playerID].field_0x229c
                        = DAT_GameSynchronyState::instance.skirmishPoints;
                    DAT_TileMapState::instance.clearKeepFootprintOnPlace = 1;
                    DAT_TileMapState::instance.skipPlacementCheck = 1;
                    DAT_TileMapState::instance.buildingPlacementFail = 0;
                    DAT_GameState::instance.playerDataArray[playerID].aiType
                        = (AI::AITypeInt)(DAT_GameSynchronyState::instance.currentAIArray[playerID] + 1);
                    int const aivID
                        = MACRO_CALL_MEMBER(AI::AIVState_Func::setupAIVMetadata, DAT_AIVState::ptr)(playerID);
                    int const keepY = keepPositions[position][1];
                    int const keepX = keepPositions[position][0];
                    DAT_GameState::instance.playerDataArray[playerID].aivID = aivID;
                    MACRO_CALL_MEMBER(AI::AIVState_Func::setKeepOffsetAndOrientation, DAT_AIVState::ptr)(
                        aivID, keepX, keepY);
                    if (castles == NULL) {
                        MACRO_CALL_MEMBER(AI::AIVState_Func::selectBestAIVwithRandomStart, DAT_AIVState::ptr)(
                            DAT_GameState::instance.playerDataArray[playerID].aivID);
                    } else {
                        DAT_AIVPlacementFit::instance[playerID] = MACRO_CALL_MEMBER(
                            AI::AIVState_Func::tryPlaceAIVAndReturnFitPercentage, DAT_AIVState::ptr)(
                            DAT_GameState::instance.playerDataArray[playerID].aivID, castles[playerID - 1]);
                    }
                    int const placedAIV = DAT_GameState::instance.playerDataArray[playerID].aivID;
                    if (DAT_AIVState::instance.aivs[placedAIV].aivSubType != 0) {
                        MACRO_CALL_MEMBER(AI::AIVState_Func::applyAIV, DAT_AIVState::ptr)(placedAIV, playerID);
                        MACRO_CALL_MEMBER(Map::TileMapState_Func::placeBuilding, DAT_TileMapState::ptr)(playerID,
                            DAT_AIVState::instance.keepX, DAT_AIVState::instance.keepY, (Commands::MappersEnum)61, 7,
                            DAT_AIVState::instance.aivs[placedAIV].keepOrientation);
                        int const keepID = DAT_GameState::instance.playerDataArray[playerID].buildingEntryInfos[0].id;
                        if (keepID != 0) {
                            int const x = DAT_BuildingsState::instance.buildings[keepID].x;
                            int const y = DAT_BuildingsState::instance.buildings[keepID].y;
                            int const height
                                = DAT_TileMapState::instance.DefaultHeightLayer
                                      [DAT_ViewportRenderState::instance.translationMatrix[y].addXgetTile + x + 6]
                                + 90;
                            MACRO_CALL_MEMBER(Map::Entities::EntityState_Func::spawnProjectileEntity,
                                DAT_EntityState::ptr)(0, playerID, playerID, x * 8 + 55, y * 8, height, x * 8 + 55,
                                y * 8, height, (Map::Entities::EntityType)11, 0);
                        }
                    } else {
                        MACRO_CALL_MEMBER(Map::TileMapState_Func::placeBuilding, DAT_TileMapState::ptr)(
                            playerID, keepX, keepY, (Commands::MappersEnum)61, 7, 15);
                    }
                }
            }
            if (DAT_GameCore::instance.mapU4Int0 != 0) {
                for (int playerID = 1; playerID < 9; playerID++) {
                    if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[playerID] == -1
                        && DAT_GameSynchronyState::instance.currentAIArray[playerID] == 0) {
                        int const keepX = keepPositions[5][0];
                        int const keepY = keepPositions[5][1];
                        DAT_GameState::instance.mapAndTime.somePlayerID = playerID;
                        DAT_TileMapState::instance.buildingPlacementFail = 0;
                        MACRO_CALL_MEMBER(Map::TileMapState_Func::placeBuilding, DAT_TileMapState::ptr)(
                            playerID, keepX, keepY, (Commands::MappersEnum)61, 7, 15);
                        int const tile = DAT_ViewportRenderState::instance.translationMatrix[keepY].addXgetTile + keepX;
                        int const buildingID = DAT_TileMapState::instance.BuildingLayer[tile];
                        int const height = DAT_TileMapState::instance.DefaultHeightLayer[tile] + 124;
                        DAT_GameState::instance.playerDataArray[playerID].buildingEntryInfos[0].id = 0;
                        *(short*)DAT_BuildingsState::instance.buildings[buildingID].padding_0x2c2
                            = MACRO_CALL_MEMBER(Map::Entities::EntityState_Func::spawnProjectileEntity,
                                DAT_EntityState::ptr)(0, playerID, 5, keepX * 8 + 55, keepY * 8, height, keepX * 8 + 55,
                                keepY * 8, height, (Map::Entities::EntityType)11, 0);
                        break;
                    }
                }
            }
            int const intensity = DAT_GameSynchronyState::instance.skirmishGameIntensityType;
            int const startGold = ((int*)&PTR_005c2a68::instance)[intensity];
            *(Game::StartingResourceStructureInt*)DAT_GameState::instance.mapAndTime.startGoods
                = DAT_RenderingDefinedData::instance.StartGoods[intensity - 1];
            DAT_GameState::instance.mapAndTime.startGoods[15] = startGold;
            for (int i = 0; i < 7; i++) {
                DAT_GameState::instance.mapAndTime.euroRecruitable[i] = 1;
                DAT_GameState::instance.mapAndTime.mercRecruitable[i] = 1;
            }
            for (int playerID = 1; playerID < 9; playerID++) {
                int advantage = 100;
                int troopsIndex;
                if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[playerID] != -1) {
                    int const lordType = MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::getLordTypeForPlayer,
                        DAT_GameSynchronyState::ptr)(playerID);
                    advantage = (&DAT_RenderingDefinedData::instance
                            .HumanAdvantageArray)[DAT_GameSynchronyState::instance.skirmishCurrentAdvantageBalance];
                    troopsIndex = lordType == 1 ? 19 : 18;
                } else if (DAT_GameSynchronyState::instance.currentAIArray[playerID] != 0) {
                    advantage = (&DAT_RenderingDefinedData::instance
                            .AIAdvantageArray)[DAT_GameSynchronyState::instance.skirmishCurrentAdvantageBalance];
                    troopsIndex = DAT_GameState::instance.playerDataArray[playerID].aiType - 1;
                } else {
                    troopsIndex = 0;
                }
                for (int i = 0; i < 20; i++) {
                    DAT_GameState::instance.mapAndTime.startingTroops[playerID - 1][i]
                        = DAT_RenderingDefinedData::instance
                              .StartingTroops[troopsIndex]
                                             [DAT_GameSynchronyState::instance.skirmishGameIntensityType - 1][i]
                        * advantage / 100;
                }
            }
            DAT_GameState::instance.mapAndTime.startingPopularity
                = DAT_GameSynchronyState::instance.skirmishDefaultPopularity * 10;
            MACRO_CALL_MEMBER(Map::TileMapState_Func::prepareMap, DAT_TileMapState::ptr)();
            MACRO_CALL_MEMBER(Map::WildlifeState_Func::clearWildlifeState, DAT_WildlifeState::ptr)();
            DAT_GameSynchronyState::instance.currentGameMode = gameMode;
            DAT_GameState::instance.mapAndTime.rawDeerCount
                = MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::getRawDeerCount, DAT_UnitsState::ptr)();
            MACRO_CALL_MEMBER(Game::GameStateStructures_Func::clearEnemyRelatedStructures, DAT_GameState::ptr)();
            DAT_GameState::instance.mapAndTime.militaryCampaignStage = 0;
            DAT_GameState::instance.mapAndTime.field3183_0x27dc = 0;
            DAT_GameState::instance.mapAndTime.militaryCampaignFlags = 0;
            DAT_GameState::instance.mapAndTime.yearCopy = 0;
            DAT_GameState::instance.mapAndTime.monthCopy = 0;
            DAT_GameState::instance.mapAndTime.field3184_0x27de = 0;
            MACRO_CALL_MEMBER(Game::GameStateStructures_Func::setMonthAndYear, DAT_GameState::ptr)(6, 1181);
            DAT_GameState::instance.mapAndTime.traderRelated1 = 4;
            DAT_GameState::instance.mapAndTime.traderRelatedCounter2 = 4;
            DAT_GameState::instance.mapAndTime.field1363_0x71c = 1;
            DAT_GameState::instance.mapAndTime.field1364_0x720 = 0;
            DAT_GameState::instance.mapAndTime.traderRelated2 = 0;
            DAT_GameState::instance.mapAndTime.traderRelatedCounter1 = 0;
            for (int playerID = 1; playerID < 9; playerID++) {
                if ((DAT_GameSynchronyState::instance.currentPlayerFullIDArray[playerID] != -1
                        || DAT_GameSynchronyState::instance.currentAIArray[playerID] != 0)
                    && DAT_GameState::instance.playerDataArray[playerID].buildingEntryInfos[0].id != 0) {
                    DAT_GameState::instance.mapAndTime.playerKeepTile[playerID]
                        = DAT_BuildingsState::instance
                              .buildings[DAT_GameState::instance.playerDataArray[playerID].buildingEntryInfos[0].id]
                              .currentTilePositionAdjusted;
                }
            }
            for (int i = 0; i < 25; i++) {
                DAT_GameState::instance.mapAndTime.buyAndSalesPriceArray[i].buyPrice
                    = DAT_RenderingDefinedData::instance.BuyPricePerResource[i];
                DAT_GameState::instance.mapAndTime.copyOfBuyAndSalesPrice[i].buyPrice
                    = DAT_RenderingDefinedData::instance.BuyPricePerResource[i];
                DAT_GameState::instance.mapAndTime.buyAndSalesPriceArray[i].salesPrice
                    = DAT_RenderingDefinedData::instance.SalesPricePerResource[i];
                DAT_GameState::instance.mapAndTime.copyOfBuyAndSalesPrice[i].salesPrice
                    = DAT_RenderingDefinedData::instance.SalesPricePerResource[i];
                DAT_GameState::instance.mapAndTime.isResourceTradeable[i] = 1;
                DAT_GameState::instance.mapAndTime.unknownResouceFlagArray1[i] = 0;
                DAT_GameState::instance.mapAndTime.unknownResourceFlagArray2[i] = 0;
            }
            if (DAT_GameSynchronyState::instance.skirmishTechLevel <= 2) {
                DAT_GameState::instance.mapAndTime.isResourceTradeable[16] = 0;
            }
            DAT_GameState::instance.mapAndTime.euroRecruitableCopy_index_0 = 1;
            DAT_GameState::instance.mapAndTime.euroRecruitableCopy_index_2 = 1;
            DAT_GameState::instance.mapAndTime.euroRecruitableCopy_index_4 = 1;
            DAT_GameState::instance.mapAndTime.euroRecruitableCopy_index_1_b = 1;
            DAT_GameState::instance.mapAndTime.euroRecruitableCopy_index_3_b = 1;
            DAT_GameState::instance.mapAndTime.euroRecruitableCopy_index_6_a = 1;
            DAT_GameState::instance.mapAndTime.euroRecruitableCopy_index_1_a = 1;
            DAT_GameState::instance.mapAndTime.euroRecruitableCopy_index_3_a_and_6_b = 1;
            DAT_GameState::instance.mapAndTime.euroRecruitableCopy_index_6_c = 1;
            MACRO_CALL(Synchrony_Func::SetAIPlayerNickNames)();
            if (DAT_GameSynchronyState::instance.currentGameMode == 99
                && DAT_GameSynchronyState::instance.currentPlayerSlotID == 0) {
                DAT_GameState::instance.playerDataArray[0].playerDeathRelated = 1;
            }
            for (int playerID = 1; playerID < 9; playerID++) {
                if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[playerID] == -1
                    && DAT_GameSynchronyState::instance.currentAIArray[playerID] == 0) {
                    DAT_GameSynchronyState::instance.finalResults.active[playerID] = 0;
                } else {
                    DAT_GameSynchronyState::instance.finalResults.active[playerID] = 1;
                    strcpy(DAT_GameSynchronyState::instance.finalResults.names[playerID],
                        DAT_GameSynchronyState::instance.DAT_PlayerNames[playerID]);
                    DAT_GameSynchronyState::instance.finalResults.finalGold[playerID] = 0;
                    DAT_GameSynchronyState::instance.finalResults.finalMaxPopulation[playerID] = 0;
                    DAT_GameSynchronyState::instance.finalResults.finalMaxGoodThings[playerID] = 0;
                    DAT_GameSynchronyState::instance.finalResults.finalMaxBadThings[playerID] = 0;
                    DAT_GameSynchronyState::instance.finalResults.finalBuildingsBurned[playerID] = 0;
                    DAT_GameSynchronyState::instance.finalResults.finalBuidingsDestroyed[playerID] = 0;
                    DAT_GameSynchronyState::instance.finalResults.finalFoodProduced[playerID] = 0;
                    DAT_GameSynchronyState::instance.finalResults.finalWeaponsProduced[playerID] = 0;
                    DAT_GameSynchronyState::instance.finalResults.finalIronProduced[playerID] = 0;
                    DAT_GameSynchronyState::instance.finalResults.finalStoneProduced[playerID] = 0;
                    DAT_GameSynchronyState::instance.finalResults.finalWoodProduced[playerID] = 0;
                    DAT_GameSynchronyState::instance.finalResults.finalPitchProduced[playerID] = 0;
                    DAT_GameSynchronyState::instance.finalResults.finalKilledLords[playerID] = 0;
                    DAT_GameSynchronyState::instance.finalResults.finalTroopsKilledWeighted[playerID] = 0;
                    DAT_GameSynchronyState::instance.finalResults.finalBuildingsDestroyedWeighted[playerID] = 0;
                    (&DAT_GameSynchronyState::instance.finalResults.yearStart)[playerID] = 0;
                }
            }
            memset(DAT_GameSynchronyState::instance.finalResults.finalKillMatrix, 0,
                sizeof(DAT_GameSynchronyState::instance.finalResults.finalKillMatrix));
            DAT_GameSynchronyState::instance.finalResults.monthStart = DAT_GameState::instance.mapAndTime.month;
            DAT_GameSynchronyState::instance.finalResults.yearStart = DAT_GameState::instance.mapAndTime.year;
            MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::clearAttackInfo, DAT_TroopValueState::ptr)();
            MACRO_CALL_MEMBER(AI::AIVState_Func::recomputeHeatmaps, DAT_AIVState::ptr)(1);
            MACRO_CALL_MEMBER(AI::AICState_Func::recomputeAttackAIZone, DAT_AICState::ptr)();
            for (int playerID = 1; playerID < 9; playerID++) {
                if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[playerID] == -1
                    && DAT_GameSynchronyState::instance.currentAIArray[playerID] != 0) {
                    MACRO_CALL_MEMBER(AI::AIVState_Func::recomputeAIAvailableGridTiles, DAT_AIVState::ptr)(playerID);
                }
            }
            MACRO_CALL_MEMBER(
                OpenSHC::Rendering::Bink::AIMessageQueue_Func::playNextStoredBinkVideo, DAT_VideoBikQueue::ptr)();
            DAT_GameState::instance.mapAndTime.skirmishStrongWalls
                = DAT_GameSynchronyState::instance.skirmishStrongWalls;
            DAT_GameState::instance.mapAndTime.skirmishAlliances = DAT_GameSynchronyState::instance.skirmishAlliances;
            DAT_GameState::instance.mapAndTime.skirmishNoDogs = DAT_GameSynchronyState::instance.skirmishNoDogs;
            DAT_GameState::instance.mapAndTime.skirmishNoCowThrowing
                = DAT_GameSynchronyState::instance.skirmishNoCowThrowing;
            DAT_GameState::instance.mapAndTime.skirmishExtremeMode
                = DAT_GameSynchronyState::instance.skirmishExtremeMode;
            DAT_GameState::instance.mapAndTime.skirmishExtremeMode2
                = DAT_GameSynchronyState::instance.skirmishExtremeMode2;
            int const noRushTicks = DAT_RenderingDefinedData::instance
                                        .NoRushTicks[DAT_GameSynchronyState::instance.skirmishNoRushSetting];
            DAT_GameState::instance.mapAndTime.skirmishNoRushTicks = noRushTicks;
            DAT_GameState::instance.mapAndTime.skirmishNoRushTicksLeft = noRushTicks;
            DAT_GameState::instance.mapAndTime.countUpTo201 = 0;
            MACRO_CALL_MEMBER(UI::MenuTextInputState_Func::clearModalDialog2to6, DAT_MenuTextInputState::ptr)();
            DAT_GameSynchronyState::instance.timeSkirmishGameStart = timeGetTime();
            DAT_GameCore::instance.buildmenuMenuTabToSwitchTo.tabType = 10;
            DAT_MissionDefinedData::instance.field_0xaf8 = false;
            int delay;
            if (DAT_GameCore::instance.currentMenuViewType == 55 || DAT_GameCore::instance.currentMenuViewType == 56) {
                delay = 0;
            } else {
                delay = 10000;
            }
            MACRO_CALL_MEMBER(Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                (UI::Enums::MenuViewType)14, delay);
            DAT_UIDragDropDefinedData::instance.MenuView_TriggerInitial = 1;
            DAT_WindowAndDirectDraw::instance.unk_resetViewportRelated = 1;
            DWORD_00b95b1c::instance = timeGetTime();
            DAT_00b960dc::instance = 1;
            MACRO_CALL_MEMBER(
                Synchrony::GameSynchronyState_Func::recomputeHashesAndSendResync, DAT_GameSynchronyState::ptr)(0);
            DAT_GameSynchronyState::instance.DAT_TwoIfNotHost = 0;
            for (int i = 0; i < 9; i++) {
                DAT_GameSynchronyState::instance.DAT_PlayerSlotArraySomeValue[i] = 0;
            }
            DAT_GameCore::instance.timeSum_2 = timeGetTime();
            DAT_GameCore::instance.gameDuration = 0;
            TIME_ReceivedMessage_2::instance = 0;
            DAT_00b960f8::instance = 0;
            INT_00b960f0::instance = 0;
        }

    } // namespace Actions
} // namespace UI
} // namespace OpenSHC
