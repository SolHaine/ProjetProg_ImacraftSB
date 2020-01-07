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
file(MAKE_DIRECTORY ${PROJECT_BINARY_DIR}/bin/savedScenes)

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
#find_package(SDL REQUIRED)
find_package(SDL2 REQUIRED)
find_package(GLEW REQUIRED)
find_package(Eigen3 REQUIRED)
find_package(Boost 1.56 REQUIRED COMPONENTS filesystem)

######################################################################################
###################################### Includes ######################################
######################################################################################

include_directories(
        ${SDL2_INCLUDE_DIRS}
        ${OPENGL_INCLUDE_DIR}
        ${GLEW_INCLUDE_DIRS}
        ${EIGEN3_INCLUDE_DIR}
        ${Boost_INCLUDE_DIRS}
        lib/glimac/include 
        lib/imgui/include 
        lib/glm/include
        )

add_subdirectory(lib/glimac)
add_subdirectory(lib/imgui)
set(ALL_LIBRARIES glimac imgui ${SDL2_LIBRARIES} ${OPENGL_LIBRARIES} ${GLEW_LIBRARY} Eigen3::Eigen Boost::filesystem)

######################################################################################
########################### Declaration of .exe  #####################################
######################################################################################

add_executable(${PROJECT_NAME} ${SRC_FILES} ${HEADER_FILES} ${SHADER_FILES})
target_link_libraries(${PROJECT_NAME} ${ALL_LIBRARIES})

######################################################################################
####################################### Copies  #####################################
######################################################################################

file(COPY src/savedScenes DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/bin)
file(COPY src/shaders DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY assets DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
