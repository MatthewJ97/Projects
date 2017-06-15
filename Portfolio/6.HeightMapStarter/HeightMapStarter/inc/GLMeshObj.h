#pragma once
#include <glm/glm.hpp>
#include "Application.h"
#include <glm/mat4x4.hpp>
#include "FBXFile.h"
#include <gl_core_4_4.h>
#include "LightObj.h"
#include "CameraObj.h"

namespace aie
{
	class Texture;
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

class GLMesh
{
public:

	void MakeCube(int x, int y, int z);
	void MakePlane(aie::Texture *heighmap);

	void Destroy();

	void Draw();

	unsigned int m_vao;
	unsigned int m_vbo;
	unsigned int m_ibo;
	unsigned int m_numIndices;
};

class FBXModel {
public:

	FBXModel();
	FBXModel(const char * fileName, glm::mat4 scale, bool ani = false);
	virtual ~FBXModel();

	void UnloadModel();

	virtual void draw(glm::mat4 projection, glm::mat4 view, glm::mat4 model, Camera* camera, int lightSize, glm::vec3* pos, glm::vec3* col, float* lightASs, glm::vec3 * lightSC, float* lightSP);
	virtual void update(float deltaTime);
	void CreateFBXOpenGLBuffers(FBXFile *file);
	void CreateFBXOpenGLBuffersWithAni(FBXFile * file);
	void CleanupFBXOpenGLBuffers(FBXFile *file);
	void LoadShaders();
	void UnloadShaders();


	unsigned int m_shader;
	FBXFile *m_FbxModel;
	glm::mat4 m_modelM;


protected:

	// camera transforms
	glm::mat4	m_viewMatrix;
	glm::mat4	m_projectionMatrix;
};

