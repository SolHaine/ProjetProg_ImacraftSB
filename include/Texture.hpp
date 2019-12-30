#pragma once

#include <glimac/common.hpp>
#include <glimac/Image.hpp>

#include <boost/filesystem.hpp>

#include <iostream>
#include <vector>
#include <string>

using namespace glimac;

class Texture {

    public:
    	struct TextureCube { 
    		std::string t_cubeName;
            GLuint t_cube;
            GLuint t_cubeRadio;
        };
        std::vector<TextureCube> t_cubeReferences;

    public:
        Texture();
        ~Texture();
        GLuint createCubeTexture(std::vector<std::string> filenames);
        GLuint createRadioTexture(std::string filename);
        int findTextureId(std::string textureName);
};
        