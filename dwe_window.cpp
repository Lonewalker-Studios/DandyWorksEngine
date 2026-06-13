#define GLFW_DLL
#include "dwe_window.hpp"
#include <stdexcept>
namespace dwe {
	dweWindow::dweWindow(int w, int h, std::string t) : width{ w }, height{ h }, title{ t } {
		initWindow();
	}
	dweWindow::~dweWindow() {
		glfwDestroyWindow(window);
		glfwTerminate();
	}
	void dweWindow::initWindow() {
		glfwInit();
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE); // Disable GLFW's default resizable functions, since we'll handle those differently.
		window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
	}
	void dweWindow::createWindowSurface(VkInstance instance, VkSurfaceKHR* surface) {
		if (glfwCreateWindowSurface(instance, window, nullptr, surface) != VK_SUCCESS) {
			throw std::runtime_error("Failed to create window surface");
		}
	}
}
