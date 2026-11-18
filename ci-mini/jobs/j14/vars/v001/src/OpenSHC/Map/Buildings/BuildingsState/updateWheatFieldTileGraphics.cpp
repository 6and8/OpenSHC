#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"

#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/GMFirstPictureIndex.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        // FUNCTION: STRONGHOLDCRUSADER 0x0040CF20
        void BuildingsState::updateWheatFieldTileGraphics(int buildingID)
        {
            // Unless all tiles are refreshed (field_0x18e024), only one tile is updated per call and the position to
            // continue from is stored in wheatFieldIndexToGrow
            int start = 0;
            int frame = 0;
            int unchangedLeft = 3;
            if (DAT_BuildingsState::instance.field_0x18e024 == 0) {
                start = this->buildings[buildingID].wheatFieldIndexToGrow;
            }
            for (int i = 0; i < 36; ++i) {
                int tile
                    = this->buildings[buildingID]
                          .tileRefs[DAT_BuildingDefinedData::instance.WheatFieldTile_Unknown[(i + start) % 36] - 1];
                if (DAT_TileMapState::instance.DamageLayer[tile] == 0) {
                    frame = 0;
                } else if (DAT_TileMapState::instance.DamageLayer[tile] < 1) {
                    frame = 0;
                } else if (DAT_TileMapState::instance.DamageLayer[tile] < 2) {
                    frame = 4;
                } else if (DAT_TileMapState::instance.DamageLayer[tile] < 5) {
                    frame = 8;
                } else if (DAT_TileMapState::instance.DamageLayer[tile] < 8) {
                    frame = 12;
                } else if (DAT_TileMapState::instance.DamageLayer[tile] < 11) {
                    frame = 16;
                } else if (DAT_TileMapState::instance.DamageLayer[tile] < 101) {
                    frame = 20;
                } else if (DAT_TileMapState::instance.DamageLayer[tile] < 102) {
                    frame = 28;
                } else if (DAT_TileMapState::instance.DamageLayer[tile] < 103) {
                    frame = 32;
                } else if (DAT_TileMapState::instance.DamageLayer[tile] < 120) {
                    frame = 32;
                } else if (DAT_TileMapState::instance.DamageLayer[tile] == 120) {
                    frame = 24;
                } else if (DAT_TileMapState::instance.DamageLayer[tile] == 121) {
                    frame = 36;
                }

                int gfx;
                if (frame < 36) {
                    gfx = (DAT_TileMapState::instance.RandomLayer[tile] & 3) + GMFirstPictureIndex::instance[14]
                        + frame;
                } else {
                    gfx = GMFirstPictureIndex::instance[14] + frame;
                }
                if (gfx == DAT_TileMapState::instance.GfxLayer[tile]) {
                    if (--unchangedLeft == 0) {
                        continue;
                    }
                } else {
                    DAT_TileMapState::instance.GfxLayer[tile] = gfx;
                }
                if (DAT_BuildingsState::instance.field_0x18e024 == 0) {
                    DAT_BuildingsState::instance.buildings[buildingID].wheatFieldIndexToGrow = (i + 1 + start) % 36;
                    return;
                }
            }
        }

    }
}
}
