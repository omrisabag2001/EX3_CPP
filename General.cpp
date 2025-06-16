//
// Created by  Omri Sabag on 28/05/2025.
//

#include "General.hpp"
#include "Player.hpp"
#include "Game.hpp"
#include <iostream>
#include <string>

using namespace coup;


void General::undo(Player& player) {
  if(!(player.getLastMove() == "coup")){throw std::runtime_error("General cannot undo "+player.getLastMove());}


//  if(player.getLastCouped().GetName() == this->GetName() && !(this->active)){
//    if(this->_coins >=5){
//      this->_coins -= 5;
//      this->reActive();
//    }else  throw std::runtime_error( "not enough coins to un coup your self!");
//  }


  if(!this->active) {
    throw std::runtime_error("Player is not alive");
  }


   if(this->_coins >=5){
      this->_coins -= 5;
      player.getLastCouped().reActive();
   }else  throw std::runtime_error( "not enough coins to undo coup");

}

string General::role() const {
    return "General";
}











