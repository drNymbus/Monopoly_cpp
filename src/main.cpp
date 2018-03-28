#include "model.hpp"
using namespace Board;

typedef enum {INIT, TURN, ACTION} State;

int main(int argc, char** argv) {
    State game_state = INIT;
    bool end_game = false;
    std::string board_txt;

    std::vector<Cell> board_game;
    std::vector<Player> players;
    unsigned int turn;

    while (!end_game) {
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
                p_turn.roll_dice();
                if (p_turn.double_dice()) {
                    turn--;
                }
                p_turn.move();
            break;

            case ACTION:
                Cell actual_cell = board_game[players[turn].Position];
                switch (actual_cell.CellType) {
                    case BUILDING:

                    break;
                    case BONUS:
                    break;
                    case JAIL:
                    break;
                }
                turn++;
            break;
        }
    }

    return 0;
}
