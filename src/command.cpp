#include "command.hpp"
using namespace command;
using namespace Board;

/*
 *\param :
 * \brief :
 * \return :
 */
unsigned int command::ask_number(std::vector<int> value);

/*
 *\param :
 * \brief :
 * \return :
 */
int command::ask_yes_no(std::string s_yes, std::string s_no);

/*
 * \param : vector<Player> p to be filled
 * \brief : Fill the classes Player of the vector,
 *          the vector passes in argument need to be initialized with empy classes Player
 *          asking the name of the players, (and their skin ...plus tard ?...)
 * \return : void
 */
void command::initialize_players(std::vector<Player> p) {
	view::message
	int nbPlayers = command::ask_number();
    std::cout << "Enter your names :" << std::endl;
    for (int i = 0; i < nbPlayers; i++) {
        std::cout << i+1 << ". ";
        Player actual_p; // DATA COULD BE DAMAGED IN FUTURE OPERATIONS
        actual_p.Id = i;
        actual_p.Name = player_name();
        std::cout << " [DONE]" << std::endl;
    }
}

/*
 *\param :
 * \brief :
 * \return :
 */
CardType command::pick_a_card(Player p) {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(0, NB_CARD-1);
	switch (dis(gen)) {
		case JAIL_FREE:
			p.Cards.push_back(JAIL_FREE);
			return JAIL_FREE;
		break;
		case TAX_FREE:
			p.Cards.push_back(TAX_FREE);
			return TAX_FREE;
		break;
		case GO_JAIL:
			go_to_jail(p);
			return GO_JAIL;
		break;
	}
	std::cerr << "I don't fucking care anymore" << std::endl;
	exit(EXIT_FAILURE);
}

/*
 *\param :
 * \brief :
 * \return :
 */
void command::roll_dice(Player p) {
	p.roll_dice();
}

/*
 *\param :
 * \brief :
 * \return :
 */
void command::upgrade(Player p, Controler c) {
	if (c.Mouse.isButtonPressed(sf::Left)) {
		Cell select_cell = c.mouse_cell_pos();
		unsigned int upgrade_price = select_cell.Value/2 + select_cell*100;

		if (p.do_possess(select_cell) && (!select_cell.bMortgage)) {
			if (p.Money > upgrade_price) {
				select_cell.upgrade();
				view::anim_upgrade(select_cell);
			} else {
				view::message("Not enough money to upgrade " + select_cell.Name);
			}
		} else {
			if (select_cell.bMortgage) {
				view::message(select_cell.Name + " is mortgaged.\No actions.");
			} else {
				view::message("You do not possess " + select_cell.Name + ".");
			}
		}

	} else {
		view::info_upgrade(select_cell);
	}
}

/*
 *\param :
 * \brief :
 * \return :
 */
void command::mortgage();

/*
 *\param :
 * \brief :
 * \return :
 */
void command::cell_management(Player p, Controler c) {
	if (p.NbMonopole > 1) {
		view::message("What do you want to do ?");
		view::yes_no("Upgrade", "Mortgage");
		if ((c.yes_no() == 1) && c.Mouse.isButtonPressed(sf::Left)) {
			upgrade(p, c);
		} else if ((c.yes_no() == 2) && c.Mouse.isButtonPressed(sf::Left)) {
			mortgage(p, c);
		}
}

/*
 *\param :
 * \brief :
 * \return :
 */
void command::pay_taxes(Player p);

/*
 *\param :
 * \brief :
 * \return :
 */
void command::go_to_jail(Player p, std::vector<Cell> b);

/*
 *\param :
 * \brief :
 * \return :
 */
void command::out_of_prison(Player p);
