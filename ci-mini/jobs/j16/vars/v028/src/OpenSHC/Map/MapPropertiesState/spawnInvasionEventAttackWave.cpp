#include "OpenSHC/Map/MapPropertiesState.func.hpp"
#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Units/TroopValueState.func.hpp"
#include "OpenSHC/Rendering/Bink/AIMessageQueue.func.hpp"
#include "OpenSHC/string-literals.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"
#include "OpenSHC/Globals/DAT_VideoBikQueue.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::Units::UnitType;

    // FUNCTION: STRONGHOLDCRUSADER 0x004C13F0
    void MapPropertiesState::spawnInvasionEventAttackWave()
    {
        int signpostIndex = 0;
        int spawnedGroups = 0;
        DAT_TroopValueState::instance.attackInfo.inv_count += 1;
        if (DAT_TroopValueState::instance.attackInfo.inv_count >= 50) {
            DAT_TroopValueState::instance.attackInfo.inv_count = 1;
        }
        MACRO_CALL_MEMBER(Units::TroopValueState_Func::initializeAttackWaveSlot, DAT_TroopValueState::ptr)(
            DAT_TroopValueState::instance.attackInfo.inv_count, 0);
        DAT_TroopValueState::instance.attackInfo
            .attackWavePlayerIDArray[DAT_TroopValueState::instance.attackInfo.inv_count]
            = (byte)(this->invasionEventContent.crusaderArabian + 2);
        // 25 slots: the last one reads invasionPoint, as in the original
        for (int slot = 0; slot < 25; ++slot) {
            int remaining = this->invasionEventContent.unitCountsPerUnitType[slot];
            if (remaining == 0) {
                continue;
            }
            int tribeType = 0;
            int unitType = 0;
            int groupSizeDivisor = 0;
            switch (slot) {
                case 0:
                    tribeType = 3;
                    unitType = 22;
                    groupSizeDivisor = 10;
                    break;
                case 1:
                    tribeType = 7;
                    unitType = 23;
                    groupSizeDivisor = 10;
                    break;
                case 2:
                    tribeType = 5;
                    unitType = 24;
                    groupSizeDivisor = 10;
                    break;
                case 3:
                    tribeType = 6;
                    unitType = 25;
                    groupSizeDivisor = 10;
                    break;
                case 4:
                    tribeType = 9;
                    unitType = 26;
                    groupSizeDivisor = 10;
                    break;
                case 5:
                    tribeType = 8;
                    unitType = 27;
                    groupSizeDivisor = 10;
                    break;
                case 6:
                    tribeType = 10;
                    unitType = 28;
                    groupSizeDivisor = 10;
                    break;
                case 7:
                    tribeType = 4;
                    unitType = 29;
                    groupSizeDivisor = 10;
                    break;
                case 8:
                    tribeType = 11;
                    unitType = 30;
                    groupSizeDivisor = 10;
                    break;
                case 9:
                    unitType = 39;
                    tribeType = 22;
                    groupSizeDivisor = 10;
                    break;
                case 10:
                    tribeType = 23;
                    unitType = 40;
                    groupSizeDivisor = 10;
                    break;
                case 11:
                    tribeType = 19;
                    unitType = 59;
                    groupSizeDivisor = 10;
                    break;
                case 12:
                    tribeType = 20;
                    unitType = 58;
                    groupSizeDivisor = 10;
                    break;
                case 13:
                    tribeType = 21;
                    unitType = 60;
                    groupSizeDivisor = 10;
                    break;
                case 14:
                    tribeType = 12;
                    unitType = 37;
                    groupSizeDivisor = 10;
                    break;
                case 15:
                    tribeType = 2;
                    unitType = 5;
                    groupSizeDivisor = 10;
                    break;
                case 16:
                    tribeType = 25;
                    unitType = 70;
                    groupSizeDivisor = 10;
                    break;
                case 17:
                    tribeType = 26;
                    unitType = 71;
                    groupSizeDivisor = 10;
                    break;
                case 18:
                    tribeType = 27;
                    unitType = 72;
                    groupSizeDivisor = 10;
                    break;
                case 19:
                    tribeType = 28;
                    unitType = 73;
                    groupSizeDivisor = 10;
                    break;
                case 20:
                    tribeType = 29;
                    unitType = 74;
                    groupSizeDivisor = 10;
                    break;
                case 21:
                    tribeType = 30;
                    unitType = 75;
                    groupSizeDivisor = 10;
                    break;
                case 22:
                    tribeType = 31;
                    unitType = 76;
                    groupSizeDivisor = 10;
                    break;
                case 23:
                    tribeType = 24;
                    unitType = 77;
                    groupSizeDivisor = 10;
                    break;
            }
            byte* score = DAT_TroopValueState::instance.attackInfo
                              .someSinglePlayerScore[DAT_TroopValueState::instance.attackInfo.inv_count];
            int scoreSlot = -1;
            if (tribeType == 22) {
                scoreSlot = 0;
            } else if (tribeType == 23) {
                scoreSlot = 1;
            } else if (tribeType == 19) {
                scoreSlot = 2;
            } else if (tribeType == 20) {
                scoreSlot = 3;
            } else if (tribeType == 21) {
                scoreSlot = 4;
            } else if (tribeType == 24) {
                scoreSlot = 8;
            }
            if (scoreSlot >= 0) {
                score[scoreSlot] += remaining;
            } else {
                int groupSize = remaining / (remaining / groupSizeDivisor + 1);
                while (remaining > 0) {
                    if (groupSize > remaining) {
                        groupSize = remaining;
                    }
                    MACRO_CALL_MEMBER(Units::TribesState_Func::spawnUnitsIntoNewTribe, DAT_TribesState::ptr)(
                        spawnedGroups, tribeType,
                        DAT_GameState::instance.mapAndTime
                            .signpostsMapEdge[DAT_TroopValueState::instance.attackInfo
                                    .unknownSignpostRelatedArray[DAT_TroopValueState::instance.attackInfo.inv_count]]
                                             [signpostIndex]
                            .x,
                        DAT_GameState::instance.mapAndTime
                            .signpostsMapEdge[DAT_TroopValueState::instance.attackInfo
                                    .unknownSignpostRelatedArray[DAT_TroopValueState::instance.attackInfo.inv_count]]
                                             [signpostIndex]
                            .y,
                        this->invasionEventContent.crusaderArabian + 2, (UnitType)unitType, (UnitType)0, groupSize, 0);
                    spawnedGroups += 1;
                    signpostIndex += 1;
                    remaining -= groupSize;
                    if (signpostIndex >= DAT_GameState::instance.mapAndTime.signpostsMapEdgeDataCounter) {
                        signpostIndex = 0;
                    }
                }
            }
        }
        switch (this->invasionEventContent.crusaderArabian) {
        case 0:
            MACRO_CALL_MEMBER(Rendering::Bink::AIMessageQueue_Func::playEventVideoBik, DAT_VideoBikQueue::ptr)(
                (char*)s__005a5339, (char*)s_sultan_nervous_bik_005a79d4, (char*)s_infidel_attack_wav_005aa808);
            break;
        case 1:
            MACRO_CALL_MEMBER(Rendering::Bink::AIMessageQueue_Func::playEventVideoBik, DAT_VideoBikQueue::ptr)(
                (char*)s__005a5339, (char*)s_good_soldier_nervous_bik_005aa81c, (char*)s_arabian_attack_wav_005aa838);
            break;
        }
        this->eventsCount = 0;
    }

}
}
