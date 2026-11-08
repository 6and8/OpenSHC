#include "../MenuTextInputState.func.hpp"

#include "OpenSHC/IO/ResourceManager.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/Text/UserTextHandler.func.hpp"
#include "OpenSHC/UI/Helpers.func.hpp"
#include "OpenSHC/UI/MenuItems/SaveLoadMap.func.hpp"
#include "OpenSHC/Commands/GameCommandType.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/string-literals.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MinimapViewState.hpp"
#include "OpenSHC/Globals/DAT_MouseState.hpp"
#include "OpenSHC/Globals/DAT_ResourceManager.hpp"
#include "OpenSHC/Globals/DAT_UserTextHandlerState.hpp"
#include "OpenSHC/Globals/INT_00b95b64.hpp"

namespace OpenSHC {
namespace UI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004968A0
    void MenuTextInputState::loadOrSaveGame(int action)
    {
        if (DAT_GameSynchronyState::instance.currentGameMode != Game::GM_SOLITARY
            && DAT_GameSynchronyState::instance.currentGameMode != Game::GM_SKIRMISH_SINGLE_PLAYER
            && DAT_GameSynchronyState::instance.saveRelated == 1 && action == OpenSHC::UI::Enums::MMT_SAVE_MAP) {
            MACRO_CALL_MEMBER(OpenSHC::UI::MenuTextInputState_Func::clearAnyOtherModalDialogs, this)();
            return;
        }
        DAT_MouseState::instance.waitCursorToggle = 1;
        MACRO_CALL(OpenSHC::UI::Helpers_Func::SetCursorDependingOnProgramState)();
        MACRO_CALL(OpenSHC::OS_Func::_memset)(
            DAT_MinimapViewState::instance.loadedMiniMap, 0, sizeof(DAT_MinimapViewState::instance.loadedMiniMap));
        INT_00b95b64::instance = 1;
        if (DAT_GameSynchronyState::instance.currentGameMode != Game::GM_SOLITARY
            && DAT_GameSynchronyState::instance.currentGameMode != Game::GM_SKIRMISH_SINGLE_PLAYER) {
            std::string path(DAT_ResourceManager::instance.paths_getSavesPath(true));
            // "*.msv"
            path.append(s__msv_005a75d4);
            MACRO_CALL_MEMBER(OpenSHC::IO::ResourceManager_Func::discoverMapFiles, DAT_ResourceManager::ptr)(
                path.c_str());
            this->fileListEntryCount = DAT_ResourceManager::instance.mapFileCounter;
            for (int i = 0; i < (int)DAT_ResourceManager::instance.mapFileCounter; ++i) {
                this->DAT_ArrayOfMapIndices[i] = i;
                this->DAT_ArrayOfMapIndices2[i - 1] = 1;
                if (action != OpenSHC::UI::Enums::MMT_SAVE_MAP) {
                    DAT_GameSynchronyState::instance.DAT_GameCommandParam0 = i;
                    MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand, DAT_GameSynchronyState::ptr)(
                        (Commands::GameCommandType)50);
                }
            }
        } else {
            std::string path(DAT_ResourceManager::instance.paths_getSavesPath(true));
            // "*.sav"
            path.append(s__sav_005a75cc);
            MACRO_CALL_MEMBER(OpenSHC::IO::ResourceManager_Func::discoverMapFiles, DAT_ResourceManager::ptr)(
                path.c_str());
            this->fileListEntryCount = DAT_ResourceManager::instance.mapFileCounter;
            for (int i = 0; i < DAT_ResourceManager::instance.mapFileCounter; ++i) {
                this->DAT_ArrayOfMapIndices[i] = i;
            }
        }
        DAT_MouseState::instance.waitCursorToggle = 0;
        this->fileListSortOrder = 0;
        this->menuLoadGameRelativeSelectionOffset = 0;
        if (this->fileListEntryCount == 0) {
            this->menuLoadGameRelativeSelectionIndex = -1;
        } else {
            this->menuLoadGameRelativeSelectionIndex = 0;
        }
        this->lastListClickTime = 0;
        this->lastClickedListIndex = -1;
        this->DAT_ArrayOfMapU3EndInt2[0] = 0;
        this->previewedListIndex = -1;
        this->fileListVisibleRowCount = 16;
        if (action == OpenSHC::UI::Enums::MMT_LOAD_MAP) {
            MACRO_CALL_MEMBER(OpenSHC::UI::MenuTextInputState_Func::activateModalDialogAndClearText, this)(
                OpenSHC::UI::Enums::MMT_LOAD_MAP);
            this->fileListContext = 1;
            if (this->menuLoadGameRelativeSelectionIndex != -1) {
                this->menuLoadGameRelativeSelectionOffset = this->savedListOffset1;
                this->fileListSortOrder = this->savedListSortOrder1;
                this->menuLoadGameRelativeSelectionIndex = this->savedListSelection1;
                if (this->menuLoadGameRelativeSelectionOffset + this->menuLoadGameRelativeSelectionIndex
                    >= this->fileListEntryCount) {
                    this->menuLoadGameRelativeSelectionIndex = 0;
                    this->menuLoadGameRelativeSelectionOffset = 0;
                }
            }
        } else {
            MACRO_CALL_MEMBER(OpenSHC::UI::MenuTextInputState_Func::activateModalDialogAndClearText, this)(
                OpenSHC::UI::Enums::MMT_SAVE_MAP);
            DAT_UserTextHandlerState::instance.allowUserTextInput = 0;
            MACRO_CALL_MEMBER(OpenSHC::Text::UserTextHandler_Func::resetToTextIndex, DAT_UserTextHandlerState::ptr)(2);
            MACRO_CALL_MEMBER(OpenSHC::Text::UserTextHandler_Func::moveCursorToEnd, DAT_UserTextHandlerState::ptr)();
            DAT_UserTextHandlerState::instance.allowUserTextInput = 1;
            this->fileListContext = 3;
            if (this->menuLoadGameRelativeSelectionIndex != -1) {
                this->menuLoadGameRelativeSelectionOffset = this->savedListOffset2;
                this->fileListSortOrder = this->savedListSortOrder2;
                this->menuLoadGameRelativeSelectionIndex = this->savedListSelection2;
                if (this->menuLoadGameRelativeSelectionOffset + this->menuLoadGameRelativeSelectionIndex
                    >= this->fileListEntryCount) {
                    this->menuLoadGameRelativeSelectionIndex = 0;
                    this->menuLoadGameRelativeSelectionOffset = 0;
                }
            }
        }
        MACRO_CALL(OpenSHC::UI::MenuItems::SaveLoadMap_Func::MenuItemActionHandler_SaveLoadMap_TableHeader)(
            -1 - this->fileListSortOrder);
    }

}
}
