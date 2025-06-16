//
// Created by  Omri Sabag on 08/05/2025.
//

#include "Judge.hpp"

using namespace coup;
void Judge::undo(Player &target){ // can cancel bribe

  if(target.getLastMove() == "bribe"){
    target.setAnotherTurn();
  }else
    throw std::runtime_error("Judge cannot undo "+target.getLastMove() );

  }
string Judge::role() const {
    return "Judge";
}


