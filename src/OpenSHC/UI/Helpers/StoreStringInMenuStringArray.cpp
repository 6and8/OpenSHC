#include "OpenSHC/UI/Helpers.func.hpp"

#include "OpenSHC/Globals/DAT_ArrayOfStoredMenuStrings.hpp"
#include "OpenSHC/Globals/DAT_NumberOfStoredMenuStrings.hpp"

namespace OpenSHC {
namespace UI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004DA750
    void Helpers::StoreStringInMenuStringArray(char* textToStore)
    {
        if ((int)DAT_NumberOfStoredMenuStrings::instance < 33 && strlen(textToStore) <= 0x3ff) {
            strcpy(DAT_ArrayOfStoredMenuStrings::instance[DAT_NumberOfStoredMenuStrings::instance++], textToStore);
        }
    }

}
}
