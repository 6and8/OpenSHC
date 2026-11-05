#include "../BuildingMenus.func.hpp"

#include "OpenSHC/Game/GameCore.func.hpp"
#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Input/MouseState.func.hpp"
#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eGM.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Game/Player/Enums/BuildingEntryInfoEnum.hpp"
#include "OpenSHC/Game/Resources/ResourceType.hpp"
#include "OpenSHC/Game/Resources/ResourceTypeInt.hpp"
#include "OpenSHC/IO/Graphics/GmID.hpp"
#include "OpenSHC/Rendering/Colors/BGR24.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_ArmoryIconsPositionNudges.hpp"
#include "OpenSHC/Globals/DAT_ArmoryMenuResourceIcons.hpp"
#include "OpenSHC/Globals/DAT_ArmoryMenuResourceTypes.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GMImageHeaders.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MenuHandlerState.hpp"
#include "OpenSHC/Globals/DAT_MouseState.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/GMFirstPictureIndex.hpp"

namespace OpenSHC {
namespace UI {

    using OpenSHC::DE::SHCDE::eGM;
    using OpenSHC::DE::SHCDE::eTextSections;
    using OpenSHC::Game::Resources::ResourceType;
    using OpenSHC::Game::Resources::ResourceTypeInt;
    using OpenSHC::IO::Graphics::GmID;
    using OpenSHC::Rendering::Colors::BGR24;
    using OpenSHC::Rendering::Enums::RenderTarget;
    using OpenSHC::Text::TextAlignment;
    using OpenSHC::UI::Enums::MenuViewType;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    using OpenSHC::Game::Player::Enums::BEIE_MARKETPLACE;

    // FUNCTION: STRONGHOLDCRUSADER 0x0043C840
    void BuildingMenus::RenderBuildingMenu_Armory()
    {
        int x = DAT_MenuHandlerState::instance.x + 0x1e;
        int iconsY = DAT_MenuHandlerState::instance.y + 0x1fb;
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_IN_ARMOURY, 0),
            DAT_MenuHandlerState::instance.x + 0x19, DAT_MenuHandlerState::instance.y + 0x1d3, OpenSHC::Text::TTA_LEFT,
            0, 0x10, FALSE, 0);
        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
        for (int i = 0; i < 8; ++i) {
            int amount = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                             .currentResources[DAT_ArmoryMenuResourceTypes::instance[i]];
            if (amount < 1) {
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithBlending,
                    DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_2,
                    DAT_ArmoryMenuResourceIcons::instance[i], DAT_ArmoryIconsPositionNudges::instance[i].x + x,
                    DAT_ArmoryIconsPositionNudges::instance[i].y + iconsY, 0x10);
            } else {
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                    DAT_TextureRenderCoreObject::ptr)(OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS2,
                    DAT_ArmoryMenuResourceIcons::instance[i], DAT_ArmoryIconsPositionNudges::instance[i].x + x,
                    DAT_ArmoryIconsPositionNudges::instance[i].y + iconsY);
            }
            if (DAT_MouseState::instance.leftClickStart != 0) {
                int image = DAT_ArmoryMenuResourceIcons::instance[i] + GMFirstPictureIndex::instance[0x2e] - 1;
                BOOLEnum inside = MACRO_CALL_MEMBER(OpenSHC::Input::MouseState_Func::isMouseInsideBox,
                    DAT_MouseState::ptr)(DAT_ArmoryIconsPositionNudges::instance[i].x + x,
                    DAT_ArmoryIconsPositionNudges::instance[i].y + iconsY,
                    DAT_GMImageHeaders::instance.imh[image].width, DAT_GMImageHeaders::instance.imh[image].height);
                if (FALSE != inside
                    && DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                            .buildingEntryInfos[BEIE_MARKETPLACE]
                            .id
                        != 0
                    && MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::isResourceTypeTradeable,
                           DAT_GameState::ptr)((ResourceType)DAT_ArmoryMenuResourceTypes::instance[i])
                        != FALSE) {
                    DAT_BuildingsState::instance.newSelectedBuildingID
                        = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                              .buildingEntryInfos[BEIE_MARKETPLACE]
                              .id;
                    DAT_GameCore::instance.buildingandstatusmenuMenuTabToSwitchTo = 0x39;
                    MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                        OpenSHC::UI::Enums::MVT_BUILDING_AND_STATUS_MENU, 0);
                    DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                        .marketSelectedResourceType = (ResourceTypeInt)DAT_ArmoryMenuResourceTypes::instance[i];
                }
            }
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                amount, x + 0xc, DAT_MenuHandlerState::instance.y + 0x22f, OpenSHC::Text::TTA_LEFT, 0, 0x11, FALSE, 0);
            x += 0x3c;
        }
        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
    }

}
}
