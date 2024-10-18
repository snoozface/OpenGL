#include "Game.h"

bool Game::initialize()
{
	/*
	* Initialize GLFW and set version and profile
	*/
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	/*
	* Create GLFW window and set context
	*/
	m_window = glfwCreateWindow(800, 600, "OpenGL Practice", nullptr, nullptr);
	if (m_window == nullptr)
	{
		std::cerr << "Failed to create GLFW window.\n";
		return false;
	}
	glfwMakeContextCurrent(m_window);

	/*
	* Initialize GLAD and set viewport
	*/
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cerr << "Failed to initialize GLAD.\n";
		return false;
	}
	glViewport(0, 0, 800, 600);

	return true;
}

void Game::runLoop()
{
	while (!glfwWindowShouldClose(m_window))
	{
		processInput();
		updateProgram();
		generateOutput();
		pollEvents();

		glfwSwapBuffers(m_window);
	}
}

void Game::processInput()
{
	/*
	* glfwGetKey returns the LAST key pressed only. If you need to handle more than
	* just the last key, or a situation where the key is pressed so fast it has been released
	* when this check happens, you need to use the key_callback functionality
	*/
	if (glfwGetKey(m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(m_window, true);
	}
}

void Game::updateProgram()
{
}

void Game::generateOutput()
{
	// Clear window with solid color
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);


	// For each loop renders each object in m_actors
	for (Actor& actor : m_actors)
		actor.render(GL_TRIANGLES);


}

void Game::pollEvents()
{
	glfwPollEvents();
}

size_t Game::addActor()
{
	Actor actor{};
	m_actors.push_back(actor);

	return m_actors.size() - 1;
}
