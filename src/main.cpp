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
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH,SCREEN_HEIGHT),APP_NAME);

    App* monopoly = new App();
    (*monopoly).OnCreate(&window);
    while (monopoly->Window->isOpen()) {
        if (!(*monopoly).IsGameOver()) {
            (*monopoly).Tick();
        }
    }

    // do {
    //     monopoly.GetEvent();
    //     while (monopoly.GameState != Board::WIN && monopoly.GameState != Board::WIN) {
    //         if (!(monopoly.Tick();)) {
    //             break;
    //         }
    //     }
    // } while (monopoly.ActualEvent.type != sf::Event::Closed)

    (*monopoly).EndApp();
    delete monopoly;

    std::cout << "BRAVO VICTOR !" << std::endl;
    return EXIT_SUCCESS;
}
