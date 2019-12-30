#include <GL/glew.h>

#include <glimac/SDLWindowManager.hpp>
#include <glimac/Program.hpp>
#include <glimac/FilePath.hpp>

#include <imgui/imgui.h>
#include <imgui/imgui_impl_opengl3.h>
#include <imgui/imgui_impl_sdl.h>

#include <iostream>
#include <numeric>

#include "../include/Cube.hpp"
#include "../include/Scene.hpp"
#include "../include/Cursor.hpp"
#include "../include/Interface.hpp"
#include "../include/FreeFlyCamera.hpp"
#include "../include/Texture.hpp"

using namespace glimac;

struct ProgramScene {
    Program m_Program;

    GLint uMVMatrix;
    GLint uMVPMatrix;
    GLint uNormalMatrix;
    GLint uTextures;

    ProgramScene(const FilePath& applicationPath):
        m_Program(loadProgram(applicationPath.dirPath() + "shaders/3D.vs.glsl",
                              applicationPath.dirPath() + "shaders/3DMultiTex.fs.glsl")) {
        uMVPMatrix = glGetUniformLocation(m_Program.getGLId(), "uMVPMatrix");
        uMVMatrix = glGetUniformLocation(m_Program.getGLId(), "uMVMatrix");
        uNormalMatrix = glGetUniformLocation(m_Program.getGLId(), "uNormalMatrix");
        uTextures = glGetUniformLocation(m_Program.getGLId(), "uTextures");
    }
};

struct ProgramCursor {
    Program m_Program;

    GLint uMVMatrix;
    GLint uMVPMatrix;
    GLint uNormalMatrix;
    GLint uCursorPosition;
    GLint uCursorColor;

    ProgramCursor(const FilePath& applicationPath):
        m_Program(loadProgram(applicationPath.dirPath() + "shaders/cursor.vs.glsl",
                              applicationPath.dirPath() + "shaders/cursor.fs.glsl")) {
        uMVPMatrix = glGetUniformLocation(m_Program.getGLId(), "uMVPMatrix");
        uMVMatrix = glGetUniformLocation(m_Program.getGLId(), "uMVMatrix");
        uNormalMatrix = glGetUniformLocation(m_Program.getGLId(), "uNormalMatrix");
        uCursorPosition = glGetUniformLocation(m_Program.getGLId(), "uCursorPosition");
        uCursorColor = glGetUniformLocation(m_Program.getGLId(), "uCursorColor");
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
     * INITIALIZATION CODE
     *********************************/
    Scene scene;
    // Radial basis function scene
    RbfElts rbfElts(3);
    scene.sceneRbfInterpolation(rbfElts);
    Cursor cursor;
    // std::cout << "Cursor position : " << cursor.getPosition() << std::endl;
    cursor.getCubeInScene(scene);
    glm::vec3 cursorColor = glm::vec3(1, 0, 0);
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
                    // O key to move cursor backwards
                    case SDLK_o: cursor.moveFront(-1);
                    break;
                    // L key to move cursor forward
                    case SDLK_l: cursor.moveFront(1);
                    break;
                    // K key to move cursor left
                    case SDLK_k: cursor.moveLeft(1);
                    break;
                    // M key to move cussor right
                    case SDLK_m: cursor.moveLeft(-1);
                    break;
                    // I key to move cursor up
                    case SDLK_i: cursor.moveUp(1);
                    break;
                    // P key to move cursor down
                    case SDLK_p: cursor.moveUp(-1);
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
        // Activate depth
        glEnable(GL_DEPTH_TEST);
        // Definition of scene model matrix
        glm::mat4 MMatrix;
        glm::mat4 ViewMatrix = Camera.getViewMatrix();
        glm::mat4 MVMatrix = ViewMatrix * MMatrix;

        /* --------- Scene --------- */

        // Choose program
        programScene.m_Program.use();
        // Set uniform objects
        // char temp[200];
        // for(uint i = 0; i < texture.texturesCube.size(); ++i) {
        //     sprintf(temp, "uTextures[%d]", i);
        //     GLint loc = glGetUniformLocation(programScene.m_Program.getGLId(), temp);
        //     glUniform1i(loc, i);
        // }
        //glUniform1iv(loc, texture.texturesCube.size(), 0);
        GLint test[32];
        std::iota(std::begin(test), std::end(test), 0);
        glUniform1iv(programScene.uTextures, 32, test);

        // Send matrix
        glUniformMatrix4fv(programScene.uMVMatrix, 1, GL_FALSE, glm::value_ptr(MVMatrix));
        glUniformMatrix4fv(programScene.uNormalMatrix, 1, GL_FALSE, glm::value_ptr(glm::transpose(glm::inverse(MVMatrix))));
        glUniformMatrix4fv(programScene.uMVPMatrix, 1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMatrix));
        // Draw scene
        scene.drawScene();

        /* --------- Cursor --------- */

        // Set cursor
        cursor.getCubeInScene(scene);
        // Desactivate depth
        glDisable(GL_DEPTH_TEST);
        // Choose program
        programCursor.m_Program.use();
        // Select right color
        if(cursor.isOnCube()) {
            cursorColor = glm::vec3(0, 0, 1);
        }
        else if(!cursor.isOnCube()) {
            cursorColor = glm::vec3(1, 0, 0);
        }
        // Send matrix
        glUniformMatrix4fv(programCursor.uMVMatrix, 1, GL_FALSE, glm::value_ptr(MVMatrix));
        glUniformMatrix4fv(programCursor.uNormalMatrix, 1, GL_FALSE, glm::value_ptr(glm::transpose(glm::inverse(MVMatrix))));
        glUniformMatrix4fv(programCursor.uMVPMatrix, 1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMatrix));
        glUniform3f(programCursor.uCursorPosition, cursor.getPosition().x, cursor.getPosition().y, cursor.getPosition().z);
        glUniform3f(programCursor.uCursorColor, cursorColor.r, cursorColor.g, cursorColor.b);
        // Draw curosr
        cursor.drawCursor();

        /* --------- Interface --------- */

        interface.beginFrame(windowManager.window);
        interface.drawInterface(scene, cursor);
        interface.endFrame(windowManager.window);


        // Update the display
        windowManager.swapBuffers();

    }

    // Free resources
    scene.freeBuffersScene();
    cursor.freeBuffersCursor();

    return EXIT_SUCCESS;
}
