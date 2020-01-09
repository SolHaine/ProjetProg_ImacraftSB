#include <GL/glew.h>

#include <glimac/SDLWindowManager.hpp>
#include <glimac/FilePath.hpp>

#include <imgui/imgui.h>
#include <imgui/imgui_impl_opengl3.h>
#include <imgui/imgui_impl_sdl.h>

#include <iostream>
#include <numeric>

#include "../include/View.hpp"
#include "../include/FreeFlyCamera.hpp"
#include "../include/Texture.hpp"
#include "../include/Scene.hpp"
#include "../include/Cursor.hpp"
#include "../include/Interface.hpp"
#include "../include/Lights.hpp"

using namespace glimac;

int main(int argc, char** argv) {

    // Initialize SDL and open a window
    SDLWindowManager windowManager(1024, 768, "ImacraftSB");

    // Initialize glew for OpenGL3+ support
    GLenum glewInitError = glewInit();
    if(GLEW_OK != glewInitError) {
        std::cerr << glewGetErrorString(glewInitError) << std::endl;
        return EXIT_FAILURE;
    }

    // Display versions
    std::cout << "OpenGL Version : " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLEW Version : " << glewGetString(GLEW_VERSION) << std::endl;

    // Activate depth
    glEnable(GL_DEPTH_TEST);

    // Definition of projection matrix
    glm::mat4 ProjMatrix = glm::perspective(glm::radians(70.f), 800.f/600.f, 0.1f, 100.f);

    /*********************************
     * INITIALIZATION CODE
     *********************************/
    
    // Definition of view (load, compile and use shaders)
    FilePath applicationPath(argv[0]);
    View view(applicationPath);

    // Definition of camera
    FreeFlyCamera Camera;

    // Definition of texture
    Texture texture;

    // Definition of scene
    Scene scene(texture, 30, 30);

    // Definition of cursor
    Cursor cursor(scene);

    // Definition of interface
    Interface interface(windowManager.window, &windowManager.openglContext);

    // Definition of lights
    Lights lights;


    /*********************************
    * APPLICATION LOOP
    *********************************/
    
    bool done = false;
    bool zPressed = false, sPressed = false, qPressed = false, dPressed = false, aPressed = false, ePressed = false;
    float speed = 0.001;

    while(!done) {

        // Event loop:
        SDL_Event e;
        while(windowManager.pollEvent(e)) {
            ImGui_ImplSDL2_ProcessEvent(&e);

            // Leave the loop after this iteration
            if(e.type == SDL_QUIT || (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE)) {
                done = true;
            }

            // Camera rotation with left click held
            if((e.type == SDL_MOUSEMOTION) && (e.motion.state & SDL_BUTTON_LEFT) && !(interface.isMouseOnInterface())) {
                Camera.rotateLeft(e.motion.xrel);
                Camera.rotateUp(e.motion.yrel);
            }

            // Camera and cursor move with keyboard keys
            if(e.type == SDL_KEYDOWN) {
                if(!ImGui::GetIO().WantCaptureKeyboard) {
                    switch(e.key.keysym.sym) {
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
                        // I key to move cursor up
                        case SDLK_i: cursor.moveUp(1, scene);
                        break;
                        // P key to move cursor down
                        case SDLK_p: cursor.moveUp(-1, scene);
                        break;

                        default: 
                        break;
                    }

                    // Cursor moves correctly for the user according to the camera rotation
                    float phi = Camera.getPhi();
                    if((phi>M_PI*0.75)&&(phi<M_PI*1.25)||(phi<-M_PI*0.75)&&(phi>-M_PI*1.25)) {
                        switch(e.key.keysym.sym) {
                            // O key to move cursor backwards
                            case SDLK_o: cursor.moveFront(-1, scene);
                            break;
                            // L key to move cursor forward
                            case SDLK_l: cursor.moveFront(1, scene);
                            break;
                            // K key to move cursor left
                            case SDLK_k: cursor.moveLeft(1, scene);
                            break;
                            // M key to move cussor right
                            case SDLK_m: cursor.moveLeft(-1, scene);
                            break;

                            default: 
                            break;
                        }
                    }
                    if((phi>M_PI*1.25)&&(phi<M_PI*1.75)||(phi<-M_PI*0.25)&&(phi>-M_PI*0.75)) {
                        switch(e.key.keysym.sym) {
                            // O key to move cursor backwards
                            case SDLK_o: cursor.moveLeft(1, scene);
                            break;
                            // L key to move cursor forward
                            case SDLK_l: cursor.moveLeft(-1, scene);
                            break;
                            // K key to move cursor left
                            case SDLK_k: cursor.moveFront(1, scene);
                            break;
                            // M key to move cussor right
                            case SDLK_m: cursor.moveFront(-1, scene);
                            break;

                            default: 
                            break;
                        }
                    }
                    if((phi>M_PI*0.25)&&(phi<M_PI*0.75) || (phi<-M_PI*1.25)&&(phi>-M_PI*1.75)) {
                        switch(e.key.keysym.sym) {
                            // O key to move cursor backwards
                            case SDLK_o: cursor.moveLeft(-1, scene);
                            break;
                            // L key to move cursor forward
                            case SDLK_l: cursor.moveLeft(1, scene);
                            break;
                            // K key to move cursor left
                            case SDLK_k: cursor.moveFront(-1, scene);
                            break;
                            // M key to move cussor right
                            case SDLK_m: cursor.moveFront(1, scene);
                            break;

                            default: 
                            break;
                        }
                    }
                    if((((phi>0)&&(phi<M_PI*0.25))||((phi>1.75*M_PI)&&(phi<M_PI*2))) || (((phi<0)&&(phi>-M_PI*0.25))||((phi<-M_PI*1.75)&&(phi>-M_PI*2)))) {
                        switch(e.key.keysym.sym) {
                            // O key to move cursor backwards
                            case SDLK_o: cursor.moveFront(1, scene);
                            break;
                            // L key to move cursor forward
                            case SDLK_l: cursor.moveFront(-1, scene);
                            break;
                            // K key to move cursor left
                            case SDLK_k: cursor.moveLeft(-1, scene);
                            break;
                            // M key to move cussor right
                            case SDLK_m: cursor.moveLeft(1, scene);
                            break;

                            default: 
                            break;
                        }
                    }
                }
            }

            if(e.type == SDL_KEYUP) {
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
        
        // Choose program
        view.useView();

        // Definition of matrix
        glm::mat4 MMatrix;
        glm::mat4 ViewMatrix = Camera.getViewMatrix();
        glm::mat4 MVMatrix = ViewMatrix * MMatrix;
        // Send uniforms (view matrix and textures)
        view.sendMatrixView(MVMatrix, ProjMatrix);
        view.sendTexturesView(texture);
        view.sendLightsView(lights);

        /* --------- Scene --------- */
        // Draw scene
        scene.drawScene();

        /* --------- Cursor --------- */
        // Desactivate depth
        glDisable(GL_DEPTH_TEST);
        // Draw cursor
        cursor.drawCursor();

        /* --------- Interface --------- */
        // Draw interface
        interface.beginFrame(windowManager.window);
        interface.drawInterface(scene, cursor, texture, lights);
        interface.endFrame(windowManager.window);

        // Update the display
        windowManager.swapBuffers();

    }

    return EXIT_SUCCESS;
}
