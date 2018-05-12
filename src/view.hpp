#ifndef SFML_MODULE
#define SFML_MODULE
    #include <SFML/System.hpp>
    #include <SFML/Window.hpp>
    #include <SFML/Graphics.hpp>
#endif

#include "model.hpp"

#define SCREEN_WIDTH 1600
#define SCREEN_HEIGHT 900

namespace view {
    class Model_view {
        private:
            sf::Window w;
        };
}
