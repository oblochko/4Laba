#include "..\include\shader.h"

const GLchar* Shader::getShader()
{
	return shaderSource;
}

void Shader::checkErrors(GLuint currentShader, string typeShader)
{
	GLint success;
	GLchar infoLog[512];
	glGetShaderiv(currentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(currentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER:" + typeShader + ":COMPILATION_FAILED\n" << infoLog << std::endl;
	}
}

void Shader::readFromFile(string patch)
{
	setlocale(LC_ALL, "rus");
	ifstream fin(patch.c_str());
	if (!fin.is_open()) // если файл не открыт
		cout << "Файл не может быть открыт!" << endl;

	if (fin.is_open())
	{
		std::stringstream sstr;
		sstr << fin.rdbuf();
		shaderCode = sstr.str();
		fin.close();
	}
	else
		cout << "Файл не может быть открыт!" << endl;
	cout << shaderCode << endl;
}

void Shader::bindCode(GLuint& _currentShader, GLuint _typeShader)
{
	shaderSource = shaderCode.c_str();

	_currentShader = glCreateShader(_typeShader);
	glShaderSource(_currentShader, 1, &shaderSource, NULL);
	glCompileShader(_currentShader);
}
