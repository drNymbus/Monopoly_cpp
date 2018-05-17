#include "command.hpp"

bool command::wait_action(sf::Event e, sf::Keyboard::Key end_k) {
    if (sf::Keyboard::isKeyPressed(end_k)) return true;
    return false;
}
bool command::wait_action(sf::Event e, sf::Mouse::Button end_k, sf::Vector2i top_corner, sf::Vector2i bot_corner) {
    sf::Vector2i mPos = sf::Mouse::getPosition();
    if (mPos.x < top_corner.x) return false;
    if (mPos.y < top_corner.y) return false;

    if (mPos.x > bot_corner.x) return false;
    if (mPos.y > bot_corner.y) return false;

    if (!(sf::Mouse::isButtonPressed(end_k))) return false;
    return true;
}

bool command::get_user_name(sf::Event e, sf::Keyboard::Key end_k, std::string* name) {
    if (sf::Keyboard::isKeyPressed(end_k)) {
        return true;
    } else {
        if (e.type == sf::Event::TextEntered) {
            if (e.text.unicode < 128) {
                (*name).push_back(static_cast<char>(e.text.unicode));
            }
        }
        return false;
    }
}
bool command::get_user_name(sf::Event e, sf::Mouse::Button end_k, sf::Vector2i top_corner, sf::Vector2i bot_corner, std::string* name) {
    if (command::wait_action(e, end_k, top_corner, bot_corner)) {
        return true;
    } else {
        if (e.type == sf::Event::TextEntered) {
            if (e.text.unicode < 128) {
                (*name).push_back(static_cast<char>(e.text.unicode));
            }
        }
        return false;
    }
}

// bool command::select_board(std::string* n) {
//     *n = "maps/Original.txt";
//     return true;
// }
