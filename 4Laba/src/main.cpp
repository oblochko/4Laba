#include <iostream>
#include "../include/shader.h"
// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>
#include <vector>
#include "../include/draw.h"
#include "../include/sphere.h"
#include "../include/camera.h"
#include "../include/lightCube.h"
#define pi 3.14

// Function prototypes
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void click_mouse_callback(GLFWwindow* window, int button, int action, int mods);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void do_movement();
void do_move_light();

// Window dimensions
//const GLuint WIDTH = 800, HEIGHT = 800;

// Shaders
Shader vertexShaderSourse, fragmentShaderSourse;
GLFWwindow* window = NULL;
//GLuint shaderProgram;
int keyPressed = 0;

//Camera  camera(glm::vec3(0.0f, 0.0f, 3.0f));
GLfloat lastX = WIDTH / 2.0;
GLfloat lastY = HEIGHT / 2.0;
bool    keys[1024];

GLfloat deltaTime = 0.0f;	// Time between current frame and last frame
GLfloat lastFrame = 0.0f;  	// Time of last frame

bool movementLight = false;
glm::vec3 finishLightPosition;
glm::vec3 stepVector;
glm::vec3 debugVector;

void InitOpenGL(/*GLFWwindow* window, */GLuint& shaderProgram);

int main()
{
	GLuint shaderProgram;
	InitOpenGL(/*window, */shaderProgram);
	Sphere* sphere = new Sphere();
	LightCube* lightCube = new LightCube();
	vector <Draw*> vectorFigures{
		sphere, lightCube
	};
	for (int i = 0; i < vectorFigures.size(); i++)
		vectorFigures[i]->generate();
	for (int i = 0; i < vectorFigures.size(); i++)
		vectorFigures[i]->init();
	//for (int i = 0; i < vectorFigures.size(); i++)
	//	vectorFigures[i]->setTexture();

	// Game loop
	while (!glfwWindowShouldClose(window))
	{
		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		GLfloat currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		glfwPollEvents();
		do_movement();
		do_move_light();
		// Render
		// Clear the colorbuffer
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		Draw::lightPos.x = sin(-3*glfwGetTime()) * 3.0f;
		Draw::lightPos.z = cos(3*glfwGetTime()) * 3.0f;
		//Draw::lightPos.y = sin(glfwGetTime() / 2.0f) * 1.0f;

		// Draw our first triangle
		vectorFigures[0]->draw(shaderProgram);
		vectorFigures[1]->draw(shaderProgram);

		// Swap the screen buffers
		glfwSwapBuffers(window);
	}

	glfwTerminate();
	return 0;

}

void InitOpenGL(/*GLFWwindow* window, */GLuint& shaderProgram)
{
	std::cout << "Starting GLFW context, OpenGL 3.3" << std::endl;
	// Init GLFW
	glfwInit();
	// Set all the required options for GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	// Create a GLFWwindow object that we can use for GLFW's functions
	window = glfwCreateWindow(WIDTH, HEIGHT, "LearnOpenGL", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	// Set the required callback functions
	glfwSetKeyCallback(window, key_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);
	glfwSetMouseButtonCallback(window, click_mouse_callback);
	
	// GLFW Options
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	// Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
	glewExperimental = GL_TRUE;
	// Initialize GLEW to setup the OpenGL Function pointers
	glewInit();

	// Define the viewport dimensions
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);
	glEnable(GL_DEPTH_TEST);
	GLuint vertexShader, fragmentShader;


	vertexShaderSourse.readFromFile("shaders/vertex_shader.txt"); 
	fragmentShaderSourse.readFromFile("shaders/fragment_shader.txt");

	vertexShaderSourse.bindCode(vertexShader, GL_VERTEX_SHADER);
	fragmentShaderSourse.bindCode(fragmentShader, GL_FRAGMENT_SHADER);

	vertexShaderSourse.checkErrors(vertexShader, "VERTEX");
	fragmentShaderSourse.checkErrors(fragmentShader, "FRAGMENT");

	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	// Check for linking errors
	GLint success;
	GLchar infoLog[512];
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

// Is called whenever a key is pressed/released via GLFW
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
		{
			keys[key] = true;
			if (keys[GLFW_KEY_ENTER])
				Draw::currentColor = ((Draw::currentColor + 1) > 6 ? 0 : Draw::currentColor + 1);
		}
		else if (action == GLFW_RELEASE)
			keys[key] = false;
	}
}

void do_movement()
{
	// Camera controls
	if (keys[GLFW_KEY_W])
		Camera::camera.ProcessKeyboard(FORWARD, deltaTime);
	if (keys[GLFW_KEY_S])
		Camera::camera.ProcessKeyboard(BACKWARD, deltaTime);
	if (keys[GLFW_KEY_A])
		Camera::camera.ProcessKeyboard(LEFT, deltaTime);
	if (keys[GLFW_KEY_D])
		Camera::camera.ProcessKeyboard(RIGHT, deltaTime);
}

bool firstMouse = true;
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	GLfloat xoffset = xpos - lastX;
	GLfloat yoffset = lastY - ypos;  // Reversed since y-coordinates go from bottom to left

	lastX = xpos;
	lastY = ypos;

	Camera::camera.ProcessMouseMovement(xoffset, yoffset);
}

void click_mouse_callback(GLFWwindow* window, int button, int action, int mods)
{
	bool lbutton_down = false;
	if (button == GLFW_MOUSE_BUTTON_LEFT) {
		if (GLFW_PRESS == action)
			lbutton_down = true;
		else if (GLFW_RELEASE == action)
			lbutton_down = false;
	}

	if (lbutton_down) {
		movementLight = true;
		finishLightPosition = Camera::camera.Position;
		glm::vec3 directVector = finishLightPosition - Draw::lightPos;
		float length = glm::length(directVector);
		float step = length / 0.002;
		stepVector = directVector / step;
	}
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	Camera::camera.ProcessMouseScroll(yoffset);
}

void do_move_light()
{
	if (movementLight)
	{		
		if (glm::length(finishLightPosition - Draw::lightPos) < 0.002)
		{
			Draw::lightPos = finishLightPosition;
			movementLight = false;
		}
		else
			Draw::lightPos = Draw::lightPos + stepVector;
	}
}