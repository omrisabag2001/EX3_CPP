#pragma once
#include "Player.hpp"

#ifndef BARON_HPP
#define BARON_HPP


namespace coup {
    class Baron : public Player{
    public:
         Baron(Game& game,const string &name) : Player(game,name){};
        ~Baron() override = default;
        void invest();
        void tax() override;
        std::string role() const override;

    };
}



#endif //BARON_HPP
