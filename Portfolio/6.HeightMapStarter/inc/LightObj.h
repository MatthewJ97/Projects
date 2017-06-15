#pragma once
#include <glm/vec3.hpp>
	class Light {

	public:
		Light();
		~Light();
		Light(glm::vec3 pos, glm::vec3 Color, float ambientStrength, glm::vec3 specColor, float specPow);		
		
		glm::vec3 m_Pos;
		glm::vec3 m_Col;
		float m_AmbientStrength;

		glm::vec3 m_specColor;
		float m_specPow;
};

