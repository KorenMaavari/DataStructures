#include "TeamInfo.h"

TeamInfo::TeamInfo(int teamId, Team* team, Player* teamHead, Player* teamTail):
teamId(teamId), team(team), teamHead(teamHead), teamTail(teamTail), isPlaying(true), goalKeeper(false){}


Player* TeamInfo::getTeamHead(){
     return teamHead;
}
Player* TeamInfo::getTeamTail(){
     return teamTail;
}

void TeamInfo::setId(int newId) {
    this->teamId = newId;
}
void TeamInfo::setTeamHead(Player* newHead){
     teamHead = newHead;
}
void TeamInfo::setTeamTail(Player* newTail){
     teamTail = newTail;
}
// int TeamInfo::getSize() const{
//      return size;
// }

Team* TeamInfo::getTeam(){
     return team;
}

bool TeamInfo::stillPlaying() const{
     return isPlaying;
}
void TeamInfo::setTeamPtr(Team* newTeamPtr){
     team = newTeamPtr;
}

void TeamInfo::eliminate(){
     isPlaying = false;
}

bool TeamInfo::hasGoalKeeper() const{
     return goalKeeper;
}
void TeamInfo::setGoalKeeper(){
     goalKeeper = true;
}