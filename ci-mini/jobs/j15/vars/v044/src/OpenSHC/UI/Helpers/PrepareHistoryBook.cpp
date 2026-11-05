#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/UI/Helpers.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/string-literals.hpp"

#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/INT_ARRAY_00eb0b28.hpp"

namespace OpenSHC {
namespace UI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004DB210
    void Helpers::PrepareHistoryBook()
    {
        int* totalLoadedGfxPtr = &DAT_TextureRenderCoreObject::instance.totalLoadedGfx;
        *totalLoadedGfxPtr = 0;
        MACRO_CALL_MEMBER(Rendering::TextureRenderCore_Func::loadGfxFile, DAT_TextureRenderCoreObject::ptr)(
            s_sand_tgx_005ab080);
        MACRO_CALL_MEMBER(Rendering::TextureRenderCore_Func::loadGfxFile, DAT_TextureRenderCoreObject::ptr)(
            s_pc0_tgx_005ab078);
        MACRO_CALL_MEMBER(Rendering::TextureRenderCore_Func::loadGfxFile, DAT_TextureRenderCoreObject::ptr)(
            s_pc1_tgx_005ab070);
        MACRO_CALL_MEMBER(Rendering::TextureRenderCore_Func::loadGfxFile, DAT_TextureRenderCoreObject::ptr)(
            s_pc2_tgx_005ab068);
        MACRO_CALL_MEMBER(Rendering::TextureRenderCore_Func::loadGfxFile, DAT_TextureRenderCoreObject::ptr)(
            s_pc3_tgx_005ab060);
        MACRO_CALL_MEMBER(Rendering::TextureRenderCore_Func::loadGfxFile, DAT_TextureRenderCoreObject::ptr)(
            s_pc4_tgx_005ab058);
        MACRO_CALL_MEMBER(Rendering::TextureRenderCore_Func::loadGfxFile, DAT_TextureRenderCoreObject::ptr)(
            s_pc5_tgx_005ab050);
        MACRO_CALL_MEMBER(Rendering::TextureRenderCore_Func::loadGfxFile, DAT_TextureRenderCoreObject::ptr)(
            s_pc6_tgx_005ab048);
        MACRO_CALL_MEMBER(Rendering::TextureRenderCore_Func::loadGfxFile, DAT_TextureRenderCoreObject::ptr)(
            s_pc7_tgx_005ab040);
        for (int i = 0; i < 48; ++i) {
            INT_ARRAY_00eb0b28::instance[i][0] = MACRO_CALL(OpenSHC::OS_Func::_rand)() % 900 << 8;
            INT_ARRAY_00eb0b28::instance[i][1] = MACRO_CALL(OpenSHC::OS_Func::_rand)() % 600 << 8;
            INT_ARRAY_00eb0b28::instance[i][2] = MACRO_CALL(OpenSHC::OS_Func::_rand)() % 8;
            INT_ARRAY_00eb0b28::instance[i][3] = MACRO_CALL(OpenSHC::OS_Func::_rand)() % 10 + 10;
        }
    }

}
}
