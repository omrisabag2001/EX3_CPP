//
// Created by  Omri Sabag on 08/05/2025.
//
#include "Player.hpp"

#ifndef JUDGE_HPP
#define JUDGE_HPP


namespace coup {
    class Judge : public Player {
    public:
        Judge(Game& game,const string& name) : Player(game,name){}
         ~Judge() override = default;
        void undo(Player &target) override; // can cancel bribe
        std::string role() const override;

    };
}
#endif //JUDGE_HPP
