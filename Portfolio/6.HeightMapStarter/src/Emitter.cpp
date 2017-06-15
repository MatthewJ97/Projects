#include "Emitter.h"
#include <gl_core_4_4.h>
#include <string>
#include <fstream>
#include <streambuf>
#include "CameraObj.h"
#include "Texture.h"
#include <math.h>
Particle::Particle()
{
}

Particle::Particle(glm::vec3 pos)
{
	position = pos;
}

Particle::~Particle()
{
}

void Particle::Update(float deltaTime)
{
	if (Alive) {
		aliveTime += deltaTime;
		position += velocity *deltaTime;
		color = glm::lerp(glm::vec4(1.0f, 1.0F, 1.0F, 1.0f), glm::vec4(1, 1, 1, 1), aliveTime);
	}
}






Emitter::Emitter(int maxPart = 100):m_maxParticles(maxPart)
{
	diffuseTexture = new aie::Texture("textures/bullet2.png");
	m_particles = new Particle[m_maxParticles];
	m_verts = new ParticleVertex[m_maxParticles * 4];
	m_indices = new unsigned int[m_maxParticles * 6];
	CreateBuffers();
	LoadShader();
}

Emitter::Emitter(int maxPart, glm::vec3 pos, float eRate, bool live, bool spawner, int numParticles)
{
	m_maxParticles = maxPart;
	position = pos; 
	emissionRate = eRate;
	isAlive = live;
	isSpawner = spawner; 
	m_numParticles = numParticles;
	diffuseTexture = new aie::Texture("textures/bullet2.png");
	m_particles = new Particle[m_maxParticles];
	m_verts = new ParticleVertex[m_maxParticles * 4];
	m_indices = new unsigned int[m_maxParticles * 6];
	CreateBuffers();
	LoadShader();
}

Emitter::~Emitter()
{
	delete[] diffuseTexture;
	UnloadShader();
	DestroyBuffers();
	delete[] m_indices;
	delete[] m_verts;
	delete[] m_particles;
}

void Emitter::Update(float deltaTime)
{
	m_animationTimer += deltaTime;
	if (m_numParticles > 0)isAlive = true;

#pragma region Spawning continously
	if (isSpawner) {
		isAlive = true;
		m_spawnTimer += deltaTime;
		while (m_spawnTimer > emissionRate && m_numParticles < m_maxParticles) {

			Particle &p = m_particles[m_numParticles];
			p.position.x = position.x;
			p.position.y = position.y;
			p.position.z = position.z;

			p.velocity.z = (rand() % 100)*0.01f + 4;
			p.velocity.y = (rand() % 100)*0.01f;
			p.velocity.x = (rand() % 100)*0.01f;
			p.Alive = true;
			p.aliveTime = 0;
			p.maxTimeAlive = 5.0f;

			m_numParticles += 1;
			m_spawnTimer -= emissionRate;
		}
	}
#pragma endregion
	if (isAlive) {

		for (int i = 0; i < m_numParticles; i++)
		{
			if (i < m_maxParticles) {
				m_particles[i].Alive = true;
				m_particles[i].Update(deltaTime);

				if (m_particles[i].aliveTime > m_particles[i].maxTimeAlive) {
					m_particles[i] = m_particles[m_numParticles - 1];
					Particle &p = m_particles[m_numParticles - 1];
					m_particles[m_numParticles - 1].position.x = position.x;
					m_particles[m_numParticles - 1].position.y = position.y;
					m_particles[m_numParticles - 1].position.z = position.z;
					p.velocity.z = (rand() % 100)*0.01f + 4;
					p.velocity.y = (rand() % 100)*0.01f;
					p.velocity.x = (rand() % 100)*0.01f;
					m_particles[m_numParticles - 1].aliveTime = 0;
					m_particles[m_numParticles - 1].maxTimeAlive = 1.0f;

					m_numParticles--;
					if (m_numParticles == 0) {
						isAlive = false;
					}
				}
			}
		}
	}
}

void Emitter::Render(Camera* camera)
{
	FillBuffers(camera);
	glUseProgram(m_shader);
	glm::mat4 scale{
		1, 0,		0,		0,
		0,	  1,		0,		0,
		0,	  0,		1,	0,
		0,	  0,		0,		1
	};
	glm::mat4 projecView = camera->m_projectionMatrix * camera->m_viewMatrix;

	glUniformMatrix4fv(glGetUniformLocation(m_shader, "projectionMatrix"), 1, false, &projecView[0][0]);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, diffuseTexture->getHandle());
	glUniform1i(glGetUniformLocation(m_shader, "diffuseTexture"), 0);
	glBindVertexArray(m_vao);
	glDrawElements(GL_TRIANGLES, m_numParticles * 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	glUseProgram(0);
}

void Emitter::SetNumParticles(int num)
{
	m_numParticles = num;
}

int Emitter::GetNumParticles()
{
	return m_numParticles;
}

void Emitter::CreateBuffers()
{
	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);

	glGenBuffers(1, &m_vbo);
	glGenBuffers(1, &m_ibo);

	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);

	ParticleVertex::SetUpVertexAttribPointers();

	glBindVertexArray(0);
}

void Emitter::DestroyBuffers()
{
	glDeleteBuffers(1, &m_ibo);
	glDeleteBuffers(1, &m_vbo);
	glDeleteVertexArrays(1, &m_vao);
}

void Emitter::FillBuffers(Camera* cam)
{
	for (int i = 0; i < m_numParticles; i++)
	{
		glm::vec3 forward = glm::normalize(cam->m_Pos - m_particles[i].position);
		glm::vec3 right = glm::cross(glm::vec3(0, 1, 0), forward);
		glm::vec3 up = glm::cross(forward, right);
		glm::mat4 billboard(glm::vec4(right, 0), glm::vec4(up, 0), glm::vec4(forward, 0), glm::vec4(0, 0, 0, 1));
		float uvXPos = 0.33f * ((int)m_animationTimer % 3)+1;
		m_verts[i * 4 + 0].position = m_particles[i].position - glm::vec3(billboard * glm::vec4(-0.5f,-0.5f, 0.0f,1.0f));
		m_verts[i * 4 + 1].position = m_particles[i].position - glm::vec3(billboard * glm::vec4(0.5f, -0.5f, 0.0f,1.0f));
		m_verts[i * 4 + 2].position = m_particles[i].position - glm::vec3(billboard * glm::vec4(0.5f,  0.5f, 0.0f,1.0f) );
		m_verts[i * 4 + 3].position = m_particles[i].position - glm::vec3(billboard * glm::vec4(-0.5f, 0.5f, 0.0f,1.0f));
		m_verts[i * 4 + 0].uv = glm::vec2(uvXPos - 0.33f,0);//{ 0.0f, 0.0f }
		m_verts[i * 4 + 1].uv = glm::vec2(uvXPos, 0);//{ 1.0f, 0.0f }
		m_verts[i * 4 + 2].uv = glm::vec2(uvXPos, 1.0f);//{ 1.0f, 1.0f }
		m_verts[i * 4 + 3].uv = glm::vec2(uvXPos - 0.33f, 1.0f);//{ 0.0f, 1.0f }
		m_verts[i * 4 + 0].color = m_particles[i].color;
		m_verts[i * 4 + 1].color = m_particles[i].color;
		m_verts[i * 4 + 2].color = m_particles[i].color;
		m_verts[i * 4 + 3].color = m_particles[i].color;
		m_verts[i * 4 + 0].aliveTime = m_particles[i].aliveTime;
		m_verts[i * 4 + 1].aliveTime = m_particles[i].aliveTime;
		m_verts[i * 4 + 2].aliveTime = m_particles[i].aliveTime;
		m_verts[i * 4 + 3].aliveTime = m_particles[i].aliveTime;
		m_indices[i * 6 + 0] = i * 4 + 0;
		m_indices[i * 6 + 1] = i * 4 + 1;
		m_indices[i * 6 + 2] = i * 4 + 2;

		m_indices[i * 6 + 3] = i * 4 + 0;
		m_indices[i * 6 + 4] = i * 4 + 2;
		m_indices[i * 6 + 5] = i * 4 + 3;
	}

	glBindVertexArray(m_vao);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);

	glBufferData(GL_ARRAY_BUFFER, sizeof(ParticleVertex) * m_numParticles * 4, m_verts, GL_DYNAMIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * m_numParticles * 6, m_indices, GL_DYNAMIC_DRAW);

	glBindVertexArray(0);
}

void Emitter::LoadShader()
{
	std::ifstream vsFileStream("shaders/particle.vert");
	std::string vShader((std::istreambuf_iterator<char>(vsFileStream)),	std::istreambuf_iterator<char>());
	std::ifstream fsFileStream("shaders/particle.frag");
	std::string fShader((std::istreambuf_iterator<char>(fsFileStream)), std::istreambuf_iterator<char>());

	unsigned int vs = glCreateShader(GL_VERTEX_SHADER);
	unsigned int fs = glCreateShader(GL_FRAGMENT_SHADER);


	const char* vSSource = vShader.c_str();
	const char* fSSource = fShader.c_str();


	glShaderSource(vs, 1, &vSSource ,0);
	glShaderSource(fs, 1, &fSSource ,0);


	glCompileShader(vs);
	glCompileShader(fs);

	m_shader = glCreateProgram();

	glAttachShader(m_shader, vs);
	glAttachShader(m_shader, fs);

	glBindAttribLocation(m_shader, 0, "position");
	glBindAttribLocation(m_shader, 1, "normal");
	glBindAttribLocation(m_shader, 2, "color");
	glBindAttribLocation(m_shader, 3, "uv");
	glBindAttribLocation(m_shader, 4, "aliveTime");

	glLinkProgram(m_shader);
	glDeleteShader(vs);
	glDeleteShader(fs);

}

void Emitter::UnloadShader()
{
	glDeleteProgram(m_shader);

}

void ParticleVertex::SetUpVertexAttribPointers()
{
	glEnableVertexAttribArray(0);//position
	glVertexAttribPointer(0,
						  3, 
						  GL_FLOAT,
						  GL_FALSE,
						  sizeof(ParticleVertex),
						  (void*)0
						 );
	glEnableVertexAttribArray(1);//normal
	glVertexAttribPointer(1,
						  4,
						  GL_FLOAT,
						  GL_FALSE,
						  sizeof(ParticleVertex),
						  (void*)(sizeof(float) * 3)
	);
	glEnableVertexAttribArray(2);//color
	glVertexAttribPointer(2,
						  4,
						  GL_FLOAT,
						  GL_FALSE,
						  sizeof(ParticleVertex),
						  (void*)(sizeof(float) * 7)
	);
	glEnableVertexAttribArray(3);//uv
	glVertexAttribPointer(3,
						  2,
						  GL_FLOAT,
						  GL_FALSE,
						  sizeof(ParticleVertex),
						  (void*)(sizeof(float) * 11)
	);
	glEnableVertexAttribArray(4);//uv
	glVertexAttribPointer(4,
						  1,
						  GL_FLOAT,
						  GL_FALSE,
						  sizeof(ParticleVertex),
						  (void*)(sizeof(float) * 13)
	);

}
