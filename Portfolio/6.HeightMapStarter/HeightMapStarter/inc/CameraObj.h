#pragma once
#include <glm/glm.hpp>
#include <Input.h>
class Camera {

public:

	Camera(glm::vec3 pos, glm::vec3 front, glm::vec3 up, float yaw, float pitch, float roll);
	glm::mat4 UpdateCamera(float deltaTime, aie::Input* input);
	void UpdateRotation(float deltaTime, aie::Input* input);
	void CalculateView();
	glm::vec3 m_Pos;
	glm::vec3 m_Front;
	glm::vec3 m_Up;

	float m_Yaw;
	float m_Pitch;
	float m_Roll;

	// last mouse xPos and yPos recorded to calculate deltaMouseMovements
	int m_lastMouseXPos = 0;
	int m_lastMouseYPos = 0;
	glm::mat4	m_viewMatrix;



};

