#ifndef SFML_MODULE
#define SFML_MODULE
    #include <SFML/System.hpp>
    #include <SFML/Window.hpp>
    #include <SFML/Graphics.hpp>
#endif

#ifndef CONTROL_H
#define CONTROL_H

namespace command {
        /*
         * \param :
         * \brief :
         * \return:
         * DONE
         */
        static bool wait_action(sf::Event e, sf::Keyboard::Key end_k);
        static bool wait_action(sf::Event e, sf::Mouse::Button end_k, sf::Vector2i top_corner, sf::Vector2i bot_corner);

        /*
         * \param :
         * \brief :
         * \return:
         * DONE
         */
        static bool get_user_name(sf::Event e, sf::Keyboard::Key end_k, std::string* name);
        static bool get_user_name(sf::Event e, sf::Mouse::Button end_k, sf::Vector2i top_corner, sf::Vector2i bot_corner, std::string* name);

        /*
         * \param :
         * \brief :
         * \return:
         */
        // bool select_board(std::string* n);

        /*
         * \param :
         * \brief :
         * \return:
         */
        // bool command::select_nb_players(int* n);
}

#endif
