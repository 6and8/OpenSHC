#include "OpenSHC/UI/Helpers.func.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_UnitTypeRelatedCounter.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace UI {

    // FUNCTION: STRONGHOLDCRUSADER 0x00440360
    void Helpers::CountPlayerUnitsByType()
    {
        int const player = DAT_GameSynchronyState::instance.currentPlayerSlotID;
        memset(DAT_UnitTypeRelatedCounter::instance, 0, sizeof(DAT_UnitTypeRelatedCounter::instance));
        for (int i = 1; i < DAT_UnitsState::instance.maxUnitCount; ++i) {
            if (DAT_UnitsState::instance.units[i].logicalState != 0 && DAT_UnitsState::instance.units[i].owner == player
                && DAT_UnitsState::instance.units[i].isStalked == 0) {
                int const unitType = DAT_UnitsState::instance.units[i].unitType;
                if (unitType >= 1 && (unitType <= 0x42 || unitType >= 0x46)) {
                    DAT_UnitTypeRelatedCounter::instance[unitType] += 1;
                }
            }
        }
    }

}
}
