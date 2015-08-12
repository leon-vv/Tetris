
// X or Y Coordinate
typedef signed char coord;

struct point {
	coord x;
	coord y;
};

typedef struct point blocks[4];

struct tetronimo {
	// Dimension of the rectangular area a tetronimo rotates in
	const unsigned char width;
	const unsigned char height;

	// Defines the point the tetronimo rotates around;
	blocks b;
};

const struct tetronimo I = {8, 8, {{-3, 1}, {-1, 1}, {1, 1}, {3, 1}}};
const struct tetronimo O = {4, 4, {{-1, 1}, {1, 1}, {-1, -1}, {1, -1}}};
const struct tetronimo T = {6, 4, {{0, 2}, {-2, 0}, {0, 0}, {2, 0}}};
const struct tetronimo S = {6, 4, {{0, 2}, {2, 2}, {-2, 0}, {0, 0}}};
const struct tetronimo Z = {6, 4, {{-2, 2}, {0, 2}, {0, 0}, {2, 0}}};
const struct tetronimo J = {6, 4, {{-2, 2}, {-2, 0}, {0, 0}, {2, 0}}};
const struct tetronimo L = {6, 4, {{-2, 0}, {0, 0}, {2, 0}, {2, 2}}};

enum color {
	WHITE = 0,
	BLACK = 1
};

const NVGcolor nvg_colors[2] = {
	(NVGcolor) {1.0, 1.0, 1.0, 1.0},
	(NVGcolor) {0.0, 0.0, 0.0, 1.0}
};

// 20 rows of 10 cells
typedef enum color board[20][10];

// Rotate clockwise
// This function uses a rotation matrix:
// [  0 1 ]
// [ -1 0 ]
// multiplications with 0 are left out
void
rotate_cw(blocks b)
{
	for(int i = 0; i < 4; i++)
		b[i] = (struct point){b[i].y, -b[i].x};
}

// Rotate counter clockwise
// This function uses a rotation matrix:
// [ 0 -1 ]
// [ 1  0 ]
// multiplications with 0 are left out
void
rotate_ccw(blocks b)
{
	for(int i = 0; i < 4; i++)
		b[i] = (struct point){-b[i].y, b[i].x};
}

void
draw_line(NVGcontext *vg,
		enum color line[10],
		float x,
		float y,
		float cell_w,
		float cell_h)
{
	for(int i = 0; i < 10; i++) {
		nvgBeginPath(vg);
		nvgRect(vg, x + i * cell_w, y, cell_w, cell_h);
		nvgFillColor(vg, nvg_colors[line[i]]);
		nvgFill(vg);
	}
}

void
draw_board(NVGcontext *vg, board b, float x, float y, float width, float height)
{
	//Outline
	nvgBeginPath(vg);

	nvgRect(vg, x , y, width, height);
	nvgStrokeColor(vg, nvgRGB(0, 0, 0));
	nvgStrokeWidth(vg, OUTLINE_WIDTH);
	nvgStroke(vg);

	// The stroke is applied with the path in the middle of the stroke.
	// Therefore to incalculate the width of the outline, we have to
	// decrease the width of the board with half the width of the left stroke
	// and half the width of the right stroke
	width -= OUTLINE_WIDTH;
	height -= OUTLINE_WIDTH;
	x += OUTLINE_WIDTH / 2.0;
	y += OUTLINE_WIDTH / 2.0;

	float cell_width = width / 10.0;
	float cell_height = height / 20.0;
	
	for(int i = 0; i < 20; i++)
		draw_line(vg,
				b[i],
				x,
				y + i*cell_height,
				cell_width,
				cell_height);
}
