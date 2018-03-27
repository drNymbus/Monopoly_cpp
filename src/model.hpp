#include <iostream>
#include <string>
#include <vector>

#define ON  true
#define OFF false

typedef enum {START, BUILDING, BONUS, JAIL} Type;

class Cell {
    public:
        Type CellType;
        int Rank;
        std::string Name;
        unsigned int Value, Mortgage;
        unsigned int Rebuy;
        Player WhoPossess = NULL;

    void action(void);
    bool is_possessed(Cell c);
};

class Player {
    public:
        std::string Name;
        unsigned int Money = 0;
        unsigned int NbBuildings = 0;
        std::vector<Cell> Buildings;
        unsigned int Position;
        int dice1, dice2;

        void roll_dice();
        void pay(Player p, int sum);
        void buy(Cell c);
        bool do_possess(Cell c);
};
