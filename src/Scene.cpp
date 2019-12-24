#include "../include/Scene.hpp"

Scene::Scene() {

    // Create VBO (Vertex Buffer Object)
    glGenBuffers(1, &s_vbo);
    
    // Create VAO (Vertex Array Object)
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

    // Create scene 1 X
    for (int i=-15; i<15; ++i){
        for (int j=-15; j<15; ++j){
            addCube(glm::vec3(i, -1, j));
            addCube(glm::vec3(i, -2, j));
            addCube(glm::vec3(i, -3, j));
        }
    }

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

int Scene::findCube(glm::vec3 position){
    for(int i = 0; i < s_cubesPositions.size(); ++i){
        if(glm::length(position-s_cubesPositions[i]) < 0.1f){
            return i;
        }
    }
    return -1; // -1 if we didn't find it
}

int Scene::getHighestCubeColumn(glm::vec3 position){
    int index = -1;
    for(int i = 0; i < s_cubesPositions.size(); ++i){
        if((position.x == s_cubesPositions[i].x) && (position.z == s_cubesPositions[i].z)){
            if((index == -1) || (position.y < s_cubesPositions[i].y)){
                position.y = s_cubesPositions[i].y;
                index = i;
            }
        }
    }
    return index; // -1 if we didn't find it
}

void Scene::addCube(glm::vec3 position){
    int index = findCube(position);
    if(index == -1){
        s_cubesPositions.push_back(position);
        updateScene();
    }
}

void Scene::deleteCube(glm::vec3 position){
    int index = findCube(position);
    if(index != -1){
        std::swap(s_cubesPositions[index], s_cubesPositions[s_cubesPositions.size() - 1]);
        s_cubesPositions.pop_back();
        //s_cubesPositions.erase(s_cubesPositions.begin() + index);
        updateScene();
    }
}

void Scene::extrudeCube(glm::vec3 position){
    int index = getHighestCubeColumn(position);
    if(index != -1){
        position = s_cubesPositions[index];
        (position.y)++;
        addCube(position);
    }
}

void Scene::digCube(glm::vec3 position){
    int index = getHighestCubeColumn(position);
    if(index != -1){
        position = s_cubesPositions[index];
        deleteCube(position);
    }
}

void Scene::freeBuffersScene() {
    glDeleteVertexArrays(1, &s_vao);
    glDeleteBuffers(1, &s_vbo);
}