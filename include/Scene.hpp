#pragma once
#include <glimac/common.hpp>
#include <vector>
#include <iostream>

#include "../include/Cube.hpp"
#include "../include/math.hpp"

using namespace glimac;

class Scene {

    private:
        Cube cube;
        GLuint s_vbo;
        GLuint s_vao;

        struct ShapeVertexScene { 
            glm::vec3 s_cubesPositions;
            glm::vec3 s_cubesColors;
        };
        std::vector<ShapeVertexScene> s_vertices;

    public:
        Scene();
        ~Scene();
        void drawScene();
        void updateScene();
        int findCube(glm::vec3 position);
        int getHighestCubeColumn(glm::vec3 position);
        void deleteCube(glm::vec3 position);
        void addCube(glm::vec3 position, glm::vec3 color = glm::vec3(0, 0, 0));
        void extrudeCube(glm::vec3 position);
        void digCube(glm::vec3 position);
        void changeColorCube(glm::vec3 position, glm::vec3 color);
        void freeBuffersScene();

        //Radial basis function
        void sceneRbfInterpolation(RbfElts &elts);

};
        