#include "../GameSynchronyState.func.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_ProtocolDefinedData.hpp"

namespace OpenSHC {
namespace Synchrony {

    // FUNCTION: STRONGHOLDCRUSADER 0x0047E5B0
    void GameSynchronyState::computeLatencyAdjustmentFromMatchTimes(int param_1)
    {
        this->minPlayerMapTime = -1;
        this->mapTimeInTicksSinglePlayer = -1;
        for (int player = 1; player < 9; ++player) {
            if (this->currentPlayerFullIDArray[player] == -1) {
                continue;
            }
            if (this->matchTimes[player] == -1) {
                this->matchTimes[player] = DAT_GameCore::instance.mapTimeInTicks;
            }
            if (this->minPlayerMapTime == -1) {
                this->mapTimeInTicksSinglePlayer = this->minPlayerMapTime = this->matchTimes[player];
            } else {
                if (this->matchTimes[player] < (int)this->minPlayerMapTime) {
                    this->minPlayerMapTime = this->matchTimes[player];
                }
                if (this->mapTimeInTicksSinglePlayer < this->matchTimes[player]) {
                    this->mapTimeInTicksSinglePlayer = this->matchTimes[player];
                }
            }
        }
        this->playerMapTimeSpread = this->mapTimeInTicksSinglePlayer - this->minPlayerMapTime;
        this->localPlayerMapTime = this->matchTimes[param_1];
        this->ticksAheadOfSlowestPlayer = 0;
        this->ticksBehindFastestPlayer = 0;
        if (this->localPlayerMapTime == this->minPlayerMapTime) {
            this->ticksBehindFastestPlayer = this->localPlayerMapTime - this->mapTimeInTicksSinglePlayer;
        } else {
            this->ticksAheadOfSlowestPlayer = this->localPlayerMapTime - this->minPlayerMapTime;
        }
        if ((int)this->ticksBehindFastestPlayer < 0) {
            this->field_0x109eb8 = 1;
            for (int i = 0; i < 12; ++i) {
                if ((int)this->ticksBehindFastestPlayer > DAT_ProtocolDefinedData::instance.field_0x4[i][0]) {
                    this->field_0x109eb8 = DAT_ProtocolDefinedData::instance.field_0x4[i][1];
                    return;
                }
            }
            return;
        }
        for (int i = 0; i < 40; ++i) {
            if ((int)this->ticksAheadOfSlowestPlayer <= DAT_ProtocolDefinedData::instance.field_0x64[i][0]) {
                this->field_0x109eb0 = DAT_ProtocolDefinedData::instance.field_0x64[i][1];
                this->field_0x109eb4 = DAT_ProtocolDefinedData::instance.field_0x64[i][2];
                return;
            }
        }
    }

}
}
