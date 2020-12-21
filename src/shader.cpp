#include <cstdio>
#include <fstream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include "shader.hpp"

#define INFO_LOG_SIZE 512

const char *vertex_src = 
"#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main() {\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";




int Shaders::first_build(const char* t_filename) {
	m_vertex_shader = create_shader(GL_VERTEX_SHADER, vertex_src);
	return build(t_filename);
}

int Shaders::build(const char* t_filename) {

	std::ifstream file(t_filename);
	if(!file.is_open()) {
	 	fprintf(stderr, "\033[33m[Warning]:\033[0m Problem reading file \"%s\" ?\n", t_filename);
		return 0;
	}

	std::string source = "#version 330 core\n";
	std::string line;
	
	while(getline(file, line)) {
		source += line + '\n';
	}

	int fragment_shader = create_shader(GL_FRAGMENT_SHADER, source.c_str());
	return link_shaders(m_vertex_shader, fragment_shader);
}

int Shaders::link_shaders(int t_vertex, int t_fragment) {
	int shader_program = glCreateProgram();
	glAttachShader(shader_program, t_vertex);
	glAttachShader(shader_program, t_fragment);
	glLinkProgram(shader_program);
	
	glDeleteShader(t_fragment);
	glDeleteShader(t_vertex);

	return shader_program;
}

int Shaders::create_shader(unsigned int t_shader_type, const char* t_source_code) {
	int shader = glCreateShader(t_shader_type);
	glShaderSource(shader, 1, &t_source_code, NULL);
	glCompileShader(shader);
	
	int compile_status = 0;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compile_status);
	if(compile_status == 0) {
		char ilog[INFO_LOG_SIZE];
		glGetShaderInfoLog(shader, INFO_LOG_SIZE, NULL, ilog);
		fprintf(stderr, "\033[31m[Compile Error]:\033[0m %s\n", ilog);
	}

	return shader;
}

bool Shaders::is_file_changed(const char* t_filename) {
	struct stat s;
	if(stat(t_filename, &s) >= 0) {
		if(m_last_modified != s.st_mtim.tv_sec) {
			m_last_modified = s.st_mtim.tv_sec;
			return true;
		}
	}
	return false;
}







