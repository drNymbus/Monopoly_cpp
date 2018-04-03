#include <SFML/Graphics.hpp>

#include "model.hpp"

namespace view {
    typedef struct {

    } Env_t;
    void init(Env_t env);

    void message(std::string s);
    void yes_no(std::string yes, std::string no);

    void info_upgrade(Board::Cell c);
    void info_mortgage(Board::Cell c);
    void info_buy(Board::Cell c);
}
