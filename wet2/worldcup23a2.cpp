#include "worldcup23a2.h"

world_cup_t::world_cup_t():teams(nullptr), prioritizedTeams(nullptr),numOfActiveTeams(0)
{
}

world_cup_t::~world_cup_t() {
    Node<Team *, int> *currentNode1 = teamDestructionList.head;
    while (currentNode1 != nullptr) {
        delete currentNode1->data;
        currentNode1 = currentNode1->next;
    }
    Node<TeamInfo *, int> *currentNode2 = this->teamInfoDestructionList.head;
    while (currentNode2 != nullptr) {
        delete currentNode2->data;
        currentNode2 = currentNode2->next;
    }
    Node<Player *, int> *currentNode3 = playerDestructionList.head;
    while (currentNode3 != nullptr) {
        delete currentNode3->data;
        currentNode3 = currentNode3->next;
    }

//    teamDestructionList.clearNodes(teamDestructionList.head);
//    teamInfoDestructionList.clearNodes(teamInfoDestructionList.head);
//    playerDestructionList.clearNodes(playerDestructionList.head);
//

//////////////////////////////////////////////////////////////////////////////////////////////////////////
//       need to go through all													   					    //
//		 destruction lists and delete them all		    	    									    //
//		 also maybe delete avl(does it do it automatically? (i don't see a destructor))				    //
//////////////////////////////////////////////////////////////////////////////////////////////////////////
}

StatusType world_cup_t::add_team(int teamId)
{
	if(teamId <= 0){                                                                         //validity check
		return StatusType::INVALID_INPUT;
	}
	if(teams.findNode(teamId)){
		return StatusType::FAILURE;
	}
	try{	
		TeamInfo* newTeamInfo = new TeamInfo(teamId);                                       //team cretion
		Team* newTeam = new Team(teamId);
		newTeam->setTeamInfo(newTeamInfo);
		newTeamInfo->setTeamPtr(newTeam);

		teamDestructionList.append(newTeam, 1);                                             //pointers save
		teamInfoDestructionList.append(newTeamInfo,1);

		TreeNode<int, Team*>* teamIdNode = new TreeNode<int, Team*>(teamId, newTeam);       //trees insertion
		TreeNode<Team, Team*>* teamRankNode = new TreeNode<Team, Team*>(*newTeam, newTeam);
		//////////////////////////////////////////////////////////////////////////////////////
		//treeDestructionList.append(teamIdNode, 1);				maybe need to delete    // 
		//rankTreeDestructionList.append(teamRankNode, 1);		nodes also	         //
		//////////////////////////////////////////////////////////////////////////////////////
		teams.insertNode(teamIdNode);
		prioritizedTeams.insertNode(teamRankNode);
	}catch(std::exception& e){
		return StatusType::ALLOCATION_ERROR;
	}
    numOfActiveTeams++;
	return StatusType::SUCCESS;
}

StatusType world_cup_t::remove_team(int teamId)
{
	if(teamId <= 0){
		return StatusType::INVALID_INPUT;
	}
	TreeNode<int, Team*>* teamToRemove = teams.findNode(teamId);
	if(!teamToRemove){
		return StatusType::FAILURE;
	} 
	Team* team = teamToRemove->m_data;
	TeamInfo* teamToRemoveInfo = teamToRemove->m_data->getTeamInfo(); // saving teamInfo
	teamToRemoveInfo->eliminate();                                    // changing bool to false

	teams.deleteNode(teamId);
	prioritizedTeams.deleteNode(*team);

//////////////////////////////////////////////////////////////////////////////////////////////////////////
//       removes from both trees													            	    //
//		 does not delete Data		    	    											            //
//		 only delete nodes from trees
//       //maybe add to tree delete removed node//
//////////////////////////////////////////////////////////////////////////////////////////////////////////
    numOfActiveTeams--;
    return StatusType::SUCCESS;
}

StatusType world_cup_t::add_player(int playerId, int teamId,
                                   const permutation_t &spirit, int gamesPlayed,
                                   int ability, int cards, bool goalKeeper)
{

	if(playerId <= 0 || playerId <= 0 || !spirit.isvalid() || cards < 0 || gamesPlayed < 0 || teamId <= 0){
		return StatusType::INVALID_INPUT;
	}
	if(!teams.findNode(teamId) || players.exist(playerId)){
		return StatusType::FAILURE;
	}

	Player* newPlayer = new Player(playerId, teamId, gamesPlayed, ability, cards, goalKeeper, spirit);
	playerDestructionList.append(newPlayer, 1);

	TreeNode<int, Team*>* teamNode = teams.findNode(teamId);
	TreeNode<Team, Team*>*  rankTeamNode = prioritizedTeams.findNode(*(teamNode->m_data));
	Team* teamPtr = teamNode->m_data;
	TeamInfo* info = teamNode->m_data->getTeamInfo();
    if(goalKeeper){
        info->setGoalKeeper();
    }
	if(!info->getTeamHead()){
		info->setTeamHead(newPlayer);
		info->setTeamTail(newPlayer);
	}
	prioritizedTeams.deleteNode(*teamPtr);
	teamPtr->addToTeamAbility(ability);
	teamPtr->incSize();
	TreeNode<Team,Team*>* updatedTeamNode = new TreeNode<Team, Team*>(*teamPtr, teamPtr);
	prioritizedTeams.insertNode(updatedTeamNode);
	players.makeSet(newPlayer, info);

//////////////////////////////////////////////////////////////////////////////////////////////////////////
//		added update teamAbility
//		remove rankTeam node (like update_player_stats from wet 1)
//		create new TreeNode<Team, Team*> (with teamPtr)
//		insert it to prioritizedTeams
//////////////////////////////////////////////////////////////////////////////////////////////////////////
	return StatusType::SUCCESS;
}

output_t<int> world_cup_t::play_match(int teamId1, int teamId2)
{

    if(teamId1 == teamId2 || teamId1<=0 || teamId2<=0){
        return StatusType::INVALID_INPUT;
    }
    TreeNode<int, Team*>* team1Node = teams.findNode(teamId1);
    TreeNode<int, Team*>* team2Node = teams.findNode(teamId2);
	if(!team1Node || !team2Node){
        return StatusType::FAILURE;
    }
    if(!team1Node->m_data->getTeamInfo()->hasGoalKeeper() || !team2Node->m_data->getTeamInfo()->hasGoalKeeper()){
        return StatusType::FAILURE;
    }
    bool team1Wins = false, team2Wins = false, tie = false, halfTie = false;
    int power1 = team1Node->m_data->getTeamPoints()+team1Node->m_data->getTeamAbility();
    int power2 = team2Node->m_data->getTeamPoints()+team2Node->m_data->getTeamAbility();
    if(power1 > power2){
        team1Wins = true;
    }
    else if(power2 > power1){
        team2Wins = true;
    }
    else{
        halfTie = true;
        int none1 = 0, none2 = 0; int a[5] = {0,1,2,3,4};
        permutation_t perm1(a); permutation_t perm2(a);
        players.find(team1Node->m_data->getTeamInfo()->getTeamTail()->getId(), &none1, &perm1, &none2);
        none1 = 0, none2 = 0;
        players.find(team2Node->m_data->getTeamInfo()->getTeamTail()->getId(), &none1, &perm2, &none2);
        if(perm1.strength() > perm2.strength()){
            team1Wins = true;
        }
        else if(perm2.strength() > perm1.strength()){
            team2Wins = true;
        }
        else{
            tie = true;
        }
    }
    team1Node->m_data->getTeamInfo()->getTeamHead()->addGamesPlayed(1);
    team2Node->m_data->getTeamInfo()->getTeamHead()->addGamesPlayed(1);

    if(team1Wins){
        team1Node->m_data->addPoints(3);
        if(halfTie){
            return 2;
        }
        return 1;
    }
    if(team2Wins){
        team2Node->m_data->addPoints(3);
        if(halfTie){
            return 4;
        }
        return 3;
    }
    if(tie){
        team1Node->m_data->addPoints(1);
        team2Node->m_data->addPoints(1);
        return 0;
    }
}

output_t<int> world_cup_t::num_played_games_for_player(int playerId)
{
    if(playerId <= 0){
        return StatusType::INVALID_INPUT;
    }
    if(!players.exist(playerId)){
        return StatusType::FAILURE;
    }
	int result = 0, none = 0; permutation_t temp;
	players.find(playerId, &none, &temp, &result);
	return result;
}

StatusType world_cup_t::add_player_cards(int playerId, int cards)
{
    int n = 0, none = 0; permutation_t temp;
	if(playerId <= 0 || cards < 0){
        return StatusType::INVALID_INPUT;
    }
    if(!players.exist(playerId)){
        return StatusType::FAILURE;
    }
    if(! players.find(playerId, &none, &temp, &n)->stillPlaying()){
        return StatusType::FAILURE;
    }
    players.getPlayer(playerId)->addCards(cards);

	return StatusType::SUCCESS;
}

output_t<int> world_cup_t::get_player_cards(int playerId)
{
	if(playerId <= 0){
        return StatusType::INVALID_INPUT;
    }
    if(!players.exist(playerId)){
        return StatusType::FAILURE;
    }
    return players.getPlayer(playerId)->getCards();
}

output_t<int> world_cup_t::get_team_points(int teamId)
{

    if(teamId <= 0){
        return StatusType::INVALID_INPUT;
    }
    TreeNode<int, Team*>* teamNode = teams.findNode(teamId);
    if(!teamNode){
        return StatusType::FAILURE;
    }
    return teamNode->m_data->getTeamPoints();

	// ללכת לקבוצה, אם היא קיימת, להחזיר
	return 30003;
}

output_t<int> world_cup_t::get_ith_pointless_ability(int i)
{

    i++;
    int num = 0;
    if(teams.getRoot() != nullptr){
        num = teams.getRoot()->m_subTreeNodesNum;
    }


    if( num == 0 || i<1 || i-1>=num){
        return StatusType::FAILURE;
    }
    TreeNode<Team, Team*>* team = prioritizedTeams.select(i);
    return team->m_data->getTeamId();
}

output_t<permutation_t> world_cup_t::get_partial_spirit(int playerId)
{
    if(playerId <= 0){
        return StatusType::INVALID_INPUT;
    }
    if(!players.exist(playerId)){
        return StatusType::FAILURE;
    }
    int none1 = 0, none2 = 0; permutation_t temp;
    if(!players.find(playerId, &none1, &temp, &none2)->stillPlaying()){
        return StatusType::FAILURE;
    }
    //if wasn't disqualified
    int n = 0, none = 0; int array[5] = {0,1,2,3,4}; permutation_t result(array);
    players.find(playerId, &none, &result, &n);
    //std::cout<<"team of "<<playerId <<" perm is: "<<result<<std::endl;
	return result;
}

StatusType world_cup_t::buy_team(int teamId1, int teamId2)
{

    if(teamId1 == teamId2 || teamId1<=0 || teamId2<=0){
        return StatusType::INVALID_INPUT;
    }
    TreeNode<int ,Team*>* buyerNode = teams.findNode(teamId1);
    TreeNode<int ,Team*>* boughtNode = teams.findNode(teamId2);
    if(buyerNode == nullptr || boughtNode == nullptr){
        return StatusType::FAILURE;
    }
    /////////////////////////////////////////////////
    //               validity check                //
    /////////////////////////////////////////////////

    //assuming its valid
    numOfActiveTeams--;
    Team* buyer = buyerNode->m_data;
    Team* bought = boughtNode->m_data;
    TeamInfo* info1 = buyer->getTeamInfo();
    TeamInfo* info2 = bought->getTeamInfo();

    if(info2->hasGoalKeeper()){
        info1->setGoalKeeper();
    }
    if(info1->hasGoalKeeper()){
        info2->setGoalKeeper();
    }
    if(bought->getSize() == 0){
        remove_team(teamId2);
        return StatusType::SUCCESS;
    }
    if(buyer->getSize() == 0){
        teams.deleteNode(teamId2);
        teams.deleteNode(teamId1);
        prioritizedTeams.deleteNode(*buyer);
        prioritizedTeams.deleteNode(*bought);

        bought->setTeamId(teamId1);
        bought->getTeamInfo()->setId(teamId1);
        TreeNode<int, Team*>* modified = new TreeNode<int, Team*>(teamId1, bought);
        TreeNode<Team, Team*>* modifiedRank = new TreeNode<Team, Team*>(*bought, bought);
        teams.insertNode(modified);
        prioritizedTeams.insertNode(modifiedRank);
        return StatusType::SUCCESS;
    }


    prioritizedTeams.deleteNode(*buyer);
    teams.deleteNode(teamId2);
    players.Union(info1->getTeamHead()->getId(), info2->getTeamHead()->getId());
    prioritizedTeams.deleteNode(*bought);
    TreeNode<Team, Team*>* modifiedRank = new TreeNode<Team, Team*>(*buyer, buyer);
    prioritizedTeams.insertNode(modifiedRank);
    return StatusType::SUCCESS;
}




