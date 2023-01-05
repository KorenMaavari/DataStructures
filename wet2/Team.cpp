#include "Team.h"

Team::Team(int teamId, int size, int points,  int teamAbility,  int allTeamMembersGamesPlayed, TeamInfo* teamInfo):
 teamId(teamId), size(size), points(points), teamAbility(teamAbility), 
allTeamMembersGamesPlayed(allTeamMembersGamesPlayed),  teamInfo(teamInfo), teamSpirit(identity){}

Team::~Team()
{
}
int Team::getSize() const{
     return size;
}
TeamInfo* Team::getTeamInfo(){
     return teamInfo;
}

int Team::getTeamId() const{
     return teamId;
}

int Team::getTeamPoints() const{
     return points;
}
void Team::addPoints(int addition){
    points += addition;
}
int Team::getTeamAbility() const{
     return teamAbility;
}
int Team::getAllTeamMembersGamesPlayed() const{
     return allTeamMembersGamesPlayed;
}

permutation_t Team::getTeamSpirit() const{
     return teamInfo->getTeamHead()->getPlayerSpirit() * teamInfo->getTeamTail()->getPlayerSpirit();
}


bool Team::operator<(const Team& other){
     if(this->getTeamAbility() < other.getTeamAbility()){
          return true;
     }
     else if(other.getTeamAbility() < this->getTeamAbility()){
          return false;
     }
     else{
          return this->getTeamId() < other.getTeamId();
     }
}bool Team::operator>(const Team& other){
     if(this->getTeamAbility() > other.getTeamAbility()){
          return true;
     }
     else if(other.getTeamAbility() > this->getTeamAbility()){
          return false;
     }
     else{
          return this->getTeamId() > other.getTeamId();
     }
}

void Team::setTeamInfo(TeamInfo* newTeamInfo){
     teamInfo = newTeamInfo;
}
void Team::addToTeamAbility(int addition){
     teamAbility += addition;
}
void Team::incSize(){
     size++;
}

Team::Team(const Team& other){
    this->teamId = other.teamId;
    this->teamAbility = other.teamAbility;
    this->size = other.size;
    this->points = other.points;
    this->allTeamMembersGamesPlayed = other.allTeamMembersGamesPlayed;
    this->teamInfo = other.teamInfo;
}
Team& Team::operator=(const Team& other){
    this->teamId = other.teamId;
    this->teamAbility = other.teamAbility;
    return *this;
}
void Team::setTeamId(int newId){
    this->teamId = newId;
}

Team& Team::operator+=(const Team& bought){
    this->size += bought.size;
    this->points += bought.points;
    this->teamAbility += bought.teamAbility;
    return *this;
}