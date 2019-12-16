cmake_minimum_required(VERSION 2.8)

project(ImacraftSB)

add_definitions(-std=c++11)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/CMake)

find_package(SDL REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

# Pour gérer un bug a la fac, a supprimer sur machine perso:
set(OPENGL_LIBRARIES /usr/lib/x86_64-linux-gnu/libGL.so.1)

include_directories(${SDL_INCLUDE_DIR} ${OPENGL_INCLUDE_DIR} ${GLEW_INCLUDE_DIR} lib/glimac/include lib/third-party/include)

set(ALL_LIBRARIES glimac ${SDL_LIBRARY} ${OPENGL_LIBRARIES} ${GLEW_LIBRARY})

add_subdirectory(lib/glimac)

# Permet de metrte les executables dans le bin
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

file(GLOB HEADER_FILES include/*.hpp)
file(GLOB SRC_FILES src/*.cpp)
file(GLOB_RECURSE SHADER_FILES *.glsl)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

foreach(SRC_FILE ${SRC_FILES})
    get_filename_component(FILE ${SRC_FILE} NAME_WE)
    set(OUTPUT ${FILE})
    add_executable(${OUTPUT} ${SRC_FILE} ${HEADER_FILES} ${SHADER_FILES})
    target_link_libraries(${OUTPUT} ${ALL_LIBRARIES})
endforeach()

file(COPY src/shaders DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/bin)
