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
                p_turn.roll_dice();
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
