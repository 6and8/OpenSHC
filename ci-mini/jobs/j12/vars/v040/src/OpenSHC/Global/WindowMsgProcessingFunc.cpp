#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/Audio/MSS/SoundSystem.func.hpp"
#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Game/GameCore.func.hpp"
#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Global.func.hpp"
#include "OpenSHC/Input/MouseState.func.hpp"
#include "OpenSHC/Map/MapPropertiesState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Rendering.func.hpp"
#include "OpenSHC/Rendering/ViewportRenderState.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/Text/TextEditorState.func.hpp"
#include "OpenSHC/Text/UserTextHandler.func.hpp"
#include "OpenSHC/UI/DisplayElements.func.hpp"
#include "OpenSHC/UI/Helpers.func.hpp"
#include "OpenSHC/UI/MenuItems/General.func.hpp"
#include "OpenSHC/UI/MenuItems/IdentityOptions.func.hpp"
#include "OpenSHC/UI/MenuItems/NewEventCondition.func.hpp"
#include "OpenSHC/UI/MenuModalComposition.func.hpp"
#include "OpenSHC/UI/MenuTextInputState.func.hpp"
#include "OpenSHC/UI/Rendering/AlphaAndButtonSurface.func.hpp"
#include "OpenSHC/UI/Rendering/WindowAndDirectDraw.func.hpp"
#include "OpenSHC/string-literals.hpp"

#include "OpenSHC/Globals/AlphaAndButtonSurfaceObj.hpp"
#include "OpenSHC/Globals/DAT_00df5538.hpp"
#include "OpenSHC/Globals/DAT_AICState.hpp"
#include "OpenSHC/Globals/DAT_BinkControlState.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_CheatCodeStringTrackerIndex.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_InsertKeyState.hpp"
#include "OpenSHC/Globals/DAT_MapPropertiesState.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition1.hpp"
#include "OpenSHC/Globals/DAT_MenuTextInputState.hpp"
#include "OpenSHC/Globals/DAT_ModifierKeyState.hpp"
#include "OpenSHC/Globals/DAT_MouseState.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"
#include "OpenSHC/Globals/DAT_ScrollingHandler.hpp"
#include "OpenSHC/Globals/DAT_ShortcutDefinedData.hpp"
#include "OpenSHC/Globals/DAT_SoundSystemState.hpp"
#include "OpenSHC/Globals/DAT_TextEditorState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_UIDragDropDefinedData.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_UserTextHandlerState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"

#include "binkw32.h"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x004B2AE0
    LRESULT __stdcall WindowMsgProcessingFunc(HWND windowHandle, UINT message, WPARAM wParam, LPARAM lParam)
    {
        PAINTSTRUCT paintStruct;

        switch (message) {
        case WM_CREATE:
        case WM_MOVE:
            if (DAT_WindowAndDirectDraw::instance.runGameAsExclusiveFullscreen == FALSE) {
                DAT_WindowAndDirectDraw::instance.windowMoveEventBlitCountdown = 10;
                MACRO_CALL_MEMBER(
                    UI::Rendering::WindowAndDirectDraw_Func::reinitWindow, DAT_WindowAndDirectDraw::ptr)();
                GetClientRect(windowHandle, &DAT_WindowAndDirectDraw::instance.clientOnScreenCoords);
                ClientToScreen(windowHandle, (LPPOINT)&DAT_WindowAndDirectDraw::instance.clientOnScreenCoords);
                ClientToScreen(windowHandle, (LPPOINT)&DAT_WindowAndDirectDraw::instance.clientOnScreenCoords.right);
            }
            break;
        case WM_SIZE:
            if (DAT_WindowAndDirectDraw::instance.runGameAsExclusiveFullscreen != FALSE) {
                SetRect(&DAT_WindowAndDirectDraw::instance.clientOnScreenCoords, 0, 0, GetSystemMetrics(0),
                    GetSystemMetrics(1));
            } else {
                MACRO_CALL_MEMBER(
                    UI::Rendering::WindowAndDirectDraw_Func::reinitWindow, DAT_WindowAndDirectDraw::ptr)();
                GetClientRect(windowHandle, &DAT_WindowAndDirectDraw::instance.clientOnScreenCoords);
                ClientToScreen(windowHandle, (LPPOINT)&DAT_WindowAndDirectDraw::instance.clientOnScreenCoords);
                ClientToScreen(windowHandle, (LPPOINT)&DAT_WindowAndDirectDraw::instance.clientOnScreenCoords.right);
            }
            break;
        case WM_ACTIVATEAPP:
            if ((WORD)wParam == 1) {
                DAT_WindowAndDirectDraw::instance.gameFocused = TRUE;
            } else if ((WORD)wParam == 2) {
                DAT_WindowAndDirectDraw::instance.gameFocused = TRUE;
            } else if ((WORD)wParam == 0) {
                DAT_WindowAndDirectDraw::instance.gameFocused = FALSE;
                DAT_WindowAndDirectDraw::instance.isNotProcessingInputEvents = TRUE;
                MACRO_CALL_MEMBER(Audio::MSS::SoundSystem_Func::endSpeechSoundStreams, DAT_SoundSystemState::ptr)();
            }
            if (DAT_WindowAndDirectDraw::instance.isNotProcessingInputEvents != FALSE
                && DAT_WindowAndDirectDraw::instance.gameFocused != FALSE) {
                if (MACRO_CALL_MEMBER(
                        UI::Rendering::WindowAndDirectDraw_Func::restoreDXSurfaces, DAT_WindowAndDirectDraw::ptr)()
                    != FALSE) {
                    MACRO_CALL_MEMBER(
                        UI::Rendering::WindowAndDirectDraw_Func::reinitWindow, DAT_WindowAndDirectDraw::ptr)();
                }
                MACRO_CALL_MEMBER(Input::MouseState_Func::resetMouseState2, DAT_MouseState::ptr)();
                MACRO_CALL_MEMBER(Input::MouseState_Func::storeXYAndResetMouseState, DAT_MouseState::ptr)();
            }
            DAT_WindowAndDirectDraw::instance.unk_resetViewportRelated = 1;
            break;
        case WM_DISPLAYCHANGE:
            DAT_WindowAndDirectDraw::instance.depthBitsPerPixel = wParam;
            DAT_WindowAndDirectDraw::instance.screenHorizontalResolutionInPixels = (WORD)lParam;
            DAT_WindowAndDirectDraw::instance.screenVerticalResolutionInPixels = (DWORD)lParam >> 16;
            break;
        case WM_SETFOCUS:
            MACRO_CALL_MEMBER(Audio::MSS::SoundSystem_Func::resumeAudioSample, DAT_SoundSystemState::ptr)();
            for (int i = 0; i < 2; ++i) {
                if (DAT_BinkControlState::instance.binkObjPtrArray[i] != 0) {
                    BinkPause(DAT_BinkControlState::instance.binkObjPtrArray[i], 0);
                }
            }
            break;
        case WM_KILLFOCUS:
            MACRO_CALL_MEMBER(Audio::MSS::SoundSystem_Func::pauseAudioSample, DAT_SoundSystemState::ptr)();
            for (int i = 0; i < 2; ++i) {
                if (DAT_BinkControlState::instance.binkObjPtrArray[i] != 0) {
                    BinkPause(DAT_BinkControlState::instance.binkObjPtrArray[i], 1);
                }
            }
            break;
        case WM_CLOSE:
        case WM_QUIT:
            DAT_WindowAndDirectDraw::instance.postWindowCloseMessage = 3;
            break;
        case WM_PAINT:
            BeginPaint(windowHandle, &paintStruct);
            EndPaint(windowHandle, &paintStruct);
            if (MACRO_CALL_MEMBER(Game::GameCore_Func::getAreWeInAInGameMenu, DAT_GameCore::ptr)() == FALSE) {
                DAT_WindowAndDirectDraw::instance.unk_resetViewportRelated = 2;
                MACRO_CALL_MEMBER(
                    UI::Rendering::WindowAndDirectDraw_Func::renderBltAndFlip, DAT_WindowAndDirectDraw::ptr)(1);
            }
            DAT_WindowAndDirectDraw::instance.unk_resetViewportRelated = 2;
            DAT_UIDragDropDefinedData::instance.MenuView_TriggerInitial = TRUE;
            break;
        case WM_DESTROY:
            DAT_WindowAndDirectDraw::instance.postWindowCloseMessage = 3;
            DAT_WindowAndDirectDraw::instance.windowHandle = NULL;
            PostQuitMessage(0);
            break;
        case WM_KEYDOWN:
            DAT_ModifierKeyState::instance.keyDownUnk = 1;
            if (DAT_GameCore::instance.currentMenuViewType == (UI::Enums::MenuViewType)41
                && DAT_ModifierKeyState::instance.ctrl != 0 && DAT_GameCore::instance.cheatModeFlag == FALSE
                && wParam
                    == (byte)DAT_ShortcutDefinedData::instance.cheatCode[DAT_CheatCodeStringTrackerIndex::instance]) {
                ++DAT_CheatCodeStringTrackerIndex::instance;
                if (DAT_ShortcutDefinedData::instance.cheatCode[DAT_CheatCodeStringTrackerIndex::instance] == 0) {
                    DAT_GameCore::instance.cheatModeFlag = TRUE;
                }
            } else {
                DAT_CheatCodeStringTrackerIndex::instance = 0;
            }
            switch (wParam) {
            case VK_SPACE:
                if ((lParam & 0x40000000) == 0) {
                    if (DAT_GameCore::instance.gameMode_2 == (Game::GameMode2)4) {
                        if ((int)MACRO_CALL(UI::Helpers_Func::GetCurrentTutorialStep)() >= 29) {
                            MACRO_CALL_MEMBER(Map::TileMapState_Func::toggleFlatView, DAT_TileMapState::ptr)(
                                DAT_TileMapState::instance.flatViewToggleValue1 ^ 1);
                        }
                    } else if (MACRO_CALL_MEMBER(Game::GameCore_Func::getAreWeInAInGameMenu, DAT_GameCore::ptr)()
                            != FALSE
                        && DAT_MenuModalComposition1::instance.activeModalDialogID == (UI::Enums::MenuModalType)-1) {
                        MACRO_CALL_MEMBER(Map::TileMapState_Func::toggleFlatView, DAT_TileMapState::ptr)(
                            DAT_TileMapState::instance.flatViewToggleValue1 ^ 1);
                    }
                }
                break;
            case VK_TAB:
                if ((lParam & 0x40000000) == 0) {
                    MACRO_CALL_MEMBER(Game::GameCore_Func::hideOrUnhideUI, DAT_GameCore::ptr)();
                }
                break;
            case VK_RIGHT:
                MACRO_CALL_MEMBER(Text::UserTextHandler_Func::handleRightKey, DAT_UserTextHandlerState::ptr)();
                if (MACRO_CALL_MEMBER(Game::GameCore_Func::getAreWeInAInGameMenu, DAT_GameCore::ptr)() != FALSE
                    && DAT_MenuModalComposition1::instance.activeModalDialogID == (UI::Enums::MenuModalType)-1
                    && DAT_ModifierKeyState::instance.ctrl != 0 && DAT_MouseState::instance.rightClickState == FALSE) {
                    MACRO_CALL_MEMBER(Map::TileMapState_Func::setMapRotation, DAT_TileMapState::ptr)(
                        (DAT_TileMapState::instance.mapOrientation + 6) % 8);
                    MACRO_CALL_MEMBER(
                        Text::UserTextHandler_Func::handleCharacterIntoInputBuffer, DAT_UserTextHandlerState::ptr)(243);
                } else {
                    if (DAT_GameCore::instance.gameMode_2 != (Game::GameMode2)3
                        || DAT_MenuModalComposition1::instance.activeModalDialogID != (UI::Enums::MenuModalType)27) {
                        DAT_ScrollingHandler::instance.rightKeyDown_0x18 = TRUE;
                    }
                    MACRO_CALL_MEMBER(
                        Text::UserTextHandler_Func::handleCharacterIntoInputBuffer, DAT_UserTextHandlerState::ptr)(243);
                }
                break;
            case VK_LEFT:
                MACRO_CALL_MEMBER(Text::UserTextHandler_Func::handleLeftKey, DAT_UserTextHandlerState::ptr)();
                if (MACRO_CALL_MEMBER(Game::GameCore_Func::getAreWeInAInGameMenu, DAT_GameCore::ptr)() != FALSE
                    && DAT_MenuModalComposition1::instance.activeModalDialogID == (UI::Enums::MenuModalType)-1
                    && DAT_ModifierKeyState::instance.ctrl != 0 && DAT_MouseState::instance.rightClickState == FALSE) {
                    MACRO_CALL_MEMBER(Map::TileMapState_Func::setMapRotation, DAT_TileMapState::ptr)(
                        (DAT_TileMapState::instance.mapOrientation + 2) % 8);
                    MACRO_CALL_MEMBER(
                        Text::UserTextHandler_Func::handleCharacterIntoInputBuffer, DAT_UserTextHandlerState::ptr)(242);
                } else {
                    if (DAT_GameCore::instance.gameMode_2 != (Game::GameMode2)3
                        || DAT_MenuModalComposition1::instance.activeModalDialogID != (UI::Enums::MenuModalType)27) {
                        DAT_ScrollingHandler::instance.leftKeyDown_0x1c = TRUE;
                    }
                    MACRO_CALL_MEMBER(
                        Text::UserTextHandler_Func::handleCharacterIntoInputBuffer, DAT_UserTextHandlerState::ptr)(242);
                }
                break;
            case VK_DOWN:
                if (MACRO_CALL_MEMBER(Game::GameCore_Func::getAreWeInAInGameMenu, DAT_GameCore::ptr)() != FALSE
                    && DAT_MenuModalComposition1::instance.activeModalDialogID == (UI::Enums::MenuModalType)-1
                    && DAT_ModifierKeyState::instance.ctrl != 0 && DAT_MouseState::instance.rightClickState == FALSE) {
                    MACRO_CALL_MEMBER(Map::TileMapState_Func::triggerLoweredView, DAT_TileMapState::ptr)(3);
                    DAT_ModifierKeyState::instance.downArrow = 1;
                    MACRO_CALL_MEMBER(
                        Text::UserTextHandler_Func::handleCharacterIntoInputBuffer, DAT_UserTextHandlerState::ptr)(245);
                } else {
                    if (DAT_GameCore::instance.gameMode_2 != (Game::GameMode2)3
                        || DAT_MenuModalComposition1::instance.activeModalDialogID != (UI::Enums::MenuModalType)27) {
                        DAT_ScrollingHandler::instance.downKeyDown_0x20 = TRUE;
                    }
                    MACRO_CALL_MEMBER(
                        Text::UserTextHandler_Func::handleCharacterIntoInputBuffer, DAT_UserTextHandlerState::ptr)(245);
                }
                break;
            case VK_UP:
                if (MACRO_CALL_MEMBER(Game::GameCore_Func::getAreWeInAInGameMenu, DAT_GameCore::ptr)() != FALSE
                    && DAT_MenuModalComposition1::instance.activeModalDialogID == (UI::Enums::MenuModalType)-1
                    && DAT_ModifierKeyState::instance.ctrl != 0 && DAT_MouseState::instance.rightClickState == FALSE) {
                    if (DAT_ViewportRenderState::instance.viewportState.isZoomedOutUnk != 0) {
                        MACRO_CALL_MEMBER(
                            Rendering::ViewportRenderState_Func::resetupViewport, DAT_ViewportRenderState::ptr)(0);
                    } else {
                        MACRO_CALL_MEMBER(
                            Rendering::ViewportRenderState_Func::resetupViewport, DAT_ViewportRenderState::ptr)(1);
                    }
                    DAT_WindowAndDirectDraw::instance.unk_resetViewportRelated = 2;
                    DAT_UIDragDropDefinedData::instance.MenuView_TriggerInitial = TRUE;
                }
                if (DAT_GameCore::instance.gameMode_2 != (Game::GameMode2)3
                    || DAT_MenuModalComposition1::instance.activeModalDialogID != (UI::Enums::MenuModalType)27) {
                    DAT_ScrollingHandler::instance.upKeyDown_0x24 = TRUE;
                }
                MACRO_CALL_MEMBER(
                    Text::UserTextHandler_Func::handleCharacterIntoInputBuffer, DAT_UserTextHandlerState::ptr)(244);
                break;
            case VK_INSERT:
                DAT_InsertKeyState::instance.insert ^= 1;
                break;
            case VK_DELETE:
                MACRO_CALL_MEMBER(Text::UserTextHandler_Func::handleDeleteKey, DAT_UserTextHandlerState::ptr)();
                MACRO_CALL_MEMBER(
                    Text::UserTextHandler_Func::handleCharacterIntoInputBuffer, DAT_UserTextHandlerState::ptr)(249);
                break;
            case VK_BACK:
                MACRO_CALL_MEMBER(Text::UserTextHandler_Func::handleBackspace, DAT_UserTextHandlerState::ptr)();
                MACRO_CALL_MEMBER(
                    Text::UserTextHandler_Func::handleCharacterIntoInputBuffer, DAT_UserTextHandlerState::ptr)(248);
                break;
            case VK_PRIOR:
                MACRO_CALL_MEMBER(
                    Text::UserTextHandler_Func::handleCharacterIntoInputBuffer, DAT_UserTextHandlerState::ptr)(250);
                break;
            case VK_NEXT:
                MACRO_CALL_MEMBER(
                    Text::UserTextHandler_Func::handleCharacterIntoInputBuffer, DAT_UserTextHandlerState::ptr)(251);
                break;
            case VK_RETURN:
                MACRO_CALL_MEMBER(Text::UserTextHandler_Func::handleReturnKey, DAT_UserTextHandlerState::ptr)();
                MACRO_CALL_MEMBER(
                    Text::UserTextHandler_Func::handleCharacterIntoInputBuffer, DAT_UserTextHandlerState::ptr)(241);
                if ((DAT_GameCore::instance.gameMode_2 == (Game::GameMode2)3
                        && DAT_MenuModalComposition1::instance.activeModalDialogID == (UI::Enums::MenuModalType)27
                        && DAT_GameSynchronyState::instance.currentGameMode != (Game::GameMode)99)
                    || DAT_GameCore::instance.currentMenuViewType == (UI::Enums::MenuViewType)20) {
                    if (DAT_UserTextHandlerState::instance.textArrayIndex == (Text::TextArrayIndexType)4) {
                        char* text = MACRO_CALL_MEMBER(
                            Text::UserTextHandler_Func::getCurrentText, DAT_UserTextHandlerState::ptr)();
                        int len = (int)strlen(text);
                        for (int i = 0; i < len; ++i) {
                            if (text[i] != ' ') {
                                DAT_GameSynchronyState::instance.DAT_ChatTauntOrMessage = 0;
                                MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand,
                                    DAT_GameSynchronyState::ptr)((Commands::GameCommandType)14);
                                MACRO_CALL_MEMBER(
                                    Text::UserTextHandler_Func::clearTextAndCursor, DAT_UserTextHandlerState::ptr)();
                                if (DAT_GameCore::instance.currentMenuViewType != (UI::Enums::MenuViewType)20) {
                                    MACRO_CALL_MEMBER(UI::MenuModalComposition_Func::activateModalDialog,
                                        DAT_MenuModalComposition1::ptr)((UI::Enums::MenuModalType)-1, FALSE);
                                }
                                break;
                            }
                        }
                    }
                } else if (DAT_GameCore::instance.gameMode_2 == (Game::GameMode2)3
                    && DAT_MenuModalComposition1::instance.activeModalDialogID == (UI::Enums::MenuModalType)-1
                    && MACRO_CALL_MEMBER(Game::GameCore_Func::getAreWeInAInGameMenu, DAT_GameCore::ptr)() != FALSE) {
                    if (DAT_GameSynchronyState::instance.currentGameMode == (Game::GameMode)99) {
                        MACRO_CALL_MEMBER(UI::MenuModalComposition_Func::activateModalDialog,
                            DAT_MenuModalComposition1::ptr)((UI::Enums::MenuModalType)121, FALSE);
                    } else {
                        MACRO_CALL_MEMBER(UI::MenuModalComposition_Func::activateModalDialog,
                            DAT_MenuModalComposition1::ptr)((UI::Enums::MenuModalType)27, FALSE);
                        DAT_UserTextHandlerState::instance.allowUserTextInput = 0;
                        MACRO_CALL_MEMBER(Text::UserTextHandler_Func::resetToTextIndex, DAT_UserTextHandlerState::ptr)(
                            4);
                        MACRO_CALL_MEMBER(
                            Text::UserTextHandler_Func::clearTextAndCursor, DAT_UserTextHandlerState::ptr)();
                    }
                } else if (DAT_MenuModalComposition1::instance.activeModalDialogID == (UI::Enums::MenuModalType)35) {
                    MACRO_CALL(UI::MenuItems::IdentityOptions_Func::MenuItemActionHandler_IdentityOptions_Confirm)(17);
                }
                break;
            case VK_HOME:
                MACRO_CALL_MEMBER(Text::UserTextHandler_Func::resetCursorToStart, DAT_UserTextHandlerState::ptr)();
                MACRO_CALL_MEMBER(
                    Text::UserTextHandler_Func::handleCharacterIntoInputBuffer, DAT_UserTextHandlerState::ptr)(246);
                break;
            case VK_END:
                MACRO_CALL_MEMBER(Text::UserTextHandler_Func::moveCursorToEnd, DAT_UserTextHandlerState::ptr)();
                MACRO_CALL_MEMBER(
                    Text::UserTextHandler_Func::handleCharacterIntoInputBuffer, DAT_UserTextHandlerState::ptr)(247);
                break;
            case VK_F1:
                if (DAT_ModifierKeyState::instance.shift == 0) {
                    goto label_F1_to_F10;
                }
                if ((DAT_GameSynchronyState::instance.currentGameMode != (Game::GameMode)0
                        || DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                .playerDeathRelated
                            == 0)
                    && DAT_GameCore::instance.gameMode_2 != (Game::GameMode2)1
                    && DAT_GameCore::instance.gameMode_2 != (Game::GameMode2)6
                    && DAT_MenuTextInputState::instance.currentModalDialog == (UI::Enums::MenuModalType)0
                    && (DAT_GameCore::instance.currentMenuViewType == (UI::Enums::MenuViewType)14
                        || DAT_GameCore::instance.currentMenuViewType == (UI::Enums::MenuViewType)16)
                    && (DAT_GameSynchronyState::instance.currentGameMode == (Game::GameMode)0
                        || DAT_GameSynchronyState::instance.isHost != FALSE)
                    && DAT_GameCore::instance.field_0x6c == 0
                    && DAT_GameCore::instance.gameMode_2 != (Game::GameMode2)4) {
                    MACRO_CALL_MEMBER(UI::MenuTextInputState_Func::loadOrSaveGame, DAT_MenuTextInputState::ptr)(10);
                }
                break;
            case VK_F2:
                if (DAT_ModifierKeyState::instance.shift == 0) {
                    goto label_F1_to_F10;
                }
                if ((DAT_GameSynchronyState::instance.currentGameMode != (Game::GameMode)0
                        || DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                .playerDeathRelated
                            == 0)
                    && DAT_GameCore::instance.gameMode_2 != (Game::GameMode2)1
                    && DAT_GameCore::instance.gameMode_2 != (Game::GameMode2)6
                    && DAT_MenuTextInputState::instance.currentModalDialog == (UI::Enums::MenuModalType)0
                    && (DAT_GameCore::instance.currentMenuViewType == (UI::Enums::MenuViewType)14
                        || DAT_GameCore::instance.currentMenuViewType == (UI::Enums::MenuViewType)16)) {
                    if (DAT_GameSynchronyState::instance.currentGameMode == (Game::GameMode)0) {
                        if (DAT_GameCore::instance.field_0x6c == 0
                            && DAT_GameCore::instance.gameMode_2 != (Game::GameMode2)4) {
                            MACRO_CALL_MEMBER(UI::MenuTextInputState_Func::loadOrSaveGame, DAT_MenuTextInputState::ptr)(
                                9);
                        }
                    } else if (DAT_GameSynchronyState::instance.currentGameMode == (Game::GameMode)99) {
                        MACRO_CALL_MEMBER(UI::MenuTextInputState_Func::loadOrSaveGame, DAT_MenuTextInputState::ptr)(9);
                    }
                }
                break;
            case VK_ESCAPE:
                if ((lParam & 0x40000000) == 0) {
                    if (DAT_GameCore::instance.currentMenuViewType == (UI::Enums::MenuViewType)26
                        || DAT_GameCore::instance.currentMenuViewType == (UI::Enums::MenuViewType)48) {
                        MACRO_CALL_MEMBER(Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                            (UI::Enums::MenuViewType)40, 0);
                        return 0;
                    }
                    if (DAT_MenuModalComposition1::instance.activeModalDialogID == (UI::Enums::MenuModalType)29) {
                        if (DAT_MenuTextInputState::instance.DAT_MenuOptionsActionParameter == 47) {
                            return 0;
                        }
                    } else if (DAT_MenuModalComposition1::instance.activeModalDialogID
                        == (UI::Enums::MenuModalType)34) {
                        DAT_GameSynchronyState::instance.DAT_GameCommandParam0 = 1;
                        MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand,
                            DAT_GameSynchronyState::ptr)((Commands::GameCommandType)92);
                        MACRO_CALL_MEMBER(UI::MenuModalComposition_Func::activateModalDialog,
                            DAT_MenuModalComposition1::ptr)((UI::Enums::MenuModalType)-1, FALSE);
                        return 0;
                    } else if (DAT_MenuModalComposition1::instance.activeModalDialogID
                        == (UI::Enums::MenuModalType)108) {
                        MACRO_CALL(UI::MenuItems::NewEventCondition_Func::MenuItemActionHandler_NewEventCondition_Main)(
                            37);
                        return 0;
                    } else if (DAT_MenuModalComposition1::instance.activeModalDialogID == (UI::Enums::MenuModalType)27
                        || DAT_MenuModalComposition1::instance.activeModalDialogID == (UI::Enums::MenuModalType)32) {
                        MACRO_CALL_MEMBER(UI::MenuModalComposition_Func::activateModalDialog,
                            DAT_MenuModalComposition1::ptr)((UI::Enums::MenuModalType)-1, FALSE);
                        return 0;
                    }
                    if (DAT_MenuTextInputState::instance.currentModalDialog != (UI::Enums::MenuModalType)0) {
                        if (DAT_MenuModalComposition1::instance.activeModalDialogID == (UI::Enums::MenuModalType)29) {
                            if (DAT_MenuTextInputState::instance.DAT_MenuOptionsActionParameter == 2000) {
                                DAT_GameSynchronyState::instance.DAT_GameCommandParam0 = 1;
                                MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand,
                                    DAT_GameSynchronyState::ptr)((Commands::GameCommandType)104);
                            }
                            MACRO_CALL_MEMBER(
                                UI::MenuTextInputState_Func::popModalDialog, DAT_MenuTextInputState::ptr)();
                            return 0;
                        }
                        if (DAT_MenuModalComposition1::instance.activeModalDialogID == (UI::Enums::MenuModalType)35) {
                            MACRO_CALL(
                                UI::MenuItems::IdentityOptions_Func::MenuItemActionHandler_IdentityOptions_Confirm)(17);
                            return 0;
                        }
                        MACRO_CALL_MEMBER(UI::MenuTextInputState_Func::popModalDialog, DAT_MenuTextInputState::ptr)();
                        return 0;
                    }
                    if (DAT_GameCore::instance.currentMenuViewType == (UI::Enums::MenuViewType)22) {
                        MACRO_CALL_MEMBER(
                            Text::TextEditorState_Func::openUnusedHelpTextEditorDialog, DAT_TextEditorState::ptr)(-1);
                        return 0;
                    }
                    if (DAT_GameCore::instance.currentMenuViewType == (UI::Enums::MenuViewType)45) {
                        MACRO_CALL_MEMBER(
                            Text::TextEditorState_Func::closeHelpDialogAndReturnToMenu, DAT_TextEditorState::ptr)();
                        MACRO_CALL_MEMBER(UI::MenuModalComposition_Func::activateModalDialog,
                            DAT_MenuModalComposition1::ptr)((UI::Enums::MenuModalType)-1, FALSE);
                        MACRO_CALL_MEMBER(Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                            (UI::Enums::MenuViewType)41, 0);
                        return 0;
                    }
                    if (DAT_TextEditorState::instance.helpDialogVariant != 0
                        && DAT_GameCore::instance.currentMenuViewType != (UI::Enums::MenuViewType)28) {
                        MACRO_CALL_MEMBER(
                            Text::TextEditorState_Func::closeHelpDialogAndReturnToMenu, DAT_TextEditorState::ptr)();
                        return 0;
                    }
                    if (DAT_GameCore::instance.currentMenuViewType == (UI::Enums::MenuViewType)55) {
                        MACRO_CALL_MEMBER(Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                            (UI::Enums::MenuViewType)41, 0);
                        return 0;
                    }
                    if (DAT_GameCore::instance.currentMenuViewType == (UI::Enums::MenuViewType)12) {
                        MACRO_CALL_MEMBER(UI::MenuModalComposition_Func::activateModalDialog,
                            DAT_MenuModalComposition1::ptr)((UI::Enums::MenuModalType)-1, FALSE);
                        MACRO_CALL_MEMBER(Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                            (UI::Enums::MenuViewType)17, 0);
                        return 0;
                    }
                    if (MACRO_CALL_MEMBER(Game::GameCore_Func::getAreWeInAInGameMenu, DAT_GameCore::ptr)() != FALSE) {
                        if (DAT_GameCore::instance.gameMode_2 == (Game::GameMode2)1) {
                            MACRO_CALL_MEMBER(Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                                (UI::Enums::MenuViewType)17, 0);
                            return 0;
                        }
                        if (DAT_GameCore::instance.gameMode_2 == (Game::GameMode2)6) {
                            MACRO_CALL_MEMBER(Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                                (UI::Enums::MenuViewType)47, 0);
                            return 0;
                        }
                        if (DAT_GameCore::instance.specialMultiplayerState != 0) {
                            MACRO_CALL_MEMBER(
                                Synchrony::GameSynchronyState_Func::disconnectDPlay, DAT_GameSynchronyState::ptr)();
                            DAT_WindowAndDirectDraw::instance.postWindowCloseMessage = 1;
                            return 0;
                        }
                        if (DAT_GameCore::instance.menuSwitchDelay == -1
                            || DAT_GameCore::instance.menuViewToSwitchTo == (UI::Enums::MenuViewType)14
                            || DAT_GameCore::instance.menuViewToSwitchTo == (UI::Enums::MenuViewType)16) {
                            MACRO_CALL_MEMBER(UI::MenuTextInputState_Func::activateModalDialogAndClearText,
                                DAT_MenuTextInputState::ptr)((UI::Enums::MenuModalType)5);
                            return 0;
                        }
                        return 0;
                    }
                    if (DAT_GameCore::instance.currentMenuViewType == (UI::Enums::MenuViewType)19
                        || DAT_GameCore::instance.currentMenuViewType == (UI::Enums::MenuViewType)20) {
                        MACRO_CALL_MEMBER(UI::MenuModalComposition_Func::activateModalDialog,
                            DAT_MenuModalComposition1::ptr)((UI::Enums::MenuModalType)-1, FALSE);
                        MACRO_CALL_MEMBER(
                            Synchrony::GameSynchronyState_Func::disconnectDPlay, DAT_GameSynchronyState::ptr)();
                        MACRO_CALL_MEMBER(Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                            (UI::Enums::MenuViewType)41, 0);
                        return 0;
                    }
                    if (DAT_GameCore::instance.currentMenuViewType == (UI::Enums::MenuViewType)35) {
                        MACRO_CALL_MEMBER(UI::MenuModalComposition_Func::activateModalDialog,
                            DAT_MenuModalComposition1::ptr)((UI::Enums::MenuModalType)-1, FALSE);
                        MACRO_CALL_MEMBER(Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                            (UI::Enums::MenuViewType)41, 0);
                        return 0;
                    }
                    if (DAT_GameCore::instance.currentMenuViewType == (UI::Enums::MenuViewType)40) {
                        return 0;
                    }
                    if (DAT_GameCore::instance.currentMenuViewType == (UI::Enums::MenuViewType)42
                        || DAT_GameCore::instance.currentMenuViewType == (UI::Enums::MenuViewType)43
                        || DAT_GameCore::instance.currentMenuViewType == (UI::Enums::MenuViewType)44) {
                        MACRO_CALL_MEMBER(UI::MenuModalComposition_Func::activateModalDialog,
                            DAT_MenuModalComposition1::ptr)((UI::Enums::MenuModalType)-1, FALSE);
                        MACRO_CALL_MEMBER(Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                            (UI::Enums::MenuViewType)41, 0);
                        return 0;
                    }
                    if (DAT_GameCore::instance.currentMenuViewType == (UI::Enums::MenuViewType)23) {
                        if (DAT_MenuModalComposition1::instance.activeModalDialogID == (UI::Enums::MenuModalType)-1) {
                            MACRO_CALL_MEMBER(Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                                (UI::Enums::MenuViewType)3, 0);
                            return 0;
                        }
                        MACRO_CALL_MEMBER(UI::MenuModalComposition_Func::activateModalDialog,
                            DAT_MenuModalComposition1::ptr)((UI::Enums::MenuModalType)-1, FALSE);
                        return 0;
                    }
                    if (DAT_GameCore::instance.currentMenuViewType == (UI::Enums::MenuViewType)24) {
                        MACRO_CALL_MEMBER(UI::MenuModalComposition_Func::activateModalDialog,
                            DAT_MenuModalComposition1::ptr)((UI::Enums::MenuModalType)-1, FALSE);
                        MACRO_CALL_MEMBER(Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                            (UI::Enums::MenuViewType)23, 0);
                        return 0;
                    }
                    if (DAT_GameCore::instance.currentMenuViewType == (UI::Enums::MenuViewType)17) {
                        MACRO_CALL_MEMBER(UI::MenuModalComposition_Func::activateModalDialog,
                            DAT_MenuModalComposition1::ptr)((UI::Enums::MenuModalType)-1, FALSE);
                        return 0;
                    }
                    if (DAT_GameCore::instance.currentMenuViewType == (UI::Enums::MenuViewType)38
                        || DAT_GameCore::instance.currentMenuViewType == (UI::Enums::MenuViewType)39) {
                        MACRO_CALL_MEMBER(UI::MenuModalComposition_Func::activateModalDialog,
                            DAT_MenuModalComposition1::ptr)((UI::Enums::MenuModalType)-1, FALSE);
                        MACRO_CALL_MEMBER(Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                            (UI::Enums::MenuViewType)41, 0);
                        return 0;
                    }
                    if (DAT_GameCore::instance.currentMenuViewType == (UI::Enums::MenuViewType)18) {
                        MACRO_CALL_MEMBER(UI::MenuModalComposition_Func::activateModalDialog,
                            DAT_MenuModalComposition1::ptr)((UI::Enums::MenuModalType)-1, FALSE);
                        MACRO_CALL_MEMBER(Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                            (UI::Enums::MenuViewType)44, 0);
                        return 0;
                    }
                    if (DAT_GameCore::instance.currentMenuViewType == (UI::Enums::MenuViewType)31) {
                        MACRO_CALL_MEMBER(UI::MenuModalComposition_Func::activateModalDialog,
                            DAT_MenuModalComposition1::ptr)((UI::Enums::MenuModalType)-1, FALSE);
                        MACRO_CALL_MEMBER(Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                            (UI::Enums::MenuViewType)18, 0);
                        return 0;
                    }
                    if (DAT_GameCore::instance.currentMenuViewType == (UI::Enums::MenuViewType)32) {
                        MACRO_CALL_MEMBER(UI::MenuModalComposition_Func::activateModalDialog,
                            DAT_MenuModalComposition1::ptr)((UI::Enums::MenuModalType)-1, FALSE);
                        MACRO_CALL_MEMBER(Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                            (UI::Enums::MenuViewType)31, 0);
                        return 0;
                    }
                    if (DAT_GameCore::instance.currentMenuViewType == (UI::Enums::MenuViewType)25
                        || DAT_GameCore::instance.currentMenuViewType == (UI::Enums::MenuViewType)26
                        || DAT_GameCore::instance.currentMenuViewType == (UI::Enums::MenuViewType)27
                        || DAT_GameCore::instance.currentMenuViewType == (UI::Enums::MenuViewType)28
                        || DAT_GameCore::instance.currentMenuViewType == (UI::Enums::MenuViewType)29
                        || DAT_GameCore::instance.currentMenuViewType == (UI::Enums::MenuViewType)30
                        || DAT_GameCore::instance.currentMenuViewType == (UI::Enums::MenuViewType)1002) {
                        return 0;
                    }
                    if (DAT_GameCore::instance.currentMenuViewType == (UI::Enums::MenuViewType)52) {
                        MACRO_CALL_MEMBER(Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                            (UI::Enums::MenuViewType)50, 0);
                        MACRO_CALL_MEMBER(Audio::MSS::SoundSystem_Func::endSpeechStreamsAndResetLoopFlags,
                            DAT_SoundSystemState::ptr)();
                        return 0;
                    }
                    if (DAT_GameCore::instance.currentMenuViewType == (UI::Enums::MenuViewType)50
                        || DAT_GameCore::instance.currentMenuViewType == (UI::Enums::MenuViewType)51) {
                        MACRO_CALL_MEMBER(Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                            (UI::Enums::MenuViewType)28, 0);
                        MACRO_CALL_MEMBER(Audio::MSS::SoundSystem_Func::endSpeechStreamsAndResetLoopFlags,
                            DAT_SoundSystemState::ptr)();
                        return 0;
                    }
                    if (DAT_GameCore::instance.currentMenuViewType == (UI::Enums::MenuViewType)37) {
                        MACRO_CALL_MEMBER(Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                            (UI::Enums::MenuViewType)31, 0);
                        return 0;
                    }
                    if (DAT_GameCore::instance.currentMenuViewType == (UI::Enums::MenuViewType)41) {
                        MACRO_CALL_MEMBER(UI::MenuTextInputState_Func::activateModalDialogAndClearText,
                            DAT_MenuTextInputState::ptr)((UI::Enums::MenuModalType)44);
                        return 0;
                    }
                    return 0;
                }
                break;
            case 'P':
                if (MACRO_CALL_MEMBER(Game::GameCore_Func::getAreWeInAInGameMenu, DAT_GameCore::ptr)() != FALSE
                    && DAT_MenuModalComposition1::instance.activeModalDialogID == (UI::Enums::MenuModalType)-1
                    && DAT_GameCore::instance.gameMode_2 != (Game::GameMode2)1
                    && DAT_GameCore::instance.gameMode_2 != (Game::GameMode2)6
                    && DAT_GameSynchronyState::instance.currentGameMode != (Game::GameMode)1) {
                    DAT_GameCore::instance.gamePausedLogical ^= 1;
                    if (DAT_GameCore::instance.gamePausedLogical != 0) {
                        MACRO_CALL(UI::DisplayElements_Func::CheckDisplayElementByIDAndSetForUnlimitedDisplay)(
                            (UI::Enums::DisplayElementID)23, 1);
                        DAT_TileMapState::instance.currentMapperCommand = (Commands::MappersEnum)0;
                        if (DAT_GameCore::instance.genieVoiceActive != FALSE) {
                            MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(
                                s_game_paused_wav_005a77fc);
                        }
                    } else if (DAT_GameCore::instance.genieVoiceActive != FALSE) {
                        MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(
                            s_game_running_wav_005a77e8);
                    }
                }
                break;
            case 'H':
                if ((lParam & 0x40000000) == 0
                    && MACRO_CALL_MEMBER(Game::GameCore_Func::getAreWeInAInGameMenu, DAT_GameCore::ptr)() != FALSE
                    && DAT_MenuModalComposition1::instance.activeModalDialogID == (UI::Enums::MenuModalType)-1) {
                    if (DAT_ModifierKeyState::instance.shift != 0) {
                        if (DAT_GameCore::instance.viewportFocusBeforeKeepHotkey != -1) {
                            MACRO_CALL_MEMBER(Rendering::ViewportRenderState_Func::focusOnTile,
                                DAT_ViewportRenderState::ptr)(DAT_GameCore::instance.viewportFocusBeforeKeepHotkey);
                            if (DAT_GameCore::instance.currentMenuViewType == (UI::Enums::MenuViewType)16) {
                                MACRO_CALL_MEMBER(Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                                    (UI::Enums::MenuViewType)14, 0);
                            }
                            DAT_GameCore::instance.viewportFocusBeforeKeepHotkey = -1;
                        }
                    } else if (DAT_ModifierKeyState::instance.ctrl != 0) {
                        int buildingID = DAT_GameState::instance
                                             .playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                             .buildingEntryInfos[0]
                                             .id;
                        if (buildingID != 0) {
                            MACRO_CALL_MEMBER(
                                UI::Rendering::AlphaAndButtonSurface_Func::openBuildingStatusMenuForBuildingID,
                                AlphaAndButtonSurfaceObj::ptr)(buildingID);
                        }
                    } else {
                        int buildingID = DAT_GameState::instance
                                             .playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                             .buildingEntryInfos[0]
                                             .id;
                        if (buildingID != 0) {
                            DAT_GameCore::instance.viewportFocusBeforeKeepHotkey
                                = MACRO_CALL(Rendering_Func::ViewportBasedTileNumber)();
                            MACRO_CALL_MEMBER(Rendering::ViewportRenderState_Func::focusOnCoordinate,
                                DAT_ViewportRenderState::ptr)(DAT_BuildingsState::instance.buildings[buildingID].x + 2,
                                DAT_BuildingsState::instance.buildings[buildingID].y + 2);
                            MACRO_CALL_MEMBER(
                                UI::Rendering::AlphaAndButtonSurface_Func::openBuildingStatusMenuForBuildingID,
                                AlphaAndButtonSurfaceObj::ptr)(buildingID);
                        }
                    }
                }
                break;
            case 'M':
                if ((lParam & 0x40000000) == 0
                    && MACRO_CALL_MEMBER(Game::GameCore_Func::getAreWeInAInGameMenu, DAT_GameCore::ptr)() != FALSE
                    && DAT_MenuModalComposition1::instance.activeModalDialogID == (UI::Enums::MenuModalType)-1) {
                    if (DAT_ModifierKeyState::instance.shift != 0) {
                        if (DAT_GameCore::instance.viewportFocusBeforeMarketHotkey != -1) {
                            MACRO_CALL_MEMBER(Rendering::ViewportRenderState_Func::focusOnTile,
                                DAT_ViewportRenderState::ptr)(DAT_GameCore::instance.viewportFocusBeforeMarketHotkey);
                            if (DAT_GameCore::instance.currentMenuViewType == (UI::Enums::MenuViewType)16) {
                                MACRO_CALL_MEMBER(Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                                    (UI::Enums::MenuViewType)14, 0);
                            }
                            DAT_GameCore::instance.viewportFocusBeforeMarketHotkey = -1;
                        }
                    } else if (DAT_ModifierKeyState::instance.ctrl != 0) {
                        int buildingID = DAT_GameState::instance
                                             .playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                             .buildingEntryInfos[7]
                                             .id;
                        if (buildingID != 0) {
                            MACRO_CALL_MEMBER(
                                UI::Rendering::AlphaAndButtonSurface_Func::openBuildingStatusMenuForBuildingID,
                                AlphaAndButtonSurfaceObj::ptr)(buildingID);
                        }
                    } else {
                        int buildingID = DAT_GameState::instance
                                             .playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                             .buildingEntryInfos[7]
                                             .id;
                        if (buildingID != 0) {
                            DAT_GameCore::instance.viewportFocusBeforeMarketHotkey
                                = MACRO_CALL(Rendering_Func::ViewportBasedTileNumber)();
                            MACRO_CALL_MEMBER(Rendering::ViewportRenderState_Func::focusOnCoordinate,
                                DAT_ViewportRenderState::ptr)(DAT_BuildingsState::instance.buildings[buildingID].x + 2,
                                DAT_BuildingsState::instance.buildings[buildingID].y + 2);
                            MACRO_CALL_MEMBER(
                                UI::Rendering::AlphaAndButtonSurface_Func::openBuildingStatusMenuForBuildingID,
                                AlphaAndButtonSurfaceObj::ptr)(buildingID);
                        }
                    }
                }
                break;
            case 'S':
                if ((lParam & 0x40000000) == 0
                    && MACRO_CALL_MEMBER(Game::GameCore_Func::getAreWeInAInGameMenu, DAT_GameCore::ptr)() != FALSE
                    && DAT_MenuModalComposition1::instance.activeModalDialogID == (UI::Enums::MenuModalType)-1) {
                    int signpostID = DAT_GameState::instance.mapAndTime.signpostIDs[DAT_00df5538::instance];
                    if (signpostID != 0) {
                        MACRO_CALL_MEMBER(Rendering::ViewportRenderState_Func::focusOnCoordinate,
                            DAT_ViewportRenderState::ptr)(DAT_BuildingsState::instance.buildings[signpostID].x + 1,
                            DAT_BuildingsState::instance.buildings[signpostID].y + 1);
                    }
                    ++DAT_00df5538::instance;
                    if ((int)DAT_00df5538::instance >= 8) {
                        DAT_00df5538::instance = 0;
                    }
                    int tries = 1;
                    if (DAT_GameState::instance.mapAndTime.signpostIDs[DAT_00df5538::instance] == 0) {
                        do {
                            ++DAT_00df5538::instance;
                            if ((int)DAT_00df5538::instance >= 8) {
                                DAT_00df5538::instance = 0;
                            }
                            ++tries;
                            if (tries >= 8) {
                                break;
                            }
                        } while (DAT_GameState::instance.mapAndTime.signpostIDs[DAT_00df5538::instance] == 0);
                    }
                }
                break;
            case 'B':
                if ((lParam & 0x40000000) == 0
                    && MACRO_CALL_MEMBER(Game::GameCore_Func::getAreWeInAInGameMenu, DAT_GameCore::ptr)() != FALSE
                    && DAT_MenuModalComposition1::instance.activeModalDialogID == (UI::Enums::MenuModalType)-1) {
                    if (DAT_ModifierKeyState::instance.shift != 0) {
                        if (DAT_GameCore::instance.viewportFocusBeforeBarracksHotkey != -1) {
                            MACRO_CALL_MEMBER(Rendering::ViewportRenderState_Func::focusOnTile,
                                DAT_ViewportRenderState::ptr)(DAT_GameCore::instance.viewportFocusBeforeBarracksHotkey);
                            if (DAT_GameCore::instance.currentMenuViewType == (UI::Enums::MenuViewType)16) {
                                MACRO_CALL_MEMBER(Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                                    (UI::Enums::MenuViewType)14, 0);
                            }
                            DAT_GameCore::instance.viewportFocusBeforeBarracksHotkey = -1;
                        }
                    } else if (DAT_ModifierKeyState::instance.ctrl != 0) {
                        int buildingID = DAT_GameState::instance
                                             .playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                             .buildingEntryInfos[5]
                                             .id;
                        if (buildingID != 0) {
                            MACRO_CALL_MEMBER(
                                UI::Rendering::AlphaAndButtonSurface_Func::openBuildingStatusMenuForBuildingID,
                                AlphaAndButtonSurfaceObj::ptr)(buildingID);
                        }
                    } else {
                        int buildingID = DAT_GameState::instance
                                             .playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                             .buildingEntryInfos[5]
                                             .id;
                        if (buildingID != 0) {
                            DAT_GameCore::instance.viewportFocusBeforeBarracksHotkey
                                = MACRO_CALL(Rendering_Func::ViewportBasedTileNumber)();
                            MACRO_CALL_MEMBER(Rendering::ViewportRenderState_Func::focusOnCoordinate,
                                DAT_ViewportRenderState::ptr)(DAT_BuildingsState::instance.buildings[buildingID].x + 2,
                                DAT_BuildingsState::instance.buildings[buildingID].y + 2);
                            MACRO_CALL_MEMBER(
                                UI::Rendering::AlphaAndButtonSurface_Func::openBuildingStatusMenuForBuildingID,
                                AlphaAndButtonSurfaceObj::ptr)(buildingID);
                        }
                    }
                }
                break;
            case 'I':
                if ((lParam & 0x40000000) == 0
                    && MACRO_CALL_MEMBER(Game::GameCore_Func::getAreWeInAInGameMenu, DAT_GameCore::ptr)() != FALSE
                    && DAT_MenuModalComposition1::instance.activeModalDialogID == (UI::Enums::MenuModalType)-1) {
                    if (DAT_ModifierKeyState::instance.shift != 0) {
                        if (DAT_GameCore::instance.viewportFocusBeforeEngineersGuildHotkey != -1) {
                            MACRO_CALL_MEMBER(
                                Rendering::ViewportRenderState_Func::focusOnTile, DAT_ViewportRenderState::ptr)(
                                DAT_GameCore::instance.viewportFocusBeforeEngineersGuildHotkey);
                            if (DAT_GameCore::instance.currentMenuViewType == (UI::Enums::MenuViewType)16) {
                                MACRO_CALL_MEMBER(Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                                    (UI::Enums::MenuViewType)14, 0);
                            }
                            DAT_GameCore::instance.viewportFocusBeforeEngineersGuildHotkey = -1;
                        }
                    } else if (DAT_ModifierKeyState::instance.ctrl != 0) {
                        int buildingID = DAT_GameState::instance
                                             .playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                             .buildingEntryInfos[9]
                                             .id;
                        if (buildingID != 0) {
                            MACRO_CALL_MEMBER(
                                UI::Rendering::AlphaAndButtonSurface_Func::openBuildingStatusMenuForBuildingID,
                                AlphaAndButtonSurfaceObj::ptr)(buildingID);
                        }
                    } else {
                        int buildingID = DAT_GameState::instance
                                             .playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                             .buildingEntryInfos[9]
                                             .id;
                        if (buildingID != 0) {
                            DAT_GameCore::instance.viewportFocusBeforeEngineersGuildHotkey
                                = MACRO_CALL(Rendering_Func::ViewportBasedTileNumber)();
                            MACRO_CALL_MEMBER(Rendering::ViewportRenderState_Func::focusOnCoordinate,
                                DAT_ViewportRenderState::ptr)(DAT_BuildingsState::instance.buildings[buildingID].x + 2,
                                DAT_BuildingsState::instance.buildings[buildingID].y + 2);
                            MACRO_CALL_MEMBER(
                                UI::Rendering::AlphaAndButtonSurface_Func::openBuildingStatusMenuForBuildingID,
                                AlphaAndButtonSurfaceObj::ptr)(buildingID);
                        }
                    }
                }
                break;
            case 'L':
                if ((lParam & 0x40000000) == 0
                    && MACRO_CALL_MEMBER(Game::GameCore_Func::getAreWeInAInGameMenu, DAT_GameCore::ptr)() != FALSE
                    && DAT_MenuModalComposition1::instance.activeModalDialogID == (UI::Enums::MenuModalType)-1) {
                    if (DAT_ModifierKeyState::instance.shift == 0) {
                        int playerID = DAT_GameSynchronyState::instance.currentPlayerSlotID;
                        int lordID = DAT_GameState::instance.playerDataArray[playerID].lordID;
                        if (lordID != 0 && DAT_UnitsState::instance.units[lordID].unitType == 55
                            && DAT_UnitsState::instance.units[lordID].owner == playerID
                            && DAT_UnitsState::instance.units[lordID].logicalState == 2) {
                            MACRO_CALL_MEMBER(Rendering::ViewportRenderState_Func::focusOnTile,
                                DAT_ViewportRenderState::ptr)(DAT_UnitsState::instance.units[lordID].tile);
                        }
                    } else {
                        for (int i = 0; i < 8; ++i) {
                            int cyclingID = DAT_ShortcutDefinedData::instance.CyclingLordID++;
                            if (DAT_ShortcutDefinedData::instance.CyclingLordID == 9) {
                                DAT_ShortcutDefinedData::instance.CyclingLordID = 1;
                            }
                            int lordID = MACRO_CALL_MEMBER(
                                Map::Units::UnitsState_Func::getAliveLordForPlayer, DAT_UnitsState::ptr)(cyclingID);
                            if (lordID != 0) {
                                MACRO_CALL_MEMBER(Rendering::ViewportRenderState_Func::focusOnTile,
                                    DAT_ViewportRenderState::ptr)(DAT_UnitsState::instance.units[lordID].tile);
                                break;
                            }
                        }
                    }
                }
                break;
            case 'T':
                if ((lParam & 0x40000000) == 0
                    && MACRO_CALL_MEMBER(Game::GameCore_Func::getAreWeInAInGameMenu, DAT_GameCore::ptr)() != FALSE
                    && DAT_MenuModalComposition1::instance.activeModalDialogID == (UI::Enums::MenuModalType)-1) {
                    if (DAT_ModifierKeyState::instance.shift != 0) {
                        if (DAT_GameCore::instance.field_0x2364 != -1) {
                            MACRO_CALL_MEMBER(Rendering::ViewportRenderState_Func::focusOnTile,
                                DAT_ViewportRenderState::ptr)(DAT_GameCore::instance.field_0x2364);
                            if (DAT_GameCore::instance.currentMenuViewType == (UI::Enums::MenuViewType)16) {
                                MACRO_CALL_MEMBER(Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                                    (UI::Enums::MenuViewType)14, 0);
                            }
                            DAT_GameCore::instance.field_0x2364 = -1;
                        }
                    } else if (DAT_ModifierKeyState::instance.ctrl != 0) {
                        int buildingID = DAT_GameState::instance
                                             .playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                             .buildingEntryInfos[10]
                                             .id;
                        if (buildingID != 0) {
                            MACRO_CALL_MEMBER(
                                UI::Rendering::AlphaAndButtonSurface_Func::openBuildingStatusMenuForBuildingID,
                                AlphaAndButtonSurfaceObj::ptr)(buildingID);
                        }
                    } else {
                        int buildingID = DAT_GameState::instance
                                             .playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                             .buildingEntryInfos[10]
                                             .id;
                        if (buildingID != 0) {
                            DAT_GameCore::instance.field_0x2364 = MACRO_CALL(Rendering_Func::ViewportBasedTileNumber)();
                            MACRO_CALL_MEMBER(Rendering::ViewportRenderState_Func::focusOnCoordinate,
                                DAT_ViewportRenderState::ptr)(DAT_BuildingsState::instance.buildings[buildingID].x + 2,
                                DAT_BuildingsState::instance.buildings[buildingID].y + 2);
                            MACRO_CALL_MEMBER(
                                UI::Rendering::AlphaAndButtonSurface_Func::openBuildingStatusMenuForBuildingID,
                                AlphaAndButtonSurfaceObj::ptr)(buildingID);
                        }
                    }
                }
                break;
            case 'N':
                if ((lParam & 0x40000000) == 0
                    && MACRO_CALL_MEMBER(Game::GameCore_Func::getAreWeInAInGameMenu, DAT_GameCore::ptr)() != FALSE
                    && DAT_MenuModalComposition1::instance.activeModalDialogID == (UI::Enums::MenuModalType)-1) {
                    if (DAT_ModifierKeyState::instance.shift != 0) {
                        if (DAT_GameCore::instance.viewportFocusBeforeMercenaryHotkey != -1) {
                            MACRO_CALL_MEMBER(
                                Rendering::ViewportRenderState_Func::focusOnTile, DAT_ViewportRenderState::ptr)(
                                DAT_GameCore::instance.viewportFocusBeforeMercenaryHotkey);
                            if (DAT_GameCore::instance.currentMenuViewType == (UI::Enums::MenuViewType)16) {
                                MACRO_CALL_MEMBER(Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                                    (UI::Enums::MenuViewType)14, 0);
                            }
                            DAT_GameCore::instance.viewportFocusBeforeMercenaryHotkey = -1;
                        }
                    } else if (DAT_ModifierKeyState::instance.ctrl != 0) {
                        int buildingID = DAT_GameState::instance
                                             .playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                             .buildingEntryInfos[11]
                                             .id;
                        if (buildingID != 0) {
                            MACRO_CALL_MEMBER(
                                UI::Rendering::AlphaAndButtonSurface_Func::openBuildingStatusMenuForBuildingID,
                                AlphaAndButtonSurfaceObj::ptr)(buildingID);
                        }
                    } else {
                        int buildingID = DAT_GameState::instance
                                             .playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                             .buildingEntryInfos[11]
                                             .id;
                        if (buildingID != 0) {
                            DAT_GameCore::instance.viewportFocusBeforeMercenaryHotkey
                                = MACRO_CALL(Rendering_Func::ViewportBasedTileNumber)();
                            MACRO_CALL_MEMBER(Rendering::ViewportRenderState_Func::focusOnCoordinate,
                                DAT_ViewportRenderState::ptr)(DAT_BuildingsState::instance.buildings[buildingID].x + 2,
                                DAT_BuildingsState::instance.buildings[buildingID].y + 2);
                            MACRO_CALL_MEMBER(
                                UI::Rendering::AlphaAndButtonSurface_Func::openBuildingStatusMenuForBuildingID,
                                AlphaAndButtonSurfaceObj::ptr)(buildingID);
                        }
                    }
                }
                break;
            case 'G':
                if ((lParam & 0x40000000) == 0
                    && MACRO_CALL_MEMBER(Game::GameCore_Func::getAreWeInAInGameMenu, DAT_GameCore::ptr)() != FALSE
                    && DAT_MenuModalComposition1::instance.activeModalDialogID == (UI::Enums::MenuModalType)-1) {
                    if (DAT_ModifierKeyState::instance.shift != 0) {
                        if (DAT_GameCore::instance.viewportFocusBeforeGranaryHotkey != -1) {
                            MACRO_CALL_MEMBER(Rendering::ViewportRenderState_Func::focusOnTile,
                                DAT_ViewportRenderState::ptr)(DAT_GameCore::instance.viewportFocusBeforeGranaryHotkey);
                            if (DAT_GameCore::instance.currentMenuViewType == (UI::Enums::MenuViewType)16) {
                                MACRO_CALL_MEMBER(Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                                    (UI::Enums::MenuViewType)14, 0);
                            }
                            DAT_GameCore::instance.viewportFocusBeforeGranaryHotkey = -1;
                        }
                    } else if (DAT_ModifierKeyState::instance.ctrl != 0) {
                        int buildingID = DAT_GameState::instance
                                             .playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                             .buildingEntryInfos[2]
                                             .id;
                        if (buildingID != 0) {
                            MACRO_CALL_MEMBER(
                                UI::Rendering::AlphaAndButtonSurface_Func::openBuildingStatusMenuForBuildingID,
                                AlphaAndButtonSurfaceObj::ptr)(buildingID);
                        }
                    } else {
                        int buildingID = DAT_GameState::instance
                                             .playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                             .buildingEntryInfos[2]
                                             .id;
                        if (buildingID != 0) {
                            DAT_GameCore::instance.viewportFocusBeforeGranaryHotkey
                                = MACRO_CALL(Rendering_Func::ViewportBasedTileNumber)();
                            MACRO_CALL_MEMBER(Rendering::ViewportRenderState_Func::focusOnCoordinate,
                                DAT_ViewportRenderState::ptr)(DAT_BuildingsState::instance.buildings[buildingID].x + 2,
                                DAT_BuildingsState::instance.buildings[buildingID].y + 2);
                            MACRO_CALL_MEMBER(
                                UI::Rendering::AlphaAndButtonSurface_Func::openBuildingStatusMenuForBuildingID,
                                AlphaAndButtonSurfaceObj::ptr)(buildingID);
                        }
                    }
                }
                break;
            case 'A':
                if ((lParam & 0x40000000) == 0
                    && MACRO_CALL_MEMBER(Game::GameCore_Func::getAreWeInAInGameMenu, DAT_GameCore::ptr)() != FALSE
                    && DAT_MenuModalComposition1::instance.activeModalDialogID == (UI::Enums::MenuModalType)-1) {
                    if (DAT_ModifierKeyState::instance.shift != 0) {
                        if (DAT_GameCore::instance.viewportFocusBeforeArmoryHotkey != -1) {
                            MACRO_CALL_MEMBER(Rendering::ViewportRenderState_Func::focusOnTile,
                                DAT_ViewportRenderState::ptr)(DAT_GameCore::instance.viewportFocusBeforeArmoryHotkey);
                            if (DAT_GameCore::instance.currentMenuViewType == (UI::Enums::MenuViewType)16) {
                                MACRO_CALL_MEMBER(Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                                    (UI::Enums::MenuViewType)14, 0);
                            }
                            DAT_GameCore::instance.viewportFocusBeforeArmoryHotkey = -1;
                        }
                    } else if (DAT_ModifierKeyState::instance.ctrl != 0) {
                        int buildingID = DAT_GameState::instance
                                             .playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                             .buildingEntryInfos[3]
                                             .id;
                        if (buildingID != 0) {
                            MACRO_CALL_MEMBER(
                                UI::Rendering::AlphaAndButtonSurface_Func::openBuildingStatusMenuForBuildingID,
                                AlphaAndButtonSurfaceObj::ptr)(buildingID);
                        }
                    } else {
                        int buildingID = DAT_GameState::instance
                                             .playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                             .buildingEntryInfos[3]
                                             .id;
                        if (buildingID != 0) {
                            DAT_GameCore::instance.viewportFocusBeforeArmoryHotkey
                                = MACRO_CALL(Rendering_Func::ViewportBasedTileNumber)();
                            MACRO_CALL_MEMBER(Rendering::ViewportRenderState_Func::focusOnCoordinate,
                                DAT_ViewportRenderState::ptr)(DAT_BuildingsState::instance.buildings[buildingID].x + 2,
                                DAT_BuildingsState::instance.buildings[buildingID].y + 2);
                            MACRO_CALL_MEMBER(
                                UI::Rendering::AlphaAndButtonSurface_Func::openBuildingStatusMenuForBuildingID,
                                AlphaAndButtonSurfaceObj::ptr)(buildingID);
                        }
                    }
                }
                break;
            case 'X':
                if (MACRO_CALL_MEMBER(Game::GameCore_Func::getAreWeInAInGameMenu, DAT_GameCore::ptr)() != FALSE
                    && DAT_MenuModalComposition1::instance.activeModalDialogID == (UI::Enums::MenuModalType)-1
                    && DAT_MouseState::instance.rightClickState == FALSE) {
                    MACRO_CALL_MEMBER(Map::TileMapState_Func::setMapRotation, DAT_TileMapState::ptr)(
                        (DAT_TileMapState::instance.mapOrientation + 2) % 8);
                }
                break;
            case 'C':
                if (MACRO_CALL_MEMBER(Game::GameCore_Func::getAreWeInAInGameMenu, DAT_GameCore::ptr)() != FALSE
                    && DAT_MenuModalComposition1::instance.activeModalDialogID == (UI::Enums::MenuModalType)-1
                    && DAT_MouseState::instance.rightClickState == FALSE) {
                    MACRO_CALL_MEMBER(Map::TileMapState_Func::setMapRotation, DAT_TileMapState::ptr)(
                        (DAT_TileMapState::instance.mapOrientation + 6) % 8);
                }
                break;
            case 'V':
                if (MACRO_CALL_MEMBER(Game::GameCore_Func::getAreWeInAInGameMenu, DAT_GameCore::ptr)() != FALSE
                    && DAT_MenuModalComposition1::instance.activeModalDialogID == (UI::Enums::MenuModalType)-1
                    && DAT_MouseState::instance.rightClickState == FALSE) {
                    MACRO_CALL_MEMBER(Map::TileMapState_Func::triggerLoweredView, DAT_TileMapState::ptr)(3);
                    DAT_ModifierKeyState::instance.v = 1;
                }
                break;
            case 'Z':
                if ((lParam & 0x40000000) == 0
                    && MACRO_CALL_MEMBER(Game::GameCore_Func::getAreWeInAInGameMenu, DAT_GameCore::ptr)() != FALSE
                    && DAT_MenuModalComposition1::instance.activeModalDialogID == (UI::Enums::MenuModalType)-1
                    && DAT_MouseState::instance.rightClickState == FALSE) {
                    if (DAT_ViewportRenderState::instance.viewportState.isZoomedOutUnk != 0) {
                        MACRO_CALL_MEMBER(
                            Rendering::ViewportRenderState_Func::resetupViewport, DAT_ViewportRenderState::ptr)(0);
                    } else {
                        MACRO_CALL_MEMBER(
                            Rendering::ViewportRenderState_Func::resetupViewport, DAT_ViewportRenderState::ptr)(1);
                    }
                    DAT_UIDragDropDefinedData::instance.MenuView_TriggerInitial = TRUE;
                    DAT_WindowAndDirectDraw::instance.unk_resetViewportRelated = 2;
                }
                break;
            case 'Q':
                if (DAT_MenuModalComposition1::instance.activeModalDialogID == (UI::Enums::MenuModalType)-1
                    && DAT_GameCore::instance.currentMenuViewType == (UI::Enums::MenuViewType)14
                    && (DAT_GameCore::instance.activeMenuTab.tabType == (UI::Enums::BuildingsAndStatusMenuTabType)61
                        || DAT_GameCore::instance.activeMenuTab.tabType
                            == (UI::Enums::BuildingsAndStatusMenuTabType)62)) {
                    MACRO_CALL_MEMBER(Map::Units::TribesState_Func::queueUnitStance, DAT_TribesState::ptr)(
                        DAT_TribesState::instance.DAT_CurrentTribeID, 0);
                }
                break;
            case 'W':
                if (DAT_MenuModalComposition1::instance.activeModalDialogID == (UI::Enums::MenuModalType)-1
                    && DAT_GameCore::instance.currentMenuViewType == (UI::Enums::MenuViewType)14
                    && (DAT_GameCore::instance.activeMenuTab.tabType == (UI::Enums::BuildingsAndStatusMenuTabType)61
                        || DAT_GameCore::instance.activeMenuTab.tabType
                            == (UI::Enums::BuildingsAndStatusMenuTabType)62)) {
                    MACRO_CALL_MEMBER(Map::Units::TribesState_Func::queueUnitStance, DAT_TribesState::ptr)(
                        DAT_TribesState::instance.DAT_CurrentTribeID, 1);
                }
                break;
            case 'E':
                if (DAT_MenuModalComposition1::instance.activeModalDialogID == (UI::Enums::MenuModalType)-1
                    && DAT_GameCore::instance.currentMenuViewType == (UI::Enums::MenuViewType)14
                    && (DAT_GameCore::instance.activeMenuTab.tabType == (UI::Enums::BuildingsAndStatusMenuTabType)61
                        || DAT_GameCore::instance.activeMenuTab.tabType
                            == (UI::Enums::BuildingsAndStatusMenuTabType)62)) {
                    MACRO_CALL_MEMBER(Map::Units::TribesState_Func::queueUnitStance, DAT_TribesState::ptr)(
                        DAT_TribesState::instance.DAT_CurrentTribeID, 2);
                }
                break;
            case VK_NUMPAD0:
            case VK_NUMPAD1:
            case VK_NUMPAD2:
            case VK_NUMPAD3:
            case VK_NUMPAD4:
            case VK_NUMPAD5:
            case VK_NUMPAD6:
            case VK_NUMPAD7:
            case VK_NUMPAD8:
            case VK_NUMPAD9:
                wParam -= 48;
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
                if ((lParam & 0x40000000) == 0
                    && DAT_MenuModalComposition1::instance.activeModalDialogID == (UI::Enums::MenuModalType)-1
                    && MACRO_CALL_MEMBER(Game::GameCore_Func::getAreWeInAInGameMenu, DAT_GameCore::ptr)() != FALSE) {
                    if (DAT_ModifierKeyState::instance.ctrl != 0) {
                        if (DAT_ModifierKeyState::instance.alt != 0) {
                            goto label_BookmarkCamera;
                        }
                        if (DAT_TribesState::instance.DAT_CurrentTribeID != 0
                            && DAT_TileMapState::instance.shiftRelated0or3 == 1
                            && DAT_TribesState::instance.DAT_CurrentTribeID != 0) {
                            MACRO_CALL_MEMBER(Game::GameStateStructures_Func::clearTribeHotKey, DAT_GameState::ptr)(
                                wParam - '0');
                            MACRO_CALL_MEMBER(Game::GameStateStructures_Func::assignSelectionToKey, DAT_GameState::ptr)(
                                wParam - '0', DAT_TribesState::instance.DAT_CurrentTribeID);
                        }
                    } else {
                        if (DAT_GameCore::instance.currentMenuViewType == (UI::Enums::MenuViewType)16) {
                            if (DAT_GameCore::instance.activeMenuTab.tabType
                                == (UI::Enums::BuildingsAndStatusMenuTabType)1) {
                                int offset;
                                switch (wParam) {
                                case '1':
                                    offset = 0;
                                    break;
                                case '2':
                                    offset = 2;
                                    break;
                                case '3':
                                    offset = 3;
                                    break;
                                case '4':
                                    offset = 1;
                                    break;
                                case '5':
                                    offset = 4;
                                    break;
                                case '6':
                                    offset = 5;
                                    break;
                                case '7':
                                    offset = 6;
                                    break;
                                default:
                                    goto label_DefWindowProc;
                                }
                                MACRO_CALL(
                                    UI::MenuItems::General_Func::MenuItemActionHandler_General_ToolbarButtonPressed)(
                                    (Commands::MappersEnum)(offset + 332));
                                break;
                            }
                            if (DAT_GameCore::instance.activeMenuTab.tabType
                                == (UI::Enums::BuildingsAndStatusMenuTabType)44) {
                                int offset;
                                switch (wParam) {
                                case '1':
                                    offset = 0;
                                    break;
                                case '2':
                                    offset = 2;
                                    break;
                                case '3':
                                    offset = 4;
                                    break;
                                case '4':
                                    offset = 3;
                                    break;
                                case '5':
                                    offset = 1;
                                    break;
                                case '6':
                                    offset = 6;
                                    break;
                                case '7':
                                    offset = 5;
                                    break;
                                default:
                                    goto label_DefWindowProc;
                                }
                                MACRO_CALL(
                                    UI::MenuItems::General_Func::MenuItemActionHandler_General_ToolbarButtonPressed)(
                                    (Commands::MappersEnum)(offset + 360));
                                break;
                            }
                            if (DAT_GameCore::instance.activeMenuTab.tabType
                                == (UI::Enums::BuildingsAndStatusMenuTabType)23) {
                                int offset = wParam - '1';
                                if ((unsigned int)offset <= 1) {
                                    MACRO_CALL(UI::MenuItems::General_Func::
                                            MenuItemActionHandler_General_ToolbarButtonPressed)(
                                        (Commands::MappersEnum)(offset + 367));
                                }
                                break;
                            }
                            if (DAT_GameCore::instance.activeMenuTab.tabType
                                == (UI::Enums::BuildingsAndStatusMenuTabType)24) {
                                if (wParam - '1' == 0) {
                                    MACRO_CALL(UI::MenuItems::General_Func::
                                            MenuItemActionHandler_General_ToolbarButtonPressed)(
                                        (Commands::MappersEnum)369);
                                }
                                break;
                            }
                            if (DAT_GameCore::instance.activeMenuTab.tabType
                                == (UI::Enums::BuildingsAndStatusMenuTabType)96) {
                                if (wParam - '1' == 0) {
                                    MACRO_CALL(UI::MenuItems::General_Func::
                                            MenuItemActionHandler_General_ToolbarButtonPressed)(
                                        (Commands::MappersEnum)370);
                                }
                                break;
                            }
                        }
                        int hotkey = wParam - '0';
                        if (MACRO_CALL_MEMBER(
                                Map::Units::UnitsState_Func::isUnitShortcutAvailable, DAT_UnitsState::ptr)(hotkey)
                            == FALSE) {
                            MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::queueEscapeCommand, DAT_UnitsState::ptr)();
                            MACRO_CALL_MEMBER(
                                Map::Units::UnitsState_Func::makeSelectionBasedOnShortcut, DAT_UnitsState::ptr)(hotkey);
                            if (DAT_UnitsState::instance.totalUnitsInSelection > 0) {
                                if (DAT_GameCore::instance.buildmenuMenuTabToSwitchTo.tabType
                                    != (UI::Enums::BuildingsAndStatusMenuTabType)61) {
                                    DAT_GameCore::instance.tabTypeSiegeSubset
                                        = DAT_GameCore::instance.buildmenuMenuTabToSwitchTo.buildMenuTab;
                                }
                                DAT_GameCore::instance.buildmenuMenuTabToSwitchTo.tabType
                                    = (UI::Enums::BuildingsAndStatusMenuTabType)61;
                                MACRO_CALL_MEMBER(Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                                    (UI::Enums::MenuViewType)14, 0);
                                DAT_TileMapState::instance.shiftRelated0or3 = 1;
                                DAT_UnitsState::instance.pendingUnitControlMode = TRUE;
                                DAT_UnitsState::instance.unitControlsRelated = 1;
                                DAT_UnitsState::instance.hasEngineerSelected = FALSE;
                                DAT_UIDragDropDefinedData::instance.MenuView_TriggerInitial = TRUE;
                            }
                        } else {
                            int unitID = DAT_GameState::instance.hotkeyTribes[hotkey].units[0].id;
                            int i = 0;
                            if (unitID == -1) {
                                do {
                                    ++i;
                                    if (i >= 2500) {
                                        break;
                                    }
                                    unitID = DAT_GameState::instance.hotkeyTribes[hotkey].units[i].id;
                                } while (unitID == -1);
                            }
                            if (unitID > 0) {
                                MACRO_CALL_MEMBER(Rendering::ViewportRenderState_Func::focusOnCoordinate,
                                    DAT_ViewportRenderState::ptr)(
                                    DAT_UnitsState::instance.units[unitID].x, DAT_UnitsState::instance.units[unitID].y);
                            }
                        }
                    }
                }
                break;
            case VK_ADD:
                if ((lParam & 0x40000000) == 0
                    && MACRO_CALL_MEMBER(Game::GameCore_Func::getAreWeInAInGameMenu, DAT_GameCore::ptr)() != FALSE
                    && DAT_MenuModalComposition1::instance.activeModalDialogID == (UI::Enums::MenuModalType)-1
                    && (DAT_GameSynchronyState::instance.currentGameMode == (Game::GameMode)0
                        || DAT_GameSynchronyState::instance.currentGameMode == (Game::GameMode)99)
                    && DAT_GameCore::instance.gameSpeedLevel < 90) {
                    DAT_GameCore::instance.gameSpeedLevel += 5;
                    if (DAT_GameCore::instance.gameSpeedLevel > 90) {
                        DAT_GameCore::instance.gameSpeedLevel = 90;
                    }
                    MACRO_CALL(UI::DisplayElements_Func::ActivateGameSpeedAndResourceLackDisplayElementUnk)(
                        (UI::Enums::DisplayElementID)24, 1, 5000);
                }
                break;
            case VK_SUBTRACT:
                if ((lParam & 0x40000000) == 0
                    && MACRO_CALL_MEMBER(Game::GameCore_Func::getAreWeInAInGameMenu, DAT_GameCore::ptr)() != FALSE
                    && DAT_MenuModalComposition1::instance.activeModalDialogID == (UI::Enums::MenuModalType)-1
                    && (DAT_GameSynchronyState::instance.currentGameMode == (Game::GameMode)0
                        || DAT_GameSynchronyState::instance.currentGameMode == (Game::GameMode)99)
                    && DAT_GameCore::instance.gameSpeedLevel > 10) {
                    DAT_GameCore::instance.gameSpeedLevel -= 5;
                    if (DAT_GameCore::instance.gameSpeedLevel < 20) {
                        DAT_GameCore::instance.gameSpeedLevel = 20;
                    }
                    MACRO_CALL(UI::DisplayElements_Func::ActivateGameSpeedAndResourceLackDisplayElementUnk)(
                        (UI::Enums::DisplayElementID)24, 1, 5000);
                }
                break;
            case VK_F3:
            case VK_F4:
            case VK_F5:
            case VK_F6:
            case VK_F7:
            case VK_F8:
            case VK_F9:
            case VK_F10:
                goto label_F1_to_F10;
            }
            break;
        case WM_SYSKEYDOWN:
            DAT_ModifierKeyState::instance.keyDownUnk = 1;
            switch (wParam) {
            case VK_RETURN:
            case VK_SHIFT:
            case VK_CONTROL:
            case 'A':
            case 'S':
                break;
            case VK_MENU:
                return 1;
            case 'H':
                if (DAT_GameCore::instance.gameMode_2 == (Game::GameMode2)1) {
                    BOOL halted = DAT_GameCore::instance.isTimeHalted2 == 0;
                    DAT_GameCore::instance.isTimeHalted2 = halted;
                    DAT_GameCore::instance.isTimeHalted = (WindowsHelper::Enums::BOOLEnum)halted;
                }
                break;
            case 'Q':
                if (MACRO_CALL_MEMBER(Game::GameCore_Func::getAreWeInAInGameMenu, DAT_GameCore::ptr)() != FALSE) {
                    MACRO_CALL_MEMBER(UI::Rendering::WindowAndDirectDraw_Func::takeScreenshot,
                        DAT_WindowAndDirectDraw::ptr)(DAT_ShortcutDefinedData::instance.ScreenshotFilenameVariant);
                    ++DAT_ShortcutDefinedData::instance.ScreenshotFilenameVariant;
                }
                break;
            case 'D':
                if (DAT_GameCore::instance.currentMenuViewType == (UI::Enums::MenuViewType)12
                    || (DAT_GameCore::instance.currentMenuViewType == (UI::Enums::MenuViewType)14
                        && DAT_GameCore::instance.gameMode_2 == (Game::GameMode2)1)) {
                    ++DAT_ViewportRenderState::instance.DAT_MapEditorDisplayLayer;
                    if ((int)DAT_ViewportRenderState::instance.DAT_MapEditorDisplayLayer > 2) {
                        DAT_ViewportRenderState::instance.DAT_MapEditorDisplayLayer = 0;
                    }
                    MACRO_CALL(UI::DisplayElements_Func::CheckDisplayElementByIDAndSetForUnlimitedDisplay)(
                        (UI::Enums::DisplayElementID)2, DAT_ViewportRenderState::instance.DAT_MapEditorDisplayLayer);
                }
                break;
            case 'T':
                if (DAT_GameSynchronyState::instance.currentGameMode != (Game::GameMode)0
                    && DAT_GameSynchronyState::instance.currentGameMode != (Game::GameMode)99) {
                    MACRO_CALL(UI::DisplayElements_Func::TogglePlayerPingDisplayElementUnk)(
                        (UI::Enums::DisplayElementID)22, 1);
                }
                break;
            case 'E':
                if (DAT_GameCore::instance.currentMenuViewType == (UI::Enums::MenuViewType)17
                    || DAT_GameCore::instance.currentMenuViewType == (UI::Enums::MenuViewType)12
                    || (DAT_GameCore::instance.currentMenuViewType == (UI::Enums::MenuViewType)14
                        && DAT_GameCore::instance.gameMode_2 == (Game::GameMode2)1)) {
                    MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::killAllUnownedUnits, DAT_UnitsState::ptr)();
                }
                break;
            case 'K':
                if (DAT_GameSynchronyState::instance.currentGameMode == (Game::GameMode)0
                    && DAT_GameCore::instance.cheatModeFlag != FALSE) {
                    DAT_GameCore::instance.solitaryAllBuildingsAreFree
                        = (WindowsHelper::Enums::BOOLEnum)(DAT_GameCore::instance.solitaryAllBuildingsAreFree == FALSE);
                }
                break;
            case 'U':
                if (DAT_GameSynchronyState::instance.currentGameMode == (Game::GameMode)0
                    && DAT_GameCore::instance.currentMenuViewType == (UI::Enums::MenuViewType)16
                    && DAT_BuildingsState::instance.buildings[DAT_BuildingsState::instance.menuSelectedBuildingID]
                            .buildingType
                        == (Map::Buildings::BuildingType)94) {
                    DAT_GameCore::instance.solitaryAltUDungeon = TRUE;
                }
                break;
            case 'C':
                if (DAT_GameCore::instance.cheatModeFlag != FALSE
                    && MACRO_CALL_MEMBER(Game::GameCore_Func::getAreWeInAInGameMenu, DAT_GameCore::ptr)() == FALSE) {
                    DAT_GameCore::instance.unlockAllHistoricalCampaigns = 1;
                }
                break;
            case 'X':
                if (DAT_GameSynchronyState::instance.currentGameMode != (Game::GameMode)1
                    && DAT_GameCore::instance.cheatModeFlag != FALSE) {
                    DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                        .popularity = 10000;
                    DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                        .currentResources[15] += 1000;
                }
                break;
            case 'R':
                DAT_GameCore::instance.altRToggleMinimapHideWildlife
                    = DAT_GameCore::instance.altRToggleMinimapHideWildlife == 0;
                break;
            case 'V':
                if (DAT_GameCore::instance.gameMode_2 == (Game::GameMode2)1) {
                    int playerID = DAT_GameSynchronyState::instance.currentPlayerSlotID;
                    int lordID = DAT_GameState::instance.playerDataArray[playerID].lordID;
                    if (lordID != 0) {
                        int lordUID = DAT_GameState::instance.playerDataArray[playerID].lordUID;
                        DAT_GameState::instance.playerDataArray[playerID].lordID = 0;
                        DAT_GameState::instance.playerDataArray[playerID].lordUID = 0;
                        if (lordUID == DAT_UnitsState::instance.units[lordID].uid) {
                            DAT_UnitsState::instance.units[lordID].logicalState = 3;
                        }
                    }
                    DAT_GameState::instance.playerDataArray[playerID].lordKilledByPlayerID = 0;
                }
                break;
            case 188:
                if (DAT_GameCore::instance.currentMenuViewType == (UI::Enums::MenuViewType)17) {
                    if (DAT_MenuModalComposition1::instance.activeModalDialogID == (UI::Enums::MenuModalType)31) {
                        MACRO_CALL_MEMBER(UI::MenuModalComposition_Func::activateModalDialog,
                            DAT_MenuModalComposition1::ptr)((UI::Enums::MenuModalType)-1, FALSE);
                    } else if (DAT_MenuModalComposition1::instance.activeModalDialogID
                        == (UI::Enums::MenuModalType)-1) {
                        MACRO_CALL_MEMBER(UI::MenuModalComposition_Func::activateModalDialog,
                            DAT_MenuModalComposition1::ptr)((UI::Enums::MenuModalType)31, FALSE);
                    }
                }
                break;
            case 192:
            case 222:
                if (DAT_GameCore::instance.currentMenuViewType == (UI::Enums::MenuViewType)1002) {
                    DAT_GameState::instance.mapAndTime.editScenarioExtraOptions ^= 1;
                }
                break;
            case VK_NUMPAD0:
            case VK_NUMPAD1:
            case VK_NUMPAD2:
            case VK_NUMPAD3:
            case VK_NUMPAD4:
            case VK_NUMPAD5:
            case VK_NUMPAD6:
            case VK_NUMPAD7:
            case VK_NUMPAD8:
            case VK_NUMPAD9:
                wParam -= 48;
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
                if (MACRO_CALL_MEMBER(Game::GameCore_Func::getAreWeInAInGameMenu, DAT_GameCore::ptr)() != FALSE) {
                label_BookmarkCamera:
                    if (DAT_ModifierKeyState::instance.ctrl != 0) {
                        int orientationOffset = 8;
                        if (DAT_TileMapState::instance.mapOrientation != 0) {
                            if (DAT_TileMapState::instance.mapOrientation == 6) {
                                orientationOffset = 80408;
                            } else if (DAT_TileMapState::instance.mapOrientation == 4) {
                                orientationOffset = 160808;
                            } else if (DAT_TileMapState::instance.mapOrientation == 2) {
                                orientationOffset = 241208;
                            }
                        }
                        DAT_GameState::instance.mapAndTime.playerKeepTile[wParam - '0']
                            = DAT_ViewportRenderState::instance
                                  .screenPointToTileNumber[DAT_ViewportRenderState::instance.viewportState.viewportX
                                          / 32
                                      + (DAT_ViewportRenderState::instance.viewportState.viewportY / 16
                                            + DAT_ViewportRenderState::instance.viewportState.mbr_0xb0 / 2)
                                          * 401
                                      + DAT_ViewportRenderState::instance.viewportState.mbr_0xac + orientationOffset
                                      - 8];
                    } else if (DAT_GameState::instance.mapAndTime.playerKeepTile[wParam - '0'] >= 0) {
                        MACRO_CALL_MEMBER(
                            Rendering::ViewportRenderState_Func::focusOnTile, DAT_ViewportRenderState::ptr)(
                            DAT_GameState::instance.mapAndTime.playerKeepTile[wParam - '0']);
                    }
                }
                break;
            case VK_F10:
            label_F1_to_F10:
                if (DAT_GameCore::instance.gameMode_2 == (Game::GameMode2)3
                    && MACRO_CALL_MEMBER(Game::GameCore_Func::getAreWeInAInGameMenu, DAT_GameCore::ptr)() != FALSE) {
                    DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[1] = 1;
                    DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[2] = 1;
                    DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[3] = 1;
                    DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[4] = 1;
                    DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[5] = 1;
                    DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[6] = 1;
                    DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[7] = 1;
                    DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[8] = 1;
                    if (DAT_ModifierKeyState::instance.ctrl != 0) {
                        wParam += 10;
                    }
                    DAT_GameSynchronyState::instance.DAT_ChatTauntOrMessage = wParam - 111;
                    MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand, DAT_GameSynchronyState::ptr)(
                        (Commands::GameCommandType)14);
                    if (DAT_GameSynchronyState::instance.currentGameMode == (Game::GameMode)99
                        && DAT_GameSynchronyState::instance.DAT_ChatTauntOrMessage != 6) {
                        MACRO_CALL_MEMBER(AI::AICState_Func::setTriggerForAITauntResponse, DAT_AICState::ptr)();
                    }
                } else if (wParam <= 112 && DAT_GameCore::instance.gameMode_2 == (Game::GameMode2)2
                    && DAT_MapPropertiesState::instance.SEC_U3_MapType2_1 == (Map::MapType2)3
                    && MACRO_CALL_MEMBER(Game::GameCore_Func::getAreWeInAInGameMenu, DAT_GameCore::ptr)() != FALSE
                    && DAT_ModifierKeyState::instance.shift == 0) {
                    MACRO_CALL_MEMBER(Map::MapPropertiesState_Func::openEventTriggerMenu, DAT_MapPropertiesState::ptr)(
                        wParam - 112);
                    break;
                }
                wParam = 32;
                break;
            case VK_F11:
            case VK_F12:
                wParam = 32;
                break;
            }
            break;
        case WM_CHAR:
            MACRO_CALL_MEMBER(Text::UserTextHandler_Func::handleCharacterCode, DAT_UserTextHandlerState::ptr)(
                (byte)wParam);
            MACRO_CALL_MEMBER(
                Text::UserTextHandler_Func::handleCharacterIntoInputBuffer, DAT_UserTextHandlerState::ptr)(wParam);
            break;
        case WM_KEYUP:
            switch (wParam) {
            case VK_RIGHT:
                DAT_ScrollingHandler::instance.rightKeyDown_0x18 = FALSE;
                break;
            case VK_LEFT:
                DAT_ScrollingHandler::instance.leftKeyDown_0x1c = FALSE;
                break;
            case VK_UP:
                DAT_ScrollingHandler::instance.upKeyDown_0x24 = FALSE;
                break;
            case VK_DOWN:
                DAT_ModifierKeyState::instance.downArrow = 0;
                DAT_ScrollingHandler::instance.downKeyDown_0x20 = FALSE;
                break;
            }
            break;
        case WM_SYSKEYUP:
            break;
        case WM_MOUSEMOVE:
            MACRO_CALL_MEMBER(Input::MouseState_Func::updateMousePositionAndClicks, DAT_MouseState::ptr)(
                (short)lParam, (short)((DWORD)lParam >> 16), (Input::Mouse::MouseClickInteraction)0);
            break;
        case WM_RBUTTONUP:
            MACRO_CALL_MEMBER(Input::MouseState_Func::updateMousePositionAndClicks, DAT_MouseState::ptr)(
                (short)lParam, (short)((DWORD)lParam >> 16), (Input::Mouse::MouseClickInteraction)4);
            break;
        case WM_RBUTTONDOWN:
            MACRO_CALL_MEMBER(Input::MouseState_Func::updateMousePositionAndClicks, DAT_MouseState::ptr)(
                (short)lParam, (short)((DWORD)lParam >> 16), (Input::Mouse::MouseClickInteraction)3);
            break;
        case WM_LBUTTONUP:
            MACRO_CALL_MEMBER(Input::MouseState_Func::updateMousePositionAndClicks, DAT_MouseState::ptr)(
                (short)lParam, (short)((DWORD)lParam >> 16), (Input::Mouse::MouseClickInteraction)2);
            break;
        case WM_LBUTTONDOWN:
            MACRO_CALL_MEMBER(Input::MouseState_Func::updateMousePositionAndClicks, DAT_MouseState::ptr)(
                (short)lParam, (short)((DWORD)lParam >> 16), (Input::Mouse::MouseClickInteraction)1);
            break;
        case WM_MBUTTONUP:
            MACRO_CALL_MEMBER(Input::MouseState_Func::updateMousePositionAndClicks, DAT_MouseState::ptr)(
                (short)lParam, (short)((DWORD)lParam >> 16), (Input::Mouse::MouseClickInteraction)6);
            break;
        case WM_MBUTTONDOWN:
            MACRO_CALL_MEMBER(Input::MouseState_Func::updateMousePositionAndClicks, DAT_MouseState::ptr)(
                (short)lParam, (short)((DWORD)lParam >> 16), (Input::Mouse::MouseClickInteraction)5);
            break;
        case 522:
            MACRO_CALL_MEMBER(Input::MouseState_Func::updateMouseWheelStatus, DAT_MouseState::ptr)(
                (short)(wParam >> 16));
            break;
        }
    label_DefWindowProc:
        return DefWindowProcA(windowHandle, message, wParam, lParam);
    }

} // namespace Global
} // namespace OpenSHC
