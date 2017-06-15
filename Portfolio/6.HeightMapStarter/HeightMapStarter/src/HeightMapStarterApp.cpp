#define GLM_SWIZZLE
#include "gl_core_4_4.h"
#include "LoadFromFile.h"
#include "HeightMapStarterApp.h"
#include "Gizmos.h"
#include "Input.h"
#include "Texture.h"
#include "LightObj.h"
#include "CameraObj.h"
#include "GLMeshObj.h"
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <iostream>
using glm::vec3;
using glm::vec4;
using glm::mat4;
using aie::Gizmos;



HeightMapStarterApp::HeightMapStarterApp() { }

HeightMapStarterApp::~HeightMapStarterApp() {

}

bool HeightMapStarterApp::startup() {
	m_camera = new Camera(glm::vec3(0, 3, 3), glm::vec3(0, 0, 1), glm::vec3(0, 1, 0),0,0,0);
	
	
	

	// glm::mat4 trnslation = glm::translate(glm::vec3(10, 10, 10);
	srand(time(NULL));
	setBackgroundColour(0.25f, 0.25f, 0.25f);

	// initialise gizmo primitive counts
	Gizmos::create(10000, 10000, 10000, 10000);

	// create simple camera transforms
	m_camera->m_viewMatrix = glm::lookAt(vec3(10), vec3(0), vec3(0, 1, 0));
	m_projectionMatrix = glm::perspective(glm::pi<float>() * 0.25f, 16.0f / 9.0f, 0.1f, 1000.0f);

	m_heightmap = new aie::Texture("./HeightMapStarter/images/heightmap0.bmp");
	m_tileTexture = new aie::Texture("./HeightMapStarter/images/tile.png");
	m_otherTexture = new aie::Texture("./HeightMapStarter/images/snow.png");
	m_heightmapMesh.MakePlane(m_heightmap);
	int y0;
	for (int x = 0; x < 10; x++)
	{
		int randn = rand() % 5 - 2;
		int xp = x - 5;
		m_cubeMesh[x].MakeCube(xp , randn, -xp);
		if (x == 5)y0 = randn;
	}
	glm::mat4 fbxMScale = {
		0.001f	,0		,0		,0,
		0		,0.001f	,0		,0,
		0		,0		,0.001f	,0,
		0		,y0 + 0.5f		,0		,1.0f

	};
	m_FBXM = new FBXModel("./models/characters/Demolition/demolition.fbx", fbxMScale, true);
	m_FBXM->m_modelM = fbxMScale;
	LoadShader();
	for (int i = 0; i < 1; i++)
	{
		float specC1 = (rand() % 128+64);
		float specC2 = (rand() % 100) / 100;
		float specC3 = (rand() % 100) / 100;
		int x = rand() % 40 ;
		int y = rand() % 5 + 2;
		int z = rand() % 20 ;

	m_light.push_back(MakeLight(glm::vec3(x, y, z), glm::vec3(1.0f, 1.0f, 1.0f),0.005f, glm::vec3(0.5f, 0.0f, 0.5f), specC1));

	}
	m_animationTime = 0;
	return true;
}

void HeightMapStarterApp::shutdown() {

	UnloadShader();
	for (int x = 0; x < 10; x++)
	{
		m_cubeMesh[x].Destroy();
	}
	m_heightmapMesh.Destroy();

	delete m_otherTexture;
	delete m_tileTexture;
	delete m_heightmap;

	Gizmos::destroy();
}

void HeightMapStarterApp::update(float deltaTime) {
	m_animationTime += deltaTime;
	// quit if we press escape
	aie::Input* input = aie::Input::getInstance();

	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();

	m_camera->m_viewMatrix = m_camera->UpdateCamera(deltaTime, input);
	float time = getTime();
		//move the light 
	input->getMouseXY(&m_camera->m_lastMouseXPos, &m_camera->m_lastMouseYPos);

	m_FBXM->update(m_animationTime);
}

void HeightMapStarterApp::draw() {

	glm::mat4 identity;

	// wipe the screen to the background colour
	clearScreen();

	// update perspective based on screen size
	m_projectionMatrix = glm::perspective(glm::pi<float>() * 0.25f, getWindowWidth() / (float)getWindowHeight(), 0.1f, 1000.0f);
	//m_FBXM->LoadShaders();
	float time = getTime();
	/*m_FBXM->m_modelM = m_camera->m_viewMatrix * m_FBXM->m_modelM;*/
	// setup the shader
	glUseProgram(m_shader);

	// dend the model, view and projection matrices
	glUniformMatrix4fv(glGetUniformLocation(m_shader, "projection"), 1, false, glm::value_ptr(m_projectionMatrix));
	glUniformMatrix4fv(glGetUniformLocation(m_shader, "view"), 1, false, glm::value_ptr(m_camera->m_viewMatrix));
	glUniformMatrix4fv(glGetUniformLocation(m_shader, "model"), 1, false, glm::value_ptr(identity));
	
	// send the textures
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_tileTexture->getHandle());
	glUniform1i(glGetUniformLocation(m_shader, "texture"), 0);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, m_otherTexture->getHandle());
	glUniform1i(glGetUniformLocation(m_shader, "texture2"), 1);

	std::vector<glm::vec3> lightPositions;
	std::vector<glm::vec3> lightColors;
	std::vector<float> lightASs;
	std::vector<glm::vec3> lightSpecCols;
	std::vector<float> lightSpecPows;

	for (int i = 0; i < m_light.size(); i++)
	{
		lightPositions.push_back(m_light[i]->m_Pos);
		lightColors.push_back(m_light[i]->m_Col);
		lightASs.push_back(m_light[i]->m_AmbientStrength);
		lightSpecCols.push_back(m_light[i]->m_specColor);
		lightSpecPows.push_back(m_light[i]->m_specPow);

	}

	glUniform1i(glGetUniformLocation(m_shader, "numLights"), m_light.size());
	glUniform3fv(glGetUniformLocation(m_shader, "lightPosition"), lightPositions.size(), &lightPositions[0].x);
	glUniform3fv(glGetUniformLocation(m_shader, "lightColor"), lightColors.size(), &lightColors[0].r);
	glUniform1fv(glGetUniformLocation(m_shader, "lightAmbientStrength"), lightASs.size(), &lightASs[0]);

	glUniform3fv(glGetUniformLocation(m_shader, "CameraPos"), 1, &m_camera->m_Pos[0]);
	glUniform3fv(glGetUniformLocation(m_shader, "SpecColor"), lightSpecCols.size(), &lightSpecCols[0].r);
	glUniform1fv(glGetUniformLocation(m_shader, "SpecPow"), lightSpecPows.size(), &lightSpecPows[0]);

	// Draw the heightmap
	m_heightmapMesh.Draw();

	for (int x = 0; x < 10; x++)
	{
		m_cubeMesh[x].Draw();

	}
	glUseProgram(0);
	m_FBXM->draw(m_projectionMatrix, m_camera->m_viewMatrix, m_FBXM->m_modelM,m_camera,m_light.size(),&m_light[0]->m_Pos, &m_light[0]->m_Col, &m_light[0]->m_AmbientStrength, &m_light[0]->m_specColor, &m_light[0]->m_specPow);




	DarwGizmosGrid();
	Gizmos::draw(m_projectionMatrix * m_camera->m_viewMatrix);
	Gizmos::clear(); // clear gizmos for next frame.
}

Light* HeightMapStarterApp::MakeLight(glm::vec3 pos, glm::vec3 Color, float ambientStrength, glm::vec3 specColor, float specPow)
{
	Light* temp = new Light(pos, Color, ambientStrength, specColor, specPow);

	return temp;
}


void HeightMapStarterApp::DarwGizmosGrid()
{
	for (int i = 0; i < m_light.size(); i++)
	{
	Gizmos::addSphere(m_light[i]->m_Pos, 0.1f, 8, 8, glm::vec4(1, 1, 1, 1));

	}

	// draw a simple grid with gizmos
	vec4 white(1);
	vec4 black(0, 0, 0, 1);

	for (int i = 0; i < 21; ++i) 
	{
		Gizmos::addLine(
			vec3(-10 + i, 0, 10),
			vec3(-10 + i, 0, -10),
			i == 10 ? white : black);

		Gizmos::addLine(
			vec3(10, 0, -10 + i),
			vec3(-10, 0, -10 + i),
			i == 10 ? white : black);
	}

	// add a transform so that we can see the axis
	Gizmos::addTransform(mat4(1));
}



void HeightMapStarterApp::LoadShader()
{
	std::string vsSource = StringFromFile("./HeightMapStarter/shaders/DiffuseLight.vert");
	const char *vsShaderSrcPtr = vsSource.c_str();

	std::string fsSource = StringFromFile("./HeightMapStarter/shaders/DiffuseLight.frag");
	const char *fsShaderSrcPtr = fsSource.c_str();
	// Step 1:
	// Load the vertex shader, provide it with the source code and compile it.
	GLuint vs = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vs, 1, &vsShaderSrcPtr, NULL);
	glCompileShader(vs);

	// Step 2:
	// Load the fragment shader, provide it with the source code and compile it.
	GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs, 1, &fsShaderSrcPtr, NULL);
	glCompileShader(fs);

	// Step 3:
	// Create the shader program
	m_shader = glCreateProgram();

	glAttachShader(m_shader, vs);
	glAttachShader(m_shader, fs);

	// Bind Attribute Locations
	glBindAttribLocation(m_shader, 0, "vPosition");
	glBindAttribLocation(m_shader, 1, "vColor");
	glBindAttribLocation(m_shader, 2, "vuv");
	glBindAttribLocation(m_shader, 3, "vNormal");
	glLinkProgram(m_shader);

	// Step 6:
	// destroy the vertex and fragment shader, we are finished with them
	// as they have been combined into the shaderProgram
	glDeleteShader(vs);
	glDeleteShader(fs);
}

void HeightMapStarterApp::UnloadShader()
{
	glDeleteProgram(m_shader);
}

void Vertex::SetupVertexAttribPointers()
{
	// enable vertex position element
	// notice when we loaded the shader, we described the "position" element to be location 0.
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(
		0,                  // attribute 0 (position)
		4,                  // size - how many floats make up the position (x, y, z, w)
		GL_FLOAT,           // type - our x,y,z, w are float values
		GL_FALSE,           // normalized? - not used
		sizeof(Vertex),     // stride - size of an entire vertex
		(void*)0            // offset - bytes from the beginning of the vertex
	);

	// enable vertex color element
	// notice when we loaded the shader, we described the "color" element to be location 1.
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(
		1,                  // attribute 1 (color)
		4,                  // size - how many floats make up the color (r, g, b, a)
		GL_FLOAT,           // type - our r,g,b,a are float values
		GL_FALSE,           // normalized? - not used
		sizeof(Vertex),     // stride - size of an entire vertex
		(void*)(sizeof(float) * 4)            // offset - bytes from the beginning of the vertex
	);

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(
		2,                  // attribute 1 (uv)
		2,                  // size - how many floats make up the uv coords
		GL_FLOAT,           // type - our u,v are float values
		GL_FALSE,           // normalized? - not used
		sizeof(Vertex),     // stride - size of an entire vertex
		(void*)(sizeof(float) * 8)            // offset - bytes from the beginning of the vertex
	);
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(
		3,                  // attribute 1 (uv)
		3,                  // size - how many floats make up the uv coords
		GL_FLOAT,           // type - our u,v are float values
		GL_FALSE,           // normalized? - not used
		sizeof(Vertex),     // stride - size of an entire vertex
		(void*)(sizeof(float) * 10)            // offset - bytes from the beginning of the vertex
	);
}




