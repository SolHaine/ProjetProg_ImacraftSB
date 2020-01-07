#include "../include/Cursor.hpp"
#include "../include/Scene.hpp"

Cursor::Cursor(Scene &s) {
	// Create VBO (Vertex Buffer Object) for vertex position
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

    // Create VBO (Vertex Buffer Object) for scene sposition
    glGenBuffers(1, &r_vboScenePosition);
    // Bind VBO
    glBindBuffer(GL_ARRAY_BUFFER, r_vboScenePosition);
        // Fill VBO
        glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3), &r_position, GL_STATIC_DRAW);
    // Debind VBO
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // Create VBO (Vertex Buffer Object) for color
    glGenBuffers(1, &r_vboColor);
    // Bind VBO
    changeColorOnSceneCube(s);

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
        // Enable vertex position attribute VAO
        const GLuint VERTEX_ATTR_VERTEXPOSITION = 0;
        glEnableVertexAttribArray(VERTEX_ATTR_VERTEXPOSITION);
        // Enable scene position attribute VAO
        const GLuint VERTEX_ATTR_SCENEPOSITION = 2;
        glEnableVertexAttribArray(VERTEX_ATTR_SCENEPOSITION);
        // // Enable color = attribute VAO
        const GLuint VERTEX_ATTR_COLOR = 3;
        glEnableVertexAttribArray(VERTEX_ATTR_COLOR);
        // Specify the format of the vertex
        glBindBuffer(GL_ARRAY_BUFFER, r_vbo);
            glVertexAttribPointer(VERTEX_ATTR_VERTEXPOSITION, 3, GL_FLOAT, GL_FALSE, 3*sizeof(GL_FLOAT), 0); // Position
        glBindBuffer(GL_ARRAY_BUFFER, r_vboScenePosition);
            glVertexAttribPointer(VERTEX_ATTR_SCENEPOSITION, 3, GL_FLOAT, GL_FALSE, 3*sizeof(GL_FLOAT), 0); // Position scene
            glVertexAttribDivisor(VERTEX_ATTR_SCENEPOSITION, 1);
        glBindBuffer(GL_ARRAY_BUFFER, r_vboColor);
            glVertexAttribPointer(VERTEX_ATTR_COLOR, 3, GL_FLOAT, GL_FALSE, 3*sizeof(GL_FLOAT), 0); // Color
            glVertexAttribDivisor(VERTEX_ATTR_COLOR, 1);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    // Debind VAO
    glBindVertexArray(0);
}

Cursor::~Cursor() {
    glDeleteBuffers(1, &r_vbo);
    glDeleteBuffers(1, &r_vboScenePosition);
    glDeleteBuffers(1, &r_vboColor);
    glDeleteBuffers(1, &r_ibo);
    glDeleteVertexArrays(1, &r_vao);
}

void Cursor::drawCursor() const {
    glBindVertexArray(r_vao);
        glDrawElements(GL_LINES, 24, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void Cursor::updateCursorScenePosition() {
    glBindBuffer(GL_ARRAY_BUFFER, r_vboScenePosition);
        glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3), &r_position, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Cursor::updateCursorColor() {
    glBindBuffer(GL_ARRAY_BUFFER, r_vboColor);
        glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3), &r_color, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Cursor::changeColorOnSceneCube(const Scene &s) {
	int cubePosition = s.findCube(r_position);
	if(cubePosition != -1) {
		r_color = glm::vec3(1.0f, 0.0f, 1.0f);
	} else {
        r_color = glm::vec3(0.0f, 0.0f, 1.0f);
    }
    updateCursorColor();
}

void Cursor::moveFront(const float t, const Scene &s) {
	r_position.z += t;
    changeColorOnSceneCube(s);
    updateCursorScenePosition();
}

void Cursor::moveLeft(const float t, const Scene &s) {
	r_position.x -= t;
    changeColorOnSceneCube(s);
    updateCursorScenePosition();
}

void Cursor::moveUp(const float t, const Scene &s) {
	r_position.y += t;
    changeColorOnSceneCube(s);
    updateCursorScenePosition();
}

glm::vec3 Cursor::getPosition() const {
    return r_position;
}