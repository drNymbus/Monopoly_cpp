#ifndef SFML_MODULE
#define SFML_MODULE
    #include <SFML/System.hpp>
    #include <SFML/Window.hpp>
    #include <SFML/Graphics.hpp>
#endif

#include "model.hpp"
#include "command.hpp"
#include "view.hpp"

#define APP_NAME "Monopoly"
#define SCREEN_HEIGHT 600
#define SCREEN_WIDTH 400

typedef enum {MENU, BEGIN, ROLL, MOVE, ACTION, WIN, PAUSE, END} GameState_e;
typedef GameState_e GameState;

typedef enum {SELECT_NB, GET_NAMES, COLOR, SELECT_BOARD, OVER} MenuState_e;
typedef MenuState_e MenuState;

class App {
public:
    GameState gState;
    MenuState mState;
    unsigned int iTurn;

    unsigned int NbPlayers;
    std::vector<Board::Player> Players;
    std::string MapName;
    sl::SList<Board::Cell>* Properties;

    Model_view* View;
    sf::RenderWindow* Window;

    void OnCreate(sf::RenderWindow* w); //DONE
    void EndApp(void); //DONE
    void Tick(sf::Event e); //MENU DONE
    bool IsGameOver(void);

private:
    bool LoadMap(std::string filename);
    bool Pause(void);
    void Win(void);
    void Menu(void);
    bool SelectColor();
    bool SelectNbPlayers();
    void ShufflePlayers();
    void BeginGame(void);
    void Turn(void);
    void Next(void);
};
