#include "OpenSHC/UI/Helpers.func.hpp"

#include "OpenSHC/Globals/DAT_SiegeInformationArray_2.hpp"
#include "OpenSHC/Globals/INT_ARRAY_00b960b8.hpp"

namespace OpenSHC {
namespace UI {

    // FUNCTION: STRONGHOLDCRUSADER 0x0042C190
    void Helpers::ClearSiegeInformationArray2()
    {
        INT_ARRAY_00b960b8::instance[0] = 0;
        INT_ARRAY_00b960b8::instance[1] = 0;
        INT_ARRAY_00b960b8::instance[2] = 0;
        INT_ARRAY_00b960b8::instance[3] = 0;
        int i = 0;
        if (i < 4) {
            do {
                // only the first 11 counts of each row are cleared
                int* const counts = &DAT_SiegeInformationArray_2::instance[i][0][0];
                for (int j = 0; j < 11; ++j) {
                    counts[j] = 0;
                }
                ++i;
            } while (i < 4);
        }
    }

}
}
