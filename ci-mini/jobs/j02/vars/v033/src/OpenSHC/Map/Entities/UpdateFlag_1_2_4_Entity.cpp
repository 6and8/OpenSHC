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
        int nextFlagState = DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].someTracker;
        int const owner = DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].owner;
        DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].graphicType2
            = DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].graphicType2RelatedOffset;
        if ((DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].yPosition & 0x1f)
            >= DAT_LandscapeState::instance.wind.countdown) {
            nextFlagState = DAT_LandscapeState::instance.wind.value;
        }
        if (DAT_GameSynchronyState::instance.currentGameMode != Game::GM_SOLITARY
            && DAT_GameSynchronyState::instance.currentPlayerFullIDArray[owner] == -1
            && DAT_GameSynchronyState::instance.currentAIArray[owner] != 0) {
            if (DAT_GameState::instance.playerDataArray[owner].aiBuildingDestroyChoiceTracker != 0) {
                nextFlagState = 3;
            } else if (DAT_GameState::instance.playerDataArray[owner].aiNervousActionsTracker == 0) {
                int const recruitChoice = DAT_GameState::instance.playerDataArray[owner].aiRecruitUnitChoiceState;
                nextFlagState = 0;
                if (recruitChoice != 0) {
                    if (recruitChoice == 1) {
                        nextFlagState = 1;
                    } else {
                        nextFlagState = 2;
                    }
                }
            } else {
                nextFlagState = 3;
            }
        }
        DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].unkOne_1 = 3;
        int frameCount;
        switch (DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].someTracker) {
        case 0:
            frameCount = DAT_EntityDefinedData::instance
                             .FlagAnimationFrames1[DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance]
                                     .unknownAnimationFrameRelated];
            break;
        case 1:
            frameCount = DAT_EntityDefinedData::instance
                             .FlagAnimationFrames2[DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance]
                                     .unknownAnimationFrameRelated];
            break;
        case 3:
            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].unkOne_1 = 1;
            // fallthrough
        case 2:
            frameCount = DAT_EntityDefinedData::instance
                             .FlagAnimationFrames3[DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance]
                                     .unknownAnimationFrameRelated];
            break;
        default:
            return;
        }
        if (frameCount <= 0) {
            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].unknownAnimationFrameRelated = 0;
            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].someTracker = nextFlagState;
            return;
        }
        DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].graphicType2 += frameCount - 1;
    }

}
}
