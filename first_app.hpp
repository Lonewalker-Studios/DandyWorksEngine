#pragma once
#include "dwe_window.hpp"
#include "dwe_pipeline.hpp"
#include "dwe_device.hpp"
#include "dwe_swap_chain.hpp"
#include <vector>
#include <memory>
#include <vulkan/vulkan.h>

namespace dwe {
	class firstapp {
	public:
		static constexpr int WIDTH = 800;
		static constexpr int HEIGHT = 600;
		void run();
		firstapp();
		~firstapp();
		firstapp(const firstapp&) = delete;
		firstapp& operator = (const firstapp&) = delete;

	private:
		void createPipelineLayout();
		void createPipeline();
		void createCommandBuffers();
		void drawFrame();

		dweWindow window{ WIDTH, HEIGHT, "Test Game" };
		dweDevice dweDevice{window};
		dweSwapChain dweSwapChain{ dweDevice, VkExtent2D{ static_cast<uint32_t>(WIDTH), static_cast<uint32_t>(HEIGHT) } };
		std::unique_ptr<dwePipeline> pipeline;
		VkPipelineLayout pipelineLayout = VK_NULL_HANDLE;
		std::vector<VkCommandBuffer> commandBuffers;
	};
}
