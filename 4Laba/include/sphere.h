#pragma once

#if !defined(_CUBE_H_)
#define _CUBE_H_
#include <vector>

#include "draw.h"

class Sphere : public Draw
{	
private:
	glShape* shape;
	vector<GLfloat> comboVector;
public:
	void init();
	void generate(int n = 0, GLfloat _radius = 0.5, GLfloat bias = 0);
	void setTexture();
	void draw(GLuint& shaderProgram);
	void fillVector();
	void initShape();
	void drawShape();
	//void draw_figure(GLuint& shaderProgram);
	~Sphere();
	//void draw_figure();
};

#endif


