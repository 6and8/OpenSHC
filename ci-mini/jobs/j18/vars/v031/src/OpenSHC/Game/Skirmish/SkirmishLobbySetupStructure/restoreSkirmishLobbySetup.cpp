#include "../SkirmishLobbySetupStructure.func.hpp"

#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/INT_00b960b0.hpp"

namespace OpenSHC {
namespace Game {
    namespace Skirmish {

        // FUNCTION: STRONGHOLDCRUSADER 0x00490060
        void SkirmishLobbySetupStructure::restoreSkirmishLobbySetup()
        {
            DAT_GameSynchronyState::instance.skirmishAutoSaveEveryMinutes = this->mapu4int2;
            // The original writes the fog-of-war setting into the structure here instead of reading it back.
            strcpy(DAT_GameSynchronyState::instance.mapName, this->mapName);
            this->mbr_0x4 = DAT_GameState::instance.mapAndTime.skirmishFogOfWar;
            for (int player = 0; player < 9; ++player) {
                DAT_GameSynchronyState::instance.DAT_RoundTableOrderArray[player] = this->roundTableOrderArray[player];
                DAT_GameSynchronyState::instance.DAT_PlayerGroupArray[player] = this->playerGroupArray[player];
                DAT_GameSynchronyState::instance.currentAIArray[player] = this->currentAIArray[player];
                DAT_GameSynchronyState::instance.aiVariationArray[player] = this->aiVariationArray[player];
            }
            DAT_GameSynchronyState::instance.playerPositionsArray[0] = this->slot1Position;
            DAT_GameSynchronyState::instance.playerPositionsArray[1] = this->slot2Position;
            DAT_GameSynchronyState::instance.playerPositionsArray[2] = this->slot3Position;
            DAT_GameSynchronyState::instance.playerPositionsArray[3] = this->slot4Position;
            DAT_GameSynchronyState::instance.playerPositionsArray[4] = this->slot5Position;
            DAT_GameSynchronyState::instance.playerPositionsArray[5] = this->slot6Position;
            DAT_GameSynchronyState::instance.playerPositionsArray[6] = this->slot7Position;
            DAT_GameSynchronyState::instance.playerPositionsArray[7] = this->slot8Position;
            DAT_GameSynchronyState::instance.currentPlayerSlotID = this->currentPlayerSlotID;
            DAT_GameSynchronyState::instance.skirmishCurrentAdvantageBalance = this->currentAdvantageBalance;
            DAT_GameSynchronyState::instance.skirmishGameIntensityType = this->currentAdvantageGroup;
            DAT_GameSynchronyState::instance.skirmishTechLevel = this->mbr_0x80;
            for (int player = 0; player < 9; ++player) {
                DAT_GameCore::instance.selectedLordTypes[player] = this->playerLordTypeArray[player];
            }
            DAT_GameCore::instance.field_0x2340 = this->mbr_0xf0;
            DAT_GameCore::instance.selectedLordTypeUnk = this->selectedLordType;
            DAT_GameSynchronyState::instance.skirmishDefaultPopularity = this->popularity;
            DAT_GameSynchronyState::instance.DAT_MapSelectionRelativeSelected = this->mapSelectionRelativeSelected;
            DAT_GameSynchronyState::instance.DAT_MapSelectionScrollOffset = this->mapSelectionScrollOffset;
            DAT_GameSynchronyState::instance.lobbyMapSortOrder = this->mbr_0xfc;
            INT_00b960b0::instance = DAT_GameSynchronyState::instance.DAT_MapSelectionScrollOffset
                + DAT_GameSynchronyState::instance.DAT_MapSelectionRelativeSelected;
            MACRO_CALL_MEMBER(
                Synchrony::GameSynchronyState_Func::reorderTeamsAndPositions, DAT_GameSynchronyState::ptr)();
        }

    }
}
}
