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
int gShader;
int yShader;

GLint nChangeCol;
float timeValue;
int state = 0;
int frame = 0;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (key == GLFW_KEY_A && action == GLFW_PRESS) {
		state = 0;
	} else if (key == GLFW_KEY_B && action == GLFW_PRESS) {
		state = 1;
	} else if (key == GLFW_KEY_C && action == GLFW_PRESS) {
		state = 2;
	} else if (key == GLFW_KEY_D && action == GLFW_PRESS) {
		state = 3;
	}
}


void init(void)
{
	//Return shaderProgram, which is used to set programIDC:\projects\lec09a\src\shader\fshader-lShape.glsl
	gShader = loadShader("../../src/shader/vshader.glsl", "../../src/shader/fshader-g.glsl");
	yShader = loadShader("../../src/shader/vshader.glsl", "../../src/shader/fshader-y.glsl");

    float vertices[] = {
        -0.95f, 0.925f, 0.0f, //0
        -0.95f, -0.95f, 0.0f,//1
        0.925f, -0.95f, 0.0f, //2

        0.95f, -0.925f, 0.0f, //3
        0.95f, 0.95f, 0.0f,//4
        -0.925f, 0.95f, 0.0f, //5
	};

	unsigned int indices[] = {  //note that we start from 0!
    	0, 1, 2,
        3, 4, 5
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

void display() {
    int timeloc;
    int nextShader;
    if (frame == 0) {
        nextShader = yShader;
        frame = 1;
    } else {
        nextShader = gShader;
        frame = 0;
    }

    switch (state) {
        case 0:
            //Render
            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            //Use the shader program when we want to render an object
            glUseProgram(gShader);
            //Drawing code
            glBindVertexArray(VAO); 
            glDrawArrays(GL_TRIANGLES, 0, 3);
            
            
            timeValue = 0.0f;

            if (nChangeCol == 0) {
                timeValue = glfwGetTime();
            }
            else if (nChangeCol == 1) {
                timeValue = 0.0f;
            }

            timeloc = glGetUniformLocation(gShader, "timeVal");
            glUniform1f(timeloc, timeValue);

            glUseProgram(gShader);
            glDrawArrays(GL_TRIANGLES, 3, 3);

            break;
        case 1:
            //Render
            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            //Use the shader program when we want to render an object
            glUseProgram(gShader);
            //Drawing code
            glBindVertexArray(VAO); 
            glDrawArrays(GL_TRIANGLES, 0, 3);
            
            
            timeValue = 0.0f;

            if (nChangeCol == 0) {
                timeValue = glfwGetTime();
            }
            else if (nChangeCol == 1) {
                timeValue = 0.0f;
            }

            timeloc = glGetUniformLocation(nextShader, "timeVal");
            glUniform1f(timeloc, timeValue);

            glUseProgram(nextShader);
            glDrawArrays(GL_TRIANGLES, 3, 3);

            break;
        case 2:
            //Render
            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            //Use the shader program when we want to render an object
            glUseProgram(nextShader);
            //Drawing code
            glBindVertexArray(VAO); 
            glDrawArrays(GL_TRIANGLES, 0, 3);
            
            
            timeValue = 0.0f;

            if (nChangeCol == 0) {
                timeValue = glfwGetTime();
            }
            else if (nChangeCol == 1) {
                timeValue = 0.0f;
            }

            timeloc = glGetUniformLocation(gShader, "timeVal");
            glUniform1f(timeloc, timeValue);

            glUseProgram(gShader);
            glDrawArrays(GL_TRIANGLES, 3, 3);

            break;
    }
	

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

