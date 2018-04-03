#include "model.hpp"
using namespace Board;

/*****CELL*********************************************************************/

/*
 * \param :
 * \brief : Cell class constructor. no comment.
 * \return :
 */
Cell::Cell(unsigned int pos, std::string name, Type t, int rank) {
    Cell::Position = pos;
    Cell::Name     = name;
    Cell::CellType = t;
    Cell::Rank     = rank;
    if (t == BUILDING){
        Cell::Value     = ((pos%5 > 3 || pos%5 < 1) ? 50 : 0) + 100*rank;
        Cell::vMortgage = Cell::Value - Cell::Value/8;
        Cell::Rebuy     = Cell::vMortgage + Cell::vMortgage/10;
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
        if ((*i).Position == c.Position) return true;
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
 *          string scheme : CELL_POS CELL_NAME CELL_TYPE CELL_RANK
 * \brief : convert the data cell string into a cell class
 * \return : the cell created from the string
 */
 Cell Board::str_to_cell(std::string str) {
    int i = 0;
    unsigned int pos, t, rank;
    std::string name;
    std::istringstream words(str);
    do {
        std::string word; words >> word;
        if (i == 0) {
            pos = stoi(word);
            i++;
        } else if (i == 1) {
            name = word;
            i++;
        } else if (i == 2) {
            t = stoi(word);
            i++;
        } else if (i == 3) {
            rank = stoi(word);
            i++;
        } else {
            std::cout << "Out of bound !!!" << std::endl;
        }
    } while (words);
    return Cell(pos, name,(Type) t, rank);
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
 * \param : vector<Cell> b, the file containing board data
 * \brief : convert the file data into cells class, filling the b vector
 * \return : void
 */
void Board::create_board(std::vector<Cell> b, std::string filename) {
    std::ifstream file(filename, std::ifstream::in);
    std::string line;
    if (file.is_open()) {
        while(getline(file, line)) {
            Cell tmp = str_to_cell(line);
            b.push_back(tmp);
        }
    } else {
        std::cout << "File: " << filename << " cannot open file.";
    }
}

/*
 * \param : vector<Cell> b the board_game, vector<Player> p all the players
 * \brief : PAS FINI faudrait redefinir les conditions de victoire
 *           en fonction du mode ça pourrait etre cool
 * \return : true if the game is over, false if not
 */
bool Board::is_game_over(std::vector<Cell> b, std::vector<Player> p) {
    int count = 0;
    for (unsigned int i = 0; i < p.size(); i++) {
        if (p[i].Buildings.size() == b.size()) return true;
        if (!p[i].Money) count++;
    }
    if (count == p.size() - 1) return true;
    return false;
}
