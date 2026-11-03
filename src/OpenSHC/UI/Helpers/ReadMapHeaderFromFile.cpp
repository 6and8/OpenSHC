#include "OpenSHC/IO/FilePackager.func.hpp"
#include "OpenSHC/IO/ResourceManager.func.hpp"
#include "OpenSHC/UI/Helpers.func.hpp"
#include "OpenSHC/string-literals.hpp"

#include "OpenSHC/Globals/DAT_ResourceManager.hpp"
#include "OpenSHC/Globals/FilePackagerObj.hpp"
#include "OpenSHC/Globals/INT_00eb9ae8.hpp"

namespace OpenSHC {
namespace UI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004D8A20
    void Helpers::ReadMapHeaderFromFile(char* mapName)
    {
        char fileName[1008];
        strcpy(fileName, mapName);
        strcat(fileName, s__map_005a2294);
        MACRO_CALL_MEMBER(IO::ResourceManager_Func::resolveResourceFileName, DAT_ResourceManager::ptr)(
            IO::FRT_MAPS, fileName);
        MACRO_CALL_MEMBER(IO::FilePackager_Func::readMapHeader, FilePackagerObj::ptr)(TRUE);
        INT_00eb9ae8::instance = 1;
    }

}
}
