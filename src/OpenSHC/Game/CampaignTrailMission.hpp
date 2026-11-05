/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Game/CampaignTrailMission.hpp'
*/

#pragma once

namespace OpenSHC {
namespace Game {

#pragma pack(push, 1)
    // SIZE: 0x00000090
    typedef struct CampaignTrailMission {

        pointer mapNameAddress; // 0x00000000 length: 4
        int fairness; // 0x00000004 length: 4
        int startLevels; // 0x00000008 length: 4
        int numberOfPlayers; // 0x0000000C length: 4
        int playerAI[8]; // 0x00000010 length: 32
        int position[8]; // 0x00000030 length: 32
        int team[8]; // 0x00000050 length: 32
        int aiv[8]; // 0x00000070 length: 32

    } CampaignTrailMission;
#pragma pack(pop)

    static_assert_cpp98_obj(sizeof(CampaignTrailMission) == 144, CampaignTrailMission);
} // namespace Game
} // namespace OpenSHC
