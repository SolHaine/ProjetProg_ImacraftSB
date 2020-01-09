#include "../include/Scene.hpp"

Scene::Scene(const Texture &t, const uint width, const uint height) : s_width(width), s_height(height), texture(t) {

    // Create VBO (Vertex Buffer Object)
    glGenBuffers(1, &s_vbo);
    
    // Create VAO (Vertex Array Object)
    s_vao = cube.getCVao();
    // Bind VAO
    glBindVertexArray(s_vao);
        // Enable scene position attribute VAO
        const GLuint VERTEX_ATTR_SCENEPOSITION = 2;
        glEnableVertexAttribArray(VERTEX_ATTR_SCENEPOSITION);
        // Enable color attribute VAO
        const GLuint VERTEX_ATTR_SCENECOLOR = 3;
        glEnableVertexAttribArray(VERTEX_ATTR_SCENECOLOR);
        // Enable texture attribute VAO
        const GLuint VERTEX_ATTR_SCENETEXTURE = 4;
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
    // Debind VAO
    glBindVertexArray(0);

    // Create first scene
    createSceneFlat();
    createSceneRbfInterpolation();

}

Scene::~Scene() {
    glDeleteVertexArrays(1, &s_vao);
    glDeleteBuffers(1, &s_vbo);
};

void Scene::createSceneFlat() {
    for (int i = -(s_width/2); i < (s_width/2); ++i){
        for (int j = -(s_height/2); j < (s_height/2); ++j){
            addCube(glm::vec3(i, -1, j), glm::vec3(0, 0, 0), "grass");
            addCube(glm::vec3(i, -2, j), glm::vec3(0, 0, 0), "stone");
            addCube(glm::vec3(i, -3, j), glm::vec3(0, 0, 0), "stone");
            addCube(glm::vec3(i, -4, j), glm::vec3(0, 0, 0), "bedrock");
        }
    }
};

//Radial basis function
void Scene::createSceneRbfInterpolation() {
    RbfElts elts(6, s_width);
    solver(elts);
    // Create interpolated scene
    for (int i = -(s_width/2); i < (s_width/2); ++i){
        for (int j = -(s_height/2); j < (s_height/2); ++j){
            glm::vec3 position = glm::vec3(i, 0, j);
            double weight = radialBasisFunction(elts, position);
            if(weight > 0) {
                for(int k = 0; k < int(weight); ++k) {
                    extrudeCube(position);
                }
            } else if(weight < 0) {
                if(weight < -4) {
                    weight = -4;
                }
                for(int k = 0; k < int(-weight); ++k) {
                    digCube(position);
                }
            }
        }
    }
}

void Scene::drawScene() const {
    // Enable alpha
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glBindVertexArray(s_vao);
        for(uint i = 0; i < texture.getCubeReferences().size(); ++i) {
            glActiveTexture(GL_TEXTURE0 + i);
            glBindTexture(GL_TEXTURE_CUBE_MAP, texture.getCubeReferences()[i].t_cube);
        }
        glDrawElementsInstanced(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0, s_vertices.size());
        for(uint i = 0; i < texture.getCubeReferences().size(); ++i) {
            glActiveTexture(GL_TEXTURE0 + i);
            glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
        }
    glBindVertexArray(0);

    glDisable(GL_BLEND);
};

void Scene::updateScene() {
    glBindBuffer(GL_ARRAY_BUFFER, s_vbo);
        glBufferData(GL_ARRAY_BUFFER, s_vertices.size() * sizeof(ShapeVertexScene), s_vertices.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

const int Scene::findCube(const glm::vec3 position) const {
    for(int i = 0; i < s_vertices.size(); ++i){
        if(glm::length(position-s_vertices[i].s_cubesPositions) < 0.1f){
            return i;
        }
    }
    return -1; // -1 if we didn't find it
}

const int Scene::getHighestCubeColumn(glm::vec3 position) const {
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

void Scene::addCube(const glm::vec3 position, const glm::vec3 color, const std::string textureName){
    deleteCube(position);

    uint textureId = texture.findTextureId(textureName);
    s_vertices.push_back({position, color, textureId});
    
    updateScene();
}

void Scene::addCube(const glm::vec3 position, const glm::vec3 color, const uint textureId){
    deleteCube(position);

    s_vertices.push_back({position, color, textureId});
    
    updateScene();
}

void Scene::deleteCube(const glm::vec3 position){
    int index = findCube(position);
    if(index != -1){
        std::swap(s_vertices[index], s_vertices[s_vertices.size() - 1]);
        s_vertices.pop_back();
        //OR s_vertices.erase(s_vertices.begin() + index);
        updateScene();
    }
}

void Scene::extrudeCube(glm::vec3 position){
    int index = getHighestCubeColumn(position);
    if(index != -1){
        position = s_vertices[index].s_cubesPositions;
        glm::vec3 color = s_vertices[index].s_cubesColors;
        uint textureId = s_vertices[index].s_cubesTexture;
        if(texture.findTextureId("grass") != textureId){
            (position.y)++;
            addCube(position, color, textureId);
        } else {
            addCube(position, color, "dirt");
            (position.y)++;
            addCube(position, color, "grass");
        }
    }

}

void Scene::digCube(glm::vec3 position){
    int index = getHighestCubeColumn(position);
    if(index != -1){
        position = s_vertices[index].s_cubesPositions;
        deleteCube(position);
    }
}

void Scene::changeColorCube(const glm::vec3 position, const glm::vec3 color){
    int index = findCube(position);
    if(index != -1) {
        s_vertices[index].s_cubesColors = color;
        updateScene();
    }
}

void Scene::changeTextureCube(const glm::vec3 position, const std::string textureName){
    int index = findCube(position);
    if(index != -1) {
        int textureId = texture.findTextureId(textureName);
        s_vertices[index].s_cubesTexture = textureId;
        updateScene();
    }
}

void Scene::changeTextureCube(const glm::vec3 position, const uint textureId){
    int index = findCube(position);
    if(index != -1) {
        s_vertices[index].s_cubesTexture = textureId;
        updateScene();
    }
}

int Scene::saveScene(const std::string &filename, const Lights &lights) const {
    // Open file
    std::ofstream myFile;
    myFile.open("./bin/savedScenes/"+filename, std::ios::out | std::ios::binary);
    if(!myFile.is_open()) {
        std::cerr << "error : can not create file : " << filename << std::endl;
        return EXIT_FAILURE;
    }
    // Write the vector size and data
    myFile << s_vertices.size() << std::endl;
    for(size_t i=0; i<s_vertices.size(); ++i) {
        myFile << s_vertices[i].s_cubesPositions.x << " ";
        myFile << s_vertices[i].s_cubesPositions.y << " ";
        myFile << s_vertices[i].s_cubesPositions.z << " ";
        myFile << s_vertices[i].s_cubesColors.r << " ";
        myFile << s_vertices[i].s_cubesColors.g << " ";
        myFile << s_vertices[i].s_cubesColors.b << " ";
        myFile << s_vertices[i].s_cubesTexture << " ";
    }
    // Save light information
    myFile << lights.isDay() << " ";
    myFile << lights.getNbPonctualLights() << " ";
    std::vector<glm::vec3> ponctualLights = lights.getPonctualLightsPositions();
    for(size_t i=0; i<lights.getNbPonctualLights(); i++) {
        myFile << ponctualLights[i].x << " ";
        myFile << ponctualLights[i].y << " ";
        myFile << ponctualLights[i].z << " ";
    }
    // Close file
    myFile.close();
    std::cout << "Scene successfully saved" << std::endl;
    return EXIT_SUCCESS;
}

int Scene::loadScene(const std::string &filename, Lights &lights) {
    // Open file
    std::ifstream myFile;
    myFile.open("./bin/savedScenes/"+filename, std::ios::in | std::ios::binary);
    if(!myFile.is_open()) {
        std::cerr << "error : can not read file : " << filename << std::endl;
        return EXIT_FAILURE;
    }
    // Read the vector size
    size_t nbCubes;
    myFile >> nbCubes;
    // Reconstruct scene
    std::vector<ShapeVertexScene> vertices(nbCubes);
    for(size_t i=0; i<nbCubes; ++i) {
        myFile >> vertices[i].s_cubesPositions.x;
        myFile >> vertices[i].s_cubesPositions.y;
        myFile >> vertices[i].s_cubesPositions.z;
        myFile >> vertices[i].s_cubesColors.r;
        myFile >> vertices[i].s_cubesColors.g;
        myFile >> vertices[i].s_cubesColors.b;
        myFile >> vertices[i].s_cubesTexture;
    }
    // Load lights
    bool day;
    myFile >> day;
    if(day != lights.isDay()) {
        lights.switchDayNight();
    }
    lights.removeAllPonctualLight();
    glm::vec3 position;
    int nbLights;
    myFile >> nbLights;
    for(int i=0; i<nbLights; i++) {
        myFile >> position.x;
        myFile >> position.y;
        myFile >> position.z;
        lights.addPonctualLight(position);
    }    

    // Close file
    myFile.close();
    s_vertices = vertices;
    updateScene();
    std::cout << "Scene successfully loaded" << std::endl;
    return EXIT_SUCCESS;
}

void Scene::resetScene() {
    s_vertices.clear();
    createSceneFlat();
}