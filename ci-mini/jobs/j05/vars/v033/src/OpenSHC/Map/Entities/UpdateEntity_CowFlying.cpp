#include "../Entities.func.hpp"

#include "OpenSHC/Globals/DAT_CurrentEntityID.hpp"
#include "OpenSHC/Globals/DAT_EntityState.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x00402180
    void Entities::UpdateEntity_CowFlying()
    {
        if (DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].someCounter_OR_hitGround != 0) {
            if (DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].unknownAnimationFrameRelated
                < 100) {
                DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].unknownAnimationFrameRelated = 100;
            }
            if (DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].unknownAnimationFrameRelated
                >= 120) {
                DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].unknownAnimationFrameRelated = 119;
            }
            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].someCounter_OR_hitGround -= 1;
            if ((int)DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].someCounter_OR_hitGround <= 0) {
                DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].logicalState = 7;
            }
            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].graphicType2
                = (DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].unknownAnimationFrameRelated
                      - 100)
                    / 4
                + DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].graphicType2RelatedOffset + 12;
            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].imageID = 0;
        } else {
            if (DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].unknownAnimationFrameRelated
                >= 12) {
                DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].unknownAnimationFrameRelated = 0;
            }
            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].graphicType2
                = DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].graphicType2RelatedOffset
                + DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].unknownAnimationFrameRelated;
            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].imageID
                = DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].graphicType2 + 17;
        }
        if (DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].orientation == 76) {
            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].orientation = 60;
            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].logicalState = 7;
        }
    }

}
}
