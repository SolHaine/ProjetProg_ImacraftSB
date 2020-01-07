#include "../include/Cube.hpp"

// struct ShapeVertex {
//     glm::vec3 position;
//     glm::vec3 normal;
//     glm::vec2 texCoords;

//     ShapeVertex(){}
//     ShapeVertex(glm::vec3 position, glm::vec3 normal, glm::vec2 texCoords):position(position), normal(normal), texCoords(texCoords){}
// };

Cube::Cube() {

    // Create VBO (Vertex Buffer Object)
    glGenBuffers(1, &c_vbo);
    // Bind VBO
    glBindBuffer(GL_ARRAY_BUFFER, c_vbo);
        // Fill VBO with vertices
        //    v------ v
        //   /|      /|
        //  v------v| |
        //  | |     | |
        //  | |v----|-|v
        //  |/      |/
        //  v------v
        std::vector<glm::vec3> c_vPosition = { 
            // Front face
            glm::vec3(-0.5f, -0.5f,  0.5f),
            glm::vec3(0.5f, -0.5f,  0.5f),
            glm::vec3(0.5f,  0.5f,  0.5f),
            glm::vec3(-0.5f,  0.5f,  0.5f),
            // Back face
            glm::vec3(-0.5f, -0.5f, -0.5f),
            glm::vec3(-0.5f,  0.5f, -0.5f),
            glm::vec3(0.5f,  0.5f, -0.5f),
            glm::vec3(0.5f, -0.5f, -0.5f),
            // Top face
            glm::vec3(-0.5f,  0.5f, -0.5f),
            glm::vec3(-0.5f,  0.5f,  0.5f),
            glm::vec3(0.5f,  0.5f,  0.5f),
            glm::vec3(0.5f,  0.5f, -0.5f),
            // Bottom face 
            glm::vec3(-0.5f, -0.5f, -0.5f),
            glm::vec3(0.5f, -0.5f, -0.5f),
            glm::vec3(0.5f, -0.5f,  0.5f),
            glm::vec3(-0.5f, -0.5f,  0.5f),
            // Left face 
            glm::vec3(-0.5f, -0.5f, -0.5f),
            glm::vec3(-0.5f, -0.5f,  0.5f),
            glm::vec3(-0.5f,  0.5f,  0.5f),
            glm::vec3(-0.5f,  0.5f, -0.5f),
            // Right face 
            glm::vec3(0.5f, -0.5f, -0.5f),
            glm::vec3(0.5f,  0.5f, -0.5f),
            glm::vec3(0.5f,  0.5f,  0.5f),
            glm::vec3(0.5f, -0.5f,  0.5f)
        };
        std::vector<glm::vec3> c_vNormals = { 
            // Front face
            glm::vec3(0.0f,  0.0f,  1.0f),
            glm::vec3(0.0f,  0.0f,  1.0f),
            glm::vec3(0.0f,  0.0f,  1.0f),
            glm::vec3(0.0f,  0.0f,  1.0f),
            // Back face
            glm::vec3(0.0f,  0.0f, -1.0f),
            glm::vec3(0.0f,  0.0f, -1.0f),
            glm::vec3(0.0f,  0.0f, -1.0f),
            glm::vec3(0.0f,  0.0f, -1.0f),
            // Top face
            glm::vec3(0.0f,  1.0f,  0.0f),
            glm::vec3(0.0f,  1.0f,  0.0f),
            glm::vec3(0.0f,  1.0f,  0.0f),
            glm::vec3(0.0f,  1.0f,  0.0f),
            // Bottom face 
            glm::vec3(0.0f, -1.0f,  0.0f),
            glm::vec3(0.0f, -1.0f,  0.0f),
            glm::vec3(0.0f, -1.0f,  0.0f),
            glm::vec3(0.0f, -1.0f,  0.0f),
            // Left face 
            glm::vec3(-1.0f,  0.0f,  0.0f),
            glm::vec3(-1.0f,  0.0f,  0.0f),
            glm::vec3(-1.0f,  0.0f,  0.0f),
            glm::vec3(-1.0f,  0.0f,  0.0f),
            // Right face 
            glm::vec3(1.0f,  0.0f,  0.0f),
            glm::vec3(1.0f,  0.0f,  0.0f),
            glm::vec3(1.0f,  0.0f,  0.0f),
            glm::vec3(1.0f,  0.0f,  0.0f)
        };
        for(size_t i = 0; i < c_vPosition.size(); ++i) {
            ShapeVertex vertex;
            vertex.position = c_vPosition[i]; // Position
            vertex.normal = c_vNormals[i]; // Normal
            c_vertices.push_back(vertex);
        }
        glBufferData(GL_ARRAY_BUFFER, c_vertices.size() * sizeof(ShapeVertex), c_vertices.data(), GL_STATIC_DRAW);
    // Debind VBO
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // Create IBO (Index Buffer Objects)
    glGenBuffers(1, &c_ibo);
    // Bind IBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, c_ibo);
        // Fill IBO with index
        //    v------ v
        //   /|      /|
        //  v------v| |
        //  | |     | |
        //  | |v----|-|v
        //  |/      |/
        //  v------v
        uint32_t indexCube[] = {
            // Back face
            0, 1, 2,
            0, 2, 3,
            // Front face
            4, 5, 6,
            4, 6, 7,
            // Top face
            8, 9, 10,
            8, 10, 11,
            // Bottom face
            12, 13, 14,
            12, 14, 15,
            // Left face
            16, 17, 18,
            16, 18, 19,
            // Right face
            20, 21, 22,
            20, 22, 23
        };
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexCube), indexCube, GL_STATIC_DRAW);
    // Debind IBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    // Create VAO (Vertex Array Object)
    glGenVertexArrays(1, &c_vao);
    // Bind VAO
    glBindVertexArray(c_vao);
        //Save IBO in VAO
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, c_ibo);
        // Enable position attribute VAO
        const GLuint VERTEX_ATTR_POSITION = 0;
        glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
        // Enable normale attribute VAO
        const GLuint VERTEX_ATTR_NORMAL = 1;
        glEnableVertexAttribArray(VERTEX_ATTR_NORMAL);
        glBindBuffer(GL_ARRAY_BUFFER, c_vbo);
            glVertexAttribPointer(VERTEX_ATTR_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), (const GLvoid*)offsetof(ShapeVertex, position)); // Position
            glVertexAttribPointer(VERTEX_ATTR_NORMAL, 3, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), (const GLvoid*)offsetof(ShapeVertex, normal)); // Normal
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    //Debind VAO
    glBindVertexArray(0);

}

Cube::~Cube() {
    glDeleteVertexArrays(1, &c_vao);
    glDeleteBuffers(1, &c_ibo);
    glDeleteBuffers(1, &c_vbo);
};

void Cube::drawCube() const {
    glBindVertexArray(c_vao);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
};

const GLuint Cube::getCVao() const {
    return c_vao;
};
