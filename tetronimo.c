// X or Y Coordinate
typedef signed char coord;

struct point {
	coord x;
	coord y;
};

typedef struct point blocks[4];

struct tetronimo {
	// Dimension of the square area a tetronimo rotates in
	unsigned char size;

	blocks b;
};

enum tetronimo_type {
	I = 0,
	O = 1,
	T = 2,
	S = 3,
	Z = 4,
	J = 5,
	L = 6
};

struct active_tetronimo {
	struct tetronimo tetr;
	struct point upper_left;
};

const struct tetronimo tetronimos[7] = {
	{8, {{-3, 1}, {-1, 1}, {1, 1}, {3, 1}}},
	{4, {{-1, 1}, {1, 1}, {-1, -1}, {1, -1}}},
	{6, {{0, 2}, {-2, 0}, {0, 0}, {2, 0}}},
	{6, {{0, 2}, {2, 2}, {-2, 0}, {0, 0}}},
	{6, {{-2, 2}, {0, 2}, {0, 0}, {2, 0}}},
	{6, {{-2, 2}, {-2, 0}, {0, 0}, {2, 0}}},
	{6, {{-2, 0}, {0, 0}, {2, 0}, {2, 2}}}
};

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

// Translates the blocks such that the upper left block
// is at position (0, 0)
void
translate_upper_left_to_origin(struct tetronimo t, blocks b)
{
	int tx = (t.size / 2) - 1;
	int ty = 1 - (t.size / 2);

	for(int i = 0; i < 4; i++) 
		b[i] = (struct point){t.b[i].x + tx, t.b[i].y + ty};
}



