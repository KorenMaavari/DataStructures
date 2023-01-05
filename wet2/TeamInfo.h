#ifndef TEAM_INFO_H
#define TEAM_INFO_H
#include "Player.h"
class Player;
class Team;
class TeamInfo
{
private:
     int teamId;
     Team* team;
     Player* teamHead;
     Player* teamTail;
     bool isPlaying;
     bool goalKeeper;
public:
     TeamInfo(int teamId, Team* team = nullptr, Player* teamHead = nullptr, Player* teamTail = nullptr);
     ~TeamInfo() = default;
     //int getSize() const;
     Player* getTeamHead();
     Player* getTeamTail();
     void setTeamHead(Player* newHead);
     void setTeamTail(Player* newTail);
     Team* getTeam();
     void setTeamPtr(Team* newTeamPtr);
     void setId(int newId);

     bool stillPlaying() const;
     bool hasGoalKeeper() const;
     void setGoalKeeper();
     void eliminate();
};



#endif