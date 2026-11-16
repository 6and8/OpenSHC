#include "OpenSHC/Globals/DAT_MissionAestheticsDefinedData.hpp"
#include "OpenSHC/Map/MapPropertiesState.func.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x004C6820
    void MapPropertiesState::loadMapSiegeHeaderForMissionIndex(int missionNumber)
    {
        int index = missionNumber - 1;
        if (index < 5) {
            MACRO_CALL_MEMBER(MapPropertiesState_Func::loadMapSiegeHeaderSections, this)(DAT_MissionAestheticsDefinedData::instance.missionMapNames1[index]);
        } else if (index < 10) {
            MACRO_CALL_MEMBER(MapPropertiesState_Func::loadMapSiegeHeaderSections, this)(DAT_MissionAestheticsDefinedData::instance.missionMapNames2[index - 5]);
        } else if (index < 15) {
            MACRO_CALL_MEMBER(MapPropertiesState_Func::loadMapSiegeHeaderSections, this)(DAT_MissionAestheticsDefinedData::instance.missionMapNames3[index - 10]);
        } else if (index < 20) {
            MACRO_CALL_MEMBER(MapPropertiesState_Func::loadMapSiegeHeaderSections, this)(DAT_MissionAestheticsDefinedData::instance.missionMapNames4[index - 15]);
        }
    }

}
}
