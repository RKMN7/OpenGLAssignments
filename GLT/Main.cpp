#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "SHADER_H.h"

#include <iostream>

glm::mat4 model, cam, look;
glm::vec3 cp, ct, cd, cr, cu, up;
float cameraSpeed = 0.05f;
const GLuint SCR_WIDTH = 900;
const GLuint SCR_HEIGHT = 900;
GLfloat aspect = SCR_WIDTH / SCR_HEIGHT;

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	//Mode
	if (key == GLFW_KEY_1 && action == GLFW_PRESS)
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	if (key == GLFW_KEY_2 && action == GLFW_PRESS)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	if (key == GLFW_KEY_3 && action == GLFW_PRESS)
		glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);

	//Rotate
	if( key == GLFW_KEY_E && action == GLFW_PRESS)
		model = glm::rotate(model, glm::radians(10.0f), glm::vec3(0.0f, 1.0f, 0.0f));

	if (key == GLFW_KEY_Q && action == GLFW_PRESS)
		model = glm::rotate(model, glm::radians(-10.0f), glm::vec3(0.0f, 1.0f, 0.0f));

	//Translate
	if (key == GLFW_KEY_UP && action == GLFW_PRESS)
		model = glm::translate(model, glm::vec3(0.0f, 0.1f, 0.0f));

	if (key == GLFW_KEY_DOWN && action == GLFW_PRESS)
		model = glm::translate(model, glm::vec3(0.0f, -0.1f, 0.0f));

	if (key == GLFW_KEY_LEFT && action == GLFW_PRESS)
		model = glm::translate(model, glm::vec3(-0.1f, 0.0f, 0.0f));

	if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS)
		model = glm::translate(model, glm::vec3(0.1f, 0.0f, 0.0f));

	if (key == GLFW_KEY_L && action == GLFW_PRESS)
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -0.1f));

	if (key == GLFW_KEY_K && action == GLFW_PRESS)
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.1f));

	//Camera Mode
	if (key == GLFW_KEY_O && action == GLFW_PRESS)
		cam = glm::ortho(-5.0f, 5.0f, -5.0f, 5.0f, 0.0f, 100.0f);

	if (key == GLFW_KEY_P && action == GLFW_PRESS)
		cam = glm::perspective(glm::radians(100.0f), aspect, 0.1f, 100.0f);
	
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		cp += cameraSpeed * cd;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		cp -= cameraSpeed * cd;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		cp += cameraSpeed * cr;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		cp -= cameraSpeed * cr;

	//Scale
	if (key == GLFW_KEY_Z && action == GLFW_PRESS)
		model = glm::scale(model, glm::vec3(0.9f, 0.9f, 0.9f));

	if (key == GLFW_KEY_X && action == GLFW_PRESS)
		model = glm::scale(model, glm::vec3(1.1f, 1.1f, 1.1f));
}


int main()
{
	//Window
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	glEnable(GL_DEPTH_TEST);

	Shader S("vs.glsl", "fs.glsl");

	//Points
	float R1[] = {
		-1.0f,  1.0f, -1.0f, //0
		-1.0f, -1.0f, -1.0f, //1
		1.0f, -1.0f, -1.0f,  //2
		1.0f,  1.0f, -1.0f,  //3
		-1.0f,  1.0f, 1.0f,	 //4
		-1.0f, -1.0f, 1.0f,  //5
		1.0f, -1.0f, 1.0f,   //6
		1.0f,  1.0f, 1.0f    //7
	};

	GLuint indices[] = {  
		4, 6, 7,
		5, 6, 4,
		0, 4, 5,
		0, 1, 5,
		2, 6, 7,
		2, 3, 7,
		3, 4, 7,
		0, 3, 4,
		2, 5, 6,
		1, 2, 5,
		0, 1, 3,
		1, 2, 3,

	};

	glm::vec3 clone[]={
		glm::vec3(0.0f, 0.f, 0.0f),
		glm::vec3(3.0f, 3.0f, -3.0f),
		glm::vec3(-4.0f, 2.0f, -5.0f),
		glm::vec3(-3.0f, -1.0f, -2.0f),
		glm::vec3(2.0f, -3.0f, -1.0f),
		glm::vec3(-3.0f, -2.0f, 2.0f),
	};

	//Buffers
	GLuint VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(R1), R1, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	
	glBindVertexArray(0);

	//Cam
	cam = glm::ortho(-5.0f, 5.0f, -5.0f, 5.0f, 0.0f, 100.0f);
	up=glm::vec3(0.0, 1.0, 0.0);

	cp = glm::vec3(0.0, 0.0, 4.0);
	ct = glm::vec3(0.0f, 0.0f, 0.0f);
	cd = glm::vec3(0.0, 0.0, -1.0);
	cr = glm::normalize(glm::cross(up, cd));
	cu = glm::cross(cd,cr);

	//Loop
	while (!glfwWindowShouldClose(window))
	{
		glfwSetKeyCallback(window, key_callback);

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		float timeValue = glfwGetTime();
		float redValue = (sin(timeValue) / 4.0f) + 0.75f;
		int vertexColorLocation = glGetUniformLocation(S.ID, "ourColour");
		S.setMat4("transform", model);
		S.setMat4("proj", cam);
		look = glm::lookAt(cp, cp+cd, up);
		S.setMat4("look",look);
		
		S.use();

		glUniform4f(vertexColorLocation, redValue, 0.0f, 0.0f, 1.0f);
		

		glBindVertexArray(VAO);
		for(int i=0;i<=4;++i)
		{
			glm::mat4 cl;
			cl= glm::translate(cl,clone[i]);
			S.setMat4("view", cl);
			glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
		}


		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	//Clean-up
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

	glfwTerminate();
	return 0;
}