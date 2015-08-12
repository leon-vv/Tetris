
#include <stdio.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "nanovg/src/nanovg.h"
#define NANOVG_GL3_IMPLEMENTATION
#include "nanovg/src/nanovg_gl.h"

#define OUTLINE_WIDTH 2

#include "utils.c"
#include "tetronimo.c"

board b;

int main() {

	GLFWwindow *window = create_window();
	NVGcontext *vg = create_vg(window);

	while(!glfwWindowShouldClose(window)) {
		begin_frame(window, vg);
		
		int win_width, win_height;
		glfwGetWindowSize(window, &win_width, &win_height);

		draw_board(vg,
				b,
				.05 * win_width,
				.05 * win_height,
				.60 * win_width,
				.90 * win_height);

		end_frame(window, vg);
	}

	return 0;
}
