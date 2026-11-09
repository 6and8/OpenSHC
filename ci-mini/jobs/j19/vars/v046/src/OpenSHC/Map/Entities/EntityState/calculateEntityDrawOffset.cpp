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
            if (DAT_TileMapState::instance.mapOrientation == 4) {
                index = (7 - subY) * 16 + (7 - subX) * 2;
            } else if (DAT_TileMapState::instance.mapOrientation == 2) {
                index = (7 - subX) * 16 + subY * 2;
            } else if (DAT_TileMapState::instance.mapOrientation == 6) {
                index = subX * 16 + (7 - subY) * 2;
            } else if (DAT_TileMapState::instance.mapOrientation != 0) {
                index = subX * 16 + subY * 2;
            } else {
                index = subY * 16 + subX * 2;
            }
            this->entityArray[entityID].x1 = DAT_EntityDefinedData::instance.EntitySubTileDrawOffsets[index].x;
            short* y1Ptr = &this->entityArray[entityID].y1;
            *y1Ptr = DAT_EntityDefinedData::instance.EntitySubTileDrawOffsets[index + 1].x;
        }

    }
}
}
