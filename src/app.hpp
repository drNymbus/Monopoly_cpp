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

typedef enum {SELECT_NB, GET_NAMES, SELECT_BOARD} MenuState_e;
typedef MenuState_e MenuState;

class App {
public:
    Controller* Control;
    Model_view* View;
    std::vector<Board::Player> Players;
    sl::SList<Board::Cell>* Properties;

    sf::RenderWindow* Window;
    GameState gState;
    MenuState mState;

    void OnCreate(sf::RenderWindow* w);
    void EndApp(void);
    void Tick(void);
    bool IsGameOver(void);

private:
    bool Pause(void);
    void Win(void);
    void Menu(void);
    void BeginGame(void);
    void Turn(void);
    void Next(void);
};
