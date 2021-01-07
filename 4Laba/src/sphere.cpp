#include "..\include\sphere.h"

void Sphere::init()
{
	/*glGenVertexArrays(MESH_COUNT, VAO); //Создать VAO
	glGenBuffers(MESH_COUNT * ATRIB_USE, VBO); //Создать 4 VBO
	for (auto i = 0u, vboidx = 0u; i < MESH_COUNT; i++) {
		if (!shapes[i]) continue;
	//Установить VAO текущим
	glBindVertexArray(VAO[i]);
	//Привязываем первый VBO к текущему VAO
	glBindBuffer(GL_ARRAY_BUFFER, VBO[vboidx++]);*/
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(Vector3f) * shape->GetVertexCount(), shape->GetVertices(), GL_STATIC_DRAW);
	glBufferData(GL_ARRAY_BUFFER, comboVector.size() * sizeof(GLfloat), &comboVector.front(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * shape->GetIndexCount(), shape->GetIndices(), GL_STATIC_DRAW);
	//Указываем параметры доступа вершинного атрибута к VBO
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vector3f), (GLvoid*)0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	//cout << shape->GetVertexCount() << endl << shape->GetIndexCount();

	/*glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, mvertices.size() * sizeof(GLfloat), &mvertices.front(), GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	// TexCoord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0);*/
}

void Sphere::generate(int n, GLfloat _radius, GLfloat bias)
{
	shape = glShape::CreateSphere(30u);
	fillVector();
	mvertices = {
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};

}

void Sphere::setTexture()
{
	/*GLuint texture1;
	GLuint texture2;*/
	// ====================
	// Texture 1
	// ====================
	glGenTextures(1, &texture1);
	glBindTexture(GL_TEXTURE_2D, texture1); // All upcoming GL_TEXTURE_2D operations now have effect on our texture object
	// Set our texture parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// Set texture wrapping to GL_REPEAT
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// Set texture filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// Load, create texture and generate mipmaps
	int width, height;
	unsigned char* image = SOIL_load_image("img/container.jpg", &width, &height, 0, SOIL_LOAD_RGB);
	//unsigned char* image = SOIL_load_image("container.jpg", &width, &height, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture when done, so we won't accidentily mess up our texture.
	// ===================
	// Texture 2
	// ===================
	glGenTextures(1, &texture2);
	glBindTexture(GL_TEXTURE_2D, texture2);
	// Set our texture parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// Set texture filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// Load, create texture and generate mipmaps
	image = SOIL_load_image("img/awesomeface.png", &width, &height, 0, SOIL_LOAD_RGB);
	//image = SOIL_load_image("awesomeface.png", &width, &height, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Sphere::draw(GLuint& shaderProgram)
{
	/*glActiveTexture(GL_TEXTURE0);

glBindTexture(GL_TEXTURE_2D, texture1);
glUniform1i(glGetUniformLocation(shaderProgram, "ourTexture1"), 0);
glActiveTexture(GL_TEXTURE1);
glBindTexture(GL_TEXTURE_2D, texture2);
glUniform1i(glGetUniformLocation(shaderProgram, "ourTexture2"), 1);*/

// Activate shader
	glUseProgram(shaderProgram);

	/*lightingShader.setVec3("light.ambient", 0.2f, 0.2f, 0.2f);
	lightingShader.setVec3("light.diffuse", 0.5f, 0.5f, 0.5f); // darken the light a bit to fit the scene
	lightingShader.setVec3("light.specular", 1.0f, 1.0f, 1.0f);*/

	GLint lightAmbientLoc = glGetUniformLocation(shaderProgram, "light.ambient");
	GLint lightDiffuseLoc = glGetUniformLocation(shaderProgram, "light.diffuse");
	GLint viewSpecularLoc = glGetUniformLocation(shaderProgram, "light.specular");

	glUniform1f(lightAmbientLoc, 0.1f);
	glUniform1f(lightDiffuseLoc, 1.0f);
	glUniform1f(viewSpecularLoc, 1.0f);

	GLint objectColorLoc = glGetUniformLocation(shaderProgram, "objectColor");
	GLint lightColorLoc = glGetUniformLocation(shaderProgram, "lightColor");
	GLint lightPosLoc = glGetUniformLocation(shaderProgram, "lightPos");
	GLint viewPosLoc = glGetUniformLocation(shaderProgram, "viewPos");
	glUniform3f(objectColorLoc, 1.0f, 0.5f, 0.31f);
	//glUniform3f(lightColorLoc, 1.0f, 1.0f, 1.0f);
	glUniform3f(lightColorLoc, vectorColor[Draw::currentColor].x, vectorColor[Draw::currentColor].y, vectorColor[Draw::currentColor].z);
	glUniform3f(lightPosLoc, Draw::lightPos.x, Draw::lightPos.y, Draw::lightPos.z);
	glUniform3f(viewPosLoc, Camera::camera.Position.x, Camera::camera.Position.y, Camera::camera.Position.z);
	// Create transformations
	glm::mat4 model;
	glm::mat4 parallel;
	
	Camera::view = Camera::camera.GetViewMatrix();
	//projection = glm::perspective(45.0f, (GLfloat)800 / (GLfloat)800, 0.1f, 100.0f);
	Camera::projection = glm::perspective(Camera::camera.Zoom, (float)WIDTH / (float)HEIGHT, 0.1f, 1000.0f);
	//projection = glm::ortho(0, 800, 0, 800, -1, 1);
	// Get their uniform location
	GLint modelLoc = glGetUniformLocation(shaderProgram, "model");
	GLint viewLoc = glGetUniformLocation(shaderProgram, "view");
	//GLint projLoc = glGetUniformLocation(shaderProgram, "projection");
	GLint projLoc = glGetUniformLocation(shaderProgram, "projection");

	// Pass them to the shaders 

	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(Camera::view));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(Camera::projection));

	// Draw container
	glBindVertexArray(VAO);
	//glDrawArrays(GL_TRIANGLES, 0, 36);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	//glDrawArrays(GL_TRIANGLES, 0, mvertices.size() / 5);
	glDrawElements(GL_TRIANGLES, shape->GetIndexCount(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void Sphere::fillVector()
{
	for (int i = 0; i < shape->GetVertexCount(); i++)
	{
		//cout << shape->GetVertices()[i].x;
		comboVector.push_back(shape->GetVertices()[i].x);
		comboVector.push_back(shape->GetVertices()[i].y);
		comboVector.push_back(shape->GetVertices()[i].z);

		comboVector.push_back(shape->GetNormals()[i].x);
		comboVector.push_back(shape->GetNormals()[i].y);
		comboVector.push_back(shape->GetNormals()[i].z);
	}
}

void Sphere::initShape()
{
	shape = glShape::CreateCube();
}



Sphere::~Sphere()
{
}
