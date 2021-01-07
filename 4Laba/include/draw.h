#pragma once

#if !defined(_DRAW_H_)
#define _DRAW_H_

#include <iostream>
#include "shader.h"
// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

#include <SOIL.h>
// GLM Mathematics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// GLFW
#include <GLFW/glfw3.h>
#include <vector>
#include <array>

// 3D figure
#include "glShape.h"
#include "camera.h"

#include <math.h>
const GLuint WIDTH = 800, HEIGHT = 800;
#define pi 3.14

enum Color {
	Red = 0,
	Orange,
	Yellow,
	Green,
	Ñyan,
	Blue,
	Purple
};

struct Points
{
	GLfloat X, Y, Z;
};

class Vertex {
private:
	Points var;
	int sizeIndexes;
	int index;
public:
	Vertex();
	Vertex(GLfloat X, GLfloat Y, GLfloat Z);
	void setX(GLfloat X);
	void setY(GLfloat Y);
	void setZ(GLfloat Z);
	void setPoint(Points temp);
	void setIndexes(int size);
	void plusIndexes(int index, int term);
	Points getPoints();
};

class Draw
{
public:
	static int currentColor;
	static glm::vec3 lightPos;
protected:
	//struct Points;
	vector<Points> vertices;
	vector <GLfloat> mvertices;
	vector<GLuint> indices;
	static GLfloat radius;
	vector<Vector3f> vectorColor;
	GLuint VBO, VAO, EBO;
	GLuint quantVertices;
	GLint uniformColor;
	GLuint texture1;
	GLuint texture2;
public:
	Draw();
	virtual void init() = 0;
	virtual void generate(int n = 0, GLfloat _radius = 0.5, GLfloat bias = 0) = 0;
	virtual void setTexture() = 0;
	virtual void draw(GLuint& shaderProgram);
	void draw_figure(GLuint& shaderProgram);
	void setGreen(GLuint& shaderProgram);
	void setRed(GLuint& shaderProgram);
	void fillVectorColor();
	void repeatIndexes(vector<GLuint> currentVectorIndexes, vector<Points>& currentVectorVertexes);
	void repeatIndexes();
	void centralIndexes(vector<GLuint> currentVectorIndexes, vector<Points>& currentVectorVertexes);
	void centralIndexes();
	void drawCentralIndexes(vector<Points>& currentVectorVertexes);
	void drawCentralIndexes();
	GLuint getVAO();
	int getSizeVertex();
};

#endif
