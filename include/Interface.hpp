#pragma once

#include <SDL2/SDL.h>

#include <imgui/imgui.h>
#include <imgui/imgui_impl_opengl3.h>
#include <imgui/imgui_impl_sdl.h>

#include <iostream>

#include "../include/Scene.hpp"
#include "../include/Cursor.hpp"

class Interface {

	public:
		Interface();
		~Interface();
		void initImgui(SDL_Window* window, SDL_GLContext* glContext) const;
		void beginFrame(SDL_Window* window) const;
		void drawInterface(Scene &scene, const Cursor &cursor);
		void endFrame(SDL_Window* window) const;

	private:
		

};