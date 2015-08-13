
void
copy_tetr_to_board(struct active_tetronimo t, board brd)
{
	blocks blks;
	translate_upper_left_to_origin(t.tetr, blks);

	for(int i = 0; i < 4; i++) {
		int y = t.upper_left.y + blks[i].y/2;
		int x = t.upper_left.x + blks[i].x/2;
		brd[y][x] = BLACK;
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
			if(b[i][j] != BLACK) goto outer;

		*lines += 1;
		memmove(b + 1, b, i * 10 * c_size);
		memcpy(b, empty_line, 10 * c_size);
	}
}

void
active_tetr_to_board_coord(struct active_tetronimo active_t, blocks b)
{
	translate_upper_left_to_origin(active_t.tetr, b);

	for(int i = 0; i < 4; i++) {
		b[i].x = (b[i].x/2) + active_t.upper_left.x;
		b[i].y = (b[i].y/2) + active_t.upper_left.y;
	}
}

void
with_board_coords(struct active_tetronimo active_t, void (*f)(blocks))
{
	blocks b;
	active_tetr_to_board_coord(active_t, b);
	f(b);
}


