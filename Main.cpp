#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

//Create a constant character pointer that defines the variable vertexShaderSource.
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0\n"
"}\0";

//Create a constant character pointer that defines the variable fragmentShaderSource.
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"	FragColor = vec4(0.8f, 0.3f, 0.2f, 1.0f);\n"
"}\n\0";

int main()
{
	//Initializes GLFW.
	glfwInit();

	//Tells GLFW that we are using OpenGL version 3.3.
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	//Tells GLFW that we should be using the core profile of OpenGL.
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	//Defines the vertices I would like to be drawn in the renderer.
	GLfloat vertices[] =
	{
		-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,
		0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,
		0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f
	};

	//Creates a window instance using GLFW.
	GLFWwindow* window = glfwCreateWindow(800, 800, "Ferrucyon Renderer", NULL, NULL);

	//Tests for any errors while trying to load the window.
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window." << std::endl;
		glfwTerminate();
		return -1;
	}
	//Makes the window the current context.
	glfwMakeContextCurrent(window);

	//Tells glad to configure OpenGL.
	gladLoadGL();

	//Defines the window size when it opens.
	glViewport(0, 0, 800, 800);

	//Defining the vertexShader and how to use it within OpenGL.
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	//Defines the fragmentShader and how to use it within OpenGL.
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	//Defines a new glProgram called ShaderProgram.
	GLuint shaderProgram = glCreateProgram();

	//Attatches both the vertexShader and fragmentShader to the shaderProgram.
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);

	//Links the shaderProgram to the current renderer.
	glLinkProgram(shaderProgram);

	//Deletes the shaders.
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);


	//Defines the variables VAO and VBO is GLuints.
	GLuint VAO, VBO;

	//Defines VAO as a VertexArray with 1 object.
	glGenVertexArrays(1, &VAO);
	//Defines VBO as a buffer with 1 object.
	glGenBuffers(1, &VBO);

	//Binds the VAO vertex array.
	glBindVertexArray(VAO);

	//Binds the VBO buffer as well as the Buffer Data as an Array Buffer.
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//Creates a vertex attribute pointer and an attribute array.
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//Binds the Array Bugger and Vertex Array.
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	//Setting the background of the renderer to a navy blue.
	glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glfwSwapBuffers(window);

	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glfwSwapBuffers(window);

		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shaderProgram);

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}