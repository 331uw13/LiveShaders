#include "live_shaders.hpp"

#define WINDOW_NAME "LiveShaders"


void _resized(GLFWwindow* t_win, int t_width, int t_height) {
	glViewport(0, 0, t_width, t_height);
	//printf("Resized: %ix%i\n", t_width, t_height);
}

void LiveShaders::run(const char* t_shader_file) {
	if(m_window != nullptr) { return; }	
	m_filename = t_shader_file;

	// Initialize GLFW

	if(!glfwInit()) {
		fprintf(stderr, "Failed to initialize glfw!\n");
		return;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);

	m_window = glfwCreateWindow(1000, 800, WINDOW_NAME, NULL, NULL);
	if(m_window == nullptr) {
		glfwTerminate();
		fprintf(stderr, "Failed to create window!\n");
		return;
	}

	glfwMakeContextCurrent(m_window);
	glfwSetFramebufferSizeCallback(m_window, _resized);
	// TODO: use vsync!


	// Initialize GLEW

	if(glewInit() != GLEW_OK) {
		if(m_window != nullptr) {
			glfwDestroyWindow(m_window);
		}
		glfwTerminate();
		fprintf(stderr, "Failed to initialize glew\n");
		return;
	}


	// Setup shaders

	m_shader_program = m_shaders.first_build(m_filename);

	// Finally start rendering everything!
	render();
}

void LiveShaders::render() {	
	while(!glfwWindowShouldClose(m_window)) {
		if(glfwGetKey(m_window, GLFW_KEY_Q)) {
			glfwSetWindowShouldClose(m_window, GLFW_TRUE);
		} 

		if(glfwGetTime() >= 2.5) {
			glfwSetTime(0.0);
			if(m_shaders.is_file_changed(m_filename)) {
				glDeleteProgram(m_shader_program);
				m_shader_program = m_shaders.build(m_filename);
			}	
		}

		glUniform1f(0, (float)m_timer.elapsed()/1000.0f);
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(m_shader_program);
		glBegin(GL_QUADS);
        glVertex2f( -1.0f, -1.0f );
        glVertex2f( -1.0f,  1.0f );
        glVertex2f(  1.0f,  1.0f );
        glVertex2f(  1.0f, -1.0f );
        glEnd();

		glfwSwapBuffers(m_window);
		glfwPollEvents();
	}
	close();
	printf("bye!\n");
}

void LiveShaders::close() {
	if(m_window != nullptr) {
		glfwDestroyWindow(m_window);
	}
	glDeleteProgram(m_shader_program);
	glfwTerminate();
}





