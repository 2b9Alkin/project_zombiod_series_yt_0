#include <stdio.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

int main(int argc, char** argv) {
	glfwInit();

	GLFWwindow* window = glfwCreateWindow(800, 600, "Title", NULL, NULL);

	// added the context creation
	glfwMakeContextCurrent(window);
	gladLoadGL();
	// --------------------------

	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();

		glfwSwapBuffers(window);
	}

	return 0;
}