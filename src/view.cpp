#include "view.hpp"
using namespace view;

void Model_view::init(std::vector<Cell> b, std::vector<Player> p) {
    // Create a window with the same pixel depth as the desktop
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    window.create(sf::VideoMode(1024, 768, desktop.bitsPerPixel), "Monopoly");
}
