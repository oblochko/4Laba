#pragma once

#if !defined(_SHADER_H_)
#define _SHADER_H_

#include <fstream>
#include <iostream>
#include <string.h>
#include <sstream>

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

using namespace std;

class Shader
{
private:
	const GLchar* shaderSource;
	string patch;
	string shaderCode;
	string typeShader;
public:
	const GLchar* getShader();
	void checkErrors(GLuint currentShader, string _typeShader);
	void readFromFile(string patch);
	void bindCode(GLuint& _currentShader, GLuint _typeShader);
};

#endif
