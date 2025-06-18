//// Email: gunrhxcd2001@gmail.com

#include <SFML/Graphics.hpp>
#include "Game.hpp"
#include "RoleFactory.hpp"
#include "Governor.hpp"
#include "Spy.hpp"
#include "General.hpp"
#include "Judge.hpp"
#include "Merchant.hpp"
#include "Baron.hpp"
#include <iostream>
#include <vector>

using namespace std;
using namespace coup;

struct ActionButton {
    string action;
    sf::RectangleShape shape;
    sf::Text label;
};

struct PlayerCard {
    Player* player;
    vector<ActionButton> buttons;
    sf::RectangleShape background;
    int y_position;
};

vector<string> getActionsForRole(const string& role) {
    if (role == "Spy") return {"peekCoins", "blockArrest"};
    if (role == "Baron") return {"invest"};
    if (role == "Merchant") return {};
    return {"undo"};
}

void createActionButtons(PlayerCard& card, const sf::Font& font, int x_start) {
    vector<string> actions = getActionsForRole(card.player->role());
    actions.insert(actions.begin(), {"gather", "tax", "bribe", "arrest", "sanction", "coup"});
    int x = x_start;
    for (const string& act : actions) {
        ActionButton btn;
        btn.action = act;
        btn.shape.setSize(sf::Vector2f(90, 30));
        btn.shape.setPosition(x, card.y_position + 50);
        btn.shape.setFillColor(sf::Color(200, 200, 250));
        btn.label.setFont(font);
        btn.label.setString(act);
        btn.label.setCharacterSize(14);
        btn.label.setPosition(x + 5, card.y_position + 55);
        btn.label.setFillColor(sf::Color::Black);
        card.buttons.push_back(btn);
        x += 100;
    }
}

int countAlivePlayers(const vector<Player*>& players) {
    int count = 0;
    for (auto* p : players) {
        if (p->isActive()) count++;
    }
    return count;
}

Player* getWinner(const vector<Player*>& players) {
    for (auto* p : players) {
        if (p->isActive()) return p;
    }
    return nullptr;
}

int main() {
    {
    Game game;
    vector<PlayerCard> playerCards;
    int playerCounter = 1;
    bool gameStarted = false;
    bool gameOver = false;

    Player* pendingActor = nullptr;
    string pendingAction = "";

    sf::RenderWindow window(sf::VideoMode(1400, 800), "Coup - GUI");
    sf::Font font;
    if (!font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf")) {
        cerr << "Font load failed" << endl;
        return 1;
    }

    sf::Text title("Coup GUI", font, 32);
    title.setPosition(460, 10);
    title.setFillColor(sf::Color::Black);

    sf::Text messageText("", font, 20);
    messageText.setPosition(50, 760);
    messageText.setFillColor(sf::Color::Red);
    string last_message = "";

    sf::RectangleShape addButton(sf::Vector2f(150, 40));
    addButton.setPosition(20, 10);
    addButton.setFillColor(sf::Color(180, 220, 180));
    sf::Text addLabel("Add Player", font, 18);
    addLabel.setPosition(30, 15);
    addLabel.setFillColor(sf::Color::Black);

    sf::RectangleShape startButton(sf::Vector2f(150, 40));
    startButton.setPosition(190, 10);
    startButton.setFillColor(sf::Color(180, 180, 255));
    sf::Text startLabel("Start Game", font, 18);
    startLabel.setPosition(200, 15);
    startLabel.setFillColor(sf::Color::Black);

    sf::RectangleShape exitButton(sf::Vector2f(150, 40));
    exitButton.setPosition(600, 380);
    exitButton.setFillColor(sf::Color(255, 100, 100));
    sf::Text exitLabel("Exit", font, 22);
    exitLabel.setPosition(650, 385);
    exitLabel.setFillColor(sf::Color::White);

    sf::Text gameOverText("", font, 32);
    gameOverText.setPosition(400, 300);
    gameOverText.setFillColor(sf::Color::Red);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2f mouse(sf::Mouse::getPosition(window));

                if (!gameStarted && addButton.getGlobalBounds().contains(mouse)) {
                    if (game.players().size() < 6) {
                        string name = "Player" + to_string(playerCounter++);
                        Player* newP = RoleFactory::createRandomPlayer(game, name);
                        PlayerCard card;
                        card.player = newP;
                        card.y_position = 70 + (game.players().size() - 1) * 110;
                        card.background.setSize(sf::Vector2f(1300, 100));
                        card.background.setPosition(50, card.y_position);
                        card.background.setOutlineColor(sf::Color::Black);
                        card.background.setOutlineThickness(1);
                        playerCards.push_back(card);
                        last_message = "Added " + newP->GetName() + " as " + newP->role();
                    } else {
                        last_message = "Max 6 players reached.";
                    }
                }

                if (!gameStarted && startButton.getGlobalBounds().contains(mouse)) {
                    if (game.players().size() >= 2) {
                        gameStarted = true;
                        for (auto& card : playerCards)
                            createActionButtons(card, font, 500);
                        last_message = "Game started!";
                    } else {
                        last_message = "Need at least 2 players.";
                    }
                }

                if (gameOver && exitButton.getGlobalBounds().contains(mouse)) {
                    window.close();
                }

                if (gameStarted && !gameOver) {
                    for (auto& card : playerCards) {
                        for (auto& btn : card.buttons) {
                            if (btn.shape.getGlobalBounds().contains(mouse)) {
                                try {
                                    if (btn.action == "gather") card.player->gather();
                                    else if (btn.action == "tax") card.player->tax();
                                    else if (btn.action == "bribe") card.player->bribe();
                                    else if (btn.action == "invest" && card.player->role() == "Baron")
                                        ((Baron*)card.player)->invest();
                                    else {
                                        pendingActor = card.player;
                                        pendingAction = btn.action;
                                        last_message = "Click on target for " + pendingAction;
                                    }
                                    if (btn.action != "arrest" && btn.action != "sanction" &&
                                        btn.action != "coup" && btn.action != "undo" &&
                                        btn.action != "peekCoins" && btn.action != "blockArrest") {
                                        pendingActor = nullptr;
                                        pendingAction = "";
                                    }
                                } catch (const exception& e) {
                                    last_message = string("Error: ") + e.what();
                                    pendingActor = nullptr;
                                    pendingAction = "";
                                }
                            }
                        }
                    }

                    for (auto& card : playerCards) {
                        if (card.background.getGlobalBounds().contains(mouse)) {
                            if (pendingActor && card.player != pendingActor) {
                                try {
                                    if (pendingAction == "arrest") pendingActor->arrest(*card.player);
                                    else if (pendingAction == "sanction") pendingActor->sanction(*card.player);
                                    else if (pendingAction == "coup") pendingActor->coup(*card.player);
                                    else if (pendingAction == "undo") pendingActor->undo(*card.player);
                                    else if (pendingAction == "peekCoins" && pendingActor->role() == "Spy")
                                        ((Spy*)pendingActor)->peekCoins(*card.player);
                                    else if (pendingAction == "blockArrest" && pendingActor->role() == "Spy")
                                        ((Spy*)pendingActor)->blockArrest(*card.player);
                                    last_message = pendingActor->GetName() + " performed " + pendingAction + " on " + card.player->GetName();
                                } catch (const exception& e) {
                                    last_message = string("Error: ") + e.what();
                                }
                                pendingActor = nullptr;
                                pendingAction = "";
                            }
                        }
                    }
                }
            }
        }

        if (gameStarted && !gameOver && countAlivePlayers(game.get_players()) == 1) {
            gameOver = true;
            Player* winner = getWinner(game.get_players());
            if (winner) gameOverText.setString("Game Over! Winner: " + winner->GetName());
            else gameOverText.setString("Game Over!");
        }

        window.clear(sf::Color::White);
        window.draw(title);

        if (!gameStarted) {
            window.draw(addButton);
            window.draw(addLabel);
            if (game.players().size() >= 2) {
                window.draw(startButton);
                window.draw(startLabel);
            }
        }

        for (auto& card : playerCards) {
            Player* p = card.player;
            card.background.setFillColor(
                !p->isActive() ? sf::Color(200, 200, 200) :
                (p == &game.CurrentPlayer() ? sf::Color(150, 200, 255) : sf::Color(240, 240, 240))
            );
            window.draw(card.background);

            string info = p->GetName() + " (" + p->role() + ") - " + to_string(p->coins()) + " coins";
            if (!p->isActive()) info += " [OUT]";
            sf::Text infoText(info, font, 18);
            infoText.setPosition(60, card.y_position + 10);
            infoText.setFillColor(sf::Color::Black);
            window.draw(infoText);

            if (gameStarted && !gameOver) {
                for (auto& btn : card.buttons) {
                    window.draw(btn.shape);
                    window.draw(btn.label);
                }
            }
        }

        if (gameOver) {
            window.draw(gameOverText);
            window.draw(exitButton);
            window.draw(exitLabel);
        }

        messageText.setString(last_message);
        window.draw(messageText);
        window.display();
    }
}
    return 0;
}
