// Email: gunrhxcd2001@gmail.com

#pragma once
#include <string>
#include <iostream>
#include <stdexcept>

#ifndef PLAYER_HPP
#define PLAYER_HPP

using namespace std;

namespace coup {

    /*
     forward declaration of Game class can be used to avoid including Game.hpp here.
     This is useful to avoid circular dependencies between Player and Game.
     Player needs to know about Game to access its methods and properties, but Game also needs
     to know about Player to manage the players in the game. By forward declaring Game here
     we can include Game.hpp only in Player.cpp where we need the full definition of Game.
     This way we can avoid including Game.hpp in Player.hpp, which would create a circular dependency.
     This is a common practice in C++ to reduce compilation dependencies and improve compilation time
     and organization of code. It allows us to use pointers or references to Game in Player
     without needing the full definition of Game in Player.hpp.
     This is a forward declaration of the Game class, which allows us to use pointers or references to Game
     in the Player class without needing to include the full definition of Game in this header file
     (which would create a circular dependency). The full definition of Game will be included in
     Player.cpp where we need to access the methods and properties of Game.
    */
    class Game; 


    class Player {
        private:
        void arrestCheck(Player &target) const;
        void sanctionCheck()const;
        void sanctionCheck(Player &target)const;
        void bribeCheck()const;



    protected:
        // There is no game without players so game is a living object! --> we use & and not *
        // in addition we will not change the Game obj.
        // using game as ref gives us control on the game such as Player turns and more.
        Game &_game;
        const string _name; // the name of the player
        int _coins = 0; // the number of coins he has
        void turnCheck() const; //checks



        bool sanctioned; // if player under sanction. (gather + tax)

        string last_move; // when player preform action as gather,tax...
                          // for tracking his last action that if player undo his move.

        bool cant_arrest; // spy can avoid player making arrest move


        bool another_turn; // if player has another turn (if he use bribe)

        Player* last_couped = nullptr; // the last player who was couped by this player (for undo coup)


        bool active; // if player is active in the game or not (if he is dead or not)
        bool special_ability = true; // if player has special ability to use (such as baron invest, governor undo tax, judge undo bribe...)
        // this flag is used to check if player can use his special ability once per turn.


    public:
        Player(Game &game, const string &name);
        virtual ~Player() = default; // virtual destructor to allow derived classes to clean up properly

        void addCoins(int);
        void reduceCoins(int);


        void gather();
        void virtual tax();
        void bribe();
        void arrest(Player &target);
        void sanction(Player& target);
        void virtual coup(Player& target); 


       
        virtual std::string role() const = 0; // return the role of the player (such as "Baron", "Spy", "General"...)
        // = 0 means this is a pure virtual function, so Player is an abstract class new and this function must be implemented in derived classes.



        void virtual undo(Player&){throw runtime_error("Player could not undo");} // undo action for player, if player can not undo his action it will throw an error.
        int coins(); // return the number of coins
        string GetName() const; // return the name of the player turns is based on the name of the player
        string getLastMove(){return last_move;} // save the last move of the player for undo action

        void openAccess(); // open access for player to preform actions again (after sanction or blockArrest)
        void blockArrest() {this->cant_arrest = true;} // block arrest for this player (used by Spy)
        bool isActive() const{return active;} // check if player is active in the game (not dead) for skiping turns and actions.
        void deActive(Player& target); // deActive player and set him as dead in the game. (if he get couped)
        void reActive(){active = true;} // reActive player and set him as active in the game (if he get revived by General undo coup action)

       void setAnotherTurn(); // set another turn as false! , on player (if he use bribe action)
        bool hasAnotherTurn(); // check if player has another turn (if he use bribe action)
        Player& getLastCouped() const {return *last_couped;} // return the last player who was couped by this player (for undo coup)

        void virtual onTurnStart(){special_ability = true;} //  special_ability is set to true on turn start, so player can use his special ability once per turn.
        // this function can be overridden by derived classes to implement specific behavior on turn start.
        // for example, if player is Merchant and has 3 coins, he can get an extra coin on turn start.
        // if player is not Merchant, it will just reset the special_ability to true.
        void setLastMove(const string &move){last_move = move;}; // set the last move of the player, used for undo action
    };


}


#endif //PLAYER_HPP
