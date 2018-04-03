#include <SFML/Window.hpp>

#include <iostream>
#include <string>

#include "view.hpp"
#include "model.hpp"

namespace command {
	Board::Cell mouse_cell_pos();

	unsigned int ask_number(std::vector<int> value);
	bool ask_key_press();
	int ask_yes_no(std::string s_yes, std::string s_no);

	void initialize_players(std::vector<Player> p);
	void cell_management(Player p, Controler c);

	void roll_dice(Player p);
	void out_of_prison(Player p);

	CardType pick_a_card(Player p);
	void pay_taxes(Player p);
	void go_to_jail(Player p, std::vector<Cell> b);
}
