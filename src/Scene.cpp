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
        // Enable color attribute VAO
        const GLuint VERTEX_ATTR_COLOR = 4;
        glEnableVertexAttribArray(VERTEX_ATTR_COLOR);
        // Specify the format of the vertex
        glBindBuffer(GL_ARRAY_BUFFER, s_vbo);
            glVertexAttribPointer(VERTEX_ATTR_SCENEPOSITION, 3, GL_FLOAT, GL_FALSE, sizeof(ShapeVertexScene), (const GLvoid*)offsetof(ShapeVertexScene, s_cubesPositions)); // Position
            glVertexAttribDivisor(1, 1);
            glVertexAttribPointer(VERTEX_ATTR_COLOR, 3, GL_FLOAT, GL_FALSE, sizeof(ShapeVertexScene), (const GLvoid*)offsetof(ShapeVertexScene, s_cubesColors)); // Color
            glVertexAttribDivisor(4, 1);
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
        glDrawElementsInstanced(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0, s_vertices.size());
    glBindVertexArray(0);
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

void Scene::addCube(glm::vec3 position, glm::vec3 color){
    deleteCube(position);
    s_vertices.push_back({position, color});
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
        glm::vec3 color = s_vertices[index].s_cubesColors;
        (position.y)++;
        addCube(position, color);
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
        //std::cout << color << std::endl;
        //std::cout << s_vertices[index].s_cubesColors << std::endl;
        s_vertices[index].s_cubesColors = color;
        for(int i = 0; i < s_vertices.size(); ++i){
            std::cout << s_vertices[i].s_cubesColors << std::endl;
        }
        updateScene();
    }
}

void Scene::freeBuffersScene() {
    glDeleteVertexArrays(1, &s_vao);
    glDeleteBuffers(1, &s_vbo);
}

//Radial basis function
void Scene::sceneRbfInterpolation(RbfElts &elts) {
    solver(elts);
    // Create interpolated scene
    for (int i=-15; i<15; ++i){
        for (int j=-15; j<15; ++j){
            glm::vec3 position = glm::vec3(i, 0, j);
            double weight = radialBasisFunction(elts, position);
            if(weight > 0) {
                for(int k=0; k<int(floor(weight)); k++) {
                    extrudeCube(position);
                }
            }
            else if(weight < 0) {
                for(int k=0; k<int(floor(-weight)); k++) {
                    digCube(position);
                }
            }
        }
    }
}