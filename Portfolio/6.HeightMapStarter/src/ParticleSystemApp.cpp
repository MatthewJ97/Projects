#include "ParticleSystemApp.h"
#include "Gizmos.h"
#include "Input.h"
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include "Camera.h"
#include "Emitter.h"
using glm::vec3;
using glm::vec4;
using glm::mat4;
using aie::Gizmos;

ParticleSystemApp::ParticleSystemApp() {

}

ParticleSystemApp::~ParticleSystemApp() {

}

bool ParticleSystemApp::startup() {
	
	setBackgroundColour(0.25f, 0.25f, 0.25f);

	// initialise gizmo primitive counts
	Gizmos::create(10000, 10000, 10000, 10000);

	// create simple camera transforms
	m_viewMatrix = glm::lookAt(vec3(10), vec3(0), vec3(0, 1, 0));
	m_projectionMatrix = glm::perspective(glm::pi<float>() * 0.25f, 16.0f / 9.0f, 0.1f, 1000.0f);
	m_camera = new Camera();
	m_camera->SetPosition(glm::vec3(0, 8, 15));
	m_camera->SetProjection(glm::radians(45.0f),
		(float)getWindowWidth() / (float)getWindowHeight(),
							0.1f, 1000.0f);

	m_camera->Lookat(glm::vec3(0, 0, 0));
	m_emitter = new Emitter(1000);
	return true;
}

void ParticleSystemApp::shutdown() {
	delete m_camera;
	delete m_emitter;
	Gizmos::destroy();
}

void ParticleSystemApp::update(float deltaTime) {

	Gizmos::clear();
	aie::Input* input = aie::Input::getInstance();
	
	if (input->wasKeyPressed(aie::INPUT_KEY_SPACE) ){
		m_emitter->isAlive = true;
		m_emitter->SetNumParticles(m_emitter->GetNumParticles() + 10);
	}
	if (input->wasKeyPressed(aie::INPUT_KEY_X)) {
		m_emitter->isSpawner = !m_emitter->isSpawner;

	}
	// wipe the gizmos clean for this frame
	m_camera->Update(deltaTime);
	m_emitter->Update(deltaTime);
	// draw a simple grid with gizmos

	// quit if we press escape

	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();


}

void ParticleSystemApp::draw() {

	// wipe the screen to the background colour
	clearScreen();
	RenderGizmos();
	m_emitter->Render(m_camera);
	
}

void ParticleSystemApp::RenderGizmos(){
	vec4 white(1);
	vec4 black(0, 0, 0, 1);
	for (int i = 0; i < 21; ++i) {
		Gizmos::addLine(vec3(-10 + i, 0, 10),
						vec3(-10 + i, 0, -10),
						i == 10 ? white : black);
		Gizmos::addLine(vec3(10, 0, -10 + i),
						vec3(-10, 0, -10 + i),
						i == 10 ? white : black);
	}

	// add a transform so that we can see the axis
	Gizmos::addTransform(mat4(1));

	Gizmos::draw(m_camera->GetProjection() * m_camera->GetView());


}