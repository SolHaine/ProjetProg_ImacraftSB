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
        int s_width;
        int s_height;

        struct ShapeVertexScene { 
            glm::vec3 s_cubesPositions;
            glm::vec3 s_cubesColors;
            uint s_cubesTexture;
        };
        std::vector<ShapeVertexScene> s_vertices;

    public:
        Scene(const Texture &t, const uint width, const uint height);
        ~Scene();
        void createSceneFlat();
        void createSceneRbfInterpolation();
        void drawScene() const;
        void updateScene();
        const int findCube(const glm::vec3 position) const;
        const int getHighestCubeColumn(glm::vec3 position) const;
        void addCube(const glm::vec3 position, const glm::vec3 color = glm::vec3(0, 0, 0), const std::string textureName = "no_texture");
        void addCube(const glm::vec3 position, const glm::vec3 color = glm::vec3(0, 0, 0), const uint textureId = 0);
        void deleteCube(const glm::vec3 position);
        void extrudeCube(glm::vec3 position);
        void digCube(glm::vec3 position);
        void changeColorCube(const glm::vec3 position, const glm::vec3 color = glm::vec3(0, 0, 0));
        void changeTextureCube(const glm::vec3 position, const std::string textureName = "no_texture");
        void changeTextureCube(const glm::vec3 position, const uint textureId = 0);
        int saveScene(const std::string &filename) const;
        int loadScene(const std::string &filename);

};
        