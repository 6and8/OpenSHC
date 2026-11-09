#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Map/Entities.func.hpp"
#include "OpenSHC/Map/Entities/EntityState.func.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Rendering/ViewportRenderState.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/UI/BottomLeftTextDisplayState.func.hpp"
#include "OpenSHC/UI/MenuItems/BuildMenu.func.hpp"
#include "OpenSHC/Commands/GameCommandType.hpp"
#include "OpenSHC/Commands/MappersEnum.hpp"
#include "OpenSHC/Map/Entities/EntityType.hpp"
#include "OpenSHC/Map/Units/States/UnitState.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"

#include "OpenSHC/Globals/DAT_BottomLeftTextDisplayState.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_EntityState.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MouseState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"
#include "OpenSHC/Globals/DAT_WallAndPitchState.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {
        namespace BuildMenu {

            // FUNCTION: STRONGHOLDCRUSADER 0x004387D0
            void MenuItemActionHandler_BuildMenu_DeleteAction(int param_1, ...)
            {
                if (DAT_GameSynchronyState::instance.syncStatus != 0
                    || DAT_GameSynchronyState::instance.saveRelated != 0
                    || DAT_TileMapState::instance.currentMapperCommand != OpenSHC::Commands::M_MAPPER_DELETE) {
                    return;
                }
                DAT_TileMapState::instance.demolishBlocked = 0;
                if (DAT_ViewportRenderState::instance.viewportState.field_0x0 == 0) {
                    return;
                }
                MACRO_CALL_MEMBER(
                    OpenSHC::Rendering::ViewportRenderState_Func::setupMouseTileXY, DAT_ViewportRenderState::ptr)();
                int const tileY = DAT_ViewportRenderState::instance.viewportState.mouseTileY;
                int const tileX = DAT_ViewportRenderState::instance.viewportState.mouseTileX;
                DAT_TileMapState::instance.DAT_ClickedTileX = tileX;
                DAT_TileMapState::instance.DAT_ClickedTileY = tileY;
                if (DAT_GameCore::instance.gameMode_2 != 1 && DAT_GameCore::instance.gameMode_2 != 6) {
                    if (MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::isEnemyTooCloseUnk,
                            DAT_PathFindingState::ptr)(DAT_GameSynchronyState::instance.currentPlayerSlotID, tileX,
                            tileY, DAT_GameSynchronyState::instance.currentGameMode == 0 ? 0x1e : 0x0f)) {
                        DAT_TileMapState::instance.demolishBlocked = 1;
                    }
                }
                if (DAT_MouseState::instance.leftClickStart == 0) {
                    if (DAT_TileMapState::instance.placementOnWall != 0
                        || DAT_TileMapState::instance.placementOnMoat != 0
                        || DAT_MouseState::instance.leftClickState != 0) {
                        return;
                    }
                    DAT_TileMapState::instance.placementOnWall = 0;
                    DAT_TileMapState::instance.placementOnMoat = 0;
                    return;
                }
                int const playerID = DAT_GameSynchronyState::instance.currentPlayerSlotID;
                if (DAT_GameCore::instance.solitaryAltUDungeon != 0
                    && DAT_ViewportRenderState::instance.viewportState.mouseRayUnitID != 0) {
                    int const unitID = DAT_ViewportRenderState::instance.viewportState.mouseRayUnitID;
                    if (DAT_UnitsState::instance.units[unitID].health != 0
                        && DAT_UnitsState::instance.units[unitID].unitType != OpenSHC::Map::Units::UT_LORD
                        && DAT_UnitsState::instance.units[unitID].dying == 0
                        && DAT_UnitsState::instance.units[unitID].owner == playerID
                        && DAT_GameSynchronyState::instance.currentGameMode == 0) {
                        if (DAT_UnitsState::instance.units[unitID].unitType == OpenSHC::Map::Units::UT_E_ENGINEER
                            && DAT_UnitsState::instance.units[unitID].resourceToDeposit != 0) {
                            MACRO_CALL(OpenSHC::Map::Entities_Func::IgniteFireAtMiniTile_Convenience)(
                                DAT_UnitsState::instance.units[unitID].owner,
                                DAT_UnitsState::instance.units[unitID].microXPosition,
                                DAT_UnitsState::instance.units[unitID].microYPosition,
                                DAT_UnitsState::instance.units[unitID].buildingHeight
                                    + DAT_UnitsState::instance.units[unitID].terrainOrClimbHeight - 8,
                                5);
                            MACRO_CALL_MEMBER(OpenSHC::Map::Entities::EntityState_Func::spawnProjectileEntity,
                                DAT_EntityState::ptr)(0, DAT_UnitsState::instance.units[unitID].owner, 0,
                                DAT_UnitsState::instance.units[unitID].microXPosition,
                                DAT_UnitsState::instance.units[unitID].microYPosition,
                                DAT_UnitsState::instance.units[unitID].terrainOrClimbHeight
                                    + DAT_UnitsState::instance.units[unitID].buildingHeight,
                                0, 0, 0, OpenSHC::Map::Entities::EntityTypeInt__ET_EXPLOSION, 0);
                        }
                        DAT_UnitsState::instance.units[unitID].dying = 1;
                        DAT_UnitsState::instance.units[unitID].tunnelerFinishedDigging = 1;
                        DAT_UnitsState::instance.units[unitID].animationCycleNumber = 0;
                        DAT_UnitsState::instance.units[unitID].state.generic
                            = OpenSHC::Map::Units::States::US_STONE_DEATH_01;
                        MACRO_CALL_MEMBER(OpenSHC::Map::Entities::EntityState_Func::spawnProjectileEntity,
                            DAT_EntityState::ptr)(0, 0, 0, DAT_UnitsState::instance.units[unitID].microXPosition,
                            DAT_UnitsState::instance.units[unitID].microYPosition,
                            DAT_UnitsState::instance.units[unitID].buildingHeight
                                + DAT_UnitsState::instance.units[unitID].terrainOrClimbHeight,
                            DAT_UnitsState::instance.units[unitID].microXPosition + 1,
                            DAT_UnitsState::instance.units[unitID].microYPosition + 1,
                            DAT_UnitsState::instance.units[unitID].buildingHeight
                                + DAT_UnitsState::instance.units[unitID].terrainOrClimbHeight,
                            (OpenSHC::Map::Entities::EntityType)0x1e, 0);
                        MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                            DAT_UnitsState::instance.units[unitID].x, DAT_UnitsState::instance.units[unitID].y,
                            OpenSHC::DE::SHCDE::eSFX(0x97));
                        return;
                    }
                }
                DAT_TileMapState::instance.buildingPlacementFailReason = 0;
                if (MACRO_CALL_MEMBER(
                        OpenSHC::Map::TileMapState_Func::spreadFlagPlacementAlgorithm, DAT_TileMapState::ptr)(playerID,
                        DAT_TileMapState::instance.DAT_ClickedTileX, DAT_TileMapState::instance.DAT_ClickedTileY)) {
                    DAT_WallAndPitchState::instance.countdown = 0;
                    DAT_GameSynchronyState::instance.DAT_GameCommandParam0
                        = DAT_TileMapState::instance.DAT_ClickedTileX;
                    DAT_GameSynchronyState::instance.DAT_GameCommandParam1
                        = DAT_TileMapState::instance.DAT_ClickedTileY;
                    MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::queueCommand,
                        DAT_GameSynchronyState::ptr)((OpenSHC::Commands::GameCommandType)0x61);
                    return;
                }
                MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::evaluateBuildingPlacementAtCursor,
                    DAT_TileMapState::ptr)(DAT_GameSynchronyState::instance.currentPlayerSlotID,
                    DAT_TileMapState::instance.DAT_ClickedTileX, DAT_TileMapState::instance.DAT_ClickedTileY);
                if (DAT_TileMapState::instance.buildingPlacementFail != 0) {
                    int const reason = DAT_TileMapState::instance.buildingPlacementFailReason;
                    if (reason == 1000) {
                        MACRO_CALL_MEMBER(OpenSHC::UI::BottomLeftTextDisplayState_Func::setBottomLeftTextDisplayText,
                            DAT_BottomLeftTextDisplayState::ptr)(1, 0x101, 2, 0, 100, 6000);
                    } else if (reason != 0) {
                        MACRO_CALL_MEMBER(OpenSHC::UI::BottomLeftTextDisplayState_Func::setBottomLeftTextDisplayText,
                            DAT_BottomLeftTextDisplayState::ptr)(1, 0x4d, reason, 0, 100, 6000);
                    }
                    return;
                }
                DAT_WallAndPitchState::instance.countdown = 0;
                int tile;
                if (DAT_TileMapState::instance.placementOnMoat != 0) {
                    tile = DAT_TileMapState::instance.savedCursorTile;
                    DAT_GameSynchronyState::instance.DAT_GameCommandParam1 = -1;
                } else {
                    DAT_GameSynchronyState::instance.DAT_GameCommandParam1 = 0x32;
                    if (DAT_TileMapState::instance.placementOnWall == 0) {
                        int const targetID = DAT_TileMapState::instance.cursorTargetID;
                        DAT_GameSynchronyState::instance.DAT_GameCommandParam0 = targetID;
                        if (targetID < 0) {
                            DAT_GameSynchronyState::instance.DAT_GameCommandParam2
                                = DAT_TileMapState::instance.pitchDitches[-targetID].uid;
                        } else {
                            DAT_GameSynchronyState::instance.DAT_GameCommandParam2
                                = DAT_BuildingsState::instance.buildings[targetID].uid;
                        }
                        MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::queueCommand,
                            DAT_GameSynchronyState::ptr)(OpenSHC::Commands::GCT_DESTROY_BUILDING);
                        return;
                    }
                    tile = DAT_ViewportRenderState::instance.viewportState.cursorWallTile;
                }
                DAT_GameSynchronyState::instance.DAT_GameCommandParam0 = tile;
                short* MiscDisplayLayerPtr = &DAT_TileMapState::instance.MiscDisplayLayer[tile];
                *MiscDisplayLayerPtr |= 0x400;
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::queueCommand,
                    DAT_GameSynchronyState::ptr)(OpenSHC::Commands::GCT_DESTROY2Unk);
            }

        }
    }
}
}
