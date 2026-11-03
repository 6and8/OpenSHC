#include "OpenSHC/UI/Helpers.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_TribesState.hpp"

namespace OpenSHC {
namespace UI {

    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x00434340
    void Helpers::SetTribesPatrolButtonPressed(BOOLEnum pressed)
    {
        DAT_TribesState::instance.patrolButtonPressed = pressed;
    }

}
}
