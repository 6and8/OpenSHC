#include "../BuildingMenus.func.hpp"

#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"
#include "OpenSHC/Map/Buildings/BuildingTypeShort.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"
#include "OpenSHC/Rendering/Colors/BGR24.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_00b98428.hpp"
#include "OpenSHC/Globals/DAT_00b9842c.hpp"
#include "OpenSHC/Globals/DAT_00b98430.hpp"
#include "OpenSHC/Globals/DAT_00b9843c.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_CurrentlyRenderedSpriteID.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_HusbandID.hpp"
#include "OpenSHC/Globals/DAT_HusbandUnitType.hpp"
#include "OpenSHC/Globals/DAT_MenuHandlerState.hpp"
#include "OpenSHC/Globals/DAT_RenderedUnitOwner.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_WifeID.hpp"
#include "OpenSHC/Globals/DAT_WifeUnitType.hpp"
#include "OpenSHC/Globals/INT_0061824c.hpp"

namespace OpenSHC {
namespace UI {

    using OpenSHC::DE::SHCDE::eTextSections;
    using OpenSHC::Map::Buildings::BuildingType;
    using OpenSHC::Map::Buildings::BuildingTypeShort;
    using OpenSHC::Map::Units::UnitType;
    using OpenSHC::Rendering::Colors::BGR24;
    using OpenSHC::Rendering::Enums::RenderTarget;
    using OpenSHC::Text::TextAlignment;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    // The argument temporaries mirror the original's evaluation order: written inline in the calls,
    // the positions are loaded after the text lookup and the match drops (measured).
    // FUNCTION: STRONGHOLDCRUSADER 0x0043C1E0
    void BuildingMenus::RenderBuildingMenu_ChapelAndChurch()
    {
        BuildingTypeShort selectedType;
        int idOrPosition;
        int xOrYOrFontSize;
        TextAlignment alignment;
        BGR24 color2;
        uint color;
        int fontSizeOrXOrBlendStrength;
        BOOLEnum keepOffsetX;
        int blendStrengthOrX;
        int blendStrength;
        int blendStrengthOrFontSizeOrY;
        idOrPosition = DAT_BuildingsState::instance.menuSelectedBuildingID;
        selectedType
            = DAT_BuildingsState::instance.buildings[DAT_BuildingsState::instance.menuSelectedBuildingID].buildingType;
        if (selectedType == OpenSHC::Map::Buildings::BT_CHAPEL) {
            int titleY = DAT_MenuHandlerState::instance.y + 0x1d3;
            int titleX = DAT_MenuHandlerState::instance.x + 0x19;
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_IN_CHURCH, 0),
                titleX, titleY, OpenSHC::Text::TTA_LEFT, 0, 0x10, FALSE, 0);
        } else if (selectedType == OpenSHC::Map::Buildings::BT_CHURCH) {
            int titleY = DAT_MenuHandlerState::instance.y + 0x1d3;
            int titleX = DAT_MenuHandlerState::instance.x + 0x19;
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_IN_CHURCH, 3),
                titleX, titleY, OpenSHC::Text::TTA_LEFT, 0, 0x10, FALSE, 0);
        } else if (selectedType == OpenSHC::Map::Buildings::BT_CATHEDRAL) {
            int titleY = DAT_MenuHandlerState::instance.y + 0x1d3;
            int titleX = DAT_MenuHandlerState::instance.x + 0x19;
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_IN_CHURCH, 4),
                titleX, titleY, OpenSHC::Text::TTA_LEFT, 0, 0x10, FALSE, 0);
        }
        if (DAT_BuildingsState::instance.buildings[idOrPosition].currentEmployeeCount == 0) {
            blendStrengthOrFontSizeOrY = 0;
            keepOffsetX = FALSE;
            fontSizeOrXOrBlendStrength = 0x12;
            color2 = 0;
            alignment = OpenSHC::Text::TTA_LEFT;
            idOrPosition = DAT_MenuHandlerState::instance.y + 0x205;
            xOrYOrFontSize = DAT_MenuHandlerState::instance.x + 0xaf;
            // "No Wedding this month"
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_MARRIAGE, 0x22),
                xOrYOrFontSize, idOrPosition, alignment, color2, fontSizeOrXOrBlendStrength, keepOffsetX,
                blendStrengthOrFontSizeOrY);
            return;
        }
        if (DAT_GameState::instance.mapAndTime.month != INT_0061824c::instance) {
            INT_0061824c::instance = DAT_GameState::instance.mapAndTime.month;
            DAT_00b9843c::instance = MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::chooseHusbandAndWife,
                DAT_UnitsState::ptr)((int*)DAT_HusbandID::ptr, (int*)DAT_WifeID::ptr);
            if (DAT_00b9843c::instance == 0) {
                /* no wedding this month: render the notice and stop */
                blendStrengthOrFontSizeOrY = 0;
                keepOffsetX = FALSE;
                fontSizeOrXOrBlendStrength = 0x12;
                alignment = OpenSHC::Text::TTA_LEFT;
                color2 = 0;
                idOrPosition = DAT_MenuHandlerState::instance.y + 0x205;
                xOrYOrFontSize = DAT_MenuHandlerState::instance.x + 0xaf;
                // "No Wedding this month"
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_MARRIAGE, 0x22),
                    xOrYOrFontSize, idOrPosition, alignment, color2, fontSizeOrXOrBlendStrength, keepOffsetX,
                    blendStrengthOrFontSizeOrY);
                return;
            }
            int husband = DAT_HusbandID::instance;
            int wife = DAT_WifeID::instance;
            DAT_HusbandUnitType::instance = (UnitTypeInt)(short)DAT_UnitsState::instance.units[husband].unitType;
            DAT_WifeUnitType::instance = (UnitTypeInt)(short)DAT_UnitsState::instance.units[wife].unitType;
            switch (DAT_WifeUnitType::instance) {
            case OpenSHC::Map::Units::UT_BREWER:
                DAT_00b98428::instance = DAT_00b98428::instance + 1;
                if ((int)DAT_00b98428::instance > 9) {
                    DAT_00b98428::instance = 0;
                }
                break;
            case OpenSHC::Map::Units::UT_TANNER:
                DAT_00b9842c::instance = DAT_00b9842c::instance + 1;
                if ((int)DAT_00b9842c::instance > 9) {
                    DAT_00b9842c::instance = 0;
                }
                break;
            default:
                DAT_00b98430::instance = DAT_00b98430::instance + 1;
                if ((int)DAT_00b98430::instance > 9) {
                    DAT_00b98430::instance = 0;
                }
            }
        }
        if (DAT_00b9843c::instance != 0) {
            if ((int)(short)DAT_UnitsState::instance.units[DAT_HusbandID::instance].unitType
                != DAT_HusbandUnitType::instance) {
                DAT_00b9843c::instance = 0;
            }
            if ((int)(short)DAT_UnitsState::instance.units[DAT_WifeID::instance].unitType
                != DAT_WifeUnitType::instance) {
                DAT_00b9843c::instance = 0;
            } else {
                if (DAT_00b9843c::instance != 0) {
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                        DAT_TextureRenderCoreObject::ptr)(
                        1, DAT_MenuHandlerState::instance.x + 0x173, DAT_MenuHandlerState::instance.y + 0x1e0);
                    xOrYOrFontSize = 0x12;
                    fontSizeOrXOrBlendStrength = 0;
                    color = 0;
                    idOrPosition = 0x15e;
                    switch (DAT_WifeUnitType::instance) {
                    case OpenSHC::Map::Units::UT_BREWER:
                        blendStrengthOrFontSizeOrY = DAT_MenuHandlerState::instance.y + 0x22f;
                        blendStrengthOrX = DAT_MenuHandlerState::instance.x + 0xb4;
                        MACRO_CALL_MEMBER(
                            OpenSHC::Text::TextManager_Func::renderMultilineText5Unk, DAT_TextManagerObject::ptr)(
                            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                                DAT_TextManagerObject::ptr)(
                                OpenSHC::DE::SHCDE::TEXT_MARRIAGE, DAT_00b98428::instance + 1),
                            blendStrengthOrX, blendStrengthOrFontSizeOrY, idOrPosition, color, xOrYOrFontSize,
                            fontSizeOrXOrBlendStrength);
                        break;
                    case OpenSHC::Map::Units::UT_TANNER:
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderMultilineTextUnk,
                            DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_MARRIAGE, DAT_00b9842c::instance + 0xc,
                            DAT_MenuHandlerState::instance.x + 0xb4, DAT_MenuHandlerState::instance.y + 0x22f, 0x15e, 0,
                            0x12, 0);
                        break;
                    default:
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderMultilineTextUnk,
                            DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_MARRIAGE,
                            DAT_00b98430::instance + 0x17, DAT_MenuHandlerState::instance.x + 0xb4,
                            DAT_MenuHandlerState::instance.y + 0x22f, 0x15e, 0, 0x12, 0);
                    }
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                    int husbandSprite = MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::getPeasantGmID,
                        DAT_UnitsState::ptr)(DAT_HusbandID::instance);
                    DAT_RenderedUnitOwner::instance = 0;
                    DAT_CurrentlyRenderedSpriteID::instance = husbandSprite;
                    MACRO_CALL_MEMBER(
                        OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                        (OpenSHC::DE::SHCDE::eGM)DAT_CurrentlyRenderedSpriteID::instance, 3,
                        DAT_MenuHandlerState::instance.x + 0x82, DAT_MenuHandlerState::instance.y + 0x1c4);
                    int wifeSprite = MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::getPeasantGmID,
                        DAT_UnitsState::ptr)(DAT_WifeID::instance);
                    DAT_RenderedUnitOwner::instance = 0;
                    DAT_CurrentlyRenderedSpriteID::instance = wifeSprite;
                    MACRO_CALL_MEMBER(
                        OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                        (OpenSHC::DE::SHCDE::eGM)DAT_CurrentlyRenderedSpriteID::instance, 3,
                        DAT_MenuHandlerState::instance.x + 0x91, DAT_MenuHandlerState::instance.y + 0x1dd);
                    idOrPosition = DAT_HusbandID::instance;
                    byte nameIndex = DAT_UnitsState::instance.units[DAT_HusbandID::instance].firstNameIndex;
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                    if ('\0' < (char)nameIndex) {
                        blendStrengthOrX = 0;
                        keepOffsetX = FALSE;
                        blendStrengthOrFontSizeOrY = 0x12;
                        color2 = 0;
                        alignment = OpenSHC::Text::TTA_LEFT;
                        xOrYOrFontSize = DAT_MenuHandlerState::instance.y + 0x1ec;
                        fontSizeOrXOrBlendStrength = DAT_MenuHandlerState::instance.x + 0xd7;
                        MACRO_CALL_MEMBER(
                            OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                                DAT_TextManagerObject::ptr)(
                                OpenSHC::DE::SHCDE::TEXT_PEASANT_NAMES, (int)((char)nameIndex)),
                            fontSizeOrXOrBlendStrength, xOrYOrFontSize, alignment, color2, blendStrengthOrFontSizeOrY,
                            keepOffsetX, blendStrengthOrX);
                        nameIndex = DAT_UnitsState::instance.units[idOrPosition].rng1_to_70;
                        if (nameIndex != 0) {
                            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                                OpenSHC::DE::SHCDE::TEXT_PEASANT_SURNAMES, (int)((char)nameIndex),
                                DAT_MenuHandlerState::instance.x + 0xdc, DAT_MenuHandlerState::instance.y + 0x1ec,
                                OpenSHC::Text::TTA_LEFT, 0, 0x12, TRUE);
                        }
                    }
                    nameIndex = DAT_UnitsState::instance.units[DAT_WifeID::instance].firstNameIndex;
                    idOrPosition = DAT_WifeID::instance;
                    if ('\0' < (char)nameIndex) {
                        blendStrengthOrX = 0;
                        keepOffsetX = FALSE;
                        blendStrengthOrFontSizeOrY = 0x12;
                        color2 = 0;
                        alignment = OpenSHC::Text::TTA_LEFT;
                        xOrYOrFontSize = DAT_MenuHandlerState::instance.y + 0x205;
                        fontSizeOrXOrBlendStrength = DAT_MenuHandlerState::instance.x + 0xe6;
                        MACRO_CALL_MEMBER(
                            OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                                DAT_TextManagerObject::ptr)(
                                OpenSHC::DE::SHCDE::TEXT_PEASANT_NAMES, (int)((char)nameIndex)),
                            fontSizeOrXOrBlendStrength, xOrYOrFontSize, alignment, color2, blendStrengthOrFontSizeOrY,
                            keepOffsetX, blendStrengthOrX);
                        nameIndex = DAT_UnitsState::instance.units[idOrPosition].rng1_to_70;
                        if (nameIndex != 0) {
                            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                                OpenSHC::DE::SHCDE::TEXT_PEASANT_SURNAMES, (int)((char)nameIndex),
                                DAT_MenuHandlerState::instance.x + 0xeb, DAT_MenuHandlerState::instance.y + 0x205,
                                OpenSHC::Text::TTA_LEFT, 0, 0x12, TRUE);
                        }
                    }
                }
            }
        }
        if (DAT_00b9843c::instance == 0) {
            blendStrengthOrFontSizeOrY = 0;
            keepOffsetX = FALSE;
            fontSizeOrXOrBlendStrength = 0x12;
            color2 = 0;
            alignment = OpenSHC::Text::TTA_LEFT;
            idOrPosition = DAT_MenuHandlerState::instance.y + 0x205;
            xOrYOrFontSize = DAT_MenuHandlerState::instance.x + 0xaf;
            // "No Wedding this month"
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_MARRIAGE, 0x22),
                xOrYOrFontSize, idOrPosition, alignment, color2, fontSizeOrXOrBlendStrength, keepOffsetX,
                blendStrengthOrFontSizeOrY);
        }
    }

}
}
