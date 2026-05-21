#include "first_app.hpp"
#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>
#include <stdexcept>
#include <vector>
#include <memory>
#include <array>

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
			drawFrame();
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
		uint32_t imageIndex;
		auto result = dweSwapChain.acquireNextImage(&imageIndex);
		if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR) {
			throw std::runtime_error("Failed to acquire next swapchain image");
		}
		result = dweSwapChain.submitCommandBuffers(&commandBuffers[imageIndex], &imageIndex);
		if (result != VK_SUCCESS) {
			throw std::runtime_error("Failed to present swapchain image!");
		}
	}
	void firstapp::createCommandBuffers() {
		commandBuffers.resize(dweSwapChain.imageCount());
		VkCommandBufferAllocateInfo allocInfo{};
		allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
		allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
		allocInfo.commandPool = dweDevice.getCommandPool();
		allocInfo.commandBufferCount = static_cast<uint32_t>(commandBuffers.size());
		if (vkAllocateCommandBuffers(dweDevice.device(), &allocInfo, commandBuffers.data()) != VK_SUCCESS) {
			throw std::runtime_error("Failed to allocate command buffers!");
		}
		for (int i = 0; i < commandBuffers.size(); ++i) {
			VkCommandBufferBeginInfo beginInfo{};
			beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
			if (vkBeginCommandBuffer(commandBuffers[i], &beginInfo) != VK_SUCCESS) {
				throw std::runtime_error("Failed to begin recording command buffers!");
			}

			VkRenderPassBeginInfo renderPassInfo{};
			renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
			renderPassInfo.renderPass = dweSwapChain.getRenderPass();
			renderPassInfo.framebuffer = dweSwapChain.getFrameBuffer(static_cast<int>(i));
			renderPassInfo.renderArea.offset = { 0, 0 };
			renderPassInfo.renderArea.extent = dweSwapChain.getSwapChainExtent();
			std::array<VkClearValue, 2> clearValues{};
			clearValues[0].color = { {0.1f, 0.1f, 0.1f, 1.0f} };
			clearValues[1].depthStencil = { 1.0f, 0 };
			renderPassInfo.clearValueCount = static_cast<uint32_t>(clearValues.size());
			renderPassInfo.pClearValues = clearValues.data();

			vkCmdBeginRenderPass(commandBuffers[i], &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

			
			pipeline->bind(commandBuffers[i]);
			vkCmdDraw(commandBuffers[i], 3, 1, 0, 0);

			vkCmdEndRenderPass(commandBuffers[i]);

			if (vkEndCommandBuffer(commandBuffers[i]) != VK_SUCCESS) {
				throw std::runtime_error("Failed to record command buffer!");
			}
		}
	}
} // namespace dwe