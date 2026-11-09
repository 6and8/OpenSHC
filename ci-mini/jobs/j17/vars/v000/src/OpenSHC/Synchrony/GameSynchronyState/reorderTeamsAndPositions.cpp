#include "../GameSynchronyState.func.hpp"

#include "OpenSHC/Commands/GameCommandType.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace Synchrony {

    // FUNCTION: STRONGHOLDCRUSADER 0x0048C7B0
    BOOLEnum GameSynchronyState::reorderTeamsAndPositions()
    {
        int positionTaken[9];
        int teamSizes[5];
        for (int player = 1; player < 9; ++player) {
            this->DAT_RoundTableOrderArray[player] = 0;
            positionTaken[player] = 0;
        }
        for (int team = 0; team < 5; ++team) {
            teamSizes[team] = 0;
        }

        int playerCount = 0;
        for (int player = 1; player < 9; ++player) {
            if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[player] == -1
                && DAT_GameSynchronyState::instance.currentAIArray[player] == 0) {
                this->DAT_PlayerGroupArray[player] = -1;
                continue;
            }
            if (this->DAT_PlayerGroupArray[player] < 0) {
                this->DAT_PlayerGroupArray[player] = 0;
            }
            int const team = this->DAT_PlayerGroupArray[player];
            teamSizes[team] += 1;
            if (team != 0) {
                teamSizes[0] += 1;
            }
            ++playerCount;
        }

        for (int team = 1; team <= 4; ++team) {
            if (teamSizes[team] < 1) {
                continue;
            }
            if (teamSizes[0] == teamSizes[team]) {
                for (int player = 1; player < 9; ++player) {
                    if (this->DAT_PlayerGroupArray[player] >= 0) {
                        this->DAT_PlayerGroupArray[player] = 0;
                    }
                }
                teamSizes[team] = 0;
                break;
            }
            if (teamSizes[team] == 1) {
                for (int player = 1; player < 9; ++player) {
                    if (this->DAT_PlayerGroupArray[player] == team) {
                        this->DAT_PlayerGroupArray[player] = 0;
                    }
                }
                teamSizes[team] = 0;
            }
        }

        for (int team = 1; team <= 3; ++team) {
            if (teamSizes[team] != 0 || teamSizes[team + 1] == 0) {
                continue;
            }
            for (int player = 1; player < 9; ++player) {
                if (this->DAT_PlayerGroupArray[player] > team) {
                    this->DAT_PlayerGroupArray[player] -= 1;
                }
            }
            for (int next = team + 1; next <= 4; ++next) {
                teamSizes[next - 1] = teamSizes[next];
            }
        }

        for (int position = 1; position <= playerCount; ++position) {
            int best = -1;
            int bestTeam = -1;
            for (int player = 1; player < 9; ++player) {
                if (this->DAT_PlayerGroupArray[player] < 0 || positionTaken[player] != 0) {
                    continue;
                }
                int team = this->DAT_PlayerGroupArray[player];
                if (team == 0) {
                    team = 10;
                }
                if (team < bestTeam || best == -1) {
                    best = player;
                    bestTeam = team;
                }
            }
            if (best < 0) {
                break;
            }
            DAT_GameSynchronyState::instance.DAT_RoundTableOrderArray[position] = (char)best;
            positionTaken[best] = 1;
        }

        if (DAT_GameSynchronyState::instance.currentGameMode != Game::GM_SKIRMISH_SINGLE_PLAYER
            && DAT_GameSynchronyState::instance.isHost) {
            MACRO_CALL_MEMBER(GameSynchronyState_Func::queueCommand, DAT_GameSynchronyState::ptr)(
                (GameCommandType)0x6e);
            MACRO_CALL_MEMBER(GameSynchronyState_Func::queueCommand, DAT_GameSynchronyState::ptr)(
                Commands::GCT_HOST_ANNOUNCE_TEAMS_AND_POSITIONS);
        }
        return TRUE;
    }

}
}
