// Email: gunrhxcd2001@gmail.com

#pragma once
#include "Player.hpp"

#ifndef BARON_HPP
#define BARON_HPP


namespace coup {
    class Baron : public Player{
    public:
         Baron(Game& game,const string &name) : Player(game,name){};
        ~Baron() override = default;
        // Baron can invest 3 coins and get 6 coins
        // if he has 3 coins and can use his special ability.
        // if he has not enough coins or can not use his special ability it will throw an error.
        // after invest action player can not use his special ability again this turn.
        void invest();
         // Baron can preform tax action and get 2 coins or 1 coin if sanctioned
        void tax() override;
        // returns the role of the player as a string "Baron"
        std::string role() const override;

    };
}



#endif //BARON_HPP
