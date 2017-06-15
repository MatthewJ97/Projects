#include "LightObj.h"



Light::Light() {};

Light::~Light() {};

Light::Light(glm::vec3 pos, glm::vec3 Color, float ambientStrength, glm::vec3 specColor, float specPow) : m_Pos(pos), m_Col(Color), m_AmbientStrength(ambientStrength), m_specColor(specColor), m_specPow(specPow) {}

