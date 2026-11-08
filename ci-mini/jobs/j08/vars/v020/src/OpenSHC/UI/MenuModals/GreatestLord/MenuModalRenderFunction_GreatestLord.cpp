#include "OpenSHC/Audio/SFX.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/MenuModals/GreatestLord.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eGM.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/IO/Graphics/GmID.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"

#include "OpenSHC/Globals/DAT_BlendingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_GreatestLordDefinedData.hpp"
#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"
#include "OpenSHC/Globals/DAT_RenderingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuModals {
        namespace GreatestLord {

            struct GreatestLordRow {
                int player;
                int primary;
                int secondary;
            };

            // FUNCTION: STRONGHOLDCRUSADER 0x004AE0F0
            void MenuModalRenderFunction_GreatestLord(int x, int y, int width, int height)
            {
                int nameX = x + 58;
                int order[10] = { 0 };
                int lordDead[10] = { 0 };
                GreatestLordRow rows[10];
                int frameHeight = height - 96;
                int frameWidth = width - 48;
                for (int row = 0; row < frameHeight; row += 24) {
                    int rowTile;
                    if (row == 0) {
                        rowTile = 1;
                    } else {
                        rowTile = row != frameHeight - 24 ? 7 : 13;
                    }
                    for (int column = 0; column < frameWidth; column += 24) {
                        int tile = rowTile;
                        if (column != 0) {
                            if (column == frameWidth - 24) {
                                tile = rowTile + 2;
                            } else {
                                if (rowTile == 7) {
                                    continue;
                                }
                                tile = rowTile + 1;
                            }
                        }
                        MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::renderGMWithAlphaMask,
                            DAT_TextureRenderCoreObject::ptr)(IO::Graphics::GID_INTERFACE_ICONS_3, tile, column + x + 24,
                            row + y + 24, IO::Graphics::GID_INTERFACE_ICONS_3, tile + 3, 0);
                    }
                }
                MACRO_CALL_MEMBER(UI::Rendering::PencilRenderCore_Func::drawBlendedBlackBox, DAT_PencilRenderCore::ptr)(
                    x + 48, y + 48, frameWidth + x - 1, frameHeight + y - 1, 20);
                for (int i = 0; i < 10; ++i) {
                    rows[i].player = 0;
                }
                int count = 0;
                if (DAT_GreatestLordDefinedData::instance.tableSortBy == 1) {
                    for (int player = 1; player < 9; ++player) {
                        if (DAT_GameSynchronyState::instance.finalResults.active[player] == 0) {
                            continue;
                        }
                        rows[count].player = player;
                        if (MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::getAliveLordForPlayer, DAT_UnitsState::ptr)(
                                player)
                                == 0
                            && (int)DAT_GameCore::instance.mapTimeInTicks > (int)(DAT_GameCore::instance.section1127 + 200)) {
                            int* lordDeadPtr = &lordDead[player];
                            *lordDeadPtr = 1;
                            rows[count].primary = 0;
                            rows[count].secondary = 0;
                        } else {
                            rows[count].primary = DAT_GameState::instance.playerDataArray[player].currentResources[15];
                            if (rows[count].primary < 0) {
                                rows[count].primary = 0;
                            }
                            rows[count].secondary = DAT_GameState::instance.playerDataArray[player].armySize;
                        }
                        count++;
                    }
                }
                if (DAT_GreatestLordDefinedData::instance.tableSortBy == 0) {
                    for (int player = 1; player < 9; ++player) {
                        if (DAT_GameSynchronyState::instance.finalResults.active[player] == 0) {
                            continue;
                        }
                        rows[count].player = player;
                        if (MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::getAliveLordForPlayer, DAT_UnitsState::ptr)(
                                player)
                                == 0
                            && (int)DAT_GameCore::instance.mapTimeInTicks > (int)(DAT_GameCore::instance.section1127 + 200)) {
                            lordDead[player] = 1;
                            rows[count].primary = 0;
                            rows[count].secondary = 0;
                        } else {
                            rows[count].primary = DAT_GameState::instance.playerDataArray[player].armySize;
                            rows[count].secondary = DAT_GameState::instance.playerDataArray[player].currentResources[15];
                            if (rows[count].secondary < 0) {
                                rows[count].secondary = 0;
                            }
                        }
                        count++;
                    }
                }
                if (DAT_GreatestLordDefinedData::instance.tableSortBy == -1) {
                    for (int player = 1; player < 9; ++player) {
                        if (DAT_GameSynchronyState::instance.finalResults.active[player] == 0) {
                            continue;
                        }
                        rows[count].player = player;
                        if (MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::getAliveLordForPlayer, DAT_UnitsState::ptr)(
                                player)
                                == 0
                            && (int)DAT_GameCore::instance.mapTimeInTicks > (int)(DAT_GameCore::instance.section1127 + 200)) {
                            lordDead[player] = 1;
                            rows[count].primary = 0;
                        } else {
                            rows[count].primary = MACRO_CALL(Audio::SFX_Func::ComputePlayerPoints1)(player);
                        }
                        rows[count].secondary = 0;
                        count++;
                    }
                }
                // selection sort by primary, then secondary, both descending
                for (int rank = 0; rank < count; ++rank) {
                    int best = -1;
                    int bestPrimary;
                    int bestSecondary;
                    for (int i = 0; i < count; ++i) {
                        if (rows[i].player == 0) {
                            continue;
                        }
                        if (best == -1 || rows[i].primary > bestPrimary
                            || (rows[i].primary == bestPrimary && rows[i].secondary > bestSecondary)) {
                            bestSecondary = rows[i].secondary;
                            bestPrimary = rows[i].primary;
                            best = i;
                        }
                    }
                    if (best < 0) {
                        break;
                    }
                    order[rank + 1] = rows[best].player;
                    rows[best].player = 0;
                }
                int lineY = y + 126;
                for (int line = 1; line < 9; ++line) {
                    if (line > 1) {
                        lineY += 24;
                    }
                    int player = order[line];
                    if (player < 1) {
                        break;
                    }
                    int dead = lordDead[player];
                    int nameOffset = 0;
                    if (dead != 0) {
                        MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::renderGM,
                            DAT_TextureRenderCoreObject::ptr)(DE::SHCDE::GM_INTERFACE_ICONS2, 665, nameX - 20, lineY + 2);
                        nameOffset = 6;
                    } else if (DAT_GameState::instance.mapAndTime.playerGroupArray[player] > 0) {
                        MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::renderGM,
                            DAT_TextureRenderCoreObject::ptr)(DE::SHCDE::GM_INTERFACE_ICONS2,
                            DAT_GameState::instance.mapAndTime.playerGroupArray[player] * 2 + 492, nameX - 20, lineY - 2);
                    }
                    DAT_TextManagerObject::instance.field_0x30 = 1;
                    MACRO_CALL_MEMBER(Text::TextManager_Func::renderMultilineText6Unk, DAT_TextManagerObject::ptr)(
                        DAT_GameSynchronyState::instance.finalResults.names[player], nameX, lineY + nameOffset, 260,
                        DAT_RenderingDefinedData::instance
                            .ColorArray[DAT_BlendingDefinedData::instance.PlayerSlotUnitColor[player]],
                        0, 18, 0);
                    if (dead == 0) {
                        int gold = DAT_GameState::instance.playerDataArray[player].currentResources[15];
                        if (gold < 0) {
                            gold = 0;
                        }
                        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                            gold, x + 365, lineY, Text::TTA_LEFT, 0xccfaff, 18, FALSE, 0);
                        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                            DAT_GameState::instance.playerDataArray[player].armySize, x + 495, lineY, Text::TTA_LEFT,
                            0xccfaff, 18, FALSE, 0);
                    }
                }
                if (DAT_GreatestLordDefinedData::instance.tableSortBy == 1) {
                    MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                        MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                            DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_MP_RANK, 2),
                        nameX, y + 360, Text::TTA_LEFT, 0xccfaff, 17, FALSE, 0);
                    MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                        DE::SHCDE::GM_INTERFACE_ICONS2, 730,
                        DAT_TextManagerObject::instance.currentXOffset_0x0 + nameX + 10, y + 355);
                }
                if (DAT_GreatestLordDefinedData::instance.tableSortBy == 0) {
                    MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                        MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                            DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_MP_RANK, 3),
                        nameX, y + 360, Text::TTA_LEFT, 0xccfaff, 17, FALSE, 0);
                    MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                        DE::SHCDE::GM_INTERFACE_ICONS2, 664,
                        DAT_TextManagerObject::instance.currentXOffset_0x0 + nameX + 10, y + 350);
                }
                if (DAT_GreatestLordDefinedData::instance.tableSortBy == -1) {
                    MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                        MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                            DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_MP_RANK, 1),
                        nameX, y + 360, Text::TTA_LEFT, 0xccfaff, 17, FALSE, 0);
                }
            }

        }
    }
}
}
