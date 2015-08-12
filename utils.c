
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
	glewExperimental = GL_TRUE;

	if(glewInit() != GLEW_OK) error("Could not init glew");
	glGetError();

	return window;
}

NVGcontext*
create_vg()
{
	NVGcontext *vg = nvgCreateGL3(NVG_ANTIALIAS | NVG_DEBUG);

	if(vg == NULL) error("Could not init nanovg");
	
	return vg;
}
