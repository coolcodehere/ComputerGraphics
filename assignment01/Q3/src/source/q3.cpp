#include "loadShaders.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

//Settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
	
//Vertex Buffer Object (VBO)
unsigned int VBO;

//Vertex Array Object (VAO)
unsigned int VAO;

//Shader Program (shaderProgram)'s ID
int shaderProgram;

float offset;
int state = 0;

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
	//Return shaderProgram, which is used to set programID
	shaderProgram = loadShader("../../src/shader/vshader_lec11a2.glsl", "../../src/shader/fshader_lec11a2.glsl");

	//Set up vertex data (and buffer(s)) and configure vertex attributes
	float vertices[] = {
		//positions         //colors
		 0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  //bottom right
		-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  //bottom left
		 0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f,   //top 
		// B STATE
		-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  //bottom left
		0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  //bottom right
		0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f,   //top 
		0.5f,  0.5f, 0.0f,  0.0f, 1.0f, 1.0f,   //top 
		// C STATE
		0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  //bottom left
		-0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  //bottom right
		0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f,   //top 
		-0.5f,  0.5f, 0.0f,  0.0f, 1.0f, 1.0f,   //top 
		 
		// D STATE
		 -0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  //bottom right
		0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  //bottom left
		 0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f   //top 
	};

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	//Bind the Vertex Array Object first, 
	//then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	offset = 0.0f;

	//Uncomment this call to draw in wireframe polygons.
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void display()
{
	int rOffsetLocation;
	//Render
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	//as we only have a single shader, 
	//we could also just activate our shader once beforehand if we want to 
	glUseProgram(shaderProgram);

	// update shader uniform
	rOffsetLocation = glGetUniformLocation(shaderProgram, "rOffset");
	glUniform1f(rOffsetLocation, offset);
	glBindVertexArray(VAO);
	switch (state) {
		case 0:
			glDrawArrays(GL_TRIANGLES, 0, 3);
			break;
		case 1:
			glDrawArrays(GL_TRIANGLES, 3, 3);
			glDrawArrays(GL_TRIANGLES, 4, 3);
			break;
		case 2:
			glDrawArrays(GL_TRIANGLES, 7, 3);
			glDrawArrays(GL_TRIANGLES, 8, 3);
			break;
		case 3:
			glDrawArrays(GL_TRIANGLES, 11, 3);
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
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Assignment 01: Q3 William Walter", NULL, NULL);
	glfwSetKeyCallback(window, key_callback);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
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

//Process all input: query GLFW whether relevant keys are 
//pressed/released this frame and react accordingly
void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) 
	{
		glfwSetWindowShouldClose(window, true);
	}
	else if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
	{
		offset += 0.005f;
	}
}

//glfw: whenever the window size changed (by OS or user resize) this callback function executes
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	//Make sure the viewport matches the new window dimensions; note that width and 
	//height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}

