#include "../Game.func.hpp"

#include "OpenSHC/Globals/DAT_00df5558.hpp"
#include "OpenSHC/Globals/DAT_00df5560.hpp"
#include "OpenSHC/Globals/DAT_00df5590.hpp"
#include "OpenSHC/Globals/DAT_DisableTutorialRestrictions.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_TutorialCurrentStep.hpp"

namespace OpenSHC {

using WindowsHelper::Enums::BOOLEnum;

// FUNCTION: STRONGHOLDCRUSADER 0x004BD800
BOOLEnum __cdecl Game::Tutorial_IsActionAllowed(undefined4 actionType, int actionParam)
{
    if (DAT_DisableTutorialRestrictions::instance != 0) {
        return TRUE;
    }
    switch (actionType) {
    case 1:
        if (DAT_TutorialCurrentStep::instance == 2) {
            if ((int)DAT_00df5558::instance < 2 && actionParam == 0x28) {
                return TRUE;
            }
        } else if (DAT_TutorialCurrentStep::instance == 5) {
            if (DAT_00df5558::instance == 0 && actionParam == 0x13) {
                return TRUE;
            }
        } else if (DAT_TutorialCurrentStep::instance == 0x11) {
            if (actionParam == 3 && DAT_00df5560::instance == 0) {
                return TRUE;
            }
        } else if (DAT_TutorialCurrentStep::instance == 0x15) {
            if (actionParam == 7) {
                return TRUE;
            }
        } else if (DAT_TutorialCurrentStep::instance == 0x18) {
            if (actionParam == 1) {
                return TRUE;
            }
        }
        return FALSE;
    case 2:
        if (DAT_TutorialCurrentStep::instance == 2) {
            if ((int)DAT_00df5558::instance < 2 && actionParam == 0x28) {
                return TRUE;
            }
        } else if (DAT_TutorialCurrentStep::instance == 5) {
            if (DAT_00df5558::instance == 0 && actionParam == 0x13 && DAT_00df5560::instance == 0) {
                return TRUE;
            }
        } else if (DAT_TutorialCurrentStep::instance == 0x11) {
            if (actionParam == 3 && (int)DAT_00df5590::instance < 4) {
                return TRUE;
            }
        } else if (DAT_TutorialCurrentStep::instance == 0x15) {
            if (actionParam == 7 && (int)DAT_00df5590::instance < 4) {
                return TRUE;
            }
        } else if (DAT_TutorialCurrentStep::instance == 0x18) {
            if (actionParam == 1 && DAT_00df5560::instance == 0) {
                return TRUE;
            }
        }
        return FALSE;
    case 3:
        if (DAT_TutorialCurrentStep::instance != 8) {
            return FALSE;
        }
        if (DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID].rationsSetting
                != 4
            || actionParam == 4) {
            return TRUE;
        }
        return FALSE;
    case 4:
        if (DAT_TutorialCurrentStep::instance != 10) {
            return FALSE;
        }
        if (DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID].taxesSetting
            != 7) {
            return TRUE;
        }
        if (actionParam != 7) {
            return FALSE;
        }
        return TRUE;
    default:
        return TRUE;
    }
}

}
