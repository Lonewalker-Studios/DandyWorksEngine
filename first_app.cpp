#include "first_app.hpp"
#include <GLFW/glfw3.h>

namespace dwe {
	void firstapp::run() {
		while (!window.shouldClose()) {
			glfwPollEvents();
		}
	}
}