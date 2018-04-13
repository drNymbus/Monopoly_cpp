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
            unsigned int width_menu, width_board;
            void render_cell(Board::Cell c);
            void render_cell_menu(Board::Cell c, bool exposed);

        public:
            void init();
            void render(std::vector<Board::Cell> b, std::vector<Board::Player> p);
            void clean();
    };

    void message(std::string s);
    void yes_no(std::string yes, std::string no);

    void info_upgrade(Board::Cell c);
    void info_mortgage(Board::Cell c);
    void info_buy(Board::Cell c);
}
