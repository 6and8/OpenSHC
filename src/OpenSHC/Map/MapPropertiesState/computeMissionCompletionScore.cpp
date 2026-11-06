#include "OpenSHC/Map/MapPropertiesState.func.hpp"

#include "OpenSHC/Map/Units/TroopValueState.func.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MapPropertiesState.hpp"
#include "OpenSHC/Globals/DAT_MissionAestheticsDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x004BDE40
    void MapPropertiesState::computeMissionCompletionScore()
    {
        int deadlineYear = 0;
        int deadlineMonth = 0;
        this->missionScore = -1;
        this->objectiveGoodsCount = 0;
        for (int i = 0; i < this->eventsCount; ++i) {
            if (this->scenarioEvents[i].header.tl_type == 3
                && (this->scenarioEvents[i].data.scenario.ScenarioEventType == 1 || this->scenarioEvents[i].data.scenario.ScenarioEventType == 27)
                && this->scenarioEvents[i].data.scenario.conditions[0].enabled != 0) {
                deadlineMonth = this->scenarioEvents[i].header.month;
                deadlineYear = this->scenarioEvents[i].header.year;
            }
            if (this->scenarioEvents[i].header.tl_type != 3
                || (this->scenarioEvents[i].data.scenario.ScenarioEventType != 0 && this->scenarioEvents[i].data.scenario.ScenarioEventType != 26)) {
                continue;
            }
            for (int j = i + 1; j < this->eventsCount; ++j) {
                if (this->scenarioEvents[j].header.tl_type == 3
                    && (this->scenarioEvents[j].data.scenario.ScenarioEventType == 0
                        || this->scenarioEvents[j].data.scenario.ScenarioEventType == 26)) {
                    goto nextEvent;
                }
            }
            if (this->scenarioEvents[i].data.scenario.conditions[6].enabled != 0) {
                this->objectiveGoodsType[this->objectiveGoodsCount] = this->scenarioEvents[i].data.scenario.conditions[6].subType;
                this->objectiveGoodsSurplus[this->objectiveGoodsCount]
                    = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                          .currentResources[this->objectiveGoodsType[this->objectiveGoodsCount]]
                    - MACRO_CALL_MEMBER(MapPropertiesState_Func::getDifficultyMultipliedValue, this)(this->scenarioEvents[i].data.scenario.conditions[6].value);
                switch (this->objectiveGoodsType[this->objectiveGoodsCount]) {
                case 2:
                case 10:
                case 11:
                case 12:
                case 13:
                    this->objectiveGoodsScore[this->objectiveGoodsCount] = this->objectiveGoodsSurplus[this->objectiveGoodsCount] * 5;
                    break;
                case 17:
                case 18:
                case 19:
                case 20:
                case 21:
                case 22:
                case 23:
                case 24:
                    this->objectiveGoodsScore[this->objectiveGoodsCount] = this->objectiveGoodsSurplus[this->objectiveGoodsCount] * 50;
                    break;
                case 6:
                    this->objectiveGoodsScore[this->objectiveGoodsCount] = this->objectiveGoodsSurplus[this->objectiveGoodsCount] * 20;
                    break;
                default:
                    this->objectiveGoodsScore[this->objectiveGoodsCount] = this->objectiveGoodsSurplus[this->objectiveGoodsCount] * 10;
                }
                if (this->objectiveGoodsSurplus[this->objectiveGoodsCount] > 0) {
                    this->objectiveGoodsCount += 1;
                }
            }
            if (this->scenarioEvents[i].data.scenario.conditions[17].enabled != 0) {
                this->objectiveGoodsType[this->objectiveGoodsCount] = this->scenarioEvents[i].data.scenario.conditions[17].subType;
                this->objectiveGoodsSurplus[this->objectiveGoodsCount]
                    = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                          .currentResources[this->objectiveGoodsType[this->objectiveGoodsCount]]
                    - MACRO_CALL_MEMBER(MapPropertiesState_Func::getDifficultyMultipliedValue, this)(this->scenarioEvents[i].data.scenario.conditions[17].value);
                switch (this->objectiveGoodsType[this->objectiveGoodsCount]) {
                case 2:
                case 10:
                case 11:
                case 12:
                case 13:
                    this->objectiveGoodsScore[this->objectiveGoodsCount] = this->objectiveGoodsSurplus[this->objectiveGoodsCount] * 5;
                    break;
                case 17:
                case 18:
                case 19:
                case 20:
                case 21:
                case 22:
                case 23:
                case 24:
                    this->objectiveGoodsScore[this->objectiveGoodsCount] = this->objectiveGoodsSurplus[this->objectiveGoodsCount] * 50;
                    break;
                case 6:
                    this->objectiveGoodsScore[this->objectiveGoodsCount] = this->objectiveGoodsSurplus[this->objectiveGoodsCount] * 20;
                    break;
                default:
                    this->objectiveGoodsScore[this->objectiveGoodsCount] = this->objectiveGoodsSurplus[this->objectiveGoodsCount] * 10;
                }
                if (this->objectiveGoodsSurplus[this->objectiveGoodsCount] > 0) {
                    this->objectiveGoodsCount += 1;
                }
            }
            if (this->scenarioEvents[i].data.scenario.conditions[5].enabled != 0) {
                this->objectiveGoodsType[this->objectiveGoodsCount] = this->scenarioEvents[i].data.scenario.conditions[5].subType;
                this->objectiveGoodsSurplus[this->objectiveGoodsCount]
                    = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                          .currentResources[this->objectiveGoodsType[this->objectiveGoodsCount]]
                    - MACRO_CALL_MEMBER(MapPropertiesState_Func::getDifficultyMultipliedValue, this)(this->scenarioEvents[i].data.scenario.conditions[5].value);
                switch (this->objectiveGoodsType[this->objectiveGoodsCount]) {
                case 2:
                case 10:
                case 11:
                case 12:
                case 13:
                    this->objectiveGoodsScore[this->objectiveGoodsCount] = this->objectiveGoodsSurplus[this->objectiveGoodsCount] * 5;
                    break;
                case 17:
                case 18:
                case 19:
                case 20:
                case 21:
                case 22:
                case 23:
                case 24:
                    this->objectiveGoodsScore[this->objectiveGoodsCount] = this->objectiveGoodsSurplus[this->objectiveGoodsCount] * 50;
                    break;
                case 6:
                    this->objectiveGoodsScore[this->objectiveGoodsCount] = this->objectiveGoodsSurplus[this->objectiveGoodsCount] * 20;
                    break;
                default:
                    this->objectiveGoodsScore[this->objectiveGoodsCount] = this->objectiveGoodsSurplus[this->objectiveGoodsCount] * 10;
                }
                if (this->objectiveGoodsSurplus[this->objectiveGoodsCount] > 0) {
                    this->objectiveGoodsCount += 1;
                }
            }
            if (this->scenarioEvents[i].data.scenario.conditions[7].enabled != 0) {
                this->objectiveGoodsType[this->objectiveGoodsCount] = this->scenarioEvents[i].data.scenario.conditions[7].subType;
                this->objectiveGoodsSurplus[this->objectiveGoodsCount]
                    = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                          .currentResources[this->objectiveGoodsType[this->objectiveGoodsCount]]
                    - MACRO_CALL_MEMBER(MapPropertiesState_Func::getDifficultyMultipliedValue, this)(this->scenarioEvents[i].data.scenario.conditions[7].value);
                switch (this->objectiveGoodsType[this->objectiveGoodsCount]) {
                case 2:
                case 10:
                case 11:
                case 12:
                case 13:
                    this->objectiveGoodsScore[this->objectiveGoodsCount] = this->objectiveGoodsSurplus[this->objectiveGoodsCount] * 5;
                    break;
                case 17:
                case 18:
                case 19:
                case 20:
                case 21:
                case 22:
                case 23:
                case 24:
                    this->objectiveGoodsScore[this->objectiveGoodsCount] = this->objectiveGoodsSurplus[this->objectiveGoodsCount] * 50;
                    break;
                case 6:
                    this->objectiveGoodsScore[this->objectiveGoodsCount] = this->objectiveGoodsSurplus[this->objectiveGoodsCount] * 20;
                    break;
                default:
                    this->objectiveGoodsScore[this->objectiveGoodsCount] = this->objectiveGoodsSurplus[this->objectiveGoodsCount] * 10;
                }
                if (this->objectiveGoodsSurplus[this->objectiveGoodsCount] > 0) {
                    this->objectiveGoodsCount += 1;
                }
            }
            if (this->scenarioEvents[i].data.scenario.conditions[4].enabled != 0) {
                this->objectiveGoodsType[this->objectiveGoodsCount] = 15;
                this->objectiveGoodsSurplus[this->objectiveGoodsCount]
                    = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID].currentResources[15]
                    - MACRO_CALL_MEMBER(MapPropertiesState_Func::getDifficultyMultipliedValue, this)(this->scenarioEvents[i].data.scenario.conditions[4].value);
                this->objectiveGoodsScore[this->objectiveGoodsCount] = this->objectiveGoodsSurplus[this->objectiveGoodsCount];
                if (this->objectiveGoodsSurplus[this->objectiveGoodsCount] > 0) {
                    this->objectiveGoodsCount += 1;
                }
            }
            if (this->scenarioEvents[i].data.scenario.conditions[1].enabled != 0) {
                this->objectiveGoodsType[this->objectiveGoodsCount] = -1;
                this->objectiveGoodsSurplus[this->objectiveGoodsCount]
                    = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID].currentPopulation
                    - MACRO_CALL_MEMBER(MapPropertiesState_Func::getDifficultyMultipliedValue, this)(this->scenarioEvents[i].data.scenario.conditions[1].value);
                this->objectiveGoodsScore[this->objectiveGoodsCount] = this->objectiveGoodsSurplus[this->objectiveGoodsCount];
                if (this->objectiveGoodsSurplus[this->objectiveGoodsCount] > 0) {
                    this->objectiveGoodsCount += 1;
                }
            }
        nextEvent:;
        }
        this->monthsRemaining = 0;
        this->timeBonusScore = 0;
        if (deadlineYear != 0) {
            int monthsLeft = (deadlineYear - DAT_GameState::instance.mapAndTime.year) * 12
                - DAT_GameState::instance.mapAndTime.month + deadlineMonth;
            monthsLeft = monthsLeft > 0 ? monthsLeft : 0;
            this->monthsRemaining = monthsLeft;
            this->timeBonusScore = monthsLeft * 100;
        }
        this->missionScore = this->timeBonusScore;
        this->missionScore += DAT_MissionAestheticsDefinedData::instance
                                  .MissionScoreByDifficulty[DAT_GameState::instance.mapAndTime.difficulty];
        for (int goodsIndex = 0; goodsIndex < this->objectiveGoodsCount; ++goodsIndex) {
            this->missionScore += this->objectiveGoodsScore[goodsIndex];
        }
        this->troopSurvivalScore = 0;
        if (DAT_GameCore::instance.gameMode_2 == 0
            || (DAT_GameCore::instance.gameMode_2 == 2 && DAT_MapPropertiesState::instance.SEC_U3_MapType2_1 < 2)) {
            int troopValue = 0;
            for (int unitID = 1; unitID < 2500; ++unitID) {
                if (DAT_UnitsState::instance.units[unitID].logicalState != 0 && DAT_UnitsState::instance.units[unitID].owner == DAT_GameSynchronyState::instance.currentPlayerSlotID
                    && DAT_UnitsState::instance.units[unitID].isSelectable_OR_matchTime != 0) {
                    troopValue += MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::getValueOfTroopType,
                        DAT_TroopValueState::ptr)((Map::Units::UnitType)DAT_UnitsState::instance.units[unitID].unitType);
                }
            }
            int const losses
                = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                      .weightedLosses;
            int const total = losses + troopValue;
            if (total != 0) {
                int const lossPercent = losses * 100 / total;
                int const survivalScore = (100 - lossPercent) * 100;
                this->missionScore += survivalScore;
                this->troopLossPercent = lossPercent;
                this->troopSurvivalScore = survivalScore;
            }
        }
        if (DAT_GameCore::instance.mapU4Int1 != 0) {
            int enemyValue = 0;
            for (int unitID = 1; unitID < 2500; ++unitID) {
                if (DAT_UnitsState::instance.units[unitID].logicalState != 0 && DAT_UnitsState::instance.units[unitID].owner == 1
                    && DAT_UnitsState::instance.units[unitID].isSelectable_OR_matchTime != 0) {
                    enemyValue += MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::getValueOfTroopType,
                        DAT_TroopValueState::ptr)((Map::Units::UnitType)DAT_UnitsState::instance.units[unitID].unitType);
                }
            }
            this->enemyTroopValueSurviving = enemyValue;
            int const enemyLosses = DAT_GameState::instance.playerDataArray[2].weightedLosses;
            this->enemyTroopValueLost = enemyLosses;
            this->enemyTroopValueTotal = enemyLosses + enemyValue;
        }
    }

}
}
