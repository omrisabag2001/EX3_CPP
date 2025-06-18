// Email: gunrhxcd2001@gmail.com

#include <iostream>

#include "Judge.hpp"

using namespace coup;
void Judge::undo(Player &target){ // can cancel bribe
  if(!target.isActive()){
    throw std::runtime_error("Player is not alive");
  }

  if(target.getLastMove() == "bribe"){
    if (special_ability==true) {
    target.setAnotherTurn();
    special_ability = false;
    }else{throw std::runtime_error("Judge can only undo bribe once per round");}
  }else
    throw std::runtime_error("Judge cannot undo "+target.getLastMove() );

  }


string Judge::role() const {
    return "Judge";
}


