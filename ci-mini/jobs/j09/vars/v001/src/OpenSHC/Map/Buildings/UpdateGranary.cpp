#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Map/Buildings.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/Game/Resources/ResourceType.hpp"

#include "OpenSHC/Globals/DAT_AICState.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_CurrentBuildingID.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x00415110
    void Buildings::UpdateGranary()
    {
        OpenSHC::Map::Buildings::Building const buildingsValue = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance];
        int const owner = buildingsValue.owner;
        int totalFood = 0;
        int bread = 0;
        int cheese = 0;
        int meat = 0;
        int apples = 0;
        int sprite = 1;
        int resourceGiven = 0;
        MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::addBuildingToTargetableBuildings, DAT_AICState::ptr)(
            DAT_CurrentBuildingID::instance);
        MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::addBuildingInRegistry, DAT_GameState::ptr)(
            DAT_CurrentBuildingID::instance);

        // Hand out one unit of each starting food while the granary has room
        if ((DAT_GameCore::instance.mapTimeInTicks & 3) == 0
            && DAT_GameCore::instance.gameMode_2 != OpenSHC::Game::GM_EDITOR
            && DAT_GameCore::instance.gameMode_2 != OpenSHC::Game::GM_SIEGE_THAT
            && DAT_GameState::instance.playerDataArray[owner].someCountdown01 == 0) {
            if (DAT_GameState::instance.playerDataArray[owner].startResources[OpenSHC::Game::Resources::RT_BREAD] > 0
                && (int)MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::computeResourceSumForBuilding,
                       DAT_BuildingsState::ptr)(DAT_CurrentBuildingID::instance)
                    < 250) {
                DAT_GameState::instance.playerDataArray[owner].currentResources[OpenSHC::Game::Resources::RT_BREAD]
                    += 1;
                DAT_GameState::instance.playerDataArray[owner].startResources[OpenSHC::Game::Resources::RT_BREAD] -= 1;
                buildingsValue
                    .resources[OpenSHC::Game::Resources::RT_BREAD] += 1;
                buildingsValue.resourceRelatedCountDown = 100;
                resourceGiven = 1;
            }
            if (DAT_GameState::instance.playerDataArray[owner].startResources[OpenSHC::Game::Resources::RT_CHEESE] > 0
                && (int)MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::computeResourceSumForBuilding,
                       DAT_BuildingsState::ptr)(DAT_CurrentBuildingID::instance)
                    < 250) {
                DAT_GameState::instance.playerDataArray[owner].currentResources[OpenSHC::Game::Resources::RT_CHEESE]
                    += 1;
                DAT_GameState::instance.playerDataArray[owner].startResources[OpenSHC::Game::Resources::RT_CHEESE] -= 1;
                buildingsValue
                    .resources[OpenSHC::Game::Resources::RT_CHEESE] += 1;
                buildingsValue.resourceRelatedCountDown = 100;
                resourceGiven = 1;
            }
            if (DAT_GameState::instance.playerDataArray[owner].startResources[OpenSHC::Game::Resources::RT_MEAT] > 0
                && (int)MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::computeResourceSumForBuilding,
                       DAT_BuildingsState::ptr)(DAT_CurrentBuildingID::instance)
                    < 250) {
                DAT_GameState::instance.playerDataArray[owner].currentResources[OpenSHC::Game::Resources::RT_MEAT] += 1;
                DAT_GameState::instance.playerDataArray[owner].startResources[OpenSHC::Game::Resources::RT_MEAT] -= 1;
                buildingsValue
                    .resources[OpenSHC::Game::Resources::RT_MEAT] += 1;
                buildingsValue.resourceRelatedCountDown = 100;
                resourceGiven = 1;
            }
            if (DAT_GameState::instance.playerDataArray[owner].startResources[OpenSHC::Game::Resources::RT_APPLE] > 0
                && (int)MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::computeResourceSumForBuilding,
                       DAT_BuildingsState::ptr)(DAT_CurrentBuildingID::instance)
                    < 250) {
                DAT_GameState::instance.playerDataArray[owner].currentResources[OpenSHC::Game::Resources::RT_APPLE]
                    += 1;
                DAT_GameState::instance.playerDataArray[owner].startResources[OpenSHC::Game::Resources::RT_APPLE] -= 1;
                buildingsValue
                    .resources[OpenSHC::Game::Resources::RT_APPLE] += 1;
                buildingsValue.resourceRelatedCountDown = 100;
                resourceGiven = 1;
            }
            if (resourceGiven != 0) {
                MACRO_CALL_MEMBER(
                    OpenSHC::Map::Buildings::BuildingsState_Func::countPlayerResources, DAT_BuildingsState::ptr)(owner);
            }
        }
        if ((int)MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::computeResourceSumForBuilding,
                DAT_BuildingsState::ptr)(DAT_CurrentBuildingID::instance)
            < 230) {
            DAT_GameState::instance.playerDataArray[owner].granaryIsAlmostFilledUp = 0;
        }
        if (DAT_GameState::instance.mapAndTime.playerTeams[owner]
                == DAT_GameState::instance.mapAndTime.playerTeams[DAT_GameSynchronyState::instance.currentPlayerSlotID]
            || (DAT_GameSynchronyState::instance.currentPlayerFullIDArray
                        [buildingsValue.owner]
                    == -1
                && DAT_GameSynchronyState::instance
                        .currentAIArray[buildingsValue.owner]
                    != 0)) {
            if (buildingsValue.resourceRelatedCountDown != 0) {
                buildingsValue.buildingIsVisuallyActive = 1;
                buildingsValue.resourceRelatedCountDown -= 1;
            } else if (DAT_BuildingsState::instance.isFirstTickInLoop != 0) {
                buildingsValue.buildingIsVisuallyActive = 0;
            }
            MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::updateVisuallyActiveState,
                DAT_BuildingsState::ptr)(DAT_CurrentBuildingID::instance);
        }
        buildingsValue.renderAnimation = 0;
        buildingsValue.displayOwnerFlag = 0;
        buildingsValue.extraAnimationSprite1 = 0;
        buildingsValue.extraAnimationSprite2 = 0;
        buildingsValue.extraAnimationSprite3 = 0;
        buildingsValue.extraAnimationSprite4 = 0;
        buildingsValue.extraOverlayImage1 = 0;
        buildingsValue.extraOverlayImage2 = 0;
        buildingsValue.extraOverlayImage3 = 0;
        buildingsValue.extraOverlayImage4 = 0;
        buildingsValue.extraOverlayImage5 = 0;
        buildingsValue.extraOverlayImage6 = 0;
        buildingsValue.extraOverlayImage7 = 0;
        buildingsValue.extraOverlayImage8 = 0;
        buildingsValue.extraOverlayImage9 = 0;
        buildingsValue.flagSlot.overlayImage = 0;
        buildingsValue.overlayImageID = 0;
        buildingsValue.extraOverlayImage10 = 0;
        if (DAT_GameState::instance.playerDataArray[owner].isFoodTypeBanned[0] == 0) {
            bread = buildingsValue
                        .resources[OpenSHC::Game::Resources::RT_BREAD];
            if (bread != 0) {
                totalFood += bread;
            }
        }
        if (DAT_GameState::instance.playerDataArray[owner].isFoodTypeBanned[1] == 0) {
            cheese = buildingsValue
                         .resources[OpenSHC::Game::Resources::RT_CHEESE];
            if (cheese != 0) {
                totalFood += cheese;
            }
        }
        if (DAT_GameState::instance.playerDataArray[owner].isFoodTypeBanned[2] == 0) {
            meat = buildingsValue
                       .resources[OpenSHC::Game::Resources::RT_MEAT];
            if (meat != 0) {
                totalFood += meat;
            }
        }
        if (DAT_GameState::instance.playerDataArray[owner].isFoodTypeBanned[3] == 0) {
            apples = buildingsValue
                         .resources[OpenSHC::Game::Resources::RT_APPLE];
            if (apples != 0) {
                totalFood += apples;
            }
        }
        DAT_GameState::instance.playerDataArray[owner].breadCount += bread;
        DAT_GameState::instance.playerDataArray[owner].cheeseCount += cheese;
        DAT_GameState::instance.playerDataArray[owner].meatCount += meat;
        DAT_GameState::instance.playerDataArray[owner].appleCount += apples;
        DAT_GameState::instance.playerDataArray[owner].totalFood += totalFood;

        bread = buildingsValue
                    .resources[OpenSHC::Game::Resources::RT_BREAD];
        cheese = buildingsValue
                     .resources[OpenSHC::Game::Resources::RT_CHEESE];
        meat = buildingsValue
                   .resources[OpenSHC::Game::Resources::RT_MEAT];
        apples = buildingsValue
                     .resources[OpenSHC::Game::Resources::RT_APPLE];
        int const storedFood = apples + meat + cheese + bread;
        if (buildingsValue.buildingIsVisuallyActive
            != buildingsValue.oldVisualActiveState) {
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::updateBuildingGraphicsLayer, DAT_TileMapState::ptr)(
                DAT_CurrentBuildingID::instance);
            buildingsValue.oldVisualActiveState
                = buildingsValue.buildingIsVisuallyActive;
        }
        if (storedFood <= 0
            || buildingsValue.buildingIsVisuallyActive == 0) {
            return;
        }

        // Each of the 16 pile slots shows the most plentiful food left, up to a per-type pile size
        buildingsValue.displayOwnerFlag = 1;
        for (int slot = 0; slot < 16; ++slot) {
            int foodType = 0;
            int amount = 0;
            if (bread > 0) {
                foodType = 1;
                amount = bread;
            }
            if (cheese > amount) {
                foodType = 2;
                amount = cheese;
            }
            if (meat > amount) {
                foodType = 3;
                amount = meat;
            }
            if (apples > amount) {
                foodType = 4;
                amount = apples;
            }
            if (foodType <= 0) {
                return;
            }
            if (foodType == 1) {
                if (amount > 32) {
                    amount = 32;
                }
            } else if (foodType == 2) {
                if (amount > 16) {
                    amount = 16;
                }
            } else if (foodType == 3) {
                if (amount > 16) {
                    amount = 16;
                }
            } else if (foodType == 4) {
                if (amount > 8) {
                    amount = 8;
                }
            }
            if (foodType == 1) {
                bread -= amount;
                sprite = amount;
            } else if (foodType == 2) {
                cheese -= amount;
                sprite = amount + 160;
            } else if (foodType == 3) {
                meat -= amount;
                sprite = amount + 176;
            } else if (foodType == 4) {
                apples -= amount;
                sprite = amount + 152;
            }
            if (slot == 0) {
                buildingsValue.extraAnimationSprite1 = sprite;
            } else if (slot == 1) {
                buildingsValue.extraAnimationSprite2 = sprite;
            } else if (slot == 2) {
                buildingsValue.extraAnimationSprite3 = sprite;
            } else if (slot == 3) {
                buildingsValue.extraAnimationSprite4 = sprite;
            } else if (slot == 4) {
                buildingsValue.extraOverlayImage1 = sprite;
            } else if (slot == 5) {
                buildingsValue.extraOverlayImage2 = sprite;
            } else if (slot == 6) {
                buildingsValue.extraOverlayImage3 = sprite;
            } else if (slot == 7) {
                buildingsValue.extraOverlayImage4 = sprite;
            } else if (slot == 8) {
                buildingsValue.extraOverlayImage5 = sprite;
            } else if (slot == 9) {
                buildingsValue.extraOverlayImage6 = sprite;
            } else if (slot == 10) {
                buildingsValue.extraOverlayImage7 = sprite;
            } else if (slot == 11) {
                buildingsValue.extraOverlayImage8 = sprite;
            } else if (slot == 12) {
                buildingsValue.extraOverlayImage9 = sprite;
            } else if (slot == 13) {
                buildingsValue.flagSlot.overlayImage = sprite;
            } else if (slot == 14) {
                buildingsValue.overlayImageID = sprite;
            } else if (slot == 15) {
                buildingsValue.extraOverlayImage10 = sprite;
            }
        }
    }

}
}
