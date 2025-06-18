//gunrhxcd2001@gmail.com

#include "General.hpp"
#include "Player.hpp"
#include "Game.hpp"
#include <iostream>
#include <string>

using namespace coup;

// The General class inherits from Player and implements the undo method
// which allows the General to undo a coup action performed on another player.
void General::undo(Player& player) {
  if(!(player.getLastMove() == "coup")){throw std::runtime_error("General cannot undo "+player.getLastMove());}

  if(!this->active) {throw std::runtime_error("Player is not alive");}

   if(this->_coins >=5){
    if(special_ability == true) {
      this->_coins -= 5;
      special_ability = false;
      player.getLastCouped().reActive();
    }
    else {
      throw std::runtime_error("General can only undo coup once per turn");
    }
   }else  throw std::runtime_error( "not enough coins to undo coup");

}

string General::role() const {
    return "General";
}











