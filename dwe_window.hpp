#pragma once
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
namespace dwe {
	class dweWindow {
	private:
		void initWindow();
		const int width;
		const int height;
		GLFWwindow * window;
	};
}