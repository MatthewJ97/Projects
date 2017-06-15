#define GLM_SWIZZLE
#include "GLMeshObj.h"
#include "gl_core_4_4.h"
#include "Texture.h"
#include <vector>
#include "LoadFromFile.h"

FBXModel::FBXModel() {

}
FBXModel::FBXModel(const char * fileName, glm::mat4 scale, bool ani) {
	m_FbxModel = new FBXFile();
	m_modelM = scale;
	m_FbxModel->load(fileName, FBXFile::UNITS_CENTIMETER);
	CreateFBXOpenGLBuffers(m_FbxModel);
	LoadShaders();
}

FBXModel::~FBXModel() {

}

void FBXModel::UnloadModel() {

	UnloadShaders();
	CleanupFBXOpenGLBuffers(m_FbxModel);
	m_FbxModel->unload();
	delete m_FbxModel;
}


void FBXModel::draw(glm::mat4 projection, glm::mat4 view, glm::mat4 model, Camera* camera, int lightSize, glm::vec3* pos, glm::vec3* col, float* lightASs, glm::vec3 * lightSC, float* lightSP ) {
	
	glUseProgram(m_shader);


	unsigned int mpLoc = glGetUniformLocation(m_shader, "projection");
	glUniformMatrix4fv(mpLoc, 1, GL_FALSE, &projection[0][0]);
	unsigned int mvLoc = glGetUniformLocation(m_shader, "view");
	glUniformMatrix4fv(mvLoc, 1, GL_FALSE, &view[0][0]);
	unsigned int mmLoc = glGetUniformLocation(m_shader, "model");
	glUniformMatrix4fv(mmLoc, 1, GL_FALSE, &model[0][0]);

	glUniform1i(glGetUniformLocation(m_shader, "numLights"), lightSize);
	glUniform3fv(glGetUniformLocation(m_shader, "lightPosition"), lightSize, &pos->x);
	glUniform3fv(glGetUniformLocation(m_shader, "lightColor"), lightSize, &col->r);
	glUniform1fv(glGetUniformLocation(m_shader, "lightAmbientStrength"), lightSize, lightASs);

	glUniform3fv(glGetUniformLocation(m_shader, "CameraPos"), 1, &camera->m_Pos[0]);
	glUniform3fv(glGetUniformLocation(m_shader, "SpecColor"), lightSize, &lightSC[0].r);
	glUniform1fv(glGetUniformLocation(m_shader, "SpecPow"), lightSize, &lightSP[0]);


	//grab skeleton 
	FBXSkeleton* skeleton = m_FbxModel->getSkeletonByIndex(0);
	skeleton->updateBones();

	int bones_location = glGetUniformLocation(m_shader, "bones");
	glUniformMatrix4fv(bones_location, skeleton->m_boneCount, GL_FALSE, (float*)skeleton->m_bones);



	//glUniform3fv(glGetUniformLocation(m_shader, "CameraPos"), 1, &camera->m_Pos[0]);
	//glUniform3fv(glGetUniformLocation(m_shader, "SpecColor"), lightSize, &lightSC->r);
	//glUniform1fv(glGetUniformLocation(m_shader, "SpecPow"), lightSize, lightSP);

	for (unsigned int i = 0; i < m_FbxModel->getMeshCount(); ++i)
	{
		FBXMeshNode* mesh = m_FbxModel->getMeshByIndex(i);
		GLMesh* glData = (GLMesh*)mesh->m_userData;
		// get the texture from the model
		unsigned int diffuseTexture =mesh->m_material->textureIDs[mesh->m_material->DiffuseTexture];
		// bid the texture and send it to our shader
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, diffuseTexture);
		glUniform1i(glGetUniformLocation(m_shader, "diffuseTexture"), 0);
		// draw the mesh
		glBindVertexArray(glData->m_vao);
		glDrawElements(GL_TRIANGLES, mesh->m_indices.size(), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}
	glUseProgram(0);




}

void FBXModel::update(float deltaTime)
{
	if (m_FbxModel->getSkeletonCount() <= 0)return;
	FBXSkeleton* skeleton = m_FbxModel->getSkeletonByIndex(0);
	FBXAnimation* animation = m_FbxModel->getAnimationByIndex(0);

	skeleton->evaluate(animation, deltaTime);

	for (unsigned int  bone_index = 0; bone_index < skeleton->m_boneCount; bone_index++)
	{
		skeleton->m_nodes[bone_index]->updateGlobalTransform();
	}
}

void FBXModel::CreateFBXOpenGLBuffers(FBXFile * file)
{
	// FBX Files contain multiple meshes, each with seperate material information
	// loop through each mesh within the FBX file and cretae VAO, VBO and IBO buffers for each mesh.
	// We can store that information within the mesh object via its "user data" void pointer variable.

	for (unsigned int i = 0; i < file->getMeshCount(); i++)
	{
		// get current mesh from file
		FBXMeshNode * fbxMesh = file->getMeshByIndex(i);

		GLMesh *glData = new GLMesh();

		glGenVertexArrays(1, &glData->m_vao);
		glBindVertexArray(glData->m_vao);

		glGenBuffers(1, &glData->m_vbo);
		glGenBuffers(1, &glData->m_ibo);

		glBindBuffer(GL_ARRAY_BUFFER, glData->m_vbo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, glData->m_ibo);

		//fill vbo with verts
		// the fbxloader has verts structure
		glBufferData(GL_ARRAY_BUFFER, fbxMesh->m_vertices.size() * sizeof(FBXVertex),
					 fbxMesh->m_vertices.data(), GL_STATIC_DRAW);

		//fill ibo buffer 
		// fbx meshes can be large so indices are stored as unsigned ints
		glBufferData(GL_ELEMENT_ARRAY_BUFFER,
					 fbxMesh->m_indices.size() * sizeof(unsigned int),
					 fbxMesh->m_indices.data(), GL_STATIC_DRAW);

		// Setup Vertex Attrib pointers
		// remember, we only need to setup the approprate attributes for the shaders that will be rendering
		// this fbx object.
		glEnableVertexAttribArray(0); //position
		glEnableVertexAttribArray(1); //normals
		glEnableVertexAttribArray(2); //tangents
		glEnableVertexAttribArray(3); //texcoords
		glEnableVertexAttribArray(4); //weights
		glEnableVertexAttribArray(5); //indices
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(FBXVertex),
			(void*)FBXVertex::PositionOffset);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_TRUE, sizeof(FBXVertex),
			(void*)FBXVertex::NormalOffset);
		glVertexAttribPointer(2, 4, GL_FLOAT, GL_TRUE, sizeof(FBXVertex),
			(void*)FBXVertex::TangentOffset);
		glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(FBXVertex),
			(void*)FBXVertex::TexCoord1Offset);
		glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(FBXVertex),
			(void*)FBXVertex::WeightsOffset);
		glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(FBXVertex),
			(void*)FBXVertex::IndicesOffset);
		// TODO: add any additional attribute pointers required for shader use.
		// unbind
		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		// attach our GLMesh object to the m_userData pointer.
		fbxMesh->m_userData = glData;
	}

}

void FBXModel::CleanupFBXOpenGLBuffers(FBXFile * file)
{
	for (unsigned int i = 0; i < file->getMeshCount(); i++)
	{
		FBXMeshNode *fbxMesh = file->getMeshByIndex(i);
		GLMesh *glData = (GLMesh *)fbxMesh->m_userData;
		glDeleteVertexArrays(1, &glData->m_vao);
		glDeleteBuffers(1, &glData->m_vbo);
		glDeleteBuffers(1, &glData->m_ibo);
		delete glData;
	}
}

void FBXModel::LoadShaders()
{
	std::string vsSource = StringFromFile("./HeightMapStarter/shaders/Animation.vert");
	const char* vsSourcePtr = vsSource.c_str();

	std::string fsSource = StringFromFile("./HeightMapStarter/shaders/Animation.frag");

	const char* fsSourcePtr = fsSource.c_str();

	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, (const char**)&vsSourcePtr, 0);
	glCompileShader(vertexShader);
	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, (const char**)&fsSourcePtr, 0);
	glCompileShader(fragmentShader);
	m_shader = glCreateProgram();
	glAttachShader(m_shader, vertexShader);
	glAttachShader(m_shader, fragmentShader);

	glBindAttribLocation(m_shader, 0, "position");
	glBindAttribLocation(m_shader, 1, "normal");
	glBindAttribLocation(m_shader, 2, "tangent");
	glBindAttribLocation(m_shader, 3, "tex_coord");
	glBindAttribLocation(m_shader, 4, "weights");
	glBindAttribLocation(m_shader, 5, "indices");

	glLinkProgram(m_shader);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}


void FBXModel::UnloadShaders()
{
	glDeleteProgram(m_shader);
}

void GLMesh::MakeCube(int x, int y, int z)
{
	glm::vec4 white(1, 1, 1, 1);

	// Step 1:
	// Specify the position and color for each vert of a cube
	// for this example, each face does not share a vert, so we have 4 verts for each face of our cube/
	Vertex verts[] = {
		// POSITION					COLOR	
		// FRONT FACE				  - RED
		{ { -0.5f + x,-0.5f + y, 0.5f + z, 1.0f },white,{ 0.0f, 0.0f } ,{ 0.0f,0.0f, -1.0f } },	// 0
		{ { 0.5f + x,-0.5f + y, 0.5f + z, 1.0f }, white,{ 1.0f, 0.0f },{ 0.0f,0.0f, -1.0f } },	// 1
		{ { 0.5f + x, 0.5f + y, 0.5f + z, 1.0f }, white,{ 1.0f, 1.0f },{ 0.0f,0.0f, -1.0f } },	// 2
		{ { -0.5f + x, 0.5f + y, 0.5f + z, 1.0f },white,{ 0.0f, 1.0f } ,{ 0.0f,0.0f, -1.0f } },	// 3

																								// BACK FACE				- YELLOW
		{ { -0.5f + x,-0.5f + y,-0.5f + z, 1.0f },white,{ 0.0f, 0.0f },{ 0.0f, 0.0f, 1.0f } },	// 4
		{ { 0.5f + x,-0.5f + y,-0.5f + z, 1.0f },white,{ 1.0f, 0.0f },{ 0.0f, 0.0f, 1.0f } },	// 5
		{ { 0.5f + x, 0.5f + y,-0.5f + z, 1.0f },white,{ 1.0f, 1.0f },{ 0.0f, 0.0f, 1.0f } },	// 6
		{ { -0.5f + x, 0.5f + y,-0.5f + z, 1.0f },white,{ 0.0f, 1.0f },{ 0.0f, 0.0f, 1.0f } },	// 7

																								// LEFT FACE				- GREEN
		{ { -0.5f + x,-0.5f + y,-0.5f + z, 1.0f },white,{ 0.0f, 0.0f },{ 1.0f, 0.0f, 0.0f } },	// 8
		{ { -0.5f + x,-0.5f + y, 0.5f + z, 1.0f },white,{ 0.0f, 1.0f },{ 1.0f, 0.0f, 0.0f } },	// 9
		{ { -0.5f + x, 0.5f + y, 0.5f + z, 1.0f },white,{ 1.0f, 1.0f },{ 1.0f, 0.0f, 0.0f } },	// 10
		{ { -0.5f + x, 0.5f + y,-0.5f + z, 1.0f },white,{ 1.0f, 0.0f },{ 1.0f, 0.0f, 0.0f } },	// 11

																								// RIGHT FACE				- CYAN
		{ { 0.5f + x,-0.5f + y,-0.5f + z, 1.0f },white,{ 0.0f, 0.0f },{ -1.0f, 0.0f, 0.0f } },	// 12
		{ { 0.5f + x,-0.5f + y, 0.5f + z, 1.0f },white,{ 0.0f, 1.0f },{ -1.0f, 0.0f, 0.0f } },	// 13
		{ { 0.5f + x, 0.5f + y, 0.5f + z, 1.0f },white,{ 1.0f, 1.0f },{ -1.0f, 0.0f, 0.0f } },	// 14
		{ { 0.5f + x, 0.5f + y,-0.5f + z, 1.0f },white,{ 1.0f, 0.0f },{ -1.0f, 0.0f, 0.0f } },	// 15

																								// TOP FACE					 - BLUE 
		{ { -0.5f + x, 0.5f + y,-0.5f + z, 1.0f },white,{ 0.0f, 0.0f },{ 0.0f, -1.0f, 0.0f } },	// 16
		{ { -0.5f + x, 0.5f + y, 0.5f + z, 1.0f },white,{ 0.0f, 1.0f },{ 0.0f, -1.0f, 0.0f } },	// 17
		{ { 0.5f + x, 0.5f + y, 0.5f + z, 1.0f },white,{ 1.0f, 1.0f },{ 0.0f, -1.0f, 0.0f } },	// 18
		{ { 0.5f + x, 0.5f + y,-0.5f + z, 1.0f },white,{ 1.0f, 0.0f },{ 0.0f, -1.0f, 0.0f } },	// 19

																								// BOTTOM FACE				- MAGENTA
		{ { -0.5f + x,-0.5f + y,-0.5f + z, 1.0f },white,{ 0.0f, 0.0f },{ 0.0f,1.0f, 0.0f } },	// 20
		{ { -0.5f + x,-0.5f + y, 0.5f + z, 1.0f },white,{ 0.0f, 1.0f },{ 0.0f,1.0f, 0.0f } },	// 21
		{ { 0.5f + x,-0.5f + y, 0.5f + z, 1.0f },white,{ 1.0f, 1.0f },{ 0.0f,1.0f, 0.0f } },	// 22
		{ { 0.5f + x,-0.5f + y,-0.5f + z, 1.0f },white,{ 1.0f, 0.0f },{ 0.0f,1.0f, 0.0f } }		// 23
	};

	// Step 2:
	// From the above verts, we need to construct triangles that opengl can then use to render.
	// Winding order is important, each triangle needs to be described in a clockwise order
	// this defines the faceing direction for the triangle.
	// By default OpenGL will cull pixels that are "facing away" from the camera glCullMode(GL_BACK) is the default setting.
	// Culling can be changed to GL_FRONT or GL_FRONT_AND_BACK, or enabled/dsabled via glEnable(GL_CULL_FACE) / glDisable(GL_CULL_FACE)
	unsigned short indices[] =
	{
		0, 1, 2,	 0, 2, 3,  // front face
		6, 5, 4,	 7, 6, 4,  // back face
		8, 9, 10,	 8,10,11,  // left face
		14,13,12,	 15,14,12, // right face
		16,17,18,	 16,18,19, // top face
		22,21,20,	 23,22,20  // bottom face
	};

	// Step 3:
	// Its always a good idea to keep track of how many verts and indices we have
	// When drawing the glDrawElements method requires the number if indices
	// sizeof(verts) returns the entire size in bytes of the array
	// sizeof(Vertex) returns the size in bytes of a single vertes
	// we can calculate the number of verts or indices by dividing.
	m_numIndices = sizeof(indices) / sizeof(unsigned short);

	// Step 4:
	// Generate the VAO and Bind bind it.
	// Our VBO (vertex buffer object) and IBO (Index Buffer Object) will be "grouped" with this VAO
	// other settings will also be grouped with the VAO. this is used so we can reduce draw calls in the render method.
	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);

	// Step 5:
	// Create our VBO and IBO.
	// Then tell Opengl what type of buffer they are used for
	// VBO a buffer in graphics memory to contains our vertices
	// IBO a buffer in graphics memory to contain our indices.
	// Then Fill the buffers with our generated data.
	// This is taking our verts and indices from ram, and sending them to the graphics card
	glGenBuffers(1, &m_vbo);
	glGenBuffers(1, &m_ibo);

	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);

	glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Step 6:
	// Vertices can have any shape, for us, each vertex has a position and color.
	// The "shape" of our vertex need to be described to OepnGL
	// This is so the vertices can be sent to our shader and be mapped to the correct variables locations.
	Vertex::SetupVertexAttribPointers();

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
void GLMesh::MakePlane(aie::Texture *heighmap)
{
	const unsigned char *pixels = heighmap->getPixels();

	unsigned int xDiv = heighmap->getWidth();
	unsigned int zDiv = heighmap->getHeight();

	std::vector<Vertex> verts;
	std::vector<unsigned short> indices;

	// build the height map
	for (unsigned int z = 0; z<zDiv; z++)
	{
		for (unsigned int x = 0; x<xDiv; x++)
		{
			unsigned int i = (z * xDiv + x);

			// get the value of the r component at the pixel located at x,z
			// the value returned is between 0 and 255 divided by 255 for a value between 0 and 1
			// minue 0.5 so we have a value between -.05 and +0.5
			// multiply by 2 for a value between -1 and 1
			float y = ((pixels[i * 3] / 255.0f) - 0.5f);

			// position of vertex
			float xPos = (x*0.1f) - (xDiv*0.1f*0.5f);
			float yPos = y * 2;
			float zPos = (z*0.1f) - (zDiv*0.1f*0.5f);

			Vertex vert{
				{ xPos, yPos, zPos, 1.0f },
				{ 1.0f, 1.0f, 1.0f, 1.0f },
				{ (float)x / (xDiv - 1), (float)z / (zDiv - 1) },
				{ 0,0,0, }


			};

			verts.push_back(vert);
		}
	}

	// calculate indices
	for (unsigned int z = 0; z < zDiv - 1; z++)
	{
		for (unsigned int x = 0; x<xDiv - 1; x++)
		{
			unsigned int i = z * xDiv + x;

			indices.push_back(i + 1);		// 1--0
			indices.push_back(i);			// | /
			indices.push_back(i + xDiv);	// 2

			indices.push_back(i + 1);			//    0
			indices.push_back(i + xDiv);		//  / |
			indices.push_back(i + xDiv + 1);	// 2--1
		}
	}
	for (unsigned int i = 0; i < indices.size() / 3; i++)
	{
		int index1 = indices[i * 3];
		int index2 = indices[i * 3 + 1];
		int index3 = indices[i * 3 + 2];

		glm::vec4 side1(verts[index1].pos - verts[index3].pos);
		glm::vec4 side2(verts[index1].pos - verts[index2].pos);

		glm::vec3 normal = glm::cross(side1.xyz(), side2.xyz());


		verts[index1].normal += normal;
		verts[index2].normal += normal;
		verts[index3].normal += normal;
	}

	for (unsigned int i = 0; i < verts.size(); i++)
	{
		verts[i].normal = glm::normalize(verts[i].normal);
	}

	m_numIndices = indices.size();

	glGenVertexArrays(1, &m_vao);
	glGenBuffers(1, &m_vbo);
	glGenBuffers(1, &m_ibo);

	glBindVertexArray(m_vao);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);

	// populate the buffers with the verts passed in
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * verts.size(), &verts[0], GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned short) * indices.size(), &indices[0], GL_STATIC_DRAW);

	Vertex::SetupVertexAttribPointers();

	// un-bind the buffers;
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void GLMesh::Destroy()
{
	glDeleteBuffers(1, &m_vbo);
	glDeleteBuffers(1, &m_ibo);
	glDeleteVertexArrays(1, &m_vao);
}

void GLMesh::Draw()
{
	// Step 2: Bind the VAO
	// When we setup the geometry, we did a bunch of glEnableVertexAttribArray and glVertexAttribPointer method calls
	// we also Bound the vertex array and index array via the glBindBuffer call.
	// if we where not using VAO's we would have to do thoes method calls each frame here.
	glBindVertexArray(m_vao);

	// Step 3: Draw Elements. We are using GL_TRIANGLES.
	// we need to tell openGL how many indices there are, and the size of our indices
	// when we setup the geometry, our indices where an unsigned char (1 byte for each indicy)
	glDrawElements(GL_TRIANGLES, m_numIndices, GL_UNSIGNED_SHORT, 0);

	// Step 5: Now that we are done drawing the geometry
	// unbind the vao, we are basicly cleaning the opengl state
	glBindVertexArray(0);
}
