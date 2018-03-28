#include "command.hpp"
using namespace command;

unsigned int command::nb_players(void) {
	unsigned int n = -1;
	std::cout << "How many are you ?" << std::endl;
	std::cin >> n; std::cin.ignore();
	if (n == -1) std::cout << "OUPS" << std::endl;
	return n;
}

std::string command::player_name(void) {
	std::string name;
	std::cin >> name; std::cin.ignore();
	return name;
}
