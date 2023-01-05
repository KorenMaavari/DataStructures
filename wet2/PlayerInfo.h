#ifndef PLAYER_INFO_H
#define PLAYER_INFO_H

#include "Player.h"
#include "TeamInfo.h"


class PlayerInfo
{
public:
     int parentId;
     Player* player;
     TeamInfo* teamInfo;

     PlayerInfo(int parentId, Player* player,TeamInfo* teamInfo):parentId(parentId), player(player), teamInfo(teamInfo) {}
     PlayerInfo(const PlayerInfo& other){
          this->parentId = other.parentId;
          this->player = other.player;
          this->teamInfo = other.teamInfo;
     }
};

#endif