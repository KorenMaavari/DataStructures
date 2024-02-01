#ifndef PLAYER_H
#define PLAYER_H
#include "wet2util.h"
#include "Team.h"


class Player{
private: 
     int id;
     int teamId;
     int gamesPlayed;
     int ability;
     int cards;
     bool goalKeeper;
     permutation_t spirit;


public:
     Player(int id, int teamId, int gamesPlayed, int ability, int cards, bool goalKeeper, permutation_t spirit);
     ~Player() = default;

     int getId() const;
     void multPermutation(const permutation_t& other);
     void multPermutationFromRight(const permutation_t& other);
    permutation_t getPlayerSpirit();// לממש
     int getGamesPlayed()const;// knna
     void addGamesPlayed(int addition);//knna (add to myself what i got)
     int getCards() const;//knna
     void addCards(int addition);//knna
};



#endif