#pragma once
#include <string>




class Shader
{
public:
	Shader(const char* vertexFilename, const char* fragmentframeFilename);
	unsigned int ID;
	const char* vertexSource;
	const char* fragmentSource;

	void use();

private:
	void checkError(const unsigned int ID, const std::string type);
};

