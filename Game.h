#ifndef GAME_H
#define GAME_H

#include "Actor.h"



class Game
{
private:
	GLFWwindow* m_window{ nullptr };

	// Vector of Actors
	// Each Actor manages its own VAO and a pointer to the shader it uses
	std::vector<Actor> m_actors{};

public:
	Game()
	{}

	bool initialize();

	void runLoop();

private:
	// Loop functions
	void processInput();
	void updateProgram();
	void generateOutput();
	void pollEvents();


public:
	void shutdown() { glfwTerminate(); }



	// Manage children

	// ***************************************************
	// Actor

	// Add actor to m_actors
	size_t addActor();

	// Get reference to actor
	Actor& getActor(size_t actorIndex) { return m_actors[actorIndex]; }
};

#endif