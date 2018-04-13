#include "view.hpp"
#include "model.hpp"
using namespace view;
using namespace Board;

void view::Model_view::init(std::vector<Cell> b, std::vector<Player> p) {
    // Create a window with the same pixel depth as the desktop
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    Model_view::w.create(sf::VideoMode(1024, 768, desktop.bitsPerPixel), "Monopoly");
}

void Model_view::render(std::vector<Cell> b, std::vector<Player> p) {
    unsigned int width, height;
    sf::Vector2u v_u =  Model_view::w.getSize();
    width = v_u.x; height = v_u.y;

    sf::Vector2f v_f;
    v_f.x = width_menu; v_f.y = height;
    sf::RectangleShape Menu = sf::RectangleShape(v_f);
}
