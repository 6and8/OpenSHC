#include "OpenSHC/UI/Helpers.func.hpp"

#include "OpenSHC/Globals/DAT_ARRAY_00ec0348.hpp"
#include "OpenSHC/Globals/DAT_MouseState.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"

namespace OpenSHC {
namespace UI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004DC140
    int Helpers::FindCampaignMapHotspotAtMouse()
    {
        int const mouseY = DAT_MouseState::instance.screenSpaceY;
        int const mouseX = DAT_MouseState::instance.screenSpaceX;
        for (int i = 0; i < 24; ++i) {
            if ((DAT_ARRAY_00ec0348::instance[i].type == 3 || DAT_ARRAY_00ec0348::instance[i].type == 1)
                && mouseX - DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth >= DAT_ARRAY_00ec0348::instance[i].x
                && mouseX - DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth
                    < DAT_ARRAY_00ec0348::instance[i].x + DAT_ARRAY_00ec0348::instance[i].width
                && mouseY - DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight >= DAT_ARRAY_00ec0348::instance[i].y
                && mouseY - DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight
                    < DAT_ARRAY_00ec0348::instance[i].y + DAT_ARRAY_00ec0348::instance[i].height) {
                return DAT_ARRAY_00ec0348::instance[i].xSpace;
            }
        }
        return -1;
    }

}
}
