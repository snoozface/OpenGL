//#include "Exercises_5_8.h"
//
//
//
//#include "Program.h"
//
//#include <iostream>
//
//
//
//
//int exercises_5_8()
//{
//	//const char* vertexShaderSource = "#version 330 core\n"
//	//	"layout (location = 0) in vec3 aPos;\n"
//	//	"void main()\n"
//	//	"{\n"
//	//	"gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
//	//	"}\n";
//
//	//const char* fragmentShaderSourceOrange = "#version 330 core\n"
//	//	"out vec4 FragColor;\n"
//	//	"void main()\n"
//	//	"{\n"
//	//	"FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);"
//	//	"}\n";
//
//	//const char* fragmentShaderSourceYellow = "#version 330 core\n"
//	//	"out vec4 FragColor;\n"
//	//	"void main()\n"
//	//	"{\n"
//	//	"FragColor = vec4(1.0f, 0.96f, 0.0f, 1.0f);"
//	//	"}\n";
//
//	Program program;
//
//	if (!program.initialize())
//	{
//		std::cerr << "Error initializing. Program shutting down.\n";
//		return -1;
//	}
//
//	// Make Shader Program
//	size_t shader = program.addShader();
//	program.createShaderProgram("VertexShader1.vert", "FragmentShader1.frag", shader);
//	//program.createShaderProgram(vertexShaderSource, fragmentShaderSourceOrange, shaderOrange);
//	//size_t shaderYellow = program.addShader();
//	//program.createShaderProgram(vertexShaderSource, fragmentShaderSourceYellow, shaderYellow);
//
//
//	 //Actor 1 - First Triangle
//	std::vector<float> vertices1{
//		-0.25f, 0.25f, 0.0f,	// Top left
//		-0.25f, -0.25f, 0.0f,	// Bottom left
//		-0.75f, -0.25f, 0.0f	// Bottom right
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
//	// Actor 2 - Second Triangle
//	std::vector<float> vertices2{
//		0.75f, 0.25f, 0.0f,		// Top right
//		0.75f, -0.25f, 0.0f,	// Bottom right
//		0.25f, -0.25f, 0.0f		// Bottom left
//	};
//
//	size_t actor2 = program.addActor();
//	program.bindVAO(actor2);
//	size_t VBO2 = program.addVBO(actor2);
//	program.bindVBO(actor2, VBO2);
//	//program.uploadVBO(actor2, VBO2, vertices2.size() * sizeof(float), vertices2.data(), GL_STATIC_DRAW);
//	program.uploadVertices(actor2, vertices2);
//	program.linkVertexAttributes(actor2, 0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
//	program.connectShader(actor2, shader);
//	program.unbindVAO(actor2);
//	program.unbindVBO(actor2, VBO2);
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
//
//
//	return 0;
//}
