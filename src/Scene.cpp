#include "../include/Scene.hpp"

Scene::Scene() {

    // Create VBO (Vertex Buffer Object)
    glGenBuffers(1, &s_vbo);
    
    // Create VAO (Vertex Array Object)
    s_vao = cube.getCVao();
    // Bind VAO
    glBindVertexArray(s_vao);
        // Enable scene position attribute VAO
        const GLuint VERTEX_ATTR_SCENEPOSITION = 3;
        glEnableVertexAttribArray(VERTEX_ATTR_SCENEPOSITION);
        // Enable color attribute VAO
        const GLuint VERTEX_ATTR_SCENECOLOR = 4;
        glEnableVertexAttribArray(VERTEX_ATTR_SCENECOLOR);
        // Enable texture attribute VAO
        const GLuint VERTEX_ATTR_SCENETEXTURE = 5;
        glEnableVertexAttribArray(VERTEX_ATTR_SCENETEXTURE);
        // Specify the format of the vertex
        glBindBuffer(GL_ARRAY_BUFFER, s_vbo);
            glVertexAttribPointer(VERTEX_ATTR_SCENEPOSITION, 3, GL_FLOAT, GL_FALSE, sizeof(ShapeVertexScene), (const GLvoid*)offsetof(ShapeVertexScene, s_cubesPositions)); // Position
            glVertexAttribDivisor(VERTEX_ATTR_SCENEPOSITION, 1);
            glVertexAttribPointer(VERTEX_ATTR_SCENECOLOR, 3, GL_FLOAT, GL_FALSE, sizeof(ShapeVertexScene), (const GLvoid*)offsetof(ShapeVertexScene, s_cubesColors)); // Color
            glVertexAttribDivisor(VERTEX_ATTR_SCENECOLOR, 1);
            glVertexAttribPointer(VERTEX_ATTR_SCENETEXTURE, 1, GL_FLOAT, GL_FALSE, sizeof(ShapeVertexScene), (const GLvoid*)offsetof(ShapeVertexScene, s_cubesTexture)); // Texture
            glVertexAttribDivisor(VERTEX_ATTR_SCENETEXTURE, 1);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    //Debind VAO
    glBindVertexArray(0);

    createSceneFlat();
}

Scene::~Scene() {
};

void Scene::createSceneFlat(){
    for (int i=-15; i<15; ++i){
        for (int j=-15; j<15; ++j){
            addCube(glm::vec3(i, -1, j), glm::vec3(0, 0, 0), "grass");
            addCube(glm::vec3(i, -2, j), glm::vec3(0, 0, 0), 1);
            addCube(glm::vec3(i, -3, j), glm::vec3(0, 0, 0), 2);
        }
    }
};

void Scene::drawScene(){
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glBindVertexArray(s_vao);
        for(uint i = 0; i < texture.t_cubeReferences.size(); ++i) {
            glActiveTexture(GL_TEXTURE0 + i);
            glBindTexture(GL_TEXTURE_CUBE_MAP, texture.t_cubeReferences[i].t_cube);
        }
        glDrawElementsInstanced(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0, s_vertices.size());
        for(uint i = 0; i < texture.t_cubeReferences.size(); ++i) {
            glActiveTexture(GL_TEXTURE0 + i);
            glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
        }
    glBindVertexArray(0);

    glDisable(GL_BLEND);
};

void Scene::updateScene(){
    // Bind VBO
    glBindBuffer(GL_ARRAY_BUFFER, s_vbo);
        // Update vertices of the VBO
        glBufferData(GL_ARRAY_BUFFER, s_vertices.size() * sizeof(ShapeVertexScene), s_vertices.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

int Scene::findCube(glm::vec3 position){
    for(int i = 0; i < s_vertices.size(); ++i){
        if(glm::length(position-s_vertices[i].s_cubesPositions) < 0.1f){
            return i;
        }
    }
    return -1; // -1 if we didn't find it
}

int Scene::getHighestCubeColumn(glm::vec3 position){
    int index = -1;
    for(int i = 0; i < s_vertices.size(); ++i){
        if((position.x == s_vertices[i].s_cubesPositions.x) && (position.z == s_vertices[i].s_cubesPositions.z)){
            if((index == -1) || (position.y < s_vertices[i].s_cubesPositions.y)){
                position.y = s_vertices[i].s_cubesPositions.y;
                index = i;
            }
        }
    }
    return index; // -1 if we didn't find it
}

void Scene::addCube(glm::vec3 position, glm::vec3 color, std::string textureName){
    deleteCube(position);

    int textureId = texture.findTextureId(textureName);
    s_vertices.push_back({position, color, textureId});
    
    updateScene();
}

void Scene::addCube(glm::vec3 position, glm::vec3 color, int textureId){
    deleteCube(position);

    s_vertices.push_back({position, color, textureId});
    
    updateScene();
}

void Scene::deleteCube(glm::vec3 position){
    int index = findCube(position);
    if(index != -1){
        std::swap(s_vertices[index], s_vertices[s_vertices.size() - 1]);
        s_vertices.pop_back();
        //s_vertices.erase(s_vertices.begin() + index);
        updateScene();
    }
}

void Scene::extrudeCube(glm::vec3 position){
    int index = getHighestCubeColumn(position);
    if(index != -1){
        position = s_vertices[index].s_cubesPositions;
        (position.y)++;
        glm::vec3 color = s_vertices[index].s_cubesColors;
        int texture = s_vertices[index].s_cubesTexture;
        addCube(position, color, texture);
    }

}

void Scene::digCube(glm::vec3 position){
    int index = getHighestCubeColumn(position);
    if(index != -1){
        position = s_vertices[index].s_cubesPositions;
        deleteCube(position);
    }
}

void Scene::changeColorCube(glm::vec3 position, glm::vec3 color){
    int index = findCube(position);
    if(index != -1) {
        s_vertices[index].s_cubesColors = color;
        updateScene();
    }
}

void Scene::changeTextureCube(glm::vec3 position, std::string textureName){
    int index = findCube(position);
    if(index != -1) {
        int textureId = texture.findTextureId(textureName);
        s_vertices[index].s_cubesTexture = textureId;
        updateScene();
    }
}

void Scene::changeTextureCube(glm::vec3 position, int textureId){
    int index = findCube(position);
    if(index != -1) {
        s_vertices[index].s_cubesTexture = textureId;
        updateScene();
    }
}

void Scene::freeBuffersScene() {
    glDeleteVertexArrays(1, &s_vao);
    glDeleteBuffers(1, &s_vbo);
}

// for(int i = 0; i < s_vertices.size(); ++i){
//     std::cout << s_vertices[i].s_cubesTexture << std::endl;
// }