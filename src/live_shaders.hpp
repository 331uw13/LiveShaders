#pragma once

#include <cstdio>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "shader.hpp"
#include "timer.hpp"

class LiveShaders {
public:
	void run(const char* t_shader_filename);

private:
	Shaders m_shaders;
	Timer m_timer;

	const char* m_filename { "" };

	void render();
	void close();

	int m_shader_program  { 0 };
	
	float m_shader_time   { 0.0f };

	GLFWwindow* m_window { nullptr };
};

