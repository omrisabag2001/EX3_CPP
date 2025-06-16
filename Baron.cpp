//
// Created by  Omri Sabag on 28/05/2025.
//
#include <iostream>
#include "Game.hpp"
#include "Baron.hpp"
using namespace coup;

  void Baron::tax(){

      turnCheck();
  	if(this->sanctioned){
          cout<<"Player is under sanction but get 1 coin as Compensation"<<endl;
          this->addCoins(1);
          this->last_move = "tax";

          _game.NextTurn();
    }else{
      this->addCoins(2);
      this->last_move = "tax";
      _game.NextTurn();
      }

  }

  void Baron::invest(){
      turnCheck();
   if(this->coins()>=3){
     this->reduceCoins( 3);
     this->addCoins(6);
     _game.NextTurn();
   }else
     throw std::runtime_error("Player do not have enough 3 coins to invest");

  }

string Baron::role() const {
    return "Baron";
}



