#pragma once
#include <glimac/common.hpp>
#include <vector>
#include <iostream>

using namespace glimac;

class Scene {

    private:
        GLuint s_vbo;
        GLuint s_vao;
        std::vector<glm::vec3> s_cubesPositions;

    public:
        Scene();
        ~Scene();
        void drawScene();
        void updateScene();
        void addCube(glm::vec3 position);
        int findCube(glm::vec3 position);
        void removeCube(glm::vec3 position);
        void freeBuffersScene();

};
        