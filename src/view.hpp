#ifndef SFML_MODULE
#define SFML_MODULE
    #include <SFML/System.hpp>
    #include <SFML/Window.hpp>
    #include <SFML/Graphics.hpp>
#endif

#include "model.hpp"

class Model_view {
    public:
        unsigned int Width,Height;
        sf::Vector2i Cursor;//useful to draw an highlighted item;but maybe not necessary

        unsigned int MarginLeft;

        //width and height of cells
        //in selection panel (=Sel) and during game (=Cell)
        unsigned int wSel, hSel;
        unsigned int wCell, hCell;

    void init(sf::Window* w);
    // void load_font();
    template <typename T> void render_select(sf::Window* w, sf::Vector2i c, T* values);

    private:
        void render_cell(Board::Cell c, sf::Vector2i tCorner);
};
