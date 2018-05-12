#include "command.hpp"
#include "view.hpp"
#include "model.hpp"
using namespace Board;

typedef enum {INIT, TURN, ACTION} State;

void usage(void) {
    fprintf(stderr, "%s\n", "Command is incorrect.");
    fprintf(stderr, "%s\n", "One argument is needed, the file to load the map.");
    fprintf(stderr, "%s\n", "Example : ./Monopoly maps/Original.txt");
    fprintf(stderr, "%s\n", "(If no argument is given then the default map is active.)");
    return exit(EXIT_FAILURE);
}

int main(int argc, char** argv) {
    try
    {
        std::string board_file;
        if (argc > 2) {
            usage();
        } else if (argc == 1) {
            board_file = "maps/Original.txt";
        } else if (argc == 2) {
            board_file = argv[1];
        }

        // State game_state = INIT;

        sl::SList<Cell>* properties = Board::create_properties(board_file);
        // std::vector<Player> players;

        // view::Model_view View; View.init();

        // while (!is_game_over(board_game, players)) {
        //
        // }

        sl::free_list(properties);
        return EXIT_SUCCESS;
    }
    catch (std::exception const &exc)
    {
        std::cerr << "Exception caught " << exc.what() << "\n";
    }
    catch (...)
    {
        std::cerr << "Unknown exception caught\n";
    }
}
