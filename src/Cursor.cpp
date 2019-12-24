#include "../include/Cursor.hpp"
#include "../include/Scene.hpp"

Cursor::Cursor() : r_position(glm::vec3(0, 0, 0)) {
	// Create VBO (Vertex Buffer Object)
    glGenBuffers(1, &r_vbo);
    // Bind VBO
    glBindBuffer(GL_ARRAY_BUFFER, r_vbo);
        // Fill VBO with vertices
        //    v6----- v5
        //   /|      /|
        //  v1------v0|
        //  | |     | |
        //  | |v7---|-|v4
        //  |/      |/
        //  v2------v3
        r_vertices = { 
            // v0
            glm::vec3(0.5f, 0.5f, 0.5f),
            // v1
            glm::vec3(-0.5f, 0.5f, 0.5f),
            // v2
            glm::vec3(-0.5f, -0.5f, 0.5f),
            // v3
            glm::vec3(0.5f, -0.5f, 0.5f),
            // v4
            glm::vec3(0.5f, -0.5f, -0.5f),
            // v5
            glm::vec3(0.5f, 0.5f, -0.5f),
            // v6
            glm::vec3(-0.5f, 0.5f, -0.5f),
            // v7
            glm::vec3(-0.5f, -0.5f, -0.5f)
        };

        glBufferData(GL_ARRAY_BUFFER, r_vertices.size() * sizeof(glm::vec3), r_vertices.data(), GL_STATIC_DRAW);
    // Debind VBO
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // Create IBO (Index Buffer Objects)
    glGenBuffers(1, &r_ibo);
    // Bind IBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, r_ibo);
        // Fill IBO with index
        //    v6----- v5
        //   /|      /|
        //  v1------v0|
        //  | |     | |
        //  | |v7---|-|v4
        //  |/      |/
        //  v2------v3
        uint32_t indexCube[] = {
            // front
            0, 1,  1, 2,  2, 3,  3, 0,
            // behind
            4, 7,  7, 6,  6, 5,  5, 4,
            // left
            1, 6,  7, 2,
            // right
            0, 5,  3, 4,
        };
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, 24*sizeof(uint32_t), indexCube, GL_STATIC_DRAW);
    // Debind IBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    // Create VAO (Vertex Array Object)
    glGenVertexArrays(1, &r_vao);
    // Bind VAO
    glBindVertexArray(r_vao);
        //Save IBO in VAO
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, r_ibo);
        // Enable position attribute VAO
        const GLuint VERTEX_ATTR_POSITION = 0;
        glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
        // Specify the format of the vertex
        glBindBuffer(GL_ARRAY_BUFFER, r_vbo);
            glVertexAttribPointer(VERTEX_ATTR_POSITION, 3, GL_FLOAT, GL_FALSE, 3*sizeof(GL_FLOAT), 0); // Position
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    //Debind VAO
    glBindVertexArray(0);
}

Cursor::~Cursor() {
}

glm::vec3 Cursor::getPosition() const {
	return r_position;
}

void Cursor::getCubeInScene(Scene &s) {
	int cubePosition = s.findCube(r_position);
	// std::cout << "Cursor position : " << r_position << std::endl;
	if(cubePosition != -1) {
		// highlight the cube
		std::cout << "Cursor on cube " << cubePosition << std::endl;
	}
	else std::cout << "Cursor not on a cube" << std::endl;
}

void Cursor::drawCursor() {
	glBindVertexArray(r_vao);
        glDrawElements(GL_LINES, 24, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void Cursor::moveFront(const float t) {
	r_position.z += t;
}

void Cursor::moveLeft(const float t) {
	r_position.x -= t;
}

void Cursor::moveUp(const float t) {
	r_position.y += t;
}

void Cursor::freeBuffersCursor() {
    glDeleteVertexArrays(1, &r_vao);
    glDeleteBuffers(1, &r_ibo);
    glDeleteBuffers(1, &r_vbo);
}