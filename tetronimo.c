
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
void rotate_ccw(blocks b)
{
	for(int i = 0; i < 4; i++)
		b[i] = (struct point){-b[i].y, b[i].x};
}
