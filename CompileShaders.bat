if not exist "shaders" mkdir "shaders"
:: The "Bin" folder in your Vulkan SDK installation MUST be added to your system's environment variables to make this batch script work.
glslc simple_shader.vert -o shaders\simple_shader_vert.spv
glslc simple_shader.frag -o shaders\simple_shader_frag.spv
pause