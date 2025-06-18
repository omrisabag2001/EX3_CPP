// tests.cpp
// Email: gunrhxcd2001@gmail.com
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "Game.hpp"
#include "Governor.hpp"
#include "Spy.hpp"
#include "Baron.hpp"
#include "General.hpp"
#include "Judge.hpp"
#include "Merchant.hpp"

using namespace coup;


//---------------------------------Turn Tests----------------------------------------------------------------------------
   // we will not delete players in the end of the test
    // this is for the test to work with the players created in the test cases.
TEST_CASE("Basic turn's test") {

    Game game;
    game.owns_players = false;
    Governor gov(game, "gov");
    Spy spy(game, "spy");
    CHECK(game.turn() == "gov");
    gov.gather();
    CHECK(game.turn() == "spy");
    spy.gather();
    // not spy turn..
    CHECK_THROWS(spy.gather());
}

TEST_CASE("Extra turn test") {
    Game game;
    game.owns_players = false;
    Governor gov(game, "gov");
    Judge Judge(game, "judge");

    // gov's turn makes bribe what gives him 2 turn's when bribe action is not a turn!!
    CHECK(game.turn() == "gov");
    gov.addCoins(4);
    gov.bribe();

    //after bribe gov has 2 turns.
    CHECK(game.turn() == "gov");

    // first turn
    gov.gather();
    CHECK(game.turn() == "gov");

    //second turn
    gov.gather();


    CHECK(game.turn() == "judge");
    Judge.gather();

    // extra turn + undo test
    gov.addCoins(2);
    gov.bribe();
    Judge.undo(gov);
    CHECK(game.turn() == "gov");
    gov.gather();
    CHECK(game.turn() == "judge");


}

//---------------------------------Coup Tests-------------------------------------------------------------------

TEST_CASE("coup turn's test") {
    Game game;
    game.owns_players = false;
    Governor gov(game, "gov");
    Spy spy(game, "spy");
    General general(game, "general");

    // adding coins for coup
    gov.addCoins(6);
    CHECK(game.turn() == "gov");
    gov.gather(); // gov has 7 coins to preform coup
    CHECK(game.turn() == "spy");
    spy.gather();
    CHECK(game.turn() == "general");
    general.gather();
 //------------------ round 1 goes well-------------
    gov.coup(spy);
    cout<<game.turn()<<endl;
    // now its spy's turn but he got couped and not active so its not his turn

    CHECK(spy.isActive() == false);
    CHECK_THROWS(spy.gather());
    CHECK(game.turn() == "general");

}





/**
* This test demonstrate the following situation:
There are 4 player's active
when 2 Player's has the ablility to preform coup on other players
and 1 general that can undo there coup

***----The rule as we asked to do: undo action can be made til the player who can be undo of his action play's again---***


the test make sure that we canot revive player who is total dead
that's means:
undo coup when the player who did it play's again




*/
TEST_CASE("coup check") {
    Game game;
    game.owns_players = false;
  Governor gov(game, "Gov");
  General general(game, "Gen");
  Spy spy(game, "spy");
  Baron baron(game, "Baron");


  gov.addCoins(7);
  general.addCoins(5);
  spy.addCoins(7);

  gov.coup(baron);
  // prefer not to undo gov
  general.gather();
  spy.coup(gov);

  CHECK_THROWS(baron.gather());
  CHECK_THROWS(gov.gather());
	// make sure that we can't undo coup on him
  CHECK(gov.getLastMove()=="");
  // want's to undo on spy what revive gov
  CHECK_THROWS(general.undo(gov));
  general.undo(spy);
  CHECK(gov.isActive() == true);

}

// test that we can preform undo coup on player who is currenly dead that his last move was coup
//and his turn didnt came yet!


TEST_CASE("coup check") {
    Game game;
    game.owns_players = false;
  Governor gov(game, "Gov");
  General general(game, "Gen");
  Spy spy(game, "spy");
  Baron baron(game, "Baron");


  gov.addCoins(7);
  general.addCoins(5);
  spy.addCoins(7);

  gov.gather();
  general.gather();

  spy.coup(baron);
  CHECK_THROWS(baron.gather());


  gov.coup(spy);
   // spy is currenly dead
  CHECK(spy.isActive() == false);

  general.undo(spy);
  CHECK(baron.isActive() == true);

}


TEST_CASE("when player has 10 coins he must preform coup!") {
    Game game;
    game.owns_players = false;
  Spy spy(game, "spy");
  spy.tax();
  Governor gov(game, "Gov");
  gov.addCoins(10);
  CHECK_THROWS(gov.gather());
  CHECK_THROWS(gov.sanction(spy));
  CHECK_THROWS(gov.arrest(spy));
  CHECK_THROWS(gov.tax());
  CHECK_THROWS(gov.bribe());


  }



//---------------------------------Role test's--------------------------------------------------------------------------


/*
						Governor
 1. get 3 coins instaed of 2 when his action is tax
 2.  in additon he can undo tax action on other players
 3. till there next turn
*/
TEST_CASE("Governor Role check") {
    Game game;
    game.owns_players = false;
  Governor gov(game, "gov");
  Spy spy(game, "spy");
  Baron baron(game, "baron");

// 1.
  gov.tax();
  CHECK(gov.coins() == 3);
//	2.
  spy.tax();
  CHECK(spy.coins() == 2);
  gov.undo(spy);
  CHECK(spy.coins() == 0);

//	3.
  baron.tax();
  gov.tax();
  spy.tax();
  baron.gather();
  CHECK_THROWS(gov.undo(baron)); // canot do


}
TEST_CASE("Governor tax and undo") {
    Game game;
    game.owns_players = false;
    Governor gov1(game, "Gov1");
    Governor gov2(game, "Gov2");
    gov1.tax();
    gov2.tax();
    gov1.undo(gov2);
    CHECK(gov2.coins() == 0);
}





/*
						SPY
 1. can see other players coins how many times he wants!, when his turn comes

 2. can avoid player from arrest action when his turn comes
	and can preform it just once each turn!

	those action not consider his actual turn
*/



TEST_CASE("Spy Role check") {
    Game game;
    game.owns_players = false;
  Governor gov(game, "gov");
  Spy spy(game, "spy");
  Baron baron(game, "Baron");

  CHECK_THROWS(spy.peekCoins(gov));
  gov.tax();
  CHECK(spy.peekCoins(gov) == 3);
  spy.blockArrest(gov);
  CHECK_THROWS(spy.blockArrest(baron));

  CHECK(game.turn() == "spy");
  spy.gather();

 baron.gather();

 // gov has 3 should able to preform arrest action
 // but he can't due spy
 CHECK_THROWS(gov.arrest(spy));

}

/*
						Baron
 1. can Invest 3 coins and get 6
 2. if he is under sanction he get 1 coin  as Compensation just if he use tax action
	gather action will not spend his it will tell him he is under sanction like other players.

*/

TEST_CASE("Baron Role check") {
    Game game;
    game.owns_players = false;
   Baron baron(game, "baron");
   Governor gov(game, "gov");
   Baron baron2(game, "baron2");

 // he must have 3 coins now he has 0.
 CHECK_THROWS(baron.invest());
 // adding coins for the test.
 baron.addCoins(3);

 CHECK(baron.coins() == 3);
 baron.invest();
 CHECK(baron.coins() == 6);

 gov.addCoins(3);
 gov.sanction(baron2);
 // canot do becuase he is under sanction
 CHECK_THROWS(baron2.gather());
 baron2.tax();
 CHECK(baron2.coins() == 1);


  }



/*
						General
 1.can pay 5 coins to avoid coup against him self or other players

 2. if he got arrested by other player he gets his coin back from the player who took it
*/

TEST_CASE("General self undo") {
    Game game;
    game.owns_players = false;
    Governor gov(game, "gov");
   gov.addCoins(7);


General general(game, "general");
 general.addCoins(5);

 gov.coup(general);

CHECK(gov.coins()==0);
CHECK(general.coins()==0);
CHECK(general.isActive()==true);
CHECK(game.turn() == "general");


 }



TEST_CASE("General undo other player") {
    Game game;
    game.owns_players = false;
  Governor gov(game, "gov");
   gov.addCoins(7);

General general(game, "general");
 general.addCoins(5);

 Baron baron(game, "baron");

 gov.coup(baron);
 CHECK(baron.isActive()==false);
 general.undo(gov);
 CHECK(baron.isActive()==true);
CHECK(general.coins()==0);

 }

 // todo what happend if the other player has 0 coins and player arrest him he has -1?

 TEST_CASE("General coin back") {
    Game game;
    game.owns_players = false;
 General general(game, "general");
 Governor gov(game, "gov");
 // general has 1 coin
 general.gather();
 gov.arrest(general);
 CHECK(general.coins()==1);
 CHECK(gov.coins()==0);

 }




 /*
						Judge
1. can cancel bribe action of other players till the player who did it get his turn again.
 the player who bribed losing his coin's (4) and lose his second turn

2. if player made sanction move on Judge the player who did it pays another coin to preform it (4 coins)

*/

 TEST_CASE("Judge undo bribe") {
    Game game;
    game.owns_players = false;
    Governor gov(game, "Gov");
    Judge judge(game, "Judge");
    gov.addCoins(4);
    gov.bribe();
    judge.undo(gov);
    CHECK(gov.hasAnotherTurn() == false);
}

TEST_CASE("Judge got sanction") {
  Game game;
    game.owns_players = false;
  //1.
    Governor gov(game, "Gov");
    Baron baron(game, "baron");
    Judge judge(game, "Judge");
    gov.addCoins(3);
    gov.sanction(baron); // goes well!
    CHECK(gov.coins()==0);
//2.
    baron.addCoins(4);
	baron.sanction(judge);
    CHECK(baron.coins()==0);


}

 /*
							Merchant
1. if Merchant start turn with 3 coins he get 1 free when his turn start

2. if Merchent is under arrest he pays 2 coins to the game instade of paying 1 to the player who did it to him

*/
 // todo what happend if Merchent dosent have 2 coins to pay?


TEST_CASE("Merchant coin bounus") {
    Game game;
    game.owns_players = false;
  //1.
	  Merchant merchant(game, "merchant");
    Judge judge(game, "Judge");
    merchant.addCoins(2);
    merchant.gather();
    CHECK(merchant.coins()==3);
    judge.gather();
    CHECK(merchant.coins()==4);
    merchant.gather();
    }


TEST_CASE("Merchant under arrest") {
  Game game;
    game.owns_players = false;
  
 //2.
	Merchant merchant(game, "merchant");
    Judge judge(game, "Judge");
    merchant.tax();
    CHECK(merchant.coins()==2);
    judge.arrest(merchant);
    CHECK(merchant.coins()==0);

}









