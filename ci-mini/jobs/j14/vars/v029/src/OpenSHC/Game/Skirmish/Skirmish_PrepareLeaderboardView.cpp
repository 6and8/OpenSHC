#include "OpenSHC/Game/Skirmish.func.hpp"
#include "OpenSHC/Text/TextManager.func.hpp"

#include "OpenSHC/Globals/DAT_00eb9b60.hpp"
#include "OpenSHC/Globals/DAT_00ed3124.hpp"
#include "OpenSHC/Globals/DAT_MissionDefinedData.hpp"
#include "OpenSHC/Globals/DAT_SkMasters2DataArray.hpp"
#include "OpenSHC/Globals/DAT_SkMasters2Data_Count.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/INT_ARRAY_00eb0e48.hpp"
#include "OpenSHC/Globals/INT_ARRAY_00eb96d8.hpp"
#include "OpenSHC/Globals/INT_ARRAY_00ed27f0.hpp"
#include "OpenSHC/Globals/INT_ARRAY_00ed2be0.hpp"

namespace OpenSHC {
namespace Game {
    namespace Skirmish {

        // FUNCTION: STRONGHOLDCRUSADER 0x004D9400
        void Skirmish_PrepareLeaderboardView()
        {
            int count = DAT_SkMasters2Data_Count::instance;
            for (int i = 0; i < count; ++i) {
                INT_ARRAY_00eb0e48::instance[i] = 1;
            }
            if (DAT_00ed3124::instance == 1) {
                for (int i = 0; i < count; ++i) {
                    if (DAT_SkMasters2DataArray::instance[i].score == 0) {
                        INT_ARRAY_00eb0e48::instance[i] = 0;
                    }
                }
            } else if (DAT_00ed3124::instance == 2) {
                for (int i = 0; i < count; ++i) {
                    if (DAT_SkMasters2DataArray::instance[i].score != 0) {
                        INT_ARRAY_00eb0e48::instance[i] = 0;
                    }
                }
            }

            if (DAT_MissionDefinedData::instance.sortColumn <= 1) {
                DAT_00eb9b60::instance = 0;
                if (DAT_MissionDefinedData::instance.descending == 1) {
                    for (int i = 0; i < count; ++i) {
                        if (INT_ARRAY_00eb0e48::instance[i] != 0) {
                            INT_ARRAY_00eb96d8::instance[DAT_00eb9b60::instance++] = i;
                        }
                    }
                } else if (DAT_MissionDefinedData::instance.descending == 0) {
                    int entry = count - 1;
                    for (int k = 0; k < count; ++k) {
                        if (INT_ARRAY_00eb0e48::instance[entry] != 0) {
                            INT_ARRAY_00eb96d8::instance[DAT_00eb9b60::instance++] = entry;
                        }
                        --entry;
                    }
                }
            } else if (DAT_MissionDefinedData::instance.sortColumn == 4) {
                DAT_00eb9b60::instance = 0;
                for (int i = 0; i != count; ++i) {
                    if (INT_ARRAY_00eb0e48::instance[i] != 0) {
                        INT_ARRAY_00ed27f0::instance[DAT_00eb9b60::instance] = i;
                        INT_ARRAY_00ed2be0::instance[DAT_00eb9b60::instance]
                            = ((DAT_SkMasters2DataArray::instance[i].localTimeYear - 2000) * 16
                                  + DAT_SkMasters2DataArray::instance[i].localTimeMonth)
                                * 32
                            + DAT_SkMasters2DataArray::instance[i].localTimeDay;
                        ++DAT_00eb9b60::instance;
                    }
                }
                MACRO_CALL(Skirmish_Func::Skirmish_SortAIOpponentOrder)(DAT_MissionDefinedData::instance.descending);
            } else if (DAT_MissionDefinedData::instance.sortColumn == 2) {
                DAT_00eb9b60::instance = 0;
                if (DAT_00ed3124::instance == 1) {
                    for (int i = 0; i < count; ++i) {
                        if (INT_ARRAY_00eb0e48::instance[i] != 0) {
                            INT_ARRAY_00ed27f0::instance[DAT_00eb9b60::instance] = i;
                            INT_ARRAY_00ed2be0::instance[DAT_00eb9b60::instance]
                                = 80 - DAT_SkMasters2DataArray::instance[i].score;
                            ++DAT_00eb9b60::instance;
                        }
                    }
                } else {
                    for (int i = 0; i < count; ++i) {
                        if (INT_ARRAY_00eb0e48::instance[i] == 0) {
                            continue;
                        }
                        if (DAT_SkMasters2DataArray::instance[i].score != 0) {
                            strcpy(DAT_SkMasters2DataArray::instance[i].mapName,
                                MACRO_CALL_MEMBER(
                                    Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(
                                    DE::SHCDE::TEXT_TRAIL_NAMES_CRU, DAT_SkMasters2DataArray::instance[i].score));
                            count = DAT_SkMasters2Data_Count::instance;
                        }
                        uchar first = DAT_SkMasters2DataArray::instance[i].mapName[0];
                        if ((uchar)(first - 'A') <= 'Z' - 'A') {
                            first += 'a' - 'A';
                        }
                        uchar second = DAT_SkMasters2DataArray::instance[i].mapName[1];
                        if ((uchar)(second - 'A') <= 'Z' - 'A') {
                            second += 'a' - 'A';
                        }
                        INT_ARRAY_00ed2be0::instance[DAT_00eb9b60::instance] = -1 - (first << 8) - second;
                        INT_ARRAY_00ed27f0::instance[DAT_00eb9b60::instance] = i;
                        ++DAT_00eb9b60::instance;
                    }
                }
                MACRO_CALL(Skirmish_Func::Skirmish_SortAIOpponentOrder)(DAT_MissionDefinedData::instance.descending);
            } else if (DAT_MissionDefinedData::instance.sortColumn == 3) {
                DAT_00eb9b60::instance = 0;
                for (int i = 0; i < count; ++i) {
                    if (INT_ARRAY_00eb0e48::instance[i] != 0) {
                        INT_ARRAY_00ed27f0::instance[DAT_00eb9b60::instance] = i;
                        INT_ARRAY_00ed2be0::instance[DAT_00eb9b60::instance]
                            = -1 - DAT_SkMasters2DataArray::instance[i].gameDurationInMinutes;
                        ++DAT_00eb9b60::instance;
                    }
                }
                MACRO_CALL(Skirmish_Func::Skirmish_SortAIOpponentOrder)(DAT_MissionDefinedData::instance.descending);
            }
        }

    }
}
}
