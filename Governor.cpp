
#include "Governor.hpp"
#include "Player.hpp"
#include "Game.hpp"
#include <string>
#include <iostream>
#include <stdexcept>

using namespace coup;

void Governor::tax() {
    turnCheck();
    if (sanctioned) {throw std::runtime_error("You are sanctioned.");}
    addCoins(3);
    this->last_move = "tax";
    this->openAccess();
    _game.NextTurn();



}

void Governor::undo(Player& target) {
    if (!this->isActive()) {
      throw std::runtime_error("your are not in the game!");
    }
    if(this==&target) {
      throw std::runtime_error("You cant undoTax on yourself!");
    }

    if (target.getLastMove() == "tax") {
      if (dynamic_cast<Governor*>(&target)){
        target.reduceCoins(3);
        }else
            target.reduceCoins(2);
            cout << " Governor undo tax on: "+target.GetName()<< endl;
    }else throw std::runtime_error("Governor cannot undo "+target.getLastMove());


}

string Governor::role() const {
    return "Governor";
}


