#pragma once
#include "Player.hpp"

#ifndef MERCHANT_HPP
#define MERCHANT_HPP

namespace coup {
    class Merchant : public Player {
    public:
        Merchant(Game& game,const string& name) : Player(game,name){}
        ~Merchant() override = default;
        void onTurnStart() override;
        std::string role() const override;



    };
}

#endif //MERCHANT_HPP
