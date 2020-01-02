#include "../include/Lights.hpp"

void Lights::switchDayNight() {
	l_directionnalLight = !l_directionnalLight;
}

void Lights::addPonctualLight(glm::vec3 position) {
	l_ponctualLightsPositions.push_back(position);
	l_nbPonctualLights++;
}

std::vector<glm::vec3> Lights::getPonctualLightsPositions() const {
	return l_ponctualLightsPositions;
}

int Lights::getNbPonctualLights() const {
	return l_nbPonctualLights;
}

bool Lights::isDay() const {
	return l_directionnalLight;
}