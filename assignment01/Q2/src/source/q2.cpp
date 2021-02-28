#include "loadShaders.h"
#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

//Settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
	
//Vertex Buffer Object (VBO)
unsigned int VBO;

//Vertex Array Object (VAO)
unsigned int VAO;

//Element Buffer Object (EBO)
unsigned int EBO;

//Shader Program (shaderProgram)'s ID
int rShader;
int gShader;
int bShader;
int cShader;
int shaderList[4];

GLint nChangeCol;
float timeValue;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (key == GLFW_KEY_A && action == GLFW_PRESS) {
		shaderList[0] = gShader;
		shaderList[1] = rShader;
		shaderList[2] = bShader; 
		shaderList[3] = cShader;
	} else if (key == GLFW_KEY_B && action == GLFW_PRESS) {
		shaderList[0] = bShader;
		shaderList[1] = gShader;
		shaderList[2] = cShader;
		shaderList[3] = rShader;
	} else if (key == GLFW_KEY_C && action == GLFW_PRESS) {
		shaderList[0] = cShader;
		shaderList[1] = bShader;
		shaderList[2] = rShader;
		shaderList[3] = gShader;
	} else if (key == GLFW_KEY_D && action == GLFW_PRESS) {
		shaderList[0] = rShader;
		shaderList[1] = cShader;
		shaderList[2] = gShader;
		shaderList[3] = bShader;
	}
}


void init(void)
{
	//Return shaderProgram, which is used to set programIDC:\projects\lec09a\src\shader\fshader-lShape.glsl
	rShader = loadShader("../../src/shader/vshader.glsl", "../../src/shader/fshader-r.glsl");
	gShader = loadShader("../../src/shader/vshader.glsl", "../../src/shader/fshader-g.glsl");
	bShader = loadShader("../../src/shader/vshader.glsl", "../../src/shader/fshader-b.glsl");
	cShader = loadShader("../../src/shader/vshader.glsl", "../../src/shader/fshader-c.glsl");
	shaderList[0] = gShader;
	shaderList[1] = rShader;
	shaderList[2] = bShader; 
	shaderList[3] = cShader;
		float vertices[] = {
			0.0f, 0.0f, 0.0f, //0
			-0.5f, 0.0f, 0.0f,//1
			0.5f, 0.0f, 0.0f, //2
			0.0f, -0.70f, 0.0f,//3
			0.0f, 0.70f, 0.0f, //4
	};

	unsigned int indices[] = {  //note that we start from 0!
		0, 1, 4,
		0, 1, 3,
		0, 2, 4,
		0, 2, 3,
	};

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	//Bind the Vertex Array Object first, 
	//then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO);

	//Copy our vertices array in a buffer for OpenGL to use
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//Copy our index array in a element buffer for OpenGL to use
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//Then set the vertex attributes pointers
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//Uncomment this call to draw in wireframe polygons.
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void display()
{
	//Render
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	//Use the shader program when we want to render an object
	glUseProgram(shaderList[0]);

	//Drawing code
	glBindVertexArray(VAO); 
	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

	timeValue = 0.0f;

	if (nChangeCol == 0) {
		timeValue = glfwGetTime();
	}
	else if (nChangeCol == 1) {
		timeValue = 0.0f;
	}

	int timeLoc = glGetUniformLocation(shaderList[1], "timeVal");
	glUniform1f(timeLoc, timeValue);

	glUseProgram(shaderList[1]);
	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void *)(sizeof(unsigned int) * 3));

	timeValue = 0.0f;

	if (nChangeCol == 0) {
		timeValue = glfwGetTime();
	}
	else if (nChangeCol == 1) {
		timeValue = 0.0f;
	}

	timeLoc = glGetUniformLocation(shaderList[2], "timeVal");
	glUniform1f(timeLoc, timeValue);

	glUseProgram(shaderList[2]);
	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void *)(sizeof(unsigned int) * 6));

	timeValue = 0.0f;

	if (nChangeCol == 0) {
		timeValue = glfwGetTime();
	}
	else if (nChangeCol == 1) {
		timeValue = 0.0f;
	}

	timeLoc = glGetUniformLocation(shaderList[3], "timeVal");
	glUniform1f(timeLoc, timeValue);

	glUseProgram(shaderList[3]);
	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void *)(sizeof(unsigned int) * 9));
	//No need to unbind it every time 
	glBindVertexArray(0); 
}

int main()
{
	//glfw: initialize and configure
	glfwInit();
	
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//glfw window creation
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Assignment 01: Q2 William Walter", NULL, NULL);
	
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwSetKeyCallback(window, key_callback);
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	//glad: load all OpenGL function pointers
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	init();
	
	//Render loop
	while (!glfwWindowShouldClose(window))
	{
		//Input
		processInput(window);
		display();
  	
		//glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	//Optional: de-allocate all resources once they've outlived their purpose:
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	//glfw: terminate, clearing all previously allocated GLFW resources.
	glfwTerminate();
	return 0;
}

//Process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

//glfw: whenever the window size changed (by OS or user resize) this callback function executes
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	//Make sure the viewport matches the new window dimensions; note that width and 
	//height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}

