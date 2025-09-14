#define GLFW_INCLUDE_NONE
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <stb_image.h>

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
        // positions          // colors          // texture coords
		 0.5f,  0.5f,  0.0f,  1.0f, 0.0f, 0.0f,	 1.0f, 1.0f,  // Top-right 
         0.5f, -0.5f,  0.0f,  0.0f, 1.0f, 0.0f,	 1.0f, 0.0f,  // Bottom-right
		-0.5f, -0.5f,  0.0f,  0.0f, 0.0f, 1.0f,	 0.0f, 0.0f,  // Bottom-left
		-0.5f,  0.5f,  0.0f,  1.0f, 1.0f, 1.0f,	 0.0f, 1.0f	  // Top-left
	};

    unsigned int indices[6] = {
        0, 1, 3, // Top-right -> Bottom-right -> Top-left
        1, 2, 3  // Bottom-right -> Bottom-left -> Top-left
    };

    GLuint VAO, VBO, EBO;
    glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	stbi_set_flip_vertically_on_load(true);
	std::string test_sprite = engine::io::sprites("grass-sprite-test.png");

	int width, height, nrChannels;
	unsigned char* data = stbi_load(test_sprite.c_str(), &width, &height, &nrChannels, 0);
	if (!data)
	{
		std::cerr << "stbi_load failed for: " << test_sprite << "\n";
	}

	GLenum srcFormat = GL_RGB;
	GLenum internalFormat = GL_RGB;
	if (nrChannels == 4) { srcFormat = GL_RGBA; internalFormat = GL_RGBA; }
	else if (nrChannels == 3) { srcFormat = GL_RGB; internalFormat = GL_RGB; }
	else if (nrChannels == 1) { srcFormat = GL_RED; internalFormat = GL_R8; } // grayscale fallback

	// Prevent row padding surprises
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, srcFormat, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(data);

	std::string vert_shader = engine::io::shader("basic.vert");
	std::string frag_shader = engine::io::shader("basic.frag");
	engine::graphics::Shader myShader(vert_shader.c_str(), frag_shader.c_str());

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glUniform1i(glGetUniformLocation(myShader.getShaderId(), "u_tex"), 0);

	if (nrChannels == 4)
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	myShader.use();

    // Position attribute.
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Color attribute.
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

	// Texture attribute.
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	while (!window.shouldClose())
	{
		auto input = window.input();
		
		glClearColor(0.25f, 0.25f, 0.25f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glBindTexture(GL_TEXTURE_2D, texture);

        glBindVertexArray(VAO);

        //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glBindVertexArray(0);

		window.swapBuffers();
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

	glfwTerminate();
	return 0;
}