#include "OpenSHC/Globals/DAT_MissionAestheticsDefinedData.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Map/MapPropertiesState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x004C6880
    void MapPropertiesState::loadMissionMapAndSetLord(int missionNumber)
    {
        int index = missionNumber - 1;
        if (index < 5) {
            MACRO_CALL_MEMBER(MapPropertiesState_Func::loadMap, this)(DAT_MissionAestheticsDefinedData::instance.missionMapNames1[index]);
        } else if (index < 10) {
            MACRO_CALL_MEMBER(MapPropertiesState_Func::loadMap, this)(DAT_MissionAestheticsDefinedData::instance.missionMapNames2[index - 5]);
        } else if (index < 15) {
            MACRO_CALL_MEMBER(MapPropertiesState_Func::loadMap, this)(DAT_MissionAestheticsDefinedData::instance.missionMapNames3[index - 10]);
        } else if (index < 20) {
            MACRO_CALL_MEMBER(MapPropertiesState_Func::loadMap, this)(DAT_MissionAestheticsDefinedData::instance.missionMapNames4[index - 15]);
        }
        MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::setMissionNumberSpecificLord, DAT_UnitsState::ptr)(index + 1);
    }

}
}
