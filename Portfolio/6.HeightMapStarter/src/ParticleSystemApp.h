#pragma once

#include "Application.h"
#include <glm/mat4x4.hpp>

class Emitter;
class Camera;

class ParticleSystemApp : public aie::Application {
public:

	ParticleSystemApp();
	virtual ~ParticleSystemApp();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

	void RenderGizmos();

protected:

	// camera transforms
	Emitter* m_emitter;
	Camera* m_camera;
	glm::mat4	m_viewMatrix;
	glm::mat4	m_projectionMatrix;
};