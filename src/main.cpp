#include "model.hpp"

typedef enum {INIT, TURN, ACTION} State;

int main(int argc, char** argv) {
    State game_state = INIT;
    bool end_game = false;

    std::vector<Cell> Board;
    std::vector<Player> Players;
    int turn;

    while (!end_game) {
        if (turn > Players.size()) turn = 0;

        switch (game_state) {
            case INIT:
                Board = create_board("maps/" + argv[1]);
                Players = initialize_players();
                shuffle_vector(Players);
                turn = 0;
            break;

            case TURN:
                Player p_turn = Players[turn];
                p_turn.roll_dice();
                if (p_turn.double()) {
                    turn--;
                }
                p_turn.move();
            break;

            case ACTION:
                Cell actual_cell = Board[Players[turn].Position];
                actual_cell.action();
                turn++;
            break;
        }
    }

    return 0;
}
