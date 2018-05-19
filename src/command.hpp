#ifndef SFML_MODULE
#define SFML_MODULE
    #include <SFML/System.hpp>
    #include <SFML/Window.hpp>
    #include <SFML/Graphics.hpp>
#endif

#ifndef CONTROL_H
#define CONTROL_H

class Controller {
public:
    sf::Event Event;

    /*
     * \param :
     * \brief :
     * \return:
     * DONE
     */
    bool wait_user_action(sf::Keyboard::Key end_k) {
        if (Controller::Event.type == sf::Event::KeyPressed) {
            if (Controller::Event.key.code == end_k) return true;
        }
        return false;
     }
    bool wait_user_action(sf::Mouse::Button end_k) {
        if(Controller::Event.type == sf::Event::MouseButtonPressed) {
            if (Controller::Event.mouseButton.button == end_k) return true;
        }
        return false;
     }

    /*
     * \param :
     * \brief :
     * \return:
     * DONE
     */
    bool get_user_name(sf::Keyboard::Key end_k, std::string* name) {
         if (Controller::wait_user_action(end_k)) {
             return true;
         } else {
             if (Controller::Event.type == sf::Event::TextEntered) {
                 if (Controller::Event.text.unicode < 128) {
                     (*name).push_back(static_cast<char>(Controller::Event.text.unicode));
                 }
             }
             return false;
         }
     }
    bool get_user_name(sf::Mouse::Button end_k, std::string* name) {
         if (Controller::wait_user_action(end_k)) {
             return true;
         } else {
             if (Controller::Event.type == sf::Event::TextEntered) {
                 if (Controller::Event.text.unicode < 128) {
                     (*name).push_back(static_cast<char>(Controller::Event.text.unicode));
                 }
             }
             return false;
         }
     }

    /*
     * \param :
     * \brief : a refaire nul a chier !!!
     * \return:
     */
    template <typename T> T select_value(sf::Window* w, T* values, unsigned int size) {
        sf::Event e = Controller::Event;
        sf::Vector2u Coord;

        sf::Vector2u mPos;
        mPos.x = e.mouseMove.x, mPos.y = e.mouseMove.y;
        std::cout << "mPos: " << mPos.x << ',' << mPos.y << std::endl;

        sf::Vector2u sSize = w->getSize();
        unsigned int hStep = 70, wStep = sSize.x/6;

        for (int x = sSize.x; x >= 0; x -= wStep) {
            if (mPos.x > x) {
                std::cout << "x:" << x << '\t';
                Coord.x = x/wStep;
                break;
            }
        }
        std::cout << std::endl;
        for (int y = sSize.y; y >= 0; y -= hStep) {
            if (mPos.y > y) {
                std::cout << "y:" << y << '\t';
                Coord.y = y/hStep;
                break;
            }
        }
        std::cout << std::endl;

        std::cout << Coord.x << ", " << Coord.y << '\n';
        std::cout << "Clicked on :" << values[(wStep * Coord.y) + Coord.x] << std::endl;
        if (sSize.x/wStep * Coord.y + Coord.x < size) {
            return values[((sSize.x/wStep) * Coord.y) + Coord.x];
        }
    }

    /*
     * \param :
     * \brief :
     * \return:
     */
    // bool command::select_nb_players(int* n);
};

#endif
