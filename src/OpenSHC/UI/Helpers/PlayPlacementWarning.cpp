#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/UI/Helpers.func.hpp"
#include "OpenSHC/string-literals.hpp"

#include "OpenSHC/Globals/DAT_SFXState.hpp"

namespace OpenSHC {
namespace UI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004380E0
    void Helpers::PlayPlacementWarning(BuildingFailReasonEnum reason)
    {
        switch (reason) {
        case OpenSHC::Map::Buildings::BFRE_NOT_ADJ_STOCKPILE:
            MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(
                SFX_NeedsToBePlacedAdjacentToStockpile);
            break;
        case OpenSHC::Map::Buildings::BFRE_NOT_ADJ_ARMORY:
            MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(
                SFX_NeedsToBePlacedAdjacentToArmory);
            break;
        case OpenSHC::Map::Buildings::BFRE_NOT_IRON_ORE:
            MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(
                SFX_IronMineMustBeBuiltOnIronOre);
            break;
        case OpenSHC::Map::Buildings::BFRE_NOT_OIL_MARSH:
            MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(
                SFX_PitchrigMustBeBuiltOnOilInTheMarsh);
            break;
        case OpenSHC::Map::Buildings::BFRE_NOT_ADJ_GRANARY:
            MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(
                SFX_NeedsToBePlacedAdjacentToGranary);
            break;
        case OpenSHC::Map::Buildings::BFRE_MISSING2:
            MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(
                s_placement_warning21_wav_005a2650);
            break;
        case OpenSHC::Map::Buildings::BFRE_MISSING4:
            MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(
                s_placement_warning19_wav_005a2638);
            break;
        case OpenSHC::Map::Buildings::BFRE_MUST_BE_PLACED_ON_OASES:
            MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(SFX_FarmsMustBePlacedOnOases);
            break;
        case OpenSHC::Map::Buildings::BFRE_MISSING5:
            MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(
                s_placement_warning20_wav_005a2608);
            break;
        default:
            MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(SFX_CantPlaceThatThereMyLord);
            break;
        }
    }

}
}
