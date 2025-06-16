 #pragma once
 #include "Player.hpp"

 #ifndef ROLEFACTORY_HPP
 #define ROLEFACTORY_HPP

 namespace coup{

      class Game;

     class RoleFactory {
     public:
         static Player* createRandomPlayer(Game& game, const std::string& name);
     };



 }
 #endif //ROLEFACTORY_HPP
