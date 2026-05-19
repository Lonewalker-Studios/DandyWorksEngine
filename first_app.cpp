#include "first_app.hpp"
#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>
#include <stdexcept>
#include <vector>
#include <memory>


namespace dwe {
	firstapp::firstapp() {
		createPipelineLayout();
		createPipeline();
		createCommandBuffers();
	}
	firstapp::~firstapp() {
		vkDestroyPipelineLayout(dweDevice.device(), pipelineLayout, nullptr);
	}
	void firstapp::run() {
		while (!window.shouldClose()) {
			glfwPollEvents();
		}
	}


	void firstapp::createPipelineLayout() {
		VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
		pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
		pipelineLayoutInfo.setLayoutCount = 0;
		pipelineLayoutInfo.pSetLayouts = nullptr;
		pipelineLayoutInfo.pushConstantRangeCount = 0;
		pipelineLayoutInfo.pPushConstantRanges = nullptr;

		if (vkCreatePipelineLayout(dweDevice.device(), &pipelineLayoutInfo, nullptr, &pipelineLayout) != VK_SUCCESS) {
			throw std::runtime_error("Failed to create pipeline layout");
		}
	}

	void firstapp::createPipeline() {
		auto pipelineConfig = dwePipeline::defaultPipelineConfigInfo(dweSwapChain.width(), dweSwapChain.height());
		pipelineConfig.renderPass = dweSwapChain.getRenderPass();
		pipelineConfig.pipelineLayout = pipelineLayout;
		pipeline = std::make_unique<dwePipeline>(dweDevice, "shaders/simple_shader_vert.spv", "shaders/simple_shader_frag.spv", pipelineConfig);
	}
	void firstapp::drawFrame() {

	}
	void firstapp::createCommandBuffers() {

	}
} // namespace dwe