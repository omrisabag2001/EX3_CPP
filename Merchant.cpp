// Email: gunrhxcd2001@gmail.com

#include <iostream>
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



