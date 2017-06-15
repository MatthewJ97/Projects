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
class BoundingSphere {
public:
	BoundingSphere();
	BoundingSphere(glm::vec3 centerp, float radi);

	~BoundingSphere();
	void fit(const std::vector<glm::vec3>& points);
	
	bool dontDraw;
	glm::vec3 center;
	float radius;
};
class GLMesh
{
public:

	void MakeCube(int x, int y, int z);
	void MakePlane(aie::Texture *heighmap);

	void Destroy();

	void Draw();
	void MakeScreenQuad();
	void DrawEffect(GLMesh quad);

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

	virtual void draw(Camera* camera, std::vector<Light*> lights);
	virtual void update(float deltaTime);
	virtual void update(float deltaTime, FBXFile* ani);

	void CreateFBXOpenGLBuffers(FBXFile *file);
	void CreateFBXOpenGLBuffersWithAni(FBXFile * file);
	void CleanupFBXOpenGLBuffers(FBXFile *file);
	void LoadShaders();
	void UnloadShaders();
	void SetAniStart(float start);
	float GetAniStart() { return animationStart; }
	float* GetAniStartP() { return &animationStart; }

	void SetAniEnd(float end);
	float GetAniEnd() { return animationEnd; }
	float* GetAniEndP() { return &animationEnd; }

	void SetAniStartEnd(float start, float end);
	unsigned int m_shader;
	FBXFile *m_FbxModel;
	glm::mat4 m_modelM;
	float m_animationTime = 0;
	int m_animationID = 0;
	BoundingSphere* collision = nullptr;
protected:

	// camera transforms
	float animationStart = 0;
	float animationEnd = 0;

};

