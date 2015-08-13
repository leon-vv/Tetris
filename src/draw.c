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
		struct active_tetronimo t,
		float x,
		float y,
		float cell_w,
		float cell_h)
{
	blocks b;
	translate_upper_left_to_origin(t.tetr, b);
	
	float upper_left_x = x + t.upper_left.x * cell_w;
	float upper_left_y = y + t.upper_left.y * cell_h;

	for(int i = 0; i < 4; i++) {
		struct point p = b[i];	

		float new_y = upper_left_y + (p.y/2) * cell_h;

		if(new_y < y) continue;

		nvgBeginPath(vg);
		nvgRect(vg,
				upper_left_x + (p.x/2) * cell_w,
				new_y,
				cell_w,
				cell_h);
		nvgFillColor(vg, nvg_colors[t.tetr.c]);
		nvgFill(vg);
	}
}

void
draw_text(NVGcontext *vg,
		float x,
		float y,
		unsigned lines)
{
	nvgFontFace(vg, "robo");
	nvgFontSize(vg, 50);
	nvgFillColor(vg, nvgRGB(0, 0, 0));
	char buffer[10];
	sprintf(buffer, "%u", lines);
	nvgText(vg, x, y, buffer, NULL);
}

void
draw_game(NVGcontext *vg,
		GLFWwindow *window,
		board b,
		struct active_tetronimo at,
		unsigned lines)
{
	begin_frame(window, vg);

	int win_width, win_height;
	glfwGetWindowSize(window, &win_width, &win_height);

	float x = .05 * win_width;
	float y =.05 * win_height;
	float board_width = .45 * win_height;
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

		
	draw_text(vg,
			.60 * win_height,	
			y + 30,
			lines);

	float cell_w = board_width / 10;
	float cell_h = board_height / 20;

	draw_blocks(vg, b, x, y, cell_w, cell_h);

	//x += at.upper_left.x * cell_w;
	//y += at.upper_left.y * cell_h;
	draw_tetronimo(vg, at, x, y, cell_w, cell_h);

	end_frame(window, vg);
}
