#include "../include/draw.h"

//vector<Points> Draw::vertices;
//vector<GLuint> Draw::indices;
GLfloat Draw::radius;
int Draw::currentColor = 0;
glm::vec3 Draw::lightPos = { 1.2f, 0.0f, 2.0f };

Draw::Draw()
{
	//lightPos = { 1.2f, 1.0f, 2.0f };
	fillVectorColor();
}

void Draw::draw(GLuint& shaderProgram)
{
	/*glActiveTexture(GL_TEXTURE0);

	glBindTexture(GL_TEXTURE_2D, texture1);
	glUniform1i(glGetUniformLocation(shaderProgram, "ourTexture1"), 0);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture2);
	glUniform1i(glGetUniformLocation(shaderProgram, "ourTexture2"), 1);*/

	// Activate shader
	glUseProgram(shaderProgram);

	// Create transformations
	glm::mat4 model;
	glm::mat4 view;
	glm::mat4 projection;
	glm::mat4 parallel;
	model = glm::rotate(model, 30.0f, glm::vec3(0.5f, 1.0f, 0.0f));
	//model = glm::rotate(model, 0.0f, glm::vec3(0.5f, 1.0f, 0.0f));
	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
	projection = glm::perspective(45.0f, (GLfloat)800 / (GLfloat)800, 0.1f, 100.0f);
	//projection = glm::ortho(0, 800, 0, 800, -1, 1);
	// Get their uniform location
	GLint modelLoc = glGetUniformLocation(shaderProgram, "model");
	GLint viewLoc = glGetUniformLocation(shaderProgram, "view");
	//GLint projLoc = glGetUniformLocation(shaderProgram, "projection");
	GLint projLoc = glGetUniformLocation(shaderProgram, "projection");

	// Pass them to the shaders 

	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

	// Draw container
	glBindVertexArray(VAO);
	//glDrawArrays(GL_TRIANGLES, 0, 36);

	glDrawArrays(GL_TRIANGLES, 0, mvertices.size() / 5);
	glBindVertexArray(0);
}

void Draw::draw_figure(GLuint& shaderProgram)
{
	glBindVertexArray(VAO);
	setGreen(shaderProgram);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	//glDrawArrays(GL_POLYGON, 0, 4);
	glDrawElements(GL_TRIANGLES, indices.size() * 3, GL_UNSIGNED_INT, 0);
	setRed(shaderProgram);
	drawCentralIndexes();
	glBindVertexArray(0);
}

void Draw::setGreen(GLuint& shaderProgram)
{
	uniformColor = glGetUniformLocation(shaderProgram, "pushColor");
	glUniform4f(uniformColor, 0.0f, 0.5f, 0.0f, 1.0f);
}

void Draw::setRed(GLuint& shaderProgram)
{
	uniformColor = glGetUniformLocation(shaderProgram, "pushColor");
	glUniform4f(uniformColor, 1.0f, 0.0f, 0.0f, 1.0f);
}

void Draw::fillVectorColor()
{
	vectorColor.push_back({ 1.0f, 0.0f, 0.0f });
	vectorColor.push_back({ 1.0f, 0.5f, 0.0f });
	vectorColor.push_back({ 1.0f, 1.0f, 0.0f });
	vectorColor.push_back({ 0.0f, 1.0f, 0.0f });
	vectorColor.push_back({ 0.5f, 1.0f, 0.0f });
	vectorColor.push_back({ 0.0f, 0.0f, 1.0f });
	vectorColor.push_back({ 1.0f, 0.0f, 1.0f });
}

void Draw::repeatIndexes(vector<GLuint> currentVectorIndexes, vector<Points>& currentVectorVertexes)
{
	const int sizeVertex = currentVectorVertexes.size();
	//int massNumber[sizeVertex]
	//int* massNumber = new int[sizeVertex]{ 0 };
	vector<int> massNumber(sizeVertex);
	for (int i = 0; i < currentVectorIndexes.size(); i++)
		massNumber[currentVectorIndexes[i]] ++;
	for (int i = 0; i < massNumber.size(); i++)
	{
		if (massNumber[i] == 2)
		{
			currentVectorVertexes.push_back(currentVectorVertexes[i]);
		}
	}
}

void Draw::repeatIndexes()
{
	const int sizeVertex = vertices.size();
	//int massNumber[sizeVertex]
	//int* massNumber = new int[sizeVertex]{ 0 };
	vector<int> massNumber(sizeVertex);
	for (int i = 0; i < indices.size(); i++)
		massNumber[indices[i]] ++;
	for (int i = 0; i < massNumber.size(); i++)
	{
		if (massNumber[i] == 2)
		{
			vertices.push_back(vertices[i]);
		}
	}
}

void Draw::centralIndexes(vector<GLuint> currentVectorIndexes, vector<Points>& currentVectorVertexes)
{
	int centralIndex = currentVectorVertexes.size() - 1;
	for (int i = 0; i < centralIndex; i++)
	{
		currentVectorVertexes.push_back(currentVectorVertexes[i]);
		currentVectorVertexes.push_back(currentVectorVertexes[centralIndex]);
	}
}

void Draw::centralIndexes()
{
	int centralIndex = vertices.size() - 1;
	int number = 0;
	for (int i = 1; i <= centralIndex; i++)
	{
		vertices.push_back(vertices[i]);
		vertices.push_back(vertices[0]);
		number++;
	}
	//cout << number << " " << vertices.size() << endl;
}

void Draw::drawCentralIndexes(vector<Points>& currentVectorVertexes)
{
	/*for (int i = quantVertices; i < currentVectorVertexes.size(); i += 2)
	{
		glDrawArrays(GL_LINE_STRIP, i, i+1);
	}*/
}

void Draw::drawCentralIndexes()
{
	/*for (int i = quantVertices; i < vertices.size(); i +=2)
	{
		glDrawArrays(GL_LINE_STRIP, i, (i+1)% (vertices.size() - 1));
	}*/

	glDrawArrays(GL_LINE_LOOP, quantVertices, vertices.size() - quantVertices);

	//cout << "vertices " << quantVertices << endl << "quant vector" << vertices.size() << endl;
	/*int number = 0;
	for (int i = quantVertices ; i < vertices.size(); (i + 2 > vertices.size() - 1? i = vertices.size() - 1: i+=2))
	{
		glDrawArrays(GL_LINE_STRIP, i, (i + 1) % (vertices.size() - 1));
		number++;
	}*/
	//cout << "number: " << number << endl;
}

GLuint Draw::getVAO()
{
	return VAO;
}

int Draw::getSizeVertex()
{
	return mvertices.size();
}

Vertex::Vertex()
{
}

Vertex::Vertex(GLfloat X, GLfloat Y, GLfloat Z)
{
	var.X = X;
	var.Y = Y;
	var.Z = Z;
}

void Vertex::setX(GLfloat X)
{
	var.X = X;
}

void Vertex::setY(GLfloat Y)
{
	var.Y = Y;
}

void Vertex::setZ(GLfloat Z)
{
	var.Z = Z;
}

void Vertex::setPoint(Points temp)
{
	var.X = temp.X;
	var.Y = temp.Y;
	var.Z = temp.Z;
}

void Vertex::setIndexes(int size)
{
	sizeIndexes = size;
}

void Vertex::plusIndexes(int _index, int term)
{
	if (_index + term < sizeIndexes)
	{
		int change = _index + term - sizeIndexes;
		index = change;
	}
	index = _index + term;
}

Points Vertex::getPoints()
{
	return var;
}
