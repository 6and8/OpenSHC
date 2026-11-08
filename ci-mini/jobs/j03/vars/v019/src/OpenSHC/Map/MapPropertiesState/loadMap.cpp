#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/Audio/mss/SoundSystem.func.hpp"
#include "OpenSHC/Game/GameCore.func.hpp"
#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/IO/FilePackager.func.hpp"
#include "OpenSHC/IO/ResourceManager.func.hpp"
#include "OpenSHC/Map/MapPropertiesState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Units/TroopValueState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Rendering/Bink/AIMessageQueue.func.hpp"
#include "OpenSHC/Game/GameMode2.hpp"

#include "OpenSHC/Globals/DAT_AICState.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MapDefinedData.hpp"
#include "OpenSHC/Globals/DAT_MapPropertiesState.hpp"
#include "OpenSHC/Globals/DAT_ResourceManager.hpp"
#include "OpenSHC/Globals/DAT_SoundSystemState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_VideoBikQueue.hpp"
#include "OpenSHC/Globals/FilePackagerObj.hpp"
#include "OpenSHC/Globals/TIME_ReceivedMessage_2.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x004C62C0
    void MapPropertiesState::loadMap(char* mapName)
    {
        // the map file overwrites these: keep the current game's values
        int difficulty = DAT_GameState::instance.mapAndTime.difficulty;
        int xbowProducible = DAT_GameCore::instance.xbowProducible_logic;
        int gameMode = DAT_GameCore::instance.gameMode_2;
        int playerSlot = DAT_GameSynchronyState::instance.currentPlayerSlotID;
        int swordProducible = DAT_GameCore::instance.swordProducible_logic;
        int pikeProducible = DAT_GameCore::instance.pikeProducible_logic;
        int bowProducible = DAT_GameCore::instance.bowProducible_logic;
        int maceProducible = DAT_GameCore::instance.maceProducible_logic;
        int spearProducible = DAT_GameCore::instance.spearProducible_logic;
        int jester = DAT_GameState::instance.mapAndTime.unitJesterRelated;
        char hintsRevealed[8];
        memcpy(hintsRevealed, &DAT_GameState::instance.mapAndTime.field43_0xf0, sizeof(hintsRevealed));
        int lady = DAT_GameState::instance.mapAndTime.unitLadyRelated;
        int mission = DAT_GameCore::instance.missionNumber1to20;
        MACRO_CALL_MEMBER(Game::GameStateStructures_Func::resetTeams, DAT_GameState::ptr)();
        MACRO_CALL_MEMBER(Map::TileMapState_Func::setupAllMapSections, DAT_TileMapState::ptr)();
        MACRO_CALL_MEMBER(IO::ResourceManager_Func::resolveResourceFileName, DAT_ResourceManager::ptr)(
            IO::FRT_MAPS, mapName);
        MACRO_CALL_MEMBER(IO::FilePackager_Func::readMapOrSavFile, FilePackagerObj::ptr)(
            DAT_MapDefinedData::instance.MapSectionAddressArray);
        MACRO_CALL_MEMBER(Audio::MSS::SoundSystem_Func::mapLoadingAndLaunchGameRelated1, DAT_SoundSystemState::ptr)();
        DAT_GameState::instance.mapAndTime.difficulty = difficulty;
        DAT_GameCore::instance.xbowProducible_logic = xbowProducible;
        DAT_GameCore::instance.pikeProducible_logic = pikeProducible;
        DAT_GameCore::instance.gameMode_2 = gameMode;
        DAT_GameCore::instance.swordProducible_logic = swordProducible;
        DAT_GameCore::instance.bowProducible_logic = bowProducible;
        DAT_GameCore::instance.mapTimeInTicks = 1;
        DAT_GameCore::instance.section1127 = 1;
        int* missionNumber1to20Ptr = &DAT_GameCore::instance.missionNumber1to20;
        *missionNumber1to20Ptr = mission;
        DAT_GameCore::instance.spearProducible_logic = spearProducible;
        DAT_GameCore::instance.maceProducible_logic = maceProducible;
        if (mission == 1) {
            // the first mission: the first eight units of type 22 owned by player 1 go to player 3
            int remaining = 8;
            for (int unit = 1; unit < 2500; ++unit) {
                if (DAT_UnitsState::instance.units[unit].logicalState != 0
                    && DAT_UnitsState::instance.units[unit].unitType == 22
                    && DAT_UnitsState::instance.units[unit].owner == 1) {
                    DAT_UnitsState::instance.units[unit].calculatedOwnerPlayerIndex = 3;
                    if (--remaining == 0) {
                        break;
                    }
                }
            }
        }
        DAT_GameState::instance.mapAndTime.unitLadyRelated = (short)lady;
        for (int player = 0; player < 9; ++player) {
            DAT_GameSynchronyState::instance.currentPlayerFullIDArray[player] = -1;
        }
        DAT_GameState::instance.mapAndTime.unitJesterRelated = (short)jester;
        DAT_GameSynchronyState::instance.currentPlayerSlotID = playerSlot;
        memcpy(&DAT_GameState::instance.mapAndTime.field43_0xf0, hintsRevealed, sizeof(hintsRevealed));
        DAT_GameSynchronyState::instance.currentPlayerFullIDArray[playerSlot] = 1;
        for (int player = 1; player < 9; ++player) {
            DAT_GameState::instance.playerDataArray[player].tacticalPowersBarLevel = 0;
        }
        DAT_GameCore::instance.isTimeHalted = FALSE;
        DAT_GameCore::instance.section1095 = 0;
        strcpy((char*)this->SEC_Section1089, mapName);
        if (DAT_GameCore::instance.gameMode_2 == Game::GM_CAMPAIGN_MISSION) {
            MACRO_CALL_MEMBER(Game::GameCore_Func::removeJesterAndLadyUnitsInCertainMissions, DAT_GameCore::ptr)();
        } else if (DAT_GameCore::instance.gameMode_2 == Game::GM_ECONOMIC_CAMPAIGN_SH1) {
            MACRO_CALL_MEMBER(Game::GameCore_Func::removeLadyAndJester, DAT_GameCore::ptr)();
        }
        int* events = (int*)this->SEC_EventsExtra;
        for (int i = 0; i < 8000; ++i) {
            events[i] = 0;
        }
        DAT_GameState::instance.mapAndTime.month = this->SEC_StartingMonth;
        DAT_GameState::instance.mapAndTime.year = this->SEC_StartingYear;
        if ((uint)(DAT_GameCore::instance.missionNumber1to20 - 16) <= 4) {
            MACRO_CALL_MEMBER(Map::MapPropertiesState_Func::adjustEventMonthAndYearForSection1047, this)();
        }
        if (DAT_GameState::instance.mapAndTime.month == this->SEC_StartingMonth
            && DAT_GameState::instance.mapAndTime.year == this->SEC_StartingYear) {
            for (int i = 0; i < 25; ++i) {
                DAT_GameState::instance.mapAndTime.startGoods[i] = this->SEC_StartingResources[i];
            }
            DAT_GameState::instance.mapAndTime.startGoods[7] = DAT_GameState::instance.mapAndTime.startGoods[8];
            DAT_GameState::instance.mapAndTime.startGoods[8] = 0;
            int* siegeTo = (int*)&DAT_GameState::instance.mapAndTime.siegeInformation;
            int* siegeFrom = (int*)&this->SEC_SiegeInformation;
            for (int i = 0; i < 20; ++i) {
                siegeTo[i] = siegeFrom[i];
            }
            DAT_GameState::instance.mapAndTime.startingPopularity = this->SEC_StartingPopularity * 10;
            MACRO_CALL_MEMBER(Game::GameStateStructures_Func::setMonthAndYear, DAT_GameState::ptr)(
                this->SEC_StartingMonth, this->SEC_StartingYear);
        }
        this->SEC_Section1080 = 0;
        this->SEC_Section1081 = 0;
        MACRO_CALL_MEMBER(Map::Units::TribesState_Func::countDeerEfficiently, DAT_TribesState::ptr)();
        MACRO_CALL_MEMBER(Map::TileMapState_Func::prepareMap, DAT_TileMapState::ptr)();
        MACRO_CALL_MEMBER(Game::GameStateStructures_Func::clearEnemyRelatedStructures, DAT_GameState::ptr)();
        DAT_UnitsState::instance.lastSelectedUnitID = 0;
        MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::deselectAllUnitsOneByOne, DAT_UnitsState::ptr)();
        MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::clearSelectionCountsAndPlayerIDs, DAT_UnitsState::ptr)();
        short* barracks = (short*)&DAT_MapPropertiesState::instance.barracksRecruitability;
        for (int i = 0; i < 7; ++i) {
            DAT_GameState::instance.mapAndTime.euroRecruitable[i] = barracks[i];
        }
        for (int i = 0; i < 7; ++i) {
            DAT_GameState::instance.mapAndTime.mercRecruitable[i] = DAT_MapPropertiesState::instance.SEC_MercRecruitable[i];
        }
        DAT_GameState::instance.mapAndTime.euroRecruitableCopy_index_0 = 0;
        DAT_GameState::instance.mapAndTime.euroRecruitableCopy_index_1_b = 0;
        DAT_GameState::instance.mapAndTime.euroRecruitableCopy_index_2 = 0;
        DAT_GameState::instance.mapAndTime.euroRecruitableCopy_index_3_b = 0;
        DAT_GameState::instance.mapAndTime.euroRecruitableCopy_index_4 = 0;
        DAT_GameState::instance.mapAndTime.euroRecruitableCopy_index_6_a = 0;
        DAT_GameState::instance.mapAndTime.euroRecruitableCopy_index_1_a = 0;
        DAT_GameState::instance.mapAndTime.euroRecruitableCopy_index_3_a_and_6_b = 0;
        DAT_GameState::instance.mapAndTime.euroRecruitableCopy_index_6_c = 0;
        if (DAT_GameState::instance.mapAndTime.euroRecruitable[0] != 0) {
            DAT_GameState::instance.mapAndTime.euroRecruitableCopy_index_0 = 1;
        }
        if (DAT_GameState::instance.mapAndTime.euroRecruitable[1] != 0) {
            DAT_GameState::instance.mapAndTime.euroRecruitableCopy_index_1_b = 1;
            DAT_GameState::instance.mapAndTime.euroRecruitableCopy_index_1_a = 1;
        }
        if (DAT_GameState::instance.mapAndTime.euroRecruitable[2] != 0) {
            DAT_GameState::instance.mapAndTime.euroRecruitableCopy_index_2 = 1;
        }
        if (DAT_GameState::instance.mapAndTime.euroRecruitable[3] != 0) {
            DAT_GameState::instance.mapAndTime.euroRecruitableCopy_index_3_b = 1;
            DAT_GameState::instance.mapAndTime.euroRecruitableCopy_index_3_a_and_6_b = 1;
        }
        if (DAT_GameState::instance.mapAndTime.euroRecruitable[4] != 0) {
            DAT_GameState::instance.mapAndTime.euroRecruitableCopy_index_4 = 1;
            DAT_GameState::instance.mapAndTime.euroRecruitableCopy_index_1_a = 1;
        }
        if (DAT_GameState::instance.mapAndTime.euroRecruitable[5] != 0) {
            DAT_GameState::instance.mapAndTime.euroRecruitableCopy_index_6_a = 1;
            DAT_GameState::instance.mapAndTime.euroRecruitableCopy_index_3_a_and_6_b = 1;
        }
        if (DAT_GameState::instance.mapAndTime.euroRecruitable[6] != 0) {
            DAT_GameState::instance.mapAndTime.euroRecruitableCopy_index_6_a = 1;
            DAT_GameState::instance.mapAndTime.euroRecruitableCopy_index_3_a_and_6_b = 1;
            DAT_GameState::instance.mapAndTime.euroRecruitableCopy_index_6_c = 1;
        }
        DAT_GameState::instance.mapAndTime.countUpTo201 = 0;
        DAT_GameState::instance.mapAndTime.cathedralRelated1 = 0;
        MACRO_CALL_MEMBER(Map::MapPropertiesState_Func::importTradingCosts, this)();
        MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::clearAttackInfo, DAT_TroopValueState::ptr)();
        MACRO_CALL_MEMBER(AI::AICState_Func::recomputeAIZonerLayer, DAT_AICState::ptr)();
        MACRO_CALL_MEMBER(Map::TileMapState_Func::setSignpostDistanceForCampaignMission, DAT_TileMapState::ptr)();
        MACRO_CALL_MEMBER(Rendering::Bink::AIMessageQueue_Func::playNextStoredBinkVideo, DAT_VideoBikQueue::ptr)();
        DAT_GameCore::instance.xbowProducible_logic = DAT_MapPropertiesState::instance.SEC_XbowProducible_save;
        DAT_GameCore::instance.bowProducible_logic = DAT_MapPropertiesState::instance.SEC_BowProducible_save;
        DAT_GameCore::instance.pikeProducible_logic = DAT_MapPropertiesState::instance.SEC_PikeProducible_save;
        DAT_GameCore::instance.spearProducible_logic = DAT_MapPropertiesState::instance.SEC_SpearProducible_save;
        DAT_GameCore::instance.swordProducible_logic = DAT_MapPropertiesState::instance.SEC_SwordProducible_save;
        DAT_GameCore::instance.maceProducible_logic = DAT_MapPropertiesState::instance.SEC_MaceProducible_save;
        DAT_GameCore::instance.gameDuration = 0;
        DAT_GameCore::instance.timeSum_2 = timeGetTime();
        TIME_ReceivedMessage_2::instance = 0;
    }

}
}
