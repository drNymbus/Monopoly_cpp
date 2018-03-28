#include <random>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "command.hpp"

typedef enum {BUILDING, BONUS, JAIL} Type;

namespace Board {
    class Cell {
        public:
            unsigned int Position;
            Type CellType;
            int Rank;
            std::string Name;
            unsigned int Value, vMortgage;
            bool bMortgage = false;
            unsigned int Rebuy;

            Cell(unsigned int pos, std::string name, Type t, int rank);
    };

    class Player {
        public:
            std::string Name;
            //int Color;
            unsigned int Money = 2500;
            std::vector<Cell> Buildings;
            unsigned int Position = 0;
            int Dice1, Dice2;

            void mortgage(Cell c);
            void roll_dice();
            bool double_dice();
            void pay(Player p, int sum);
            void buy(Cell c);
            bool do_possess(Cell c);
    };

    Cell str_to_cell(std::string str);
    void shuffle_players(std::vector<Player> p);
    void create_board(std::vector<Cell> b, std::string filename);
    void initialize_players(std::vector<Player> p);
    bool is_game_over(std::vector<Cell> b, std::vector<Player> p);
};