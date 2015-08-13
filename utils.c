
void
error(char *s)
{
	fputs(s, stderr);
	exit(-1);
}

GLFWwindow*
create_window()
{
	if(!glfwInit()) error("Failed to init GLFW");

	#ifndef _WIN32 // don't require this on win32, and works with more cards
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	#endif

	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, 1);

	GLFWwindow* window = glfwCreateWindow(600, 500, "Tetris", NULL, NULL);

	if(!window) {
		glfwTerminate();
		error("Failed to create GLFW window");
	}

	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);
	glewExperimental = GL_TRUE;

	if(glewInit() != GLEW_OK) error("Could not init glew");
	glGetError();
	
	return window;
}

NVGcontext*
create_vg()
{
	NVGcontext *vg = nvgCreateGL3(NVG_DEBUG);

	glDisable(GL_BLEND);
	glClearColor(1,1,1,1);

	if(vg == NULL) error("Could not init nanovg");
	
	return vg;
}

void
begin_frame(GLFWwindow *w, NVGcontext *c)
{
	int win_width, win_height, fb_width, fb_height;
	glfwGetWindowSize(w, &win_width, &win_height);
	glfwGetFramebufferSize(w, &fb_width, &fb_height);
	float px_ratio = (float)fb_width / (float)fb_height;
	
	glViewport(0, 0, fb_width, fb_height);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	nvgBeginFrame(c, win_width, win_height, px_ratio);
}

void
end_frame(GLFWwindow *w, NVGcontext *c)
{
	nvgEndFrame(c);
	glfwSwapBuffers(w);
}
