//
// Created by  Omri Sabag on 08/05/2025.
//

#include "Game.hpp"
#include "RoleFactory.hpp"
#include <iostream>

using namespace std;

using namespace coup;
Game::Game(){};

void Game::NextTurn(){

  if(activePlayers() == 1){
    winner();
    return;
   }


  if(CurrentPlayer().hasAnotherTurn()){
    CurrentPlayer().setAnotherTurn();
    return;
  }


 index_turn = (index_turn + 1) % arr_players.size();

 if(!(arr_players[index_turn]->isActive())){
   arr_players[index_turn]->setLastMove("");
   this->NextTurn();
  }

 // if the player role is Merchant it adds addtion coin if he has 3 otherwise noting.
  arr_players[index_turn]->onTurnStart();




}

void Game::add_player(Player* player) {
  if(arr_players.size()>6){
   throw "max capacity of Players";
    }
    arr_players.push_back(player);
}
Player* Game::add_random_player(const std::string& name) {
    Player* p = RoleFactory::createRandomPlayer(*this, name);
    return p; // Player constructor will auto-register to game
}




const string Game:: turn(){
  return arr_players[index_turn]->GetName();

  }

   Player& Game:: CurrentPlayer(){
    return *arr_players[this->index_turn];
  }




vector<string> Game:: players(){
  vector<string> players;
     for(size_t i = 0; i < arr_players.size(); i++){
       if(arr_players[i]->isActive()){
       players.push_back(arr_players[i]->GetName());
       }

      }
      return players;
}





const string Game::winner(){
    int alive = 0;
    string alive_name;

    for(size_t i = 0; i < arr_players.size(); i++){
        if(arr_players[i]->isActive()){
            alive_name = arr_players[i]->GetName();
            alive++;
        }
    }

    if (alive == 1){
        return alive_name;
    } else {
        throw std::runtime_error("No winner yet!");
    }
}
 int Game::activePlayers()const{
    int alive = 0;

    for(size_t i = 0; i < arr_players.size(); i++){
        if(arr_players[i]->isActive()){
            alive++;
        }
    }
    return alive;

}




