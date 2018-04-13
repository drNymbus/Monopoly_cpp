#include "command.hpp"
#include "model.hpp"
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
}

/*
 *\param :
 * \brief :
 * \return :
 */
CardType command::pick_a_card(Player p) {
}

/*
 *\param :
 * \brief :
 * \return :
 */
void command::roll_dice(Player p) {
}

/*
 *\param :
 * \brief :
 * \return :
 */
void command::upgrade(Player p, Controler c) {
}

/*
 *\param :
 * \brief :
 * \return :
 */
void command::mortgage(Cell c) {}

/*
 *\param :
 * \brief :
 * \return :
 */
void command::cell_management(Player p, Controler c) {
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
