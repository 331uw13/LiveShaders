#include "live_shaders.hpp"

int main(int argc, char** argv) {
	LiveShaders live_shaders;
	if(argc != 2) {
		fprintf(stderr, "Usage: ./LiveShaders <file.glsl>\n");
		return -1;
	}	
	live_shaders.run(argv[1]);

	return 0;
}

