#ifndef TEAM_H
#define TEAM_H
#include "wet2util.h"
#include "TeamInfo.h"
class TeamInfo;
class Team
{
private:
     const int identity[5] = {1,2,3,4,5};
     int size;
     int teamId;
     int points;
     int teamAbility;
     int allTeamMembersGamesPlayed;
     permutation_t teamSpirit;
     TeamInfo* teamInfo;
     
public:
     Team(int teamId, int size = 0, int points = 0,  int teamAbility = 0,  int allTeamMembersGamesPlayed = 0, TeamInfo* teamInfo = nullptr);
     Team(const Team& other);
     ~Team();
     Team& operator=(const Team& other);
     int getSize() const;
     int getTeamId() const;
     void setTeamId(int newId);
     int getTeamPoints() const;
     void addPoints(int additions);
     int getTeamAbility() const;
     int getAllTeamMembersGamesPlayed() const;
     permutation_t getTeamSpirit() const;
     TeamInfo* getTeamInfo();
     void setTeamInfo(TeamInfo* newTeamInfo);
     void incSize();
     void addToTeamAbility(int addition);
     Team& operator+=(const Team& bought);



//     bool operator==(const Team& other);

     bool operator<(const Team& other);
     bool operator>(const Team& other);
};



#endif