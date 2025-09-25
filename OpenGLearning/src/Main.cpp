//#define GLFW_INCLUDE_NONE
//#include <glad/glad.h>
//#include <GLFW/glfw3.h>
// 
//#include "EngineCore/Platform/GlfwCallbacks.hpp"
//#include "EngineCore/Platform/Window.hpp"
//#include "EngineCore/Graphics/Shader.hpp"
//#include "EngineCore/IO/AssetPath.hpp"
//#include "EngineCore/Graphics/Texture2D.hpp"

//constexpr short window_w_default = 1280;
//constexpr short window_h_default = 720;

#include <iostream>
#include "EngineCore/Core/Application.hpp"

using engine::core::Application;

int main()
{
	Application game = Application(engine::core::ApplicationSpecs{ .width = 1280, .height = 720, .title = "NotTerrarian" });

	game.Run();

	return 0;

	//glfwInit();
	//glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	//glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//engine::platform::Window window(window_w_default, window_h_default, "OpenGLearning");

	//if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	//{
	//	std::cerr << "Failed to initialize GLAD" << std::endl;
	//	glfwTerminate();
	//	return -1;
	//};

	//float vertices[] = {
 //       // positions          // colors          // texture coords
	//	 0.5f,  0.5f,  0.0f,  1.0f, 0.0f, 0.0f,	 1.0f, 1.0f,  // Top-right 
 //        0.5f, -0.5f,  0.0f,  0.0f, 1.0f, 0.0f,	 1.0f, 0.0f,  // Bottom-right
	//	-0.5f, -0.5f,  0.0f,  0.0f, 0.0f, 1.0f,	 0.0f, 0.0f,  // Bottom-left
	//	-0.5f,  0.5f,  0.0f,  1.0f, 1.0f, 1.0f,	 0.0f, 1.0f	  // Top-left
	//};

 //   unsigned int indices[6] = {
 //       0, 1, 3, // Top-right -> Bottom-right -> Top-left
 //       1, 2, 3  // Bottom-right -> Bottom-left -> Top-left
 //   };

 //   GLuint VAO, VBO, EBO;
 //   glGenVertexArrays(1, &VAO);
	//glGenBuffers(1, &VBO);
	//glGenBuffers(1, &EBO);

 //   glBindVertexArray(VAO);

	//glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

 //   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
 //   glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//auto grassTex = engine::graphics::Texture2D::fromFile(
	//	engine::io::sprites("grass-sprite-test.png"),
	//	engine::graphics::TextureParams{ .generateMipmaps = false, .srgb = false }
	//);

	//auto faceTex = engine::graphics::Texture2D::fromFile(
	//	engine::io::sprites("face-sprite-test.png"),
	//	engine::graphics::TextureParams{ .generateMipmaps = false, .srgb = false }
	//);

	//grassTex->bind(0);
	//faceTex->bind(1);

	//std::string vert_shader = engine::io::shader("basic.vert");
	//std::string frag_shader = engine::io::shader("basic.frag");
	//engine::graphics::Shader myShader(vert_shader.c_str(), frag_shader.c_str());

 //   // Position attribute.
 //   glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
 //   glEnableVertexAttribArray(0);

 //   // Color attribute.
 //   glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
 //   glEnableVertexAttribArray(1);

	//// Texture attribute.
	//glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	//glEnableVertexAttribArray(2);

	//while (!window.shouldClose())
	//{
	//	auto input = window.input();
	//	
	//	glClearColor(0.25f, 0.25f, 0.25f, 1.0f);
	//	glClear(GL_COLOR_BUFFER_BIT);

	//	myShader.use();

	//	grassTex->bind(0);
	//	faceTex->bind(1);

	//	myShader.setInt("u_tex", 0);
	//	myShader.setInt("u_tex2", 1);

 //       glBindVertexArray(VAO);

 //       //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
 //       glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

 //       glBindVertexArray(0);

	//	window.swapBuffers();
	//	glfwPollEvents();
	//}

	//glDeleteVertexArrays(1, &VAO);
	//glDeleteBuffers(1, &VBO);
	//glDeleteBuffers(1, &EBO);

	//glfwTerminate();
	//return 0;
}