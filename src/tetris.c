
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
struct active_tetronimo active_t;
board b;
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
fall()
{
	blocks blcks;
	active_tetr_to_board_coord(active_t, blcks);
	
	int valid_downs = -1;

	for(int i = 0; i < 4; i++) {

		int j = 0;
		for(; j < 20 && b[j][blcks[i].x] == WHITE; j++) {}

		int current_valid = j - blcks[i].y - 1;

		if(current_valid < valid_downs || valid_downs == -1)
			valid_downs = current_valid;
	}

	for(int i = 0; i < valid_downs; i++)
		active_t.upper_left.y += 1;

	new_tetr(b, &lines);
}

void
down()
{
	blocks blcks;
	active_tetr_to_board_coord(active_t, blcks);

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
				rotate_cw_if_valid(&active_t, b);
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
			case GLFW_KEY_SPACE:
				fall();
				break;
		};
	}
}

void*
time_func(void *arg)
{
	double delay = *(double*)arg;
	int sec = delay;
	// Three digits of accuracy
	long milliseconds = (delay - (double)sec) * (double)1000;

	struct timespec time = {sec, milliseconds * 1000000};

	int counter = 0;
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

	active_t.tetr = tetronimos[rand() % 7];
	active_t.upper_left = (struct point){4, -1};

	double *delay = malloc(sizeof(double));

	*delay = argc < 2 ? .5 : strtof(argv[1], NULL);

	pthread_t time_thread;
	pthread_create(&time_thread, NULL, time_func, (void*)delay);


	while(!glfwWindowShouldClose(window)) {
		glfwWaitEvents();

		if(glfwGetTime() > *delay) {
			down();
			glfwSetTime(0.0);
		}

		draw_game(vg, window, b, active_t, lines);
	}

	return 0;
}
