#pragma once
#include <string>

class Shader
{
public:
	const char* vertexCode;
	const char* fragmentCode;
	unsigned int ID;

	Shader(const char* vertexPath, const char*  fragmentPath);
	void use();

private:
	void errorCheck(unsigned int ID,const std::string type);

};

