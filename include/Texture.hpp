#pragma once

#include <glimac/common.hpp>
#include <glimac/Image.hpp>

#include <boost/filesystem.hpp>

#include <iostream>
#include <vector>
#include <string>

using namespace glimac;

class Texture {

    private:
    	struct TextureCube { 
    		std::string t_cubeName;
            GLuint t_cube;
            GLuint t_cubeRadio;
        };
        std::vector<Texture::TextureCube> t_cubeReferences;

    public:
        Texture();
        ~Texture();
        GLuint createCubeTexture(std::vector<std::string> filenames);
        GLuint createRadioTexture(std::string filename);
        void addCubeTexture(std::vector<std::string>  filenames, std::string name);
        int findTextureId(std::string textureName);
        std::vector<TextureCube> getCubeReferences();
        void deleteTextures();
};
        