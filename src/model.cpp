Cell::Cell(std::string name, Type t, unsigned int pos, int rank=-1) {
    Cell::Name     = name;
    Cell::CellType = t;
    Cell::Rank     = rank;
    if (t == BUILDING){
        Cell::Value   = ((pos%5 > 3 && pos%5 < 1) ? 50 : 0) + 100*rank;
        Cell:Mortgage = Cell::Value - Cell::Value/8;
        Cell::Rebuy   = Cell::Mortgage + Cell::Mortgage/10;
    }
}
int Cell::action(Player p) {
    switch (Cell::CellType) {
        case BUILDING:
            if (Player.do_possess(Cell)) break;
            if (Cell::is_possessed()) {
                Player.pay(Cell::WhoPossess, Cell::Value/3);
            }
        break;

        case BONUS:
        break;

        case JAIL:
        break;
    }
}

void roll_dice();
void pay(Player p);
void buy(Cell c);
