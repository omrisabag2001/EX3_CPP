// Email: gunrhxcd2001@gmail.com

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
    if(special_ability==true){
      this->last_move = "invest";
     this->reduceCoins( 3);
     this->addCoins(6);
     _game.NextTurn();
      special_ability = false;
    }else{
      throw std::runtime_error("Baron can only invest once per turn");
    }
   }else
     throw std::runtime_error("Player do not have enough 3 coins to invest");

  }

string Baron::role() const {
    return "Baron";
}



