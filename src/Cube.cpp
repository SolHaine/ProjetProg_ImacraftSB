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
    glGenBuffers(1, &this->vbo);
    // Bind VBO
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
        //    v6----- v5
        //   /|      /|
        //  v1------v0|
        //  | |     | |
        //  | |v7---|-|v4
        //  |/      |/
        //  v2------v3
        std::vector<glm::vec3> vPositionCube = { 
            // v0
            glm::vec3(0.5f,0.5f,0.5f),
            // v1
            glm::vec3(-0.5f,0.5f,0.5f),
            // v2
            glm::vec3(-0.5f,-0.5f,0.5f),
            // v3
            glm::vec3(0.5f,-0.5f,0.5f),
            // v4
            glm::vec3(0.5f,-0.5f,-0.5f),
            // v5
            glm::vec3(0.5f,0.5f,-0.5f),
            // v6
            glm::vec3(-0.5f,0.5f,-0.5f),
            // v7
            glm::vec3(-0.5f,-0.5f,-0.5f)
        };
        std::vector<glm::vec2> vTexCoordsCube = {
            // v0
            glm::vec2(1,0),
            // v1
            glm::vec2(0,0),
            // v2
            glm::vec2(0,1),
            // v3
            glm::vec2(1,1),
            // v4
            glm::vec2(1,1),
            // v5
            glm::vec2(1,0),
            // v6
            glm::vec2(0,0),
            // v7
            glm::vec2(0,1)
        };
        for(size_t i = 0; i < vPositionCube.size(); ++i) {
            ShapeVertex vertex;

            // Position
            vertex.position.x = vPositionCube[i].x;
            vertex.position.y = vPositionCube[i].y;
            vertex.position.z = vPositionCube[i].z;
            // Normal
            vertex.normal = vertex.position;
            // Texture coordinates
            vertex.texCoords.x = vTexCoordsCube[i].x;
            vertex.texCoords.y = vTexCoordsCube[i].y;

            this->vertices.push_back(vertex);
        }
        // Fill VBO with vertices
        glBufferData(GL_ARRAY_BUFFER, (this->vertices.size())*sizeof(ShapeVertex), this->vertices.data(), GL_STATIC_DRAW);
    // Debind VBO
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // Create IBO (Index Buffer Objects)
    glGenBuffers(1, &this->ibo);
    // Bind IBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
        //    v6----- v5
        //   /|      /|
        //  v1------v0|
        //  | |     | |
        //  | |v7---|-|v4
        //  |/      |/
        //  v2------v3
        uint32_t index[] = {
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
        // Fill IBO with vertices
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(index), index, GL_STATIC_DRAW);
    // Debind IBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    // Create VAO (Vertex Array Object) - décrit les données
    glGenVertexArrays(1, &this->vao);
    // Bind VAO
    glBindVertexArray(vao);
        //Save IBO in VAO
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,ibo);
        // Enable position attribute VAO
        const GLuint VERTEX_ATTR_POSITION = 0;
        glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
        // Enable normale attribute VAO
        const GLuint VERTEX_ATTR_NORMAL = 1;
        glEnableVertexAttribArray(VERTEX_ATTR_NORMAL);
        // Enable texture attribute VAO
        const GLuint VERTEX_ATTR_TEXCOORDS = 2;
        glEnableVertexAttribArray(VERTEX_ATTR_TEXCOORDS);
        // Specify the format of the vertex position attribute
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
            glVertexAttribPointer(VERTEX_ATTR_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), (const GLvoid*)offsetof(ShapeVertex, position)); // Position
            glVertexAttribPointer(VERTEX_ATTR_NORMAL, 3, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), (const GLvoid*)offsetof(ShapeVertex, normal)); // Normal
            glVertexAttribPointer(VERTEX_ATTR_TEXCOORDS, 2, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), (const GLvoid*)offsetof(ShapeVertex, texCoords)); // Texture
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    //Debind VAO
    glBindVertexArray(0);

}

void Cube::drawCube(){
    glBindVertexArray(vao);
        glDrawElements(GL_TRIANGLES, 12*3, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
};

void Cube::freeBuffersCube() {
    glDeleteVertexArrays(1, &this->vao);
    glDeleteBuffers(1, &this->vbo);
}

Cube::~Cube() {
};
