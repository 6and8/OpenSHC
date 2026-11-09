#include "OpenSHC/Map/LandscapeState.func.hpp"

#include "OpenSHC/Globals/DAT_CurrentRockID.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_OrganismDefinedData.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x004F2140
    int LandscapeState::createRock(undefined4 x, undefined4 y, int rockType, undefined4 size, undefined4 orientation)
    {
        int rockID;
        for (rockID = 1; rockID < 4000; ++rockID) {
            if (this->rocks[rockID].one == 0) {
                break;
            }
            if (rockID >= 3999) {
                return 0;
            }
        }
        this->rocks[rockID].uid = DAT_GameCore::instance.uniqueGameObjectTracker;
        this->rocks[rockID].size = (short)size;
        DAT_GameCore::instance.uniqueGameObjectTracker += 1;
        this->rocks[rockID].y = (ushort)y;
        this->rocks[rockID].x = (ushort)x;
        this->rocks[rockID].one = 1;
        short* typePtr = &this->rocks[rockID].type;
        *typePtr = (short)rockType;
        this->rocks[rockID].tile = (short)x + DAT_ViewportRenderState::instance.translationMatrix[(short)y].addXgetTile;
        this->rocks[rockID].orientation = (short)orientation;
        this->rocks[rockID].unknownGMID = (short)DAT_OrganismDefinedData::instance.Rock_field0xe[rockType];
        DAT_CurrentRockID::instance = rockID;
        DAT_OrganismDefinedData::instance.RockTypeFunctions[this->rocks[rockID].type]();
        return rockID;
    }

}
}
