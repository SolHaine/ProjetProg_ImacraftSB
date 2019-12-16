#include "common.hpp"
#include <glm/gtx/transform.hpp>


class FreeflyCamera {
	private :
	glm::vec3 m_Position;
	float m_fPhi;
	float m_fTheta;

	glm::vec3 m_FrontVector;
	glm::vec3 m_LeftVector;
	glm::vec3 m_UpVector;

	public :
	void computeDirectionVectors();

	FreeflyCamera() : m_Position(glm::vec3(0, 0, 5)), m_fPhi(glm::pi<float>()), m_fTheta(0.0) {computeDirectionVectors();};

	void moveLeft(float t);
	void moveFront(float t);
	void rotateLeft(float degrees);
	void rotateUp(float degrees);

	glm::mat4 getViewMatrix() const;

};