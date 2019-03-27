#include "Shader.h"
#include <sstream>
#include <iostream>
#include <fstream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

Shader::Shader(const char* vertexFilename, const char* fragmentFilename)
{
	std::ifstream vertexFstream;
	std::ifstream fragmentFstream;
	std::string vertexString;
	std::string fragmentString;
	std::stringstream vertexSstream;
	std::stringstream fragmentSstream;

	vertexFstream.open(vertexFilename);
	fragmentFstream.open(fragmentFilename);

	vertexFstream.exceptions(std::ifstream::failbit || std::ifstream::badbit);
	fragmentFstream.exceptions(std::ifstream::failbit || std::ifstream::badbit);

	try
	{
		if (!vertexFstream.is_open() || !fragmentFstream.is_open())
		{
			throw std::exception("Open file failed");
		}

		vertexSstream << vertexFstream.rdbuf();
		fragmentSstream << fragmentFstream.rdbuf();
		vertexFstream.close();
		fragmentFstream.close();
		vertexString = vertexSstream.str();
		fragmentString = fragmentSstream.str();
		vertexSource = vertexString.c_str();
		fragmentSource = fragmentString.c_str();

		unsigned int vertex, fragment;
		vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex, 1, &vertexSource, NULL);
		glCompileShader(vertex);
		checkError(vertex, "VERTEX");

		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &fragmentSource, NULL);
		glCompileShader(fragment);
		checkError(fragment, "FRAGMENT");

		ID = glCreateProgram();
		glAttachShader(ID, vertex);
		glAttachShader(ID, fragment);
		glLinkProgram(ID);
		checkError(ID, "PROGRAM");

		glDeleteShader(vertex);
		glDeleteShader(fragment);

	}
	catch (const std::exception& ex)
	{
		std::cout << ex.what() << std::endl;
	}

}

void Shader::use()
{
	glUseProgram(ID);
}

void Shader::checkError(const unsigned int ID, std::string type)
{
	int success;
	char infoLog[512];

	if (type == "PROGRAM")
	{
		glGetProgramiv(ID, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(ID, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::PROGRAM::LINK FAILED" << infoLog << std::endl;
		}
	}

	else
	{
		glGetShaderiv(ID, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(ID, 521, NULL, infoLog);
			std::cout << "ERROR::SHADER::"<<type<< "COMPILE FAILED" << infoLog << std::endl;
		}
	}
}
