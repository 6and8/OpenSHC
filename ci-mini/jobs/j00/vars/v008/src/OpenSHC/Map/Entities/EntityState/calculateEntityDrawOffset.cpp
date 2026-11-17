#include "OpenSHC/Map/Entities/EntityState.func.hpp"

#include "OpenSHC/Globals/DAT_EntityDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Entities {

        // FUNCTION: STRONGHOLDCRUSADER 0x004036F0
        void EntityState::calculateEntityDrawOffset(int entityID)
        {
            int const subX = (byte)this->entityArray[entityID].microX & 7;
            int const subY = (byte)this->entityArray[entityID].microY & 7;
            int index;
            int const mapOrientationValue = DAT_TileMapState::instance.mapOrientation;
            if (mapOrientationValue == 4) {
                index = (7 - subY) * 16 + (7 - subX) * 2;
            } else if (mapOrientationValue == 2) {
                index = (7 - subX) * 16 + subY * 2;
            } else if (mapOrientationValue == 6) {
                index = subX * 16 + (7 - subY) * 2;
            } else if (mapOrientationValue == 0) {
                index = subY * 16 + subX * 2;
            } else {
                index = subX * 16 + subY * 2;
            }
            this->entityArray[entityID].x1 = DAT_EntityDefinedData::instance.EntitySubTileDrawOffsets[index].x;
            this->entityArray[entityID].y1 = DAT_EntityDefinedData::instance.EntitySubTileDrawOffsets[index + 1].x;
        }

    }
}
}
