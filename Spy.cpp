// Email: gunrhxcd2001@gmail.com

#include <iostream>
#include "Spy.hpp"
#include "Player.hpp"
#include "Game.hpp"
using namespace coup;
using namespace std;

int Spy:: peekCoins(Player &target) const{
  if(this->GetName()==_game.turn()){
    return target.coins();
  }else{throw std::runtime_error("Not your turn!");}

}


void Spy::blockArrest(Player &target){
  if(this->GetName()==_game.turn()){
      if(this->active){
        if(target.isActive()){
          if(special_ability == true){
       		 target.blockArrest();
              special_ability=false;
        	  cout<<"Spy preformed BlockArrest"<<endl;

       	   }else{throw std::runtime_error("BlockArrest can be preformed only once each turn!");}

         }else{throw std::runtime_error("Target is not in the game");}

      	 }else{throw std::runtime_error(" your are dead");}

  	   }else{throw std::runtime_error("BlockArrest can be preformed only at your turn!");}

}


string Spy::role() const {
    return "Spy";
}

