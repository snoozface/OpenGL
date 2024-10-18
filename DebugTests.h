#pragma once


//DEBUG

//******************************************************************************
// Test data uploaded to buffers

//GLint bufferSize{ 0 };
//glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, &bufferSize);
//std::vector<float> vertData(bufferSize / sizeof(float));
//glGetBufferSubData(GL_ARRAY_BUFFER, 0, bufferSize, vertData.data());
//for (const auto& value : vertData)
//{
//	std::cout << value << '\n';
//}
//std::cout << '\n';
//glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, &bufferSize);
//std::vector<GLuint> indexData(bufferSize / sizeof(float));
//glGetBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, bufferSize, indexData.data());
//for (const auto& value : indexData)
//{
//	std::cout << value << '\n';
//}

//******************************************************************************
// Test buffer binding

//GLint currentVAO{};
//glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &currentVAO);
//if (currentVAO == program.getVAOID(VAO1))
//{
//	std::cout << "VAO 1 is current!\n";
//}
//else
//{
//	std::cout << "VAO 1 is NOT current!\n";
//}
//GLint currentVBO{};
//glGetIntegerv(GL_ARRAY_BUFFER_BINDING, &currentVBO);
//if (currentVBO == program.getVBOID(VAO1, VBO1))
//{
//	std::cout << "VBO 1 is current!\n";
//}
//else
//{
//	std::cout << "VBO 1 is NOT current!\n";
//}
//GLint currentEBO{};
//glGetIntegerv(GL_ELEMENT_ARRAY_BUFFER_BINDING, &currentEBO);
//if (currentEBO == program.getEBOID(VAO1, EBO1))
//{
//	std::cout << "EBO 1 is current!\n";
//}
//else
//{
//	std::cout << "EBO 1 is NOT current!\n";
//}

