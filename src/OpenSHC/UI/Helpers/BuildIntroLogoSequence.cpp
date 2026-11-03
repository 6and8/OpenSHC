#include "OpenSHC/UI/Credits.func.hpp"
#include "OpenSHC/UI/Helpers.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/string-literals.hpp"

#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"

namespace OpenSHC {
namespace UI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004DB180
    void Helpers::BuildIntroLogoSequence(undefined4 param_1, undefined4 param_2)
    {
        DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
        MACRO_CALL_MEMBER(Rendering::TextureRenderCore_Func::loadGfxFile, DAT_TextureRenderCoreObject::ptr)(
            s_logo1_tgx_005a1f74);
        MACRO_CALL_MEMBER(Rendering::TextureRenderCore_Func::loadGfxFile, DAT_TextureRenderCoreObject::ptr)(
            s_logo2_tgx_005a1f68);
        MACRO_CALL(Credits_Func::AppendCreditsSegmentEndCommand)();
        MACRO_CALL(Credits_Func::AppendCreditsSoundEntry)(1, 0);
        MACRO_CALL(Credits_Func::AppendCreditsListTerminator)();
        MACRO_CALL(Credits_Func::AppendCreditsCommand)(0x12);
        MACRO_CALL(Credits_Func::AppendCreditsSoundStreamCommand)(0x14, (OpenSHC::Audio::MSS::enums::SHC_SoundStream)0);
        MACRO_CALL(Credits_Func::AppendCreditsSoundStreamCommand)(1, (OpenSHC::Audio::MSS::enums::SHC_SoundStream)0x3c);
        MACRO_CALL(Credits_Func::AppendCreditsCommand)(0x13);
        MACRO_CALL(Credits_Func::AppendCreditsSoundStreamCommand)(0x14, (OpenSHC::Audio::MSS::enums::SHC_SoundStream)0);
        MACRO_CALL(Credits_Func::AppendCreditsPauseCommand)();
        MACRO_CALL(Credits_Func::AppendCreditsSoundStreamCommand)(8, (OpenSHC::Audio::MSS::enums::SHC_SoundStream)0);
    }

}
}
