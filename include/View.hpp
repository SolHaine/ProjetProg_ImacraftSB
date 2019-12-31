#pragma once

#include <glimac/common.hpp>
#include <glimac/Program.hpp>
#include <glimac/FilePath.hpp>

#include <iostream>
#include <numeric>

#include "../include/Texture.hpp"

using namespace glimac;

class View {

    private:
        Program m_program;
        GLint m_uMVMatrix;
        GLint m_uMVPMatrix;
        GLint m_uNormalMatrix;
        GLint m_uTextures;

    public:
        View(const FilePath& applicationPath);
        ~View() = default;
        void useView() const;
        void sendMatrixView(const glm::mat4 MVMatrix, const glm::mat4 ProjMatrix) const;
        void sendTexturesView(const Texture &t) const;

};
        