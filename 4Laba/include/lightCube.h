#pragma once

#if !defined(_LIGHTCUBE_H_)
#define _LIGHTCUBE_H_

#include "draw.h"

class LightCube : public Draw
{
private:
	glShape* shape;
	//glm::vec3 lightPos;
	Shader lightVertexShader, lightFragmentShader;
	GLuint shaderProgram;
public:
	void init();
	void initShader();
	void generate(int n = 0, GLfloat _radius = 0.5, GLfloat bias = 0);
	void setTexture();
	void draw(GLuint& unworkableShader);
	void initShape();
	void drawShape();
	//void draw_figure(GLuint& shaderProgram);
	~LightCube();
	//void draw_figure();
};

#endif


