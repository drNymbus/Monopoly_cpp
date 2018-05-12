#include <SFML/Window.hpp>

#include <iostream>
#include <string>

#include "model.hpp"

namespace command {
	class Controler {};
	Board::Cell mouse_cell_pos();

	unsigned int ask_number(std::vector<int> value);
	bool ask_key_press();
	int ask_yes_no(std::string s_yes, std::string s_no);

	void initialize_players(std::vector<Board::Player> p);
	void cell_management(Board::Player p, Controler c);

	void roll_dice(Board::Player p);
	void out_of_prison(Board::Player p);

	CardType pick_a_card(Board::Player p);
	void pay_taxes(Board::Player p);
	void go_to_jail(Board::Player p, std::vector<Board::Cell> b);

	void upgrade(Board::Player, Controler c);
	void mortgage(Board::Cell c);
	void get_user_input(sf::Event event);
}
