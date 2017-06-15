#pragma once
#include <glm/glm.hpp>
#include <Input.h>
class Camera {

public:

	Camera(glm::vec3 pos, glm::vec3 front, glm::vec3 up, float yaw, float pitch, float roll);
	glm::mat4 UpdateCamera(float deltaTime, aie::Input* input);
	void UpdateRotation(float deltaTime, aie::Input* input);
	void CalculateView();
	void getFrustumPlanes() {
		m_globalSpace = m_projectionMatrix * m_viewMatrix;
		// right side 
		frustrumPlanes[0] = glm::vec4( m_globalSpace[0][3] - m_globalSpace[0][0], m_globalSpace[1][3] - m_globalSpace[1][0], m_globalSpace[2][3] - m_globalSpace[2][0], m_globalSpace[3][3] - m_globalSpace[3][0]);
		// left side 
		frustrumPlanes[1] = glm::vec4( m_globalSpace[0][3] + m_globalSpace[0][0], m_globalSpace[1][3] + m_globalSpace[1][0], m_globalSpace[2][3] + m_globalSpace[2][0], m_globalSpace[3][3] + m_globalSpace[3][0]); 
		// top 
		frustrumPlanes[2] = glm::vec4( m_globalSpace[0][3] - m_globalSpace[0][1], m_globalSpace[1][3] - m_globalSpace[1][1], m_globalSpace[2][3] - m_globalSpace[2][1], m_globalSpace[3][3] - m_globalSpace[3][1]);
		// bottom 
		frustrumPlanes[3] = glm::vec4( m_globalSpace[0][3] + m_globalSpace[0][1], m_globalSpace[1][3] + m_globalSpace[1][1], m_globalSpace[2][3] + m_globalSpace[2][1], m_globalSpace[3][3] + m_globalSpace[3][1]);
		// far
		frustrumPlanes[4] = glm::vec4( m_globalSpace[0][3] - m_globalSpace[0][2], m_globalSpace[1][3] - m_globalSpace[1][2], m_globalSpace[2][3] - m_globalSpace[2][2], m_globalSpace[3][3] - m_globalSpace[3][2]);
		// near 
		frustrumPlanes[5] = glm::vec4( m_globalSpace[0][3] + m_globalSpace[0][2], m_globalSpace[1][3] + m_globalSpace[1][2], m_globalSpace[2][3] + m_globalSpace[2][2], m_globalSpace[3][3] + m_globalSpace[3][2]);
		// plane normalisation, based on length of normal
		for (int i = 0; i < 6; i++) { 
			float d = glm::length(glm::vec3(frustrumPlanes[i]));
			frustrumPlanes[i] /= d; }
	}
	glm::vec3 m_Pos;
	glm::vec3 m_Front;
	glm::vec3 m_Up;
	glm::vec4 frustrumPlanes[6];
	float m_Yaw;
	float m_Pitch;
	float m_Roll;

	// last mouse xPos and yPos recorded to calculate deltaMouseMovements
	int m_lastMouseXPos = 0;
	int m_lastMouseYPos = 0;
	glm::mat4	m_viewMatrix;
	glm::mat4	m_projectionMatrix;
	glm::mat4	m_globalSpace;



};

