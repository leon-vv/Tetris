
void
active_tetr_to_board_coord(struct active_tetronimo active_t, blocks b)
{
	translate_upper_left_to_origin(active_t.tetr, b);

	for(int i = 0; i < 4; i++) {
		b[i].x = (b[i].x/2) + active_t.upper_left.x;
		b[i].y = (b[i].y/2) + active_t.upper_left.y;
	}
}


bool
is_valid(struct active_tetronimo t, board brd)
{
	blocks coords;
	active_tetr_to_board_coord(t, coords);
	
	for(int i = 0; i < 4; i++) {
		struct point current = coords[i];

		if(current.y > 0 &&
				(current.y > 19
				|| current.x > 9
				|| current.x < 0
				|| brd[current.y][current.x] != 0)) {
			return false;
		}
	}

	return true;
}

// Rotate clockwise
// This function uses a rotation matrix:
// [  0 1 ]
// [ -1 0 ]
// multiplications with 0 are left out
void
rotate_cw_if_valid(struct active_tetronimo *t, board brd)
{
	blocks old;
	memcpy(old, t->tetr.b, sizeof(blocks));

	for(int i = 0; i < 4; i++)
		t->tetr.b[i] = (struct point){t->tetr.b[i].y, -t->tetr.b[i].x};

	if(!is_valid(*t, brd))
		memcpy(t->tetr.b, old, sizeof(blocks));
}


void
copy_tetr_to_board(struct active_tetronimo t, board brd)
{
	blocks blks;
	translate_upper_left_to_origin(t.tetr, blks);

	for(int i = 0; i < 4; i++) {
		int y = t.upper_left.y + blks[i].y/2;
		int x = t.upper_left.x + blks[i].x/2;
		brd[y][x] = t.tetr.c;
	}
}

void
check_full(board b, unsigned *lines)
{
	const enum color empty_line[10] = {WHITE};
	int c_size = sizeof(enum color);	
	int i = -1;

outer:
	for(i++; i < 20;) {
		int j = 0;
		for(; j < 10; j++)
			if(b[i][j] == WHITE) goto outer;

		*lines += 1;
		memmove(b + 1, b, i * 10 * c_size);
		memcpy(b, empty_line, 10 * c_size);
	}
}

void
with_board_coords(struct active_tetronimo active_t, void (*f)(blocks))
{
	blocks b;
	active_tetr_to_board_coord(active_t, b);
	f(b);
}


