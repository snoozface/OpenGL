

#include "Game.h"
#include "Renderer.h"

#include <iostream>
#include <vector>


#include "_7_1_Textures.h"




int main()
{
	//_7_6_Textures();
	Game game;
	game.initialize();
	Renderer renderer;
	std::vector<float> vertices{
		// positions		// colors		 
		 0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f,	// top right
		 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,	// bottom right
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f,	// bottom left
		-0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 0.0f,	// top left
	};
	std::vector<unsigned int> indices{
		0, 1, 3,  // first triangle
		1, 2, 3   // second triangle
	};

	size_t actor = game.addActor();
	renderer.bindVAO(game.getActor(actor));
	size_t VBO = renderer.addVBO(game.getActor(actor));
	renderer.bindVBO(game.getActor(actor), VBO);
	renderer.uploadVBO(game.getActor(actor), VBO, vertices);
	renderer.uploadVertices(game.getActor(actor), vertices);

	renderer.addEBO(game.getActor(actor));
	renderer.bindEBO(game.getActor(actor));
	renderer.uploadEBO(game.getActor(actor), indices);
	renderer.uploadIndices(game.getActor(actor), indices);


	// create shader
	size_t shader = renderer.addShader();
	renderer.createShaderProgram("Vert_6_5_Attributes.vert", "Frag_6_5_Attributes.frag", shader);



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

	return 0;
}

