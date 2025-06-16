#pragma once
#include "Player.hpp"
#include "Game.hpp"
#ifndef GENERAL_HPP
#define GENERAL_HPP

namespace coup {
    class General : public Player {
    public:
        General(Game& game,const string& name): Player(game,name) {}
        ~General() override = default;
        void undo(Player&)override;
        std::string role() const override;









    };
}

#endif //GENERAL_HPP
