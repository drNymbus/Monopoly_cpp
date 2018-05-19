// #include "command.hpp"
// #include "view.hpp"
// #include "model.hpp"

#include "app.hpp"

void usage(void) {
    fprintf(stderr, "%s\n", "Command is incorrect.");
    fprintf(stderr, "%s\n", "One argument is needed, the file to load the map.");
    fprintf(stderr, "%s\n", "Example : ./Monopoly maps/Original.txt");
    fprintf(stderr, "%s\n", "(If no argument is given then the default map is active.)");
    return exit(EXIT_FAILURE);
}

int main(int argc, char** argv) {
    App* monopoly = new App();
    (*monopoly).OnCreate();
    std::cout << "App created...\n";

    while (monopoly->Window->isOpen()) {
        // std::cout << "Window is open\n";
        if (!(*monopoly).IsGameOver()) {
            // std::cout << "Game not over\n";
            (*monopoly).Tick();
        }
    }

    (*monopoly).EndApp();
    delete monopoly;

    std::cout << "BRAVO VICTOR !" << std::endl;
    return EXIT_SUCCESS;
}
