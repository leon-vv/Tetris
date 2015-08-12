void
draw_outline(NVGcontext *vg, float x, float y, float width, float height)
{
	nvgBeginPath(vg);
	nvgRect(vg, x , y, width, height);
	nvgStrokeColor(vg, nvgRGB(0, 0, 0));
	nvgStrokeWidth(vg, OUTLINE_WIDTH);
	nvgStroke(vg);
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
draw_blocks(NVGcontext *vg,
		board b,
		float x,
		float y,
		float cell_w,
		float cell_h)
{
	for(int i = 0; i < 20; i++)
		draw_line(vg,
				b[i],
				x,
				y + i*cell_h,
				cell_w,
				cell_h);
}

void
draw_tetronimo(NVGcontext *vg,
		struct tetronimo t,
		float x,
		float y,
		float cell_w,
		float cell_h)
{
	blocks b;
	translate_upper_left_to_origin(t, b);
	
	for(int i = 0; i < 4; i++) {
		struct point p = b[i];	

		nvgBeginPath(vg);
		nvgRect(vg,
				x + (p.x/2) * cell_w,
				y + (p.y/2) * cell_h,
				cell_w,
				cell_h);
		nvgFillColor(vg, nvg_colors[BLACK]);
		nvgFill(vg);
	}
}

void
draw_board_and_tetronimo(NVGcontext *vg,
		board b,
		int win_width,
		int win_height,
		struct tetronimo t,
		struct point upper_left)
{
	float x = .05 * win_width;
	float y =.05 * win_height;
	float board_width = .60 * win_width;
	float board_height = .90 * win_height;

	draw_outline(vg, x, y, board_width, board_height);

	// The stroke is applied with the path in the middle of the stroke.
	// Therefore to incalculate the width of the outline, we have to
	// decrease the width of the board with half the width of the left stroke
	// and half the width of the right stroke (thus once the OUTLINE_WIDTH)
	board_width -= OUTLINE_WIDTH;
	board_height -= OUTLINE_WIDTH;
	x += OUTLINE_WIDTH / 2.0;
	y += OUTLINE_WIDTH / 2.0;

	float cell_w = board_width / 10;
	float cell_h = board_height / 20;

	draw_blocks(vg, b, x, y, cell_w, cell_h);

	x += upper_left.x * cell_w;
	y += upper_left.y * cell_h;
	draw_tetronimo(vg, t, x, y, cell_w, cell_h);
}
