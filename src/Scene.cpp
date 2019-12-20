#include "../include/Scene.hpp"
#include "../include/Cube.hpp"

Scene::Scene() {

    // Create VBO (Vertex Buffer Object)
    glGenBuffers(1, &s_vbo);
    // Fill VBO with vertices
    for (int i=-15; i<15; ++i){
        for (int j=-15; j<15; ++j){
            addCube(glm::vec3(i, -1, j));
            addCube(glm::vec3(i, -2, j));
            addCube(glm::vec3(i, -3, j));
        }
    }
    
    // Create VAO (Vertex Array Object)
    Cube cube;
    s_vao = cube.getCVao();
    // Bind VAO
    glBindVertexArray(s_vao);
        // Enable scene position attribute VAO
        const GLuint VERTEX_ATTR_SCENEPOSITION = 1;
        glEnableVertexAttribArray(VERTEX_ATTR_SCENEPOSITION);
        // Specify the format of the vertex
        glBindBuffer(GL_ARRAY_BUFFER, s_vbo);
            glVertexAttribPointer(VERTEX_ATTR_SCENEPOSITION, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0); // Position
            glVertexAttribDivisor(1, 1);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    //Debind VAO
    glBindVertexArray(0);

}

Scene::~Scene() {
};

void Scene::drawScene(){
    glBindVertexArray(s_vao);
        glDrawElementsInstanced(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0, s_cubesPositions.size());
    glBindVertexArray(0);
};

void Scene::updateScene(){
    // Bind VBO
    glBindBuffer(GL_ARRAY_BUFFER, s_vbo);
        // Update vertices of the VBO
        glBufferData(GL_ARRAY_BUFFER, s_cubesPositions.size() * sizeof(glm::vec3), s_cubesPositions.size() > 0 ? &(s_cubesPositions)[0] : nullptr, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Scene::addCube(glm::vec3 position){
    removeCube(position);
    s_cubesPositions.push_back(position);
    updateScene();
}

int Scene::findCube(glm::vec3 position){
    for(int i=0; i < s_cubesPositions.size(); ++i){
        if(glm::length(position-s_cubesPositions[i]) < 0.1f){
            return i;
        }
    }
    return -1; // if we didn't find it
}

void Scene::removeCube(glm::vec3 position){
    int index = findCube(position);
    if(index != -1){
        int lastIndex = s_cubesPositions.size() - 1;
        std::swap(s_cubesPositions[index], s_cubesPositions[lastIndex]);
        s_cubesPositions.pop_back();
        updateScene();
    }
}

void Scene::freeBuffersScene() {
    glDeleteVertexArrays(1, &s_vao);
    glDeleteBuffers(1, &s_vbo);
}
