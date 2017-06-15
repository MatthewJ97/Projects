#pragma once

#include "Application.h"
#include "LightObj.h"
#include "CameraObj.h"
#include "GLMeshObj.h"
#include <string>



class HeightMapStarterApp : public aie::Application {
public:

	HeightMapStarterApp();
	virtual ~HeightMapStarterApp();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();
	Light* MakeLight(glm::vec3 pos, glm::vec3 Color, float ambientStrength, glm::vec3 specColor, float specPow);


	void DarwGizmosGrid();

	void LoadShader();
	void UnloadShader();


protected:

	// textures
	aie::Texture *m_heightmap;
	aie::Texture *m_tileTexture;
	aie::Texture *m_otherTexture;
	// handle to our shader program
	unsigned int m_shader;
	float m_animationTime;
	// handle for our vao, vbo and ibo buffer objects
	GLMesh m_heightmapMesh;
	GLMesh m_cubeMesh[10];
	FBXModel *m_FBXM;
	std::vector<Light*> m_light;
	Camera *m_camera;
	// camera transforms
	glm::mat4	m_projectionMatrix;


};

