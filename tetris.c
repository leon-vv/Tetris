
#include <stdio.h>
#include <time.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "nanovg/src/nanovg.h"
#define NANOVG_GL3_IMPLEMENTATION
#include "nanovg/src/nanovg_gl.h"

#define OUTLINE_WIDTH 2

#include "utils.c"
#include "tetronimo.c"
#include "draw.c"

board b;

int main() {

	GLFWwindow *window = create_window();
	NVGcontext *vg = create_vg(window);

	srand(time(NULL));

	while(!glfwWindowShouldClose(window)) {

		enum tetronimo_type t = rand() % 7;
		struct tetronimo current = tetronimos[t];
		struct point upper_left = {4, 10};

		begin_frame(window, vg);
		
		int win_width, win_height;
		glfwGetWindowSize(window, &win_width, &win_height);

		draw_board_and_tetronimo(vg,
				b,
				win_width,
				win_height,
				current,
				upper_left);

		end_frame(window, vg);
	}

	return 0;
}
