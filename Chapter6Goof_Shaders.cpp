//#include "Chapter6Goof_Shaders.h"
//
//#include "Program.h"
//
//#include <iostream>
//
//void chapter6goof()
//{
//
//
//
//	Program program;
//
//	program.initialize();
//
//	// Make Shader Program
//	size_t shader = program.addShader();
//	program.createShaderProgram("Vert_6_4_Uniforms.vert", "Frag_6_4_Uniforms.frag", shader);
//
//
//
//	//Actor 1 - First Triangle
//	std::vector<float> vertices1{
//		-0.5f, -0.5f, 0.0f,		// Bottom left
//		0.5f, -0.5f, 0.0f,		// Bottom right
//		0.0f, 0.5f, 0.0f		// Top centre
//	};
//
//
//	size_t actor1 = program.addActor();
//	program.bindVAO(actor1);
//	size_t VBO1 = program.addVBO(actor1);
//	program.bindVBO(actor1, VBO1);
//	//program.uploadVBO(actor1, VBO1, vertices1.size() * sizeof(float), vertices1.data(), GL_STATIC_DRAW);
//	program.uploadVertices(actor1, vertices1);
//	program.linkVertexAttributes(actor1, 0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
//	program.connectShader(actor1, shader);
//	program.unbindVAO(actor1);
//	program.unbindVBO(actor1, VBO1);
//
//
//
//
//
//
//
//
//
//
//
//	program.runLoop();
//
//	program.shutdown();
//}
