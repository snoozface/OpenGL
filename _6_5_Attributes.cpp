#include "_6_5_Attributes.h"
#include "Game.h"
#include "Renderer.h"

#include <iostream>
#include <vector>

void _6_5_Attributes()
{
	/*
	* To have more attribuites you can shove them all in the same vector
	* 
	* In the following example there are two sets of data in the same vector
	* it will have position and color.
	*/

	std::vector<float> vertices{
		// postitions			// colors
		 0.5f, -0.5f, 0.0f,		1.0f, 0.0f, 0.0f,	// bottom right
		-0.5f, -0.5f, 0.0f,		0.0f, 1.0f, 0.0f,	// bottom left
		 0.0f,  0.5f, 0.0f,		0.0f, 0.0f, 1.0f	// top
	};

	Game game;
	game.initialize();
	Renderer renderer;
	

	size_t actor = game.addActor();
	renderer.bindVAO(game.getActor(actor));
	size_t VBO = renderer.addVBO(game.getActor(actor));
	renderer.bindVBO(game.getActor(actor), VBO);
	renderer.uploadVBO(game.getActor(actor), VBO, vertices);
	renderer.uploadVertices(game.getActor(actor), vertices);

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

}