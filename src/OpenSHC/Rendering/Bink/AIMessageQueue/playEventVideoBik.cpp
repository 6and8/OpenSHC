#include "OpenSHC/Rendering/Bink/AIMessageQueue.func.hpp"

namespace OpenSHC {
namespace Rendering {
    namespace Bink {

        // FUNCTION: STRONGHOLDCRUSADER 0x004BE7E0
        void AIMessageQueue::playEventVideoBik(char* messageText, char* messageVfxFile, char* messageSfxFile)
        {
            if (messageText == 0) {
                return;
            }
            if (this->messagePlaying_0x0) {
                if (this->storedMessages_0x924 == 10) {
                    return;
                }
                this->savedMessageUnknownValue_0x104[this->storedMessages_0x924] = 1;
                this->savedMessageTextPtr_0xdc[this->storedMessages_0x924] = messageText;
                strcpy(this->savedMessageVfxFile_0x12c[this->storedMessages_0x924], messageVfxFile);
                strcpy(this->savedMessageSfxFile_0x514[this->storedMessages_0x924], messageSfxFile);
                this->savedMessageUnknownValue2_0x8fc[this->storedMessages_0x924] = 0;
                this->storedMessages_0x924 += 1;
                return;
            }
            this->currentMessageText_0x8 = messageText;
            this->currentMessageUnknownValue_0x4 = 1;
            this->currentMessageUnknownValue2_0xd4 = 0;
            MACRO_CALL_MEMBER(AIMessageQueue_Func::playVideoOverMap, this)(messageVfxFile, messageSfxFile);
        }

    }
}
}
