#include "first_app.hpp"


namespace dwe {
	void firstapp::run() {
		while (!window.shouldClose()) {
			glfwPollEvents();
		}
	}
}