#include "model.hpp"
using namespace Board;

/*****CELL*********************************************************************/

/*
 * \param :
 * \descprt : Cell class constructor. no comment.
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
 * \descprt : upgrade the cell
 * \return : bool
 */
bool Cell::upgrade(void) {
    if (Cell::Level+1 > 3) return false;
    Cell::Level++;
    Cell::vUpgrade = Cell::Level*100;
    return true;
}

/*****PLAYER*******************************************************************/

/*
 * \param :
 * \descprt :
 * \return :
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
 * \param :
 * \descprt :
 * \return :
 */
void Player::roll_dice() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 6);
    Player::Dice1 = dis(gen); Player::Dice2 = dis(gen);
}

/*
 * \param :
 * \descprt :
 * \return :
 */
bool Player::double_dice() {
    return (Player::Dice1 == Player::Dice2);
}

/*
 * \param :
 * \descprt :
 * \return :
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
 * \param :
 * \descprt :
 * \return :
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
 * \param :
 * \descprt :
 * \return :
 */
void Player::buy(Cell c) {
    Player::Money -= c.Value;
    Player::Buildings.push_back(c);
}

/*****Board::functions*********************************************************/

/*
 * \param :
 * \descprt :
 * \return :
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
 * \param :
 * \descprt :
 * \return :
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
 * \param :
 * \descprt :
 * \return :
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
 * \param :
 * \descprt :
 * \return :
 */
void Board::initialize_players(std::vector<Player> p) {
    int nbPlayers = command::nb_players();
    std::cout << "Enter your names :" << std::endl;
    for (int i = 0; i < nbPlayers; i++) {
        std::cout << i+1 << ". ";
        Player actual_p;
        actual_p.Id = i;
        actual_p.Name = command::player_name();
        std::cout << " [DONE]" << std::endl;
    }
}

/*
 * \param :
 * \descprt :
 * \return :
 */
bool Board::is_game_over(std::vector<Cell> b, std::vector<Player> p) {
    int count = 0;
    for (unsigned int i = 0; i < p.size(); i++) {
        if (p[i].Buildings.size() == b.size()) return true;
        if (!p[i].Money) count++;
    }
    return false;
}
