#include "model.hpp"
using namespace Board;

/*****CELL*********************************************************************/

/*
 * \param :
 * \brief : Cell class constructor. no comment.
 * \return :
 */
Cell::Cell(int id, std::string name, Type t, int rank, bool is_last) {
    Cell::Id       = id;
    Cell::Name     = name;
    Cell::CellType = t;
    Cell::Rank     = rank;
    if (t == BUILDING){
        Cell::Value     = 60 + (40*rank) + ( is_last ? 20 : 0);
        Cell::vMortgage = Cell::Value - Cell::Value/8;
        Cell::Rebuy     = Cell::vMortgage + Cell::vMortgage/10;
    }
}

/*
 * \param : void
 * \brief : upgrade the cell
 * \return : returns true if the cell has been upgraded, false otherwise
 */
void Cell::fix_name(void) {
    std::string::iterator i = Cell::Name.begin();
    for (; i != Cell::Name.end(); i++) {
        if ((*i) == '_') (*i) = ' ';
    }
}

/*
 * \param : void
 * \brief : upgrade the cell
 * \return : returns true if the cell has been upgraded, false otherwise
 */
bool Cell::upgrade(void) {
    if (Cell::Level+1 > 3) return false;
    Cell::Level++;
    Cell::vUpgrade = Cell::Level*100;
    return true;
}

/*****PLAYER*******************************************************************/

/*
 * \param : Cell c the building to mortgage
 * \brief : pass the cell into a mortgage state, while giving money
 *          to the player mortgaging it
 * \return : true if the mortgage was successful, false if not
 */
void Player::mortgage(Cell c) {
    if (!Player::do_possess(c) || c.bMortgage) {
        std::cout << c.Name << std::endl;
        std::cout << "Mortgage : ";
        std::cout << (c.bMortgage ? "True" : "False") << std::endl;
        std::cout << "Can't mortgage this cell." << std::endl;
        return;
    }
    c.bMortgage = true;
    Player::Money += c.vMortgage;
}

/*
 * \param : void
 * \brief : reaffecting new value to dices's player (range 1, 6)
 * \return : void
 */
void Player::roll_dice() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 6);
    Player::Dice1 = dis(gen); Player::Dice2 = dis(gen);
}

/*
 * \param : void
 * \brief : check if the dices's value are equals
 * \return : bool
 */
bool Player::double_dice() {
    return (Player::Dice1 == Player::Dice2);
}

/*
 * \param : Player p to pay, the sum to pay
 * \brief : pay the player p, in case the player does not have any money
 *          the payment doesn't take place
 * \return : true if the player p has receive the correct amount of money
 */
bool Player::pay(Player p, int sum) {
    if (Player::Money - sum > Player::Money) {
        std::cout << "Insufficient money." << std::endl;
        return false;
    }
    p.Money += sum;
    Player::Money -= sum;
    return true;
}

/*
 * \param : Cell c
 * \brief : Check if the cell c is possessed by the player
 * \return : true if the cell is possessed by the player, false if not
 */
bool Player::do_possess(Cell c) {
    std::vector<Cell>::iterator i = Player::Buildings.begin();
    while (i != Player::Buildings.end()) {
        if ((*i).Id == c.Id) return true;
        i++;
    }
    return false;
}

/*
 * \param : Cell c to buy
 * \brief : add the cell into the player's buildings
 *          while redefining the number of monopole possessed
 *          (at least three cells of the same rank)
 * \return : void
 */
void Player::buy(Cell c) {
    Player::Money -= c.Value;
    Player::Buildings.push_back(c);

    int nb_monopole = 0, count[MAX_CELL_RANK];
    for (int i=0; i < MAX_CELL_RANK; i++) count[i] = 0;

    std::vector<Cell>::iterator i = Player::Buildings.begin();
    for (; i != Player::Buildings.end(); i++) count[(*i).Rank]++;
    for (int i = 0; i < MAX_CELL_RANK; i++) {
        if (count[i] > 2) nb_monopole++;
    }
    Player::NbMonopole = nb_monopole;
}

/*****Board::functions*********************************************************/

/*
 * \param : String s containing data cell
 *          string scheme : CELL_ID CELL_NAME CELL_TYPE CELL_RANK
 *          if the property is the last of this rank then put LAST
 *          at the end of the string scheme
 *          replace all spaces by _ (those will not appear in rendering)
 * \brief : convert the data cell string into a cell class
 * \return : the cell created from the string
 */
 Cell* Board::str_to_cell(std::string str, unsigned int line) {
    int i = 0, id = 0;
    unsigned int t, rank;
    std::string name;
    bool is_last = false;

    std::istringstream words(str);
    do {
        std::string word; words >> word;
        // std::cout << word << ' ';
        // std::cout << word << "| "<< i << std::endl;
        if (i == 1) {
            name = word;
            i++;
        } else if (i == 4) {
            is_last = true;
            i++;
        } else {
            try {
                if (i == 0) {
                    id = stoi(word);
                    i++;
                } else if (i == 2) {
                    t = stoi(word);
                    i++;
                } else if (i == 3) {
                    rank = stoi(word);
                    i++;
                }
            } catch (std::exception const &e) {
                std::cerr << "Incorrect parameter LINE " << line << std::endl;
                std::cerr << "\t\"" << word << '\"' << ": is incorrect !" << i <<std::endl;
                std::cerr << "Error : " << e.what() << std::endl;
                exit(EXIT_FAILURE);
            } catch (...) {
                std::cerr << "Incorrect parameter LINE " << line << std::endl;
                std::cerr << "\t\"" << word << '\"' << ": is incorrect !" << i <<std::endl;
                std::cerr << "Unknown error" << std::endl;
                exit(EXIT_FAILURE);
            }
        }
    } while (words);
    // std::cout << std::endl;

    Cell* c = new Cell(id, name,(Type) t, rank, is_last);
    c->fix_name();
    return c;
}

/*
 * \param : vector<Cell> b, the file containing board data
 * \brief : convert the file data into cells class, filling the b vector
 * \return : void
 */
 sl::SList<Cell>* Board::create_properties(std::string filename) {
    sl::SList<Cell>* properties = sl::create_list<Cell>();
    int id = 0;

    unsigned int i_line = 0;
    std::ifstream file(filename, std::ifstream::in);
    std::string line;
    if (file.is_open()) {
        while(getline(file, line)) {
            Cell* property = str_to_cell(line, i_line);
            property->Id = id;
            properties = sl::append(properties, property);
        }
    } else {
        std::cout << "File: " << filename << " cannot open file.";
    }

    return properties;
}

/*
* \param : vector<Player> p to shuffle
* \brief : reaffecting the position of the class player in the vector randomly
* \return : void
*/
void Board::shuffle_players(std::vector<Player> p) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, p.size()-1);
    for (unsigned int i = 0; i < p.size(); i++) {
        int r = dis(gen);
        Player tmp = p[i];
        p[i] = p[r];
        p[r] = tmp;
    }
}

/*
 * \param : vector<Cell> b the board_game, vector<Player> p all the players
 * \brief :  Si qlqun possède tout les bâtiments,
 *           ou tous les joueurs ont fait faillite sauf un
 *           PAS FINI faudrait redefinir les conditions de victoire
 *           en fonction du mode ça pourrait etre cool
 * \return : true if the game is over, false if not
 */
bool Board::is_game_over(sl::SList<Cell>* b, std::vector<Player> p) {
    unsigned int count = 0;
    for (unsigned int i = 0; i < p.size(); i++) {
        if (p[i].Buildings.size() == sl::size(b)) return true;
        if (!p[i].Money) count++;
    }
    if (count == p.size() - 1) return true;
    return false;
}
