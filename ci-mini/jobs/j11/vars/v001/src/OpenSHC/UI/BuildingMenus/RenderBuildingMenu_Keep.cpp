#include "../BuildingMenus.func.hpp"

#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Synchrony/Commands.func.hpp"
#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Helpers.func.hpp"
#include "OpenSHC/UI/Rendering.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/Audio/SFX/SpeechEffectID.hpp"
#include "OpenSHC/DE/SHCDE/eGM.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Rendering/Colors/BGR24.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GMImageHeaders.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MenuHandlerState.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/GMFirstPictureIndex.hpp"

namespace OpenSHC {
namespace UI {

    using OpenSHC::Audio::SFX::SpeechEffectID;
    using OpenSHC::DE::SHCDE::eGM;
    using OpenSHC::DE::SHCDE::eTextSections;
    using OpenSHC::Rendering::Colors::BGR24;
    using OpenSHC::Rendering::Enums::RenderTarget;
    using OpenSHC::Text::TextAlignment;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    // The argument temporaries mirror the original's evaluation order: written inline in the calls,
    // the positions are loaded after the text lookup and the match drops (measured).
    // FUNCTION: STRONGHOLDCRUSADER 0x0043A9F0
    void BuildingMenus::RenderBuildingMenu_Keep()
    {
        char* _textAddress;
        int _displayNumber;
        int rateOrPosition;
        int playerIDOrWidth;
        TextAlignment _alignment;
        int _blendStrength;
        BGR24 _color;
        int _fontSize;
        BOOLEnum _keepOffsetX;
        int _xPos;
        playerIDOrWidth = DAT_GameSynchronyState::instance.currentPlayerSlotID;
        _displayNumber = DAT_BuildingsState::instance.menuSelectedBuildingID;
        int gold = DAT_GameState::instance.playerDataArray[playerIDOrWidth].currentResources[0xf];
        if (DAT_GameState::instance.playerDataArray[playerIDOrWidth].timeTaxesOrRationsChange != 0) {
            DWORD now = timeGetTime();
            if (2000 < now - DAT_GameState::instance.playerDataArray[playerIDOrWidth].timeTaxesOrRationsChange) {
                rateOrPosition = DAT_GameState::instance.playerDataArray[playerIDOrWidth].taxesSliderUI;
                if (rateOrPosition < 3) {
                    MACRO_CALL(OpenSHC::UI::Helpers_Func::SetTaxesSetting_unknown)(2);
                } else if (rateOrPosition < 5) {
                    MACRO_CALL(OpenSHC::UI::Helpers_Func::SetTaxesSetting_unknown)(1);
                } else {
                    MACRO_CALL(OpenSHC::UI::Helpers_Func::SetTaxesSetting_unknown)(3);
                }
            }
            now = timeGetTime();
            if (0x9c4 < now - DAT_GameState::instance.playerDataArray[playerIDOrWidth].timeTaxesOrRationsChange) {
                rateOrPosition = DAT_GameState::instance.playerDataArray[playerIDOrWidth].taxesSliderUI;
                DAT_GameState::instance.playerDataArray[playerIDOrWidth].timeTaxesOrRationsChange = 0;
                if (8 < rateOrPosition) {
                    rateOrPosition = rateOrPosition - 1;
                }
                if (6 < rateOrPosition) {
                    rateOrPosition = rateOrPosition - 1;
                }
                if (4 < rateOrPosition) {
                    rateOrPosition = rateOrPosition - 1;
                }
                if (0 < rateOrPosition) {
                    rateOrPosition = rateOrPosition - 1;
                }
                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSpeechSFX, DAT_SFXState::ptr)(
                    (OpenSHC::Audio::SFX::SpeechEffectID)(rateOrPosition + OpenSHC::Audio::SFX::SEID_TAXES_RATE1));
            }
        }
        rateOrPosition = (int)(short)DAT_BuildingsState::instance.buildings[_displayNumber].buildingType;
        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
        if (!(rateOrPosition - 0x47U > 2)) {
            rateOrPosition = (int)(short)DAT_BuildingsState::instance.buildings[_displayNumber].quarryStockpileID;
            if ((rateOrPosition != 0)
                && (DAT_BuildingsState::instance.buildings[rateOrPosition].uid
                    == DAT_BuildingsState::instance.buildings[_displayNumber].uidWhenPlaced)) {
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                    OpenSHC::DE::SHCDE::TEXT_IN_KEEP,
                    (int)((short)DAT_BuildingsState::instance.buildings[rateOrPosition].buildingType * 2 - 0x50),
                    DAT_MenuHandlerState::instance.x + 0x19, DAT_MenuHandlerState::instance.y + 0x1d3,
                    OpenSHC::Text::TTA_LEFT, 0, 0x10, FALSE);
            }
        } else {
            _blendStrength = 0;
            _keepOffsetX = FALSE;
            _fontSize = 0x10;
            _color = 0;
            _alignment = OpenSHC::Text::TTA_LEFT;
            _displayNumber = DAT_MenuHandlerState::instance.y + 0x1d3;
            _xPos = DAT_MenuHandlerState::instance.x + 0x19;
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_IN_KEEP, rateOrPosition * 2 - 0x50),
                _xPos, _displayNumber, _alignment, _color, _fontSize, _keepOffsetX, _blendStrength);
        }
        _displayNumber = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                             .taxesSliderUI;
        _blendStrength = 0;
        _keepOffsetX = FALSE;
        _fontSize = 0x12;
        _color = 0;
        rateOrPosition = DAT_MenuHandlerState::instance.y + 0x237;
        _alignment = OpenSHC::Text::TTA_LEFT;
        _xPos = DAT_MenuHandlerState::instance.x + 0xf0;
        if (_displayNumber >= 3) {
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_IN_KEEP, _displayNumber + 7),
                _xPos, rateOrPosition, _alignment, _color, _fontSize, _keepOffsetX, _blendStrength);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                DAT_GameState::instance.playerDataArray[playerIDOrWidth].currentPopulation,
                DAT_MenuHandlerState::instance.x + 300, DAT_MenuHandlerState::instance.y + 0x1e3,
                OpenSHC::Text::TTA_LEFT, 0, 0x12, FALSE, 0);
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                DAT_TextureRenderCoreObject::ptr)(OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS2, 0x7f,
                DAT_TextManagerObject::instance.currentXOffset_0x0 + 0x136 + DAT_MenuHandlerState::instance.x,
                DAT_MenuHandlerState::instance.y + 0x1db);
            DAT_TextManagerObject::instance.currentXOffset_0x0 = DAT_TextManagerObject::instance.currentXOffset_0x0
                + DAT_GMImageHeaders::instance.imh[GMFirstPictureIndex::instance[0x2e] + 0x7e].width;
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(" = ",
                DAT_MenuHandlerState::instance.x + 0x140, DAT_MenuHandlerState::instance.y + 0x1e3,
                OpenSHC::Text::TTA_LEFT, 0, 0x12, TRUE, 0);
            _xPos = DAT_MenuHandlerState::instance.y + 0x1e3;
            rateOrPosition = DAT_MenuHandlerState::instance.x + 0x14a;
            _displayNumber = MACRO_CALL_MEMBER(
                OpenSHC::Game::GameStateStructures_Func::getNumberToDisplayPlayerTaxIncome, DAT_GameState::ptr)(
                playerIDOrWidth, DAT_GameState::instance.playerDataArray[playerIDOrWidth].taxesSliderUI,
                DAT_GameState::instance.playerDataArray[playerIDOrWidth].currentPopulation);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                _displayNumber, rateOrPosition, _xPos, OpenSHC::Text::TTA_LEFT, 0, 0x12, TRUE, 0);
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                DAT_TextureRenderCoreObject::ptr)(OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS2, 0x7c,
                DAT_TextManagerObject::instance.currentXOffset_0x0 + 0x154 + DAT_MenuHandlerState::instance.x,
                DAT_MenuHandlerState::instance.y + 0x1e1);
        } else {
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_IN_KEEP, _displayNumber + 7),
                _xPos, rateOrPosition, _alignment, _color, _fontSize, _keepOffsetX, _blendStrength);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                DAT_GameState::instance.playerDataArray[playerIDOrWidth].currentPopulation,
                DAT_MenuHandlerState::instance.x + 300, DAT_MenuHandlerState::instance.y + 0x1e3,
                OpenSHC::Text::TTA_LEFT, 0, 0x12, FALSE, 0);
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                DAT_TextureRenderCoreObject::ptr)(OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS2, 0x7f,
                DAT_TextManagerObject::instance.currentXOffset_0x0 + 0x136 + DAT_MenuHandlerState::instance.x,
                DAT_MenuHandlerState::instance.y + 0x1db);
            DAT_TextManagerObject::instance.currentXOffset_0x0 = DAT_TextManagerObject::instance.currentXOffset_0x0
                + DAT_GMImageHeaders::instance.imh[GMFirstPictureIndex::instance[0x2e] + 0x7e].width;
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(" = ",
                DAT_MenuHandlerState::instance.x + 0x140, DAT_MenuHandlerState::instance.y + 0x1e3,
                OpenSHC::Text::TTA_LEFT, 0, 0x12, TRUE, 0);
            _xPos = DAT_MenuHandlerState::instance.y + 0x1e3;
            rateOrPosition = DAT_MenuHandlerState::instance.x + 0x14a;
            _displayNumber = MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::getNumberToDisplayBribeIncome,
                DAT_GameState::ptr)(playerIDOrWidth,
                DAT_GameState::instance.playerDataArray[playerIDOrWidth].taxesSliderUI,
                DAT_GameState::instance.playerDataArray[playerIDOrWidth].currentPopulation);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                -_displayNumber, rateOrPosition, _xPos, OpenSHC::Text::TTA_LEFT, 0, 0x12, TRUE, 0);
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                DAT_TextureRenderCoreObject::ptr)(OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS2, 0x7c,
                DAT_TextManagerObject::instance.currentXOffset_0x0 + 0x154 + DAT_MenuHandlerState::instance.x,
                DAT_MenuHandlerState::instance.y + 0x1e1);
        }
        playerIDOrWidth = 0x12;
        _displayNumber = 0;
        playerIDOrWidth
            = MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::computeTextWidth, DAT_TextManagerObject::ptr)(
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_IN_KEEP,
                    DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                            .taxesSliderUI
                        + 7),
                playerIDOrWidth);
        if (0xbe < playerIDOrWidth) {
            _displayNumber = playerIDOrWidth - 0xbe;
        }
        if (DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                .currentPopulation
            == 0) {
            rateOrPosition = 0;
        } else {
            playerIDOrWidth
                = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                      .taxesSliderUI;
            if (playerIDOrWidth >= 3 || gold > 0) {
                if (playerIDOrWidth == 0) {
                    rateOrPosition = 0xaf;
                } else if (playerIDOrWidth == 1) {
                    rateOrPosition = 0x7d;
                } else if (playerIDOrWidth == 2) {
                    rateOrPosition = 0x4b;
                } else if (playerIDOrWidth == 3) {
                    rateOrPosition = 0x19;
                } else if (playerIDOrWidth == 4) {
                    rateOrPosition = -0x32;
                } else if (playerIDOrWidth == 5) {
                    rateOrPosition = -100;
                } else if (playerIDOrWidth == 6) {
                    rateOrPosition = -0x96;
                } else if (playerIDOrWidth == 7) {
                    rateOrPosition = -200;
                } else if (playerIDOrWidth == 8) {
                    rateOrPosition = -300;
                } else if (playerIDOrWidth == 9) {
                    rateOrPosition = -400;
                } else if (playerIDOrWidth == 10) {
                    rateOrPosition = -500;
                } else if (playerIDOrWidth == 11) {
                    rateOrPosition = -600;
                } else {
                    rateOrPosition = gold;
                }
            } else {
                rateOrPosition = 0x19;
            }
        }
        MACRO_CALL(OpenSHC::UI::Rendering_Func::TransformAndRenderPercentage)(
            DAT_MenuHandlerState::instance.x + 0x1cc + _displayNumber, DAT_MenuHandlerState::instance.y + 0x237,
            rateOrPosition, FALSE);
        MACRO_CALL(OpenSHC::Synchrony::Commands_Func::QueueChangeTaxes)();
        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
    }

}
}
