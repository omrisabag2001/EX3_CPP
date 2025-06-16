#pragma once
#include "Player.hpp"

#ifndef SPY_HPP
#define SPY_HPP

namespace coup {
    class Spy : public Player {
        bool blockArrest_flag = true;
    public:
        Spy(Game& game,const string& name) : Player(game,name){}
         ~Spy() override = default;
        int peekCoins(Player &target) const;
        void BlockArrest(Player &target);
        void onTurnStart() override;
        std::string role() const override;

    };
}
#endif //SPY_HPP
