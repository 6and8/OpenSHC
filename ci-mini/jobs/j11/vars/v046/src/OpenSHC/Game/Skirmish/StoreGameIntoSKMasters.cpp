#include "OpenSHC/Game/Skirmish.func.hpp"
#include "OpenSHC/IO.func.hpp"

#include "OpenSHC/Globals/DAT_SkMasterDataEntry.hpp"
#include "OpenSHC/Globals/DAT_SkMasters2DataArray.hpp"
#include "OpenSHC/Globals/DAT_SkMasters2Data_Count.hpp"

namespace OpenSHC {
namespace Game {
    namespace Skirmish {

        // FUNCTION: STRONGHOLDCRUSADER 0x004D52A0
        void StoreGameIntoSKMasters(int score)
        {
            if (!MACRO_CALL(Skirmish_Func::StoreCurrentGameIntoTemporarySKMasterEntry)(score)) {
                return;
            }
            int const count = DAT_SkMasters2Data_Count::instance;
            int insertAt = -1;
            if (count <= 0) {
                insertAt = 0;
            }
            if (count < 250) {
                insertAt = count;
            }
            if (insertAt != 0) {
                for (int i = 0; i < count; ++i) {
                    if (DAT_SkMasterDataEntry::instance.skMasterScore
                        > DAT_SkMasters2DataArray::instance[i].skMasterScore) {
                        insertAt = i;
                        break;
                    }
                }
                if (insertAt == -1) {
                    return;
                }
            }
            for (int i = count; i > insertAt; --i) {
                if (i <= 249) {
                    DAT_SkMasters2DataArray::instance[i] = DAT_SkMasters2DataArray::instance[i - 1];
                }
            }
            OpenSHC::IO::SkMasterDataEntry* instancePtr = &DAT_SkMasters2DataArray::instance[insertAt];
            *instancePtr = DAT_SkMasterDataEntry::instance;
            if ((int)DAT_SkMasters2Data_Count::instance < 250) {
                DAT_SkMasters2Data_Count::instance += 1;
            }
            MACRO_CALL(OpenSHC::IO_Func::WriteSkMasters2)();
        }

    }
}
}
