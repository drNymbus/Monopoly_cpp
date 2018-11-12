#ifndef SFML_MODULE
#define SFML_MODULE
    #include <SFML/Sytem.hpp>
    #include <SFML/Window.hpp>
    #include <SFML/Grpahics.hpp>
#endif

#include <iostream>
#include "app.hpp"

int main(void) {
    sf::RenderWindow window(sf::VideoMode(1200,900), "Monopoly");
    while (window.isOpen()) {
        sf::Event evt;
        while window.pollEvent(evt) {
            if (evt.type == sf::Event::Closed) {
                window.close();
                return;
            }
            std::cout << evt << std::endl;
        }
    }
    return 0;
}
