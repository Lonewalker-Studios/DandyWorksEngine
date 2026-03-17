#pragma once
#include "dwe_device.hpp"
#include <string>
#include <vector>
namespace dwe {
	class dwePipeline {
		struct pipelineConfigInfo {

		};
	public:
		dwePipeline(dweDevice& device, const std::string& vertFilepath, const std::string& fragFilepath, const pipelineConfigInfo& configInfo);
		~dwePipeline() {}
		dwePipeline(const dwePipeline&) = delete;
		void operator = (const dwePipeline&) = delete;
		static pipelineConfigInfo defaultPipelineConfigInfo(uint32_t width, uint32_t height);
	private:
		static std::vector<char> readFile(const std::string& filepath);
		void createGraphicsPipeline(const std::string& vertFilepath, const std::string& fragFilepath, const pipelineConfigInfo& configInfo);
		void createShaderModule(const std::vector<char>& code, VkShaderModule*shaderModule);
		dweDevice& device;
		VkPipeline graphicsPipeline;
		VkShaderModule vertShaderModule;
		VkShaderModule fragShaderModule;
		
	};
}
