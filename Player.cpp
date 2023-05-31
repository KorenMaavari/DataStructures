#include "Player.h"
#include <iostream>



Player::Player(int id, int teamId, int gamesPlayed, int ability, int cards, bool goalKeeper, permutation_t spirit):
id(id), teamId(teamId), gamesPlayed(gamesPlayed), ability(ability), cards(cards), goalKeeper(goalKeeper), spirit(spirit){}


int Player::getId() const{
     return id;
}

void Player::multPermutation(const permutation_t& other){
    spirit = other*spirit;
}
void Player::multPermutationFromRight(const permutation_t& other){
    spirit = spirit*other;
}
permutation_t Player::getPlayerSpirit(){
     return spirit;
}

int Player::getGamesPlayed() const {
     return gamesPlayed;
}

void Player::addGamesPlayed(int addition){
     gamesPlayed += addition;
}
int Player::getCards() const{
     return cards;
}

void Player::addCards(int addition){
     cards += addition;
}