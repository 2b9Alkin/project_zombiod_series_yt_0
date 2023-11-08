#include <stdio.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

struct Vertex {
	float x, y;
};

int main(int argc, char** argv) {
	if (!glfwInit()) {
		puts("Faield to init glfw!\n");
		exit(1);
	}

	GLFWwindow* window = glfwCreateWindow(800, 600, "Title", NULL, NULL);

	struct Vertex vertices[3] = {
		{0, 0},
		{1, 0},
		{1, 1},
	};

	// added the context creation
	glfwMakeContextCurrent(window);
	gladLoadGL();
	// --------------------------

	// vbo
	unsigned int vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(struct Vertex) * 3, vertices, GL_STATIC_DRAW);

	// vao
	unsigned int vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// layout
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(struct Vertex), (const void*) 0);

	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();

		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(window);
	}

	return 0;
}