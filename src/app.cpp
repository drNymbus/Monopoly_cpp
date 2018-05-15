#include "app.hpp"


/*
 * \param :
 * \brief :
 * \return:
 */
// void App::Menu(void) {
//     App::Control->select_nb_players(App::Window);
//     App::View->select_nb_players(App::Control);
// }

// void BeginGame(void);
// void Turn(void);
// void Next(void);

void App::OnCreate(sf::RenderWindow* w) {
    try {
        App::Window = w;
        App::Control = new Controller();
        App::View = new Model_view();

        App::gState = MENU;
        App::mState = SELECT_NB;
    } catch (std::exception const& e) {
        std::cerr << "Error alocating App : " << e.what() << '\n';
    } catch (...) {std::cerr << "Unknown error OnCreate\n";}
}

void App::EndApp(void) {
    try {
        delete App::Control;
        delete App::View;
    } catch (std::exception const& e) {
        std::cerr << "Exception on EndApp : " << e.what() << '\n';
    } catch (...) {std::cerr << "Unknown error on EndApp\n";}
}

void App::Tick(void) {
    App::Control->get_event(App::Window);

    if (App::Control->ActualEvent.type == sf::Event::Closed) {
        App::Window->close();
    } else {
        // switch (App::GameState) {
        //     case MENU:
        //         App::Menu();
        //     break;
        //     case PAUSE:
        //         while (!App::Pause()) {}
        //     break;
        // }
    }
    App::Window->display();
}

bool App::IsGameOver(void) {
    return false;
}
