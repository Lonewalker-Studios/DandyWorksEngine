#pragma once
#include "dwe_window.hpp"
#include "dwe_pipeline.hpp"

namespace dwe {
	class firstapp {
	public:
		static constexpr int WIDTH = 800;
		static constexpr int HEIGHT = 600;
		void run();
		
	private:
		dweWindow window{ WIDTH, HEIGHT, "Test Game" };
		dwePipeline dwePipeline{"shaders/simple_shader_vert.spv", "shaders/simple_shader_frag.spv"};
	};
}