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
        void addCubeTexture(const std::vector<std::string> filenames, const std::string name);
        GLuint createCubeTexture(const std::vector<std::string> filenames);
        GLuint createRadioTexture(const std::string filename);
        int findTextureId(const std::string textureName) const;
        const std::vector<Texture::TextureCube>& getCubeReferences() const;
};
        