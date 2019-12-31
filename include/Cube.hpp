#pragma once

#include <glimac/common.hpp>

#include <iostream>
#include <vector>

using namespace glimac;

class Cube {

    private:
        GLuint c_vbo;
        GLuint c_ibo;
        GLuint c_vao;
        std::vector<ShapeVertex> c_vertices;

    public:
        Cube();
        ~Cube();
        void drawCube() const;
        const GLuint getCVao() const;

};
        