#include "OpenSHC/UI/Helpers.func.hpp"

#include "OpenSHC/Globals/DAT_00b960bc.hpp"
#include "OpenSHC/Globals/DAT_SiegeInformationArray_2.hpp"
#include "OpenSHC/Globals/INT_00b960b8.hpp"
#include "OpenSHC/Globals/INT_00b960c0.hpp"
#include "OpenSHC/Globals/INT_00b960c4.hpp"

namespace OpenSHC {
namespace UI {

    // FUNCTION: STRONGHOLDCRUSADER 0x0042C190
    void Helpers::ClearSiegeInformationArray2()
    {
        DAT_00b960bc::instance = 0;
        INT_00b960b8::instance = 0;
        INT_00b960c0::instance = 0;
        INT_00b960c4::instance = 0;
        for (int i = 0; i < 4; ++i) {
            // only the first 11 counts of each row are cleared
            int* const counts = &DAT_SiegeInformationArray_2::instance[i][0][0];
            for (int j = 0; j < 11; ++j) {
                counts[j] = 0;
            }
        }
    }

}
}
