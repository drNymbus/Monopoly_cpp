#include <iostream>
#include <string>

namespace command {
	unsigned int nb_players(void);
	std::string player_name(void);
	void pick_a_card(Player p);
	void roll_dice(Player p);
	void upgrade(Player p);
	void pay_taxes(Player p);
	void go_to_jail(Player p, std::vector<Cell> b);
	void out_of_prison(Player p);
	void cell_management(Player p);
}
