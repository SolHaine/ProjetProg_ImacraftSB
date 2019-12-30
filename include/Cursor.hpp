#pragma once
#include <glimac/common.hpp>
#include <vector>
#include <iostream>

#include "Scene.hpp"

class Cursor {

	private:
		glm::vec3 r_position;
		GLuint r_vbo;
        GLuint r_ibo;
        GLuint r_vao;
        std::vector<glm::vec3> r_vertices;
        bool r_onCube;

	public:
		Cursor();
		~Cursor();
		glm::vec3 getPosition() const;
		void getCubeInScene(Scene &s);
		void drawCursor();
		void moveFront(const float t);
		void moveLeft(const float t);
		void moveUp(const float t);
		void freeBuffersCursor();
		bool isOnCube();	
};