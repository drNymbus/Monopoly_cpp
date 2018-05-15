#ifndef SFML_MODULE
#define SFML_MODULE
    #include <SFML/System.hpp>
    #include <SFML/Window.hpp>
    #include <SFML/Graphics.hpp>
#endif

class Controller {

	public:
		sf::Event ActualEvent;
		sf::Keyboard Keyboard;
		sf::Mouse Mouse;

		void get_event(sf::RenderWindow* w);
		void select_nb_players();
		sf::String get_user_name(unsigned int end_k);
		bool wait_action(unsigned int end_k);
};
