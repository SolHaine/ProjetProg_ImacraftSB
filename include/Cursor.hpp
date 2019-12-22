#pragma once
#include <glimac/common.hpp>
#include <vector>
#include <iostream>

#include "Scene.hpp"

class Cursor {

	private:
		glm::vec3 c_position;
		GLuint c_vbo;
        GLuint c_ibo;
        GLuint c_vao;
        std::vector<glm::vec3> c_vertices;

	public:
		Cursor();
		~Cursor();
		glm::vec3 getPosition();
		void getCubeInScene(Scene s);
		void drawSelection();
		void updateSelection();
		void moveFront(float t);
		void moveLeft(float t);
		void moveUp(float t);
		void freeBuffers();
	
};