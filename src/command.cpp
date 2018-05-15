#include "command.hpp"

void Controller::get_event(sf::RenderWindow* w) {
    w->pollEvent(Controller::ActualEvent);
}
