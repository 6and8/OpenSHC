#include "OpenSHC/Game/Skirmish.func.hpp"
#include "OpenSHC/IO.func.hpp"

#include "OpenSHC/Globals/DAT_SkMasters2DataArray.hpp"
#include "OpenSHC/Globals/DAT_SkMasters2Data_Count.hpp"

namespace OpenSHC {
namespace Game {
    namespace Skirmish {

        // FUNCTION: STRONGHOLDCRUSADER 0x004D5370
        void SkirmishLeaderboard_DeleteEntry(int index)
        {
            if (index < 0 || DAT_SkMasters2Data_Count::instance <= index) {
                return;
            }
            for (int i = index; i < DAT_SkMasters2Data_Count::instance - 1; ++i) {
                DAT_SkMasters2DataArray::instance[i] = DAT_SkMasters2DataArray::instance[i + 1];
            }
            DAT_SkMasters2Data_Count::instance -= 1;
            MACRO_CALL(OpenSHC::IO_Func::WriteSkMasters2)();
        }

    }
}
}
