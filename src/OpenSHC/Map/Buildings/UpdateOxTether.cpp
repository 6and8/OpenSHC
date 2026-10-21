#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Map/Buildings.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Game/Resources/ResourceType.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"

#include "OpenSHC/Globals/DAT_AICState.hpp"
#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_CurrentBuildingID.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x0041CA00
    void Buildings::UpdateOxTether()
    {
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].renderAnimation = 0;
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].spriteID
            = DAT_BuildingDefinedData::instance.Building_Sprite_ID_Array_1
                  [DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].buildingType]
            + DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance]
                    .resources[OpenSHC::Game::Resources::RT_STONE]
                * 4;
        if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].spriteID
            != DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].oldVisualActiveState) {
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::updateBuildingGraphicsLayer, DAT_TileMapState::ptr)(
                DAT_CurrentBuildingID::instance);
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].oldVisualActiveState
                = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].spriteID;
        }
        MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::addBuildingToTargetableBuildings, DAT_AICState::ptr)(
            DAT_CurrentBuildingID::instance);
        MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::addBuildingInRegistry, DAT_GameState::ptr)(
            DAT_CurrentBuildingID::instance);
        int const buildingID = DAT_CurrentBuildingID::instance;
        if (DAT_GameSynchronyState::instance.currentGameMode != 0) {
            DAT_BuildingsState::instance.buildings[buildingID].displayOwnerFlag = 1;
            DAT_BuildingsState::instance.buildings[buildingID].flagSlot.overlayImage += 1;
            if (DAT_BuildingDefinedData::instance.SharedOverlayAnimationFrames
                    [DAT_BuildingsState::instance.buildings[buildingID].flagSlot.overlayImage / 2]
                <= 0) {
                DAT_BuildingsState::instance.buildings[buildingID].flagSlot.overlayImage = 0;
            }
            DAT_BuildingsState::instance.buildings[buildingID].overlayImageID
                = DAT_BuildingDefinedData::instance.SharedOverlayAnimationFrames
                      [DAT_BuildingsState::instance.buildings[buildingID].flagSlot.overlayImage / 2];
        } else {
            DAT_BuildingsState::instance.buildings[buildingID].overlayImageID = 0;
        }
        if (DAT_BuildingsState::instance.buildings[buildingID].outpostRelatedUnk4 > 0) {
            DAT_BuildingsState::instance.buildings[buildingID].outpostRelatedUnk4 -= 1;
            return;
        }
        if (DAT_BuildingsState::instance.buildings[buildingID].oxTetherRelatedUnitID <= 0) {
            if (DAT_BuildingsState::instance.buildings[buildingID].workerID[0] == 0) {
                return;
            }
            DAT_BuildingsState::instance.buildings[buildingID].animationTickCounter += 1;
            if (DAT_BuildingsState::instance.buildings[buildingID].animationTickCounter < 100) {
                return;
            }
            DAT_BuildingsState::instance.buildings[buildingID].animationTickCounter = 0;
            MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::setBuildingInitialEntryTileTry,
                DAT_BuildingsState::ptr)(buildingID, 1);
            MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::determineBuildingEntranceFromKeepArea,
                DAT_BuildingsState::ptr)(buildingID, 1, 1);
            if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].buildingEntryX != 0
                && DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].buildingEntryY != 0) {
                int const unitID = MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::spawnUnit,
                    DAT_UnitsState::ptr)(DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].owner,
                    0, DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].buildingEntryX * 8,
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].buildingEntryY * 8,
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].terrainHeightUnk,
                    OpenSHC::Map::Units::UT_QUARRYOX);
                if (unitID != 0) {
                    DAT_UnitsState::instance.units[unitID].workplaceBuildingUID
                        = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].uid;
                    DAT_UnitsState::instance.units[unitID].targetX_2
                        = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].buildingEntryX;
                    DAT_UnitsState::instance.units[unitID].targetY_2
                        = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].buildingEntryY;
                    DAT_UnitsState::instance.units[unitID].workplaceBuildingID_1 = DAT_CurrentBuildingID::instance;
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].oxTetherRelatedUnitID
                        = unitID;
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].oxTetherRelatedUnitUID
                        = DAT_UnitsState::instance.units[unitID].uid;
                }
            }
            MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::setBuildingInitialEntryTileTry,
                DAT_BuildingsState::ptr)(DAT_CurrentBuildingID::instance, 0);
            MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::determineBuildingEntranceFromKeepArea,
                DAT_BuildingsState::ptr)(DAT_CurrentBuildingID::instance, 1, 0);
            return;
        }
        // An ox is already out: forget it once its unit slot was reused, and wait 300 ticks when it burns
        if (DAT_BuildingsState::instance.buildings[buildingID].oxTetherRelatedUnitUID
            != DAT_UnitsState::instance.units[DAT_BuildingsState::instance.buildings[buildingID].oxTetherRelatedUnitID]
                .uid) {
            DAT_BuildingsState::instance.buildings[buildingID].oxTetherRelatedUnitID = 0;
            return;
        }
        if (DAT_UnitsState::instance.units[DAT_BuildingsState::instance.buildings[buildingID].oxTetherRelatedUnitID]
                .unitType
            == OpenSHC::Map::Units::UT_BURNING_ANIMAL_BIG) {
            DAT_BuildingsState::instance.buildings[buildingID].outpostRelatedUnk4 = 300;
        }
    }

}
}
