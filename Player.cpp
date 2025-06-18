// Email: gunrhxcd2001@gmail.com

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

// Constructor for Player class
// Initializes the player with a game reference and a name, adds the player to the game,
// and sets initial values for various attributes such as sanctioned, cant_arrest, another_turn,
// and active status.
Player::Player(Game &game, const string &name):_game(game),_name(name){
  _game.add_player(this);
  sanctioned = false;
  cant_arrest = false;
  another_turn = false;
  active = true;


  }





// check throw if player can preform gather action (look at sanctionCheck())
// if he can, it increases his coins by 1, sets the last move to "gather",
  void Player::gather(){

      sanctionCheck();

        this->_coins++;
         this->last_move = "gather";
 		 _game.NextTurn();
     
     
  }

// check throw if player can preform tax action (look at sanctionCheck())
  // if Baron player is sanctioned he gets 1 coin as compensation. makes this move
  // if player is Governor he gets 3 coins
  // otherwise he gets 2 coins
  // sets the last move to "tax" and calls NextTurn() on the game.
  void Player::tax(){
     sanctionCheck();

      this->addCoins(2);
       this->last_move = "tax";
      _game.NextTurn();
     

  }

// check throw if player can preform arrest action (look at arrestCheck())

// if he can, it reduces the target player coins by 1, adds 1 coin
 // if the target is type of General he gets his coin back from the player who took it.
 // so it pointless to give and take back 1 coin.
  // if the target is a Merchant so he pays 2 coins to the "game" instade of paying 1 to the player who arrested him
  // sets the last move to "arrest" and calls NextTurn() on the game.

  void Player::arrest(Player& target) {

      arrestCheck(target);


    if(target.role() == "General"){
      _game.last_arrested = &target;
       this->last_move = "arrest";
      _game.NextTurn();
      return;
     }
    if(target.role() == "Merchant"){
      if(target.coins()<2){throw std::invalid_argument("Merchant Target doesn't have 2 coins.");}
      target.reduceCoins(2);
      _game.last_arrested = &target;
      this->last_move = "arrest";
       _game.NextTurn();
       return;
    }

  
    _game.last_arrested = &target;
	  target._coins-=1;
    this->addCoins(1);
    this->last_move = "arrest";
    _game.NextTurn();
}


// check throw if player can preform bribe action (look at bribeCheck())
// if he can, it reduces his coins by 4, sets the another_turn to true (for next turn),
// and sets the last move to "bribe".
// this allows the player to take another 2 turns after preforming this action.

  void Player::bribe(){
      bribeCheck();
     	this->_coins-=4;
      this->another_turn = true;
      last_move = "bribe";
      
  }



// check throw if player can preform sanction action (look at sanctionCheck(target)) (overloading)
 // if he can, it reduces his coins by 3, sets the sanctioned flag to true,
 // and sets the last move to "sanction".
 // if target is Judge it reduces his coins by 4.
 // calls NextTurn() on the game.
void Player::sanction(Player& target) {
    sanctionCheck(target);

    if (target.role() == "Judge") {

        this->_coins-=4;
        target.sanctioned = true;
        this->last_move = "sanction";
        _game.NextTurn();

    }else{
        this->_coins-=3;
        target.sanctioned = true;
        this->last_move = "sanction";
         _game.NextTurn();
    }
    


}

// check if the player can preform coup
// if he can, it reduces his coins by 7, deactivates the target player,
// sets the last_couped to the target player, sets the last move to "coup",
// and calls NextTurn() on the game.

// if the target player is a General and has at least 5 coins and special ability is true,
// it auto revive himself by paying 5 coins, reactivating himself,
// and setting special_ability to false. that means if General used his special ability
// he can not use it again in the same turn.
// if the target player is a General and does not have enough coins or special ability is false
// it prints a message indicating that the player is totally dead.

// if the player is not active or it is not his turn, it throws an error.
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
         if(target._coins >=5&& target.special_ability){
           //todo ask if self-revive
           special_ability = false;
          target._coins -= 5;
          target.reActive();
          }else{cout<<"your are total dead"<<endl;}
      }
      _game.NextTurn();


     }else{throw std::runtime_error("You dont have enough coins to preform coup action");}
}








//returns the name of the player
  string Player::GetName() const{
     return this->_name;
 }


// used from Game class to open access for player to preform actions again
// after he was sanctioned or blocked from arresting by Spy.
  void Player::openAccess(){
    this->sanctioned = false;
    this->cant_arrest = false;

  }


// checks if the player has another turn (if he used bribe action)
// returns true if he has another turn, false otherwise.
// this is used to allow the player to take another turn after using bribe action.
// used in Game class to check if the player can take another turn
   bool Player::hasAnotherTurn(){
     return this->another_turn;
   }

// sets the another_turn flag to false, indicating that the player does not have another turn anymore.
// this is used to reset the player's ability to take another turn after he has used it.
//in addition that's how Judge undo bribe action works.
   void Player::setAnotherTurn(){
      this->another_turn = false;
   }




   // deActive function sets the active flag of the target player to false,
   // indicating that the player is no longer active in the game (dead).
   void Player::deActive(Player& target){
     target.active=false;
   _game.lastDead(target);}




// returns the number of coins the player has
// this is used to check if the player has enough coins to preform actions such as coup
   int Player::coins(){
     return this->_coins;
   }


   // adds coins to the player's coin count
   void Player::addCoins(int coins){
      if(coins < 0){
        throw std::invalid_argument("Cannot add negative coins");
      }
      this->_coins+=coins;

   }

    // reduces coins from the player's coin count
   void Player::reduceCoins(int coins){
      if(coins < 0){
        throw std::invalid_argument("Cannot reduce negative coins");
      }
      if(this->_coins < coins){
        throw std::runtime_error("Not enough coins to reduce");
      }
     this->_coins-=coins;
   }

// ------------------------------------- Checks for Player Actions ----------------------------------------------------------------

   void Player::arrestCheck(Player& target)const {
          turnCheck();
        if(!target.isActive()){
        throw std::runtime_error("Target player is dead and canot be arrested");
        }

         if (_game.last_arrested == &target) {
        throw std::runtime_error("Player canot be arrested twice in a row");
        }
       if(this->cant_arrest){
       throw std::runtime_error("Spy avoid you to preform arrest move");
        }
        if (target.coins() < 1) {
      throw std::runtime_error("Target player has no coins, try again");
    }
    
   }

// check's if the player has enough coins to preform bribe action
   void Player::bribeCheck()const{
      turnCheck();
      if(this->_coins<4){
        throw std::runtime_error("Player has no money for this action");
        
      }
    }



// check all the things that must be checked before player can preform any action by the player who wants to preform a back action  
  void Player::turnCheck()const{
    if(!this->isActive()){ throw std::runtime_error("your not active!");}

    if(!(this->GetName() == _game.turn())){ throw std::runtime_error("Not your turn!");}


    if(this->_coins>=10){throw std::invalid_argument("Player must preform Coup");}
  }




// check if player is sanctioned (overloading)
  void Player::sanctionCheck()const{
     turnCheck();
     
    if(this->sanctioned){
      throw std::runtime_error("Player is sanctioned and can not preform this action");
    }
  }




  // Check if target can be sanctioned by someone (overloadding)
    void Player::sanctionCheck(Player& target)const{
            turnCheck();
      if(!target.isActive()){
        throw std::runtime_error("Target player is dead and canot be sanctioned");
      }
      if(target.sanctioned == true){
        throw std::runtime_error("Target player is already sanctioned");
      }
        if(this->_coins<3){
        throw std::runtime_error("Player has no money for this action");
      }
      if (target.role() == "Judge" && this->_coins < 4)
      {
        throw std::runtime_error("Player has no money for this action on Judge");
        
      }
      
    }








