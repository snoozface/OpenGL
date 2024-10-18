#include "Exercises_6_8.h"

#include "Game.h"
#include "Renderer.h"

void exercises_6_8_1()
{
	Game game{};
	game.initialize();

	Renderer renderer{};

	std::vector<float> vertices{
		// postitions			// colors
		 0.5f, -0.5f, 0.0f,		1.0f, 0.0f, 0.0f,	// bottom right
		-0.5f, -0.5f, 0.0f,		0.0f, 1.0f, 0.0f,	// bottom left
		 0.0f,  0.5f, 0.0f,		0.0f, 0.0f, 1.0f	// top
	};

	size_t actor = game.addActor();
	renderer.bindVAO(game.getActor(actor));
	size_t VBO = renderer.addVBO(game.getActor(actor));
	renderer.bindVBO(game.getActor(actor), VBO);
	renderer.uploadVBO(game.getActor(actor), VBO, vertices);
	renderer.uploadVertices(game.getActor(actor), vertices);


	// create shader
	size_t shader = renderer.addShader();
	renderer.createShaderProgram("Vert_6_8_Exercise1.vert", "Frag_6_8_Exercise1.frag", shader);



	// have to link two attributes because the vertex shader has two attributes, one for pos and one for color

	// link position attribute location 0
	// location 0, size 3 (vec3)
	// stride is 6 because there are vec3 position and vec 3 color
	// offset is 0 because position is at the beginning 
	renderer.linkVertexAttributes(game.getActor(actor), 0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);

	// link color attribute location 1
	// location 1, size 3
	// stride is 6 again
	// offset is 3 because color comes after the vec3 position
	renderer.linkVertexAttributes(game.getActor(actor), 1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));

	renderer.connectShader(game.getActor(actor), shader);


	game.runLoop();
	game.shutdown();
}

void exercises_6_8_2()
{
	Game game{};
	game.initialize();

	Renderer renderer{};

	std::vector<float> vertices{
		// postitions			// colors
		 0.5f, -0.5f, 0.0f,		1.0f, 0.0f, 0.0f,	// bottom right
		-0.5f, -0.5f, 0.0f,		0.0f, 1.0f, 0.0f,	// bottom left
		 0.0f,  0.5f, 0.0f,		0.0f, 0.0f, 1.0f	// top
	};

	size_t actor = game.addActor();
	renderer.bindVAO(game.getActor(actor));
	size_t VBO = renderer.addVBO(game.getActor(actor));
	renderer.bindVBO(game.getActor(actor), VBO);
	renderer.uploadVBO(game.getActor(actor), VBO, vertices);
	renderer.uploadVertices(game.getActor(actor), vertices);


	// create shader
	size_t shader = renderer.addShader();
	renderer.createShaderProgram("Vert_6_8_Exercise2.vert", "Frag_6_8_Exercise2.frag", shader);
	renderer.useShaderProgram(shader);

	// Set uniform data
	// Uniform 'xOffset' is declared in Vert_6_8_Exercise2.vert
	renderer.setUniformFloat1(shader, "xOffset", 0.5f);



	// have to link two attributes because the vertex shader has two attributes, one for pos and one for color

	// link position attribute location 0
	// location 0, size 3 (vec3)
	// stride is 6 because there are vec3 position and vec 3 color
	// offset is 0 because position is at the beginning 
	renderer.linkVertexAttributes(game.getActor(actor), 0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);

	// link color attribute location 1
	// location 1, size 3
	// stride is 6 again
	// offset is 3 because color comes after the vec3 position
	renderer.linkVertexAttributes(game.getActor(actor), 1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));

	renderer.connectShader(game.getActor(actor), shader);


	game.runLoop();
	game.shutdown();
}

void exercises_6_8_3()
{
	Game game{};
	game.initialize();

	Renderer renderer{};

	std::vector<float> vertices{
		// postitions
		 0.5f, -0.5f, 0.0f,	// bottom right
		-0.5f, -0.5f, 0.0f,	// bottom left
		 0.0f,  0.5f, 0.0f	// top
	};

	size_t actor = game.addActor();
	renderer.bindVAO(game.getActor(actor));
	size_t VBO = renderer.addVBO(game.getActor(actor));
	renderer.bindVBO(game.getActor(actor), VBO);
	renderer.uploadVBO(game.getActor(actor), VBO, vertices);
	renderer.uploadVertices(game.getActor(actor), vertices);


	// create shader
	size_t shader = renderer.addShader();
	renderer.createShaderProgram("Vert_6_8_Exercise3.vert", "Frag_6_8_Exercise3.frag", shader);




	// have to link two attributes because the vertex shader has two attributes, one for pos and one for color

	// link position attribute location 0
	// location 0, size 3 (vec3)
	// stride is 6 because there are vec3 position and vec 3 color
	// offset is 0 because position is at the beginning 
	renderer.linkVertexAttributes(game.getActor(actor), 0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);



	renderer.connectShader(game.getActor(actor), shader);


	game.runLoop();
	game.shutdown();
}
