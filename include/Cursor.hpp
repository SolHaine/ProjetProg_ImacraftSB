#pragma once
#include <glimac/common.hpp>
#include <vector>
#include <iostream>

#include "Scene.hpp"

class Cursor {

	private:
		GLuint r_vbo;
		GLuint r_vboScenePosition;
		GLuint r_vboColor;
        GLuint r_ibo;
        GLuint r_vao;

        std::vector<glm::vec3> r_vertices;
		glm::vec3 r_position;
		glm::vec3 r_color;

	public:
		Cursor(Scene &s);
		~Cursor();
		void drawCursor() const;
		void updateCursorScenePosition();
		void updateCursorColor();
		void changeColorOnSceneCube(const Scene &s);
		void moveFront(const float t, const Scene &s);
		void moveLeft(const float t, const Scene &s);
		void moveUp(const float t, const Scene &s);
		glm::vec3 getPosition() const;
};