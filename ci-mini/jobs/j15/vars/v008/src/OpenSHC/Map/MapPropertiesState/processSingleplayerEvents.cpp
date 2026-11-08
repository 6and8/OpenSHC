#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Game/GameCore.func.hpp"
#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Input/MouseState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/LandscapeState.func.hpp"
#include "OpenSHC/Map/MapPropertiesState.func.hpp"
#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Units/TroopValueState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Rendering/Bink/AIMessageQueue.func.hpp"
#include "OpenSHC/Rendering/ViewportRenderState.func.hpp"
#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/DisplayElements.func.hpp"
#include "OpenSHC/UI/Helpers.func.hpp"
#include "OpenSHC/UI/MenuItems/General.func.hpp"
#include "OpenSHC/UI/MenuModalComposition.func.hpp"
#include "OpenSHC/UI/MenuTextInputState.func.hpp"
#include "OpenSHC/UI/MinimapViewState.func.hpp"
#include "OpenSHC/Audio/SFX/SoundEffectID.hpp"
#include "OpenSHC/Game/MissionAestheticsDefinedData.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"
#include "OpenSHC/Map/MapPropertiesState.hpp"
#include "OpenSHC/Map/Units/Instructions/UnitMatchSpeedEnum.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"
#include "OpenSHC/UI/Enums/BuildMenuTabType.hpp"
#include "OpenSHC/UI/Enums/DisplayElementID.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"
#include "OpenSHC/string-literals.hpp"

#include "OpenSHC/Globals/DAT_BinkControlState.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_LandscapeState.hpp"
#include "OpenSHC/Globals/DAT_MapPropertiesState.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition1.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition2.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition3.hpp"
#include "OpenSHC/Globals/DAT_MenuTextInputState.hpp"
#include "OpenSHC/Globals/DAT_MinimapViewState.hpp"
#include "OpenSHC/Globals/DAT_MissionAestheticsDefinedData.hpp"
#include "OpenSHC/Globals/DAT_MouseState.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_VideoBikQueue.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"
#include "OpenSHC/Globals/SEC_RNG.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x004c31a0
    void MapPropertiesState::processSingleplayerEvents()
    {
        int edgeSignpostCount = DAT_GameState::instance.mapAndTime.signpostsMapEdgeDataCounter;
        int signpostIndex = 0;
        int prevWinEventIdx = -1;

        if (DAT_GameSynchronyState::instance.currentGameMode != 0) {
            if (DAT_GameCore::instance.gameMode_2 == 0) {
                MACRO_CALL_MEMBER(MapPropertiesState_Func::updateMilitaryCampaignMissionState, this)();
            }
            return;
        }

        if (DAT_GameCore::instance.gameMode_2 == 1 || DAT_GameCore::instance.gameMode_2 == 6) {
            return;
        }

        if (DAT_GameCore::instance.gameMode_2 == 4) {
            MACRO_CALL(UI::Helpers_Func::UpdateTutorialStepAndProgress)();
        }

        if (DAT_GameCore::instance.section1095 == 1) {
            return;
        }

        if (DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                .playerDeathRelated
            != 0) {
            if (DAT_BinkControlState::instance.binkObjPtrArray[1] == 0
                && DAT_VideoBikQueue::instance.storedMessages_0x924 == 0) {
                DAT_GameState::instance.mapAndTime.unknownCountdown01 -= 1;
            }
            if (DAT_GameState::instance.mapAndTime.unknownCountdown01 == 0) {
                int* storedMessages_0x924Ptr = &DAT_VideoBikQueue::instance.storedMessages_0x924;
                *storedMessages_0x924Ptr = 0;
                MACRO_CALL_MEMBER(UI::MenuModalComposition_Func::activateModalDialog, DAT_MenuModalComposition1::ptr)(
                    UI::Enums::MMT_NONE, FALSE);
                MACRO_CALL_MEMBER(UI::MenuModalComposition_Func::activateModalDialog, DAT_MenuModalComposition2::ptr)(
                    UI::Enums::MMT_NONE, FALSE);
                MACRO_CALL_MEMBER(UI::MenuModalComposition_Func::activateModalDialog, DAT_MenuModalComposition3::ptr)(
                    UI::Enums::MMT_NONE, FALSE);
                DAT_MenuTextInputState::instance.DAT_SomeTextArrayIndex = 9;
                MACRO_CALL_MEMBER(
                    UI::MenuTextInputState_Func::clearAnyOtherModalDialogs, DAT_MenuTextInputState::ptr)();

                if (DAT_GameCore::instance.gameMode_2 == 0) {
                    if (DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                            .playerDeathRelated
                        == 1) {
                        MACRO_CALL_MEMBER(Game::GameCore_Func::incrementMissionProgress, DAT_GameCore::ptr)();
                        DAT_GameCore::instance.section1066 = 2;
                    }
                    if (DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                            .playerDeathRelated
                        == 2) {
                        MACRO_CALL_MEMBER(Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                            UI::Enums::MVT_GAME_LOSTUnk, 0);
                        DAT_GameCore::instance.section1066 = 0;
                    }
                    MACRO_CALL(UI::DisplayElements_Func::CheckDisplayElementByIDAndSetForUnlimitedDisplay)(
                        UI::Enums::DEID_MISSION_WIN_DEFEAT_BANNER, 0);
                } else if (DAT_GameCore::instance.gameMode_2 == 5) {
                    if (DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                            .playerDeathRelated
                        == 1) {
                        MACRO_CALL_MEMBER(Game::GameCore_Func::incrementMission, DAT_GameCore::ptr)();
                    }
                    if (DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                            .playerDeathRelated
                        == 2) {
                        MACRO_CALL_MEMBER(Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                            UI::Enums::MVT_GAME_LOSTUnk, 0);
                    }
                    MACRO_CALL(UI::DisplayElements_Func::CheckDisplayElementByIDAndSetForUnlimitedDisplay)(
                        UI::Enums::DEID_MISSION_WIN_DEFEAT_BANNER, 0);
                } else if (DAT_GameCore::instance.gameMode_2 == 2) {
                    if (DAT_GameCore::instance.field_0x6c != 0) {
                        DAT_MenuTextInputState::instance.DAT_MenuOptionsActionParameter = 7;
                        MACRO_CALL(
                            UI::MenuItems::General_Func::MenuItemActionHandler_General_LaunchOrQuitMultiplayerGameUnk)(
                            22);
                    } else {
                        if (DAT_GameState::instance
                                .playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                .playerDeathRelated
                            == 1) {
                            if (DAT_MapPropertiesState::instance.SEC_U3_MapType2_1 < 2) {
                                MACRO_CALL_MEMBER(Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                                    UI::Enums::MVT_MISSION_FINISHED_TRANSITION, 0);
                            } else {
                                DAT_GameCore::instance.section1095 = 1;
                                DAT_MenuTextInputState::instance.DAT_MenuOptionsActionParameter = 47;
                                MACRO_CALL_MEMBER(UI::MenuTextInputState_Func::activateModalDialogAndClearText,
                                    DAT_MenuTextInputState::ptr)((UI::Enums::MenuModalType)29);
                            }
                        }
                        if (DAT_GameState::instance
                                .playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                .playerDeathRelated
                            == 2) {
                            MACRO_CALL_MEMBER(Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                                UI::Enums::MVT_GAME_LOSTUnk, 0);
                        }
                        DAT_GameCore::instance.section1066 = 2;
                    }
                }
                MACRO_CALL(UI::DisplayElements_Func::CheckDisplayElementByIDAndSetForUnlimitedDisplay)(
                    UI::Enums::DEID_MISSION_WIN_DEFEAT_BANNER, 0);
            }
            return;
        }

        if (this->SEC_Section1081 != 0 && (int)this->SEC_Section1080 > 0) {
            this->SEC_Section1080 -= 1;
        }

        if (DAT_GameState::instance.mapAndTime.startOfDay == 0) {
            return;
        }

        if (DAT_GameCore::instance.unknownAlwaysZero != 0) {
            DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                .playerDeathRelated = 1;
            DAT_GameCore::instance.unknownAlwaysZero = 0;
            DAT_GameState::instance.mapAndTime.unknownCountdown01 = 10;
            return;
        }

        for (int i = 0; i < 32; ++i) {
            if (DAT_GameState::instance.mapAndTime.scenarioEventTimers[i] != 0) {
                DAT_GameState::instance.mapAndTime.scenarioEventTimers[i] += 1;
                if (DAT_GameState::instance.mapAndTime.scenarioEventTimers[i] > 1200) {
                    DAT_GameState::instance.mapAndTime.scenarioEventTimers[i] = 0;
                }
            }
        }

        int playerInvSlot[9];
        for (int i = 0; i < 9; ++i) {
            playerInvSlot[i] = -1;
        }
        int savedInvCount = DAT_TroopValueState::instance.attackInfo.inv_count;
        int playerVideoPlayed[9];
        int spawnedGroups[9];
        for (int i = 0; i < 9; ++i) {
            playerVideoPlayed[i] = 0;
            spawnedGroups[i] = 0;
        }

        if (DAT_GameState::instance.mapAndTime.month == this->SEC_StartingMonth
            && DAT_GameState::instance.mapAndTime.year == this->SEC_StartingYear + 1
            && DAT_GameState::instance.gameTicksLoadBalancer == 1 && DAT_GameState::instance.mapAndTime.week == 0) {
            int hasFireEvent = 0;
            for (int i = 0; i < this->eventsCount; ++i) {
                if (this->scenarioEvents[i].header.tl_type == 3
                    && this->scenarioEvents[i].data.scenario.ScenarioEventType == 30) {
                    hasFireEvent = 1;
                }
            }
            if (hasFireEvent != 0) {
                int hasWaterBuilding = 0;
                for (int i = 0; i < DAT_BuildingsState::instance.maxBuildingsCount; ++i) {
                    if (DAT_BuildingsState::instance.buildings[i].logicalState != 0
                        && DAT_BuildingsState::instance.buildings[i].owner
                            == DAT_GameSynchronyState::instance.currentPlayerSlotID) {
                        if (DAT_BuildingsState::instance.buildings[i].buildingType == Buildings::BT_WELL
                            || DAT_BuildingsState::instance.buildings[i].buildingType == Buildings::BT_WATERPOT) {
                            hasWaterBuilding = 1;
                            break;
                        }
                    }
                }
                if (hasWaterBuilding == 0) {
                    MACRO_CALL_MEMBER(Rendering::Bink::AIMessageQueue_Func::playEventVideoBik, DAT_VideoBikQueue::ptr)(
                        MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                            DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_ACTION, 18),
                        (char*)s_ap_civil12_bik_005aaae8, (char*)s_general_message3_wav_005aa2c0);
                }
            }
        }

        for (int eventIdx = 0; eventIdx < this->eventsCount; ++eventIdx) {
            if (DAT_GameState::instance.mapAndTime.year < this->scenarioEvents[eventIdx].header.year
                || (DAT_GameState::instance.mapAndTime.year == this->scenarioEvents[eventIdx].header.year
                    && DAT_GameState::instance.mapAndTime.month < this->scenarioEvents[eventIdx].header.month)) {
                break;
            }
            if (this->scenarioEvents[eventIdx].header.done != 0) {
                continue;
            }

            switch (this->scenarioEvents[eventIdx].header.tl_type) {
            case 3: {
                if (this->scenarioEvents[eventIdx].data.scenario.ScenarioEventType == 0
                    || this->scenarioEvents[eventIdx].data.scenario.ScenarioEventType == 26) {
                    if (prevWinEventIdx != -1) {
                        this->scenarioEvents[prevWinEventIdx].header.done = 1;
                    }
                    prevWinEventIdx = eventIdx;
                }

                int matchedConditions = 0;
                int enabledConditions = 0;
                for (int condIdx = 0; condIdx < 40; ++condIdx) {
                    if (this->scenarioEvents[eventIdx].data.scenario.conditions[condIdx].enabled != 0) {
                        enabledConditions += 1;
                        this->SEC_EventsExtra[eventIdx].conditionIsTrue[condIdx] = 0;

                        switch (condIdx) {
                        case 0:
                            matchedConditions = enabledConditions;
                            break;
                        case 1: {
                            int reqPop = MACRO_CALL_MEMBER(MapPropertiesState_Func::getDifficultyMultipliedValue, this)(
                                this->scenarioEvents[eventIdx].data.scenario.conditions[1].value);
                            if (DAT_GameState::instance
                                    .playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                    .currentPopulation
                                >= reqPop) {
                                matchedConditions += 1;
                                this->SEC_EventsExtra[eventIdx].conditionIsTrue[condIdx] = 1;
                            } else {
                                this->SEC_EventsExtra[eventIdx].conditionIsTrue[condIdx] = 0;
                            }
                            break;
                        }
                        case 2: {
                            int killer = DAT_GameState::instance
                                             .playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                             .lordKilledByPlayerID;
                            if (killer != 0) {
                                char subType = this->scenarioEvents[eventIdx].data.scenario.conditions[condIdx].subType;
                                if (subType == 0 || killer == 10 || subType + 1 == killer) {
                                    matchedConditions += 1;
                                    this->SEC_EventsExtra[eventIdx].conditionIsTrue[condIdx] = 1;
                                } else {
                                    this->SEC_EventsExtra[eventIdx].conditionIsTrue[condIdx] = 0;
                                }
                            }
                            break;
                        }
                        case 3:
                            if (DAT_GameState::instance
                                    .playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                    .playerRelatedFlag
                                != 0) {
                                matchedConditions += 1;
                                this->SEC_EventsExtra[eventIdx].conditionIsTrue[condIdx] = 1;
                            }
                            break;
                        case 4: {
                            int reqGold = MACRO_CALL_MEMBER(MapPropertiesState_Func::getDifficultyMultipliedValue,
                                this)(this->scenarioEvents[eventIdx].data.scenario.conditions[4].value);
                            if (DAT_GameState::instance
                                    .playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                    .currentResources[15]
                                >= reqGold) {
                                matchedConditions += 1;
                                this->SEC_EventsExtra[eventIdx].conditionIsTrue[condIdx] = 1;
                            } else {
                                this->SEC_EventsExtra[eventIdx].conditionIsTrue[condIdx] = 0;
                            }
                            break;
                        }
                        case 5: {
                            int reqFood = MACRO_CALL_MEMBER(MapPropertiesState_Func::getDifficultyMultipliedValue,
                                this)(this->scenarioEvents[eventIdx].data.scenario.conditions[5].value);
                            char subType = this->scenarioEvents[eventIdx].data.scenario.conditions[condIdx].subType;
                            int curFood;
                            if (subType == 0) {
                                int slot = DAT_GameSynchronyState::instance.currentPlayerSlotID;
                                curFood = DAT_GameState::instance.playerDataArray[slot].currentResources[10]
                                    + DAT_GameState::instance.playerDataArray[slot].currentResources[11]
                                    + DAT_GameState::instance.playerDataArray[slot].currentResources[12]
                                    + DAT_GameState::instance.playerDataArray[slot].currentResources[13];
                            } else {
                                int resIdx = subType;
                                if (resIdx == 8) {
                                    resIdx = 7;
                                }
                                curFood = DAT_GameState::instance
                                              .playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                              .currentResources[resIdx];
                            }
                            if (curFood >= reqFood) {
                                matchedConditions += 1;
                                this->SEC_EventsExtra[eventIdx].conditionIsTrue[condIdx] = 1;
                            } else {
                                this->SEC_EventsExtra[eventIdx].conditionIsTrue[condIdx] = 0;
                            }
                            break;
                        }
                        case 6:
                        case 17: {
                            int reqWeapons = MACRO_CALL_MEMBER(MapPropertiesState_Func::getDifficultyMultipliedValue,
                                this)(this->scenarioEvents[eventIdx].data.scenario.conditions[condIdx].value);
                            char subType = this->scenarioEvents[eventIdx].data.scenario.conditions[condIdx].subType;
                            int curWeapons;
                            if (subType == 0) {
                                int slot = DAT_GameSynchronyState::instance.currentPlayerSlotID;
                                curWeapons = DAT_GameState::instance.playerDataArray[slot].currentResources[17]
                                    + DAT_GameState::instance.playerDataArray[slot].currentResources[18]
                                    + DAT_GameState::instance.playerDataArray[slot].currentResources[19]
                                    + DAT_GameState::instance.playerDataArray[slot].currentResources[20]
                                    + DAT_GameState::instance.playerDataArray[slot].currentResources[21]
                                    + DAT_GameState::instance.playerDataArray[slot].currentResources[22]
                                    + DAT_GameState::instance.playerDataArray[slot].currentResources[23]
                                    + DAT_GameState::instance.playerDataArray[slot].currentResources[24];
                            } else {
                                int resIdx = subType;
                                if (resIdx == 8) {
                                    resIdx = 7;
                                }
                                curWeapons = DAT_GameState::instance
                                                 .playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                                 .currentResources[resIdx];
                            }
                            if (curWeapons >= reqWeapons) {
                                matchedConditions += 1;
                                this->SEC_EventsExtra[eventIdx].conditionIsTrue[condIdx] = 1;
                            } else {
                                this->SEC_EventsExtra[eventIdx].conditionIsTrue[condIdx] = 0;
                            }
                            break;
                        }
                        case 7: {
                            int reqGoods = MACRO_CALL_MEMBER(MapPropertiesState_Func::getDifficultyMultipliedValue,
                                this)(this->scenarioEvents[eventIdx].data.scenario.conditions[7].value);
                            char subType = this->scenarioEvents[eventIdx].data.scenario.conditions[condIdx].subType;
                            int curGoods;
                            if (subType == 0) {
                                int slot = DAT_GameSynchronyState::instance.currentPlayerSlotID;
                                curGoods = DAT_GameState::instance.playerDataArray[slot].currentResources[14]
                                    + DAT_GameState::instance.playerDataArray[slot].currentResources[2]
                                    + DAT_GameState::instance.playerDataArray[slot].currentResources[3]
                                    + DAT_GameState::instance.playerDataArray[slot].currentResources[4]
                                    + DAT_GameState::instance.playerDataArray[slot].currentResources[6]
                                    + DAT_GameState::instance.playerDataArray[slot].currentResources[7]
                                    + DAT_GameState::instance.playerDataArray[slot].currentResources[9];
                            } else {
                                int resIdx = subType;
                                if (resIdx == 8) {
                                    resIdx = 7;
                                }
                                curGoods = DAT_GameState::instance
                                               .playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                               .currentResources[resIdx];
                            }
                            if (curGoods >= reqGoods) {
                                matchedConditions += 1;
                                this->SEC_EventsExtra[eventIdx].conditionIsTrue[condIdx] = 1;
                            } else {
                                this->SEC_EventsExtra[eventIdx].conditionIsTrue[condIdx] = 0;
                            }
                            break;
                        }
                        case 15: {
                            int slot = DAT_GameSynchronyState::instance.currentPlayerSlotID;
                            if (DAT_GameState::instance.playerDataArray[slot].totalEnemyUnitsCount == 0) {
                                matchedConditions += 1;
                                this->SEC_EventsExtra[eventIdx].conditionIsTrue[condIdx] = 1;
                            } else if (DAT_GameCore::instance.gameMode_2 == 2
                                && DAT_MapPropertiesState::instance.SEC_U3_MapType2_1 == 0 && slot == 1
                                && MACRO_CALL_MEMBER(
                                       Units::TroopValueState_Func::isAttackWaveComplete, DAT_TroopValueState::ptr)()
                                    != 0) {
                                matchedConditions += 1;
                                this->SEC_EventsExtra[eventIdx].conditionIsTrue[condIdx] = 1;
                            }
                            break;
                        }
                        case 8: {
                            if (DAT_GameState::instance
                                    .playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                    .totalEnemyUnitsCount
                                == 0) {
                                int evType = this->scenarioEvents[eventIdx].data.scenario.ScenarioEventType;
                                if (evType == 26 || evType == 0 || evType == 23) {
                                    int pendingInvasion = 0;
                                    for (int k = eventIdx + 1; k < this->eventsCount; ++k) {
                                        if (this->scenarioEvents[k].header.tl_type == 1
                                            && this->scenarioEvents[k].data.invasion.repeatMonths == 0
                                            && this->scenarioEvents[k].header.done == 0) {
                                            pendingInvasion = 1;
                                            break;
                                        }
                                    }
                                    if (pendingInvasion == 0) {
                                        matchedConditions += 1;
                                        this->SEC_EventsExtra[eventIdx].conditionIsTrue[condIdx] = 1;
                                    }
                                } else {
                                    matchedConditions += 1;
                                    this->SEC_EventsExtra[eventIdx].conditionIsTrue[condIdx] = 1;
                                }
                            }
                            break;
                        }
                        case 9:
                            if (MACRO_CALL_MEMBER(Game::GameStateStructures_Func::checkKeepEnclosed,
                                    DAT_GameState::ptr)(DAT_GameSynchronyState::instance.currentPlayerSlotID)
                                != 0) {
                                matchedConditions += 1;
                                this->SEC_EventsExtra[eventIdx].conditionIsTrue[condIdx] = 1;
                            }
                            break;
                        case 10: {
                            int wolfCount = 0;
                            for (int u = 1; u < DAT_UnitsState::instance.maxUnitCount; ++u) {
                                if (DAT_UnitsState::instance.units[u].logicalState == 2
                                    && DAT_UnitsState::instance.units[u].unitType == Units::UT_LIONSHWOLF) {
                                    wolfCount += 1;
                                }
                            }
                            if (wolfCount == 0) {
                                matchedConditions += 1;
                                this->SEC_EventsExtra[eventIdx].conditionIsTrue[condIdx] = 1;
                            }
                            break;
                        }
                        case 11:
                            if (DAT_GameState::instance
                                    .playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                    .totalEnemyUnitsCount
                                != 0) {
                                matchedConditions += 1;
                                this->SEC_EventsExtra[eventIdx].conditionIsTrue[condIdx] = 1;
                            }
                            break;
                        case 12: {
                            int troopCount = 0;
                            for (int u = 1; u < DAT_UnitsState::instance.maxUnitCount; ++u) {
                                if (DAT_UnitsState::instance.units[u].logicalState == 2
                                    && DAT_UnitsState::instance.units[u].owner
                                        == DAT_GameSynchronyState::instance.currentPlayerSlotID
                                    && DAT_UnitsState::instance.units[u].isStalked == 0
                                    && DAT_UnitsState::instance.units[u].unknownTestAgainst0_2 == 0) {
                                    ushort ut = DAT_UnitsState::instance.units[u].unitType;
                                    if (ut != Units::UT_E_LADDER
                                        && (ut != Units::UT_E_ENGINEER
                                            || DAT_UnitsState::instance.units[u].resourceToDeposit != 0)
                                        && ut != Units::UT_S_TOWER && ut != Units::UT_S_BATTERINGRAM
                                        && ut != Units::UT_S_SHIELD && ut != Units::UT_S_MANGONEL
                                        && ut != Units::UT_S_BALLISTA && ut != Units::UT_S_CATAPULT
                                        && ut != Units::UT_S_FBALLISTA && ut != Units::UT_S_TREBUCHET) {
                                        troopCount += 1;
                                    }
                                }
                            }
                            if (troopCount == 0) {
                                matchedConditions += 1;
                                this->SEC_EventsExtra[eventIdx].conditionIsTrue[condIdx] = 1;
                            }
                            break;
                        }
                        case 13: {
                            char subType = this->scenarioEvents[eventIdx].data.scenario.conditions[condIdx].subType;
                            if (subType != 0) {
                                if (subType >= 1 && subType <= 4) {
                                    if (DAT_GameState::instance.mapAndTime.hitsDealtToPlayerArray[subType + 1]
                                        >= this->scenarioEvents[eventIdx].data.scenario.conditions[13].value) {
                                        matchedConditions += 1;
                                        DAT_GameState::instance.mapAndTime.hitsDealtToPlayerArray[subType + 1] = 0;
                                        this->SEC_EventsExtra[eventIdx].conditionIsTrue[condIdx] = 1;
                                    }
                                }
                            } else {
                                int totalHits = DAT_GameState::instance.mapAndTime.hitsDealtToPlayerArray[0]
                                    + DAT_GameState::instance.mapAndTime.hitsDealtToPlayerArray[1]
                                    + DAT_GameState::instance.mapAndTime.hitsDealtToPlayerArray[2]
                                    + DAT_GameState::instance.mapAndTime.hitsDealtToPlayerArray[3]
                                    + DAT_GameState::instance.mapAndTime.hitsDealtToPlayerArray[4]
                                    + DAT_GameState::instance.mapAndTime.hitsDealtToPlayerArray[5]
                                    + DAT_GameState::instance.mapAndTime.hitsDealtToPlayerArray[6]
                                    + DAT_GameState::instance.mapAndTime.hitsDealtToPlayerArray[7]
                                    + DAT_GameState::instance.mapAndTime.hitsDealtToPlayerArray[8];
                                if (totalHits >= this->scenarioEvents[eventIdx].data.scenario.conditions[13].value) {
                                    DAT_GameState::instance.mapAndTime.hitsDealtToPlayerArray[0] = 0;
                                    DAT_GameState::instance.mapAndTime.hitsDealtToPlayerArray[1] = 0;
                                    DAT_GameState::instance.mapAndTime.hitsDealtToPlayerArray[2] = 0;
                                    DAT_GameState::instance.mapAndTime.hitsDealtToPlayerArray[3] = 0;
                                    DAT_GameState::instance.mapAndTime.hitsDealtToPlayerArray[4] = 0;
                                    DAT_GameState::instance.mapAndTime.hitsDealtToPlayerArray[5] = 0;
                                    DAT_GameState::instance.mapAndTime.hitsDealtToPlayerArray[6] = 0;
                                    DAT_GameState::instance.mapAndTime.hitsDealtToPlayerArray[7] = 0;
                                    DAT_GameState::instance.mapAndTime.hitsDealtToPlayerArray[8] = 0;
                                    matchedConditions += 1;
                                    this->SEC_EventsExtra[eventIdx].conditionIsTrue[13] = 1;
                                }
                            }
                            break;
                        }
                        case 14: {
                            char subType = this->scenarioEvents[eventIdx].data.scenario.conditions[condIdx].subType;
                            if (subType != 0) {
                                if (subType >= 1 && subType <= 4) {
                                    if (DAT_GameState::instance.mapAndTime.emenyHitArray[subType + 1]
                                        >= this->scenarioEvents[eventIdx].data.scenario.conditions[14].value) {
                                        matchedConditions += 1;
                                        DAT_GameState::instance.mapAndTime.emenyHitArray[subType + 1] = 0;
                                        this->SEC_EventsExtra[eventIdx].conditionIsTrue[condIdx] = 1;
                                    }
                                }
                            } else {
                                int totalHits = DAT_GameState::instance.mapAndTime.emenyHitArray[0]
                                    + DAT_GameState::instance.mapAndTime.emenyHitArray[1]
                                    + DAT_GameState::instance.mapAndTime.emenyHitArray[2]
                                    + DAT_GameState::instance.mapAndTime.emenyHitArray[3]
                                    + DAT_GameState::instance.mapAndTime.emenyHitArray[4]
                                    + DAT_GameState::instance.mapAndTime.emenyHitArray[5]
                                    + DAT_GameState::instance.mapAndTime.emenyHitArray[6]
                                    + DAT_GameState::instance.mapAndTime.emenyHitArray[7]
                                    + DAT_GameState::instance.mapAndTime.emenyHitArray[8];
                                if (totalHits >= this->scenarioEvents[eventIdx].data.scenario.conditions[14].value) {
                                    DAT_GameState::instance.mapAndTime.emenyHitArray[0] = 0;
                                    DAT_GameState::instance.mapAndTime.emenyHitArray[1] = 0;
                                    DAT_GameState::instance.mapAndTime.emenyHitArray[2] = 0;
                                    DAT_GameState::instance.mapAndTime.emenyHitArray[3] = 0;
                                    DAT_GameState::instance.mapAndTime.emenyHitArray[4] = 0;
                                    DAT_GameState::instance.mapAndTime.emenyHitArray[5] = 0;
                                    DAT_GameState::instance.mapAndTime.emenyHitArray[6] = 0;
                                    DAT_GameState::instance.mapAndTime.emenyHitArray[7] = 0;
                                    DAT_GameState::instance.mapAndTime.emenyHitArray[8] = 0;
                                    matchedConditions += 1;
                                    this->SEC_EventsExtra[eventIdx].conditionIsTrue[14] = 1;
                                }
                            }
                            break;
                        }
                        case 20:
                            if (DAT_GameState::instance
                                    .playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                    .previousBlessedPeoplePercentage
                                >= this->scenarioEvents[eventIdx].data.scenario.conditions[20].value) {
                                matchedConditions += 1;
                                this->SEC_EventsExtra[eventIdx].conditionIsTrue[condIdx] = 1;
                            }
                            break;
                        case 22:
                            if (DAT_GameState::instance
                                    .playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                    .fearFactorLevel
                                <= -this->scenarioEvents[eventIdx].data.scenario.conditions[22].value) {
                                matchedConditions += 1;
                                this->SEC_EventsExtra[eventIdx].conditionIsTrue[condIdx] = 1;
                            }
                            break;
                        case 23:
                            if (DAT_GameState::instance
                                    .playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                    .fearFactorLevel
                                >= this->scenarioEvents[eventIdx].data.scenario.conditions[23].value) {
                                matchedConditions += 1;
                                this->SEC_EventsExtra[eventIdx].conditionIsTrue[condIdx] = 1;
                            } else {
                                this->SEC_EventsExtra[eventIdx].conditionIsTrue[condIdx] = 0;
                            }
                            break;
                        case 21: {
                            int aleCov = MACRO_CALL_MEMBER(Game::GameStateStructures_Func::computeAleCoverage,
                                DAT_GameState::ptr)(DAT_GameSynchronyState::instance.currentPlayerSlotID);
                            if (aleCov >= this->scenarioEvents[eventIdx].data.scenario.conditions[21].value) {
                                matchedConditions += 1;
                                this->SEC_EventsExtra[eventIdx].conditionIsTrue[condIdx] = 1;
                            } else {
                                this->SEC_EventsExtra[eventIdx].conditionIsTrue[condIdx] = 0;
                            }
                            break;
                        }
                        case 39:
                            if (matchedConditions == enabledConditions - 1) {
                                MACRO_CALL(UI::DisplayElements_Func::CheckDisplayElementByIDAndSetForUnlimitedDisplay)(
                                    UI::Enums::DEID_TIME_UNTIL_VICTORY, 1);
                                if (this->SEC_Section1081 == 0) {
                                    int ticks = this->scenarioEvents[eventIdx].data.scenario.conditions[39].value * 800;
                                    this->SEC_Section1080 = ticks;
                                    this->SEC_Section1090 = ticks;
                                }
                                this->SEC_Section1081 = 1;
                                if ((int)this->SEC_Section1080 <= 0) {
                                    matchedConditions += 1;
                                    this->SEC_EventsExtra[eventIdx].conditionIsTrue[condIdx] = 1;
                                }
                            } else {
                                if (this->SEC_Section1081 != 0) {
                                    MACRO_CALL(
                                        UI::DisplayElements_Func::CheckDisplayElementByIDAndSetForUnlimitedDisplay)(
                                        UI::Enums::DEID_TIME_UNTIL_VICTORY, 0);
                                }
                                this->SEC_Section1081 = 0;
                            }
                            break;
                        case 16:
                            if (DAT_GameState::instance.mapAndTime.cathedralRelated1 == 1) {
                                matchedConditions += 1;
                                this->SEC_EventsExtra[eventIdx].conditionIsTrue[condIdx] = 1;
                            }
                            break;
                        case 18:
                            if (DAT_GameCore::instance.gameMode_2 != 2) {
                                int dairyCount = 0;
                                for (int b = 1; b < DAT_BuildingsState::instance.maxBuildingsCount; ++b) {
                                    if (DAT_BuildingsState::instance.buildings[b].logicalState != 0
                                        && DAT_BuildingsState::instance.buildings[b].buildingType
                                            == Buildings::BT_DAIRYFARM
                                        && DAT_BuildingsState::instance.buildings[b].currentlyNeededEmployeeCount
                                            == 0) {
                                        dairyCount += 1;
                                    }
                                }
                                if (dairyCount >= 4) {
                                    matchedConditions += 1;
                                    this->SEC_EventsExtra[eventIdx].conditionIsTrue[condIdx] = 1;
                                } else {
                                    this->SEC_EventsExtra[eventIdx].conditionIsTrue[condIdx] = 0;
                                }
                            }
                            break;
                        case 19:
                            if (DAT_GameCore::instance.gameMode_2 != 2) {
                                int innCount = 0;
                                for (int b = 1; b < DAT_BuildingsState::instance.maxBuildingsCount; ++b) {
                                    if (DAT_BuildingsState::instance.buildings[b].logicalState != 0
                                        && DAT_BuildingsState::instance.buildings[b].buildingType == Buildings::BT_INN
                                        && DAT_BuildingsState::instance.buildings[b].currentlyNeededEmployeeCount == 0
                                        && DAT_BuildingsState::instance.buildings[b].flagonsOfAleOrCheeseOrReleaseDogs
                                            > 0) {
                                        innCount += 1;
                                    }
                                }
                                if (innCount >= 2) {
                                    matchedConditions += 1;
                                    this->SEC_EventsExtra[eventIdx].conditionIsTrue[condIdx] = 1;
                                } else {
                                    this->SEC_EventsExtra[eventIdx].conditionIsTrue[condIdx] = 0;
                                }
                            }
                            break;
                        }
                    }
                }

                if ((*(short*)&this->scenarioEvents[eventIdx].data.scenario.allOrAnyCondition != 0
                        || matchedConditions == 0)
                    && matchedConditions < enabledConditions) {
                    continue;
                }

                this->scenarioEvents[eventIdx].header.done = 1;
                DAT_GameState::instance.mapAndTime
                    .scenarioEventTimers[this->scenarioEvents[eventIdx].data.scenario.ScenarioEventType] = 1;

                switch (this->scenarioEvents[eventIdx].data.scenario.ScenarioEventType) {
                case 26: {
                    if (DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                            .playerDeathRelated
                        == 0) {
                        int hasLaterWinEvent = 0;
                        for (int k = eventIdx + 1; k < this->eventsCount; ++k) {
                            if (this->scenarioEvents[k].header.tl_type == 3
                                && (this->scenarioEvents[k].data.scenario.ScenarioEventType == 0
                                    || this->scenarioEvents[k].data.scenario.ScenarioEventType == 26)) {
                                if (DAT_GameState::instance.mapAndTime.year < this->scenarioEvents[k].header.year
                                    || (DAT_GameState::instance.mapAndTime.year == this->scenarioEvents[k].header.year
                                        && DAT_GameState::instance.mapAndTime.month
                                            < this->scenarioEvents[k].header.month)) {
                                    break;
                                }
                                hasLaterWinEvent = 1;
                                break;
                            }
                        }
                        if (hasLaterWinEvent == 0) {
                            this->scenarioEvents[eventIdx].header.done = 0;
                            this->scenarioEvents[eventIdx].data.scenario.ScenarioEventType = 0;
                            this->scenarioEvents[eventIdx].header.year = DAT_GameState::instance.mapAndTime.year;
                            this->scenarioEvents[eventIdx].header.month = DAT_GameState::instance.mapAndTime.month + 1;
                            if (this->scenarioEvents[eventIdx].header.month >= 12) {
                                this->scenarioEvents[eventIdx].header.year += 1;
                                this->scenarioEvents[eventIdx].header.month -= 12;
                            }
                        }
                    }
                    break;
                }
                case 0: {
                    if (DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                            .playerDeathRelated
                        == 0) {
                        int hasLaterWinEvent = 0;
                        for (int k = eventIdx + 1; k < this->eventsCount; ++k) {
                            if (this->scenarioEvents[k].header.tl_type == 3
                                && (this->scenarioEvents[k].data.scenario.ScenarioEventType == 0
                                    || this->scenarioEvents[k].data.scenario.ScenarioEventType == 26)) {
                                if (DAT_GameState::instance.mapAndTime.year < this->scenarioEvents[k].header.year
                                    || (DAT_GameState::instance.mapAndTime.year == this->scenarioEvents[k].header.year
                                        && DAT_GameState::instance.mapAndTime.month
                                            < this->scenarioEvents[k].header.month)) {
                                    break;
                                }
                                hasLaterWinEvent = 1;
                                break;
                            }
                        }
                        if (hasLaterWinEvent == 0
                            && (DAT_GameCore::instance.gameMode_2 == 0 || DAT_GameCore::instance.gameMode_2 == 5
                                || DAT_GameCore::instance.gameMode_2 == 2)) {
                            DAT_GameState::instance
                                .playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                .playerDeathRelated = 1;
                            DAT_GameState::instance.mapAndTime.unknownCountdown01 = 240;
                            MACRO_CALL(UI::DisplayElements_Func::CheckDisplayElementByIDAndSetForUnlimitedDisplay)(
                                UI::Enums::DEID_MISSION_WIN_DEFEAT_BANNER, 1);
                            if (DAT_GameCore::instance.buildmenuMenuTabToSwitchTo.buildMenuTab == 61
                                || DAT_GameCore::instance.buildmenuMenuTabToSwitchTo.buildMenuTab == 62) {
                                DAT_GameCore::instance.buildmenuMenuTabToSwitchTo.buildMenuTab
                                    = DAT_GameCore::instance.tabTypeSiegeSubset;
                                MACRO_CALL_MEMBER(Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                                    UI::Enums::MVT_BUILD_MENU, 0);
                            }
                            DAT_TileMapState::instance.currentMapperCommand = (Commands::MappersEnum)0;
                            if (DAT_UnitsState::instance.totalUnitsInSelection > 0) {
                                MACRO_CALL_MEMBER(
                                    Units::UnitsState_Func::deselectAllUnitsOneByOne, DAT_UnitsState::ptr)();
                                MACRO_CALL_MEMBER(Units::UnitsState_Func::queueEscapeCommand, DAT_UnitsState::ptr)();
                                MACRO_CALL_MEMBER(Input::MouseState_Func::resetMouseCursorState, DAT_MouseState::ptr)();
                            }
                            this->field133_0x145d8 = 0;
                            if (this->scenarioEvents[eventIdx].data.scenario.conditions[1].enabled != 0) {
                                this->field133_0x145d8 = 1;
                            } else if (this->scenarioEvents[eventIdx].data.scenario.conditions[4].enabled != 0) {
                                this->field133_0x145d8 = 2;
                            } else if (this->scenarioEvents[eventIdx].data.scenario.conditions[5].enabled == 0
                                && this->scenarioEvents[eventIdx].data.scenario.conditions[6].enabled == 0
                                && this->scenarioEvents[eventIdx].data.scenario.conditions[7].enabled == 0
                                && this->scenarioEvents[eventIdx].data.scenario.conditions[17].enabled == 0) {
                                this->field133_0x145d8 = 1;
                            } else {
                                this->field133_0x145d8 = 3;
                            }
                        }
                    }
                    break;
                }
                case 27: {
                    if (DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                            .playerDeathRelated
                        == 0) {
                        this->scenarioEvents[eventIdx].header.done = 0;
                        this->scenarioEvents[eventIdx].data.scenario.ScenarioEventType = 1;
                        this->scenarioEvents[eventIdx].header.year = DAT_GameState::instance.mapAndTime.year;
                        this->scenarioEvents[eventIdx].header.month = DAT_GameState::instance.mapAndTime.month + 1;
                        if (this->scenarioEvents[eventIdx].header.month >= 12) {
                            this->scenarioEvents[eventIdx].header.year += 1;
                            this->scenarioEvents[eventIdx].header.month -= 12;
                        }
                    }
                    break;
                }
                case 1: {
                    if (DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                            .playerDeathRelated
                        == 0) {
                        if (DAT_GameCore::instance.gameMode_2 == 0 || DAT_GameCore::instance.gameMode_2 == 5
                            || DAT_GameCore::instance.gameMode_2 == 2) {
                            DAT_GameState::instance
                                .playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                .playerDeathRelated = 2;
                            MACRO_CALL_MEMBER(
                                Units::UnitsState_Func::setAIControlStatusTo100000, DAT_UnitsState::ptr)();
                            DAT_GameState::instance.mapAndTime.unknownCountdown01 = 240;
                            if (DAT_GameCore::instance.gameMode_2 == 2
                                && DAT_MapPropertiesState::instance.SEC_U3_MapType2_1 == 0) {
                                DAT_GameState::instance.mapAndTime.unknownCountdown01 = 640;
                            }
                            MACRO_CALL(UI::DisplayElements_Func::CheckDisplayElementByIDAndSetForUnlimitedDisplay)(
                                UI::Enums::DEID_MISSION_WIN_DEFEAT_BANNER, 2);
                            if (DAT_GameCore::instance.buildmenuMenuTabToSwitchTo.buildMenuTab == 61
                                || DAT_GameCore::instance.buildmenuMenuTabToSwitchTo.buildMenuTab == 62) {
                                DAT_GameCore::instance.buildmenuMenuTabToSwitchTo.buildMenuTab
                                    = DAT_GameCore::instance.tabTypeSiegeSubset;
                                MACRO_CALL_MEMBER(Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                                    UI::Enums::MVT_BUILD_MENU, 0);
                            }
                            DAT_TileMapState::instance.currentMapperCommand = (Commands::MappersEnum)0;
                            if (DAT_UnitsState::instance.totalUnitsInSelection > 0) {
                                MACRO_CALL_MEMBER(
                                    Units::UnitsState_Func::deselectAllUnitsOneByOne, DAT_UnitsState::ptr)();
                                MACRO_CALL_MEMBER(Units::UnitsState_Func::queueEscapeCommand, DAT_UnitsState::ptr)();
                                MACRO_CALL_MEMBER(Input::MouseState_Func::resetMouseCursorState, DAT_MouseState::ptr)();
                            }
                        }
                    }
                    break;
                }
                case 3:
                    MACRO_CALL_MEMBER(Units::TribesState_Func::flagTribesOfType, DAT_TribesState::ptr)(14);
                    break;
                case 4: {
                    int count = this->scenarioEvents[eventIdx].data.scenario.actionData;
                    if (count == 0) {
                        count = 1;
                    }
                    MACRO_CALL_MEMBER(Units::TribesState_Func::consumeFlaggedTribesOfType, DAT_TribesState::ptr)(
                        14, count);
                    break;
                }
                case 5: {
                    int slot1 = DAT_GameSynchronyState::instance.currentPlayerSlotID;
                    MACRO_CALL_MEMBER(Units::UnitsState_Func::spawnUnit, DAT_UnitsState::ptr)(slot1,
                        SEC_RNG::instance.currentNumber2 % 9,
                        DAT_GameState::instance.playerDataArray[slot1].buildingEntryInfos[8].xEntry * 8,
                        DAT_GameState::instance.playerDataArray[slot1].buildingEntryInfos[8].yEntry * 8,
                        DAT_TileMapState::instance.HeightLayer
                            [DAT_GameState::instance.playerDataArray[slot1].buildingEntryInfos[8].tileEntry],
                        Units::UT_JUGGLER);

                    int slot2 = DAT_GameSynchronyState::instance.currentPlayerSlotID;
                    MACRO_CALL_MEMBER(Units::UnitsState_Func::spawnUnit, DAT_UnitsState::ptr)(slot2,
                        ((int)SEC_RNG::instance.currentNumber2 >> 3) % 9,
                        DAT_GameState::instance.playerDataArray[slot2].buildingEntryInfos[8].xEntry * 8,
                        DAT_GameState::instance.playerDataArray[slot2].buildingEntryInfos[8].yEntry * 8,
                        DAT_TileMapState::instance.HeightLayer
                            [DAT_GameState::instance.playerDataArray[slot2].buildingEntryInfos[8].tileEntry],
                        Units::UT_JUGGLER);

                    int slot3 = DAT_GameSynchronyState::instance.currentPlayerSlotID;
                    MACRO_CALL_MEMBER(Units::UnitsState_Func::spawnUnit, DAT_UnitsState::ptr)(slot3,
                        ((int)SEC_RNG::instance.currentNumber2 >> 6) % 9,
                        DAT_GameState::instance.playerDataArray[slot3].buildingEntryInfos[8].xEntry * 8,
                        DAT_GameState::instance.playerDataArray[slot3].buildingEntryInfos[8].yEntry * 8,
                        DAT_TileMapState::instance.HeightLayer
                            [DAT_GameState::instance.playerDataArray[slot3].buildingEntryInfos[8].tileEntry],
                        Units::UT_JUGGLER);

                    int slot4 = DAT_GameSynchronyState::instance.currentPlayerSlotID;
                    MACRO_CALL_MEMBER(Units::UnitsState_Func::spawnUnit, DAT_UnitsState::ptr)(slot4,
                        ((int)SEC_RNG::instance.currentNumber2 >> 9) % 9,
                        DAT_GameState::instance.playerDataArray[slot4].buildingEntryInfos[8].xEntry * 8,
                        DAT_GameState::instance.playerDataArray[slot4].buildingEntryInfos[8].yEntry * 8,
                        DAT_TileMapState::instance.HeightLayer
                            [DAT_GameState::instance.playerDataArray[slot4].buildingEntryInfos[8].tileEntry],
                        Units::UT_FIREEATER);

                    int slot5 = DAT_GameSynchronyState::instance.currentPlayerSlotID;
                    MACRO_CALL_MEMBER(Units::UnitsState_Func::spawnUnit, DAT_UnitsState::ptr)(slot5,
                        ((int)SEC_RNG::instance.currentNumber2 >> 12) % 9,
                        DAT_GameState::instance.playerDataArray[slot5].buildingEntryInfos[8].xEntry * 8,
                        DAT_GameState::instance.playerDataArray[slot5].buildingEntryInfos[8].yEntry * 8,
                        DAT_TileMapState::instance.HeightLayer
                            [DAT_GameState::instance.playerDataArray[slot5].buildingEntryInfos[8].tileEntry],
                        Units::UT_FIREEATER);

                    MACRO_CALL_MEMBER(Rendering::Bink::AIMessageQueue_Func::playEventVideoBik, DAT_VideoBikQueue::ptr)(
                        MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                            DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_ACTION, 1),
                        DAT_MissionAestheticsDefinedData::instance.RandomEvent1VideoName,
                        (char*)s_Random_Events1_wav_005aa8ec);

                    if (this->scenarioEvents[eventIdx].data.scenario.repeat != 0
                        && this->scenarioEvents[eventIdx].data.scenario.repeatMonths != 1) {
                        if (this->scenarioEvents[eventIdx].data.scenario.repeatMonths != 10) {
                            this->scenarioEvents[eventIdx].data.scenario.repeatMonths -= 1;
                        }
                        int delay = this->scenarioEvents[eventIdx].data.scenario.repeat;
                        this->scenarioEvents[eventIdx].header.done = 0;
                        if (delay >= 4) {
                            delay += SEC_RNG::instance.currentNumber2 % (delay / 4);
                        }
                        this->scenarioEvents[eventIdx].header.year
                            = DAT_GameState::instance.mapAndTime.year + delay / 12;
                        this->scenarioEvents[eventIdx].header.month
                            = DAT_GameState::instance.mapAndTime.month + delay % 12;
                        if (this->scenarioEvents[eventIdx].header.month >= 12) {
                            this->scenarioEvents[eventIdx].header.month -= 12;
                            this->scenarioEvents[eventIdx].header.year += 1;
                        }
                        eventIdx -= 1;
                    }
                    break;
                }
                case 6:
                    DAT_GameCore::instance.isTimeHalted = 1;
                    break;
                case 7:
                    DAT_GameCore::instance.isTimeHalted = 0;
                    break;
                case 8: {
                    MACRO_CALL_MEMBER(Game::GameStateStructures_Func::switchPlayerOwnership, DAT_GameState::ptr)(
                        DAT_GameSynchronyState::instance.currentPlayerSlotID);
                    MACRO_CALL_MEMBER(Buildings::BuildingsState_Func::setupBarracksCampgroundPositions,
                        DAT_BuildingsState::ptr)(DAT_GameSynchronyState::instance.currentPlayerSlotID);
                    MACRO_CALL_MEMBER(Buildings::BuildingsState_Func::setupMercenaryPostCampgroundPositions,
                        DAT_BuildingsState::ptr)(DAT_GameSynchronyState::instance.currentPlayerSlotID);
                    MACRO_CALL_MEMBER(Units::UnitsState_Func::triggerStoneTowerDeathForPlayer, DAT_UnitsState::ptr)(
                        DAT_GameSynchronyState::instance.currentPlayerSlotID);
                    MACRO_CALL_MEMBER(Buildings::BuildingsState_Func::countPlayerResources, DAT_BuildingsState::ptr)(
                        DAT_GameSynchronyState::instance.currentPlayerSlotID);

                    DAT_GameCore::instance.buildmenuMenuTabToSwitchTo.buildMenuTab
                        = (UI::Enums::BuildMenuTabTypeShort)10;
                    DAT_GameCore::instance.secondaryActiveMenuTabToSwitchTo.buildMenuTab
                        = (UI::Enums::BuildMenuTabTypeShort)10;
                    DAT_GameCore::instance.tabTypeSiegeSubset = (UI::Enums::BuildMenuTabTypeShort)10;
                    if (DAT_GameCore::instance.currentMenuViewType == UI::Enums::MVT_BUILD_MENU) {
                        if (DAT_GameCore::instance.activeMenuTab.buildMenuTab == 48) {
                            MACRO_CALL_MEMBER(Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                                UI::Enums::MVT_BUILD_MENU, 0);
                        }
                        if (DAT_GameCore::instance.currentMenuViewType == UI::Enums::MVT_BUILD_MENU
                            && (DAT_GameCore::instance.activeMenuTab.buildMenuTab == 61
                                || DAT_GameCore::instance.activeMenuTab.buildMenuTab == 62)) {
                            DAT_GameCore::instance.buildmenuMenuTabToSwitchTo.buildMenuTab
                                = (UI::Enums::BuildMenuTabTypeShort)61;
                            MACRO_CALL_MEMBER(Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                                UI::Enums::MVT_BUILD_MENU, 0);
                        }
                    }
                    int slot = DAT_GameSynchronyState::instance.currentPlayerSlotID;
                    int lordId = DAT_GameState::instance.playerDataArray[slot].lordID;
                    if (lordId != 0
                        && DAT_GameState::instance.playerDataArray[slot].lordUID
                            != DAT_UnitsState::instance.units[lordId].uid) {
                        DAT_GameState::instance.playerDataArray[slot].lordID = 0;
                        DAT_GameState::instance.playerDataArray[slot].lordUID = 0;
                    }
                    break;
                }
                case 9:
                    DAT_GameCore::instance.xbowProducible_logic = 1;
                    break;
                case 11: {
                    int slot = DAT_GameSynchronyState::instance.currentPlayerSlotID;
                    DAT_GameState::instance.playerDataArray[slot].eventPlagueCountdown = 24;
                    if (DAT_GameState::instance.playerDataArray[slot].popularity > 6000) {
                        DAT_GameState::instance.playerDataArray[slot].popularity
                            = (DAT_GameState::instance.playerDataArray[slot].popularity - 6000) / 2 + 6000;
                    }
                    MACRO_CALL_MEMBER(Game::GameStateStructures_Func::spawnPoisonCloudsAtRandomStorageOrArmyBuilding,
                        DAT_GameState::ptr)(slot, this->scenarioEvents[eventIdx].data.scenario.actionData);
                    MACRO_CALL_MEMBER(Rendering::Bink::AIMessageQueue_Func::playEventVideoBik, DAT_VideoBikQueue::ptr)(
                        MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                            DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_ACTION, 2),
                        DAT_MissionAestheticsDefinedData::instance.RandomEvent2VideoName,
                        (char*)s_Random_Events2_wav_005aa888);

                    if (this->scenarioEvents[eventIdx].data.scenario.repeat != 0
                        && this->scenarioEvents[eventIdx].data.scenario.repeatMonths != 1) {
                        if (this->scenarioEvents[eventIdx].data.scenario.repeatMonths != 10) {
                            this->scenarioEvents[eventIdx].data.scenario.repeatMonths -= 1;
                        }
                        int delay = this->scenarioEvents[eventIdx].data.scenario.repeat;
                        this->scenarioEvents[eventIdx].header.done = 0;
                        if (delay >= 4) {
                            delay += SEC_RNG::instance.currentNumber2 % (delay / 4);
                        }
                        this->scenarioEvents[eventIdx].header.year
                            = DAT_GameState::instance.mapAndTime.year + delay / 12;
                        this->scenarioEvents[eventIdx].header.month
                            = DAT_GameState::instance.mapAndTime.month + delay % 12;
                        if (this->scenarioEvents[eventIdx].header.month >= 12) {
                            this->scenarioEvents[eventIdx].header.month -= 12;
                            this->scenarioEvents[eventIdx].header.year += 1;
                        }
                        eventIdx -= 1;
                    }
                    break;
                }
                case 12: {
                    if (MACRO_CALL_MEMBER(
                            Buildings::BuildingsState_Func::findBuildingOfTypeForPlayer, DAT_BuildingsState::ptr)(
                            DAT_GameSynchronyState::instance.currentPlayerSlotID, Buildings::BT_WHEATFARM)
                        != 0) {
                        MACRO_CALL_MEMBER(Buildings::BuildingsState_Func::harmWheatFarmsOfPlayer,
                            DAT_BuildingsState::ptr)(DAT_GameSynchronyState::instance.currentPlayerSlotID);
                        MACRO_CALL_MEMBER(
                            Rendering::Bink::AIMessageQueue_Func::playEventVideoBik, DAT_VideoBikQueue::ptr)(
                            MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                                DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_ACTION, 3),
                            DAT_MissionAestheticsDefinedData::instance.RandomEvent3VideoName,
                            (char*)s_Random_Events3_wav_005aaad4);
                    }
                    if (this->scenarioEvents[eventIdx].data.scenario.repeat != 0
                        && this->scenarioEvents[eventIdx].data.scenario.repeatMonths != 1) {
                        if (this->scenarioEvents[eventIdx].data.scenario.repeatMonths != 10) {
                            this->scenarioEvents[eventIdx].data.scenario.repeatMonths -= 1;
                        }
                        int delay = this->scenarioEvents[eventIdx].data.scenario.repeat;
                        this->scenarioEvents[eventIdx].header.done = 0;
                        if (delay >= 4) {
                            delay += SEC_RNG::instance.currentNumber2 % (delay / 4);
                        }
                        this->scenarioEvents[eventIdx].header.year
                            = DAT_GameState::instance.mapAndTime.year + delay / 12;
                        this->scenarioEvents[eventIdx].header.month
                            = DAT_GameState::instance.mapAndTime.month + delay % 12;
                        if (this->scenarioEvents[eventIdx].header.month >= 12) {
                            this->scenarioEvents[eventIdx].header.month -= 12;
                            this->scenarioEvents[eventIdx].header.year += 1;
                        }
                        eventIdx -= 1;
                    }
                    break;
                }
                case 13: {
                    if (MACRO_CALL_MEMBER(
                            Buildings::BuildingsState_Func::findBuildingOfTypeForPlayer, DAT_BuildingsState::ptr)(
                            DAT_GameSynchronyState::instance.currentPlayerSlotID, Buildings::BT_HOPFARM)
                        != 0) {
                        MACRO_CALL_MEMBER(Buildings::BuildingsState_Func::harmHopFarmsOfPlayer,
                            DAT_BuildingsState::ptr)(DAT_GameSynchronyState::instance.currentPlayerSlotID);
                        MACRO_CALL_MEMBER(
                            Rendering::Bink::AIMessageQueue_Func::playEventVideoBik, DAT_VideoBikQueue::ptr)(
                            MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                                DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_ACTION, 4),
                            DAT_MissionAestheticsDefinedData::instance.RandomEvent4VideoName,
                            (char*)s_Random_Events4_wav_005aaac0);
                    }
                    if (this->scenarioEvents[eventIdx].data.scenario.repeat != 0
                        && this->scenarioEvents[eventIdx].data.scenario.repeatMonths != 1) {
                        if (this->scenarioEvents[eventIdx].data.scenario.repeatMonths != 10) {
                            this->scenarioEvents[eventIdx].data.scenario.repeatMonths -= 1;
                        }
                        int delay = this->scenarioEvents[eventIdx].data.scenario.repeat;
                        this->scenarioEvents[eventIdx].header.done = 0;
                        if (delay >= 4) {
                            delay += SEC_RNG::instance.currentNumber2 % (delay / 4);
                        }
                        this->scenarioEvents[eventIdx].header.year
                            = DAT_GameState::instance.mapAndTime.year + delay / 12;
                        this->scenarioEvents[eventIdx].header.month
                            = DAT_GameState::instance.mapAndTime.month + delay % 12;
                        if (this->scenarioEvents[eventIdx].header.month >= 12) {
                            this->scenarioEvents[eventIdx].header.month -= 12;
                            this->scenarioEvents[eventIdx].header.year += 1;
                        }
                        eventIdx -= 1;
                    }
                    break;
                }
                case 14: {
                    if (MACRO_CALL_MEMBER(
                            Buildings::BuildingsState_Func::findBuildingOfTypeForPlayer, DAT_BuildingsState::ptr)(
                            DAT_GameSynchronyState::instance.currentPlayerSlotID, Buildings::BT_APPLEFARM)
                        != 0) {
                        MACRO_CALL_MEMBER(Buildings::BuildingsState_Func::harmAppleFarmTreesOfPlayer,
                            DAT_BuildingsState::ptr)(DAT_GameSynchronyState::instance.currentPlayerSlotID);
                        MACRO_CALL_MEMBER(
                            Rendering::Bink::AIMessageQueue_Func::playEventVideoBik, DAT_VideoBikQueue::ptr)(
                            MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                                DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_ACTION, 5),
                            (char*)s__005a5339, (char*)s_Random_Events5_wav_005aaaac);
                        MACRO_CALL_MEMBER(Rendering::Bink::AIMessageQueue_Func::playEventVideoBik,
                            DAT_VideoBikQueue::ptr)((char*)s__005a5339,
                            DAT_MissionAestheticsDefinedData::instance.RandomEvent5VideoName, (char*)s__005a5339);
                    }
                    if (this->scenarioEvents[eventIdx].data.scenario.repeat != 0
                        && this->scenarioEvents[eventIdx].data.scenario.repeatMonths != 1) {
                        if (this->scenarioEvents[eventIdx].data.scenario.repeatMonths != 10) {
                            this->scenarioEvents[eventIdx].data.scenario.repeatMonths -= 1;
                        }
                        int delay = this->scenarioEvents[eventIdx].data.scenario.repeat;
                        this->scenarioEvents[eventIdx].header.done = 0;
                        if (delay >= 4) {
                            delay += SEC_RNG::instance.currentNumber2 % (delay / 4);
                        }
                        this->scenarioEvents[eventIdx].header.year
                            = DAT_GameState::instance.mapAndTime.year + delay / 12;
                        this->scenarioEvents[eventIdx].header.month
                            = DAT_GameState::instance.mapAndTime.month + delay % 12;
                        if (this->scenarioEvents[eventIdx].header.month >= 12) {
                            this->scenarioEvents[eventIdx].header.month -= 12;
                            this->scenarioEvents[eventIdx].header.year += 1;
                        }
                        eventIdx -= 1;
                    }
                    break;
                }
                case 15: {
                    MACRO_CALL_MEMBER(LandscapeState_Func::killEveryFifthTree, DAT_LandscapeState::ptr)();
                    MACRO_CALL_MEMBER(Rendering::Bink::AIMessageQueue_Func::playEventVideoBik, DAT_VideoBikQueue::ptr)(
                        MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                            DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_ACTION, 6),
                        DAT_MissionAestheticsDefinedData::instance.RandomEvent6VideoName,
                        (char*)s_Random_Events6_wav_005aa8c4);

                    if (this->scenarioEvents[eventIdx].data.scenario.repeat != 0
                        && this->scenarioEvents[eventIdx].data.scenario.repeatMonths != 1) {
                        if (this->scenarioEvents[eventIdx].data.scenario.repeatMonths != 10) {
                            this->scenarioEvents[eventIdx].data.scenario.repeatMonths -= 1;
                        }
                        int delay = this->scenarioEvents[eventIdx].data.scenario.repeat;
                        this->scenarioEvents[eventIdx].header.done = 0;
                        if (delay >= 4) {
                            delay += SEC_RNG::instance.currentNumber2 % (delay / 4);
                        }
                        this->scenarioEvents[eventIdx].header.year
                            = DAT_GameState::instance.mapAndTime.year + delay / 12;
                        this->scenarioEvents[eventIdx].header.month
                            = DAT_GameState::instance.mapAndTime.month + delay % 12;
                        if (this->scenarioEvents[eventIdx].header.month >= 12) {
                            this->scenarioEvents[eventIdx].header.month -= 12;
                            this->scenarioEvents[eventIdx].header.year += 1;
                        }
                        eventIdx -= 1;
                    }
                    break;
                }
                case 16: {
                    if (MACRO_CALL_MEMBER(
                            Units::TribesState_Func::hasAvailableSpawnSlotForWildlifeOrMercs, DAT_TribesState::ptr)()
                            != 0
                        && (MACRO_CALL_MEMBER(
                                Buildings::BuildingsState_Func::findBuildingOfTypeForPlayer, DAT_BuildingsState::ptr)(
                                DAT_GameSynchronyState::instance.currentPlayerSlotID, Buildings::BT_HOPFARM)
                                != 0
                            || MACRO_CALL_MEMBER(Buildings::BuildingsState_Func::findBuildingOfTypeForPlayer,
                                   DAT_BuildingsState::ptr)(
                                   DAT_GameSynchronyState::instance.currentPlayerSlotID, Buildings::BT_WHEATFARM)
                                != 0)) {
                        DAT_GameState::instance.mapAndTime.eventCountdownRabbitInfestation = 1200;
                        MACRO_CALL_MEMBER(
                            Units::TribesState_Func::spawnRabbitAtFirstFreeSpawnPoint, DAT_TribesState::ptr)();
                        MACRO_CALL_MEMBER(UI::MinimapViewState_Func::setSpawnMoment, DAT_MinimapViewState::ptr)(
                            DAT_TribesState::instance.unknownX_01, DAT_TribesState::instance.unknownY_01);
                        MACRO_CALL_MEMBER(
                            Rendering::Bink::AIMessageQueue_Func::playEventVideoBik, DAT_VideoBikQueue::ptr)(
                            MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                                DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_ACTION, 7),
                            DAT_MissionAestheticsDefinedData::instance.RandomEvent7VideoName,
                            (char*)s_Random_Events7_wav_005aa8d8);
                    }
                    if (this->scenarioEvents[eventIdx].data.scenario.repeat != 0
                        && this->scenarioEvents[eventIdx].data.scenario.repeatMonths != 1) {
                        if (this->scenarioEvents[eventIdx].data.scenario.repeatMonths != 10) {
                            this->scenarioEvents[eventIdx].data.scenario.repeatMonths -= 1;
                        }
                        int delay = this->scenarioEvents[eventIdx].data.scenario.repeat;
                        this->scenarioEvents[eventIdx].header.done = 0;
                        if (delay >= 4) {
                            delay += SEC_RNG::instance.currentNumber2 % (delay / 4);
                        }
                        this->scenarioEvents[eventIdx].header.year
                            = DAT_GameState::instance.mapAndTime.year + delay / 12;
                        this->scenarioEvents[eventIdx].header.month
                            = DAT_GameState::instance.mapAndTime.month + delay % 12;
                        if (this->scenarioEvents[eventIdx].header.month >= 12) {
                            this->scenarioEvents[eventIdx].header.month -= 12;
                            this->scenarioEvents[eventIdx].header.year += 1;
                        }
                        eventIdx -= 1;
                    }
                    break;
                }
                case 17: {
                    uint spawnX;
                    uint spawnY;
                    if (MACRO_CALL_MEMBER(Units::TribesState_Func::findRecentOrSignpostSpawnLocation,
                            DAT_TribesState::ptr)(&spawnX, &spawnY)
                            != 0
                        && MACRO_CALL_MEMBER(Rendering::ViewportRenderState_Func::xyAreValid,
                               DAT_ViewportRenderState::ptr)(spawnX, spawnY)
                            != 0) {
                        int slot = DAT_GameSynchronyState::instance.currentPlayerSlotID;
                        DAT_GameState::instance.playerDataArray[slot].eventLionsCountdown = 12;
                        if (DAT_GameState::instance.playerDataArray[slot].popularity > 6000) {
                            DAT_GameState::instance.playerDataArray[slot].popularity
                                = (DAT_GameState::instance.playerDataArray[slot].popularity - 6000) / 2 + 6000;
                        }
                        for (int n = 0; n < this->scenarioEvents[eventIdx].data.scenario.actionData; ++n) {
                            MACRO_CALL_MEMBER(Units::TribesState_Func::findRecentOrSignpostSpawnLocation,
                                DAT_TribesState::ptr)(&spawnX, &spawnY);
                            int tribeId = MACRO_CALL_MEMBER(Units::TribesState_Func::createAnimal,
                                DAT_TribesState::ptr)((Commands::MappersEnum)221, spawnX, spawnY,
                                DAT_TileMapState::instance
                                    .HeightLayer[DAT_ViewportRenderState::instance.translationMatrix[spawnY].addXgetTile
                                        + spawnX]);
                            MACRO_CALL_MEMBER(UI::MinimapViewState_Func::setSpawnMoment, DAT_MinimapViewState::ptr)(
                                spawnX, spawnY);
                            DAT_TribesState::instance.tribes[tribeId].unknownBool02 = 0;
                            DAT_TribesState::instance.tribes[tribeId].unknownBool01 = 1;
                        }
                        MACRO_CALL_MEMBER(
                            Rendering::Bink::AIMessageQueue_Func::playEventVideoBik, DAT_VideoBikQueue::ptr)(
                            MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                                DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_ACTION, 8),
                            (char*)s__005a5339, (char*)s__005a5339);
                    }
                    if (this->scenarioEvents[eventIdx].data.scenario.repeat != 0
                        && this->scenarioEvents[eventIdx].data.scenario.repeatMonths != 1) {
                        if (this->scenarioEvents[eventIdx].data.scenario.repeatMonths != 10) {
                            this->scenarioEvents[eventIdx].data.scenario.repeatMonths -= 1;
                        }
                        int delay = this->scenarioEvents[eventIdx].data.scenario.repeat;
                        this->scenarioEvents[eventIdx].header.done = 0;
                        if (delay >= 4) {
                            delay += SEC_RNG::instance.currentNumber2 % (delay / 4);
                        }
                        this->scenarioEvents[eventIdx].header.year
                            = DAT_GameState::instance.mapAndTime.year + delay / 12;
                        this->scenarioEvents[eventIdx].header.month
                            = DAT_GameState::instance.mapAndTime.month + delay % 12;
                        if (this->scenarioEvents[eventIdx].header.month >= 12) {
                            this->scenarioEvents[eventIdx].header.month -= 12;
                            this->scenarioEvents[eventIdx].header.year += 1;
                        }
                        eventIdx -= 1;
                    }
                    break;
                }
                case 18: {
                    if (MACRO_CALL_MEMBER(Game::GameStateStructures_Func::hasAnySignpost, DAT_GameState::ptr)() != 0) {
                        DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                            .eventBanditsCountdown = 16;
                        DAT_TroopValueState::instance.attackInfo.inv_count += 1;
                        if (DAT_TroopValueState::instance.attackInfo.inv_count >= 50) {
                            DAT_TroopValueState::instance.attackInfo.inv_count = 1;
                        }
                        MACRO_CALL_MEMBER(Units::TroopValueState_Func::initializeAttackWaveSlot,
                            DAT_TroopValueState::ptr)(DAT_TroopValueState::instance.attackInfo.inv_count, 0);
                        DAT_TroopValueState::instance.attackInfo
                            .attackWavePlayerIDArray[DAT_TroopValueState::instance.attackInfo.inv_count] = 8;

                        int spIdx = MACRO_CALL_MEMBER(
                            Game::GameStateStructures_Func::pickRandomAccessibleSignpostEntry, DAT_GameState::ptr)();
                        int tribeId = MACRO_CALL_MEMBER(Units::TribesState_Func::createTribeWithSpawnedUnit,
                            DAT_TribesState::ptr)(0, 16, DAT_GameState::instance.mapAndTime.signpostEntryData[spIdx].x,
                            DAT_GameState::instance.mapAndTime.signpostEntryData[spIdx].y, 8, Units::UT_E_MACE,
                            this->scenarioEvents[eventIdx].data.scenario.actionData + 1);
                        MACRO_CALL_MEMBER(UI::MinimapViewState_Func::setSpawnMoment, DAT_MinimapViewState::ptr)(
                            DAT_GameState::instance.mapAndTime.signpostEntryData[spIdx].x,
                            DAT_GameState::instance.mapAndTime.signpostEntryData[spIdx].y);

                        for (int u = 0; u < DAT_TribesState::instance.tribes[tribeId].size; ++u) {
                            int unitId = MACRO_CALL_MEMBER(
                                Units::TribesState_Func::getUnitIDForIndexInTribe, DAT_TribesState::ptr)(tribeId, u);
                            DAT_UnitsState::instance.units[unitId].calculatedOwnerPlayerIndex = 5;
                            DAT_UnitsState::instance.units[unitId].logicalState = 2;
                        }

                        MACRO_CALL_MEMBER(
                            Rendering::Bink::AIMessageQueue_Func::playEventVideoBik, DAT_VideoBikQueue::ptr)(
                            MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                                DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_ACTION, 9),
                            DAT_MissionAestheticsDefinedData::instance.RandomEvent9VideoName,
                            (char*)s_Random_Events9_wav_005aa860);
                    }
                    if (this->scenarioEvents[eventIdx].data.scenario.repeat != 0
                        && this->scenarioEvents[eventIdx].data.scenario.repeatMonths != 1) {
                        if (this->scenarioEvents[eventIdx].data.scenario.repeatMonths != 10) {
                            this->scenarioEvents[eventIdx].data.scenario.repeatMonths -= 1;
                        }
                        int delay = this->scenarioEvents[eventIdx].data.scenario.repeat;
                        this->scenarioEvents[eventIdx].header.done = 0;
                        if (delay >= 4) {
                            delay += SEC_RNG::instance.currentNumber2 % (delay / 4);
                        }
                        this->scenarioEvents[eventIdx].header.year
                            = DAT_GameState::instance.mapAndTime.year + delay / 12;
                        this->scenarioEvents[eventIdx].header.month
                            = DAT_GameState::instance.mapAndTime.month + delay % 12;
                        if (this->scenarioEvents[eventIdx].header.month >= 12) {
                            this->scenarioEvents[eventIdx].header.month -= 12;
                            this->scenarioEvents[eventIdx].header.year += 1;
                        }
                        eventIdx -= 1;
                    }
                    break;
                }
                case 19: {
                    if (MACRO_CALL_MEMBER(
                            Buildings::BuildingsState_Func::findBuildingOfTypeForPlayer, DAT_BuildingsState::ptr)(
                            DAT_GameSynchronyState::instance.currentPlayerSlotID, Buildings::BT_DAIRYFARM)
                        != 0) {
                        MACRO_CALL_MEMBER(Units::UnitsState_Func::setRandomNumberOnCows, DAT_UnitsState::ptr)(
                            DAT_GameSynchronyState::instance.currentPlayerSlotID);
                        MACRO_CALL_MEMBER(Buildings::BuildingsState_Func::setDairyFarmCheeseCounter,
                            DAT_BuildingsState::ptr)(DAT_GameSynchronyState::instance.currentPlayerSlotID);
                        MACRO_CALL_MEMBER(
                            Rendering::Bink::AIMessageQueue_Func::playEventVideoBik, DAT_VideoBikQueue::ptr)(
                            MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                                DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_ACTION, 10),
                            (char*)s__005a5339, (char*)s_Random_Events10_wav_005aaa98);
                        MACRO_CALL_MEMBER(Rendering::Bink::AIMessageQueue_Func::playEventVideoBik,
                            DAT_VideoBikQueue::ptr)((char*)s__005a5339,
                            DAT_MissionAestheticsDefinedData::instance.RandomEvent10VideoName, (char*)s__005a5339);
                    }
                    if (this->scenarioEvents[eventIdx].data.scenario.repeat != 0
                        && this->scenarioEvents[eventIdx].data.scenario.repeatMonths != 1) {
                        if (this->scenarioEvents[eventIdx].data.scenario.repeatMonths != 10) {
                            this->scenarioEvents[eventIdx].data.scenario.repeatMonths -= 1;
                        }
                        int delay = this->scenarioEvents[eventIdx].data.scenario.repeat;
                        this->scenarioEvents[eventIdx].header.done = 0;
                        if (delay >= 4) {
                            delay += SEC_RNG::instance.currentNumber2 % (delay / 4);
                        }
                        this->scenarioEvents[eventIdx].header.year
                            = DAT_GameState::instance.mapAndTime.year + delay / 12;
                        this->scenarioEvents[eventIdx].header.month
                            = DAT_GameState::instance.mapAndTime.month + delay % 12;
                        if (this->scenarioEvents[eventIdx].header.month >= 12) {
                            this->scenarioEvents[eventIdx].header.month -= 12;
                            this->scenarioEvents[eventIdx].header.year += 1;
                        }
                        eventIdx -= 1;
                    }
                    break;
                }
                case 20: {
                    if (MACRO_CALL_MEMBER(Game::GameStateStructures_Func::hasAnySignpost, DAT_GameState::ptr)() != 0) {
                        int spIdx = MACRO_CALL_MEMBER(
                            Game::GameStateStructures_Func::pickRandomAccessibleSignpostEntry, DAT_GameState::ptr)();
                        int tribe1 = MACRO_CALL_MEMBER(Units::TribesState_Func::createTribeWithSpawnedUnit,
                            DAT_TribesState::ptr)(0, 4, DAT_GameState::instance.mapAndTime.signpostEntryData[spIdx].x,
                            DAT_GameState::instance.mapAndTime.signpostEntryData[spIdx].y,
                            DAT_GameSynchronyState::instance.currentPlayerSlotID, Units::UT_E_ARCHER,
                            this->scenarioEvents[eventIdx].data.scenario.actionData);
                        int tribe2 = MACRO_CALL_MEMBER(Units::TribesState_Func::createTribeWithSpawnedUnit,
                            DAT_TribesState::ptr)(0, 14, DAT_GameState::instance.mapAndTime.signpostEntryData[spIdx].x,
                            DAT_GameState::instance.mapAndTime.signpostEntryData[spIdx].y,
                            DAT_GameSynchronyState::instance.currentPlayerSlotID, Units::UT_E_MONK, 1);
                        MACRO_CALL_MEMBER(UI::MinimapViewState_Func::setSpawnMoment, DAT_MinimapViewState::ptr)(
                            DAT_GameState::instance.mapAndTime.signpostEntryData[spIdx].x,
                            DAT_GameState::instance.mapAndTime.signpostEntryData[spIdx].y);

                        DAT_TribesState::instance.tribes[tribe1].pendingScatterMove = 0;
                        DAT_TribesState::instance.tribes[tribe2].pendingScatterMove = 0;

                        for (int u = 0; u < DAT_TribesState::instance.tribes[tribe1].size; ++u) {
                            int unitId = MACRO_CALL_MEMBER(
                                Units::TribesState_Func::getUnitIDForIndexInTribe, DAT_TribesState::ptr)(tribe1, u);
                            DAT_UnitsState::instance.units[unitId].calculatedOwnerPlayerIndex = 8;
                            DAT_UnitsState::instance.units[unitId].logicalState = 2;
                        }
                        for (int u = 0; u < DAT_TribesState::instance.tribes[tribe2].size; ++u) {
                            int unitId = MACRO_CALL_MEMBER(
                                Units::TribesState_Func::getUnitIDForIndexInTribe, DAT_TribesState::ptr)(tribe2, u);
                            DAT_UnitsState::instance.units[unitId].calculatedOwnerPlayerIndex = 8;
                            DAT_UnitsState::instance.units[unitId].logicalState = 2;
                        }

                        int keepBldId = DAT_GameState::instance
                                            .playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                            .buildingEntryInfos[0]
                                            .id;
                        if (keepBldId > 0) {
                            ushort bt = DAT_BuildingsState::instance.buildings[keepBldId].buildingType;
                            int targetX = 0;
                            int targetY = 0;
                            if (bt == Buildings::BT_MANORHOUSE) {
                                targetX = DAT_BuildingsState::instance.buildings[keepBldId].x + 3;
                                targetY = DAT_BuildingsState::instance.buildings[keepBldId].y + 8;
                            } else if (bt == Buildings::BT_STONEKEEP) {
                                targetX = DAT_BuildingsState::instance.buildings[keepBldId].x + 3;
                                targetY = DAT_BuildingsState::instance.buildings[keepBldId].y + 3;
                            } else if (bt == Buildings::BT_STRONGHOLD) {
                                targetX = DAT_BuildingsState::instance.buildings[keepBldId].x + 3;
                                targetY = DAT_BuildingsState::instance.buildings[keepBldId].y + 3;
                            } else if (bt == Buildings::BT_KEEPFOUR) {
                                targetX = DAT_BuildingsState::instance.buildings[keepBldId].x + 4;
                                targetY = DAT_BuildingsState::instance.buildings[keepBldId].y + 4;
                            } else if (bt == Buildings::BT_KEEPFIVE) {
                                targetX = DAT_BuildingsState::instance.buildings[keepBldId].x + 5;
                                targetY = DAT_BuildingsState::instance.buildings[keepBldId].y + 5;
                            }
                            MACRO_CALL_MEMBER(Units::TribesState_Func::giveTribeMoveInstruction, DAT_TribesState::ptr)(
                                tribe1, targetX, targetY, 0, 0, Units::Instructions::UMSE_0);
                            MACRO_CALL_MEMBER(Units::TribesState_Func::giveTribeMoveInstruction, DAT_TribesState::ptr)(
                                tribe2, targetX, targetY, 0, 0, Units::Instructions::UMSE_0);
                        }

                        MACRO_CALL_MEMBER(
                            Rendering::Bink::AIMessageQueue_Func::playEventVideoBik, DAT_VideoBikQueue::ptr)(
                            MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                                DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_ACTION, 11),
                            DAT_MissionAestheticsDefinedData::instance.RandomEvent11VideoName,
                            (char*)s_Random_Events11_wav_005aa84c);
                    }
                    if (this->scenarioEvents[eventIdx].data.scenario.repeat != 0
                        && this->scenarioEvents[eventIdx].data.scenario.repeatMonths != 1) {
                        if (this->scenarioEvents[eventIdx].data.scenario.repeatMonths != 10) {
                            this->scenarioEvents[eventIdx].data.scenario.repeatMonths -= 1;
                        }
                        int delay = this->scenarioEvents[eventIdx].data.scenario.repeat;
                        this->scenarioEvents[eventIdx].header.done = 0;
                        if (delay >= 4) {
                            delay += SEC_RNG::instance.currentNumber2 % (delay / 4);
                        }
                        this->scenarioEvents[eventIdx].header.year
                            = DAT_GameState::instance.mapAndTime.year + delay / 12;
                        this->scenarioEvents[eventIdx].header.month
                            = DAT_GameState::instance.mapAndTime.month + delay % 12;
                        if (this->scenarioEvents[eventIdx].header.month >= 12) {
                            this->scenarioEvents[eventIdx].header.month -= 12;
                            this->scenarioEvents[eventIdx].header.year += 1;
                        }
                        eventIdx -= 1;
                    }
                    break;
                }
                case 21: {
                    int slot = DAT_GameSynchronyState::instance.currentPlayerSlotID;
                    DAT_GameState::instance.mapAndTime.unitLadyRelated = 1;
                    DAT_GameState::instance.playerDataArray[slot].eventMarriageCountdown = 12;
                    if (DAT_GameState::instance.playerDataArray[slot].popularity > 10000) {
                        DAT_GameState::instance.playerDataArray[slot].popularity = 10000;
                    }
                    MACRO_CALL_MEMBER(Rendering::Bink::AIMessageQueue_Func::playEventVideoBik, DAT_VideoBikQueue::ptr)(
                        MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                            DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_ACTION, 12),
                        DAT_MissionAestheticsDefinedData::instance.RandomEvent12VideoName,
                        (char*)s_Random_Events12_wav_005aa8b0);
                    MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::setUpSFXToPlayUnk, DAT_SFXState::ptr)(
                        (Audio::SFX::SoundEffectID)207);
                    break;
                }
                case 22: {
                    int slot = DAT_GameSynchronyState::instance.currentPlayerSlotID;
                    DAT_GameState::instance.mapAndTime.unitJesterRelated = 1;
                    DAT_GameState::instance.playerDataArray[slot].eventJesterCountdown = 48;
                    if (DAT_GameState::instance.playerDataArray[slot].popularity > 10000) {
                        DAT_GameState::instance.playerDataArray[slot].popularity = 10000;
                    }
                    MACRO_CALL_MEMBER(Rendering::Bink::AIMessageQueue_Func::playEventVideoBik, DAT_VideoBikQueue::ptr)(
                        MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                            DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_ACTION, 13),
                        DAT_MissionAestheticsDefinedData::instance.RandomEvent13VideoName,
                        (char*)s_Random_Events13_wav_005aa89c);
                    break;
                }
                case 29: {
                    int slot = DAT_GameSynchronyState::instance.currentPlayerSlotID;
                    if (DAT_GameState::instance.playerDataArray[slot].totalFood != 0) {
                        MACRO_CALL_MEMBER(Buildings::BuildingsState_Func::applyFoodLossPercentageToPlayer,
                            DAT_BuildingsState::ptr)(slot, this->scenarioEvents[eventIdx].data.scenario.actionData);
                        if (this->scenarioEvents[eventIdx].data.scenario.actionData == 100) {
                            MACRO_CALL_MEMBER(
                                Rendering::Bink::AIMessageQueue_Func::playEventVideoBik, DAT_VideoBikQueue::ptr)(
                                MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                                    DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_ACTION, 16),
                                DAT_MissionAestheticsDefinedData::instance.RandomEvent14VideoName,
                                (char*)s_general_message3_wav_005aa2c0);
                        } else {
                            MACRO_CALL_MEMBER(
                                Rendering::Bink::AIMessageQueue_Func::playEventVideoBik, DAT_VideoBikQueue::ptr)(
                                MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                                    DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_ACTION, 14),
                                DAT_MissionAestheticsDefinedData::instance.RandomEvent14VideoName,
                                (char*)s_general_message3_wav_005aa2c0);
                        }
                    }
                    if (this->scenarioEvents[eventIdx].data.scenario.repeat != 0
                        && this->scenarioEvents[eventIdx].data.scenario.repeatMonths != 1) {
                        if (this->scenarioEvents[eventIdx].data.scenario.repeatMonths != 10) {
                            this->scenarioEvents[eventIdx].data.scenario.repeatMonths -= 1;
                        }
                        int delay = this->scenarioEvents[eventIdx].data.scenario.repeat;
                        this->scenarioEvents[eventIdx].header.done = 0;
                        if (delay >= 4) {
                            delay += SEC_RNG::instance.currentNumber2 % (delay / 4);
                        }
                        this->scenarioEvents[eventIdx].header.year
                            = DAT_GameState::instance.mapAndTime.year + delay / 12;
                        this->scenarioEvents[eventIdx].header.month
                            = DAT_GameState::instance.mapAndTime.month + delay % 12;
                        if (this->scenarioEvents[eventIdx].header.month >= 12) {
                            this->scenarioEvents[eventIdx].header.month -= 12;
                            this->scenarioEvents[eventIdx].header.year += 1;
                        }
                        eventIdx -= 1;
                    }
                    break;
                }
                case 30: {
                    int slot = DAT_GameSynchronyState::instance.currentPlayerSlotID;
                    DAT_GameState::instance.playerDataArray[slot].eventFireCountdown = 8;
                    MACRO_CALL_MEMBER(Buildings::BuildingsState_Func::spreadFireRandomlyToBuildings,
                        DAT_BuildingsState::ptr)(slot, this->scenarioEvents[eventIdx].data.scenario.actionData);
                    if (MACRO_CALL_MEMBER(
                            Buildings::BuildingsState_Func::findFirstBuildingOfType, DAT_BuildingsState::ptr)(
                            DAT_GameSynchronyState::instance.currentPlayerSlotID, Buildings::BT_WELL)
                        != 0) {
                        MACRO_CALL_MEMBER(
                            Rendering::Bink::AIMessageQueue_Func::playEventVideoBik, DAT_VideoBikQueue::ptr)(
                            MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                                DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_ACTION, 15),
                            DAT_MissionAestheticsDefinedData::instance.RandomEvent15VideoName,
                            (char*)s_general_warning16_wav_005aaa80);
                    } else if (MACRO_CALL_MEMBER(
                                   Buildings::BuildingsState_Func::findFirstBuildingOfType, DAT_BuildingsState::ptr)(
                                   DAT_GameSynchronyState::instance.currentPlayerSlotID, Buildings::BT_WATERPOT)
                        != 0) {
                        MACRO_CALL_MEMBER(
                            Rendering::Bink::AIMessageQueue_Func::playEventVideoBik, DAT_VideoBikQueue::ptr)(
                            MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                                DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_ACTION, 15),
                            DAT_MissionAestheticsDefinedData::instance.RandomEvent15VideoName,
                            (char*)s_general_warning16_wav_005aaa80);
                    } else {
                        MACRO_CALL_MEMBER(
                            Rendering::Bink::AIMessageQueue_Func::playEventVideoBik, DAT_VideoBikQueue::ptr)(
                            MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                                DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_ACTION, 17),
                            DAT_MissionAestheticsDefinedData::instance.RandomEvent15VideoName,
                            (char*)s_general_warning16_wav_005aaa80);
                    }

                    if (this->scenarioEvents[eventIdx].data.scenario.repeat != 0
                        && this->scenarioEvents[eventIdx].data.scenario.repeatMonths != 1) {
                        if (this->scenarioEvents[eventIdx].data.scenario.repeatMonths != 10) {
                            this->scenarioEvents[eventIdx].data.scenario.repeatMonths -= 1;
                        }
                        int delay = this->scenarioEvents[eventIdx].data.scenario.repeat;
                        this->scenarioEvents[eventIdx].header.done = 0;
                        if (delay >= 4) {
                            delay += SEC_RNG::instance.currentNumber2 % (delay / 4);
                        }
                        this->scenarioEvents[eventIdx].header.year
                            = DAT_GameState::instance.mapAndTime.year + delay / 12;
                        this->scenarioEvents[eventIdx].header.month
                            = DAT_GameState::instance.mapAndTime.month + delay % 12;
                        if (this->scenarioEvents[eventIdx].header.month >= 12) {
                            this->scenarioEvents[eventIdx].header.month -= 12;
                            this->scenarioEvents[eventIdx].header.year += 1;
                        }
                        eventIdx -= 1;
                    }
                    break;
                }
                case 23: {
                    if (DAT_GameCore::instance.gameMode_2 != 0 && this->scenarioEvents[eventIdx].header.year == 1085
                        && this->scenarioEvents[eventIdx].header.month == 11) {
                        int tribeId = MACRO_CALL_MEMBER(
                            Units::TribesState_Func::createTribeWithSpawnedUnit, DAT_TribesState::ptr)(0, 4, 133, 278,
                            DAT_GameSynchronyState::instance.currentPlayerSlotID, Units::UT_E_ARCHER, 20);
                        DAT_TribesState::instance.tribes[tribeId].pendingScatterMove = 3;
                        for (int u = 0; u < DAT_TribesState::instance.tribes[tribeId].size; ++u) {
                            int unitId = MACRO_CALL_MEMBER(
                                Units::TribesState_Func::getUnitIDForIndexInTribe, DAT_TribesState::ptr)(tribeId, u);
                            DAT_UnitsState::instance.units[unitId].calculatedOwnerPlayerIndex = 6;
                        }
                    }
                    break;
                }
                case 25:
                    DAT_GameCore::instance.section1076 = 1;
                    break;
                case 24:
                    DAT_GameCore::instance.section1076 = 0;
                    break;
                case 28:
                    for (int k = 0; k < this->eventsCount; ++k) {
                        if (this->scenarioEvents[k].header.tl_type == 1
                            && this->scenarioEvents[k].data.invasion.repeatMonths != 0) {
                            this->scenarioEvents[k].data.invasion.repeatMonths = 0;
                            this->scenarioEvents[k].header.done = 1;
                            this->scenarioEvents[k].header.month = 1181;
                        }
                    }
                    break;
                }

                MACRO_CALL_MEMBER(MapPropertiesState_Func::sortEventsByDate, this)();
                break;
            }
            case 2:
                this->scenarioEvents[eventIdx].header.done = 1;
                break;
            case 1: {
                DAT_GameState::instance.mapAndTime.field3171_0x27a8 = 0;
                DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                    .aiControlStatusRelated = -200;

                int invFaction = this->scenarioEvents[eventIdx].data.invasion.crusaderArabian;
                if (playerInvSlot[invFaction] == -1) {
                    DAT_TroopValueState::instance.attackInfo.inv_count += 1;
                    if (DAT_TroopValueState::instance.attackInfo.inv_count >= 50) {
                        DAT_TroopValueState::instance.attackInfo.inv_count = 1;
                    }
                    MACRO_CALL_MEMBER(Units::TroopValueState_Func::initializeAttackWaveSlot, DAT_TroopValueState::ptr)(
                        DAT_TroopValueState::instance.attackInfo.inv_count,
                        this->scenarioEvents[eventIdx].data.invasion.messageMonth);
                    playerInvSlot[this->scenarioEvents[eventIdx].data.invasion.crusaderArabian]
                        = DAT_TroopValueState::instance.attackInfo.inv_count;
                    savedInvCount = DAT_TroopValueState::instance.attackInfo.inv_count;
                } else {
                    DAT_TroopValueState::instance.attackInfo.inv_count = playerInvSlot[invFaction];
                }

                DAT_TroopValueState::instance.attackInfo
                    .attackWavePlayerIDArray[DAT_TroopValueState::instance.attackInfo.inv_count]
                    = (byte)(this->scenarioEvents[eventIdx].data.invasion.crusaderArabian + 2);

                for (int slot = 0; slot < 25; ++slot) {
                    int remaining = this->scenarioEvents[eventIdx].data.invasion.unitCountsPerUnitType[slot];
                    if (remaining != 0) {
                        int spawnType = 0;
                        int unitType = 0;
                        int groupSizeDivisor = 0;
                        switch (slot) {
                        case 0:
                            spawnType = 3;
                            unitType = 22;
                            groupSizeDivisor = 10;
                            break;
                        case 1:
                            spawnType = 7;
                            unitType = 23;
                            groupSizeDivisor = 10;
                            break;
                        case 2:
                            spawnType = 5;
                            unitType = 24;
                            groupSizeDivisor = 10;
                            break;
                        case 3:
                            spawnType = 6;
                            unitType = 25;
                            groupSizeDivisor = 10;
                            break;
                        case 4:
                            spawnType = 9;
                            unitType = 26;
                            groupSizeDivisor = 10;
                            break;
                        case 5:
                            spawnType = 8;
                            unitType = 27;
                            groupSizeDivisor = 10;
                            break;
                        case 6:
                            spawnType = 10;
                            unitType = 28;
                            groupSizeDivisor = 10;
                            break;
                        case 7:
                            spawnType = 4;
                            unitType = 29;
                            groupSizeDivisor = 10;
                            break;
                        case 8:
                            spawnType = 11;
                            unitType = 30;
                            groupSizeDivisor = 10;
                            break;
                        case 9:
                            spawnType = 22;
                            unitType = 39;
                            groupSizeDivisor = 10;
                            break;
                        case 10:
                            spawnType = 23;
                            unitType = 40;
                            groupSizeDivisor = 10;
                            break;
                        case 11:
                            spawnType = 19;
                            unitType = 59;
                            groupSizeDivisor = 10;
                            break;
                        case 12:
                            spawnType = 20;
                            unitType = 58;
                            groupSizeDivisor = 10;
                            break;
                        case 13:
                            spawnType = 21;
                            unitType = 60;
                            groupSizeDivisor = 10;
                            break;
                        case 14:
                            spawnType = 12;
                            unitType = 37;
                            groupSizeDivisor = 10;
                            break;
                        case 15:
                            spawnType = 2;
                            unitType = 5;
                            groupSizeDivisor = 10;
                            break;
                        case 16:
                            spawnType = 25;
                            unitType = 70;
                            groupSizeDivisor = 10;
                            break;
                        case 17:
                            spawnType = 26;
                            unitType = 71;
                            groupSizeDivisor = 20;
                            break;
                        case 18:
                            spawnType = 27;
                            unitType = 72;
                            groupSizeDivisor = 20;
                            break;
                        case 19:
                            spawnType = 28;
                            unitType = 73;
                            groupSizeDivisor = 2;
                            break;
                        case 20:
                            spawnType = 29;
                            unitType = 74;
                            groupSizeDivisor = 10;
                            break;
                        case 21:
                            spawnType = 30;
                            unitType = 75;
                            groupSizeDivisor = 8;
                            break;
                        case 22:
                            spawnType = 31;
                            unitType = 76;
                            groupSizeDivisor = 4;
                            break;
                        case 23:
                            spawnType = 24;
                            unitType = 77;
                            groupSizeDivisor = 10;
                            break;
                        }

                        int diffMult = 100;
                        switch (DAT_GameState::instance.mapAndTime.difficulty) {
                        case 0:
                            diffMult = 50;
                            break;
                        case 2:
                            diffMult = 140;
                            break;
                        case 3:
                            diffMult = 200;
                            break;
                        }
                        remaining = (remaining * diffMult) / 100;

                        if (spawnType == 22) {
                            DAT_TroopValueState::instance.attackInfo
                                .someSinglePlayerScore[DAT_TroopValueState::instance.attackInfo.inv_count][0]
                                += (byte)remaining;
                        } else if (spawnType == 23) {
                            DAT_TroopValueState::instance.attackInfo
                                .someSinglePlayerScore[DAT_TroopValueState::instance.attackInfo.inv_count][1]
                                += (byte)remaining;
                        } else if (spawnType == 19) {
                            DAT_TroopValueState::instance.attackInfo
                                .someSinglePlayerScore[DAT_TroopValueState::instance.attackInfo.inv_count][2]
                                += (byte)remaining;
                        } else if (spawnType == 20) {
                            DAT_TroopValueState::instance.attackInfo
                                .someSinglePlayerScore[DAT_TroopValueState::instance.attackInfo.inv_count][3]
                                += (byte)remaining;
                        } else if (spawnType == 21) {
                            DAT_TroopValueState::instance.attackInfo
                                .someSinglePlayerScore[DAT_TroopValueState::instance.attackInfo.inv_count][4]
                                += (byte)remaining;
                        } else if (spawnType == 24) {
                            DAT_TroopValueState::instance.attackInfo
                                .someSinglePlayerScore[DAT_TroopValueState::instance.attackInfo.inv_count][8]
                                += (byte)remaining;
                        } else {
                            int batchSize = remaining / (remaining / groupSizeDivisor + 1);
                            while (remaining > 0) {
                                if (batchSize > remaining) {
                                    batchSize = remaining;
                                }
                                int faction = this->scenarioEvents[eventIdx].data.invasion.crusaderArabian;
                                int groupIdx = spawnedGroups[faction];
                                spawnedGroups[faction] = groupIdx + 1;

                                int edgeEntryIndex = DAT_TroopValueState::instance.attackInfo
                                                         .unknownSignpostRelatedArray[DAT_TroopValueState::instance
                                                                 .attackInfo.inv_count];
                                MACRO_CALL_MEMBER(Units::TribesState_Func::spawnUnitsIntoNewTribe,
                                    DAT_TribesState::ptr)(groupIdx, (Units::UnitType)spawnType,
                                    DAT_GameState::instance.mapAndTime.signpostsMapEdge[edgeEntryIndex][signpostIndex]
                                        .x,
                                    DAT_GameState::instance.mapAndTime.signpostsMapEdge[edgeEntryIndex][signpostIndex]
                                        .y,
                                    faction + 2, (Units::UnitType)unitType, (Units::UnitType)0, batchSize, 0);
                                signpostIndex += 1;
                                remaining -= batchSize;
                                if (signpostIndex >= edgeSignpostCount) {
                                    signpostIndex = 0;
                                }
                            }
                        }
                    }
                }

                int spIdx = DAT_TroopValueState::instance.attackInfo
                                .unknownSignpostRelatedArray[DAT_TroopValueState::instance.attackInfo.inv_count];
                MACRO_CALL_MEMBER(UI::MinimapViewState_Func::setSpawnMoment, DAT_MinimapViewState::ptr)(
                    DAT_GameState::instance.mapAndTime.signpostEntryData[spIdx].x,
                    DAT_GameState::instance.mapAndTime.signpostEntryData[spIdx].y);

                DAT_TroopValueState::instance.attackInfo.inv_count = savedInvCount;

                if (DAT_GameCore::instance.section1076 == 0) {
                    int faction = this->scenarioEvents[eventIdx].data.invasion.crusaderArabian;
                    if (playerVideoPlayed[faction] == 0) {
                        playerVideoPlayed[faction] = 1;
                        switch (faction) {
                        case 0:
                            MACRO_CALL_MEMBER(Rendering::Bink::AIMessageQueue_Func::playEventVideoBik,
                                DAT_VideoBikQueue::ptr)((char*)s__005a5339, (char*)s_sultan_nervous_bik_005a79d4,
                                (char*)s_infidel_attack_wav_005aa808);
                            break;
                        case 1:
                            MACRO_CALL_MEMBER(Rendering::Bink::AIMessageQueue_Func::playEventVideoBik,
                                DAT_VideoBikQueue::ptr)((char*)s__005a5339, (char*)s_good_soldier_nervous_bik_005aa81c,
                                (char*)s_arabian_attack_wav_005aa838);
                            break;
                        }
                        if (DAT_GameCore::instance.currentMenuViewType == UI::Enums::MVT_BUILD_MENU
                            && (DAT_GameCore::instance.activeMenuTab.buildMenuTab == 60
                                || DAT_GameCore::instance.activeMenuTab.buildMenuTab == 62)) {
                            MACRO_CALL_MEMBER(Game::GameCore_Func::swapBuildMenuTab, DAT_GameCore::ptr)();
                            if (DAT_GameCore::instance.buildmenuMenuTabToSwitchTo.buildMenuTab == 60) {
                                if (DAT_GameCore::instance.currentMenuViewType == UI::Enums::MVT_BUILD_MENU) {
                                    DAT_GameCore::instance.buildmenuMenuTabToSwitchTo.buildMenuTab
                                        = (UI::Enums::BuildMenuTabTypeShort)10;
                                } else if (DAT_GameCore::instance.currentMenuViewType == 12) {
                                    DAT_GameCore::instance.landscapingmenuMenuTabToSwitchTo.buildMenuTab
                                        = (UI::Enums::BuildMenuTabTypeShort)231;
                                }
                            }
                            MACRO_CALL_MEMBER(Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                                (UI::Enums::MenuViewType)DAT_GameCore::instance.currentMenuViewType, 0);
                        }
                    }
                }

                if (this->scenarioEvents[eventIdx].data.invasion.repeatMonths == 0) {
                    this->scenarioEvents[eventIdx].header.done = 1;
                } else {
                    this->scenarioEvents[eventIdx].header.year
                        += this->scenarioEvents[eventIdx].data.invasion.repeatMonths / 12;
                    this->scenarioEvents[eventIdx].header.month
                        += this->scenarioEvents[eventIdx].data.invasion.repeatMonths % 12;
                    this->scenarioEvents[eventIdx].header.pre_done = 0;
                    if (this->scenarioEvents[eventIdx].header.month >= 12) {
                        this->scenarioEvents[eventIdx].header.month -= 12;
                        this->scenarioEvents[eventIdx].header.year += 1;
                    }
                    MACRO_CALL_MEMBER(MapPropertiesState_Func::sortEventsByDate, this)();
                    eventIdx -= 1;
                }
                break;
            }
            }
        }

        int warnYear = DAT_GameState::instance.mapAndTime.year;
        int warnMonth = DAT_GameState::instance.mapAndTime.month + 3;
        if (warnMonth >= 12) {
            warnMonth -= 12;
            warnYear += 1;
        }

        for (int i = 0; i < 9; ++i) {
            playerVideoPlayed[i] = 0;
        }

        for (int eventIdx = 0; eventIdx < this->eventsCount; ++eventIdx) {
            if (this->scenarioEvents[eventIdx].header.year == warnYear
                && this->scenarioEvents[eventIdx].header.month == warnMonth
                && this->scenarioEvents[eventIdx].header.pre_done == 0) {
                this->scenarioEvents[eventIdx].header.pre_done = 1;
                if (this->scenarioEvents[eventIdx].header.tl_type == 1) {
                    DAT_GameState::instance.mapAndTime.field3171_0x27a8 = 1;
                    if (DAT_GameCore::instance.section1076 == 0) {
                        int faction = this->scenarioEvents[eventIdx].data.invasion.crusaderArabian;
                        if (playerVideoPlayed[faction] == 0) {
                            int totalUnits = 0;
                            for (int j = 0; j < 25; ++j) {
                                totalUnits += this->scenarioEvents[eventIdx].data.invasion.unitCountsPerUnitType[j];
                            }
                            int msgOffset = faction * 4 + 1;
                            if (totalUnits >= 25) {
                                if (totalUnits < 75) {
                                    msgOffset += 1;
                                } else if (totalUnits < 150) {
                                    msgOffset += 2;
                                } else {
                                    msgOffset += 3;
                                }
                            }
                            playerVideoPlayed[faction] = 1;
                            switch (faction) {
                            case 0: {
                                char* text = MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                                    DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_SANDS_OF_TIME, msgOffset);
                                MACRO_CALL_MEMBER(Rendering::Bink::AIMessageQueue_Func::playEventVideoBik,
                                    DAT_VideoBikQueue::ptr)(text, (char*)s_good_arab_nervous_bik_005aaa68,
                                    (&DAT_MissionAestheticsDefinedData::instance.field_0xec)[msgOffset]);
                                break;
                            }
                            case 1: {
                                char* text = MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                                    DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_SANDS_OF_TIME, msgOffset);
                                MACRO_CALL_MEMBER(Rendering::Bink::AIMessageQueue_Func::playEventVideoBik,
                                    DAT_VideoBikQueue::ptr)(text, (char*)s_good_soldier_nervous_bik_005aa81c,
                                    (&DAT_MissionAestheticsDefinedData::instance.field_0xec)[msgOffset]);
                                break;
                            }
                            }
                        }
                    }
                }
            }
        }

        if (DAT_GameState::instance.gameTicksLoadBalancer == 151 && DAT_GameState::instance.mapAndTime.week == 3) {
            int nextMonth = DAT_GameState::instance.mapAndTime.month + 1;
            int nextYear = DAT_GameState::instance.mapAndTime.year;
            if (nextMonth >= 12) {
                nextMonth -= 12;
                nextYear += 1;
            }
            for (int i = 0; i < this->eventsCount; ++i) {
                if (this->scenarioEvents[i].header.year == nextYear && this->scenarioEvents[i].header.month == nextMonth
                    && this->scenarioEvents[i].header.tl_type == 1) {
                    DAT_GameState::instance.mapAndTime.gameEventRelatedCountdown = i + 40;
                }
            }
        }
    }

} // namespace Map
} // namespace OpenSHC
