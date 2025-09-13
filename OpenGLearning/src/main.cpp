#define GLFW_INCLUDE_NONE
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include "EngineCore/GlfwCallbacks.hpp"
#include "EngineCore/Window.hpp"
#include "EngineCore/Graphics/Shader.hpp"
#include "EngineCore/IO/AssetPath.hpp"

constexpr short window_w_default = 800;
constexpr short window_h_default = 600;

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	engine::Window window(window_w_default, window_h_default, "OpenGLearning");

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cerr << "Failed to initialize GLAD" << std::endl;
		glfwTerminate();
		return -1;
	};

	float vertices[] = {
        // positions          // colors
		 0.5f,  0.5f,  0.0f,  1.0f, 0.0f, 0.0f, // Top-right 
         0.5f, -0.5f,  0.0f,  0.0f, 1.0f, 0.0f, // Bottom-right
		-0.5f, -0.5f,  0.0f,  0.0f, 0.0f, 1.0f, // Bottom-left
		-0.5f,  0.5f,  0.0f,  1.0f, 1.0f, 1.0f  // Top-left
	};

    unsigned int indices[6] = {
        0, 1, 3, // Top-right -> Bottom-right -> Top-left
        1, 2, 3  // Bottom-right -> Bottom-left -> Top-left
    };

    GLuint VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

	GLuint VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    GLuint EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	std::string vert_shader = engine::io::shader("basic.vert");
	std::string frag_shader = engine::io::shader("basic.frag");
	engine::graphics::Shader myShader(vert_shader.c_str(), frag_shader.c_str());

    // Position attribute.
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Color attribute.
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

	while (!window.shouldClose())
	{
		auto input = window.input();
		
		glClearColor(0.25f, 0.25f, 0.25f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		myShader.use();

        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

        glBindVertexArray(VAO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

		window.swapBuffers();
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}