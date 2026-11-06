#include "../EntityState.func.hpp"

#include <stdlib.h>

#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/DE/SHCDE/eSFX.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Entities.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_EntityDefinedData.hpp"
#include "OpenSHC/Globals/DAT_EntityState.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"
#include "OpenSHC/Globals/SEC_RNG.hpp"

namespace OpenSHC {
namespace Map {
    namespace Entities {

        using namespace OpenSHC::Map::Buildings;

        // FUNCTION: STRONGHOLDCRUSADER 0x00407190
        undefined4 EntityState::processEntityHitBuildingOrUnit(int entityID)
        {
            this->entityArray[entityID].xPosition = this->entityArray[entityID].microX / 8;
            this->entityArray[entityID].yPosition = this->entityArray[entityID].microY / 8;
            int const x = this->entityArray[entityID].xPosition;
            int const y = this->entityArray[entityID].yPosition;
            int const tile = DAT_ViewportRenderState::instance.translationMatrix[y].addXgetTile + x;
            undefined4 result = 1;
            this->entityArray[entityID].tile = tile;
            if (this->entityArray[entityID].entityType == ET_SEAGULLUnk) {
                if ((uint)x <= 399 && (uint)y <= 399
                    && DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[y * 400 + x] != 0
                    && (DAT_TileMapState::instance.LogicLayer[tile] & 0x30) == 0
                    && this->entityArray[entityID].height > 0) {
                    this->entityArray[entityID].nextEntityOnThisTileByID = DAT_TileMapState::instance.EntityLayer[tile];
                    DAT_TileMapState::instance.EntityLayer[tile] = entityID;
                    return 1;
                }
                this->entityArray[entityID].tile = 0;
                return 0;
            }
            if (!((uint)x <= 399 && (uint)y <= 399
                    && DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[y * 400 + x] != 0)) {
                this->entityArray[entityID].logicalState = 3;
                return 0;
            }
            if ((DAT_TileMapState::instance.LogicLayer[tile] & 0x30) != 0) {
                MACRO_CALL_MEMBER(EntityState_Func::markEntityDestroyed, this)(entityID);
                return 0;
            }
            int pitchID;
            if ((uint)(this->entityArray[entityID].entityType - ET_FLAG_1) <= 5) {
                DAT_TileMapState::instance.MiscDisplayLayer[tile] |= 0x1000;
                if (this->entityArray[entityID].entityType != ET_BRAZIER
                    && this->entityArray[entityID].entityType != ET_HEADS_ON_SPIKES) {
                    int const entityTile = this->entityArray[entityID].tile;
                    uint const logic = DAT_TileMapState::instance.LogicLayer[entityTile];
                    if (logic != 0) {
                        if (DAT_TileMapState::instance.DamageLayer[entityTile] != 0) {
                            if ((logic & 0x400000) != 0) {
                                this->entityArray[entityID].height
                                    = DAT_TileMapState::instance.HeightLayer[entityTile] + 20;
                            } else if ((logic & 0x200) != 0) {
                                this->entityArray[entityID].height
                                    = DAT_TileMapState::instance.HeightLayer[entityTile] + 10;
                            } else {
                                this->entityArray[entityID].height = DAT_TileMapState::instance.HeightLayer[entityTile];
                            }
                        }
                    } else if (DAT_TileMapState::instance.BuildingLayer[entityTile] == 0) {
                        MACRO_CALL_MEMBER(EntityState_Func::markEntityDestroyed, this)(entityID);
                    }
                    goto end;
                }
                int const entityTile = this->entityArray[entityID].tile;
                short const buildingID = DAT_TileMapState::instance.BuildingLayer[entityTile];
                if (buildingID != 0) {
                    switch (DAT_BuildingsState::instance.buildings[buildingID].buildingType) {
                    case BT_STONEKEEP:
                    case BT_STRONGHOLD:
                    case BT_KEEPFOUR:
                    case BT_KEEPFIVE:
                    case BT_GATEHOUSELARGE:
                    case BT_GATEHOUSESMALL:
                    case BT_TOWER1:
                    case BT_TOWER2:
                    case BT_TOWER3:
                    case BT_TOWER4:
                    case BT_TOWER5:
                        this->entityArray[entityID].height = MACRO_CALL_MEMBER(
                            TileMapState_Func::getTotalHeightAtTile, DAT_TileMapState::ptr)(entityTile);
                        goto end;
                    }
                } else if ((DAT_TileMapState::instance.LogicLayer[entityTile] & 0x100) != 0) {
                    if (DAT_TileMapState::instance.DamageLayer[entityTile] != 0) {
                        this->entityArray[entityID].height = DAT_TileMapState::instance.HeightLayer[entityTile] + 15;
                    } else {
                        this->entityArray[entityID].height = DAT_TileMapState::instance.HeightLayer[entityTile];
                    }
                    goto end;
                }
                if (Game::GM_SIEGE_THAT == DAT_GameCore::instance.gameMode_2) {
                    int stone;
                    int gold;
                    MACRO_CALL_MEMBER(BuildingsState_Func::getBuildingCost, DAT_BuildingsState::ptr)(
                        Commands::M_MAPPER_BRAZIER, &stone, &gold);
                    DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                        .startResources[Game::Resources::RT_GOLD]
                        += gold;
                }
                MACRO_CALL_MEMBER(EntityState_Func::markEntityDestroyed, this)(entityID);
                goto end;
            }
            {
                int unitID = DAT_TileMapState::instance.UnitLayer[tile];
                if (this->entityArray[entityID].entityType != ET_ARROW_AND_DEFAULT
                    || this->entityArray[entityID].rng_2 != 2) {
                    if (this->entityArray[entityID].entityType == ET_COW_POISON_CLOUD
                        || this->entityArray[entityID].entityType == ET_TREBUCHET
                        || this->entityArray[entityID].entityType == ET_CATAPULT
                        || this->entityArray[entityID].entityType == ET_MANGONEL
                        || this->entityArray[entityID].velocityUnk > 80) {
                        for (; unitID != 0; unitID = DAT_UnitsState::instance.units[unitID].nextUnitOnTheSameTile) {
                            if (this->entityArray[entityID].logicalState == 2
                                && MACRO_CALL_MEMBER(Units::UnitsState_Func::processEntityDamageToUnit,
                                       DAT_UnitsState::ptr)(unitID, entityID, 0)
                                    != 0) {
                                if (this->entityArray[entityID].entityType == ET_COW_FLYING) {
                                    this->entityArray[entityID].height = MACRO_CALL_MEMBER(
                                        TileMapState_Func::returnSomeHeight, DAT_TileMapState::ptr)(tile, 0);
                                    goto cowHit;
                                }
                                MACRO_CALL_MEMBER(EntityState_Func::markEntityDestroyed, this)(entityID);
                                return 0;
                            }
                        }
                    }
                    if (this->entityArray[entityID].entityType == ET_TREBUCHET
                        || this->entityArray[entityID].entityType == ET_CATAPULT
                        || this->entityArray[entityID].entityType == ET_MANGONEL
                        || this->entityArray[entityID].velocityUnk > 80) {
                        for (int dir = 1; dir < 8; dir += 2) {
                            int const neighbour = DAT_TileMapState::instance
                                                      .directionTranslationMatrix[this->entityArray[entityID].yPosition][dir]
                                + tile;
                            for (int other = DAT_TileMapState::instance.UnitLayer[neighbour]; other != 0;
                                 other = DAT_UnitsState::instance.units[other].nextUnitOnTheSameTile) {
                                if (DAT_UnitsState::instance.units[other].field_0x90 != 0
                                    && this->entityArray[entityID].logicalState == 2
                                    && MACRO_CALL_MEMBER(Units::UnitsState_Func::processEntityDamageToUnit,
                                           DAT_UnitsState::ptr)(other, entityID, 1)
                                        != 0) {
                                    MACRO_CALL_MEMBER(EntityState_Func::markEntityDestroyed, this)(entityID);
                                    return 0;
                                }
                            }
                        }
                    }
                }
            }
            if (this->entityArray[entityID].entityType == ET_COW_POISON_CLOUD) {
                int const cloudHeight
                    = MACRO_CALL_MEMBER(TileMapState_Func::getTotalHeightAtTile, DAT_TileMapState::ptr)(tile);
                for (int dir = 0; dir < 8; dir++) {
                    int const neighbour
                        = DAT_TileMapState::instance.directionTranslationMatrix[this->entityArray[entityID].yPosition][dir]
                        + tile;
                    for (int unitID = DAT_TileMapState::instance.UnitLayer[neighbour]; unitID != 0;
                         unitID = DAT_UnitsState::instance.units[unitID].nextUnitOnTheSameTile) {
                        if (abs(cloudHeight
                                - (int)MACRO_CALL_MEMBER(TileMapState_Func::getTotalHeightAtTile, DAT_TileMapState::ptr)(
                                    neighbour))
                                < 120
                            && this->entityArray[entityID].logicalState == 2) {
                            MACRO_CALL_MEMBER(Units::UnitsState_Func::processEntityDamageToUnit, DAT_UnitsState::ptr)(
                                unitID, entityID, 1);
                        }
                    }
                }
                for (int i = 0; i < 16; i++) {
                    int const blastTile
                        = MACRO_CALL_MEMBER(TileMapState_Func::computeTileAlongAxisOffset, DAT_TileMapState::ptr)(tile,
                            DAT_EntityDefinedData::instance.EntityBlastTileOffsets[i].xOffset,
                            DAT_EntityDefinedData::instance.EntityBlastTileOffsets[i].yOffset);
                    for (int unitID = DAT_TileMapState::instance.UnitLayer[blastTile]; unitID != 0;
                         unitID = DAT_UnitsState::instance.units[unitID].nextUnitOnTheSameTile) {
                        if (abs(cloudHeight
                                - (int)MACRO_CALL_MEMBER(TileMapState_Func::getTotalHeightAtTile, DAT_TileMapState::ptr)(
                                    blastTile))
                                < 120
                            && this->entityArray[entityID].logicalState == 2) {
                            MACRO_CALL_MEMBER(Units::UnitsState_Func::processEntityDamageToUnit, DAT_UnitsState::ptr)(
                                unitID, entityID, 2);
                        }
                    }
                }
            }
            if (this->entityArray[entityID].entityType == ET_FIRE
                && (DAT_TileMapState::instance.LogicLayer[this->entityArray[entityID].tile] & 8) != 0) {
                pitchID = MACRO_CALL_MEMBER(TileMapState_Func::getPitchDitchIDForTile, DAT_TileMapState::ptr)(
                    this->entityArray[entityID].tile);
                if (pitchID != 0 && DAT_TileMapState::instance.pitchDitches[pitchID].state == 1) {
                    MACRO_CALL(Entities_Func::SetPlaceOnFire)(this->entityArray[entityID].owner,
                        DAT_TileMapState::instance.pitchDitches[pitchID].x * 8,
                        DAT_TileMapState::instance.pitchDitches[pitchID].y * 8,
                        DAT_TileMapState::instance.HeightLayer[DAT_TileMapState::instance.pitchDitches[pitchID].tile], 3);
                    DAT_TileMapState::instance.pitchDitches[pitchID].state = 2;
                }
            }
            {
                int groundHeight
                    = MACRO_CALL_MEMBER(TileMapState_Func::returnSomeHeight, DAT_TileMapState::ptr)(tile, 0);
                int const buildingID = DAT_TileMapState::instance.BuildingLayer[tile];
                if (buildingID != 0) {
                    int const buildingType = DAT_BuildingsState::instance.buildings[buildingID].buildingType;
                    if ((buildingType == BT_TOWER || (uint)(buildingType - BT_TOWER1) <= 4)
                        && (this->entityArray[entityID].rng_1 & 4) != 0) {
                        groundHeight += 20;
                    }
                }
                if (groundHeight <= this->entityArray[entityID].height) {
                    goto end;
                }
            }
            if (this->entityArray[entityID].entityType == 32) {
                if (this->entityArray[entityID].height >= DAT_TileMapState::instance.DefaultHeightLayer[tile]) {
                    goto end;
                }
                this->entityArray[entityID].someCounter_OR_hitGround = 1;
                if ((DAT_TileMapState::instance.LogicLayer[tile] & 0x10000100) != 0) {
                    goto end;
                }
                if (DAT_TileMapState::instance.DefaultHeightLayer[tile]
                    >= this->entityArray[entityID].startingHeight_2 + 50) {
                    goto end;
                }
                MACRO_CALL(Entities_Func::IgniteFireAtMiniTile_Convenience)(this->entityArray[entityID].owner,
                    this->entityArray[entityID].microX, this->entityArray[entityID].microY,
                    DAT_TileMapState::instance.HeightLayer[this->entityArray[entityID].tile] - 8, 2);
                if ((DAT_TileMapState::instance.LogicLayer[tile] & 8) == 0) {
                    goto end;
                }
                pitchID = MACRO_CALL_MEMBER(TileMapState_Func::getPitchDitchIDForTile, DAT_TileMapState::ptr)(tile);
                if (pitchID == 0) {
                    goto end;
                }
                MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                    this->entityArray[entityID].xPosition, this->entityArray[entityID].yPosition, DE::SHCDE::FX_IGNITE_PITCH);
                MACRO_CALL(Entities_Func::SetPlaceOnFire)(this->entityArray[entityID].owner,
                    DAT_TileMapState::instance.pitchDitches[pitchID].x * 8,
                    DAT_TileMapState::instance.pitchDitches[pitchID].y * 8,
                    DAT_TileMapState::instance.HeightLayer[DAT_TileMapState::instance.pitchDitches[pitchID].tile], 3);
                if (DAT_TileMapState::instance.pitchDitches[pitchID].state == 1) {
                    DAT_TileMapState::instance.pitchDitches[pitchID].state = 2;
                }
                goto end;
            }
            if (this->entityArray[entityID].entityType == 27) {
                if (this->entityArray[entityID].height > DAT_TileMapState::instance.DefaultHeightLayer[tile]) {
                    goto end;
                }
                this->entityArray[entityID].someCounter_OR_hitGround = 1;
                if ((DAT_TileMapState::instance.LogicLayer[tile] & 0x40100001) == 0) {
                    goto end;
                }
                if (this->entityArray[entityID].unitID_OR_seaGullID != 0) {
                    goto end;
                }
                {
                    int const splashHeight
                        = DAT_TileMapState::instance.HeightLayer[this->entityArray[entityID].tile] + 2;
                    MACRO_CALL_MEMBER(EntityState_Func::spawnProjectileEntity, this)(1, 0, 0,
                        this->entityArray[entityID].microX, this->entityArray[entityID].microY, splashHeight,
                        this->entityArray[entityID].microX, this->entityArray[entityID].microY, splashHeight,
                        (EntityType)31, 0);
                }
                MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                    this->entityArray[entityID].xPosition, this->entityArray[entityID].yPosition, DE::SHCDE::FX_MED_PLOP);
                goto end;
            }
            if (this->entityArray[entityID].entityType == 8) {
                if (abs(this->entityArray[entityID].height - this->entityArray[entityID].targetZ) < 20
                    || this->entityArray[entityID].height <= 8) {
                    this->entityArray[entityID].someCounter_OR_hitGround = 1;
                }
                goto end;
            }
            if (this->entityArray[entityID].entityType == ET_ARROW_AND_DEFAULT
                || this->entityArray[entityID].entityType == ET_CROSSBOWARROW
                || this->entityArray[entityID].entityType == ET_BALLISTA
                || this->entityArray[entityID].entityType == ET_SLINGER
                || this->entityArray[entityID].entityType == ET_FIRETHROWER) {
                if (this->entityArray[entityID].rng_2 == 2) {
                    for (int dir = 0; dir < 8; dir++) {
                        int const neighbour = DAT_TileMapState::instance
                                                  .directionTranslationMatrix[this->entityArray[entityID].yPosition][dir]
                            + tile;
                        if ((DAT_TileMapState::instance.LogicLayer[neighbour] & 8) != 0) {
                            pitchID = MACRO_CALL_MEMBER(TileMapState_Func::getPitchDitchIDForTile, DAT_TileMapState::ptr)(
                                neighbour);
                            if (pitchID != 0) {
                                goto ignitePitch;
                            }
                        }
                    }
                }
                int buildingID = DAT_TileMapState::instance.BuildingLayer[tile];
                if (this->entityArray[entityID].travelledDistance <= this->entityArray[entityID].totalFlightDistance / 2) {
                    goto end;
                }
                uint logic = DAT_TileMapState::instance.LogicLayer[tile];
                if ((logic & 0x40100001) != 0) {
                    int const splashHeight
                        = DAT_TileMapState::instance.HeightLayer[this->entityArray[entityID].tile] + 2;
                    MACRO_CALL_MEMBER(EntityState_Func::spawnProjectileEntity, this)(1, 0, 0,
                        this->entityArray[entityID].microX, this->entityArray[entityID].microY, splashHeight,
                        this->entityArray[entityID].microX, this->entityArray[entityID].microY, splashHeight,
                        (EntityType)31, 0);
                    this->entityArray[entityID].logicalState = 3;
                    result = 0;
                    MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                        this->entityArray[entityID].xPosition, this->entityArray[entityID].yPosition, DE::SHCDE::FX_LITTLE_PLOP);
                    goto end;
                }
                if ((logic & 0x10000100) != 0
                    || (buildingID != 0
                        && (DAT_BuildingsState::instance.buildings[buildingID].buildingType == BT_STONEKEEP
                            || DAT_BuildingsState::instance.buildings[buildingID].buildingType == BT_STRONGHOLD
                            || DAT_BuildingsState::instance.buildings[buildingID].buildingType == BT_KEEPFOUR
                            || DAT_BuildingsState::instance.buildings[buildingID].buildingType == BT_KEEPFIVE))) {
                    if ((this->entityArray[entityID].rotationFrameIndex < 3
                            && this->entityArray[entityID].startingAngle < 0)
                        || this->entityArray[entityID].hasDoneEffectUnk != 0
                        || this->entityArray[entityID].clearanceStepsRemaining > 0) {
                        goto end;
                    }
                    MACRO_CALL_MEMBER(EntityState_Func::handleProjectileWallBounce, this)(entityID);
                    result = 0;
                    goto end;
                }
                if ((logic & 8) != 0) {
                    if (this->entityArray[entityID].rng_2 == 2) {
                        pitchID = MACRO_CALL_MEMBER(TileMapState_Func::getPitchDitchIDForTile, DAT_TileMapState::ptr)(
                            tile);
                        if (pitchID != 0) {
                        ignitePitch:
                            MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                                this->entityArray[entityID].xPosition, this->entityArray[entityID].yPosition,
                                DE::SHCDE::FX_IGNITE_PITCH);
                            MACRO_CALL(Entities_Func::SetPlaceOnFire)(this->entityArray[entityID].owner,
                                DAT_TileMapState::instance.pitchDitches[pitchID].x * 8,
                                DAT_TileMapState::instance.pitchDitches[pitchID].y * 8,
                                DAT_TileMapState::instance
                                    .HeightLayer[DAT_TileMapState::instance.pitchDitches[pitchID].tile],
                                3);
                            if (DAT_TileMapState::instance.pitchDitches[pitchID].state == 1) {
                                DAT_TileMapState::instance.pitchDitches[pitchID].state = 2;
                            }
                        }
                    }
                    this->entityArray[entityID].someCounter_OR_hitGround = 1;
                    result = 0;
                    goto end;
                }
                if (buildingID != 0) {
                    int const shooterID = this->entityArray[entityID].unitID_OR_seaGullID;
                    int const buildingType = DAT_BuildingsState::instance.buildings[buildingID].buildingType;
                    if (buildingType >= BT_TOWER1 && buildingType <= BT_TOWER5) {
                        goto end;
                    }
                    if (DAT_BuildingsState::instance.buildings[buildingID].currentHealth == 0) {
                        goto end;
                    }
                    if ((logic & 0xf000000) != 0) {
                        goto end;
                    }
                    if (DAT_UnitsState::instance.units[shooterID].unitType == Units::UT_S_FBALLISTA) {
                        MACRO_CALL_MEMBER(TileMapState_Func::processDamageToBuilding, DAT_TileMapState::ptr)(tile,
                            this->entityArray[entityID].xPosition, this->entityArray[entityID].yPosition, 10, 0,
                            this->entityArray[entityID].owner, FALSE, shooterID);
                        if (MACRO_CALL_MEMBER(
                                TileMapState_Func::getNonFarmFieldBuildingHealthAtTileOr1000, DAT_TileMapState::ptr)(tile)
                            < 50) {
                            MACRO_CALL(Entities_Func::SetPlaceOnFire)(this->entityArray[entityID].owner,
                                this->entityArray[entityID].xPosition * 8, this->entityArray[entityID].yPosition * 8,
                                DAT_TileMapState::instance.HeightLayer[this->entityArray[entityID].tile], 3);
                        }
                    } else if (this->entityArray[entityID].entityType == ET_BALLISTA) {
                        MACRO_CALL_MEMBER(TileMapState_Func::processDamageToBuilding, DAT_TileMapState::ptr)(tile,
                            this->entityArray[entityID].xPosition, this->entityArray[entityID].yPosition, 2, 0,
                            this->entityArray[entityID].owner, FALSE, shooterID);
                    } else {
                        MACRO_CALL_MEMBER(TileMapState_Func::processDamageToBuilding, DAT_TileMapState::ptr)(tile,
                            this->entityArray[entityID].xPosition, this->entityArray[entityID].yPosition, 1, 0,
                            this->entityArray[entityID].owner, FALSE, shooterID);
                    }
                    this->entityArray[entityID].someCounter_OR_hitGround = 1;
                } else {
                    this->entityArray[entityID].someCounter_OR_hitGround = 40;
                }
                result = 0;
                goto end;
            }
            if (this->entityArray[entityID].entityType == ET_TREBUCHET
                || this->entityArray[entityID].entityType == ET_CATAPULT
                || this->entityArray[entityID].entityType == ET_MANGONEL) {
                this->entityArray[entityID].someCounter_OR_hitGround = 1;
                uint const logic = DAT_TileMapState::instance.LogicLayer[tile];
                int damage = 10;
                int collateral = 10;
                if ((logic & 0x40100001) != 0) {
                    MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                        this->entityArray[entityID].xPosition, this->entityArray[entityID].yPosition, DE::SHCDE::FX_ROCK_SPLASH);
                }
                uint const wall = logic & 0x100;
                if (wall == 0 && (logic & 0x10000400) == 0 && DAT_TileMapState::instance.BuildingLayer[tile] == 0) {
                    DAT_UnitsState::instance.units[this->entityArray[entityID].unitID_OR_seaGullID].field_0xd2 += 1;
                    if ((logic & 0x4a5014b1) != 0) {
                        if ((logic & 0x40100001) != 0) {
                            for (int i = 0; i < this->entityArray[entityID].rng_1 % 16 + 10; i++) {
                                short const rng = SEC_RNG::instance.currentNumber2;
                                MACRO_CALL_MEMBER(EntityState_Func::spawnProjectileEntity, this)(1, 0, 0,
                                    this->entityArray[entityID].microX, this->entityArray[entityID].microY,
                                    DAT_TileMapState::instance.HeightLayer[this->entityArray[entityID].tile] + 2,
                                    rng % 80 + this->entityArray[entityID].microX - 40,
                                    (rng >> 8) % 80 + this->entityArray[entityID].microY - 40, 8, (EntityType)27, 0);
                            }
                            int const splashHeight
                                = DAT_TileMapState::instance.HeightLayer[this->entityArray[entityID].tile] + 2;
                            MACRO_CALL_MEMBER(EntityState_Func::spawnProjectileEntity, this)(0, 0, 0,
                                this->entityArray[entityID].microX, this->entityArray[entityID].microY, splashHeight,
                                this->entityArray[entityID].microX, this->entityArray[entityID].microY, splashHeight,
                                (EntityType)31, 0);
                        }
                    } else {
                        MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                            this->entityArray[entityID].xPosition, this->entityArray[entityID].yPosition,
                            DE::SHCDE::FX_ROCK_HIT_GROUND);
                        this->entityArray[entityID].someCounter_OR_hitGround = 40;
                        for (int i = 0; i < this->entityArray[entityID].rng_1 % 8 + 5; i++) {
                            short const rng = SEC_RNG::instance.currentNumber2;
                            MACRO_CALL_MEMBER(EntityState_Func::spawnProjectileEntity, this)(2, 0, 0,
                                this->entityArray[entityID].microX, this->entityArray[entityID].microY,
                                DAT_TileMapState::instance.HeightLayer[this->entityArray[entityID].tile] + 2,
                                rng % 80 + this->entityArray[entityID].microX - 40,
                                (rng >> 8) % 80 + this->entityArray[entityID].microY - 40, 8, (EntityType)27, 0);
                        }
                    }
                    result = 0;
                    goto end;
                }
                MACRO_CALL_MEMBER(EntityState_Func::spawnProjectileImpactDebris, this)(entityID);
                if (this->entityArray[entityID].entityType == ET_TREBUCHET) {
                    damage = 60;
                    collateral = 30;
                } else if (this->entityArray[entityID].entityType == ET_CATAPULT) {
                    damage = 20;
                } else if (this->entityArray[entityID].entityType == ET_MANGONEL) {
                    damage = 5;
                    collateral = 0;
                }
                int const buildingID = DAT_TileMapState::instance.BuildingLayer[tile];
                if (buildingID != 0) {
                    if (DAT_GameState::instance.mapAndTime
                            .playerTeams[DAT_BuildingsState::instance.buildings[buildingID].owner]
                        == DAT_GameState::instance.mapAndTime.playerTeams[this->entityArray[entityID].owner]) {
                        damage = 0;
                        collateral = 0;
                    }
                } else if (wall != 0) {
                    if (DAT_GameState::instance.mapAndTime.playerTeams[this->entityArray[entityID].owner]
                        == DAT_GameState::instance.mapAndTime
                               .playerTeams[(DAT_TileMapState::instance.WallOwnerLayer[tile] & 7) + 1]) {
                        damage = 0;
                        collateral = 0;
                    }
                }
                if (this->entityArray[entityID].entityType == ET_MANGONEL) {
                    MACRO_CALL_MEMBER(TileMapState_Func::processDamageToBuilding, DAT_TileMapState::ptr)(tile,
                        this->entityArray[entityID].xPosition, this->entityArray[entityID].yPosition, damage, 0,
                        -this->entityArray[entityID].owner, FALSE, this->entityArray[entityID].unitID_OR_seaGullID);
                    MACRO_CALL_MEMBER(TileMapState_Func::processEntityDamageToBuildingCollateral, DAT_TileMapState::ptr)(
                        tile, this->entityArray[entityID].xPosition, this->entityArray[entityID].yPosition, collateral,
                        -this->entityArray[entityID].owner, 0, this->entityArray[entityID].unitID_OR_seaGullID);
                } else {
                    MACRO_CALL_MEMBER(TileMapState_Func::processDamageToBuilding, DAT_TileMapState::ptr)(tile,
                        this->entityArray[entityID].xPosition, this->entityArray[entityID].yPosition, damage, 0,
                        this->entityArray[entityID].owner, FALSE, this->entityArray[entityID].unitID_OR_seaGullID);
                    MACRO_CALL_MEMBER(
                        TileMapState_Func::processEntityDamageToBuildingCollateralThunk, DAT_TileMapState::ptr)(tile,
                        this->entityArray[entityID].xPosition, this->entityArray[entityID].yPosition, collateral,
                        this->entityArray[entityID].owner, 0);
                }
                MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                    this->entityArray[entityID].xPosition, this->entityArray[entityID].yPosition, DE::SHCDE::FX_ROCK_HIT_WALL);
                result = 0;
                goto end;
            }
            if (this->entityArray[entityID].entityType != ET_COW_FLYING) {
                goto end;
            }
        cowHit:
            if (this->entityArray[entityID].hasDoneEffectUnk == 0) {
                MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                    this->entityArray[entityID].xPosition, this->entityArray[entityID].yPosition, DE::SHCDE::FX_COW_SPLAT);
                this->entityArray[entityID].hasDoneEffectUnk = 1;
                if ((DAT_TileMapState::instance.LogicLayer[tile] & 0x401000b1) != 0) {
                    this->entityArray[entityID].someCounter_OR_hitGround = 1;
                } else {
                    this->entityArray[entityID].someCounter_OR_hitGround = 40;
                    int const cloudCount = SEC_RNG::instance.currentNumber2 % 5 - 2;
                    DAT_GameCore::instance.cowPoisonTrackerUnk += 500;
                    for (int i = cloudCount; i < 8; i++) {
                        MACRO_CALL_MEMBER(EntityState_Func::spawnProjectileEntity, DAT_EntityState::ptr)(0,
                            this->entityArray[entityID].owner, 0, this->entityArray[entityID].microX,
                            this->entityArray[entityID].microY, this->entityArray[entityID].height, 0, 0, 0,
                            ET_COW_POISON_CLOUD, 0);
                    }
                    MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                        this->entityArray[entityID].xPosition, this->entityArray[entityID].yPosition, DE::SHCDE::FX_FLIES);
                }
            }
            result = 0;
        end:
            if (entityID != 0) {
                if (entityID < 25) {
                    this->entityArray[entityID].nextEntityOnThisTileByID
                        = (byte)DAT_TileMapState::instance.EntityLayerLT25[tile];
                    DAT_TileMapState::instance.EntityLayerLT25[tile] = entityID;
                } else {
                    this->entityArray[entityID].nextEntityOnThisTileByID = DAT_TileMapState::instance.EntityLayer[tile];
                    DAT_TileMapState::instance.EntityLayer[tile] = entityID;
                }
            }
            return result;
        }

    } // namespace Entities
} // namespace Map
} // namespace OpenSHC
