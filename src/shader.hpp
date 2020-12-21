#pragma once

class Shaders {
public:
	int first_build(const char* t_filename);
	int build(const char* t_filename);

	bool is_file_changed(const char* t_filename);

private:

	// vertex shader will be created only once!
	int m_vertex_shader { 0 }; 

	long int m_last_modified { 0 };
	
	int link_shaders(int t_vertex, int t_fragment);
	int create_shader(unsigned int t_shader_type, const char* t_source_code);



};

