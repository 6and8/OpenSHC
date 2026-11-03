#include "OpenSHC/UI/Helpers.func.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace UI {

    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x00465040
    BOOLEnum Helpers::HasEnoughGold(int unitType)
    {
        int cost = 0;
        if (unitType == OpenSHC::Map::Units::UT_E_ENGINEER) {
            cost = 30;
        } else if (unitType == OpenSHC::Map::Units::UT_E_LADDER) {
            cost = 4;
        } else if (unitType == OpenSHC::Map::Units::UT_E_MONK) {
            cost = 10;
        }
        return (BOOLEnum)(DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                              .currentResources[OpenSHC::Game::Resources::RT_GOLD]
            >= cost);
    }

}
}
