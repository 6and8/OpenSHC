#include "OpenSHC/Map/WildlifeState.func.hpp"
#include "OpenSHC/Map/WildlifeState.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x0052df30
    void WildlifeState::updateWildlife()
    {
        if (DAT_GameSynchronyState::instance.currentGameMode != 0) {
            return;
        }
        for (int y = 0; y < 40; ++y) {
            for (int x = 0; x < 40; ++x) {
                this->grid[x][y].field_0x34 = 0;
                this->grid[x][y].field_0x50 = 0;
                this->grid[x][y].field_0x60 = 0;
                this->grid[x][y].field_0x64 = 0;
                this->grid[x][y].field_0x70 /= 100;
                if (this->grid[x][y].chimps != 0) {
                    if (this->grid[x][y].keeps != 0) {
                        this->grid[x][y].field_0x60 = 1;
                    }
                    if (this->grid[x][y].castlebuildings != 0) {
                        this->grid[x][y].field_0x60 += 1;
                    }
                }
            }
        }
        for (int y = 0; y < 40; ++y) {
            for (int x = 0; x < 40; ++x) {
                if (this->grid[x][y].unstalkedUnitCount != 0) {
                    MACRO_CALL_MEMBER(WildlifeState_Func::floodFillField13FromCell, this)(x, y, 2);
                } else if (this->grid[x][y].buildingTiles != 0) {
                    MACRO_CALL_MEMBER(WildlifeState_Func::floodFillField13FromCell, this)(x, y, 2);
                } else if (this->grid[x][y].lionCount != 0) {
                    MACRO_CALL_MEMBER(WildlifeState_Func::floodFillField13FromCell, this)(x, y, 3);
                }
                if (this->grid[x][y].farmFieldTiles != 0) {
                    MACRO_CALL_MEMBER(WildlifeState_Func::floodFillField20FromCell, this)(x, y, 6);
                }
            }
        }
    }

} // namespace Map
} // namespace OpenSHC
