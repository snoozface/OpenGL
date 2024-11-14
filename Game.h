#ifndef GAME_H
#define GAME_H

#include "Actor.h"

#include <memory>
#include <unordered_map>

class Game
{
private:
	GLFWwindow* m_window{ nullptr };

	// Unordered map of Actors
	// Each Actor manages its own VAO, buffers, and a pointer to the shader it uses
	std::unordered_map<size_t, std::shared_ptr<Actor>> m_actors{};
	size_t m_actorID{ 0 };


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
	//Actor& getActor(size_t actorIndex) { return m_actors[actorIndex]; }
	std::shared_ptr<Actor> getActor(size_t actorIndex) { return m_actors[actorIndex]; }
};

#endif