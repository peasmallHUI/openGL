#include "Shader.h"
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>

#include <glad/glad.h>


Shader::Shader(const char * vertexPath, const char * fragmentPath)
{
	std::ifstream vertexFile, fragmentFile;
	std::stringstream vertexSstream, fragmentSstream;
	std::string vertexString, fragmentString;
	
	vertexFile.exceptions(std::fstream::failbit | std::fstream::badbit);
	fragmentFile.exceptions(std::fstream::failbit | std::fstream::badbit);
	try
	{
		vertexFile.open(vertexPath);
		fragmentFile.open(fragmentPath);

		vertexSstream << vertexFile.rdbuf();
		fragmentSstream << fragmentFile.rdbuf();

		vertexFile.close();
		fragmentFile.close();

		vertexString = vertexSstream.str();
		fragmentString = fragmentSstream.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "Read File Failed." << std::endl;
	}
	
	vertexSource = vertexString.c_str();
	fragmentSource = fragmentString.c_str();

	unsigned int vertex, fragment;
	
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vertexSource, NULL);
	glCompileShader(vertex);
	errorCheck(vertex, "VERTEX");

	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fragmentSource, NULL);
	glCompileShader(fragment);
	errorCheck(fragment, "FRAGMENT");

	ID = glCreateProgram();
	glAttachShader(ID, vertex);
	glAttachShader(ID, fragment);
	glLinkProgram(ID);
	errorCheck(ID, "PROGRAM");

	glDeleteShader(vertex);
	glDeleteShader(fragment);

}

void Shader::use()
{
	glUseProgram(ID);
}

Shader::~Shader()
{
}

void Shader::errorCheck(unsigned int ID, std::string type)
{
	int success;
	char infoLog[512];
	if (type == "PROGRAM")
	{
		glGetProgramiv(ID, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(ID, 512, NULL, infoLog);
			std::cout << "ERROR::PROGRAM::LINK::FAILED" << infoLog << std::endl;
		}
	}
	else
	{
		glGetShaderiv(ID, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(ID, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::COMPILE::FAILED" << infoLog << std::endl;
		}
	}
}

