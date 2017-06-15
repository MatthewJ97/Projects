#pragma once
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm\ext.hpp>
class Camera;
namespace aie {
	class Texture;
}
class Particle {

public:
	Particle();
	Particle(glm::vec3 pos);
	virtual ~Particle();

	virtual void Update(float deltaTime);

	glm::vec3 position;
	glm::vec3 velocity= glm::vec3(rand() % 40 - 20, rand() % 40 - 20, rand() % 40 - 20);
	glm::vec4 color;

	float aliveTime = 0.0f;
	float maxTimeAlive = 1.0f;
	bool Alive = false;

protected:

private:

};

struct ParticleVertex {
	glm::vec3 position;
	glm::vec4 normal;
	glm::vec4 color;
	glm::vec2 uv;
	float aliveTime;
	static void SetUpVertexAttribPointers();
};

class Emitter {

public :

	Emitter(int maxPart);
	Emitter(int maxPart, glm::vec3 pos, float eRate, bool live = false, bool spawner = false , int numParticles = 1);
	virtual ~Emitter();

	virtual void Update(float deltaTime);
	virtual void Render(Camera* camera);
	void SetNumParticles(int num);
	int GetNumParticles();
public:
	glm::vec3 position;
	float emissionRate= 0.5f;
	bool isAlive = false;
	bool isSpawner = true;
protected:
	void CreateBuffers();
	void DestroyBuffers();
	void FillBuffers(Camera* cam);

	void LoadShader();
	void UnloadShader();
protected:
	float m_spawnTimer = 0;
	float m_animationTimer = 0;
	int m_maxParticles;
	int m_numParticles = 1;
	Particle* m_particles = nullptr;
	ParticleVertex * m_verts;
	unsigned int* m_indices;
	unsigned int m_shader = 0;
	//opengl particle buffer
	unsigned int m_vao;
	unsigned int m_vbo;
	unsigned int m_ibo;
	aie::Texture* diffuseTexture;
private:

};