#include "model.hpp"
using namespace Board;

typedef enum {INIT, TURN, ACTION} State;

int main(int argc, char** argv) {
    State game_state = INIT;
    std::string board_txt;

    std::vector<Cell> board_game;
    std::vector<Player> players;
    unsigned int turn;

    while (!is_game_over(board_game, players)) {
        if (turn > players.size()) turn = 0;
        Player p_turn;

        switch (game_state) {
            case INIT:
                create_board(board_game, board_txt);
                initialize_players(players);
                shuffle_players(players);
                turn = 0;
            break;

            case TURN:
                p_turn = players[turn];
                command::roll_dice();
                if (p_turn.double_dice()) {
                    turn--;
                }        
                for (int i = p_turn.Dice1 + p_turn.Dice2; i >= 0; i--) {
                    if (p_turn.Position > board_game.size()) p_turn.Position = 0;
                    if (p_turn.Position == 0) p_turn.Money += 200;
                    p_turn.Position++;
                }
                if (!p_turn.Position) p_turn.Money += 300;
            break;

            case ACTION:
                Cell actual_cell = board_game[players[turn].Position];
                if (!actual_cell.bMortgage) {
                    p_turn = players[turn];
                    switch (actual_cell.CellType) {
                        case BUILDING:
                            std::vector<Player>::iterator i = players.begin();
                            for(; i != players.end(); i++) {
                                if ((*i).do_possess(actual_cell)) {
                                    if ((*i).Id != p_turn.Id) {
                                        int due = actual_cell.Value/3 + actual_cell.vUpgrade;
                                        p_turn.pay((*i), due);
                                    } else {
                                        command::upgrade()
                                    }
                                }
                            }
                        break;

                        case BONUS:
                            command::pick_a_card();
                        break;
                        case JAIL:
                        break;
                    }
                }
                turn++;
            break;
        }
    }

    return 0;
}
