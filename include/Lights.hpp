#pragma once
#include <glimac/common.hpp>
#include <vector>
#include <iostream>

class Lights {
	private:
        bool l_directionnalLight;
        int l_nbPonctualLights;
        std::vector<glm::vec3> l_ponctualLightsPositions;

    public:
        Lights() : l_directionnalLight(true), l_nbPonctualLights(0) {};
        ~Lights() = default;      
		void switchDayNight();
		void addPonctualLight(glm::vec3 position);
		std::vector<glm::vec3> getPonctualLightsPositions() const;
		int getNbPonctualLights() const;
		bool isDay() const;
};