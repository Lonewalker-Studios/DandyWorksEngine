#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include "first_app.hpp"

int main() {
	dwe::firstapp app{};
	try {
		app.run();
	}
	catch(const std::exception &e){
		std::cerr << e.what() << '\n';
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}