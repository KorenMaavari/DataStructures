#include "UnionFind.h"



void UnionFind::makeSet(Player* player_ptr, TeamInfo* teamInfo_ptr) {
    int tempArr[5] = {1, 2, 3, 4, 5};
    int a = 0, aa = 0;
    permutation_t temp(tempArr);
    //assuming there's no player in that id already. otherwise, its replacing him:
    PlayerInfo *playerInfo = nullptr;
    try {
        playerInfo = new PlayerInfo(teamInfo_ptr->getTeamTail()->getId(), player_ptr, teamInfo_ptr);
    }catch(std::exception& e){
        if(playerInfo != nullptr){
            delete playerInfo;
        }
        throw std::bad_alloc();
    }
    //playersInfosDestructionList.append(playerInfo, 1);

    players.insert(playerInfo, player_ptr->getId());
    find(player_ptr->getId(),&aa,  &temp, &a);
    if(teamInfo_ptr->getTeamTail()->getId() != teamInfo_ptr->getTeamHead()->getId())
        correctGamesPlayed(player_ptr, teamInfo_ptr->getTeamTail());
    correctGamesPlayed(player_ptr, teamInfo_ptr->getTeamHead());


    teamInfo_ptr->setTeamTail(player_ptr);
}

void UnionFind::Union(int buyerHeadId, int boughtHeadId){// צריך להתייחס למקרה שיש קבוצה ריקה או שתיהן
    int tempArr[5] = {1,2,3,4,5}; int a = 0, aa=0; permutation_t temp(tempArr);

    TeamInfo* buyerInfo = find(buyerHeadId, &aa, &temp, &a);
    TeamInfo* boughtInfo = find(boughtHeadId, &aa, &temp, &a);
    Team* buyer = buyerInfo->getTeam();
    Team* bought = boughtInfo->getTeam();
    if(buyerInfo->getTeam()->getSize() >= boughtInfo->getTeam()->getSize()){
        bigTeamBuys(buyerInfo->getTeamHead(),
                    buyerInfo->getTeamTail(),
                    boughtInfo->getTeamHead(),
                    boughtInfo->getTeamTail());

    }
    else{
        smallTeamBuys(buyerInfo->getTeamHead(),
                      buyerInfo->getTeamTail(),
                      boughtInfo->getTeamHead(),
                      boughtInfo->getTeamTail());
        buyer->setTeamInfo(boughtInfo); // פה  אני גורם שקבוצה קונה קטנה תצביע למידע על קבוצה גדולה
    }
    *buyer += *bought;
    int tempArr2[5] = {1,2,3,4,5}; a = 0; aa=0; permutation_t temp2(tempArr2);
    find(buyerInfo->getTeamTail()->getId(), &aa, &temp2, &a);

}




TeamInfo* UnionFind::find(int key_playerId, int* headId, permutation_t* perm, int* numOfGames){
    //assumptions:\\_//input is legal\\_//perm is the identity permutation\\_//num of games is 0
    PlayerInfo* currentPlayerInfo = players[key_playerId];
    //int headId = currentPlayerInfo->teamInfo->getTeamHead()->getId();
    int parentId = currentPlayerInfo->parentId;

    if(parentId == key_playerId){
        *headId = key_playerId;
        *perm = (currentPlayerInfo->player->getPlayerSpirit());
        *numOfGames+=currentPlayerInfo->player->getGamesPlayed();
        return currentPlayerInfo->teamInfo;
    }
    Player* currentPlayer = currentPlayerInfo->player;
    Player* parent = players[parentId]->player;
    TeamInfo* result = find(parentId,headId, perm, numOfGames);
    *perm = (*perm) * (currentPlayerInfo->player->getPlayerSpirit());
    *numOfGames += currentPlayer->getGamesPlayed();
    if(currentPlayerInfo->parentId != *headId){// :קיצור מסלולים
        currentPlayer->multPermutation(parent->getPlayerSpirit());
        currentPlayer->addGamesPlayed(parent->getGamesPlayed());
        currentPlayerInfo->parentId = *headId;
    }
    return result;
}


Player* UnionFind::getPlayer(int playerId){
    return players[playerId]->player;
}

bool UnionFind::exist(int playerId) const{
    //std::cout << "id i think UnionFind should look for: "<< playerId<< std::endl;
    return players.doesExist(playerId);
}

void UnionFind::bigTeamBuys(Player* bigTeamHead, Player* bigTeamTail, Player* smallTeamHead, Player* smallTeamTail){
    if(bigTeamTail->getId() != bigTeamHead->getId()) {
        smallTeamHead->multPermutation(bigTeamTail->getPlayerSpirit());
    }
    correctGamesPlayed(smallTeamHead, bigTeamHead);
    players[smallTeamHead->getId()]->parentId = bigTeamHead->getId();
    players[bigTeamHead->getId()]->teamInfo->setTeamTail(smallTeamTail);
}

void UnionFind::smallTeamBuys(Player* smallTeamHead, Player* smallTeamTail, Player* bigTeamHead, Player* bigTeamTail){
    if(smallTeamHead->getId() == smallTeamTail->getId()){
        bigTeamHead->multPermutation(smallTeamHead->getPlayerSpirit());
    }
    else {
        bigTeamHead->multPermutation(smallTeamHead->getPlayerSpirit() * smallTeamTail->getPlayerSpirit());
    }
    smallTeamHead->multPermutation(bigTeamHead->getPlayerSpirit().inv());
    correctGamesPlayed(smallTeamHead, bigTeamHead);
    players[smallTeamHead->getId()]->parentId = bigTeamHead->getId();
    players[bigTeamHead->getId()]->teamInfo->setTeamTail(/*small*/bigTeamTail);
    //teamInfo of big team head should know about small team that bought it:
    players[bigTeamHead->getId()]->teamInfo->setTeamPtr(players[smallTeamHead->getId()]->teamInfo->getTeam());
    players[bigTeamHead->getId()]->teamInfo->setId(players[smallTeamHead->getId()]->teamInfo->getTeam()->getTeamId());

}

void UnionFind::correctGamesPlayed(Player* newPlayer, Player* teamHead){
    if(newPlayer->getId() == teamHead->getId()){
        return;
    }
    newPlayer->addGamesPlayed(-teamHead->getGamesPlayed());              // subtract the number of games the team leader has played
}






UnionFind::~UnionFind(){
    for (int i = 0; i < players.getTableSize(); i++) {
        List<PlayerInfo*, int>& list = players.table[i];
        Node<PlayerInfo*, int>* current = list.head;
        while (current != nullptr) {
            // Delete the PlayerInfo object that the current node points to
            delete current->data;
            current = current->next;
        }
    }
}