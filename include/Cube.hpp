#pragma once
#include <glimac/common.hpp>
#include <vector>
#include <iostream>

using namespace glimac;

class Cube {

    private:
        std::vector<glimac::ShapeVertex> vertices;
        GLuint vao;
        GLuint vbo;
        GLuint ibo;

    public:
        Cube();
        ~Cube();
        void drawCube();
        void freeBuffersCube();

};
        