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
#include <imgui.h>
using glm::vec3;
using glm::vec4;
using glm::mat4;
using aie::Gizmos;



HeightMapStarterApp::HeightMapStarterApp() { }

HeightMapStarterApp::~HeightMapStarterApp() {

}

bool HeightMapStarterApp::startup() {

	//CAMERA AND BASIC SETUP
	//======================================================================================//
	m_camera = new Camera(glm::vec3(0, 3, 3), glm::vec3(0, 0, 1), glm::vec3(0, 1, 0),0,0,0);
	
	srand((unsigned int)time(NULL));
	setBackgroundColour(0.25f, 0.25f, 0.25f);

	// initialise gizmo primitive counts
	Gizmos::create(10000, 10000, 10000, 10000);
	// create simple camera transforms
	m_camera->m_viewMatrix = glm::lookAt(vec3(10), vec3(0), vec3(0, 1, 0));
	m_camera->m_projectionMatrix = glm::perspective(glm::pi<float>() * 0.25f, 16.0f / 9.0f, 0.1f, 1000.0f);
	//================================================//

	//LIGHT CREATION//
	//========================================================//
	for (int i = 0; i < numOfLights; i++)
	{
		float specC1 = (float)(rand() % 128 + 64);
		float specC2 = (float)(rand() % 100) / 100;
		float specC3 = (float)(rand() % 100) / 100;
		int x = rand() % 20;
		int y = rand() % 5 + 5;
		int z = rand() % 20;

		m_light.push_back(MakeLight(glm::vec3(x, y, z), glm::vec3(1.0f, 1.0f, 1.0f), 0.05f, glm::vec3(0.5f, 0.0f, 0.5f), specC1));
		std::cout << "Lights " << i + 1 << " :Loaded" << std::endl;
	}

	//===========================================================================//

	//TEXTURE LOADING//
	//============================//
	m_heightmap = new aie::Texture("./HeightMapStarter/images/heightmap0.bmp");
	std::cout << "heightMap :Loaded" << std::endl;
	m_tileTexture = new aie::Texture("./HeightMapStarter/images/tile.png");
	std::cout << "tileTexture :Loaded" << std::endl;
	m_otherTexture = new aie::Texture("./HeightMapStarter/images/snow.png");
	std::cout << "othertexture :Loaded" << std::endl;
	m_heightmapMesh.MakePlane(m_heightmap);
	std::cout << "HeightmapMesh :Loaded" << std::endl;
	//======================================================//


	//MODEL CREATION AND LOADING
	//======================================================//
	int x0, y0 , z0;
	int x1, y1 ,z1;
	glm::mat4 fbxMScale;
	float s = 0.001f;
	for (int x = 0; x < 10; x++)
	{
		int randn = rand() % 2 + 2;
		int xp = rand() % 10 - 5;
		int zp = rand() % 10 - 5;

		m_cubeMesh[x].MakeCube(xp, randn, -zp);
		if (x == 5) {
			y0 = randn; x0 = xp; z0 = -zp;
		}
		if (x == 4) {
			y1 = randn; x1 = xp; z1 = -zp;
		}
		std::cout << "Cube "<< x+1 << " :Loaded" << std::endl;
	}
	fbxMScale = {
		s	,0		,0		,0,
		0		,s	,0		,0,
		0		,0		,s	,0,
		x1		,y1 + 0.5f		,z1		,1.0f

	};
	m_FBXM.push_back(new FBXModel("./models/characters/Demolition/demolition.fbx", fbxMScale, true));
	m_FBXM[0]->SetAniStartEnd(200, 206);
	std::cout << "demolitonModel :Loaded" << std::endl;
	m_emitters.push_back(new Emitter(1000,
		glm::vec3(
			m_FBXM[0]->m_modelM[3][0],
			m_FBXM[0]->m_modelM[3][1] + 1.0f,
			m_FBXM[0]->m_modelM[3][2] + 0.8F),
		6.0f, false, false, 0));
	fbxMScale = {
		s	,0		,0		,0,
		0		,s	,0		,0,
		0		,0		,s	,0,
		x0		,y0 + 0.5f		,z0		,1.0f

	};
	m_FBXM.push_back(new FBXModel("./models/characters/Marksman/Marksman.fbx", fbxMScale, true));
	m_FBXM[1]->SetAniStartEnd(420, 432);
	std::cout << "MarksmanModel :Loaded" << std::endl;
	m_emitters.push_back(new Emitter(1000,
		glm::vec3(
			m_FBXM[1]->m_modelM[3][0],
			m_FBXM[1]->m_modelM[3][1] + 1.1f,
			m_FBXM[1]->m_modelM[3][2] + 0.8F),
		12.0f, false, false,0));
	s = 0.01f;
	fbxMScale = {
		s	,0		,0		,0,
		0		,s	,0		,0,
		0		,0		,s	,0,
		0		,2		,0		,1.0f

	};
	m_FBXM[1]->SetAniStartEnd(420, 432);
	m_FBXM.push_back(new FBXModel("./models/characters/MicroGhoul/MicroGhoul/micro_ghoul_animated.fbx", fbxMScale, true));
	std::cout << "Microghoul :Loaded" << std::endl;
	m_FBXM[2]->SetAniStartEnd(0, 1000);
	m_FBXM[2]->collision = new BoundingSphere(glm::vec3(0,2,0), 1);
	//=========================================================================//

	//ANIMATION LOADING
	//=========================================================================//
	ghoulAnimations.push_back("./models/characters/MicroGhoul/MicroGhoul/animations/mic_ghoul_attack.fbx");
	std::cout << "ani1 :Loaded" << std::endl;
	ghoulAnimations.push_back("./models/characters/MicroGhoul/MicroGhoul/animations/mic_ghoul_block.fbx");
	std::cout << "ani2 :Loaded" << std::endl;
	ghoulAnimations.push_back("./models/characters/MicroGhoul/MicroGhoul/animations/mic_ghoul_die.fbx");
	std::cout << "ani3 :Loaded" << std::endl;
	ghoulAnimations.push_back("./models/characters/MicroGhoul/MicroGhoul/animations/mic_ghoul_gethit_front.fbx");
	std::cout << "ani4 :Loaded" << std::endl;
	ghoulAnimations.push_back("./models/characters/MicroGhoul/MicroGhoul/animations/mic_ghoul_gethit_left.fbx");
	std::cout << "ani5 :Loaded" << std::endl;
	ghoulAnimations.push_back("./models/characters/MicroGhoul/MicroGhoul/animations/mic_ghoul_gethit_right.fbx");
	std::cout << "ani6 :Loaded" << std::endl;
	ghoulAnimations.push_back("./models/characters/MicroGhoul/MicroGhoul/animations/mic_ghoul_idle.fbx");
	std::cout << "ani7 :Loaded" << std::endl;
	ghoulAnimations.push_back("./models/characters/MicroGhoul/MicroGhoul/animations/mic_ghoul_laugh.fbx");
	std::cout << "ani8 :Loaded" << std::endl;
	ghoulAnimations.push_back("./models/characters/MicroGhoul/MicroGhoul/animations/mic_ghoul_panic.fbx");
	std::cout << "ani9 :Loaded" << std::endl;

	int numFiles = ghoulAnimations.size();
	for (int i = 0; i < numFiles; i++)
	{
	m_FBXA.push_back(new FBXFile());
	m_FBXA.at(i)->loadAnimationsOnly(ghoulAnimations[i].c_str(), FBXFile::UNITS_CENTIMETER);
	}
	//==============================================//
	//LOAD HIEGHTMAP SHADERS
	LoadShader();
	std::cout << "HeightMap.cpp Shaders :Loaded" << std::endl;

	//========================================================//
	
	MakeScreenQuad();
	LoadEffect(BLUR);
	std::cout << "Finished Startup "<< std::endl;

	return true;
}

void HeightMapStarterApp::shutdown() {
	UnloadEffect();
	UnloadShader();
	for (int x = 0; x < 10; x++)
	{
		m_cubeMesh[x].Destroy();
	}
	m_heightmapMesh.Destroy();
	for (unsigned int x = 0; x < m_FBXM.size(); x++)
	{
		m_FBXM[x]->UnloadModel();
	}
	delete m_otherTexture;
	delete m_tileTexture;
	delete m_heightmap;

	Gizmos::destroy();
}

void HeightMapStarterApp::update(float deltaTime) {
	// quit if we press escape
	m_light[0]->m_Pos.x += sin(getTime());
	m_light[0]->m_Pos.z += cos(getTime());
	for (unsigned int i = 0; i < m_emitters.size(); i++)
	{
	m_emitters[i]->Update(deltaTime);
	}
	aie::Input* input = aie::Input::getInstance();

	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
	if(!ImGui::IsMouseHoveringAnyWindow())	m_camera->m_viewMatrix = m_camera->UpdateCamera(deltaTime, input);
	
		//move the light 
	input->getMouseXY(&m_camera->m_lastMouseXPos, &m_camera->m_lastMouseYPos);
	for (unsigned int i = 0; i < m_FBXM.size() - 1; i++)
	{
	m_FBXM[i]->update(deltaTime);

	}
	if ((m_FBXM[0]->m_animationTime >= DemoTime -0.5f && m_FBXM[0]->m_animationTime <= DemoTime + 0.5f)|| (m_FBXM[0]->m_animationTime >= DemoTime + 0.7f && m_FBXM[0]->m_animationTime <= DemoTime + 1.5f)) {
		m_emitters[0]->SetNumParticles(5);
	}
	if ((m_FBXM[1]->m_animationTime >= MarkTime - 0.5f && m_FBXM[1]->m_animationTime <= MarkTime + 0.5f)) {
		m_emitters[1]->SetNumParticles(2);
	}
	m_FBXM[2]->update(deltaTime, m_FBXA[m_FBXM[2]->m_animationID]);
	if (ImGui::Button("Turn On/Off Post Processing")) {
		effect = !effect;

	}
	if (effect) {
		if (ImGui::Button("Blur Effect")) {
			eType = 1;
		}
		if (ImGui::Button("Distort Effect")) {
			eType = 2;
		}
		if (ImGui::Button("No Effect")) {
			eType = 0;
		}
		if (ImGui::Button("EXPERIMENTAL ")) {
			eType = 3;
		}
	}
	if (ImGui::Button("Turn ON Frustum Gizmo")) {
		drawCol = !drawCol;
	}
	const char* t = "Frstum cull = false";
	const char* f = "Frstum cull = true";
	m_camera->getFrustumPlanes();
	for (int i = 0; i < 6; i++) 
	{
		float d = glm::dot(vec3(m_camera->frustrumPlanes[i]), m_FBXM[2]->collision->center) + m_camera->frustrumPlanes[i].w;
		if (d < -m_FBXM[2]->collision->radius) {
			
			
			m_FBXM[2]->collision->dontDraw = true;
			break;
		} 
		else if (d < m_FBXM[2]->collision->radius) {
			
			m_FBXM[2]->collision->dontDraw = false;

		}
		else { 
			
			m_FBXM[2]->collision->dontDraw = false;
		}
	}
	if (m_FBXM[2]->collision->dontDraw) {
		ImGui::BulletText(t);
		if (drawCol)Gizmos::addSphere(m_FBXM[2]->collision->center, m_FBXM[2]->collision->radius, 10, 10, glm::vec4(1, 0, 0, 1));
	}
	else if (!m_FBXM[2]->collision->dontDraw) {
		ImGui::BulletText(f);
		if (drawCol)Gizmos::addSphere(m_FBXM[2]->collision->center, m_FBXM[2]->collision->radius, 10, 10, glm::vec4(0, 1, 0, 1));

	}

}

void HeightMapStarterApp::draw() {

	glm::mat4 identity;

	// wipe the screen to the background colour
	clearScreen();
// update perspective based on screen size
	m_camera->m_projectionMatrix = glm::perspective(glm::pi<float>() * 0.25f, getWindowWidth() / (float)getWindowHeight(), 0.1f, 1000.0f);
	float time = getTime();
	
	/*m_FBXM->m_modelM = m_camera->m_viewMatrix * m_FBXM->m_modelM;*/
	// setup the shader
	if (effect) {
		DrawEffect();
		glUniform1i(glGetUniformLocation(m_postShaderProgram, "effect"), eType);

	}
	glUseProgram(m_shader);

	// dend the model, view and projection matrices
	glUniformMatrix4fv(glGetUniformLocation(m_shader, "projection"), 1, false, glm::value_ptr(m_camera->m_projectionMatrix));
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

	for (unsigned int i = 0; i < m_light.size(); i++)
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
	for (unsigned int i = 0; i < m_FBXM.size(); i++)
	{
		if(m_FBXM[i]->collision == nullptr)	
			m_FBXM[i]->draw(m_camera, m_light);
		else if(!m_FBXM[i]->collision->dontDraw)m_FBXM[i]->draw(m_camera, m_light);
	}

	for (unsigned int i = 0; i < m_emitters.size(); i++)
	{
		m_emitters[i]->Render(m_camera);
	}
	DarwGizmosGrid();

	Gizmos::draw(m_camera->m_projectionMatrix * m_camera->m_viewMatrix);
	if (effect) {
		DrawBackEffect();
	}
	Gizmos::clear(); // clear gizmos for next frame.
}

Light* HeightMapStarterApp::MakeLight(glm::vec3 pos, glm::vec3 Color, float ambientStrength, glm::vec3 specColor, float specPow)
{
	Light* temp = new Light(pos, Color, ambientStrength, specColor, specPow);

	return temp;
}


void HeightMapStarterApp::DarwGizmosGrid()
{
	for (unsigned int i = 0; i < m_light.size(); i++)
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
void HeightMapStarterApp::UnloadEffect()
{
	glDeleteProgram(m_postShaderProgram);
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

void HeightMapStarterApp::LoadEffect(effects id) {
	// setup framebuffer 
	glGenFramebuffers(1, &m_fbo);
	glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
	glGenTextures(1, &m_fboTexture);
	glBindTexture(GL_TEXTURE_2D, m_fboTexture);
	glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGBA8, getWindowWidth(), getWindowHeight());
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, m_fboTexture, 0);
	glGenRenderbuffers(1, &m_fboDepth);
	glBindRenderbuffer(GL_RENDERBUFFER, m_fboDepth);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, getWindowWidth(), getWindowHeight());
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_fboDepth);
	GLenum drawBuffers[] = { GL_COLOR_ATTACHMENT0 };
	glDrawBuffers(1, drawBuffers);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	LoadScreenShaders();

}


void HeightMapStarterApp::LoadScreenShaders() {
	std::string vsSource = StringFromFile("./shaders/postprocessing.vert");
	const char *vsShaderSrcPtr = vsSource.c_str();

	std::string fsSource = StringFromFile("./shaders/postprocessing.frag");
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
	m_postShaderProgram = glCreateProgram();

	glAttachShader(m_postShaderProgram, vs);
	glAttachShader(m_postShaderProgram, fs);

	// Bind Attribute Locations
	glBindAttribLocation(m_postShaderProgram, 0, "position");
	glBindAttribLocation(m_postShaderProgram, 1, "texCoord");
	glLinkProgram(m_postShaderProgram);

	// Step 6:
	// destroy the vertex and fragment shader, we are finished with them
	// as they have been combined into the shaderProgram
	glDeleteShader(vs);
	glDeleteShader(fs);
}

void HeightMapStarterApp::DrawEffect()
{
		// bind our target
		glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
		glViewport(0, 0, 1280, 720);
		// clear the target 
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		
}
void HeightMapStarterApp::DrawBackEffect() {
	// bind the back-buffer 
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glViewport(0, 0, 1280, 720);
	glUseProgram(m_postShaderProgram);

	// just clear the back-buffer depth as // each pixel will be filled 
	//glClear(GL_DEPTH_BUFFER_BIT);
	// draw our full-screen quad 
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_fboTexture);
	int loc = glGetUniformLocation(m_postShaderProgram, "target");
	glUniform1i(loc, 0);
	glBindVertexArray(m_vao);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, 0);

	glBindVertexArray(0);
}

void HeightMapStarterApp::MakeScreenQuad() {
	glm::vec2 halfTexel = 1.0f / glm::vec2(1280, 720) * 0.5f;
	float vertexData[] = {
		-1,		  1,	 0,		 1,		 halfTexel.x,		 1 - halfTexel.y,		//top lft		//0
	   	 1,		  1,	 0,		 1,		 1 - halfTexel.x ,	 1 - halfTexel.y,		//top rght		//1
		 1,		 -1,	 0,		 1,		 1 - halfTexel.x,	 halfTexel.y,		//btm rght		//2
		-1,		 -1,	 0,		 1,		 halfTexel.x,		 halfTexel.y		//btm lft		//3
	};
	std::cout << halfTexel.x << " ," << halfTexel.y << std::endl;

	unsigned char indices[] = {
		0,3,1,
		1,3,2
	};
	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);

	glGenBuffers(1, &m_vbo);
	glGenBuffers(1, &m_ibo);

	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 6, 0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 6,(void*)(sizeof(float) * 4));

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}