#include "../Entities.func.hpp"

#include "OpenSHC/Globals/DAT_CurrentEntityID.hpp"
#include "OpenSHC/Globals/DAT_EntityDefinedData.hpp"
#include "OpenSHC/Globals/DAT_EntityState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_LandscapeState.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x00402900
    void Entities::UpdateFlag_1_2_4_Entity()
    {
        OpenSHC::Map::Entities::Entity const entityArrayValue = DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance];
        int nextFlagState = entityArrayValue.someTracker;
        int const owner = entityArrayValue.owner;
        entityArrayValue.graphicType2
            = entityArrayValue.graphicType2RelatedOffset;
        if ((entityArrayValue.yPosition & 0x1f)
            >= DAT_LandscapeState::instance.wind.countdown) {
            nextFlagState = DAT_LandscapeState::instance.wind.value;
        }
        if (DAT_GameSynchronyState::instance.currentGameMode != Game::GM_SOLITARY
            && DAT_GameSynchronyState::instance.currentPlayerFullIDArray[owner] == -1
            && DAT_GameSynchronyState::instance.currentAIArray[owner] != 0) {
            if (DAT_GameState::instance.playerDataArray[owner].aiBuildingDestroyChoiceTracker != 0) {
                nextFlagState = 3;
            } else if (DAT_GameState::instance.playerDataArray[owner].aiNervousActionsTracker != 0) {
                nextFlagState = 3;
            } else {
                int const recruitChoice = DAT_GameState::instance.playerDataArray[owner].aiRecruitUnitChoiceState;
                nextFlagState = 0;
                if (recruitChoice != 0) {
                    if (recruitChoice == 1) {
                        nextFlagState = 1;
                    } else {
                        nextFlagState = 2;
                    }
                }
            }
        }
        entityArrayValue.unkOne_1 = 3;
        int frameCount;
        switch (entityArrayValue.someTracker) {
        case 0:
            frameCount = DAT_EntityDefinedData::instance
                             .FlagAnimationFrames1[entityArrayValue
                                     .unknownAnimationFrameRelated];
            break;
        case 1:
            frameCount = DAT_EntityDefinedData::instance
                             .FlagAnimationFrames2[entityArrayValue
                                     .unknownAnimationFrameRelated];
            break;
        case 3:
            entityArrayValue.unkOne_1 = 1;
            // fallthrough
        case 2:
            frameCount = DAT_EntityDefinedData::instance
                             .FlagAnimationFrames3[entityArrayValue
                                     .unknownAnimationFrameRelated];
            break;
        default:
            return;
        }
        if (frameCount <= 0) {
            entityArrayValue.unknownAnimationFrameRelated = 0;
            entityArrayValue.someTracker = nextFlagState;
            return;
        }
        entityArrayValue.graphicType2 += frameCount - 1;
    }

}
}
