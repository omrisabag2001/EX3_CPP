// Email: gunrhxcd2001@gmail.com


#include "Game.hpp"
#include "RoleFactory.hpp"
#include <iostream>

using namespace std;

using namespace coup;
// Constructor initializes the game and sets the index of the current turn to 0.
// It also initializes the last dead player and previous player pointers to nullptr.
Game::Game(){};


// Destructor cleans up the dynamically allocated players if owns_players is true.
// It iterates through the vector of players and deletes each player object.
// It also clears the vector of players to free up memory.
Game::~Game() {
    if (owns_players) {
        for (Player* p : arr_players) {
            delete p;
        }
    }
    arr_players.clear();
}


/*
  This function is called to advance the game to the next turn.
  It checks if there is a winner, and if so, it ends the game.
  If the current player has another turn, it allows them to take another action.
  If the next player is not active, it skips to the next active player.
  It also resets the special ability
  and open access for the current player at the start of their turn.


*/
void Game::NextTurn(){



  if(activePlayers() == 1){
    cout << "Game Over! The winner is: " << winner() << endl;
    return;
   }

  OnEndTurn();


  if(CurrentPlayer().hasAnotherTurn()){
    CurrentPlayer().setAnotherTurn();
    return;
  }


 index_turn = (index_turn + 1) % arr_players.size();

 if(!(arr_players[index_turn]->isActive())){
   arr_players[index_turn]->setLastMove("");
   this->NextTurn();
  }

 // if the player role is Merchant and has 3 coins it adds extra coin.
 // if other role it make the role special ability access again.
  arr_players[index_turn]->onTurnStart();




}

// Adds a player to the game.
// It checks if the maximum capacity of players (6) is reached.
// the GUI makes sure there is at least 2 players before starting the game.
// If the maximum capacity is reached, it throws an exception.
void Game::add_player(Player* player) {
  if(arr_players.size()>6){
   throw "max capacity of Players";
    }
    arr_players.push_back(player);
}


// Returns a vector of pointers to all players in the game.
// This is used to access all players in the game for various operations.
// It returns a constant reference to the vector of Player pointers.
// This allows the game to manage all players and their actions.
const std::vector<Player*>& Game::get_players() const {
    return arr_players;
}


// returns the name of the player whose turn it is currently.
const string Game:: turn(){
  return arr_players[index_turn]->GetName();

  }

  // Returns the current player object.
// This is used to access the current player's actions and properties.
// It returns a reference to the current player.
// This allows the game to manage player turns and actions.
// It is used to get the current player who is allowed to take actions.
// It is used to access the current player's actions and properties.
// It is used to get the current player who is allowed to take actions.
   Player& Game:: CurrentPlayer(){
    return *arr_players[this->index_turn];
  }



// Returns a vector of strings containing the names of all active players in the game.
vector<string> Game:: players(){
  vector<string> players;
     for(size_t i = 0; i < arr_players.size(); i++){
       if(arr_players[i]->isActive()){
       players.push_back(arr_players[i]->GetName());
       }

      }
      return players;
}




// Returns the name of the winner of the game.
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
// when player end his turn this function is called.
// it open access for the previous player to preform actions again.
// when his turn comes back.
void Game::OnEndTurn(){
  if(CurrentPlayer().isActive()){
    previous_player = &CurrentPlayer();
    previous_player->openAccess();
  }
}




