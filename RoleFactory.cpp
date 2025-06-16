#include "RoleFactory.hpp"
#include "Governor.hpp"
#include "Spy.hpp"
#include "Baron.hpp"
#include "General.hpp"
#include "Judge.hpp"
#include "Merchant.hpp"
#include <random>
#include <vector>

using namespace coup;

Player* RoleFactory::createRandomPlayer(Game& game, const std::string& name) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, 5);

    int role = dist(gen);

    switch (role) {
        case 0: return new Governor(game, name);
        case 1: return new Spy(game, name);
        case 2: return new Baron(game, name);
        case 3: return new General(game, name);
        case 4: return new Judge(game, name);
        case 5: return new Merchant(game, name);
        default: throw std::runtime_error("Invalid role selected");
    }
}
