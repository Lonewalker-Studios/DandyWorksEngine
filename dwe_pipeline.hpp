#pragma once
#include "dwe_device.hpp"
#include <string>
#include <vector>
#include <vulkan/vulkan.h>

namespace dwe {
	class dwePipeline {
	public:
		struct pipelineConfigInfo {
			VkPipelineVertexInputStateCreateInfo vertexInputInfo;
			VkPipelineInputAssemblyStateCreateInfo inputAssemblyInfo;
			VkViewport viewport;
			VkRect2D scissor;
			VkPipelineRasterizationStateCreateInfo rasterizationInfo;
			VkPipelineMultisampleStateCreateInfo multisampleInfo;
			VkPipelineColorBlendAttachmentState colorBlendAttachment;
			VkPipelineColorBlendStateCreateInfo colorBlendInfo;
			VkPipelineDepthStencilStateCreateInfo depthStencilInfo;
			VkPipelineLayout pipelineLayout = VK_NULL_HANDLE;
			VkRenderPass renderPass = VK_NULL_HANDLE;
			uint32_t subpass = 0;
		};

		dwePipeline(dweDevice& device, const std::string& vertFilepath, const std::string& fragFilepath, const pipelineConfigInfo& configInfo);
		~dwePipeline();
		dwePipeline(const dwePipeline&) = delete;
		void operator = (const dwePipeline&) = delete;
		static pipelineConfigInfo defaultPipelineConfigInfo(uint32_t width, uint32_t height);
	private:
		static std::vector<char> readFile(const std::string& filepath);
		void createGraphicsPipeline(const std::string& vertFilepath, const std::string& fragFilepath, const pipelineConfigInfo& configInfo);
		void createShaderModule(const std::vector<char>& code, VkShaderModule* shaderModule);
		dweDevice& device;
		VkPipeline graphicsPipeline = VK_NULL_HANDLE;
		VkShaderModule vertShaderModule = VK_NULL_HANDLE;
		VkShaderModule fragShaderModule = VK_NULL_HANDLE;
	};
}
