#include "shader.h"
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
	std::ifstream vertexFile;
	std::ifstream fragmentFile;
	std::stringstream vertexSstream;
	std::stringstream fragmentSstream;
	std::string vertexString;
	std::string fragmentString;


	vertexFile.open(vertexPath);
	fragmentFile.open(fragmentPath);

	vertexFile.exceptions(std::ifstream::failbit || std::ifstream::badbit);
	fragmentFile.exceptions(std::ifstream::failbit || std::ifstream::badbit);

	try
	{
		if (!vertexFile.is_open() || !fragmentFile.is_open())
		{
			throw std::exception("open file error");
		}
		vertexSstream << vertexFile.rdbuf();
		fragmentSstream << fragmentFile.rdbuf();
		vertexFile.close();
		fragmentFile.close();
		vertexString = vertexSstream.str();
		fragmentString = fragmentSstream.str();

		vertexCode = vertexString.c_str();
		fragmentCode = fragmentString.c_str();

		unsigned int vertex, fragment;

		vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex, 1, &vertexCode, NULL);
		glCompileShader(vertex);
		errorCheck(vertex, "SHADER");

		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &fragmentCode, NULL);
		glCompileShader(fragment);
		errorCheck(fragment, "SHADER");

		ID = glCreateProgram();
		glAttachShader(ID, vertex);
		glAttachShader(ID, fragment);
		glLinkProgram(ID);
		errorCheck(ID, "PROGRAM");

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

void Shader::errorCheck(unsigned int ID, std::string type)
{
	int success;
	char infoLog[512];
	if (type == "SHADER" )
	{
		glGetShaderiv(ID, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(ID, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
		}
	}
	else if (type == "PROGRAM")
	{
		glGetProgramiv(ID, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(ID, 512, NULL, infoLog);
			std::cout << "ERROR::PROGRAM::LINK_FAILED\n" << infoLog << std::endl;
		}
	}
}


