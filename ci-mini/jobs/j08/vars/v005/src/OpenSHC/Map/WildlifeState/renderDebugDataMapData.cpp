#include "OpenSHC/Map/WildlifeState.func.hpp"
#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/Map/WildlifeState.hpp"
#include "OpenSHC/Rendering/Colors/ColorsEnum.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"

#include "OpenSHC/Globals/COL_BLACK.hpp"
#include "OpenSHC/Globals/COL_BLUE.hpp"
#include "OpenSHC/Globals/COL_BRIGHT_YELLOW.hpp"
#include "OpenSHC/Globals/COL_DARK_CYAN_GREY.hpp"
#include "OpenSHC/Globals/COL_DARK_GREEN.hpp"
#include "OpenSHC/Globals/COL_LIME.hpp"
#include "OpenSHC/Globals/COL_MODERATE_GREEN.hpp"
#include "OpenSHC/Globals/COL_RED.hpp"
#include "OpenSHC/Globals/COL_VERY_DARK_GREY.hpp"
#include "OpenSHC/Globals/COL_VIVID_BLUE.hpp"
#include "OpenSHC/Globals/COL_WHITE.hpp"
#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x0052bf40
    void WildlifeState::renderDebugDataMapData(int x, int y, int width, int height)
    {
        x += 2;
        int displayType = this->DAT_DebugDataMapDataDisplayType;
        if (displayType == 0) {
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                "Connect ", x + 420, y + 4, Text::TTA_LEFT, OpenSHC::Rendering::Colors::COL_FFFFFF, 17, FALSE, 0);
        } else if (displayType == 1) {
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                "Chimps  ", x + 420, y + 4, Text::TTA_LEFT, OpenSHC::Rendering::Colors::COL_FFFFFF, 17, FALSE, 0);
        } else if (displayType == 2) {
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                "Farmland   ", x + 420, y + 4, Text::TTA_LEFT, OpenSHC::Rendering::Colors::COL_FFFFFF, 17, FALSE, 0);
        } else if (displayType == 3) {
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                "Humans  ", x + 420, y + 4, Text::TTA_LEFT, OpenSHC::Rendering::Colors::COL_FFFFFF, 17, FALSE, 0);
        } else if (displayType == 4) {
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                "Mankind  ", x + 420, y + 4, Text::TTA_LEFT, OpenSHC::Rendering::Colors::COL_FFFFFF, 17, FALSE, 0);
        } else if (displayType == 5) {
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                "Deer  ", x + 420, y + 4, Text::TTA_LEFT, OpenSHC::Rendering::Colors::COL_FFFFFF, 17, FALSE, 0);
        } else if (displayType == 6) {
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                "Route  ", x + 420, y + 4, Text::TTA_LEFT, OpenSHC::Rendering::Colors::COL_FFFFFF, 17, FALSE, 0);
        } else if (displayType == 7) {
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                "Panic  ", x + 420, y + 4, Text::TTA_LEFT, OpenSHC::Rendering::Colors::COL_FFFFFF, 17, FALSE, 0);
        } else if (displayType == 8) {
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                "Siege  ", x + 420, y + 4, Text::TTA_LEFT, OpenSHC::Rendering::Colors::COL_FFFFFF, 17, FALSE, 0);
        } else if (displayType == 9) {
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                "Slink  ", x + 420, y + 4, Text::TTA_LEFT, OpenSHC::Rendering::Colors::COL_FFFFFF, 17, FALSE, 0);
        }

        for (int i = 0; i < 401; i += 10) {
            MACRO_CALL_MEMBER(UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                x, y + i, x + 400, y + i, (ushort)COL_WHITE::instance.shortValue);
        }

        for (int i = 0; i < 401; i += 10) {
            MACRO_CALL_MEMBER(UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                x + i, y, x + i, y + 400, (ushort)COL_WHITE::instance.shortValue);
        }

        for (int gy = 0; gy < 40; ++gy) {
            for (int gx = 0; gx < 40; ++gx) {
                if (this->grid[gx][gy].firstMember > 0) {
                    int mode = this->DAT_DebugDataMapDataDisplayType;
                    ushort col;
                    if (mode == 0) {
                        int areaId = this->grid[gx][gy].separateAreaID;
                        int idx = areaId & 7;
                        if (areaId == 0) {
                            col = (ushort)COL_BLUE::instance.shortValue;
                        } else if (idx == 1) {
                            col = (ushort)COL_RED::instance.shortValue;
                        } else if (idx == 2) {
                            col = (ushort)COL_BRIGHT_YELLOW::instance.shortValue;
                        } else if (idx == 3) {
                            col = (ushort)COL_MODERATE_GREEN::instance.shortValue;
                        } else if (idx == 4) {
                            col = (ushort)COL_WHITE::instance.shortValue;
                        } else if (idx == 5) {
                            col = (ushort)COL_DARK_CYAN_GREY::instance.shortValue;
                        } else if (idx == 6) {
                            col = (ushort)COL_LIME::instance.shortValue;
                        } else if (idx == 7) {
                            col = (ushort)COL_VIVID_BLUE::instance.shortValue;
                        } else {
                            col = (ushort)COL_VERY_DARK_GREY::instance.shortValue;
                        }
                        MACRO_CALL_MEMBER(
                            UI::Rendering::PencilRenderCore_Func::drawColorBox, DAT_PencilRenderCore::ptr)(
                            x + gx * 10 + 1, y + gy * 10 + 1, x + gx * 10 + 9, y + gy * 10 + 9, col);
                    } else if (mode == 1) {
                        if (this->grid[gx][gy].separateAreaID == 0) {
                            col = (ushort)COL_BLUE::instance.shortValue;
                        } else if (this->grid[gx][gy].chimps != 0) {
                            col = (ushort)COL_RED::instance.shortValue;
                        } else {
                            col = (ushort)COL_LIME::instance.shortValue;
                        }
                        MACRO_CALL_MEMBER(
                            UI::Rendering::PencilRenderCore_Func::drawColorBox, DAT_PencilRenderCore::ptr)(
                            x + gx * 10 + 1, y + gy * 10 + 1, x + gx * 10 + 9, y + gy * 10 + 9, col);
                    } else if (mode == 2) {
                        if (this->grid[gx][gy].separateAreaID == 0) {
                            col = (ushort)COL_BLUE::instance.shortValue;
                        } else if (this->grid[gx][gy].farmFieldTiles != 0) {
                            col = (ushort)COL_DARK_GREEN::instance.shortValue;
                        } else if (this->grid[gx][gy].rabbitCount != 0) {
                            col = (ushort)COL_RED::instance.shortValue;
                        } else if (this->grid[gx][gy].field_0x3c != 0) {
                            col = (ushort)COL_WHITE::instance.shortValue;
                        } else if (this->grid[gx][gy].field_0x50 != 0) {
                            col = (ushort)COL_DARK_CYAN_GREY::instance.shortValue;
                        } else {
                            col = (ushort)COL_LIME::instance.shortValue;
                        }
                        MACRO_CALL_MEMBER(
                            UI::Rendering::PencilRenderCore_Func::drawColorBox, DAT_PencilRenderCore::ptr)(
                            x + gx * 10 + 1, y + gy * 10 + 1, x + gx * 10 + 9, y + gy * 10 + 9, col);
                    } else if (mode == 3) {
                        if (this->grid[gx][gy].separateAreaID == 0) {
                            col = (ushort)COL_BLUE::instance.shortValue;
                        } else if (this->grid[gx][gy].unstalkedUnitCount != 0) {
                            col = (ushort)COL_RED::instance.shortValue;
                        } else {
                            col = (ushort)COL_LIME::instance.shortValue;
                        }
                        MACRO_CALL_MEMBER(
                            UI::Rendering::PencilRenderCore_Func::drawColorBox, DAT_PencilRenderCore::ptr)(
                            x + gx * 10 + 1, y + gy * 10 + 1, x + gx * 10 + 9, y + gy * 10 + 9, col);
                    } else if (mode == 4) {
                        if (this->grid[gx][gy].separateAreaID == 0) {
                            col = (ushort)COL_BLUE::instance.shortValue;
                        } else if (this->grid[gx][gy].unstalkedUnitCount != 0) {
                            col = (ushort)COL_RED::instance.shortValue;
                        } else if (this->grid[gx][gy].buildingTiles != 0) {
                            col = (ushort)COL_RED::instance.shortValue;
                        } else if (this->grid[gx][gy].field_0x34 != 0) {
                            col = (ushort)COL_BRIGHT_YELLOW::instance.shortValue;
                        } else {
                            col = (ushort)COL_LIME::instance.shortValue;
                        }
                        MACRO_CALL_MEMBER(
                            UI::Rendering::PencilRenderCore_Func::drawColorBox, DAT_PencilRenderCore::ptr)(
                            x + gx * 10 + 1, y + gy * 10 + 1, x + gx * 10 + 9, y + gy * 10 + 9, col);
                    } else if (mode == 5) {
                        if (this->grid[gx][gy].separateAreaID == 0) {
                            col = (ushort)COL_BLUE::instance.shortValue;
                        } else if (this->grid[gx][gy].unstalkedUnitCount != 0) {
                            col = (ushort)COL_RED::instance.shortValue;
                        } else if (this->grid[gx][gy].buildingTiles != 0) {
                            col = (ushort)COL_RED::instance.shortValue;
                        } else if (this->grid[gx][gy].lionCount != 0) {
                            col = (ushort)COL_BLACK::instance.shortValue;
                        } else if (this->grid[gx][gy].camelCount != 0) {
                            col = (ushort)COL_BLACK::instance.shortValue;
                        } else if (this->grid[gx][gy].deerCount != 0) {
                            col = (ushort)COL_MODERATE_GREEN::instance.shortValue;
                        } else if (this->grid[gx][gy].field_0x34 == 0) {
                            col = (ushort)COL_LIME::instance.shortValue;
                        } else {
                            col = (ushort)COL_BRIGHT_YELLOW::instance.shortValue;
                        }
                        MACRO_CALL_MEMBER(
                            UI::Rendering::PencilRenderCore_Func::drawColorBox, DAT_PencilRenderCore::ptr)(
                            x + gx * 10 + 1, y + gy * 10 + 1, x + gx * 10 + 9, y + gy * 10 + 9, col);
                    } else if (mode == 6) {
                        if (this->grid[gx][gy].separateAreaID == 0) {
                            col = (ushort)COL_BLUE::instance.shortValue;
                        } else if (this->grid[gx][gy].deerCount != 0) {
                            col = (ushort)COL_RED::instance.shortValue;
                        } else if (this->grid[gx][gy].lionCount != 0) {
                            col = (ushort)COL_VIVID_BLUE::instance.shortValue;
                        } else if (this->grid[gx][gy].field_0x3c != 0) {
                            col = (ushort)COL_WHITE::instance.shortValue;
                        } else if (this->grid[gx][gy].casDisRelated2 != 0) {
                            col = (ushort)COL_BRIGHT_YELLOW::instance.shortValue;
                        } else if (this->grid[gx][gy].field_0x34 != 0) {
                            col = (ushort)COL_BLACK::instance.shortValue;
                        } else {
                            col = (ushort)COL_LIME::instance.shortValue;
                        }
                        MACRO_CALL_MEMBER(
                            UI::Rendering::PencilRenderCore_Func::drawColorBox, DAT_PencilRenderCore::ptr)(
                            x + gx * 10 + 1, y + gy * 10 + 1, x + gx * 10 + 9, y + gy * 10 + 9, col);
                    } else if (mode == 7) {
                        if (this->grid[gx][gy].separateAreaID == 0) {
                            col = (ushort)COL_BLUE::instance.shortValue;
                        } else if (this->grid[gx][gy].field_0x48 != 0) {
                            col = (ushort)COL_WHITE::instance.shortValue;
                        } else if (this->grid[gx][gy].deerCount != 0) {
                            col = (ushort)COL_RED::instance.shortValue;
                        } else if (this->grid[gx][gy].field_0x34 != 0) {
                            col = (ushort)COL_BLACK::instance.shortValue;
                        } else {
                            col = (ushort)COL_LIME::instance.shortValue;
                        }
                        MACRO_CALL_MEMBER(
                            UI::Rendering::PencilRenderCore_Func::drawColorBox, DAT_PencilRenderCore::ptr)(
                            x + gx * 10 + 1, y + gy * 10 + 1, x + gx * 10 + 9, y + gy * 10 + 9, col);
                    } else if (mode == 8) {
                        if (this->grid[gx][gy].field_0x60 != 0) {
                            col = (ushort)COL_WHITE::instance.shortValue;
                        } else if (this->grid[gx][gy].field_0x64 != 0) {
                            col = (ushort)COL_BLACK::instance.shortValue;
                        } else if (this->grid[gx][gy].castlebuildings != 0) {
                            col = (ushort)COL_BRIGHT_YELLOW::instance.shortValue;
                        } else if (this->grid[gx][gy].separateAreaID == 0) {
                            col = (ushort)COL_BLUE::instance.shortValue;
                        } else if (this->grid[gx][gy].unknownNonZero01 != 0) {
                            col = (ushort)COL_VIVID_BLUE::instance.shortValue;
                        } else if (this->grid[gx][gy].field_0x6c != 0) {
                            col = (ushort)COL_RED::instance.shortValue;
                        } else {
                            col = (ushort)COL_LIME::instance.shortValue;
                        }
                        MACRO_CALL_MEMBER(
                            UI::Rendering::PencilRenderCore_Func::drawColorBox, DAT_PencilRenderCore::ptr)(
                            x + gx * 10 + 1, y + gy * 10 + 1, x + gx * 10 + 9, y + gy * 10 + 9, col);
                    } else if (mode == 9) {
                        if (this->grid[gx][gy].field_0x74 != 0) {
                            col = (ushort)COL_RED::instance.shortValue;
                        } else if (this->grid[gx][gy].unknownNonZero01 != 0) {
                            col = (ushort)COL_VIVID_BLUE::instance.shortValue;
                        } else if (this->grid[gx][gy].separateAreaID == 0) {
                            col = (ushort)COL_BLUE::instance.shortValue;
                        } else {
                            col = (ushort)COL_LIME::instance.shortValue;
                        }
                        MACRO_CALL_MEMBER(
                            UI::Rendering::PencilRenderCore_Func::drawColorBox, DAT_PencilRenderCore::ptr)(
                            x + gx * 10 + 1, y + gy * 10 + 1, x + gx * 10 + 9, y + gy * 10 + 9, col);
                    }
                }
            }
        }
    }

} // namespace Map
} // namespace OpenSHC
