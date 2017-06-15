#include "CameraObj.h"
#include <glm/ext.hpp>



Camera::Camera(glm::vec3 pos, glm::vec3 front, glm::vec3 up, float yaw, float pitch, float roll) : m_Pos(pos), m_Front(front), m_Up(up), m_Yaw(yaw), m_Pitch(pitch), m_Roll(roll) {};

glm::mat4 Camera::UpdateCamera(float deltaTime, aie::Input* input)
{
	UpdateRotation(deltaTime, input);
	const float cameraSpeed = 5.0f * deltaTime;

	if (input->isKeyDown(aie::INPUT_KEY_W))
		m_Pos += cameraSpeed * m_Front;

	if (input->isKeyDown(aie::INPUT_KEY_S))
		m_Pos -= cameraSpeed * m_Front;

	if (input->isKeyDown(aie::INPUT_KEY_A))
		m_Pos -= glm::normalize(glm::cross(m_Front, m_Up)) * cameraSpeed;

	if (input->isKeyDown(aie::INPUT_KEY_D))
		m_Pos += glm::normalize(glm::cross(m_Front, m_Up)) * cameraSpeed;
	  CalculateView();
	  return m_viewMatrix;
}

void Camera::UpdateRotation(float deltaTime, aie::Input* input)
{
	if (input->isMouseButtonDown(aie::INPUT_MOUSE_BUTTON_LEFT) || input->isMouseButtonDown(aie::INPUT_MOUSE_BUTTON_RIGHT))
	{
		const float mouseSensitivity = 10.0f * deltaTime;

		int mouseX, mouseY;
		float xOffset, yOffset;
		aie::Input *input = aie::Input::getInstance();
		input->getMouseXY(&mouseX, &mouseY);

		// get the change in the mouse movement.
		xOffset = (mouseX - m_lastMouseXPos) * mouseSensitivity;
		yOffset = (mouseY - m_lastMouseYPos) * mouseSensitivity;

		// ajdust yaw and pitch based on movement
		m_Yaw += xOffset;
		m_Pitch += yOffset;

		if (m_Pitch > 89.0f)  m_Pitch = 89.0f;
		if (m_Pitch < -89.0f) m_Pitch = -89.0f;

		glm::vec3 front;
		front.x = glm::cos(glm::radians(m_Yaw)) * glm::cos(glm::radians(m_Pitch));
		front.y = glm::sin(glm::radians(m_Pitch));
		front.z = glm::sin(glm::radians(m_Yaw)) * glm::cos(glm::radians(m_Pitch));
		m_Front = glm::normalize(front);
	}
}

void Camera::CalculateView()
{
	m_viewMatrix = glm::lookAt(m_Pos, m_Pos + m_Front, m_Up);

}



