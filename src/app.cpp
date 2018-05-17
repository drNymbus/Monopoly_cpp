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
        App::View = new Model_view();

        App::gState = MENU;
        App::mState = SELECT_NB;
        App::iTurn  = 0;

        App::NbPlayers = 0;
    } catch (std::exception const& e) {
        std::cerr << "Error alocating App : " << e.what() << '\n';
    } catch (...) {std::cerr << "Unknown error OnCreate\n";}
}

void App::EndApp(void) {
    try {
        delete App::View;
        if (App::Properties) sl::free_list(App::Properties);
    } catch (std::exception const& e) {
        std::cerr << "Exception on EndApp : " << e.what() << '\n';
    } catch (...) {std::cerr << "Unknown error on EndApp\n";}
}

void App::Tick(sf::Event e) {
    if (e.type == sf::Event::Closed) {
        App::Window->close();
    } else if (App::gState == MENU){
        switch (App::mState) {
            case SELECT_NB:
                if (App::SelectNbPlayers()) {
                    App::mState = GET_NAMES;
                    App::iTurn  = 0;
                }
            break;
            // case GET_NAMES:
            //     if (command::get_user_name(e, sf::Keyboard::Return, &(App::Players[App::iTurn].Name))) {
            //         App::iTurn++;
            //         if (iTurn == NbPlayers) {
            //             App::iTurn = 0;
            //             App::mState = COLOR;
            //         }
            //     }
            // break;
            // case COLOR:
            //     if (App::SelectColor()) {
            //         App::iTurn++;
            //         if (App::iTurn == App::NbPlayers) {
            //             App::iTurn = 0;
            //             App::mState = SELECT_BOARD;
            //         }
            //     }
            // break;
            // case SELECT_BOARD:
            //     if (command::select_board(&(App::MapName))) {
            //         App::LoadMap(App::MapName);
            //         App::mState = OVER;
            //         App::gState = BEGIN;
            //     }
            // break;
            default:
                std::cerr << "YOU SHOULDN'T BE HERE" << std::endl;
                std::cerr << "GO AWAY ! STOP HACKING !" << std::endl;
            break;
        }
    }
    // App::View->Tick();
    App::Window->display();
}

/*
 * \param :
 * \brief :  Si qlqun possède tout les bâtiments,
 *           ou tous les joueurs ont fait faillite sauf un
 *           PAS FINI faudrait redefinir les conditions de victoire
 *           en fonction du mode ça pourrait etre cool
 * \return : true if the game is over, false if not
 */
bool App::IsGameOver(void) {
    unsigned int count = 0;
    for (unsigned int i = 0; i < App::NbPlayers; i++) {
        if (App::Players[i].Buildings.size() == sl::size(App::Properties)) return true;
        if (!App::Players[i].Money) count++;
    }
    if (count == (App::NbPlayers-1) - 1) return true;
    return false;
}


/**************************************************************************************************/
/*                                       PRIVATE                                                  */
/**************************************************************************************************/

/*
 * \param : str the string to be examined, actual line that being examined
 * \brief : convert the string str into a properly formed cell,
 *          the line is used to treat errors
 * \return : A properly set Cell class pointer
 */
Board::Cell* str_to_cell(std::string str, unsigned int line) {
   int i = 0, id = 0;
   unsigned int t, rank;
   std::string name;
   bool is_last = false;

   std::istringstream words(str);
   do {
       std::string word; words >> word;
       // std::cout << word << ' ';
       // std::cout << word << "| "<< i << std::endl;
       if (i == 1) {
           name = word;
           i++;
       } else if (i == 4) {
           is_last = true;
           i++;
       } else {
           try {
               if (i == 0) {
                   id = stoi(word);
                   i++;
               } else if (i == 2) {
                   t = stoi(word);
                   i++;
               } else if (i == 3) {
                   rank = stoi(word);
                   i++;
               }
           } catch (std::exception const &e) {
               std::cerr << "Incorrect parameter LINE " << line << std::endl;
               std::cerr << "\t\"" << word << '\"' << ": is incorrect !" << i <<std::endl;
               std::cerr << "Error : " << e.what() << std::endl;
               exit(EXIT_FAILURE);
           } catch (...) {
               std::cerr << "Incorrect parameter LINE " << line << std::endl;
               std::cerr << "\t\"" << word << '\"' << ": is incorrect !" << i <<std::endl;
               std::cerr << "Unknown error" << std::endl;
               exit(EXIT_FAILURE);
           }
       }
   } while (words);
   // std::cout << std::endl;

   Board::Cell* c = new Board::Cell(id, name,(Type) t, rank, is_last);
   c->fix_name();
   return c;
}

/*
 * \param : the name of the file containing board data
 * \brief : convert the file data into cells class,
 *          filling the attr Properties of the class App;
 * \return : true if the file has been loaded, false if not
 */
bool App::LoadMap(std::string filename) {
    sl::SList<Board::Cell>* properties = sl::create_list<Board::Cell>();
    int id = 0;

    unsigned int i_line = 0;
    std::ifstream file(filename, std::ifstream::in);
    std::string line;
    if (file.is_open()) {
        while(getline(file, line)) {
            Board::Cell* property = str_to_cell(line, i_line);
            property->Id = id;
            properties = sl::append(properties, property);
        }
    } else {
        std::cerr << "File: " << filename << " cannot open file.";
        return false;
    }

    App::Properties = properties;
    return true;
}

/*
 * \param  : NONE
 * \brief  : reaffecting the position of the class player in the vector randomly
 * \return : void
 */
void App::ShufflePlayers() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, App::NbPlayers-1);
    for (unsigned int i = 0; i < App::NbPlayers; i++) {
        int r = dis(gen);
        Board::Player tmp = App::Players[i];
        App::Players[i] = App::Players[r];
        App::Players[r] = tmp;
    }
}

bool App::SelectNbPlayers() {
    App::NbPlayers = 1;
    return true;
}
