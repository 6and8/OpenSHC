#include "../GameSynchronyState.func.hpp"

#include "OpenSHC/IO/LowLevelMemory.func.hpp"
#include "OpenSHC/Commands/GameCommandScheduling.hpp"
#include "OpenSHC/Commands/GameCommandState.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"
#include "OpenSHC/Globals/DAT_ProtocolDefinedData.hpp"

namespace OpenSHC {
namespace Synchrony {

    // FUNCTION: STRONGHOLDCRUSADER 0x00480210
    void GameSynchronyState::scheduleReceivedCommand(
        char commandCategory, DWORD dxPlayerHandle, dword time, void* address)
    {
        if (this->DAT_GameCommandArrayIndex >= 200) {
            return;
        }
        if (commandCategory == 0x4d) {
            DAT_GameSynchronyState::instance.unknownIncrementBy40_01 += 40;
            if (MACRO_CALL_MEMBER(GameSynchronyState_Func::translateMultiplayerIDsIntoPlayerIDs, this)(dxPlayerHandle)
                == DAT_GameSynchronyState::instance.currentPlayerSlotID) {
                this->DAT_GameCommandArray[this->DAT_CurrentGameCommandID].time
                    = DAT_GameCore::instance.mapTimeInTicks + 1;
            }
        }
        if (time != 0) {
            if ((int)time <= DAT_GameCore::instance.mapTimeInTicks) {
                this->lateCommandPenalty += 2;
            } else if ((int)time - DAT_GameCore::instance.mapTimeInTicks
                < this->DAT_LagIndicatorPerPlayer[this->currentPlayerSlotID]) {
                this->DAT_LagIndicatorPerPlayer[this->currentPlayerSlotID]
                    = (short)(time - DAT_GameCore::instance.mapTimeInTicks);
            }
        }
        this->DAT_CurrentGameCommandID = this->DAT_GameCommandArrayIndex;
        MACRO_CALL_MEMBER(IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
            1260, '\0', &this->DAT_GameCommandArray[this->DAT_GameCommandArrayIndex].parameters);
        this->DAT_GameCommandArray[this->DAT_CurrentGameCommandID].stateUnk = Commands::GCS_UNPROCESSED;
        this->DAT_GameCommandArray[this->DAT_CurrentGameCommandID].playerUnk = dxPlayerHandle;
        this->DAT_GameCommandArray[this->DAT_CurrentGameCommandID].commandType = commandCategory;
        this->DAT_GameCommandArray[this->DAT_CurrentGameCommandID].time = time;
        this->DAT_CommandParameterOffset = 0;
        this->DAT_CommandActionPlan = Commands::GCS_SCHEDULE_RECEIVED_COMMAND;
        (&DAT_ProtocolDefinedData::instance
                .commandFunctions)[this->DAT_GameCommandArray[this->DAT_CurrentGameCommandID].commandType]();
        if (0 < (int)this->DAT_GameCommandArray[this->DAT_CurrentGameCommandID].time) {
            MACRO_CALL_MEMBER(IO::LowLevelMemory_Func::copyData, DAT_LowLevelMemory::ptr)(
                this->DAT_CommandSize, address, &this->DAT_GameCommandArray[this->DAT_CurrentGameCommandID].parameters);
            ++this->DAT_GameCommandArrayIndex;
            if (this->DAT_GameCommandArrayIndex >= 200) {
                this->DAT_GameCommandArrayIndex = 0;
            }
            return;
        }
        MACRO_CALL_MEMBER(IO::LowLevelMemory_Func::copyData, DAT_LowLevelMemory::ptr)(
            this->DAT_CommandSize, address, this->DAT_GameCommandFixedParameterLocation);
        Commands::GameCommand& command = this->DAT_GameCommandArray[this->DAT_CurrentGameCommandID];
        this->protocolInvokerPlayerID
            = MACRO_CALL_MEMBER(GameSynchronyState_Func::translateMultiplayerIDsIntoPlayerIDs, this)(command.playerUnk);
        this->DAT_GameCommandParam5 = 0;
        this->DAT_GameCommandParam4 = 0;
        this->DAT_GameCommandParam3 = 0;
        this->DAT_GameCommandParam2 = 0;
        this->DAT_GameCommandParam1 = 0;
        this->DAT_GameCommandParam0 = 0;
        this->DAT_CommandActionPlan = Commands::GCS_EXECUTE;
        this->DAT_CommandParameterOffset = 0;
        MACRO_CALL_MEMBER(GameSynchronyState_Func::clearGameCommandEntry, this)(this->DAT_CurrentGameCommandID);
        (&DAT_ProtocolDefinedData::instance.commandFunctions)[command.commandType]();
    }

}
}
