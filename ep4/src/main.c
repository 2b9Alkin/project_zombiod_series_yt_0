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

	struct Vertex vertices[4] = {
		{0, 0},
		{1, 0},
		{1, 1},
		{0, 1}
	};

	GLuint indices[6] = {
		0, 1, 2,
		0, 2, 3
	};

	// added the context creation
	glfwMakeContextCurrent(window);
	gladLoadGL();
	// --------------------------

	// vbo
	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(struct Vertex) * 4, vertices, GL_STATIC_DRAW);

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


	// element array buffer
	GLuint ebo;
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * 6, indices, GL_STATIC_DRAW);


	GLuint shader = create_shader(vert, frag);

	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();

		glUseProgram(shader);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);

		glfwSwapBuffers(window);
	}

	return 0;
}