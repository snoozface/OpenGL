#include "_7_1_Textures.h"

#include "Game.h"
#include "Renderer.h"

#include "stb_image.h"

void _7_1_Textures()
{
	/*
	*  Texture coordinates give information to the vertex shader about where
	*  in the texture image to sample.
	* 
	* The coordinates in this vector align with the coordinates of the triangle.
	* 
	* The fragment shader interpolates with this data like it does for other things.
	* 
	* Texture coordinates start at 0,0 in the lower-left and go to 1,1 in the upper-right.
	*/
	std::vector<float> texCoords{
		0.0f, 0.0f,		// lower-left corner
		1.0f, 0.0f,		// lower-right corner
		0.5f, 1.0f		// top-center corner
	};


	/*
	*	Texture wrapping.
	* 
	* If you enter texture coordinate values outside of 0-1 the texture will have to wrap.
	* 
	* By default OpenGL will repeat the texture (ignoring the integer part of the float), but 
	* there are other options:
	* 
	* • GL_REPEAT: The default behavior for textures. Repeats the texture image.
	* • GL_MIRRORED_REPEAT: Same as GL_REPEAT but mirrors the image with each repeat.
	* • GL_CLAMP_TO_EDGE: Clamps the coordinates between 0 and 1. The result is that higher
	*				coordinates become clamped to the edge, resulting in a stretched edge pattern.
	* • GL_CLAMP_TO_BORDER: Coordinates outside the range are now given a user-specified
	*				border color
	* 
	* The options can be set per coordinate axis (OpenGL uses s, t, r for x, y, z instead of u, v, w)
	*/

	// You can set the options above:
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

	// In order to use the clamp to border option you need to specify a border color:
	float borderColor[] = { 1.0f, 1.0f, 0.0f, 1.0f };
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);


	/*
	*	Texture Filtering.
	* 
	* Texture coordinates can be any floating point value so OpenGL has to figure out which
	* texture pixel (texel) to map the texture coordinate to.
	* 
	* GL_NEAREST (nearest neighbor or point filtering) is the default texture filtering method in OpenGL.
	* This simply selects the texel that is closest to the texture coordinate.
	* 
	* GL_LINEAR (known as (bi)linear filtering) takes an interpolated value from the texture coordinate's neighboring
	* texels, approximating a color between the texels.
	* 
	* Texture filtering can be set seperately for magnifying (when scaling up) or minifying (when scaling down)
	*/

	// Set magnifying texture filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	// Set minifying texture filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


	/*
	*	Mipmaps.
	* 
	* If you have objects that are very far away they are very small. This causes issues with texture sampling
	* because the texture coordinate covers a large portion of the texels which can cause visible artifacts on
	* small objects and is also a waste of memory bandwidth.
	* 
	* In order to deal with these issues you can use mipmaps which are a series of sequentially smaller (twice as
	* small) compared to the previous one.
	* 
	* OpenGL can automatically create mipmaps with a call to glGenerateMipmaps after we've created a texture.
	* 
	* Filtering options are also available:
	* • GL_NEAREST_MIPMAP_NEAREST: takes the nearest mipmap to match the pixel size and
	*				uses nearest neighbor interpolation for texture sampling.
	* • GL_LINEAR_MIPMAP_NEAREST: takes the nearest mipmap level and samples that level
	*				using linear interpolation.
	* • GL_NEAREST_MIPMAP_LINEAR: linearly interpolates between the two mipmaps that
	*				most closely match the size of a pixel and samples the interpolated level via 
	*				nearest neighbor interpolation.
	* • GL_LINEAR_MIPMAP_LINEAR: linearly interpolates between the two closest mipmaps
	*				and samples the interpolated level via linear interpolation.
	*/

	// Set filtering options for mipmaps:
	// Note: only use mimpap option for MINIFYING filter
	//		 using one for MAGNIFYING filter will result in a GL_INVALID_ENUM error code.
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


	/*
	*	Loading and creating textures.
	* 
	* To be able to use textures, they must first be loaded into the application.
	* 
	* std_image.h is a popular single header image loading library.
	* It's located here: github.com/nothings/stb/blob/master/stb_image.h
	* Also in: D:\Programming\C++\External\stb_image.h
	* 
	* Add the file to the project and make a cpp file with the following code:
	*		#define STB_IMAGE_IMPLEMENTATION
	*		#include "stb_image.h"
	* 
	* By defining STB_IMAGE_IMPLEMENTATION the preprocessor modifies the header file such
	* that it only contains the relevant definition source code, effectively turning the header file into a
	* .cpp file, and that’s about it. Now simply include stb_image.h somewhere in your program
	* and compile.
	*/

	// Load an image (container.jpg) using std_image.h's stbi_load function.
	// The function takes the location of the file as in input and gives the width, height, and
	// number of color channels as ints.
	int width, height, nrChannels;
	unsigned char* data = stbi_load("container.jpg", &width, &height, &nrChannels, 0);


	/*
	*	Generating a texture.
	* 
	* Like other objects, textures are referenced with an ID.
	* First argument is how many textures to generate
	* Second argument is either a Uint or an array of Uint that receives the ID value
	*/
	GLuint texture;
	glGenTextures(1, &texture);
	// Textures must also be bound for subsequent texture commands
	glBindTexture(GL_TEXTURE_2D, texture);
	/*
	*	Generate texture
	* 
	* • The first argument specifies the texture target; setting this to GL_TEXTURE_2D means this
	*			operation will generate a texture on the currently bound texture object at the same target (so
	*			any textures bound to targets GL_TEXTURE_1D or GL_TEXTURE_3D will not be affected).
	* • The second argument specifies the mipmap level for which we want to create a texture for if
	*			you want to set each mipmap level manually, but we’ll leave it at the base level which is 0.
	* • The third argument tells OpenGL in what kind of format we want to store the texture. Our
	*			image has only RGB values so we’ll store the texture with RGB values as well.
	* • The 4th and 5th argument sets the width and height of the resulting texture. We stored those
	*			earlier when loading the image so we’ll use the corresponding variables.
	* • The next argument should always be 0 (some legacy stuff).
	* • The 7th and 8th argument specify the format and datatype of the source image. We loaded the
	*			image with RGB values and stored them as chars (bytes) so we’ll pass in the corresponding
	*			values.
	* • The last argument is the actual image data.
	*/
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	// Automatically generate mipmaps
	glGenerateMipmap(GL_TEXTURE_2D);
	// Free the image memory
	stbi_image_free(data);

	/*
	* Up until this point the process of generating a texture is something like this:
			unsigned int texture;
			glGenTextures(1, &texture);
			glBindTexture(GL_TEXTURE_2D, texture);
			// set the texture wrapping/filtering options (on currently bound texture)
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			// load and generate the texture
			int width, height, nrChannels;
			unsigned char *data = stbi_load("container.jpg", &width, &height, &nrChannels, 0);
			if (data)
			{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
			}
			else
			{
			std::cout << "Failed to load texture" << std::endl;
			}
			stbi_image_free(data);
	*/

	/*
	*	Applying textures.
	* 
	* OpenGL needs to know how to sample the texture so the vertex data must be updated with the texture coords:
	*/

	std::vector<float> vertices{
		// positions		// colors		  // texture coords
		 0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,	// top right
		 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,	// bottom right
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,	// bottom left
		-0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f	// top left
	};
	// Update OpenGL vertex format (3 position, 3 color, 2 tex coord = 8 total * 4 byte = 32 stride)
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	/*
	* 	Also have to update the vertex and fragment shaders to include this new attribute location.
	* 
	* Modify the vertex shader to accept texture coordinates and forward them to the fragment shader.
	* 
	* The fragment shader should accept the TexCoord output variable as in input variable.
	* 
	* The fragment shader should also have access to the texture object.  To do this, GLSL has a built-in
	* data type for texture objects called a 'sampler' that can be sampler1D, sampler2D, or sampler3D.
	* 
	* You can add a texture to the fragment shader by declaring a uniform sampler2D that we will later
	* assign our texture to.
	* 
	* To sample the color of a texture we use GLSL texture function that takes a texture sampler as the first 
	* argument and the corresponding texture coordinates as the second.  The texture function then samples the
	* color using the texture parameters we set earlier.  The output of this fragment shader is then the (filtered) 
	* color of the texture and the (interpolated) texture coordinate.
	*/

	// Bind the textures before calling glDrawElements and it will automatically assign the texture
	// to the fragment shader's sampler:
	glBindTexture(GL_TEXTURE_2D, texture);
	//glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void _7_6_Textures()
{
	std::vector<float> posData{
		0.5f,  0.5f, 0.0f, 	// top right
		0.5f, -0.5f, 0.0f,		// bottom right
	   -0.5f, -0.5f, 0.0f,		// bottom left
	   -0.5f,  0.5f, 0.0f		// top left
	};
	std::vector<float> colorData{
		1.0f, 0.0f, 0.0f,	// top right
		0.0f, 1.0f, 0.0f,	// bottom right
		0.0f, 0.0f, 1.0f,	// bottom left
		1.0f, 1.0f, 0.0f,	// top left
	};
	std::vector<float> texCoordData{
		1.0f, 1.0f,	// top right
		1.0f, 0.0f,	// bottom right
		0.0f, 0.0f,	// bottom left
		0.0f, 1.0f	// top left
	};
	std::vector<int> eboData{
		0, 1, 3,  // first triangle
		1, 2, 3   // second triangle
	};

	Game game;
	game.initialize();
	Renderer renderer;

	

	size_t actorID = game.addActor();
	const auto& rActor = game.getActor(actorID);
	rActor->uploadBuffers(eboData, posData, colorData, texCoordData);
	rActor->addTexture("textures/container.jpg", GL_REPEAT, GL_REPEAT, GL_LINEAR, GL_LINEAR, GL_RGB);


	// create shader
	size_t shaderIndex = renderer.addShader();
	Shader& rShader = renderer.getShader(shaderIndex);
	renderer.createShaderProgram("Vert_7_6_Applying Textures.vert", "Frag_7_6_Applying Textures.frag", shaderIndex);
	rActor->connectShader(&rShader);



	// have to link THREE attributes because the vertex shader has three attributes, one for pos and one for color, one for texCoords

	// link position attribute location 0
	rActor->linkVertexAttributes(Buffer::VBOPos, 0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	// link color attribute location 1
	rActor->linkVertexAttributes(Buffer::VBOColor, 1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	// link texture coordinates attribute location 2
	rActor->linkVertexAttributes(Buffer::VBOTexCoord, 2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);





	game.runLoop();
	game.shutdown();
}

void _7_7_TextureUnits()
{
	std::vector<float> posData{
		 0.5f,  0.5f, 0.0f, 	// top right
		 0.5f, -0.5f, 0.0f,		// bottom right
		-0.5f, -0.5f, 0.0f,		// bottom left
		-0.5f,  0.5f, 0.0f		// top left
	};
	std::vector<float> colorData{
		1.0f, 0.0f, 0.0f,	// top right
		0.0f, 1.0f, 0.0f,	// bottom right
		0.0f, 0.0f, 1.0f,	// bottom left
		1.0f, 1.0f, 0.0f,	// top left
	};
	std::vector<float> texCoordData{
		1.0f, 1.0f,	// top right
		1.0f, 0.0f,	// bottom right
		0.0f, 0.0f,	// bottom left
		0.0f, 1.0f	// top left
	};
	std::vector<int> eboData{
		0, 1, 3,  // first triangle
		1, 2, 3   // second triangle
	};

	Game game;
	game.initialize();
	Renderer renderer;

	// create shader
	size_t shaderIndex = renderer.addShader();
	Shader& rShader = renderer.getShader(shaderIndex);
	renderer.createShaderProgram("Vert_7_7_Texture Units.vert", "Frag_7_7_Texture Units.frag", shaderIndex);

	size_t actorID = game.addActor();
	const auto& rActor = game.getActor(actorID);
	rActor->connectShader(&rShader);
	rActor->uploadBuffers(eboData, posData, colorData, texCoordData);
	rActor->addTexture("textures/container.jpg", GL_REPEAT, GL_REPEAT, GL_LINEAR, GL_LINEAR, GL_RGB);
	rActor->addTexture("textures/awesomeface.png", GL_REPEAT, GL_REPEAT, GL_LINEAR, GL_LINEAR, GL_RGBA);
 	rActor->setTextureUniforms();




	


	// have to link THREE attributes because the vertex shader has three attributes, one for pos and one for color, one for texCoords

	// link position attribute location 0
	rActor->linkVertexAttributes(Buffer::VBOPos, 0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	// link color attribute location 1
	rActor->linkVertexAttributes(Buffer::VBOColor, 1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	// link texture coordinates attribute location 2
	rActor->linkVertexAttributes(Buffer::VBOTexCoord, 2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);





	game.runLoop();
	game.shutdown();
}

void _7_8_Exercises()
{
	std::vector<float> posData{
		0.5f,  0.5f, 0.0f, 	// top right
		0.5f, -0.5f, 0.0f,		// bottom right
		-0.5f, -0.5f, 0.0f,		// bottom left
		-0.5f,  0.5f, 0.0f		// top left
	};
	std::vector<float> colorData{
		1.0f, 0.0f, 0.0f,	// top right
		0.0f, 1.0f, 0.0f,	// bottom right
		0.0f, 0.0f, 1.0f,	// bottom left
		1.0f, 1.0f, 0.0f,	// top left
	};
	std::vector<float> texCoordData{
		1.0f, 1.0f,	// top right
		1.0f, 0.0f,	// bottom right
		0.0f, 0.0f,	// bottom left
		0.0f, 1.0f	// top left
	};
	std::vector<int> eboData{
		0, 1, 3,  // first triangle
		1, 2, 3   // second triangle
	};

	Game game;
	game.initialize();
	Renderer renderer;

	// create shader
	size_t shaderIndex = renderer.addShader();
	Shader& rShader = renderer.getShader(shaderIndex);
	renderer.createShaderProgram("Vert_7_8_Variable Mix.vert", "Frag_7_8_Variable Mix.frag", shaderIndex);

	size_t actorID = game.addActor();
	const auto& rActor = game.getActor(actorID);
	rActor->connectShader(&rShader);
	rActor->uploadBuffers(eboData, posData, colorData, texCoordData);
	rActor->addTexture("textures/container.jpg", GL_MIRRORED_REPEAT, GL_REPEAT, GL_LINEAR, GL_NEAREST, GL_RGB);
	rActor->addTexture("textures/awesomeface.png", GL_MIRRORED_REPEAT, GL_REPEAT, GL_LINEAR, GL_NEAREST, GL_RGBA);
	rActor->setTextureUniforms();







	// have to link THREE attributes because the vertex shader has three attributes, one for pos and one for color, one for texCoords

	// link position attribute location 0
	rActor->linkVertexAttributes(Buffer::VBOPos, 0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	// link color attribute location 1
	rActor->linkVertexAttributes(Buffer::VBOColor, 1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	// link texture coordinates attribute location 2
	rActor->linkVertexAttributes(Buffer::VBOTexCoord, 2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);





	game.runLoop();
	game.shutdown();
}

