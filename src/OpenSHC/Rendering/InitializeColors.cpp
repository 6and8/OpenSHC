#include "OpenSHC/Rendering.func.hpp"
#include "OpenSHC/UI/Rendering.func.hpp"
#include "OpenSHC/Rendering/ColorMode.hpp"

#include "OpenSHC/Globals/COL_BLACK.hpp"
#include "OpenSHC/Globals/COL_BLUE.hpp"
#include "OpenSHC/Globals/COL_BRIGHT_YELLOW.hpp"
#include "OpenSHC/Globals/COL_DARK_CYAN_GREY.hpp"
#include "OpenSHC/Globals/COL_DARK_GRAYISH_GREEN.hpp"
#include "OpenSHC/Globals/COL_DARK_GREEN.hpp"
#include "OpenSHC/Globals/COL_DARK_LIME.hpp"
#include "OpenSHC/Globals/COL_DARK_RED.hpp"
#include "OpenSHC/Globals/COL_GREYISH_YELLOW.hpp"
#include "OpenSHC/Globals/COL_LIGHT_GREY.hpp"
#include "OpenSHC/Globals/COL_LIME.hpp"
#include "OpenSHC/Globals/COL_MAGENTA.hpp"
#include "OpenSHC/Globals/COL_MODERATE_GREEN.hpp"
#include "OpenSHC/Globals/COL_RED.hpp"
#include "OpenSHC/Globals/COL_VERY_DARK_GREY.hpp"
#include "OpenSHC/Globals/COL_VERY_SOFT_YELLOW.hpp"
#include "OpenSHC/Globals/COL_VIVID_BLUE.hpp"
#include "OpenSHC/Globals/COL_WHITE.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"

namespace OpenSHC {
namespace Rendering {

    // FUNCTION: STRONGHOLDCRUSADER 0x00467890
    void InitializeColors()
    {
        COL_BLUE::instance.shortValue = 31;
        COL_BLACK::instance.shortValue = 0;
        if (DAT_WindowAndDirectDraw::instance.colorBitMode == RGB_555) {
            COL_RED::instance.shortValue = (short)0xFC00;
            COL_LIME::instance.shortValue = (short)0x03E0;
            COL_DARK_GREEN::instance.shortValue = (short)0x01E0;
            COL_WHITE::instance.shortValue = (short)0x7FFF;
            COL_BRIGHT_YELLOW::instance.shortValue = (short)0x7307;
            COL_MODERATE_GREEN::instance.shortValue = (short)0x3307;
            COL_DARK_CYAN_GREY::instance.shortValue = (short)0x35EF;
            COL_VERY_DARK_GREY::instance.shortValue = (short)0x1CE7;
            COL_MAGENTA::instance.shortValue = (short)0x7C1F;
            COL_VIVID_BLUE::instance.shortValue = (short)0x125F;
            COL_VERY_SOFT_YELLOW::instance.shortValue = (short)0x77B7;
        } else {
            COL_RED::instance.shortValue = (short)0xF800;
            COL_LIME::instance.shortValue = (short)0x07C0;
            COL_DARK_GREEN::instance.shortValue = (short)0x03C0;
            COL_WHITE::instance.shortValue = (short)0xFFFF;
            COL_BRIGHT_YELLOW::instance.shortValue = (short)0xC607;
            COL_MODERATE_GREEN::instance.shortValue = (short)0x4607;
            COL_DARK_CYAN_GREY::instance.shortValue = (short)0x7BCF;
            COL_VERY_DARK_GREY::instance.shortValue = (short)0x39C7;
            COL_MAGENTA::instance.shortValue = (short)0xF81F;
            COL_VIVID_BLUE::instance.shortValue = (short)0x24BF;
            COL_VERY_SOFT_YELLOW::instance.shortValue = (short)0xEF77;
        }
        COL_LIGHT_GREY::instance.shortValue = (short)MACRO_CALL(UI::Rendering_Func::TransformToCurrentModeColor)(192, 192, 192);
        COL_GREYISH_YELLOW::instance.shortValue = (short)MACRO_CALL(UI::Rendering_Func::TransformToCurrentModeColor)(215, 210, 164);
        COL_DARK_LIME::instance.shortValue = (short)MACRO_CALL(UI::Rendering_Func::TransformToCurrentModeColor)(41, 117, 32);
        COL_DARK_GRAYISH_GREEN::instance.shortValue = (short)MACRO_CALL(UI::Rendering_Func::TransformToCurrentModeColor)(104, 116, 88);
        COL_DARK_RED::instance.shortValue = (short)MACRO_CALL(UI::Rendering_Func::TransformToCurrentModeColor)(140, 0, 0);
    }

}
}
