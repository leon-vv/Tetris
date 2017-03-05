#include <stdbool.h>
#include <stdio.h>
#include <time.h>
#include <pthread.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../nanovg/src/nanovg.h"
#define NANOVG_GL3_IMPLEMENTATION
#include "../nanovg/src/nanovg_gl.h"

#define OUTLINE_WIDTH 2

#include "tetronimo.c"
#include "collision.c"
#include "utils.c"
#include "draw.c"

NVGcontext *vg;
struct active_tetronimo active_tetr;
board b;
unsigned lines = 0;

void
new_tetr(board b, unsigned *lines)
{
	copy_tetr_to_board(active_tetr, b);
	check_full(b, lines);

	active_tetr.tetr = tetronimos[rand() % 7];
	active_tetr.upper_left = (struct point){4, -1};
}

void
fall(blocks blcks)
{
	int valid_downs = -1;

	for(int i = 0; i < 4; i++) {

		int j = 0;
		for(; j < 20 && b[j][blcks[i].x] == WHITE; j++) {}

		int current_valid = j - blcks[i].y - 1;

		if(current_valid < valid_downs || valid_downs == -1)
			valid_downs = current_valid;
	}

	for(int i = 0; i < valid_downs; i++)
		active_tetr.upper_left.y += 1;

	new_tetr(b, &lines);
}

void
with_active_board_coords(void (*callback)(blocks))
{
	blocks blcks;
	active_tetr_to_board_coord(active_tetr, blcks);
	callback(blcks);
}

void
down(blocks blcks)
{
	for(int i = 0; i < 4; i++) {

		if(blcks[i].y == 19
				|| (blcks[i].y != -2 && b[blcks[i].y + 1][blcks[i].x] != WHITE)) {
			
			if(blcks[i].y == -1) {
				printf("You got a score of %u!\n", lines);
				exit(0);
			}

			new_tetr(b, &lines);
			return;
		}
	}
	

	active_tetr.upper_left.y += 1;
}

void
left(blocks blcks)
{
	for(int i = 0; i < 4; i++) {
		struct point current = blcks[i];		

		// If the tetronimo stick above the top border
		// we do not want to block the movement
		if(current.y < 0) continue;

		// Block the movement
		if(current.x == 0
			|| b[current.y][current.x - 1] != WHITE) return;
	}

	active_tetr.upper_left.x -= 1;
}

void
right(blocks blcks)
{
	for(int i = 0; i < 4; i++)
	{
		struct point current = blcks[i];

		if(current.x == 9 || b[current.y][current.x + 1] != WHITE)
			return;
	}

	active_tetr.upper_left.x += 1;
}

void
ticker(GLFWwindow *window, int key, int scancode, int action, int mods)
{

	if(action == GLFW_PRESS || action == GLFW_REPEAT) {
		switch (key) {
			case GLFW_KEY_UP:
				rotate_cw_if_valid(&active_tetr, b);
				break;
			case GLFW_KEY_LEFT:
				with_active_board_coords(left);
				break;
			case GLFW_KEY_RIGHT:
				with_active_board_coords(right);
				break;
			case GLFW_KEY_DOWN:
				with_active_board_coords(down);
				break;
			case GLFW_KEY_SPACE:
				with_active_board_coords(fall);
				break;
		};
	}
}

void*
time_func(void *arg)
{
	double delay = *(double*)arg;

	struct timespec time;

	time.tv_sec = delay; // Rounded by int conversion
	time.tv_nsec = (delay - (double)time.tv_sec) * (double)1e9;

	for(;;) {
		glfwPostEmptyEvent();
		nanosleep(&time, NULL);
	}
}

int main(int argc, char** argv)
{
	GLFWwindow *window = create_window();
	vg = create_vg(window);

	glfwSetKeyCallback(window, ticker);

	srand(time(NULL));

	active_tetr.tetr = tetronimos[rand() % 7];
	active_tetr.upper_left = (struct point){4, -1};

	double *delay = malloc(sizeof(double));

	*delay = argc < 2 ? .5 : strtof(argv[1], NULL);

	pthread_t time_thread;
	pthread_create(&time_thread, NULL, time_func, (void*)delay);


	while(!glfwWindowShouldClose(window)) {
		glfwWaitEvents();

		if(glfwGetTime() > *delay) {
			with_active_board_coords(down);
			glfwSetTime(0.0);
		}

		draw_game(vg, window, b, active_tetr, lines);
	}

	free(delay);

	return 0;
}
