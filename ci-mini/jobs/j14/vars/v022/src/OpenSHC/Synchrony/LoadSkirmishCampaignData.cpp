// disable deprecation warnings for strcpy
#pragma warning(disable : 4996)

#include "../Synchrony.func.hpp"

#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Game/TrailType.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/Text/UserTextHandler.func.hpp"

#include "OpenSHC/Globals/CHAR_ARRAY_00eb0ab0.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_SkirmishDefinedData.hpp"
#include "OpenSHC/Globals/DAT_UserTextHandlerState.hpp"

namespace OpenSHC {

// FUNCTION: STRONGHOLDCRUSADER 0x004C6B20
void Synchrony::LoadSkirmishCampaignData(int missionID)
{
    Game::CampaignTrailMission* mission = &DAT_SkirmishDefinedData::instance.SkirmishTrailMissions[missionID];
    if (DAT_GameCore::instance.currentTrailType == Game::TT_EXTREME) {
        mission = &DAT_SkirmishDefinedData::instance.ExtremeTrailMissions[missionID];
    } else if (DAT_GameCore::instance.currentTrailType == Game::TT_WARCHEST) {
        mission = &DAT_SkirmishDefinedData::instance.WarchestTrailMissions[missionID];
    }
    strcpy(CHAR_ARRAY_00eb0ab0::instance, (char*)mission->mapNameAddress);
    memset(DAT_GameSynchronyState::instance.DAT_PlayerNames, 0, sizeof(DAT_GameSynchronyState::instance.DAT_PlayerNames));
    for (int i = 0; i != 9; ++i) {
        DAT_GameSynchronyState::instance.currentPlayerFullIDArray[i] = -1;
        DAT_GameSynchronyState::instance.currentAIArray[i] = 0;
        DAT_GameSynchronyState::instance.aiVariationArray[i] = -1;
    }
    strcpy(DAT_GameSynchronyState::instance.DAT_PlayerNames[1],
        MACRO_CALL_MEMBER(Text::UserTextHandler_Func::getTextArrayPointer, DAT_UserTextHandlerState::ptr)(0));
    DAT_GameSynchronyState::instance.isHost = TRUE;
    DAT_GameSynchronyState::instance.currentGameMode = Game::GM_SKIRMISH_SINGLE_PLAYER;
    MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand, DAT_GameSynchronyState::ptr)(
        Commands::GCT_ASK_FOR_SLOT_ASSIGNMENT);
    for (int i = 1; i < mission->numberOfPlayers; ++i) {
        DAT_GameSynchronyState::instance.currentAIArray[i + 1] = mission->playerAI[i];
        MACRO_CALL(Synchrony_Func::ResetAiVariationArrayValue)(i + 1);
    }
    MACRO_CALL(Synchrony_Func::SetAIPlayerNickNames)();
    for (int i = 0; i != 8; ++i) {
        DAT_GameSynchronyState::instance.DAT_PlayerGroupArray[i + 1] = (char)mission->team[i];
        if (mission->numberOfPlayers <= i) {
            DAT_GameSynchronyState::instance.DAT_PlayerGroupArray[i + 1] = -1;
        }
    }
    int highestTeam = 0;
    for (int i = 1; i != 9; ++i) {
        char group = DAT_GameSynchronyState::instance.DAT_PlayerGroupArray[i];
        DAT_GameState::instance.mapAndTime.playerGroupArray[i] = group;
        if (group > 0) {
            DAT_GameState::instance.mapAndTime.playerTeams[i] = group;
            if (group > highestTeam) {
                highestTeam = group;
            }
        }
    }
    for (int i = 1; i != 9; ++i) {
        if (DAT_GameSynchronyState::instance.DAT_PlayerGroupArray[i] == 0) {
            highestTeam += 1;
            DAT_GameState::instance.mapAndTime.playerTeams[i] = highestTeam;
        }
    }
    DAT_GameSynchronyState::instance.skirmishCurrentAdvantageBalance = mission->fairness;
    DAT_GameSynchronyState::instance.skirmishGameIntensityType = mission->startLevels;
    memset(DAT_GameSynchronyState::instance.playerPositionsArray, -10,
        sizeof(DAT_GameSynchronyState::instance.playerPositionsArray));
    for (int i = 0; i != 8; ++i) {
        if (mission->position[i] != 0) {
            DAT_GameSynchronyState::instance.playerPositionsArray[mission->position[i] - 1] = (char)i;
        }
    }
}

}
