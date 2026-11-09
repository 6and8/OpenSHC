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
            if (index < 0 || index >= DAT_SkMasters2Data_Count::instance) {
                return;
            }
            for (int i = index; i < DAT_SkMasters2Data_Count::instance - 1; ++i) {
                OpenSHC::IO::SkMasterDataEntry* entryPtr = &DAT_SkMasters2DataArray::instance[i];
                *entryPtr = DAT_SkMasters2DataArray::instance[i + 1];
            }
            MACRO_CALL(OpenSHC::IO_Func::WriteSkMasters2)();
            DAT_SkMasters2Data_Count::instance -= 1;
        }

    }
}
}
