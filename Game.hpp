// Email: gunrhxcd2001@gmail.com

#pragma once
#include <vector>
#include "Player.hpp"
#ifndef GAME_HPP
#define GAME_HPP


namespace coup {
    class Game {
    private:
  
        vector<Player *> arr_players;
        size_t index_turn = 0;
        Player* lastdead = nullptr;
        Player* previous_player = nullptr;
        void OnEndTurn();



    public:
        // if true the game owns the players and will delete them in destructor.
        // if false the game does not own the players and will not delete them in destructor.
        // this is useful for GUI where the players are created by the GUI and not by the
    bool owns_players = true; 


        // player can not be arrested 2 times a row.
        Player* last_arrested = nullptr;

        Game();


// Destructor to clean up dynamically allocated players if owns_players is true
        // It will delete all players in arr_players if owns_players is true. (for GUI) 
        ~Game();

        // This function is called to advance the game to the next turn.
        // It checks if there is a winner, and if so, it ends the game.
        // If the current player has another turn, it allows them to take another action.
        // If the next player is not active, it skips to the next active player.
        // It also resets the special ability
        // and open access for the current player at the start of their turn.
        void NextTurn();

        // Returns the name of the player whose turn it is currently.
        const string turn();
        // Returns the current player object.
        // This is used to access the current player's actions and properties.
        // It returns a reference to the current player.
        // This allows the game to manage player turns and actions.
        // It is used to get the current player who is allowed to take actions.
        // It is used to access the current player's actions and properties.
        // It is used to get the current player who is allowed to take actions.
        Player& CurrentPlayer();

// Returns a vector of strings containing the names of all active players in the game.
        // This is used to display the list of players in the game.
        vector<string> players();

        // Adds a player to the game.
        void add_player(Player*);

        // Returns a vector of pointers to all players in the game.
        // This is used to access all players in the game for various operations.
        // It returns a vector of pointers to Player objects.
        // This allows the game to manage all players and their actions.
       const vector<Player *> &get_players()const;

        // Returns the name of the winner of the game.
        const string winner();

        // This function is called to set the last dead player in the game.
        void lastDead(Player& target){lastdead = &target;}
        //returns the number of active players in the game.
        // This is used to check if there is a winner or if the game should continue.
        int activePlayers()const;
    };
}

#endif //GAME_HPP
