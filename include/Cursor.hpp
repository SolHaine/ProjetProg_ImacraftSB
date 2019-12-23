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
		glm::vec3 getPosition() const;
		void getCubeInScene(Scene &s);
		void drawSelection();
		void moveFront(const float t);
		void moveLeft(const float t);
		void moveUp(const float t);
		void freeBuffers();
	
};