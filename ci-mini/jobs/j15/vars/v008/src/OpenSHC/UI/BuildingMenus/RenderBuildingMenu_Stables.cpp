#include "../BuildingMenus.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Rendering/Colors/BGR24.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_MenuHandlerState.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"

namespace OpenSHC {
namespace UI {

    using OpenSHC::DE::SHCDE::eTextSections;
    using OpenSHC::Rendering::Colors::BGR24;
    using OpenSHC::Text::TextAlignment;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x0043D520
    void BuildingMenus::RenderBuildingMenu_Stables()
    {
        int id = DAT_BuildingsState::instance.menuSelectedBuildingID;
        // "Stables"
        int titleY = DAT_MenuHandlerState::instance.y + 0x1d3;
        int titleX = DAT_MenuHandlerState::instance.x + 0x19;
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_IN_STABLES, 0),
            titleX, titleY, OpenSHC::Text::TTA_LEFT, 0, 0x10, FALSE, 0);
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            DAT_BuildingsState::instance.buildings[id].numberOfAnimals
                - DAT_BuildingsState::instance.buildings[id].randomOutpostField,
            DAT_MenuHandlerState::instance.x + 0xaf, DAT_MenuHandlerState::instance.y + 0x205, OpenSHC::Text::TTA_LEFT,
            0, 0x12, FALSE, 0);
        // "Horse Available" / "Horses Available"
        int x = DAT_MenuHandlerState::instance.x;
        if (DAT_BuildingsState::instance.buildings[id].numberOfAnimals
                - DAT_BuildingsState::instance.buildings[id].randomOutpostField
            != 1) {
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_IN_STABLES, 1),
                x + 0xb4, DAT_MenuHandlerState::instance.y + 0x205, OpenSHC::Text::TTA_LEFT, 0, 0x12, TRUE, 0);
        } else {
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_IN_STABLES, 3),
                x + 0xb4, DAT_MenuHandlerState::instance.y + 0x205, OpenSHC::Text::TTA_LEFT, 0, 0x12, TRUE, 0);
        }
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            DAT_BuildingsState::instance.buildings[id].randomOutpostField, DAT_MenuHandlerState::instance.x + 0xaf,
            DAT_MenuHandlerState::instance.y + 0x219, OpenSHC::Text::TTA_LEFT, 0, 0x12, FALSE, 0);
        // "Horse In Use" / "Horses In Use"
        int y2 = DAT_MenuHandlerState::instance.y;
        int x2 = DAT_MenuHandlerState::instance.x;
        if (DAT_BuildingsState::instance.buildings[id].randomOutpostField == 1) {
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_IN_STABLES, 4),
                x2 + 0xb4, y2 + 0x219, OpenSHC::Text::TTA_LEFT, 0, 0x12, TRUE, 0);
        } else {
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_IN_STABLES, 2),
                x2 + 0xb4, y2 + 0x219, OpenSHC::Text::TTA_LEFT, 0, 0x12, TRUE, 0);
        }
    }

}
}
