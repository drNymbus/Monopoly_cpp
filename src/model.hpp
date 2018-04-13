#include <random>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#ifndef MODEL
#define MODEL

#define MAX_CELL_RANK 10
typedef enum {BUILDING, BONUS, JAIL} Type_e;
typedef Type_e Type;

typedef enum {FREE, IN_JAIL, VISIT} StatePlayer_e;
typedef StatePlayer_e StatePlayer;

#define NB_CARD 3
typedef enum {JAIL_FREE, TAX_FREE, GO_JAIL} CardType_e;
typedef CardType_e CardType;

namespace Board {
    class Cell {
        public:
            unsigned int Position;
            Type CellType;
            int Rank;
            std::string Name;
            unsigned int Value, Level = 0;
            unsigned int vMortgage, vUpgrade = 0;
            bool bMortgage = false;
            unsigned int Rebuy;

            Cell(unsigned int pos, std::string name, Type t, int rank);
            bool upgrade();

    };

    class Player {
        public:
            int Id;
            std::string Name;
            //int Color;
            StatePlayer Status;
            unsigned int Money = 2500;
            std::vector<Cell> Buildings;
            unsigned int NbMonopole = 0;
            unsigned int Position = 0;
            unsigned int JailTime = 0;
            int Dice1, Dice2;
            std::vector<CardType> Cards;

            void mortgage(Cell c);
            void roll_dice();
            bool double_dice();
            bool pay(Player p, int sum);
            void buy(Cell c);
            bool do_possess(Cell c);
    };

    Cell str_to_cell(std::string str);
    void shuffle_players(std::vector<Player> p);
    void create_board(std::vector<Cell> b, std::string filename);
    void initialize_players(std::vector<Player> p);
    bool is_game_over(std::vector<Cell> b, std::vector<Player> p);
};

#endif
