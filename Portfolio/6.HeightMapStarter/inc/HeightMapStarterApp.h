#pragma once

#include "Application.h"
#include <glm/mat4x4.hpp>
#include <glm/mat3x3.hpp>
#include <glm/vec4.hpp>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>

#include <string>

namespace aie
{
	class Texture;
};

class GLMesh
{
public:

	void MakeCube();
	void MakePlane(aie::Texture *heighmap);

	void Destroy();

	void Draw();

	unsigned int m_vao;
	unsigned int m_vbo;
	unsigned int m_ibo;
	unsigned int m_numIndices;
};

class Vertex
{
public:
	glm::vec4 pos;
	glm::vec4 col;
	glm::vec2 uv;
	glm::vec3 normal;

	static void SetupVertexAttribPointers();
};

class HeightMapStarterApp : public aie::Application {
public:

	HeightMapStarterApp();
	virtual ~HeightMapStarterApp();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

	void UpdateCamera(float deltaTime);

	void DarwGizmosGrid();

	void LoadShader();
	void UnloadShader();

	std::string StringFromFile(const char *filename);


protected:

	// textures
	aie::Texture *m_heightmap;
	aie::Texture *m_tileTexture;
	aie::Texture *m_otherTexture;
	// handle to our shader program
	unsigned int m_shader;

	// handle for our vao, vbo and ibo buffer objects
	GLMesh m_heightmapMesh;
	GLMesh m_cubeMesh;

	// camera transforms
	glm::mat4	m_viewMatrix;
	glm::mat4	m_projectionMatrix;

	glm::vec3 m_cameraPos = glm::vec3(0, 3, 3);
	glm::vec3 m_cameraFront = glm::vec3(0, 0, 1);
	glm::vec3 m_cameraUp = glm::vec3(0, 1, 0);

	float m_cameraYaw = 0.0f;
	float m_cameraPitch = 0.0f;
	float m_cameraRoll = 0.0f;

	// last mouse xPos and yPos recorded to calculate deltaMouseMovements
	int m_lastMouseXPos = 0.0f;
	int m_lastMouseYPos = 0.0f;

	glm::vec3 m_lightPos = glm::vec3(0, 5, 0);
	glm::vec3 m_lightCol = glm::vec3(1, 1, 1);
	float m_lightAmbientStrength = 0.05f;

	glm::vec3 m_specColor = glm::vec3(0, 0, 1);
	float m_specPow = 32.0f;

};

