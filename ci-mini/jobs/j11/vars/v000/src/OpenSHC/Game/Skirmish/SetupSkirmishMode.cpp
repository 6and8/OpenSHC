// disable deprecation warnings for strcpy
#pragma warning(disable : 4996)

#include "../Skirmish.func.hpp"

#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Game/TrailType.hpp"
#include "OpenSHC/Synchrony.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/Text/UserTextHandler.func.hpp"
#include "OpenSHC/UI/Actions.func.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_SkirmishDefinedData.hpp"
#include "OpenSHC/Globals/DAT_UserTextHandlerState.hpp"

namespace OpenSHC {
namespace Game {
    namespace Skirmish {

        // FUNCTION: STRONGHOLDCRUSADER 0x004C68D0
        void SetupSkirmishMode(int skirmishTrailMission)
        {
            CampaignTrailMission* mission = &DAT_SkirmishDefinedData::instance.SkirmishTrailMissions[skirmishTrailMission];
            if (TT_EXTREME == DAT_GameCore::instance.currentTrailType) {
                mission = &DAT_SkirmishDefinedData::instance.ExtremeTrailMissions[skirmishTrailMission];
            } else if (DAT_GameCore::instance.currentTrailType == TT_WARCHEST) {
                mission = &DAT_SkirmishDefinedData::instance.WarchestTrailMissions[skirmishTrailMission];
            }
            MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::setupSkirmishLobby, DAT_GameSynchronyState::ptr)();
            DAT_GameSynchronyState::instance.isHost = TRUE;
            DAT_GameSynchronyState::instance.currentGameMode = GM_SKIRMISH_SINGLE_PLAYER;
            DAT_GameSynchronyState::instance.DPLAYX_ReceivedPlayerID = 1;
            DAT_GameCore::instance.gameMode_2 = 3;
            memset(DAT_GameSynchronyState::instance.DAT_PlayerNames, 0,
                sizeof(DAT_GameSynchronyState::instance.DAT_PlayerNames));
            for (int i = 0; i != 9; ++i) {
                DAT_GameSynchronyState::instance.currentPlayerFullIDArray[i] = -1;
                DAT_GameSynchronyState::instance.currentAIArray[i] = 0;
                DAT_GameSynchronyState::instance.aiVariationArray[i] = -1;
            }
            strcpy(DAT_GameSynchronyState::instance.DAT_PlayerNames[1],
                MACRO_CALL_MEMBER(Text::UserTextHandler_Func::getTextArrayPointer, DAT_UserTextHandlerState::ptr)(0));
            MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand, DAT_GameSynchronyState::ptr)(
                Commands::GCT_ASK_FOR_SLOT_ASSIGNMENT);
            for (int i = 0; i < 9; ++i) {
                DAT_GameSynchronyState::instance.DAT_PlayerSlotArraySomeValue[i] = 1;
            }
            DAT_GameSynchronyState::instance.skirmishRelated1 = -1;
            DAT_GameCore::instance.mapU4Int0 = 0;
            for (int i = 1; i < mission->numberOfPlayers; ++i) {
                DAT_GameSynchronyState::instance.currentAIArray[i + 1] = mission->playerAI[i];
                MACRO_CALL(Synchrony_Func::ResetAiVariationArrayValue)(i + 1);
            }
            memset(DAT_GameSynchronyState::instance.playerPositionsArray, -10,
                sizeof(DAT_GameSynchronyState::instance.playerPositionsArray));
            for (int i = 0; i != 8; ++i) {
                if (mission->position[i] != 0) {
                    DAT_GameSynchronyState::instance.playerPositionsArray[mission->position[i] - 1] = (char)i;
                }
            }
            for (int i = 0; i != 8; ++i) {
                DAT_GameSynchronyState::instance.DAT_PlayerGroupArray[i + 1] = (char)mission->team[i];
                if (i >= mission->numberOfPlayers) {
                    DAT_GameSynchronyState::instance.DAT_PlayerGroupArray[i + 1] = -1;
                }
            }
            strcpy(DAT_GameSynchronyState::instance.mapName, (char*)mission->mapNameAddress);
            DAT_GameSynchronyState::instance.skirmishCurrentAdvantageBalance = mission->fairness;
            DAT_GameSynchronyState::instance.skirmishGameIntensityType = mission->startLevels;
            DAT_GameCore::instance.isSkirmishTrail = TRUE;
            int startMonths;
            if (DAT_GameCore::instance.currentTrailType == TT_EXTREME) {
                DAT_GameCore::instance.extremeTrailProgress = skirmishTrailMission;
                MACRO_CALL(UI::Actions_Func::LaunchSkirmishGame)((int)mission->aiv);
                startMonths
                    = DAT_GameCore::instance.extremeTrailStartDatesInMonths[DAT_GameCore::instance.extremeTrailProgress];
                DAT_GameCore::instance.extremeTrailStartDateMonths = startMonths;
            } else if (DAT_GameCore::instance.currentTrailType == TT_WARCHEST) {
                DAT_GameCore::instance.warchestTrailProgress = skirmishTrailMission;
                MACRO_CALL(UI::Actions_Func::LaunchSkirmishGame)((int)mission->aiv);
                startMonths
                    = DAT_GameCore::instance.warchestTrailStartDatesInMonths[DAT_GameCore::instance.warchestTrailProgress];
                DAT_GameCore::instance.warchestTrailStartDateMonths = startMonths;
            } else {
                DAT_GameCore::instance.skirmishTrailProgress = skirmishTrailMission;
                MACRO_CALL(UI::Actions_Func::LaunchSkirmishGame)((int)mission->aiv);
                startMonths
                    = DAT_GameCore::instance.skirmishTrailStartDateInMonths[DAT_GameCore::instance.skirmishTrailProgress];
                DAT_GameCore::instance.skirmishTrailStartDateMonths = startMonths;
            }
            DAT_GameState::instance.mapAndTime.year = startMonths / 12;
            DAT_GameState::instance.mapAndTime.month = startMonths % 12;
            DAT_GameSynchronyState::instance.finalResults.yearStart = startMonths / 12;
            DAT_GameSynchronyState::instance.finalResults.monthStart = startMonths % 12;
        }

    } // namespace Skirmish
} // namespace Game
} // namespace OpenSHC
