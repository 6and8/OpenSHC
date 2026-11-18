#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/GMFirstPictureIndex.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        // FUNCTION: STRONGHOLDCRUSADER 0x0040EDF0
        void BuildingsState::updateHopsFieldTileGraphics(int buildingID)
        {
            // Unless all tiles are refreshed (field_0x18e024), only one tile is updated per call and the position to
            // continue from is stored in wheatFieldIndexToGrow
            int start = 0;
            int unchangedLeft = 3;
            if (DAT_BuildingsState::instance.field_0x18e024 == 0) {
                start = DAT_BuildingsState::instance.buildings[buildingID].wheatFieldIndexToGrow;
            }
            for (int i = 0; i < 24; ++i) {
                int tile = this->buildings[buildingID].tileRefs[(i + start) % 24];
                int frame;
                if (DAT_TileMapState::instance.DamageLayer[tile] == 0) {
                    frame = 0;
                } else if (DAT_TileMapState::instance.DamageLayer[tile] < 2) {
                    frame = 0;
                } else if (DAT_TileMapState::instance.DamageLayer[tile] < 4) {
                    frame = 1;
                } else if (DAT_TileMapState::instance.DamageLayer[tile] < 6) {
                    frame = 2;
                } else if (DAT_TileMapState::instance.DamageLayer[tile] < 8) {
                    frame = 3;
                } else if (DAT_TileMapState::instance.DamageLayer[tile] < 10) {
                    frame = 4;
                } else if (DAT_TileMapState::instance.DamageLayer[tile] < 12) {
                    frame = 5;
                } else if (DAT_TileMapState::instance.DamageLayer[tile] < 14) {
                    frame = 6;
                } else if (DAT_TileMapState::instance.DamageLayer[tile] < 28) {
                    frame = 7;
                } else if (DAT_TileMapState::instance.DamageLayer[tile] < 32) {
                    frame = 8;
                } else {
                    frame = 0;
                }

                int gfx = GMFirstPictureIndex::instance[14] + (DAT_TileMapState::instance.RandomLayer[tile] & 1) * 9
                    + 37 + frame;
                if (gfx == DAT_TileMapState::instance.GfxLayer[tile]) {
                    if (--unchangedLeft == 0) {
                        continue;
                    }
                } else {
                    DAT_TileMapState::instance.GfxLayer[tile] = gfx;
                }
                if (DAT_BuildingsState::instance.field_0x18e024 == 0) {
                    // Note: wraps at 36 instead of 24 like the tile index above
                    DAT_BuildingsState::instance.buildings[buildingID].wheatFieldIndexToGrow = (i + 1 + start) % 36;
                    return;
                }
            }
        }

    }
}
}
