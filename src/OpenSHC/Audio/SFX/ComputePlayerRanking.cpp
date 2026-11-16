#include "../SFX.func.hpp"

#include "OpenSHC/Map/Units/UnitsState.func.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Audio {
    namespace SFX {

        struct PlayerRankingEntry {
            int playerID;
            int points;
        };

        // FUNCTION: STRONGHOLDCRUSADER 0x0044B680
        int ComputePlayerRanking(int playerID)
        {
            int defeated[10];
            PlayerRankingEntry entries[10];
            for (int i = 0; i < 10; ++i) {
                entries[i].playerID = 0;
            }

            int count = 0;
            for (int player = 1; player < 9; ++player) {
                if (DAT_GameSynchronyState::instance.finalResults.active[player] == 0) {
                    continue;
                }
                entries[count].playerID = player;
                if (MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::getAliveLordForPlayer, DAT_UnitsState::ptr)(player)
                    == 0) {
                    if (player == playerID) {
                        return 0;
                    }
                    defeated[player] = 1;
                    entries[count].points = 0;
                } else {
                    entries[count].points = MACRO_CALL(SFX_Func::ComputePlayerPoints1)(player);
                }
                ++count;
            }

            for (int rank = 0; rank < count; ++rank) {
                int maxPoints;
                int best = -1;
                for (int i = 0; i < count; ++i) {
                    if (entries[i].playerID != 0 && (best == -1 || entries[i].points > maxPoints)) {
                        maxPoints = entries[i].points;
                        best = i;
                    }
                }
                if (best < 0) {
                    return 0;
                }
                int id = entries[best].playerID;
                entries[best].playerID = 0;
                if (id == playerID) {
                    return rank + 1;
                }
            }
            return 0;
        }

    }
}
}
