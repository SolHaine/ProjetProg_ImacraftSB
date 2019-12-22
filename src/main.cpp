#include <GL/glew.h>

#include <glimac/SDLWindowManager.hpp>
#include <glimac/Program.hpp>
#include <glimac/FilePath.hpp>
#include <glimac/Image.hpp>

#include <imgui/imgui.h>
#include <imgui/imgui_impl_opengl3.h>
#include <imgui/imgui_impl_sdl.h>

#include <iostream>

#include "../include/Cube.hpp"
#include "../include/Scene.hpp"
#include "../include/Cursor.hpp"
#include "../include/Interface.hpp"
#include "../include/FreeFlyCamera.hpp"

using namespace glimac;

struct ProgramScene {
    Program m_Program;

    GLint uMVMatrix;
    GLint uMVPMatrix;
    GLint uNormalMatrix;
    GLint uTexture;
    GLint uTexture2;

    ProgramScene(const FilePath& applicationPath):
        m_Program(loadProgram(applicationPath.dirPath() + "shaders/3D.vs.glsl",
                              applicationPath.dirPath() + "shaders/normals.fs.glsl")) {
        uMVPMatrix = glGetUniformLocation(m_Program.getGLId(), "uMVPMatrix");
        uMVMatrix = glGetUniformLocation(m_Program.getGLId(), "uMVMatrix");
        uNormalMatrix = glGetUniformLocation(m_Program.getGLId(), "uNormalMatrix");
        uTexture = glGetUniformLocation(m_Program.getGLId(), "uTexture");
        uTexture2 = glGetUniformLocation(m_Program.getGLId(), "uTexture2");
    }
};

struct ProgramCursor {
    Program m_Program;

    GLint uMVMatrix;
    GLint uMVPMatrix;
    GLint uNormalMatrix;
    GLint uCursorPosition;

    ProgramCursor(const FilePath& applicationPath):
        m_Program(loadProgram(applicationPath.dirPath() + "shaders/cursor.vs.glsl",
                              applicationPath.dirPath() + "shaders/cursor.fs.glsl")) {
        uMVPMatrix = glGetUniformLocation(m_Program.getGLId(), "uMVPMatrix");
        uMVMatrix = glGetUniformLocation(m_Program.getGLId(), "uMVMatrix");
        uNormalMatrix = glGetUniformLocation(m_Program.getGLId(), "uNormalMatrix");
        uCursorPosition = glGetUniformLocation(m_Program.getGLId(), "uCursorPosition");
    }
};

int main(int argc, char** argv) {
    // Initialize SDL and open a window
    SDLWindowManager windowManager(1024, 768, "ImacraftSB");

    // Initialize glew for OpenGL3+ support
    GLenum glewInitError = glewInit();
    if(GLEW_OK != glewInitError) {
        std::cerr << glewGetErrorString(glewInitError) << std::endl;
        return EXIT_FAILURE;
    }

    // Load, compile and use shaders
    FilePath applicationPath(argv[0]);
    ProgramScene programScene(applicationPath);
    ProgramCursor programCursor(applicationPath);

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
    Scene scene;
    Cursor cursor;
    std::cout << "Cursor position : " << cursor.getPosition() << std::endl;
    Interface interface;
    interface.initImgui(windowManager.window, &windowManager.openglContext);

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
                    // O key to move cursor forward
                    case SDLK_o: cursor.moveFront(1);
                                std::cout << "Cursor position : " << cursor.getPosition() << std::endl;
                                cursor.getCubeInScene(scene);

                    break;
                    // L key to move cursor backward
                    case SDLK_l: cursor.moveFront(-1);
                                std::cout << "Cursor position : " << cursor.getPosition() << std::endl;
                                cursor.getCubeInScene(scene);

                    break;
                    // K key to move cursor forward
                    case SDLK_k: cursor.moveLeft(1);
                                std::cout << "Cursor position : " << cursor.getPosition() << std::endl;
                                cursor.getCubeInScene(scene);

                    break;
                    // M key to move cussor backward
                    case SDLK_m: cursor.moveLeft(-1);
                                std::cout << "Cursor position : " << cursor.getPosition() << std::endl;
                                cursor.getCubeInScene(scene);

                    break;
                    // I key to move cursor up
                    case SDLK_i: cursor.moveUp(1);
                                std::cout << "Cursor position : " << cursor.getPosition() << std::endl;
                                cursor.getCubeInScene(scene);

                    break;
                    // P key to move cursor down
                    case SDLK_p: cursor.moveUp(-1);
                                std::cout << "Cursor position : " << cursor.getPosition() << std::endl;
                                cursor.getCubeInScene(scene);

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
        programScene.m_Program.use();

        // Set uniform objects
        glUniform1i(programScene.uTexture, 0);
        glUniform1i(programScene.uTexture2, 1);

        // Activate depth
        glEnable(GL_DEPTH_TEST);

        // Definition of scene model matrix
        glm::mat4 MMatrix;
        //MMatrix = glm::rotate(MMatrix, 90.0f, glm::vec3(0, 1, 0)); // Rotation
        // Send matrix
        glm::mat4 ViewMatrix = Camera.getViewMatrix();
        glm::mat4 MVMatrix = ViewMatrix * MMatrix;
        glUniformMatrix4fv(programScene.uMVMatrix, 1, GL_FALSE, glm::value_ptr(MVMatrix));
        glUniformMatrix4fv(programScene.uNormalMatrix, 1, GL_FALSE, glm::value_ptr(glm::transpose(glm::inverse(MVMatrix))));
        glUniformMatrix4fv(programScene.uMVPMatrix, 1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMatrix));

        // Draw with textures
        scene.drawScene();

        interface.beginFrame(windowManager.window);
        interface.drawInterface(scene);
        interface.endFrame(windowManager.window);

        programCursor.m_Program.use();

        glUniformMatrix4fv(programCursor.uMVMatrix, 1, GL_FALSE, glm::value_ptr(MVMatrix));
        glUniformMatrix4fv(programCursor.uNormalMatrix, 1, GL_FALSE, glm::value_ptr(glm::transpose(glm::inverse(MVMatrix))));
        glUniformMatrix4fv(programCursor.uMVPMatrix, 1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMatrix));
        glUniform3f(programCursor.uCursorPosition, cursor.getPosition().x, cursor.getPosition().y, cursor.getPosition().z);

        // Desactivate depth
        glDisable(GL_DEPTH_TEST);

        cursor.drawSelection();

        // Update the display
        windowManager.swapBuffers();

    }

    // Free resources
    scene.freeBuffersScene();
    cursor.freeBuffers();
    glDeleteTextures(1, &textureObject);

    return EXIT_SUCCESS;
}
