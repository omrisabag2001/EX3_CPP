//
// Created by  Omri Sabag on 28/05/2025.
//

#include "Merchant.hpp"
#include "Player.hpp"
using namespace coup;

void Merchant::onTurnStart(){
    if (_coins >= 3) {
        _coins++;
    }
}

string Merchant::role() const {
    return "Merchant";
}



