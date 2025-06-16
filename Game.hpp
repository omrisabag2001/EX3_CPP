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



    public:
        // player can not be arrested 2 times a row.
        Player* last_arrested = nullptr;


        Game();

        ~Game()= default;

        void NextTurn();

        const string turn();
         Player& CurrentPlayer();


        vector<string> players();

        void add_player(Player*);
        // from gui
        Player* add_random_player(const std::string& name);

        vector<Player *> &get_players();
        const string winner();
        void lastDead(Player& target){lastdead = &target;}
        int activePlayers()const;
    };
}

#endif //GAME_HPP
