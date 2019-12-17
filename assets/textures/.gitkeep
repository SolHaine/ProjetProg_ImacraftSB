#include <glimac/SDLWindowManager.hpp>
#include <GL/glew.h>

#include <iostream>

#include <glimac/Program.hpp>
#include <glimac/FilePath.hpp>
#include <glimac/Image.hpp>
#include <glimac/Sphere.hpp>
#include <glimac/FreeFlyCamera.hpp>

using namespace glimac;

// struct ShapeVertex {
//     glm::vec3 position;
//     glm::vec3 normal;
//     glm::vec2 texCoords;

//     ShapeVertex(){}
//     ShapeVertex(glm::vec3 position, glm::vec3 normal, glm::vec2 texCoords):position(position), normal(normal), texCoords(texCoords){}
// };

struct EarthProgram {
    Program m_Program;

    GLint uMVPMatrix;
    GLint uMVMatrix;
    GLint uNormalMatrix;
    GLint uTexture;
    GLint uTexture2;

    EarthProgram(const FilePath& applicationPath):
        m_Program(loadProgram(applicationPath.dirPath() + "shaders/3D.vs.glsl",
                              applicationPath.dirPath() + "shaders/multiTex3D.fs.glsl")) {
        uMVPMatrix = glGetUniformLocation(m_Program.getGLId(), "uMVPMatrix");
        uMVMatrix = glGetUniformLocation(m_Program.getGLId(), "uMVMatrix");
        uNormalMatrix = glGetUniformLocation(m_Program.getGLId(), "uNormalMatrix");
        uTexture = glGetUniformLocation(m_Program.getGLId(), "uTexture");
        uTexture2 = glGetUniformLocation(m_Program.getGLId(), "uTexture2");
    }
};

struct MoonProgram {
    Program m_Program;

    GLint uMVPMatrix;
    GLint uMVMatrix;
    GLint uNormalMatrix;
    GLint uTexture;

    MoonProgram(const FilePath& applicationPath):
        m_Program(loadProgram(applicationPath.dirPath() + "shaders/3D.vs.glsl",
                              applicationPath.dirPath() + "shaders/tex3D.fs.glsl")) {
        uMVPMatrix = glGetUniformLocation(m_Program.getGLId(), "uMVPMatrix");
        uMVMatrix = glGetUniformLocation(m_Program.getGLId(), "uMVMatrix");
        uNormalMatrix = glGetUniformLocation(m_Program.getGLId(), "uNormalMatrix");
        uTexture = glGetUniformLocation(m_Program.getGLId(), "uTexture");
    }
};

int main(int argc, char** argv) {
    // Initialize SDL and open a window
    SDLWindowManager windowManager(800, 600, "GLImac");

    // Initialize glew for OpenGL3+ support
    GLenum glewInitError = glewInit();
    if(GLEW_OK != glewInitError) {
        std::cerr << glewGetErrorString(glewInitError) << std::endl;
        return EXIT_FAILURE;
    }

    // Load, compile and use shaders
    FilePath applicationPath(argv[0]);
    EarthProgram earthProgram(applicationPath);
    MoonProgram moonProgram(applicationPath);
    //program.use();

    // Activate depth
    glEnable(GL_DEPTH_TEST);

    // Definition of projection matrix
    glm::mat4 ProjMatrix = glm::perspective(glm::radians(70.f), 800.f/600.f, 0.1f, 100.f);

    // Definition of camera
    FreeFlyCamera Camera;

    // Create axes sphere placement
    std::vector<glm::vec3> AxesRotation;
    std::vector<glm::vec3> Translations;
    for (int i=0; i<32; ++i) { 
        AxesRotation.push_back(glm::sphericalRand(1.0f));
        Translations.push_back(glm::sphericalRand(2.0f));
    }

    // Versions
    std::cout << "OpenGL Version : " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLEW Version : " << glewGetString(GLEW_VERSION) << std::endl;

    /*********************************
     * TEXTURES
     *********************************/
    // Load textures
    std::unique_ptr<Image> EarthMap = loadImage("/media/baptisteo/OS/Users/OryBa/Documents/Pas logiciels/Études/IMAC2/Synthèse d'images/TDs/GLImac-Template/assets/textures/EarthMap.jpg");
    std::unique_ptr<Image> MoonMap = loadImage("/media/baptisteo/OS/Users/OryBa/Documents/Pas logiciels/Études/IMAC2/Synthèse d'images/TDs/GLImac-Template/assets/textures/MoonMap.jpg");
    std::unique_ptr<Image> CloudMap = loadImage("/media/baptisteo/OS/Users/OryBa/Documents/Pas logiciels/Études/IMAC2/Synthèse d'images/TDs/GLImac-Template/assets/textures/CloudMap.jpg");
    if(EarthMap == NULL || MoonMap == NULL || CloudMap == NULL) {
        std::cout << "Erreur de chargement d'une des textures" << std::endl;
        exit(0);
    } else {
        std::cout << "Textures chargées" <<std::endl;
    }

    // Create textureObjectE
    GLuint textureObjectE;
    glGenTextures(1, &textureObjectE);
    // Bind textureObjectE
    glBindTexture(GL_TEXTURE_2D, textureObjectE);
        // Fill textureObject with the image
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, EarthMap->getWidth() , EarthMap->getHeight(), 0, GL_RGBA, GL_FLOAT, EarthMap->getPixels());
        // Filters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // Debind textureObjectE
    glBindTexture(GL_TEXTURE_2D, 0);
    // Create textureObjectM
    GLuint textureObjectM;
    glGenTextures(1, &textureObjectM);
    // Bind textureObjectM
    glBindTexture(GL_TEXTURE_2D, textureObjectM);
        // Fill textureObject with the image
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, MoonMap->getWidth() , MoonMap->getHeight(), 0, GL_RGBA, GL_FLOAT, MoonMap->getPixels());  
        // Filters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // Debind textureObjectM
    glBindTexture(GL_TEXTURE_2D, 0);
    // Create textureObjectM
    GLuint textureObjectC;
    glGenTextures(1, &textureObjectC);
    // Bind textureObjectC
    glBindTexture(GL_TEXTURE_2D, textureObjectC);
        // Fill textureObject with the image
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, CloudMap->getWidth() , CloudMap->getHeight(), 0, GL_RGBA, GL_FLOAT, CloudMap->getPixels());  
        // Filters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // Debind textureObjectC
    glBindTexture(GL_TEXTURE_2D, 0);

    /*********************************
     * INITIALIZATION CODE
     *********************************/
    // Create sphere
    Sphere sphere(1, 32, 16);

    // Create VBO (Vertex Buffer Object) - contient les données
    GLuint vbo;
    glGenBuffers(1, &vbo);
    // Bind VBO
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
        // Fill VBO with vertices
        glBufferData(GL_ARRAY_BUFFER, sphere.getVertexCount()*sizeof(ShapeVertex), sphere.getDataPointer(), GL_STATIC_DRAW);
    // Debind VBO
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // Create VAO (Vertex Array Object) - décrit les données
    GLuint vao;
    glGenVertexArrays(1, &vao);
    // Bind VAO
    glBindVertexArray(vao);
        // Enable position attribute VAO
        const GLuint VERTEX_ATTR_POSITION = 0;
        glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
        // Enable normale attribute VAO
        const GLuint VERTEX_ATTR_NORMAL = 1;
        glEnableVertexAttribArray(VERTEX_ATTR_NORMAL);
        // Enable texture attribute VAO
        const GLuint VERTEX_ATTR_TEXCOORDS = 2;
        glEnableVertexAttribArray(VERTEX_ATTR_TEXCOORDS);
        // Specify the format of the vertex position attribute
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glVertexAttribPointer(VERTEX_ATTR_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), (const GLvoid*)offsetof(ShapeVertex, position)); // Position
        glVertexAttribPointer(VERTEX_ATTR_NORMAL, 3, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), (const GLvoid*)offsetof(ShapeVertex, normal)); // Normal
        glVertexAttribPointer(VERTEX_ATTR_TEXCOORDS, 2, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), (const GLvoid*)offsetof(ShapeVertex, texCoords)); // Texture
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    //Debind VAO
    glBindVertexArray(0);

    /*********************************
    * APPLICATION LOOP
    *********************************/
    bool done = false;
    bool zPressed = false, sPressed = false, qPressed = false, dPressed = false, aPressed = false, ePressed = false;
    while(!done) {

        // Event loop:
        SDL_Event e;
        while(windowManager.pollEvent(e)){

            if(e.type == SDL_QUIT) {
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

        // Definition of MVMatrix and ViewMatrix (camera)
        glm::mat4 MVMatrix;
        glm::mat4 ViewMatrix = Camera.getViewMatrix();

        /*********************************
         * RENDERING CODE
         *********************************/
         // Clean window and depth buffer
         glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
         
         // Draw with VAO
         glBindVertexArray(vao);

                /* Earth */
                // Choose program
                earthProgram.m_Program.use();

                // Set uniform objects
                glUniform1i(earthProgram.uTexture, 0);
                glUniform1i(earthProgram.uTexture2, 1);

                // Definition of Earth model matrix
                glm::mat4 MMatrixEarth;
                MMatrixEarth = glm::rotate(MMatrixEarth, windowManager.getTime(), glm::vec3(0, 1, 0)); // Rotation
                // Send matrix
                MVMatrix = ViewMatrix * MMatrixEarth;
                glUniformMatrix4fv(earthProgram.uMVMatrix, 1, GL_FALSE, glm::value_ptr(MVMatrix));
                glUniformMatrix4fv(earthProgram.uNormalMatrix, 1, GL_FALSE, glm::value_ptr(glm::transpose(glm::inverse(MVMatrix))));
                glUniformMatrix4fv(earthProgram.uMVPMatrix, 1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMatrix));
              
                // Draw with texture
                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, textureObjectE);
                glActiveTexture(GL_TEXTURE1);
                glBindTexture(GL_TEXTURE_2D, textureObjectC);
                    // Create sphere 1
                    glDrawArrays(GL_TRIANGLES, 0, sphere.getVertexCount());
                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, 0);
                glActiveTexture(GL_TEXTURE1);
                glBindTexture(GL_TEXTURE_2D, 0);
             
                /* Moons */
                // Choose program
                moonProgram.m_Program.use();
                for (int i=0; i<AxesRotation.size(); ++i){

                    // Set uniform objects
                    glUniform1i(moonProgram.uTexture, 0);

                    // Definition of Moon model matrix
                    glm::mat4 MMatrixMoon;
                    MMatrixMoon = glm::rotate(MMatrixMoon, windowManager.getTime(), AxesRotation.at(i)); // Rotation /glm::vec3(0, 1, 0)
                    MMatrixMoon = glm::translate(MMatrixMoon, Translations.at(i)); // Rotation * Translation
                    MMatrixMoon = glm::scale(MMatrixMoon, glm::vec3(0.2, 0.2, 0.2)); // Rotation * Translation * Scale
                    // Send matrix
                    MVMatrix = ViewMatrix * MMatrixMoon;
                    glUniformMatrix4fv(moonProgram.uMVMatrix, 1, GL_FALSE, glm::value_ptr(MVMatrix));
                    glUniformMatrix4fv(moonProgram.uNormalMatrix, 1, GL_FALSE, glm::value_ptr(glm::transpose(glm::inverse(MVMatrix))));
                    glUniformMatrix4fv(moonProgram.uMVPMatrix, 1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMatrix));
                    
                    // Draw with texture
                    glActiveTexture(GL_TEXTURE0);
                    glBindTexture(GL_TEXTURE_2D, textureObjectM);
                        // Create sphere 2
                        glDrawArrays(GL_TRIANGLES, 0, sphere.getVertexCount());
                    glBindTexture(GL_TEXTURE_2D, 0);

                }

         glBindVertexArray(0);

        // Update the display
        windowManager.swapBuffers();
    }

    // Free resources
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glDeleteTextures(1, &textureObjectE);
    glDeleteTextures(1, &textureObjectM);
    glDeleteTextures(1, &textureObjectC);

    return EXIT_SUCCESS;
}
