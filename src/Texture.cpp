#include "../include/Texture.hpp"

Texture::Texture() {

    boost::filesystem::path pathCubeTextures("assets/textures/cube_textures");

    std::string filenameNoTexture = pathCubeTextures.string() + "/no_texture.png";
    GLuint textureRadio = createRadioTexture(filenameNoTexture);
    t_cubeReferences.push_back({"no_texture", (GLuint)0, textureRadio});

    std::vector<boost::filesystem::path> directoriesCubeTextures;
    for(auto &p : boost::filesystem::directory_iterator(pathCubeTextures)){ 
        if(is_directory(p)){
            directoriesCubeTextures.push_back(p.path());
        }
    }
    for (uint i = 0; i < directoriesCubeTextures.size(); i++) {
        std::vector<std::string> filenames(6);
        std::string filenameCubeTexture = directoriesCubeTextures[i].string() + "/" + directoriesCubeTextures[i].filename().string();
        filenames[0] = filenameCubeTexture + ".png";
        filenames[1] = filenameCubeTexture + ".png";
        filenames[2] = (boost::filesystem::exists(filenameCubeTexture + "_top.png")) ? filenameCubeTexture + "_top.png" : filenameCubeTexture + ".png";
        filenames[3] = (boost::filesystem::exists(filenameCubeTexture + "_bottom.png")) ? filenameCubeTexture + "_bottom.png" : filenameCubeTexture + ".png";
        filenames[4] = (boost::filesystem::exists(filenameCubeTexture + "_front.png")) ?  filenameCubeTexture + "_front.png" : filenameCubeTexture + ".png";
        filenames[5] = (boost::filesystem::exists(filenameCubeTexture + "_back.png")) ?  filenameCubeTexture + "_back.png" : filenameCubeTexture + ".png";
        addCubeTexture(filenames, directoriesCubeTextures[i].filename().string());
    }  

    std::cout << "lol" << std::endl;

}

Texture::~Texture() {
};

GLuint Texture::createCubeTexture(std::vector<std::string> filenames){
    // Create textureObject
    GLuint textureCube;
    glGenTextures(1, &textureCube);
     // Bind textureObject
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureCube); 
        // Fill textureObject with the images
        for (uint i = 0; i < filenames.size(); i++) {
            std::unique_ptr<Image> textureImage = loadImage(filenames[i].c_str());
            if (textureImage != NULL) {
                glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA, textureImage->getWidth(), textureImage->getHeight(), 0, GL_RGBA, GL_FLOAT, textureImage->getPixels());
            } else {
                std::cout << "Texture loading error: " << filenames[i] << std::endl;
                exit(0);
            }
        }
        // Filters
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    // Debind textureObject
    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

    return textureCube;
}

GLuint Texture::createRadioTexture(std::string filename){
    // Create textureObject
    GLuint textureRadio;
    glGenTextures(1, &textureRadio);
    // Bind textureObject
    glBindTexture(GL_TEXTURE_2D, textureRadio);
        // Fill textureObject with the image
        std::unique_ptr<Image> textureImage = loadImage(filename);
        if(textureImage != NULL) {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textureImage->getWidth() , textureImage->getHeight(), 0, GL_RGBA, GL_FLOAT, textureImage->getPixels());
        } else {
            std::cout << "Texture loading error: " << filename << std::endl;
            exit(0);
        }
        // Filters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    // Debind textureObject
    glBindTexture(GL_TEXTURE_2D, 0);

    return textureRadio;
}

void Texture::addCubeTexture(std::vector<std::string> filenames, std::string name){
    GLuint textureCube = createCubeTexture(filenames);
    GLuint textureCubeRadio = createRadioTexture(filenames[4]);
    t_cubeReferences.push_back({name, textureCube, textureCubeRadio});
}

int Texture::findTextureId(std::string textureName){
    int textureId = -1;
    for (int i = 0; i < t_cubeReferences.size(); ++i) {
        if(t_cubeReferences[i].t_cubeName == textureName){
            textureId = i;
        }
    }
    return textureId;
}

std::vector<Texture::TextureCube> Texture::getCubeReferences() {
    return t_cubeReferences;
}

void Texture::deleteTextures() {
    for (int i = 0; i < t_cubeReferences.size(); ++i) {
        glDeleteTextures(1, &(t_cubeReferences[i].t_cube));
        glDeleteTextures(1, &(t_cubeReferences[i].t_cubeRadio));
    }
}