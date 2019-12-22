#pragma once

#include <SDL2/SDL.h>

#include <imgui/imgui.h>
#include <imgui/imgui_impl_opengl3.h>
#include <imgui/imgui_impl_sdl.h>

#include <iostream>

#include "../include/Scene.hpp"

class Interface {

	public:
		Interface();
		~Interface();
		void initImgui(SDL_Window* window,SDL_GLContext* glContext) const;
		void beginFrame(SDL_Window* window) const;
		void drawInterface(Scene &scene);
		void endFrame(SDL_Window* window) const;

		inline float* getColor(){return &m_myCol;};
		inline void setColor(float color){m_myCol = color;};

	private:
		float m_myCol = 0.f;
		bool p_open;

};