#include "../LandscapeState.func.hpp"

#include "OpenSHC/Globals/DAT_CurrentTreeID.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_OrganismDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x004F1CE0
    int LandscapeState::createTree(undefined4 x, undefined4 y, TreeType treeType, undefined4 size,
        int stageRelatedValue, undefined4 param_6, int stage)
    {
        int treeID = 1;
        for (; treeID < 2000; ++treeID) {
            if (this->trees[treeID].state == 0) {
                break;
            }
            if (treeID >= 1999) {
                return 0;
            }
        }
        if (this->maxTreeCount <= treeID) {
            this->maxTreeCount = treeID + 1;
        }
        this->trees[treeID].uid = DAT_GameCore::instance.uniqueGameObjectTracker;
        DAT_GameCore::instance.uniqueGameObjectTracker += 1;
        switch (treeType) {
        case Trees::TT_UNKNOWN_16:
        case Trees::TT_UNKNOWN_17:
        case Trees::TT_UNKNOWN_18:
        case Trees::TT_UNKNOWN_19:
            this->trees[treeID].state = 4;
            break;
        default:
            this->trees[treeID].state = 1;
        }
        this->trees[treeID].size = (short)size;
        this->trees[treeID].xPosition = (short)x;
        this->trees[treeID].yPosition = (short)y;
        this->trees[treeID].treeType = (short)treeType;
        int const tile = (short)x + DAT_ViewportRenderState::instance.translationMatrix[(short)y].addXgetTile;
        this->trees[treeID].microX = (short)x * 8 + 3;
        this->trees[treeID].microY = (short)y * 8 + 3;
        this->trees[treeID].tile = tile;
        this->trees[treeID].rng1 = (ushort)DAT_TileMapState::instance.RandomLayer[tile] & 2047;
        this->trees[treeID].param_6 = (short)param_6;
        this->trees[treeID].appleTreeColorVariation = stageRelatedValue;
        this->trees[treeID].treeTypeBasedValue1
            = (short)DAT_OrganismDefinedData::instance.TreeTypeBasedValueMapping[treeType];
        this->trees[treeID].treeAdultHoodStageRelatedVisual3 = this->trees[treeID].stageRelated4
            = (short)DAT_OrganismDefinedData::instance.TreeRelated1[treeType][stage];
        this->trees[treeID].stageRelated1 = this->trees[treeID].stageRelated2
            = (short)DAT_OrganismDefinedData::instance.TreeRelated2[treeType][stage];
        this->trees[treeID].gmOriginX = DAT_TextureRenderCoreObject::instance
                                            .gmFileHeaderColorpaletteArray[this->trees[treeID].treeTypeBasedValue1]
                                            .originX;
        this->trees[treeID].gmOriginY = DAT_TextureRenderCoreObject::instance
                                            .gmFileHeaderColorpaletteArray[this->trees[treeID].treeTypeBasedValue1]
                                            .originY;
        this->trees[treeID].treeTypeRelated2 = DAT_OrganismDefinedData::instance.field_0x854[treeType];
        this->trees[treeID].zero = 0;
        this->trees[treeID].animationFrameIndex = DAT_TileMapState::instance.RandomLayer[tile] & 0x1f;
        this->trees[treeID].one = 1;
        this->trees[treeID].stage = stage;
        DAT_CurrentTreeID::instance = treeID;
        this->trees[treeID].stageTracker = DAT_OrganismDefinedData::instance.TreeStageLevels[treeType][stage];
        switch (treeType) {
        case Trees::TT_UNKNOWN_1:
            this->trees[treeID].appleTreeColorVariation = this->trees[treeID].rng1 & 0xf;
            if (this->trees[treeID].appleTreeColorVariation >= 15) {
                this->trees[treeID].appleTreeColorVariation = 4;
            } else if (this->trees[treeID].appleTreeColorVariation >= 13) {
                this->trees[treeID].appleTreeColorVariation = 6;
            } else if (this->trees[treeID].appleTreeColorVariation >= 11) {
                this->trees[treeID].appleTreeColorVariation = 1;
            } else if (this->trees[treeID].appleTreeColorVariation > 8) {
                this->trees[treeID].appleTreeColorVariation = 0;
            }
            break;
        case Trees::TT_UNKNOWN_2:
            this->trees[treeID].appleTreeColorVariation = this->trees[treeID].rng1 & 0xf;
            if (this->trees[treeID].appleTreeColorVariation > 8) {
                this->trees[treeID].appleTreeColorVariation = 8;
            }
            break;
        case Trees::TT_UNKNOWN_3:
            this->trees[treeID].appleTreeColorVariation = treeID % 9;
            break;
        case Trees::TT_UNKNOWN_4:
            this->trees[treeID].appleTreeColorVariation = this->trees[treeID].rng1 & 0xf;
            if (this->trees[treeID].appleTreeColorVariation >= 15) {
                this->trees[treeID].appleTreeColorVariation = 4;
            } else if (this->trees[treeID].appleTreeColorVariation >= 13) {
                this->trees[treeID].appleTreeColorVariation = 6;
            } else if (this->trees[treeID].appleTreeColorVariation >= 11) {
                this->trees[treeID].appleTreeColorVariation = 1;
            } else if (this->trees[treeID].appleTreeColorVariation > 8) {
                this->trees[treeID].appleTreeColorVariation = 0;
            }
            if (this->trees[treeID].appleTreeColorVariation > 8) {
                this->trees[treeID].appleTreeColorVariation = 0;
            }
            break;
        case 6:
            this->trees[treeID].appleTreeColorVariation = 3;
            this->trees[treeID].stage = 4;
            break;
        case 7:
            this->trees[treeID].appleTreeColorVariation = 4;
            this->trees[treeID].stage = 4;
            break;
        case 8:
            this->trees[treeID].appleTreeColorVariation = 7;
            this->trees[treeID].stage = 4;
            break;
        case 9:
            this->trees[treeID].appleTreeColorVariation = 8;
            this->trees[treeID].stage = 4;
            break;
        case 5:
        case 10:
        case Trees::TT_UNKNOWN_16:
        case Trees::TT_UNKNOWN_17:
        case Trees::TT_UNKNOWN_18:
        case Trees::TT_UNKNOWN_19:
            this->trees[treeID].stage = 4;
            this->trees[treeID].appleTreeColorVariation = 0;
            break;
        }
        undefined4 const savedField0 = this->field_0x0;
        this->field_0x0 = 0;
        DAT_OrganismDefinedData::instance.UpdateTree[this->trees[treeID].treeType]();
        this->field_0x0 = savedField0;
        return treeID;
    }

}
}
