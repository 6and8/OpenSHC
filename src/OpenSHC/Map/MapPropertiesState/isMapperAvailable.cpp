#include "OpenSHC/Map/MapPropertiesState.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x004BB010
    BOOLEnum MapPropertiesState::isMapperAvailable(MappersEnum mapper)
    {
        if ((mapper == 0xb2 || mapper == 0xb3) && DAT_GameCore::instance.gameMode_2 != 1) {
            return FALSE;
        }
        if (DAT_GameCore::instance.gameMode_2 == 1 && DAT_GameCore::instance.U2_mapType_singleOrMulti >= 1) {
            if (mapper == 0x3c || (mapper > 0x3d && mapper <= 0x40)) {
                return FALSE;
            }
            return TRUE;
        }
        if (DAT_GameCore::instance.gameMode_2 == 1) {
            return TRUE;
        }
        if (mapper == 0x138) {
            if (DAT_GameSynchronyState::instance.currentGameMode != 0
                && DAT_GameSynchronyState::instance.currentGameMode != 0x63
                && DAT_GameState::instance.mapAndTime.skirmishNoDogs != 0) {
                return FALSE;
            }
        } else if (mapper == 0x4e) {
            if (DAT_GameSynchronyState::instance.currentGameMode != 0
                && DAT_GameState::instance.mapAndTime.rawDeerCount == 0) {
                return FALSE;
            }
        }
        return (BOOLEnum)this->buildingAvailabilityRelatedFlags[mapper];
    }

}
}
