#pragma once

#include "Application.h"
#include "LightObj.h"
#include "CameraObj.h"
#include "GLMeshObj.h"
#include "Emitter.h"
#include <string>



enum effects {
	BLUR,
	DISTORT
}; 
class HeightMapStarterApp : public aie::Application {
public:

	HeightMapStarterApp();
	virtual ~HeightMapStarterApp();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();
	Light* MakeLight(glm::vec3 pos, glm::vec3 Color, float ambientStrength, glm::vec3 specColor, float specPow);
	glm::vec4 m_clearColour = glm::vec4(1,1,1,1);

	void DarwGizmosGrid();

	void LoadShader();
	void UnloadShader();

	void UnloadEffect();

	void LoadEffect(effects id);

	void LoadScreenShaders();

	void DrawEffect();

	void DrawBackEffect();

	void MakeScreenQuad();

	bool drawCol = false;
protected:

	// textures
	aie::Texture *m_heightmap;
	aie::Texture *m_tileTexture;
	aie::Texture *m_otherTexture;
	// handle to our shader program
	unsigned int m_shader;
	unsigned int m_postShaderProgram;
	
	// handle for our vao, vbo and ibo buffer objects
	unsigned int m_vao;
	unsigned int m_vbo;
	unsigned int m_ibo;
	unsigned int m_fbo;
	unsigned int m_fboTexture;
	unsigned int m_fboDepth;
	
	int numOfLights = 1;

	float m_animationTime;
	int DemoTime = 203;
	float MarkTime = 422.45f;

	bool effect = true;
	int eType = 1;
	GLMesh m_heightmapMesh;
	GLMesh m_cubeMesh[10];
	GLMesh m_pP;
	std::vector<FBXModel*> m_FBXM;
	std::vector<FBXFile*> m_FBXA;
	std::vector<std::string> ghoulAnimations;
	std::vector<Light*> m_light;
	std::vector<Emitter*> m_emitters;
	Camera *m_camera;






	// camera transforms


};

