######################################################################################
################################# Presets CMakeList ##################################
######################################################################################

cmake_minimum_required(VERSION 3.0)
add_definitions(-std=c++11)

######################################################################################
############################### Configuration project  ###############################
######################################################################################

project(ImacraftSB)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/CMake)

######################################################################################
################################## Project files  ####################################
######################################################################################

file(GLOB_RECURSE SRC_FILES src/*.cpp)
file(GLOB_RECURSE HEADER_FILES include/*.hpp)
file(GLOB_RECURSE SHADER_FILES shaders/*.glsl)

######################################################################################
################################## Dependencies  #####################################
######################################################################################

find_package(OpenGL REQUIRED)
find_package(SDL REQUIRED)
find_package(GLEW REQUIRED)

######################################################################################
###################################### Includes ######################################
######################################################################################

#### --------------- Necessary in order to run on Apple's laptop ---------------- ####
if (APPLE)
    include_directories(/usr/local/include)
    set(GLEW_LIBRARY /usr/local/lib/libGLEW.dylib)
endif (APPLE)

include_directories(
        ${SDL_INCLUDE_DIRS}
        ${OPENGL_INCLUDE_DIR}
        ${GLEW_INCLUDE_DIRS}
        lib/glimac/include 
        lib/glm/include
        )

set(ALL_LIBRARIES glimac ${SDL_LIBRARY} ${OPENGL_LIBRARIES} ${GLEW_LIBRARY})
add_subdirectory(lib/glimac)

######################################################################################
########################### Declaration of .exe  #####################################
######################################################################################

add_executable(${PROJECT_NAME} ${SRC_FILES} ${HEADER_FILES} ${SHADER_FILES})
target_link_libraries(${PROJECT_NAME} ${ALL_LIBRARIES})

######################################################################################
####################################### Copies  #####################################
######################################################################################

file(COPY src/shaders DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/bin)
