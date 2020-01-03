#include "../include/Lights.hpp"

void Lights::switchDayNight() {
	l_directionnalLight = !l_directionnalLight;
}

void Lights::addPonctualLight(const glm::vec3 &position) {
	if(asAlreadyLight(position)==-1) {
		l_ponctualLightsPositions.push_back(position);
		l_nbPonctualLights++;
	}
}

void Lights::removePonctualLight(const glm::vec3 &position) {
	if(asAlreadyLight(position)!=-1) {
		l_ponctualLightsPositions.erase(l_ponctualLightsPositions.begin()+asAlreadyLight(position));
		l_nbPonctualLights--;
	}
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

int Lights::asAlreadyLight(const glm::vec3 &position) const {
	for(int i=0; i<l_nbPonctualLights; i++) {
		if(l_ponctualLightsPositions[i]==position) {
			return i;
		}
	}
	return -1;
}