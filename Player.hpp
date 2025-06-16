#pragma once
#include <string>

#ifndef PLAYER_HPP
#define PLAYER_HPP

using namespace std;

namespace coup {
    class Game; // forward declaretion

    // לכל שחקן יש שם, תפקיד ומטבעות. בכל תור יכול שחקן, בלי קשר לתפקידו, לבצע את אחת מהפעולות הבאות:

    class Player {


    protected:
        // There is no game without players so game is a living object! --> we use & and not *
        // in addition we will not change the Game obj.
        // using game as ref gives us control on the game such as Player turns and more.
        Game &_game;
        const string _name; // the name of the player
        int _coins = 0; // the number of coins he has


        bool sanctioned; // if player under sanction. (gather + tax)

        string last_move; // when player preform action as gather,tax...
                          // for tracking his last action that if player undo his move.

        bool cant_arrest; // spy can avoid player making arrest move


        bool another_turn;

        Player* last_couped = nullptr;


        bool active;


    public:
        Player(Game &game, const string &name);
        virtual ~Player() = default;

        void addCoins(int);
        void reduceCoins(int);


        void gather();
        void virtual tax();
        void bribe();
        void arrest(Player &target);
        void sanction(Player& target);
        void virtual coup(Player& target); // all players


        void turnCheck();
        virtual std::string role() const = 0;



        void virtual undo(Player&){throw runtime_error("Player could not undo");};

        int coins(); // return the number of coins
        string GetName() const;
        string getLastMove(){return last_move;}

        void openAccess();
        void blockArrest() {
            this->cant_arrest = true;
        }
        bool isActive() const{return active;}
        void deActive(Player& target);
        void reActive(){active = true;}

       void setAnotherTurn();
        bool hasAnotherTurn();
        Player& getLastCouped() const {return *last_couped;}

        void virtual onTurnStart(){} // Merchant bonus , Spy reactive special ability
        void setLastMove(const string &move){last_move = move;};
    };


}


#endif //PLAYER_HPP
