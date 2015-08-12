
#include <stdio.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "nanovg/src/nanovg.h"
#define NANOVG_GL3_IMPLEMENTATION
#include "nanovg/src/nanovg_gl.h"

#include "utils.c"
#include "tetronimo.c"

int main() {

	GLFWwindow *window = create_window();
	NVGcontext *vg = create_vg();
	

	return 0;
}
