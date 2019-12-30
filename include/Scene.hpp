#pragma once
#include <glimac/common.hpp>
#include <vector>
#include <iostream>

#include "../include/Cube.hpp"
#include "../include/Math.hpp"
#include "../include/Texture.hpp"

using namespace glimac;

class Scene {

    private:
        Cube cube;
        Texture texture;
        GLuint s_vbo;
        GLuint s_vao;

        struct ShapeVertexScene { 
            glm::vec3 s_cubesPositions;
            glm::vec3 s_cubesColors;
            int s_cubesTexture;
        };
        std::vector<ShapeVertexScene> s_vertices;

    public:
        Scene(Texture t);
        ~Scene();
        void createSceneFlat();
        void createSceneRbfInterpolation();
        void drawScene();
        void updateScene();
        int findCube(glm::vec3 position);
        int getHighestCubeColumn(glm::vec3 position);
        void deleteCube(glm::vec3 position);
        void addCube(glm::vec3 position, glm::vec3 color = glm::vec3(0, 0, 0), std::string textureName = "no_texture");
        void addCube(glm::vec3 position, glm::vec3 color = glm::vec3(0, 0, 0), int textureId = 0);
        void extrudeCube(glm::vec3 position);
        void digCube(glm::vec3 position);
        void changeColorCube(glm::vec3 position, glm::vec3 color = glm::vec3(0, 0, 0));
        void changeTextureCube(glm::vec3 position, std::string textureName = "no_texture");
        void changeTextureCube(glm::vec3 position, int textureId = 0);
        void freeBuffersScene();

};
        