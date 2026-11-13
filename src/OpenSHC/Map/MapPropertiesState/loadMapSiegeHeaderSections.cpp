#include "OpenSHC/IO/FilePackager.func.hpp"
#include "OpenSHC/IO/ResourceManager.func.hpp"
#include "OpenSHC/Map/MapPropertiesState.func.hpp"

#include "OpenSHC/Globals/DAT_MapDefinedData.hpp"
#include "OpenSHC/Globals/DAT_MapPropertiesState.hpp"
#include "OpenSHC/Globals/DAT_ResourceManager.hpp"
#include "OpenSHC/Globals/FilePackagerObj.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x004C3110
    void MapPropertiesState::loadMapSiegeHeaderSections(char* mapName)
    {
        MACRO_CALL_MEMBER(IO::ResourceManager_Func::resolveResourceFileName, DAT_ResourceManager::ptr)(
            IO::FRT_MAPS, mapName);
        MACRO_CALL_MEMBER(IO::FilePackager_Func::readMapHeaderSectionByID, FilePackagerObj::ptr)(
            DAT_MapDefinedData::instance.MapSectionAddressArray, 0x427);
        MACRO_CALL_MEMBER(IO::FilePackager_Func::readMapHeaderSectionByID, FilePackagerObj::ptr)(
            DAT_MapDefinedData::instance.MapSectionAddressArray, 0x426);
        MACRO_CALL_MEMBER(IO::FilePackager_Func::readMapHeaderSectionByID, FilePackagerObj::ptr)(
            DAT_MapDefinedData::instance.MapSectionAddressArray, 0x428);
        MACRO_CALL_MEMBER(IO::FilePackager_Func::readMapHeaderSectionByID, FilePackagerObj::ptr)(
            DAT_MapDefinedData::instance.MapSectionAddressArray, 0x420);
        MACRO_CALL_MEMBER(IO::FilePackager_Func::readMapHeaderSectionByID, FilePackagerObj::ptr)(
            DAT_MapDefinedData::instance.MapSectionAddressArray, 0x421);
        if (FilePackagerObj::instance.versionNumOfCurrentFileTypeUnk < 0x9a) {
            MACRO_CALL_MEMBER(MapPropertiesState_Func::removeProcessedInvasionEvents, DAT_MapPropertiesState::ptr)();
        }
    }

}
}
