#ifndef UNION_FIND
#define UNION_FIND
#include <ostream>
#include "HashTable.h"
#include "PlayerInfo.h"
#include "intHash.h"
#include "wet2util.h"
#include "Player.h"

class UnionFind{
private:
     HashTable<PlayerInfo*, int, intHash> players;
     //List<PlayerInfo*, int> playersInfosDestructionList;
public:
     UnionFind() = default;
     ~UnionFind();
     void makeSet(Player* player_ptr, TeamInfo* teamInfo_ptr);
     void Union(int buyerId, int boughtId);
     TeamInfo* find(int key_playerId, int* headId, permutation_t* perm, int* numOfGames);
     Player* getPlayer(int playerId);
     bool exist(int playerId) const;

     void bigTeamBuys(Player* bigTeamHead, Player* bigTeamTail, Player* smallTeamHead, Player* smallTeamTail);
     void smallTeamBuys(Player* bigTeamHead, Player* bigTeamTail, Player* smallTeamHead, Player* smallTeamTail);


     void correctGamesPlayed(Player* newPlayer, Player* teamHead);
};



#endif
















/*
template <class ItemKey, class SetKey>
void UnionFind<class ItemKey, class SetKey>::makeSet(ItemKey itemKey, SetKey setKey, SetInfo* setInfo){
     if(fathers.doesExist(itemKey)){
          return;//if player is already inside it is a mistake
     }

     Pair<ItemKey, SetKey> value(itemKey, setKey);
     fathers.insert(value, itemKey);

     if(! sets.doesExist(SetKey)){ // Set was not yet inside
          setInfo->setHead(itemKey);
          sets.insert(setInfo, setKey);
          return;
     }
     if(setInfo->getIsActive()){   // Set was inside, and active
          value.itemKey = setInfo->getHeadId();
          // לדאוג כאן לחסר ממנו את התמורה של הראש שאליו הוא הצטרף
          return;
     }
     if(!setInfo->getWasBought()){//if it was removed but not bought
          ItemKey headId = setInfo->getHead();
          SetInfo* toMove = sets[setKey];
          removedHeads.insert(headId, headId);
          removedSets.insert(toMove , headId);
     }
     sets.remove(setKey); // was removed anyway
     setInfo->setHead(itemKey);
     sets.insert(setInfo, setKey);

}




*/

