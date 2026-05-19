#pragma once
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <string>
namespace dwe {
	class dweWindow {
	public:
		dweWindow(int w, int h, std::string t);
		~dweWindow();
		bool shouldClose() { return glfwWindowShouldClose(window); }
		VkExtent2D getExtent() { return { static_cast<uint32_t>(width), static_cast<uint32_t>(height) }; }
		void createWindowSurface(VkInstance instance, VkSurfaceKHR* surface);
	private:
		void initWindow();
		const int width;
		const int height;
		GLFWwindow*window;
		std::string title;
	};
}
