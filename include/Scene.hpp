#pragma once
#include <glimac/common.hpp>
#include <vector>
#include <iostream>

#include "../include/Cube.hpp"

using namespace glimac;

class Scene {

    private:
        Cube cube;
        GLuint s_vbo;
        GLuint s_vao;
        std::vector<glm::vec3> s_cubesPositions;

    public:
        Scene();
        ~Scene();
        void drawScene();
        void updateScene();
        int findCube(glm::vec3 position);
        int getHighestCubeColumn(glm::vec3 position);
        void deleteCube(glm::vec3 position);
        void addCube(glm::vec3 position);
        void extrudeCube(glm::vec3 position);
        void digCube(glm::vec3 position);
        void freeBuffersScene();

};
        