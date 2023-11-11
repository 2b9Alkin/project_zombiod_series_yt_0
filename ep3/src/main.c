#include <stdio.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

struct Vertex {
	float x, y;
};

GLuint compile_shader(const char* src, GLenum type) {
	GLuint id = glCreateShader(type);

	glShaderSource(id, 1, &src, NULL);
	glCompileShader(id);

	return id;
}

GLuint create_shader(const char* vert, const char* frag) {
	GLuint program_id = glCreateProgram();

	GLuint v = compile_shader(vert, GL_VERTEX_SHADER);
	GLuint f = compile_shader(frag, GL_FRAGMENT_SHADER);

	// group up
	glAttachShader(program_id, v);
	glAttachShader(program_id, f);

	glLinkProgram(program_id);

	return program_id;
}


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
	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(struct Vertex) * 3, vertices, GL_STATIC_DRAW);

	// vao
	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// layout
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(struct Vertex), (const void*) 0);

	const char* vert = "#version 440 core\n"
						"\n"
						"layout (location = 0) in vec2 aPos;\n"
						"\n"
						"void main() {\n"
						"\tgl_Position = vec4(aPos.xy, 0, 1);\n"
						"}\n";

	const char* frag = "#version 440 core\n"
						"\n"
						"layout (location = 0) out vec4 fragColor;\n"
						"\n"
						"void main() {\n"
						"\tfragColor = vec4(1, 0, 1, 1); // red green blue alpha\n"
						"}\n";

	GLuint shader = create_shader(vert, frag);

	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();

		glUseProgram(shader);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(window);
	}

	return 0;
}