#include "../LandscapeState.func.hpp"

#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/UI/DisplayElements.func.hpp"
#include "OpenSHC/Map/LogicHelpers/Logic1.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_LandscapeState.hpp"
#include "OpenSHC/Globals/DAT_OrganismDefinedData.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x004F3960
    void LandscapeState::updateTreeStage(uint treeID, uint rng)
    {
        if (DAT_GameSynchronyState::instance.currentGameMode == Game::GM_SOLITARY) {
            if (DAT_GameCore::instance.isTimeHalted) {
                return;
            }
            if (MACRO_CALL(UI::DisplayElements_Func::GetIfDisplayElementStateNotZero)(
                    UI::Enums::DEID_KEEP_AND_GRANERY_PLACEMENT_INFO)) {
                return;
            }
        }
        if ((this->trees[treeID].rng1 & 0x3f) != rng) {
            return;
        }
        int const treeType = this->trees[treeID].treeType;
        if (treeType >= 5 && treeType <= Trees::TT_UNKNOWN_19) {
            return;
        }
        if (this->trees[treeID].zeroUpTo2 != 0) {
            return;
        }
        if ((short)this->trees[treeID].stageRelated1 < (short)this->trees[treeID].stageRelated2) {
            return;
        }
        if (this->field_0x4 == 0) {
            return;
        }
        if (DAT_GameCore::instance.currentMenuViewType == UI::Enums::MVT_MAP_EDITOR_LANDSCAPING) {
            return;
        }
        this->trees[treeID].stageTracker += 1;
        if (this->trees[treeID].stageTracker
            < DAT_OrganismDefinedData::instance.TreeStageLevels[treeType][this->trees[treeID].stage + 1]) {
            return;
        }
        int const nextStage = this->trees[treeID].stage + 1;
        this->trees[treeID].stage = nextStage;
        MACRO_CALL_MEMBER(LandscapeState_Func::setTreeStageRelatedValues, this)(treeID, nextStage);
        if (this->trees[treeID].stage >= 6) {
            this->trees[treeID].state = 3;
            return;
        }
        if (this->trees[treeID].stage < 4) {
            return;
        }
        DAT_GameState::instance.mapAndTime.treeSpreadCounter += 1;
        if (DAT_GameState::instance.mapAndTime.treeSpreadCounter
            > DAT_GameState::instance.mapAndTime.treeSpreadInterval) {
            DAT_GameState::instance.mapAndTime.treeSpreadCounter = 0;
            this->trees[treeID].stage = 5;
            this->trees[treeID].stageTracker
                = DAT_OrganismDefinedData::instance.TreeStageLevels[this->trees[treeID].treeType][5];
            return;
        }
        this->trees[treeID].stageTracker
            = DAT_OrganismDefinedData::instance.TreeStageLevels[this->trees[treeID].treeType][3];
        this->trees[treeID].stage = 3;
        DAT_GameState::instance.mapAndTime.newOrganismsValue2 += 1;
        if (!MACRO_CALL_MEMBER(LandscapeState_Func::setupBabyTreeLocation, this)(
                treeID, this->trees[treeID].treeType, this->trees[treeID].xPosition, this->trees[treeID].yPosition)) {
            return;
        }
        int const babyTreeType = this->trees[treeID].treeType;
        int const babyTreeID = MACRO_CALL_MEMBER(LandscapeState_Func::createTree, DAT_LandscapeState::ptr)(
            DAT_PathFindingState::instance.ALG_ResultX, DAT_PathFindingState::instance.ALG_ResultY,
            (Trees::TreeType)babyTreeType, MACRO_CALL_MEMBER( LandscapeState_Func::getValueFrom0UpTo3ForTreeTypeAndTreeStage, DAT_LandscapeState::ptr)(babyTreeType, 0), 0, 0, 0);
        DAT_TileMapState::instance.LogicLayer[DAT_PathFindingState::instance.ALG_ResultTile] |= LogicHelpers::L_TREE;
        DAT_TileMapState::instance.OrganismLayer[DAT_PathFindingState::instance.ALG_ResultTile] = babyTreeID;
        MACRO_CALL_MEMBER(TileMapState_Func::applyTreeBrushToLogicalLayer, DAT_TileMapState::ptr)(babyTreeID, 0);
        MACRO_CALL_MEMBER(Navigation::PathFindingState_Func::updatePathLinkagesInAllEightDirections,
            DAT_PathFindingState::ptr)(this->trees[babyTreeID].yPosition, this->trees[babyTreeID].tile);
        DAT_GameState::instance.mapAndTime.newOrganisms += 1;
        DAT_PathFindingState::instance.toggleUpdateSeparateAreaTileMap = 1;
    }

}
}
