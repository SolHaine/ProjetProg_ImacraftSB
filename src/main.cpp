#include <GL/glew.h>

#include <glimac/SDLWindowManager.hpp>
#include <glimac/Program.hpp>
#include <glimac/FilePath.hpp>
#include <glimac/Image.hpp>
#include <glimac/FreeFlyCamera.hpp>

#include <iostream>

#include "../include/Cube.hpp"

using namespace glimac;

struct Scene {
    Program m_Program;

    GLint uMVMatrix;
    GLint uMVPMatrix;
    GLint uNormalMatrix;
    GLint uTexture;
    GLint uTexture2;

    Scene(const FilePath& applicationPath):
        m_Program(loadProgram(applicationPath.dirPath() + "shaders/3D.vs.glsl",
                              applicationPath.dirPath() + "shaders/normals.fs.glsl")) {
        uMVPMatrix = glGetUniformLocation(m_Program.getGLId(), "uMVPMatrix");
        uMVMatrix = glGetUniformLocation(m_Program.getGLId(), "uMVMatrix");
        uNormalMatrix = glGetUniformLocation(m_Program.getGLId(), "uNormalMatrix");
        uTexture = glGetUniformLocation(m_Program.getGLId(), "uTexture");
        uTexture2 = glGetUniformLocation(m_Program.getGLId(), "uTexture2");
    }
};

int main(int argc, char** argv) {
    // Initialize SDL and open a window
    SDLWindowManager windowManager(800, 600, "ImacraftSB");

    // Initialize glew for OpenGL3+ support
    GLenum glewInitError = glewInit();
    if(GLEW_OK != glewInitError) {
        std::cerr << glewGetErrorString(glewInitError) << std::endl;
        return EXIT_FAILURE;
    }

    // Load, compile and use shaders
    FilePath applicationPath(argv[0]);
    Scene scene(applicationPath);

    // Versions
    std::cout << "OpenGL Version : " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLEW Version : " << glewGetString(GLEW_VERSION) << std::endl;

    // Activate depth
    glEnable(GL_DEPTH_TEST);

    // Definition of projection matrix
    glm::mat4 ProjMatrix = glm::perspective(glm::radians(70.f), 800.f/600.f, 0.1f, 100.f);
    // Definition of camera
    FreeFlyCamera Camera;

    /*********************************
     * TEXTURES
     *********************************/
    // Load textures
    std::unique_ptr<Image> triForce = loadImage("assets/textures/triforce.png");
    if(triForce == NULL) {
        std::cout << "Erreur de chargement d'une des textures" << std::endl;
        exit(0);
    } else {
        std::cout << "Textures chargées" <<std::endl;
    }

    // Create textureObject
    GLuint textureObject;
    glGenTextures(1, &textureObject);
    // Bind textureObject
    glBindTexture(GL_TEXTURE_2D, textureObject);
        // Fill textureObject with the image
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, triForce->getWidth() , triForce->getHeight(), 0, GL_RGBA, GL_FLOAT, triForce->getPixels());
        // Filters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // Debind textureObject
    glBindTexture(GL_TEXTURE_2D, 0);

    /*********************************
     * INITIALIZATION CODE
     *********************************/
    Cube cube;

    /*********************************
    * APPLICATION LOOP
    *********************************/
    bool done = false;
    bool zPressed = false, sPressed = false, qPressed = false, dPressed = false, aPressed = false, ePressed = false;
    
    while(!done) {

        // Event loop:
        SDL_Event e;
        while(windowManager.pollEvent(e)){

            if(e.type == SDL_QUIT){
                done = true; // Leave the loop after this iteration
            }

            if(e.type == SDL_MOUSEMOTION && (e.motion.state & SDL_BUTTON_LEFT)){
                Camera.rotateLeft(e.motion.xrel);
                Camera.rotateUp(e.motion.yrel);
            }

            if(e.type == SDL_KEYDOWN){
                switch(e.key.keysym.sym){
                    // Z key to move forward
                    case SDLK_z: zPressed = true;
                    break;
                    // S key to move backward
                    case SDLK_s: sPressed = true;
                    break;
                    // Q key to move forward
                    case SDLK_q: qPressed = true;
                    break;
                    // D key to move backward
                    case SDLK_d: dPressed = true;
                    break;
                    // A key to move up
                    case SDLK_a: aPressed = true;
                    break;
                    // E key to move down
                    case SDLK_e: ePressed = true;
                    break;

                    default: 
                    break;
                }
            }

            if(e.type == SDL_KEYUP){
                switch(e.key.keysym.sym){
                    case SDLK_z: zPressed = false;
                    break;
                    case SDLK_s: sPressed = false;
                    break;
                    case SDLK_q: qPressed = false;
                    break;
                    case SDLK_d: dPressed = false;
                    break;
                    case SDLK_a: aPressed = false;
                    break;
                    case SDLK_e: ePressed = false;
                    break;

                    default: 
                    break;
                }
            }

        }
        float speed = 0.001;
        if(zPressed) Camera.moveFront(speed);
        if(sPressed) Camera.moveFront(-speed);
        if(qPressed) Camera.moveLeft(speed);
        if(dPressed) Camera.moveLeft(-speed);
        if(aPressed) Camera.moveUp(speed);
        if(ePressed) Camera.moveUp(-speed);

        /*********************************
         * RENDERING CODE
         *********************************/
        // Clean window and depth buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        /* --------- Scene --------- */

        // Choose program
        scene.m_Program.use();

        // Set uniform objects
        glUniform1i(scene.uTexture, 0);
        glUniform1i(scene.uTexture2, 1);

        // Definition of scene model matrix
        glm::mat4 MMatrix;
        MMatrix = glm::rotate(MMatrix, 90.0f, glm::vec3(0, 1, 0)); // Rotation
        // Send matrix
        glm::mat4 ViewMatrix = Camera.getViewMatrix();
        glm::mat4 MVMatrix = ViewMatrix * MMatrix;
        glUniformMatrix4fv(scene.uMVMatrix, 1, GL_FALSE, glm::value_ptr(MVMatrix));
        glUniformMatrix4fv(scene.uNormalMatrix, 1, GL_FALSE, glm::value_ptr(glm::transpose(glm::inverse(MVMatrix))));
        glUniformMatrix4fv(scene.uMVPMatrix, 1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMatrix));

        // Draw with textures
        glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, textureObject);
                cube.drawCube();
        glBindTexture(GL_TEXTURE_2D, 0);

        // Update the display
        windowManager.swapBuffers();
    }

    // Free resources
    cube.freeBuffersCube();
    glDeleteTextures(1, &textureObject);

    return EXIT_SUCCESS;
}
