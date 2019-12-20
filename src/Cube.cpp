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
        //    v6----- v5
        //   /|      /|
        //  v1------v0|
        //  | |     | |
        //  | |v7---|-|v4
        //  |/      |/
        //  v2------v3
        std::vector<glm::vec3> c_vPosition = { 
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
        std::vector<glm::vec2> c_vTexCoords = {
            // v0
            glm::vec2(1, 0),
            // v1
            glm::vec2(0, 0),
            // v2
            glm::vec2(0, 1),
            // v3
            glm::vec2(1, 1),
            // v4
            glm::vec2(1, 1),
            // v5
            glm::vec2(1, 0),
            // v6
            glm::vec2(0, 0),
            // v7
            glm::vec2(0, 1)
        };
        for(size_t i = 0; i < c_vPosition.size(); ++i) {
            ShapeVertex vertex;

            // Position
            vertex.position.x = c_vPosition[i].x;
            vertex.position.y = c_vPosition[i].y;
            vertex.position.z = c_vPosition[i].z;
            // Normal
            vertex.normal = vertex.position;
            // Texture coordinates
            vertex.texCoords.x = c_vTexCoords[i].x;
            vertex.texCoords.y = c_vTexCoords[i].y;

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
        //    v6----- v5
        //   /|      /|
        //  v1------v0|
        //  | |     | |
        //  | |v7---|-|v4
        //  |/      |/
        //  v2------v3
        uint32_t indexCube[] = {
            // front
            0, 1, 2,  0, 2, 3,
            // behind
            4, 7, 6,  4, 6, 5,
            // left
            1, 6, 7,  1, 7, 2,
            // right
            0, 3, 4,  0, 4, 5,
            // below
            2, 7, 4,  2, 4, 3,
            // above
            0, 5, 6,  0, 6, 1
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
        const GLuint VERTEX_ATTR_NORMAL = 2;
        glEnableVertexAttribArray(VERTEX_ATTR_NORMAL);
        // Enable texture attribute VAO
        const GLuint VERTEX_ATTR_TEXCOORDS = 3;
        glEnableVertexAttribArray(VERTEX_ATTR_TEXCOORDS);
        // Specify the format of the vertex
        glBindBuffer(GL_ARRAY_BUFFER, c_vbo);
            glVertexAttribPointer(VERTEX_ATTR_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), (const GLvoid*)offsetof(ShapeVertex, position)); // Position
            glVertexAttribPointer(VERTEX_ATTR_NORMAL, 3, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), (const GLvoid*)offsetof(ShapeVertex, normal)); // Normal
            glVertexAttribPointer(VERTEX_ATTR_TEXCOORDS, 2, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), (const GLvoid*)offsetof(ShapeVertex, texCoords)); // Texture
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    //Debind VAO
    glBindVertexArray(0);

}

Cube::~Cube() {
};

void Cube::drawCube(){
    glBindVertexArray(c_vao);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
};

void Cube::freeBuffersCube() {
    glDeleteVertexArrays(1, &c_vao);
    glDeleteBuffers(1, &c_ibo);
    glDeleteBuffers(1, &c_vbo);
}

GLuint Cube::getCVao(){
    return c_vao;
};
