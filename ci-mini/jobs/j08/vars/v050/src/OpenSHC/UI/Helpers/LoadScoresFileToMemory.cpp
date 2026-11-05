#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/UI/Helpers.func.hpp"
#include "OpenSHC/string-literals.hpp"

#include "OpenSHC/Globals/DAT_MissionScores.hpp"

namespace OpenSHC {
namespace UI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004DAF50
    void Helpers::LoadScoresFileToMemory(char* filename)
    {
        FILE* const file = MACRO_CALL(OpenSHC::OS_Func::_fopen)(filename, s_rb_005a4e18);
        if (file) {
            MACRO_CALL(OpenSHC::OS_Func::_fseek)(file, 4, SEEK_SET);
            for (int i = 0; i != 10; ++i) {
                MACRO_CALL(OpenSHC::OS_Func::_fread)(&DAT_MissionScores::instance[i], 4, 1, file);
            }
            MACRO_CALL(OpenSHC::OS_Func::_fclose)(file);
        }
    }

}
}
