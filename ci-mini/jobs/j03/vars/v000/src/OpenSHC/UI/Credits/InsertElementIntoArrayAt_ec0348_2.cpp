#include "OpenSHC/UI/Credits.func.hpp"

#include "OpenSHC/Globals/DAT_ARRAY_00ec0348.hpp"

namespace OpenSHC {
namespace UI {
    namespace Credits {

        // FUNCTION: STRONGHOLDCRUSADER 0x004DAE90
        void InsertElementIntoArrayAt_ec0348_2(
            int state, int xSpace, int field8, int field10, int x, int y, int fadeMode, int width, int field9)
        {
            if (state != 2) {
                return;
            }
            int index = -1;
            for (int i = 0; i < 24; i++) {
                if (DAT_ARRAY_00ec0348::instance[i].type == 0) {
                    index = i;
                    break;
                }
            }
            if (index == -1) {
                return;
            }
            DAT_ARRAY_00ec0348::instance[index].xSpace = xSpace;
            DAT_ARRAY_00ec0348::instance[index].blendStrength = 0.0f;
            DAT_ARRAY_00ec0348::instance[index].field_0x20 = field8;
            DAT_ARRAY_00ec0348::instance[index].x = x;
            DAT_ARRAY_00ec0348::instance[index].y = y;
            DAT_ARRAY_00ec0348::instance[index].width = width;
            DAT_ARRAY_00ec0348::instance[index].field_0x24 = field9;
            DAT_ARRAY_00ec0348::instance[index].field_0x28 = field10;
            DAT_ARRAY_00ec0348::instance[index].type = 2;
            DAT_ARRAY_00ec0348::instance[index].fadeMode = fadeMode;
            DAT_ARRAY_00ec0348::instance[index].field_0x1c = 7;
            if (fadeMode == 1) {
                float* blendStrengthPtr = &DAT_ARRAY_00ec0348::instance[index].blendStrength;
                *blendStrengthPtr = 31.0f;
            } else if (fadeMode == 2) {
                float* blendStrengthPtr = &DAT_ARRAY_00ec0348::instance[index].blendStrength;
                *blendStrengthPtr = 1.0f;
            }
        }

    }
}
}
