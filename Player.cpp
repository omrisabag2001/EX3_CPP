#include <iostream>
#include "Player.hpp"
#include "Game.hpp"
#include "Judge.hpp"
#include "General.hpp"
#include "Merchant.hpp"
#include "Baron.hpp"
#include <string>
using namespace std;
using namespace coup;


Player::Player(Game &game, const string &name):_game(game),_name(name){
  _game.add_player(this);
  sanctioned = false;
  cant_arrest = false;
  another_turn = false;
  active = true;


  }


  void Player::gather(){
      turnCheck();
 	 if(this->sanctioned){
          throw std::runtime_error( "Player is sanctioned: and can not preform this move");
 	 }else{
          this->_coins++;
         this->last_move = "gather";
         this->openAccess();
 		 _game.NextTurn();
     }
  }


  void Player::tax(){
      turnCheck();
  	if(this->sanctioned){
      throw std::runtime_error("Player is sanctioned: and can not preform this move");
    }else{
      this->addCoins(2);
       this->last_move = "tax";
       this->openAccess();
      _game.NextTurn();
     }

  }

  void Player::arrest(Player& target) {

      turnCheck();

     if (_game.last_arrested == &target) {
        throw std::runtime_error("Player canot be arrested twice in a row");
    }

     if(this->cant_arrest){
       throw std::runtime_error("Spy avoid you to preform arrest move");
     }

    // if the target is type of General so he get his coin back from the player who took it.
     // so it pointless to give and take back 1 coin.
    if(target.role() == "General"){
      _game.last_arrested = &target;
       this->last_move = "arrest";
       this->openAccess();
      _game.NextTurn();
      return;
     }
     // if the target is a Merchant so he pays 2 coins to the "game" instade of paying 1 to the player who arrested him
    if(target.role() == "Merchant"){
      if(target.coins()<2){throw std::invalid_argument("Merchant Target doesn't have 2 coins.");}
      target.reduceCoins(2);
      _game.last_arrested = &target;
      this->last_move = "arrest";
      this->openAccess();
       _game.NextTurn();
       return;
    }


    _game.last_arrested = &target;
	target._coins-=1;
    this->addCoins(1);
    this->last_move = "gather";
    this->openAccess();
    _game.NextTurn();
}


  void Player::bribe(){
      turnCheck();

      if(this->_coins>=4){
     	this->_coins-=4;
        this->another_turn = true;
        last_move = "bribe";
      }else
       throw std::runtime_error("Player has no money for this action");
  }




void Player::sanction(Player& target) {

      turnCheck();

    if (target.role() == "Judge") {
      if(this->_coins>=4){
        this->_coins-=4;
        target.sanctioned = true;
        this->last_move = "sanction";
        _game.NextTurn();


        }else{throw std::runtime_error("you dont have enough money to preform this action on judge");}
    }else if(this->_coins>=3){
        this->_coins-=3;
        target.sanctioned = true;
        this->last_move = "sanction";
         _game.NextTurn();
    }else {throw std::runtime_error("you dont have enough money to preform this action");}

	this->openAccess();

}

void Player::coup(Player& target) {
    if(!this->isActive()){
      throw std::runtime_error("Your dead!");
    }
    if(!(this->GetName() == _game.turn())){
      throw std::runtime_error("Not your turn!");
    }
    if(!(target.isActive())){
      throw std::runtime_error("Target player is dead and canot be couped");
    }
    if (this->coins()>=7){
      this->reduceCoins(7);

      this->deActive(target);
      last_couped = &target;
      this->last_move = "coup";
      cout<<"Player: "+this->_game.turn()+" preformed coup"<<endl;

      if(target.role() == "General"){
         if(target._coins >=5){
           //todo ask if self-revive
          target._coins -= 5;
          target.reActive();
          }else{cout<<"your are total dead"<<endl;}
      }
      _game.NextTurn();


     }else{throw std::invalid_argument("You dont have enough coins to preform coup action");}
}









  string Player::GetName() const{
     return this->_name;
 }



  void Player::openAccess(){
    this->sanctioned = false;
    this->cant_arrest = false;

  }


  void Player::turnCheck(){
    if(!this->isActive()){ throw std::runtime_error("your not active!");}

    if(!(this->GetName() == _game.turn())){ throw std::runtime_error("Not your turn!");}


    if(this->_coins>=10){throw std::invalid_argument("Player must preform Coup");}
  }

   bool Player::hasAnotherTurn(){
     return this->another_turn;
   }

   void Player::setAnotherTurn(){
      this->another_turn = false;
   }

   void Player::deActive(Player& target){
     target.active=false;
   _game.lastDead(target);}

   int Player::coins(){
     return this->_coins;
   }
   void Player::addCoins(int coins){
      this->_coins+=coins;
   }
   void Player::reduceCoins(int coins){
     this->_coins-=coins;
   }









