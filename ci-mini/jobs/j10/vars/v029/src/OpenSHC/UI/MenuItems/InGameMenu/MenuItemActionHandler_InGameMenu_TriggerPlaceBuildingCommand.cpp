#include "../InGameMenu.func.hpp"

#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Map/WallAndPitchState.func.hpp"
#include "OpenSHC/Random/RNG.func.hpp"
#include "OpenSHC/Rendering/ViewportRenderState.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/UI/Actions.func.hpp"
#include "OpenSHC/UI/BottomLeftTextDisplayState.func.hpp"
#include "OpenSHC/UI/Helpers.func.hpp"
#include "OpenSHC/UI/HoveredState.func.hpp"

#include "OpenSHC/Globals/DAT_00b96110.hpp"
#include "OpenSHC/Globals/DAT_00b98450.hpp"
#include "OpenSHC/Globals/DAT_00b98454.hpp"
#include "OpenSHC/Globals/DAT_BottomLeftTextDisplayState.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_HoveredState.hpp"
#include "OpenSHC/Globals/DAT_MouseState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"
#include "OpenSHC/Globals/DAT_ScrollingHandler.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"
#include "OpenSHC/Globals/DAT_WallAndPitchState.hpp"
#include "OpenSHC/Globals/SEC_RNG.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        // FUNCTION: STRONGHOLDCRUSADER 0x004451c0
        void __cdecl InGameMenu::MenuItemActionHandler_InGameMenu_TriggerPlaceBuildingCommand(int param_1, ...)
        {
            if (DAT_GameSynchronyState::instance.syncStatus != 0 || DAT_GameSynchronyState::instance.saveRelated != 0
                || DAT_GameCore::instance.gamePausedLogical != 0) {
                return;
            }
            DAT_TileMapState::instance.DAT_BuildingSize
                = MACRO_CALL_MEMBER(Map::TileMapState_Func::getBuildingSizeForCommandBuildingType,
                    DAT_TileMapState::ptr)(DAT_TileMapState::instance.currentMapperCommand);
            if ((int)DAT_TileMapState::instance.DAT_BuildingSize < 0) {
                DAT_TileMapState::instance.DAT_BuildingSize = 0;
                return;
            }
            MACRO_CALL_MEMBER(UI::BottomLeftTextDisplayState_Func::setBottomLeftTextDisplayText,
                DAT_BottomLeftTextDisplayState::ptr)(2, -1, 0, DAT_TileMapState::instance.currentMapperCommand, 50, -1);
            if (DAT_ViewportRenderState::instance.viewportState.field_0x0 == 0) {
                return;
            }
            DAT_TileMapState::instance.buildingPlacementFailReason = 0;
            if (DAT_TileMapState::instance.flatViewToggleValue1 != 0) {
                MACRO_CALL_MEMBER(
                    Rendering::ViewportRenderState_Func::setupMouseTileXY2, DAT_ViewportRenderState::ptr)();
            } else {
                MACRO_CALL_MEMBER(
                    Rendering::ViewportRenderState_Func::setupMouseTileXY, DAT_ViewportRenderState::ptr)();
            }
            if (DAT_MouseState::instance.leftClickStart == 0 && DAT_ScrollingHandler::instance.isScrolling_0x0 != 0) {
                return;
            }
            DAT_TileMapState::instance.DAT_ClickedTileY = DAT_ViewportRenderState::instance.viewportState.mouseTileY;
            DAT_TileMapState::instance.DAT_ClickedTileX = DAT_ViewportRenderState::instance.viewportState.mouseTileX;
            if (DAT_TileMapState::instance.currentMapperCommand == (Commands::MappersEnum)210) {
                int tile
                    = DAT_ViewportRenderState::instance.translationMatrix[DAT_TileMapState::instance.DAT_ClickedTileY]
                          .addXgetTile
                    + DAT_TileMapState::instance.DAT_ClickedTileX;
                int buildingID = DAT_TileMapState::instance.BuildingLayer[tile];
                if (DAT_MouseState::instance.draggingStopped == 0) {
                    if (buildingID != 0
                        && DAT_BuildingsState::instance.buildings[buildingID].owner
                            == DAT_GameSynchronyState::instance.currentPlayerSlotID
                        && (DAT_BuildingsState::instance.buildings[buildingID].buildingType == 77
                            || DAT_BuildingsState::instance.buildings[buildingID].buildingType == 78)
                        && (DAT_TileMapState::instance.LogicLayer[tile] & 0x10000000) != 0
                        && DAT_TileMapState::instance.UnitLayer[tile] == 0
                        && DAT_BuildingsState::instance.buildings[buildingID].defensiveTowerEngineType == 0) {
                        MACRO_CALL_MEMBER(Rendering::ViewportRenderState_Func::createFloatingLayerElement,
                            DAT_ViewportRenderState::ptr)((IO::Graphics::GmID)83, 1, 0, 0, tile, 5);
                        return;
                    }
                    MACRO_CALL_MEMBER(Rendering::ViewportRenderState_Func::createFloatingLayerElement,
                        DAT_ViewportRenderState::ptr)((IO::Graphics::GmID)83, 1, 0, 0, tile, 1048581);
                    return;
                }
                if (buildingID != 0
                    && DAT_BuildingsState::instance.buildings[buildingID].owner
                        == DAT_GameSynchronyState::instance.currentPlayerSlotID
                    && (DAT_BuildingsState::instance.buildings[buildingID].buildingType == 77
                        || DAT_BuildingsState::instance.buildings[buildingID].buildingType == 78)
                    && (DAT_TileMapState::instance.LogicLayer[tile] & 0x10000000) != 0
                    && DAT_TileMapState::instance.UnitLayer[tile] == 0
                    && DAT_BuildingsState::instance.buildings[buildingID].defensiveTowerEngineType == 0
                    && MACRO_CALL_MEMBER(Game::GameStateStructures_Func::checkRequiredResourcesForBuildingOrPlanToBuy,
                           DAT_GameState::ptr)(
                           (Commands::MappersEnum)210, DAT_GameSynchronyState::instance.currentPlayerSlotID, TRUE)
                        != 0) {
                    MACRO_CALL_MEMBER(UI::HoveredState_Func::createHoverStateElement, DAT_HoveredState::ptr)(
                        DAT_TileMapState::instance.DAT_ClickedTileX, DAT_TileMapState::instance.DAT_ClickedTileY,
                        DAT_TileMapState::instance.currentMapperCommand, DAT_TileMapState::instance.DAT_BuildingSize,
                        0);
                    DAT_TileMapState::instance.DAT_ClickedTileX
                        = DAT_BuildingsState::instance.buildings[buildingID].x + 2;
                    DAT_TileMapState::instance.DAT_ClickedTileY
                        = DAT_BuildingsState::instance.buildings[buildingID].y + 2;
                    DAT_GameSynchronyState::instance.DAT_GameCommandParam0
                        = DAT_TileMapState::instance.DAT_ClickedTileX * 8 + 4;
                    DAT_GameSynchronyState::instance.DAT_GameCommandParam1
                        = DAT_TileMapState::instance.DAT_ClickedTileY * 8 + 4;
                    DAT_GameSynchronyState::instance.DAT_GameCommandParam2
                        = DAT_TileMapState::instance
                              .HeightLayer[DAT_ViewportRenderState::instance
                                               .translationMatrix[DAT_TileMapState::instance.DAT_ClickedTileY]
                                               .addXgetTile
                                  + DAT_TileMapState::instance.DAT_ClickedTileX];
                    DAT_GameSynchronyState::instance.DAT_GameCommandParam3 = 41;
                    MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand, DAT_GameSynchronyState::ptr)(
                        (Commands::GameCommandType)42);
                }
                return;
            }
            if (DAT_TileMapState::instance.currentMapperCommand == (Commands::MappersEnum)211) {
                int tile
                    = DAT_ViewportRenderState::instance.translationMatrix[DAT_TileMapState::instance.DAT_ClickedTileY]
                          .addXgetTile
                    + DAT_TileMapState::instance.DAT_ClickedTileX;
                int buildingID = DAT_TileMapState::instance.BuildingLayer[tile];
                if (DAT_MouseState::instance.draggingStopped == 0) {
                    if (buildingID != 0
                        && DAT_BuildingsState::instance.buildings[buildingID].owner
                            == DAT_GameSynchronyState::instance.currentPlayerSlotID
                        && (DAT_BuildingsState::instance.buildings[buildingID].buildingType == 77
                            || DAT_BuildingsState::instance.buildings[buildingID].buildingType == 78)
                        && (DAT_TileMapState::instance.LogicLayer[tile] & 0x10000000) != 0
                        && DAT_TileMapState::instance.UnitLayer[tile] == 0
                        && DAT_BuildingsState::instance.buildings[buildingID].defensiveTowerEngineType == 0) {
                        MACRO_CALL_MEMBER(Rendering::ViewportRenderState_Func::createFloatingLayerElement,
                            DAT_ViewportRenderState::ptr)((IO::Graphics::GmID)120, 1, 0, 0, tile, 5);
                        return;
                    }
                    MACRO_CALL_MEMBER(Rendering::ViewportRenderState_Func::createFloatingLayerElement,
                        DAT_ViewportRenderState::ptr)((IO::Graphics::GmID)120, 1, 0, 0, tile, 1048581);
                    return;
                }
                if (buildingID != 0
                    && DAT_BuildingsState::instance.buildings[buildingID].owner
                        == DAT_GameSynchronyState::instance.currentPlayerSlotID
                    && (DAT_BuildingsState::instance.buildings[buildingID].buildingType == 77
                        || DAT_BuildingsState::instance.buildings[buildingID].buildingType == 78)
                    && (DAT_TileMapState::instance.LogicLayer[tile] & 0x10000000) != 0
                    && DAT_TileMapState::instance.UnitLayer[tile] == 0
                    && DAT_BuildingsState::instance.buildings[buildingID].defensiveTowerEngineType == 0
                    && MACRO_CALL_MEMBER(Game::GameStateStructures_Func::checkRequiredResourcesForBuildingOrPlanToBuy,
                           DAT_GameState::ptr)(
                           (Commands::MappersEnum)211, DAT_GameSynchronyState::instance.currentPlayerSlotID, TRUE)
                        != 0) {
                    MACRO_CALL_MEMBER(UI::HoveredState_Func::createHoverStateElement, DAT_HoveredState::ptr)(
                        DAT_TileMapState::instance.DAT_ClickedTileX, DAT_TileMapState::instance.DAT_ClickedTileY,
                        DAT_TileMapState::instance.currentMapperCommand, DAT_TileMapState::instance.DAT_BuildingSize,
                        0);
                    DAT_TileMapState::instance.DAT_ClickedTileX
                        = DAT_BuildingsState::instance.buildings[buildingID].x + 2;
                    DAT_TileMapState::instance.DAT_ClickedTileY
                        = DAT_BuildingsState::instance.buildings[buildingID].y + 2;
                    DAT_GameSynchronyState::instance.DAT_GameCommandParam0
                        = DAT_TileMapState::instance.DAT_ClickedTileX * 8 + 4;
                    DAT_GameSynchronyState::instance.DAT_GameCommandParam1
                        = DAT_TileMapState::instance.DAT_ClickedTileY * 8 + 4;
                    DAT_GameSynchronyState::instance.DAT_GameCommandParam2
                        = DAT_TileMapState::instance
                              .HeightLayer[DAT_ViewportRenderState::instance
                                               .translationMatrix[DAT_TileMapState::instance.DAT_ClickedTileY]
                                               .addXgetTile
                                  + DAT_TileMapState::instance.DAT_ClickedTileX];
                    DAT_GameSynchronyState::instance.DAT_GameCommandParam3 = 61;
                    MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand, DAT_GameSynchronyState::ptr)(
                        (Commands::GameCommandType)42);
                }
                return;
            }
            if (DAT_TileMapState::instance.currentMapperCommand == (Commands::MappersEnum)120
                || DAT_TileMapState::instance.currentMapperCommand == (Commands::MappersEnum)121
                || DAT_TileMapState::instance.currentMapperCommand == (Commands::MappersEnum)122
                || DAT_TileMapState::instance.currentMapperCommand == (Commands::MappersEnum)123) {
                int tile
                    = DAT_ViewportRenderState::instance.translationMatrix[DAT_TileMapState::instance.DAT_ClickedTileY]
                          .addXgetTile
                    + DAT_TileMapState::instance.DAT_ClickedTileX;
                int spriteIdx;
                int xOff;
                int yOff;
                switch (DAT_TileMapState::instance.currentMapperCommand) {
                case 120:
                    spriteIdx = 9;
                    xOff = 15;
                    yOff = 7;
                    break;
                case 121:
                    spriteIdx = 41;
                    xOff = 15;
                    yOff = -2;
                    break;
                case 122:
                    spriteIdx = 73;
                    xOff = 6;
                    yOff = 6;
                    break;
                case 123:
                    spriteIdx = 1;
                    xOff = 6;
                    yOff = 7;
                    break;
                }
                if (DAT_MouseState::instance.draggingStopped == 0) {
                    int gmID = 76;
                    if (DAT_TileMapState::instance.currentMapperCommand == (Commands::MappersEnum)123) {
                        gmID = 201;
                    }
                    if (MACRO_CALL_MEMBER(Map::TileMapState_Func::getTotalHeightAt, DAT_TileMapState::ptr)(
                            tile, DAT_GameSynchronyState::instance.currentPlayerSlotID)
                            >= 0
                        && (DAT_TileMapState::instance.MiscDisplayLayer[tile] & 0x1000) == 0) {
                        MACRO_CALL_MEMBER(Rendering::ViewportRenderState_Func::createFloatingLayerElement,
                            DAT_ViewportRenderState::ptr)((IO::Graphics::GmID)gmID, spriteIdx, xOff, yOff, tile, 13);
                        return;
                    }
                    MACRO_CALL_MEMBER(Rendering::ViewportRenderState_Func::createFloatingLayerElement,
                        DAT_ViewportRenderState::ptr)((IO::Graphics::GmID)gmID, spriteIdx, xOff, yOff, tile, 1572877);
                    return;
                }
                int totalHeight = MACRO_CALL_MEMBER(Map::TileMapState_Func::getTotalHeightAt, DAT_TileMapState::ptr)(
                    tile, DAT_GameSynchronyState::instance.currentPlayerSlotID);
                if (totalHeight >= 0 && (DAT_TileMapState::instance.MiscDisplayLayer[tile] & 0x1000) == 0) {
                    int entityType;
                    int px;
                    int py;
                    switch (DAT_TileMapState::instance.currentMapperCommand) {
                    case 120:
                        px = DAT_TileMapState::instance.DAT_ClickedTileX * 8;
                        entityType = 10;
                        py = DAT_TileMapState::instance.DAT_ClickedTileY * 8;
                        MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                            DAT_TileMapState::instance.DAT_ClickedTileX, DAT_TileMapState::instance.DAT_ClickedTileY,
                            (DE::SHCDE::eSFX)203);
                        break;
                    case 121:
                        entityType = 11;
                        px = DAT_TileMapState::instance.DAT_ClickedTileX * 8;
                        py = DAT_TileMapState::instance.DAT_ClickedTileY * 8;
                        MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                            DAT_TileMapState::instance.DAT_ClickedTileX, DAT_TileMapState::instance.DAT_ClickedTileY,
                            (DE::SHCDE::eSFX)204);
                        break;
                    case 122:
                        entityType = 12;
                        px = DAT_TileMapState::instance.DAT_ClickedTileX * 8;
                        py = DAT_TileMapState::instance.DAT_ClickedTileY * 8;
                        MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                            DAT_TileMapState::instance.DAT_ClickedTileX, DAT_TileMapState::instance.DAT_ClickedTileY,
                            (DE::SHCDE::eSFX)203);
                        break;
                    case 123:
                        entityType = 13;
                        px = DAT_TileMapState::instance.DAT_ClickedTileX * 8;
                        py = DAT_TileMapState::instance.DAT_ClickedTileY * 8;
                        MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                            DAT_TileMapState::instance.DAT_ClickedTileX, DAT_TileMapState::instance.DAT_ClickedTileY,
                            (DE::SHCDE::eSFX)203);
                        break;
                    }
                    MACRO_CALL_MEMBER(UI::HoveredState_Func::createHoverStateElement, DAT_HoveredState::ptr)(
                        DAT_TileMapState::instance.DAT_ClickedTileX, DAT_TileMapState::instance.DAT_ClickedTileY,
                        DAT_TileMapState::instance.currentMapperCommand, DAT_TileMapState::instance.DAT_BuildingSize,
                        0);
                    DAT_GameSynchronyState::instance.DAT_GameCommandParam0
                        = DAT_GameSynchronyState::instance.currentPlayerSlotID;
                    DAT_GameSynchronyState::instance.DAT_GameCommandParam1 = px;
                    DAT_GameSynchronyState::instance.DAT_GameCommandParam2 = py;
                    DAT_GameSynchronyState::instance.DAT_GameCommandParam3 = totalHeight;
                    DAT_GameSynchronyState::instance.DAT_GameCommandParam4 = entityType;
                    DAT_GameSynchronyState::instance.DAT_GameCommandParam5
                        = DAT_GameSynchronyState::instance.currentPlayerSlotID;
                    MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand, DAT_GameSynchronyState::ptr)(
                        (Commands::GameCommandType)69);
                }
                return;
            }
            if (DAT_TileMapState::instance.currentMapperCommand == (Commands::MappersEnum)129) {
                int tile
                    = DAT_ViewportRenderState::instance.translationMatrix[DAT_TileMapState::instance.DAT_ClickedTileY]
                          .addXgetTile
                    + DAT_TileMapState::instance.DAT_ClickedTileX;
                int spriteIdx = DAT_TileMapState::instance.decorationVariantIndex + 1;
                if (DAT_MouseState::instance.draggingStopped == 0) {
                    if (MACRO_CALL_MEMBER(Map::TileMapState_Func::getTotalHeightAt, DAT_TileMapState::ptr)(
                            tile, DAT_GameSynchronyState::instance.currentPlayerSlotID)
                            >= 0
                        && (DAT_TileMapState::instance.MiscDisplayLayer[tile] & 0x1000) == 0) {
                        MACRO_CALL_MEMBER(Rendering::ViewportRenderState_Func::createFloatingLayerElement,
                            DAT_ViewportRenderState::ptr)((IO::Graphics::GmID)187, spriteIdx, 15, 7, tile, 29);
                        return;
                    }
                    MACRO_CALL_MEMBER(Rendering::ViewportRenderState_Func::createFloatingLayerElement,
                        DAT_ViewportRenderState::ptr)((IO::Graphics::GmID)187, spriteIdx, 15, 7, tile, 1572893);
                    return;
                }
                int totalHeight = MACRO_CALL_MEMBER(Map::TileMapState_Func::getTotalHeightAt, DAT_TileMapState::ptr)(
                    tile, DAT_GameSynchronyState::instance.currentPlayerSlotID);
                if (totalHeight >= 0 && (DAT_TileMapState::instance.MiscDisplayLayer[tile] & 0x1000) == 0) {
                    MACRO_CALL_MEMBER(UI::HoveredState_Func::createHoverStateElement, DAT_HoveredState::ptr)(
                        DAT_TileMapState::instance.DAT_ClickedTileX, DAT_TileMapState::instance.DAT_ClickedTileY,
                        DAT_TileMapState::instance.currentMapperCommand,
                        DAT_TileMapState::instance.decorationVariantIndex, 0);
                    int px = DAT_TileMapState::instance.DAT_ClickedTileX * 8;
                    int py = DAT_TileMapState::instance.DAT_ClickedTileY * 8;
                    DAT_GameSynchronyState::instance.DAT_GameCommandParam0
                        = DAT_GameSynchronyState::instance.currentPlayerSlotID;
                    DAT_GameSynchronyState::instance.DAT_GameCommandParam1 = px;
                    DAT_GameSynchronyState::instance.DAT_GameCommandParam2 = py;
                    DAT_GameSynchronyState::instance.DAT_GameCommandParam3 = totalHeight;
                    DAT_GameSynchronyState::instance.DAT_GameCommandParam4 = 15;
                    DAT_GameSynchronyState::instance.DAT_GameCommandParam5
                        = DAT_TileMapState::instance.decorationVariantIndex;
                    MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand, DAT_GameSynchronyState::ptr)(
                        (Commands::GameCommandType)69);
                    DAT_TileMapState::instance.decorationVariantIndex = SEC_RNG::instance.currentNumber1 % 7;
                    MACRO_CALL_MEMBER(Random::RNG_Func::nextRandomNumber1, SEC_RNG::ptr)();
                }
                return;
            }
            if (DAT_TileMapState::instance.currentMapperCommand == (Commands::MappersEnum)148) {
                int tile
                    = DAT_ViewportRenderState::instance.translationMatrix[DAT_TileMapState::instance.DAT_ClickedTileY]
                          .addXgetTile
                    + DAT_TileMapState::instance.DAT_ClickedTileX;
                int canAfford = 1;
                if (DAT_GameCore::instance.gameMode_2 == 6) {
                    int stoneCost;
                    int goldCost;
                    MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::getBuildingCost, DAT_BuildingsState::ptr)(
                        (Commands::MappersEnum)148, &stoneCost, &goldCost);
                    if (goldCost
                        > DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                            .startResources[15]) {
                        canAfford = 0;
                    }
                }
                if (DAT_MouseState::instance.draggingStopped == 0) {
                    if (MACRO_CALL_MEMBER(Map::TileMapState_Func::getHeightAtTileIncludingOwnersBuildings,
                            DAT_TileMapState::ptr)(tile, DAT_GameSynchronyState::instance.currentPlayerSlotID)
                            != 0
                        && canAfford != 0) {
                        MACRO_CALL_MEMBER(Rendering::ViewportRenderState_Func::createFloatingLayerElement,
                            DAT_ViewportRenderState::ptr)((IO::Graphics::GmID)138, 1, 15, 7, tile, 29);
                    } else {
                        MACRO_CALL_MEMBER(Rendering::ViewportRenderState_Func::createFloatingLayerElement,
                            DAT_ViewportRenderState::ptr)((IO::Graphics::GmID)138, 1, 15, 7, tile, 1048605);
                    }
                    return;
                }
                if (MACRO_CALL_MEMBER(Map::TileMapState_Func::getHeightAtTileIncludingOwnersBuildings,
                        DAT_TileMapState::ptr)(tile, DAT_GameSynchronyState::instance.currentPlayerSlotID)
                        != 0
                    && canAfford != 0) {
                    MACRO_CALL_MEMBER(UI::HoveredState_Func::createHoverStateElement, DAT_HoveredState::ptr)(
                        DAT_TileMapState::instance.DAT_ClickedTileX, DAT_TileMapState::instance.DAT_ClickedTileY,
                        DAT_TileMapState::instance.currentMapperCommand, DAT_TileMapState::instance.DAT_BuildingSize,
                        0);
                    int px = DAT_TileMapState::instance.DAT_ClickedTileX * 8;
                    int py = DAT_TileMapState::instance.DAT_ClickedTileY * 8;
                    uint totalHeight
                        = MACRO_CALL_MEMBER(Map::TileMapState_Func::getTotalHeightAtTile, DAT_TileMapState::ptr)(tile);
                    switch (DAT_TileMapState::instance.mapOrientation) {
                    case 2:
                        px += 7;
                        break;
                    case 4:
                        px += 7;
                        py += 7;
                        break;
                    case 6:
                        py += 7;
                        break;
                    }
                    DAT_GameSynchronyState::instance.DAT_GameCommandParam0
                        = DAT_GameSynchronyState::instance.currentPlayerSlotID;
                    DAT_GameSynchronyState::instance.DAT_GameCommandParam1 = px;
                    DAT_GameSynchronyState::instance.DAT_GameCommandParam2 = py;
                    DAT_GameSynchronyState::instance.DAT_GameCommandParam3 = totalHeight;
                    DAT_GameSynchronyState::instance.DAT_GameCommandParam4 = 14;
                    MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand, DAT_GameSynchronyState::ptr)(
                        (Commands::GameCommandType)69);
                }
                return;
            }
            if (DAT_TileMapState::instance.currentMapperCommand == (Commands::MappersEnum)332
                || DAT_TileMapState::instance.currentMapperCommand == (Commands::MappersEnum)333
                || DAT_TileMapState::instance.currentMapperCommand == (Commands::MappersEnum)334
                || DAT_TileMapState::instance.currentMapperCommand == (Commands::MappersEnum)335
                || DAT_TileMapState::instance.currentMapperCommand == (Commands::MappersEnum)336
                || DAT_TileMapState::instance.currentMapperCommand == (Commands::MappersEnum)337
                || DAT_TileMapState::instance.currentMapperCommand == (Commands::MappersEnum)338) {
                MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::createEntityForAssemblyPointsForActiveTabType,
                    DAT_BuildingsState::ptr)();
                int tile
                    = DAT_ViewportRenderState::instance.translationMatrix[DAT_TileMapState::instance.DAT_ClickedTileY]
                          .addXgetTile
                    + DAT_TileMapState::instance.DAT_ClickedTileX;
                int playerID = DAT_GameSynchronyState::instance.currentPlayerSlotID;
                int buildingID = DAT_GameState::instance.playerDataArray[playerID].buildingEntryInfos[5].id;
                int canNavigate = 1;
                if (buildingID <= 0) {
                    canNavigate = 0;
                } else {
                    int startTile = DAT_ViewportRenderState::instance
                                        .translationMatrix[DAT_GameState::instance.playerDataArray[playerID]
                                                .barracksParadegroundLocations[0][0]
                                                .y]
                                        .addXgetTile
                        + DAT_GameState::instance.playerDataArray[playerID].barracksParadegroundLocations[0][0].x;
                    if (MACRO_CALL_MEMBER(
                            Map::Navigation::PathFindingState_Func::calculateCanPlayerUnitsNavigateToAreaFromArea,
                            DAT_PathFindingState::ptr)(playerID,
                            (short)DAT_TileMapState::instance.PathConnectionLayer[startTile],
                            (short)DAT_TileMapState::instance.PathConnectionLayer[tile], 0)
                        == 0) {
                        canNavigate = 0;
                    }
                    if (DAT_TileMapState::instance.BuildingLayer[tile] == buildingID) {
                        canNavigate = 1;
                    }
                }
                if (DAT_MouseState::instance.draggingStopped == 0) {
                    if (canNavigate != 0) {
                        MACRO_CALL_MEMBER(Rendering::ViewportRenderState_Func::createFloatingLayerElement,
                            DAT_ViewportRenderState::ptr)((IO::Graphics::GmID)172, 97, 15, 7, tile, 13);
                    } else {
                        MACRO_CALL_MEMBER(Rendering::ViewportRenderState_Func::createFloatingLayerElement,
                            DAT_ViewportRenderState::ptr)((IO::Graphics::GmID)172, 97, 15, 7, tile, 1572877);
                    }
                    return;
                }
                if (canNavigate != 0) {
                    DAT_GameSynchronyState::instance.DAT_GameCommandParam0
                        = DAT_TileMapState::instance.currentMapperCommand - 332;
                    DAT_GameSynchronyState::instance.DAT_GameCommandParam1
                        = DAT_TileMapState::instance.DAT_ClickedTileX;
                    DAT_GameSynchronyState::instance.DAT_GameCommandParam2
                        = DAT_TileMapState::instance.DAT_ClickedTileY;
                    MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand, DAT_GameSynchronyState::ptr)(
                        (Commands::GameCommandType)102);
                    DAT_TileMapState::instance.currentMapperCommand = (Commands::MappersEnum)0;
                }
                return;
            }
            if (DAT_TileMapState::instance.currentMapperCommand == (Commands::MappersEnum)360
                || DAT_TileMapState::instance.currentMapperCommand == (Commands::MappersEnum)361
                || DAT_TileMapState::instance.currentMapperCommand == (Commands::MappersEnum)362
                || DAT_TileMapState::instance.currentMapperCommand == (Commands::MappersEnum)363
                || DAT_TileMapState::instance.currentMapperCommand == (Commands::MappersEnum)364
                || DAT_TileMapState::instance.currentMapperCommand == (Commands::MappersEnum)365
                || DAT_TileMapState::instance.currentMapperCommand == (Commands::MappersEnum)366) {
                MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::createEntityForAssemblyPointsForActiveTabType,
                    DAT_BuildingsState::ptr)();
                int tile
                    = DAT_ViewportRenderState::instance.translationMatrix[DAT_TileMapState::instance.DAT_ClickedTileY]
                          .addXgetTile
                    + DAT_TileMapState::instance.DAT_ClickedTileX;
                int playerID = DAT_GameSynchronyState::instance.currentPlayerSlotID;
                int buildingID = DAT_GameState::instance.playerDataArray[playerID].buildingEntryInfos[11].id;
                int canNavigate = 1;
                if (buildingID <= 0) {
                    canNavigate = 0;
                } else {
                    int startTile = DAT_ViewportRenderState::instance
                                        .translationMatrix[DAT_GameState::instance.playerDataArray[playerID]
                                                .structure.mercenaryOutpostCampgroundLocations[0][0][0]
                                                .y]
                                        .addXgetTile
                        + DAT_GameState::instance.playerDataArray[playerID]
                              .structure.mercenaryOutpostCampgroundLocations[0][0][0]
                              .x;
                    if (MACRO_CALL_MEMBER(
                            Map::Navigation::PathFindingState_Func::calculateCanPlayerUnitsNavigateToAreaFromArea,
                            DAT_PathFindingState::ptr)(playerID,
                            (short)DAT_TileMapState::instance.PathConnectionLayer[startTile],
                            (short)DAT_TileMapState::instance.PathConnectionLayer[tile], 0)
                        == 0) {
                        canNavigate = 0;
                    }
                    if (DAT_TileMapState::instance.BuildingLayer[tile] == buildingID) {
                        canNavigate = 1;
                    }
                }
                if (DAT_MouseState::instance.draggingStopped == 0) {
                    if (canNavigate != 0) {
                        MACRO_CALL_MEMBER(Rendering::ViewportRenderState_Func::createFloatingLayerElement,
                            DAT_ViewportRenderState::ptr)((IO::Graphics::GmID)172, 97, 15, 7, tile, 13);
                    } else {
                        MACRO_CALL_MEMBER(Rendering::ViewportRenderState_Func::createFloatingLayerElement,
                            DAT_ViewportRenderState::ptr)((IO::Graphics::GmID)172, 97, 15, 7, tile, 1572877);
                    }
                    return;
                }
                if (canNavigate != 0) {
                    DAT_GameSynchronyState::instance.DAT_GameCommandParam0
                        = DAT_TileMapState::instance.currentMapperCommand - 350;
                    DAT_GameSynchronyState::instance.DAT_GameCommandParam1
                        = DAT_TileMapState::instance.DAT_ClickedTileX;
                    DAT_GameSynchronyState::instance.DAT_GameCommandParam2
                        = DAT_TileMapState::instance.DAT_ClickedTileY;
                    MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand, DAT_GameSynchronyState::ptr)(
                        (Commands::GameCommandType)102);
                    DAT_TileMapState::instance.currentMapperCommand = (Commands::MappersEnum)0;
                }
                return;
            }
            if (DAT_TileMapState::instance.currentMapperCommand == (Commands::MappersEnum)367
                || DAT_TileMapState::instance.currentMapperCommand == (Commands::MappersEnum)368) {
                MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::createEntityForAssemblyPointsForActiveTabType,
                    DAT_BuildingsState::ptr)();
                int tile
                    = DAT_ViewportRenderState::instance.translationMatrix[DAT_TileMapState::instance.DAT_ClickedTileY]
                          .addXgetTile
                    + DAT_TileMapState::instance.DAT_ClickedTileX;
                int playerID = DAT_GameSynchronyState::instance.currentPlayerSlotID;
                int buildingID = DAT_GameState::instance.playerDataArray[playerID].buildingEntryInfos[9].id;
                int canNavigate = 1;
                if (buildingID <= 0) {
                    canNavigate = 0;
                } else {
                    int startTile = DAT_ViewportRenderState::instance
                                        .translationMatrix[DAT_GameState::instance.playerDataArray[playerID]
                                                .engineersParadegroundLocations[0]
                                                .y]
                                        .addXgetTile
                        + DAT_GameState::instance.playerDataArray[playerID].engineersParadegroundLocations[0].x;
                    if (MACRO_CALL_MEMBER(
                            Map::Navigation::PathFindingState_Func::calculateCanPlayerUnitsNavigateToAreaFromArea,
                            DAT_PathFindingState::ptr)(playerID,
                            (short)DAT_TileMapState::instance.PathConnectionLayer[startTile],
                            (short)DAT_TileMapState::instance.PathConnectionLayer[tile], 0)
                        == 0) {
                        canNavigate = 0;
                    }
                    if (DAT_TileMapState::instance.BuildingLayer[tile] == buildingID) {
                        canNavigate = 1;
                    }
                }
                if (DAT_MouseState::instance.draggingStopped == 0) {
                    if (canNavigate != 0) {
                        MACRO_CALL_MEMBER(Rendering::ViewportRenderState_Func::createFloatingLayerElement,
                            DAT_ViewportRenderState::ptr)((IO::Graphics::GmID)172, 97, 15, 7, tile, 13);
                    } else {
                        MACRO_CALL_MEMBER(Rendering::ViewportRenderState_Func::createFloatingLayerElement,
                            DAT_ViewportRenderState::ptr)((IO::Graphics::GmID)172, 97, 15, 7, tile, 1572877);
                    }
                    return;
                }
                if (canNavigate != 0) {
                    DAT_GameSynchronyState::instance.DAT_GameCommandParam0
                        = DAT_TileMapState::instance.currentMapperCommand - 347;
                    DAT_GameSynchronyState::instance.DAT_GameCommandParam1
                        = DAT_TileMapState::instance.DAT_ClickedTileX;
                    DAT_GameSynchronyState::instance.DAT_GameCommandParam2
                        = DAT_TileMapState::instance.DAT_ClickedTileY;
                    MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand, DAT_GameSynchronyState::ptr)(
                        (Commands::GameCommandType)102);
                    DAT_TileMapState::instance.currentMapperCommand = (Commands::MappersEnum)0;
                }
                return;
            }
            if (DAT_TileMapState::instance.currentMapperCommand == (Commands::MappersEnum)369) {
                MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::createEntityForAssemblyPointsForActiveTabType,
                    DAT_BuildingsState::ptr)();
                int tile
                    = DAT_ViewportRenderState::instance.translationMatrix[DAT_TileMapState::instance.DAT_ClickedTileY]
                          .addXgetTile
                    + DAT_TileMapState::instance.DAT_ClickedTileX;
                int playerID = DAT_GameSynchronyState::instance.currentPlayerSlotID;
                int buildingID = DAT_GameState::instance.playerDataArray[playerID].buildingEntryInfos[10].id;
                int canNavigate = 1;
                if (buildingID <= 0) {
                    canNavigate = 0;
                } else {
                    int startTile = DAT_ViewportRenderState::instance
                                        .translationMatrix[DAT_GameState::instance.playerDataArray[playerID]
                                                .tunnelersGuildParadegroundLocations[0]
                                                .y]
                                        .addXgetTile
                        + DAT_GameState::instance.playerDataArray[playerID].tunnelersGuildParadegroundLocations[0].x;
                    if (MACRO_CALL_MEMBER(
                            Map::Navigation::PathFindingState_Func::calculateCanPlayerUnitsNavigateToAreaFromArea,
                            DAT_PathFindingState::ptr)(playerID,
                            (short)DAT_TileMapState::instance.PathConnectionLayer[startTile],
                            (short)DAT_TileMapState::instance.PathConnectionLayer[tile], 0)
                        == 0) {
                        canNavigate = 0;
                    }
                    if (DAT_TileMapState::instance.BuildingLayer[tile] == buildingID) {
                        canNavigate = 1;
                    }
                }
                if (DAT_MouseState::instance.draggingStopped == 0) {
                    if (canNavigate != 0) {
                        MACRO_CALL_MEMBER(Rendering::ViewportRenderState_Func::createFloatingLayerElement,
                            DAT_ViewportRenderState::ptr)((IO::Graphics::GmID)172, 97, 15, 7, tile, 13);
                    } else {
                        MACRO_CALL_MEMBER(Rendering::ViewportRenderState_Func::createFloatingLayerElement,
                            DAT_ViewportRenderState::ptr)((IO::Graphics::GmID)172, 97, 15, 7, tile, 1572877);
                    }
                    return;
                }
                if (canNavigate != 0) {
                    DAT_GameSynchronyState::instance.DAT_GameCommandParam0 = 30;
                    DAT_GameSynchronyState::instance.DAT_GameCommandParam1
                        = DAT_TileMapState::instance.DAT_ClickedTileX;
                    DAT_GameSynchronyState::instance.DAT_GameCommandParam2
                        = DAT_TileMapState::instance.DAT_ClickedTileY;
                    MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand, DAT_GameSynchronyState::ptr)(
                        (Commands::GameCommandType)102);
                    DAT_TileMapState::instance.currentMapperCommand = (Commands::MappersEnum)0;
                }
                return;
            }
            if (DAT_TileMapState::instance.currentMapperCommand == (Commands::MappersEnum)370) {
                MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::createEntityForAssemblyPointsForActiveTabType,
                    DAT_BuildingsState::ptr)();
                int tile
                    = DAT_ViewportRenderState::instance.translationMatrix[DAT_TileMapState::instance.DAT_ClickedTileY]
                          .addXgetTile
                    + DAT_TileMapState::instance.DAT_ClickedTileX;
                int playerID = DAT_GameSynchronyState::instance.currentPlayerSlotID;
                int startTile = DAT_ViewportRenderState::instance
                                    .translationMatrix
                                        [DAT_GameState::instance.playerDataArray[playerID].buildingEntryInfos[8].yEntry]
                                    .addXgetTile
                    + DAT_GameState::instance.playerDataArray[playerID].buildingEntryInfos[8].xEntry;
                int canNavigate = 1;
                if (MACRO_CALL_MEMBER(
                        Map::Navigation::PathFindingState_Func::calculateCanPlayerUnitsNavigateToAreaFromArea,
                        DAT_PathFindingState::ptr)(playerID,
                        (short)DAT_TileMapState::instance.PathConnectionLayer[startTile],
                        (short)DAT_TileMapState::instance.PathConnectionLayer[tile], 0)
                    == 0) {
                    canNavigate = 0;
                }
                if (DAT_BuildingsState::instance.buildings[DAT_TileMapState::instance.BuildingLayer[tile]].buildingType
                    == 38) {
                    canNavigate = 1;
                }
                if (DAT_MouseState::instance.draggingStopped == 0) {
                    if (canNavigate != 0) {
                        MACRO_CALL_MEMBER(Rendering::ViewportRenderState_Func::createFloatingLayerElement,
                            DAT_ViewportRenderState::ptr)((IO::Graphics::GmID)172, 97, 15, 7, tile, 13);
                    } else {
                        MACRO_CALL_MEMBER(Rendering::ViewportRenderState_Func::createFloatingLayerElement,
                            DAT_ViewportRenderState::ptr)((IO::Graphics::GmID)172, 97, 15, 7, tile, 1572877);
                    }
                    return;
                }
                if (canNavigate != 0) {
                    DAT_GameSynchronyState::instance.DAT_GameCommandParam0 = 40;
                    DAT_GameSynchronyState::instance.DAT_GameCommandParam1
                        = DAT_TileMapState::instance.DAT_ClickedTileX;
                    DAT_GameSynchronyState::instance.DAT_GameCommandParam2
                        = DAT_TileMapState::instance.DAT_ClickedTileY;
                    MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand, DAT_GameSynchronyState::ptr)(
                        (Commands::GameCommandType)102);
                    DAT_TileMapState::instance.currentMapperCommand = (Commands::MappersEnum)0;
                }
                return;
            }
            if (DAT_TileMapState::instance.currentMapperCommand >= (Commands::MappersEnum)270
                && DAT_TileMapState::instance.currentMapperCommand <= (Commands::MappersEnum)286) {
                MACRO_CALL(UI::Actions_Func::PlaceUnit)();
                return;
            }
            if (DAT_TileMapState::instance.currentMapperCommand >= (Commands::MappersEnum)350
                && DAT_TileMapState::instance.currentMapperCommand <= (Commands::MappersEnum)357) {
                MACRO_CALL(UI::Actions_Func::PlaceUnit)();
                return;
            }
            DAT_TileMapState::instance.DAT_TempBuildingRotation = 0;
            DAT_TileMapState::instance.DAT_ClickedTileX = DAT_ViewportRenderState::instance.viewportState.mouseTileX
                - DAT_TileMapState::instance.DAT_BuildingSize / 2;
            DAT_TileMapState::instance.DAT_ClickedTileY = DAT_ViewportRenderState::instance.viewportState.mouseTileY
                - DAT_TileMapState::instance.DAT_BuildingSize / 2;
            if (DAT_GameCore::instance.currentMenuViewType == 12) {
                switch (DAT_TileMapState::instance.currentMapperCommand) {
                case 62:
                    if (DAT_GameCore::instance.mapU2MiddleBytes[2] != 0) {
                        MACRO_CALL_MEMBER(Map::TileMapState_Func::checkBuildingCanBePlacedHere, DAT_TileMapState::ptr)(
                            DAT_GameSynchronyState::instance.currentPlayerSlotID,
                            DAT_TileMapState::instance.DAT_ClickedTileX, DAT_TileMapState::instance.DAT_ClickedTileY,
                            (Commands::MappersEnum)62, DAT_TileMapState::instance.DAT_BuildingSize);
                    }
                case 61:
                    if (DAT_GameCore::instance.mapU2MiddleBytes[1] != 0) {
                        MACRO_CALL_MEMBER(Map::TileMapState_Func::checkBuildingCanBePlacedHere, DAT_TileMapState::ptr)(
                            DAT_GameSynchronyState::instance.currentPlayerSlotID,
                            DAT_TileMapState::instance.DAT_ClickedTileX, DAT_TileMapState::instance.DAT_ClickedTileY,
                            (Commands::MappersEnum)61, DAT_TileMapState::instance.DAT_BuildingSize);
                    }
                case 60:
                    if (DAT_GameCore::instance.mapU2MiddleBytes[0] != 0) {
                        MACRO_CALL_MEMBER(Map::TileMapState_Func::checkBuildingCanBePlacedHere, DAT_TileMapState::ptr)(
                            DAT_GameSynchronyState::instance.currentPlayerSlotID,
                            DAT_TileMapState::instance.DAT_ClickedTileX, DAT_TileMapState::instance.DAT_ClickedTileY,
                            (Commands::MappersEnum)60, DAT_TileMapState::instance.DAT_BuildingSize);
                    }
                    break;
                default:
                    MACRO_CALL_MEMBER(Map::TileMapState_Func::checkBuildingCanBePlacedHere, DAT_TileMapState::ptr)(
                        DAT_GameSynchronyState::instance.currentPlayerSlotID,
                        DAT_TileMapState::instance.DAT_ClickedTileX, DAT_TileMapState::instance.DAT_ClickedTileY,
                        DAT_TileMapState::instance.currentMapperCommand, DAT_TileMapState::instance.DAT_BuildingSize);
                    break;
                }
            } else {
                MACRO_CALL_MEMBER(Map::TileMapState_Func::checkBuildingCanBePlacedHere, DAT_TileMapState::ptr)(
                    DAT_GameSynchronyState::instance.currentPlayerSlotID, DAT_TileMapState::instance.DAT_ClickedTileX,
                    DAT_TileMapState::instance.DAT_ClickedTileY, DAT_TileMapState::instance.currentMapperCommand,
                    DAT_TileMapState::instance.DAT_BuildingSize);
            }
            switch (DAT_TileMapState::instance.currentMapperCommand) {
            case 50:
            case 75:
            case 76:
            case 82:
            case 83:
            case 84:
            case 85:
                MACRO_CALL_MEMBER(Map::TileMapState_Func::determineBuildingPlacementRotation, DAT_TileMapState::ptr)(
                    DAT_TileMapState::instance.DAT_ClickedTileX, DAT_TileMapState::instance.DAT_ClickedTileY);
                break;
            case 105:
                MACRO_CALL_MEMBER(Map::TileMapState_Func::checkDrawbridgePlacement, DAT_TileMapState::ptr)(
                    DAT_TileMapState::instance.DAT_ClickedTileX, DAT_TileMapState::instance.DAT_ClickedTileY);
                break;
            }
            if (DAT_TileMapState::instance.currentMapperCommand == (Commands::MappersEnum)106
                || DAT_TileMapState::instance.currentMapperCommand == (Commands::MappersEnum)107
                || DAT_TileMapState::instance.currentMapperCommand == (Commands::MappersEnum)45
                || DAT_TileMapState::instance.currentMapperCommand == (Commands::MappersEnum)44) {
                DAT_TileMapState::instance.editorActiveBrush = 2;
                if (MACRO_CALL_MEMBER(Rendering::ViewportRenderState_Func::xyAreValid, DAT_ViewportRenderState::ptr)(
                        DAT_ViewportRenderState::instance.viewportState.mouseTileX,
                        DAT_ViewportRenderState::instance.viewportState.mouseTileY)
                    == 0) {
                    return;
                }
                int tile = DAT_ViewportRenderState::instance
                               .translationMatrix[DAT_ViewportRenderState::instance.viewportState.mouseTileY]
                               .addXgetTile
                    + DAT_ViewportRenderState::instance.viewportState.mouseTileX;
                if ((DAT_TileMapState::instance.currentMapperCommand == (Commands::MappersEnum)106
                        || DAT_TileMapState::instance.currentMapperCommand == (Commands::MappersEnum)45)
                    && MACRO_CALL_MEMBER(Map::TileMapState_Func::getUnownedMoatCount, DAT_TileMapState::ptr)() < 15) {
                    DAT_TileMapState::instance.buildingPlacementFail = 1;
                    MACRO_CALL_MEMBER(Map::TileMapState_Func::renderPreviewMapperWithBrush, DAT_TileMapState::ptr)(
                        DAT_ViewportRenderState::instance.viewportState.mouseTileX,
                        DAT_ViewportRenderState::instance.viewportState.mouseTileY,
                        DAT_TileMapState::instance.currentMapperCommand);
                    MACRO_CALL_MEMBER(UI::BottomLeftTextDisplayState_Func::setBottomLeftTextDisplayText,
                        DAT_BottomLeftTextDisplayState::ptr)(1, 8, 333, 0, 100, 6000);
                    return;
                }
                if ((DAT_MouseState::instance.leftClickState != 0 && (uint)tile != DAT_00b96110::instance)
                    || DAT_MouseState::instance.draggingStopped != 0) {
                    if (DAT_MouseState::instance.leftClickState != 0 && (uint)tile != DAT_00b96110::instance) {
                        DAT_00b96110::instance = tile;
                    }
                    if (MACRO_CALL_MEMBER(Map::Navigation::PathFindingState_Func::isSignPostWithinDistance,
                            DAT_PathFindingState::ptr)(DAT_ViewportRenderState::instance.viewportState.mouseTileX,
                            DAT_ViewportRenderState::instance.viewportState.mouseTileY,
                            DAT_GameState::instance.mapAndTime.unk_signpostDistance + 5)
                        != 0) {
                        MACRO_CALL_MEMBER(UI::BottomLeftTextDisplayState_Func::setBottomLeftTextDisplayText,
                            DAT_BottomLeftTextDisplayState::ptr)(1, 77, 21, 0, 100, 6000);
                        return;
                    }
                    if ((DAT_TileMapState::instance.currentMapperCommand == (Commands::MappersEnum)106
                            || DAT_TileMapState::instance.currentMapperCommand == (Commands::MappersEnum)107)
                        && MACRO_CALL_MEMBER(Map::TileMapState_Func::isValidCastleSiteLocation, DAT_TileMapState::ptr)(
                               DAT_ViewportRenderState::instance.viewportState.mouseTileX,
                               DAT_ViewportRenderState::instance.viewportState.mouseTileY,
                               DAT_TileMapState::instance.currentMapperCommand)
                            == 0) {
                        return;
                    }
                    if (DAT_GameSynchronyState::instance.currentGameMode != 0
                        && DAT_GameSynchronyState::instance.currentGameMode != 99) {
                        DWORD now = timeGetTime();
                        if (DAT_00b98450::instance == 0) {
                            now = timeGetTime();
                        } else if (now - DAT_00b98450::instance <= 200) {
                            return;
                        }
                        DAT_00b98450::instance = now;
                    }
                    DAT_GameSynchronyState::instance.DAT_GameCommandParam0
                        = DAT_ViewportRenderState::instance.viewportState.mouseTileX;
                    DAT_GameSynchronyState::instance.DAT_GameCommandParam1
                        = DAT_ViewportRenderState::instance.viewportState.mouseTileY;
                    DAT_GameSynchronyState::instance.DAT_GameCommandParam2 = 2;
                    DAT_GameSynchronyState::instance.DAT_GameCommandParam3 = 1073741824;
                    if (DAT_TileMapState::instance.currentMapperCommand == (Commands::MappersEnum)106) {
                        DAT_GameSynchronyState::instance.DAT_GameCommandParam4 = 0;
                        MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand,
                            DAT_GameSynchronyState::ptr)((Commands::GameCommandType)21);
                        return;
                    }
                    if (DAT_TileMapState::instance.currentMapperCommand == (Commands::MappersEnum)107) {
                        DAT_GameSynchronyState::instance.DAT_GameCommandParam4 = 1;
                        MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand,
                            DAT_GameSynchronyState::ptr)((Commands::GameCommandType)21);
                        return;
                    }
                    if (DAT_TileMapState::instance.currentMapperCommand == (Commands::MappersEnum)45) {
                        DAT_GameSynchronyState::instance.DAT_GameCommandParam4 = 2;
                    } else {
                        DAT_GameSynchronyState::instance.DAT_GameCommandParam4 = 3;
                    }
                    MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand, DAT_GameSynchronyState::ptr)(
                        (Commands::GameCommandType)21);
                    return;
                }
                MACRO_CALL_MEMBER(Map::TileMapState_Func::renderPreviewMapperWithBrush, DAT_TileMapState::ptr)(
                    DAT_ViewportRenderState::instance.viewportState.mouseTileX,
                    DAT_ViewportRenderState::instance.viewportState.mouseTileY,
                    DAT_TileMapState::instance.currentMapperCommand);
                return;
            }
            if (DAT_TileMapState::instance.currentMapperCommand == (Commands::MappersEnum)99) {
                if (MACRO_CALL_MEMBER(Map::TileMapState_Func::countUnownedPitchDitches, DAT_TileMapState::ptr)() < 15) {
                    DAT_TileMapState::instance.buildingPlacementFail = 1;
                    MACRO_CALL_MEMBER(UI::BottomLeftTextDisplayState_Func::setBottomLeftTextDisplayText,
                        DAT_BottomLeftTextDisplayState::ptr)(1, 8, 333, 0, 100, 6000);
                }
            } else if (DAT_BuildingsState::instance.unknownCountdown01 < 3
                || ((DAT_BuildingsState::instance.unknownCountdown01 <= 10
                        || (DAT_TileMapState::instance.currentMapperCommand != (Commands::MappersEnum)190
                            && DAT_TileMapState::instance.currentMapperCommand != (Commands::MappersEnum)191
                            && DAT_TileMapState::instance.currentMapperCommand != (Commands::MappersEnum)192
                            && DAT_TileMapState::instance.currentMapperCommand != (Commands::MappersEnum)193
                            && DAT_TileMapState::instance.currentMapperCommand != (Commands::MappersEnum)194
                            && DAT_TileMapState::instance.currentMapperCommand != (Commands::MappersEnum)358))
                    && DAT_TileMapState::instance.currentMapperCommand != (Commands::MappersEnum)66
                    && DAT_BuildingsState::instance.unknownCountdown01 < 20)) {
                DAT_TileMapState::instance.buildingPlacementFail = 1;
                MACRO_CALL_MEMBER(UI::BottomLeftTextDisplayState_Func::setBottomLeftTextDisplayText,
                    DAT_BottomLeftTextDisplayState::ptr)(1, 8, 333, 0, 100, 6000);
            }
            if (DAT_MouseState::instance.leftClickStart != 0) {
                DAT_00b96110::instance = 0;
            }
            bool shouldPlace = false;
            if (DAT_MouseState::instance.leftClickState != 0 && DAT_TileMapState::instance.buildingPlacementFail == 0
                && DAT_TileMapState::instance.currentMapperCommand == (Commands::MappersEnum)99) {
                if (DAT_GameSynchronyState::instance.currentGameMode != 0
                    && DAT_GameSynchronyState::instance.currentGameMode != 99) {
                    DWORD now = timeGetTime();
                    if (DAT_00b98454::instance == 0) {
                        now = timeGetTime();
                    } else if (now - DAT_00b98454::instance <= 200) {
                        return;
                    }
                    DAT_00b98454::instance = now;
                }
                int tile
                    = DAT_ViewportRenderState::instance.translationMatrix[DAT_TileMapState::instance.DAT_ClickedTileY]
                          .addXgetTile
                    + DAT_TileMapState::instance.DAT_ClickedTileX;
                if (DAT_00b96110::instance != (uint)tile) {
                    if (DAT_00b96110::instance == 0) {
                        MACRO_CALL_MEMBER(
                            Map::WallAndPitchState_Func::resetWallAndPitchState, DAT_WallAndPitchState::ptr)();
                    }
                    DAT_00b96110::instance = tile;
                    shouldPlace = true;
                }
            }
            if (!shouldPlace) {
                if (DAT_MouseState::instance.draggingStopped == 0) {
                    if (((DAT_TileMapState::instance.currentMapperCommand >= (Commands::MappersEnum)190
                             && DAT_TileMapState::instance.currentMapperCommand <= (Commands::MappersEnum)194)
                            || DAT_TileMapState::instance.currentMapperCommand == (Commands::MappersEnum)358)
                        && DAT_TileMapState::instance.buildingPlacementFail == 0) {
                        int tileX = DAT_TileMapState::instance.DAT_ClickedTileX;
                        int tileY = DAT_TileMapState::instance.DAT_ClickedTileY;
                        int xOff = 0;
                        int yOff = 0;
                        switch (DAT_TileMapState::instance.mapOrientation) {
                        case 0:
                            xOff = 13;
                            tileX += 1;
                            tileY += 1;
                            yOff = 2;
                            break;
                        case 2:
                            xOff = 45;
                            tileX -= 1;
                            tileY += 1;
                            yOff = -14;
                            break;
                        case 4:
                            xOff = 13;
                            tileX -= 1;
                            tileY -= 1;
                            yOff = -30;
                            break;
                        case 6:
                            xOff = -19;
                            tileX += 1;
                            tileY -= 1;
                            yOff = -12;
                            break;
                        }
                        MACRO_CALL_MEMBER(Rendering::ViewportRenderState_Func::createFloatingLayerElement,
                            DAT_ViewportRenderState::ptr)((IO::Graphics::GmID)82, 1, xOff, yOff,
                            DAT_ViewportRenderState::instance.translationMatrix[tileY].addXgetTile + tileX, 5);
                        return;
                    }
                    MACRO_CALL_MEMBER(Map::TileMapState_Func::setConstructionGFXLayerBasedOnPlacementChecks,
                        DAT_TileMapState::ptr)(DAT_TileMapState::instance.DAT_ClickedTileX,
                        DAT_TileMapState::instance.DAT_ClickedTileY, DAT_TileMapState::instance.currentMapperCommand,
                        DAT_TileMapState::instance.DAT_BuildingSize);
                    return;
                }
                if (DAT_TileMapState::instance.buildingPlacementFail != 0) {
                    if (DAT_TileMapState::instance.buildingPlacementFailReason == 1000) {
                        MACRO_CALL_MEMBER(UI::BottomLeftTextDisplayState_Func::setBottomLeftTextDisplayText,
                            DAT_BottomLeftTextDisplayState::ptr)(1, 257, 2, 0, 100, 6000);
                        return;
                    }
                    if (DAT_TileMapState::instance.buildingPlacementFailReason != 0) {
                        MACRO_CALL_MEMBER(UI::BottomLeftTextDisplayState_Func::setBottomLeftTextDisplayText,
                            DAT_BottomLeftTextDisplayState::ptr)(
                            1, 77, DAT_TileMapState::instance.buildingPlacementFailReason, 0, 100, 6000);
                        MACRO_CALL(UI::Helpers_Func::PlayPlacementWarning)((Map::Buildings::BuildingFailReasonEnum)
                                DAT_TileMapState::instance.buildingPlacementFailReason);
                        return;
                    }
                    if (DAT_TileMapState::instance.placementWarning != 0) {
                        MACRO_CALL(UI::Helpers_Func::PlayPlacementWarning)(
                            (Map::Buildings::BuildingFailReasonEnum)(-1 - DAT_TileMapState::instance.placementWarning));
                        return;
                    }
                    if (DAT_TileMapState::instance.currentMapperCommand != (Commands::MappersEnum)99
                        || DAT_00b96110::instance == 0) {
                        MACRO_CALL(UI::Helpers_Func::PlayPlacementWarning)((Map::Buildings::BuildingFailReasonEnum)-1);
                    }
                    return;
                }
            }
            if (MACRO_CALL_MEMBER(Game::GameStateStructures_Func::checkRequiredResourcesForBuildingOrPlanToBuy,
                    DAT_GameState::ptr)(DAT_TileMapState::instance.currentMapperCommand,
                    DAT_GameSynchronyState::instance.currentPlayerSlotID, TRUE)
                == 0) {
                return;
            }
            DAT_GameSynchronyState::instance.DAT_GameCommandParam0 = DAT_TileMapState::instance.DAT_ClickedTileX;
            DAT_GameSynchronyState::instance.DAT_GameCommandParam1 = DAT_TileMapState::instance.DAT_ClickedTileY;
            DAT_GameSynchronyState::instance.DAT_GameCommandParam2 = DAT_TileMapState::instance.currentMapperCommand;
            DAT_GameSynchronyState::instance.DAT_GameCommandParam3 = DAT_TileMapState::instance.DAT_BuildingSize;
            int orientation;
            if (DAT_TileMapState::instance.currentMapperCommand == (Commands::MappersEnum)101
                || DAT_TileMapState::instance.currentMapperCommand == (Commands::MappersEnum)102) {
                orientation = DAT_TileMapState::instance.gateOrientationVariant;
            } else if (DAT_TileMapState::instance.currentMapperCommand == (Commands::MappersEnum)140) {
                orientation = 0;
            } else if (DAT_TileMapState::instance.currentMapperCommand == (Commands::MappersEnum)141) {
                orientation = 2;
            } else if (DAT_TileMapState::instance.currentMapperCommand == (Commands::MappersEnum)142) {
                orientation = 4;
            } else if (DAT_TileMapState::instance.currentMapperCommand == (Commands::MappersEnum)143) {
                orientation = 6;
            } else if (DAT_TileMapState::instance.currentMapperCommand == (Commands::MappersEnum)145) {
                orientation = 80;
            } else if (DAT_TileMapState::instance.currentMapperCommand == (Commands::MappersEnum)144) {
                orientation = 81;
            } else if (DAT_TileMapState::instance.currentMapperCommand == (Commands::MappersEnum)147) {
                orientation = 80;
            } else if (DAT_TileMapState::instance.currentMapperCommand == (Commands::MappersEnum)146) {
                orientation = 81;
            } else {
                orientation = DAT_TileMapState::instance.uiBuildingRotation;
            }
            DAT_GameSynchronyState::instance.DAT_GameCommandParam4 = orientation;
            MACRO_CALL_MEMBER(UI::HoveredState_Func::createHoverStateElement, DAT_HoveredState::ptr)(
                DAT_TileMapState::instance.DAT_ClickedTileX, DAT_TileMapState::instance.DAT_ClickedTileY,
                DAT_TileMapState::instance.currentMapperCommand, DAT_TileMapState::instance.DAT_BuildingSize,
                orientation);
            DAT_GameSynchronyState::instance.DAT_GameCommandParam5 = DAT_TribesState::instance.DAT_CurrentTribeID;
            MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand, DAT_GameSynchronyState::ptr)(
                (Commands::GameCommandType)28);
            switch (DAT_TileMapState::instance.currentMapperCommand) {
            case 66:
                DAT_TileMapState::instance.currentMapperCommand = (Commands::MappersEnum)0;
                break;
            case 190:
            case 191:
            case 192:
            case 193:
            case 194:
            case 358:
                MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playUnitSpeechEffect, DAT_SFXState::ptr)(21);
                DAT_TileMapState::instance.currentMapperCommand = (Commands::MappersEnum)0;
                break;
            case 160:
            case 161:
            case 162:
            case 163:
            case 164:
            case 165:
            case 166:
            case 167:
            case 168:
            case 169:
            case 170:
            case 171:
            case 175:
            case 313:
            case 314:
            case 315:
            case 316:
            case 317:
            case 318:
            case 319:
            case 320:
            case 321:
            case 322:
            case 324:
            case 325:
            case 326:
            case 327:
            case 328:
            case 330:
                MACRO_CALL(UI::Helpers_Func::SetTaxesSetting_unknown)(2);
                break;
            case 176:
            case 177:
            case 301:
            case 302:
            case 303:
            case 304:
            case 305:
            case 306:
            case 307:
            case 308:
            case 310:
            case 311:
                MACRO_CALL(UI::Helpers_Func::SetTaxesSetting_unknown)(3);
                break;
            }
        }

    } // namespace MenuItems
} // namespace UI
} // namespace OpenSHC
