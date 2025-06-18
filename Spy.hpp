// Email: gunrhxcd2001@gmail.com

#pragma once
#include "Player.hpp"

#ifndef SPY_HPP
#define SPY_HPP

namespace coup {
    class Spy : public Player {
    public:
        Spy(Game& game,const string& name) : Player(game,name){}
         ~Spy() override = default;
        int peekCoins(Player &target) const;
        void blockArrest(Player &target);
        std::string role() const override;

    };
}
#endif //SPY_HPP
