// Email: gunrhxcd2001@gmail.com

#pragma once
#include "Player.hpp"

#ifndef GOVERNOR_HPP
#define GOVERNOR_HPP

namespace coup {
    class Governor : public Player {
    public:
        Governor(Game &game, const string &name) : Player(game, name) {}

        ~Governor() override = default;
        void tax() override;
        void undo(Player& target) override;
        std::string role() const override;

    };
}


#endif //GOVERNOR_HPP
