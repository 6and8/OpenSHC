#include "../SFX.func.hpp"

#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Game/Resources/ResourceType.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"

namespace OpenSHC {
namespace Audio {
    namespace SFX {

        using namespace OpenSHC::Game::Resources;

        // FUNCTION: STRONGHOLDCRUSADER 0x0044A830
        int ComputePlayerPoints1(int playerID)
        {
            int const goldPoints = DAT_GameState::instance.playerDataArray[playerID].currentResources[RT_GOLD] / 10;
            int const troopPoints = DAT_GameState::instance.playerDataArray[playerID].totalTroopValue;
            int foodPoints
                = MACRO_CALL_MEMBER(Game::GameStateStructures_Func::getSalePriceOfGood, DAT_GameState::ptr)(RT_APPLE)
                * DAT_GameState::instance.playerDataArray[playerID].currentResources[RT_APPLE];
            foodPoints
                += MACRO_CALL_MEMBER(Game::GameStateStructures_Func::getSalePriceOfGood, DAT_GameState::ptr)(RT_MEAT)
                * DAT_GameState::instance.playerDataArray[playerID].currentResources[RT_MEAT];
            foodPoints
                += MACRO_CALL_MEMBER(Game::GameStateStructures_Func::getSalePriceOfGood, DAT_GameState::ptr)(RT_CHEESE)
                * DAT_GameState::instance.playerDataArray[playerID].currentResources[RT_CHEESE];
            foodPoints
                += MACRO_CALL_MEMBER(Game::GameStateStructures_Func::getSalePriceOfGood, DAT_GameState::ptr)(RT_BREAD)
                * DAT_GameState::instance.playerDataArray[playerID].currentResources[RT_BREAD];
            foodPoints /= 10;
            int weaponPoints = MACRO_CALL_MEMBER(
                                   Game::GameStateStructures_Func::getSalePriceOfGood, DAT_GameState::ptr)(RT_IRONARMOR)
                * DAT_GameState::instance.playerDataArray[playerID].currentResources[RT_IRONARMOR];
            weaponPoints += MACRO_CALL_MEMBER(Game::GameStateStructures_Func::getSalePriceOfGood, DAT_GameState::ptr)(
                                RT_LEATHERARMOR)
                * DAT_GameState::instance.playerDataArray[playerID].currentResources[RT_LEATHERARMOR];
            weaponPoints
                += MACRO_CALL_MEMBER(Game::GameStateStructures_Func::getSalePriceOfGood, DAT_GameState::ptr)(RT_SWORD)
                * DAT_GameState::instance.playerDataArray[playerID].currentResources[RT_SWORD];
            weaponPoints
                += MACRO_CALL_MEMBER(Game::GameStateStructures_Func::getSalePriceOfGood, DAT_GameState::ptr)(RT_MACE)
                * DAT_GameState::instance.playerDataArray[playerID].currentResources[RT_MACE];
            weaponPoints
                += MACRO_CALL_MEMBER(Game::GameStateStructures_Func::getSalePriceOfGood, DAT_GameState::ptr)(RT_PIKE)
                * DAT_GameState::instance.playerDataArray[playerID].currentResources[RT_PIKE];
            weaponPoints
                += MACRO_CALL_MEMBER(Game::GameStateStructures_Func::getSalePriceOfGood, DAT_GameState::ptr)(RT_SPEAR)
                * DAT_GameState::instance.playerDataArray[playerID].currentResources[RT_SPEAR];
            weaponPoints += MACRO_CALL_MEMBER(Game::GameStateStructures_Func::getSalePriceOfGood, DAT_GameState::ptr)(
                                RT_CROSSBOW)
                * DAT_GameState::instance.playerDataArray[playerID].currentResources[RT_CROSSBOW];
            weaponPoints
                += MACRO_CALL_MEMBER(Game::GameStateStructures_Func::getSalePriceOfGood, DAT_GameState::ptr)(RT_BOW)
                * DAT_GameState::instance.playerDataArray[playerID].currentResources[RT_BOW];
            weaponPoints /= 10;
            int materialPoints
                = MACRO_CALL_MEMBER(Game::GameStateStructures_Func::getSalePriceOfGood, DAT_GameState::ptr)(RT_FLOUR)
                * DAT_GameState::instance.playerDataArray[playerID].currentResources[RT_FLOUR];
            materialPoints
                += MACRO_CALL_MEMBER(Game::GameStateStructures_Func::getSalePriceOfGood, DAT_GameState::ptr)(RT_ALE)
                * DAT_GameState::instance.playerDataArray[playerID].currentResources[RT_ALE];
            materialPoints += MACRO_CALL_MEMBER(Game::GameStateStructures_Func::getSalePriceOfGood, DAT_GameState::ptr)(
                                  RT_PARTIALPITCH)
                * DAT_GameState::instance.playerDataArray[playerID].currentResources[RT_PARTIALPITCH];
            materialPoints
                += MACRO_CALL_MEMBER(Game::GameStateStructures_Func::getSalePriceOfGood, DAT_GameState::ptr)(RT_IRON)
                * DAT_GameState::instance.playerDataArray[playerID].currentResources[RT_IRON];
            materialPoints
                += MACRO_CALL_MEMBER(Game::GameStateStructures_Func::getSalePriceOfGood, DAT_GameState::ptr)(RT_STONE)
                * DAT_GameState::instance.playerDataArray[playerID].currentResources[RT_STONE];
            materialPoints
                += MACRO_CALL_MEMBER(Game::GameStateStructures_Func::getSalePriceOfGood, DAT_GameState::ptr)(RT_HOPS)
                * DAT_GameState::instance.playerDataArray[playerID].currentResources[RT_HOPS];
            materialPoints
                += MACRO_CALL_MEMBER(Game::GameStateStructures_Func::getSalePriceOfGood, DAT_GameState::ptr)(RT_WOOD)
                * DAT_GameState::instance.playerDataArray[playerID].currentResources[RT_WOOD];
            materialPoints /= 10;
            return DAT_GameState::instance.playerDataArray[playerID].currentPopulation * 10 + materialPoints
                + weaponPoints + foodPoints + troopPoints + goldPoints;
        }

    }
}
}
