
#include <stdbool.h>
#include <stdio.h>
#include <time.h>
#include <pthread.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "nanovg/src/nanovg.h"
#define NANOVG_GL3_IMPLEMENTATION
#include "nanovg/src/nanovg_gl.h"

#define OUTLINE_WIDTH 2

#include "tetronimo.c"
board b;
#include "utils.c"
#include "draw.c"
#include "collision.c"

NVGcontext *vg;
struct active_tetronimo active_t;
unsigned lines = 0;

void
new_tetr(board b, unsigned *lines)
{
	copy_tetr_to_board(active_t, b);
	check_full(b, lines);

	active_t.tetr = tetronimos[rand() % 7];
	active_t.upper_left = (struct point){4, -1};
}

void
down()
{
	blocks blcks;
	active_tetr_to_board_coord(active_t, blcks);

	for(int i = 0; i < 4; i++)
		if(blcks[i].y == 19 || b[blcks[i].y + 1][blcks[i].x] == BLACK) {
			new_tetr(b, &lines);
			return;
		}


	active_t.upper_left.y += 1;
}

void
left()
{
	blocks blcks;
	active_tetr_to_board_coord(active_t, blcks);

	for(int i = 0; i < 4; i++)
		if(blcks[i].x == 0 || b[blcks[i].y][blcks[i].x - 1] == BLACK)
			return;

	active_t.upper_left.x -= 1;
}

void
right()
{
	blocks blcks;
	active_tetr_to_board_coord(active_t, blcks);

	for(int i = 0; i < 4; i++)
		if(blcks[i].x == 9 || b[blcks[i].y][blcks[i].x + 1] == BLACK)
			return;

	active_t.upper_left.x += 1;
}

void
ticker(GLFWwindow *window, int key, int scancode, int action, int mods)
{

	if(action == GLFW_PRESS || action == GLFW_REPEAT) {
		switch (key) {
			case GLFW_KEY_UP:
				rotate_cw(active_t.tetr.b);
				break;
			case GLFW_KEY_LEFT:
				left();
				break;
			case GLFW_KEY_RIGHT:
				right();
				break;
			case GLFW_KEY_DOWN:
				down();
				break;
		};
	}
}

void*
time_func()
{
	const struct timespec time = {0, 500000000L};

	for(;;) {
		glfwPostEmptyEvent();
		nanosleep(&time, NULL);
	}
}

int main()
{
	GLFWwindow *window = create_window();
	vg = create_vg(window);

	glfwSetKeyCallback(window, ticker);

	srand(time(NULL));

	active_t.tetr = tetronimos[rand() % 7];
	active_t.upper_left = (struct point){4, -1};

	pthread_t time_thread;
	pthread_create(&time_thread, NULL, time_func, NULL);

	while(!glfwWindowShouldClose(window)) {
		glfwWaitEvents();

		if(glfwGetTime() > .5) {
			down();
			glfwSetTime(0.0);
		}

		draw_game(vg, window, b, active_t, lines);
	}

	return 0;
}
