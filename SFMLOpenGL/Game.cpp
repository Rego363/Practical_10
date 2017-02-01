#include <Game.h>

static bool flip;

Game::Game() : window(VideoMode(800, 600), "OpenGL Cube Texturing")
{
}

Game::~Game() {}

void Game::run()
{

	initialize();

	Event event;

	while (isRunning) {

#if (DEBUG >= 2)
		DEBUG_MSG("Game running...");
#endif

		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				isRunning = false;
			}
		}
		update();
		render();
	}

}

typedef struct
{
	float coordinate[3];
	float color[4];
	float texel[2];
} Vertex;

Vertex vertex[8];
GLubyte triangles[36];

/* Variable to hold the VBO identifier and shader data */
GLuint	index,		//Index to draw
		vsid,		//Vertex Shader ID
		fsid,		//Fragment Shader ID
		progID,		//Program ID
		vao = 0,	//Vertex Array ID
		vbo[1],		// Vertex Buffer ID
		positionID, //Position ID
		colorID,	// Color ID
		to,			// Texture ID 1 to 32
		textureID,	//Texture ID
		texelID;	// Texel ID

//const string filename = "minecraft.tga";
const string filename = "cube.tga";

//const string filename = "texture.tga";

int width; //width of texture
int height; //height of texture
int comp_count; //Component of texture
const int number = 4; //4 = RGBA

unsigned char* img_data;

static const GLfloat g_uv_buffer_data[] = {
	0.000059f, 1.0f - 0.000004f,
	0.000103f, 1.0f - 0.336048f,
	0.335973f, 1.0f - 0.335903f,
	1.000023f, 1.0f - 0.000013f,
	0.667979f, 1.0f - 0.335851f,
	0.999958f, 1.0f - 0.336064f,
	0.667979f, 1.0f - 0.335851f,
	0.336024f, 1.0f - 0.671877f,
	0.667969f, 1.0f - 0.671889f,
	1.000023f, 1.0f - 0.000013f,
	0.668104f, 1.0f - 0.000013f,
	0.667979f, 1.0f - 0.335851f,
	0.000059f, 1.0f - 0.000004f,
	0.335973f, 1.0f - 0.335903f,
	0.336098f, 1.0f - 0.000071f,
	0.667979f, 1.0f - 0.335851f,
	0.335973f, 1.0f - 0.335903f,
	0.336024f, 1.0f - 0.671877f,
	1.000004f, 1.0f - 0.671847f,
	0.999958f, 1.0f - 0.336064f,
	0.667979f, 1.0f - 0.335851f,
	0.668104f, 1.0f - 0.000013f,
	0.335973f, 1.0f - 0.335903f,
	0.667979f, 1.0f - 0.335851f,
	0.335973f, 1.0f - 0.335903f,
	0.668104f, 1.0f - 0.000013f,
	0.336098f, 1.0f - 0.000071f,
	0.000103f, 1.0f - 0.336048f,
	0.000004f, 1.0f - 0.671870f,
	0.336024f, 1.0f - 0.671877f,
	0.000103f, 1.0f - 0.336048f,
	0.336024f, 1.0f - 0.671877f,
	0.335973f, 1.0f - 0.335903f,
	0.667969f, 1.0f - 0.671889f,
	1.000004f, 1.0f - 0.671847f,
	0.667979f, 1.0f - 0.335851f
};

void Game::initialize()
{
	isRunning = true;
	GLint isCompiled = 0;
	GLint isLinked = 0;

	glewInit();

	glEnable(GL_CULL_FACE);

	DEBUG_MSG(glGetString(GL_VENDOR));
	DEBUG_MSG(glGetString(GL_RENDERER));
	DEBUG_MSG(glGetString(GL_VERSION));

	/* Vertices counter-clockwise winding */
	vertex[0].coordinate[0] = -0.5f;
	vertex[0].coordinate[1] = -0.5f;
	vertex[0].coordinate[2] = -0.0f;

	vertex[1].coordinate[0] = -0.5f;
	vertex[1].coordinate[1] = 0.5f;
	vertex[1].coordinate[2] = -0.0f;

	vertex[2].coordinate[0] = 0.5f;
	vertex[2].coordinate[1] = 0.5f;
	vertex[2].coordinate[2] = -0.0f;

	vertex[3].coordinate[0] = 0.5f;
	vertex[3].coordinate[1] = -0.5f;
	vertex[3].coordinate[2] = -0.0f;

	vertex[4].coordinate[0] = -0.5f;
	vertex[4].coordinate[1] = -0.5f;
	vertex[4].coordinate[2] = -1.0f;

	vertex[5].coordinate[0] = -0.5f;
	vertex[5].coordinate[1] = 0.5f;
	vertex[5].coordinate[2] = -1.0f;

	vertex[6].coordinate[0] = 0.5f;
	vertex[6].coordinate[1] = 0.5f;
	vertex[6].coordinate[2] = -1.0f;

	vertex[7].coordinate[0] = 0.5f;
	vertex[7].coordinate[1] = -0.5f;
	vertex[7].coordinate[2] = -1.0f;

	vertex[0].color[0] = 1.0f;
	vertex[0].color[1] = 0.0f;
	vertex[0].color[2] = 0.0f;
	vertex[0].color[3] = 1.0f;

	vertex[1].color[0] = 1.0f;
	vertex[1].color[1] = 0.0f;
	vertex[1].color[2] = 0.0f;
	vertex[1].color[3] = 1.0f;

	vertex[2].color[0] = 1.0f;
	vertex[2].color[1] = 0.0f;
	vertex[2].color[2] = 0.0f;
	vertex[2].color[3] = 0.0f;

	vertex[3].color[0] = 1.0f;
	vertex[3].color[1] = 0.0f;
	vertex[3].color[2] = 0.0f;
	vertex[3].color[3] = 1.0f;

	vertex[4].color[0] = 1.0f;
	vertex[4].color[1] = 0.0f;
	vertex[4].color[2] = 0.0f;
	vertex[4].color[3] = 1.0f;

	vertex[5].color[0] = 1.0f;
	vertex[5].color[1] = 0.0f;
	vertex[5].color[2] = 0.0f;
	vertex[5].color[3] = 0.0f;

	vertex[6].color[0] = 1.0f;
	vertex[6].color[1] = 0.0f;
	vertex[6].color[2] = 0.0f;
	vertex[6].color[3] = 1.0f;

	vertex[7].color[0] = 1.0f;
	vertex[7].color[1] = 0.0f;
	vertex[7].color[2] = 0.0f;
	vertex[7].color[3] = 1.0f;

	vertex[0].texel[0] = 0.5f;
	vertex[0].texel[1] = 0.5f;
	
	vertex[1].texel[0] = 1.0f;
	vertex[1].texel[1] = 1.0f;
	
	vertex[2].texel[0] = 1.0f;
	vertex[2].texel[1] = 0.0f;
	
	vertex[3].texel[0] = 0.0f;
	vertex[3].texel[1] = 0.0f;
	
	vertex[4].texel[0] = 0.0f;
	vertex[4].texel[1] = 1.0f;
	
	vertex[5].texel[0] = 1.0f;
	vertex[5].texel[1] = 0.0f;
	
	vertex[6].texel[0] = 0.0f;
	vertex[6].texel[1] = 1.0f;
	
	vertex[7].texel[0] = 1.0f;
	vertex[7].texel[1] = 0.0f;

	/*Index of Poly / Triangle to Draw */
	//Front Face
	triangles[0] = 0;   triangles[1] = 3;   triangles[2] = 2;
	triangles[3] = 0;	triangles[4] = 2;	triangles[5] = 1;
	// Left Face
	triangles[6] = 4;	triangles[7] = 1;	triangles[8] = 5;
	triangles[15] = 4;	triangles[16] = 0;	triangles[17] = 1;
	// Top Face
	triangles[9] = 1;	triangles[10] = 6;	triangles[11] = 5;
	triangles[12] = 1;	triangles[13] = 2;	triangles[14] = 6;
	// Back Face
	triangles[18] = 7;	triangles[19] = 5;	triangles[20] = 6;
	triangles[21] = 7;	triangles[22] = 4;	triangles[23] = 5;
	// Bottom Face
	triangles[24] = 4;	triangles[25] = 3;	triangles[26] = 0;
	triangles[27] = 4;	triangles[28] = 7;	triangles[29] = 3;
	// Right Face
	triangles[30] = 3;	triangles[31] = 6;	triangles[32] = 2;
	triangles[33] = 3;	triangles[34] = 7;	triangles[35] = 6;

	/* Create a new VBO using VBO id */
	glGenBuffers(1, vbo);

	/* Bind the VBO */
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);

	/* Upload vertex data to GPU */
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * 8, vertex, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &index);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLubyte) * 36, triangles, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	

	/* Vertex Shader which would normally be loaded from an external file */
	
	vertexInput.open("vertexShader.txt");
	vss << vertexInput.rdbuf();
	vsLine = vss.str();
	const char* vs_src = vsLine.c_str();


	//const char* vs_src = "#version 400\n\r"
	//	"in vec4 sv_position;"
	//	"in vec4 sv_color;"
	//	"in vec2 sv_texel;"
	//	"out vec4 color;"
	//	"out vec2 texel;"
	//	"void main() {"
	//	"	color = sv_color;"
	//	"	texel = sv_texel;"
	//	"	gl_Position = sv_position;"
	//	"}"; //Vertex Shader Src

	DEBUG_MSG("Setting Up Vertex Shader");

	vsid = glCreateShader(GL_VERTEX_SHADER); //Create Shader and set ID
	glShaderSource(vsid, 1, (const GLchar**)&vs_src, NULL); // Set the shaders source
	glCompileShader(vsid); //Check that the shader compiles

	//Check is Shader Compiled
	glGetShaderiv(vsid, GL_COMPILE_STATUS, &isCompiled);

	if (isCompiled == GL_TRUE) {
		DEBUG_MSG("Vertex Shader Compiled");
		isCompiled = GL_FALSE;
	}
	else
	{
		DEBUG_MSG("ERROR: Vertex Shader Compilation Error");
	}

	/* Fragment Shader which would normally be loaded from an external file */
	
	fragInput.open("fragShader.txt");
	ss << fragInput.rdbuf();
	line = ss.str();
	const char* fs_src = line.c_str();

	//const char* fs_src = "#version 400\n\r"
	//	"uniform sampler2D f_texture;"
	//	"in vec4 color;"
	//	"in vec2 texel;"
	//	"out vec4 fColor;"
	//	"void main() {"
	//	//"	fColor = vec4(0.0f, 1.0f, 0.0f, 1.0f);"
	//	"	fColor = texture(f_texture, texel.st);"
	//	"}"; //Fragment Shader Src

	DEBUG_MSG("Setting Up Fragment Shader");

	fsid = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fsid, 1, (const GLchar**)&fs_src, NULL);
	glCompileShader(fsid);
	//Check is Shader Compiled
	glGetShaderiv(fsid, GL_COMPILE_STATUS, &isCompiled);

	if (isCompiled == GL_TRUE) {
		DEBUG_MSG("Fragment Shader Compiled");
		isCompiled = GL_FALSE;
	}
	else
	{
		DEBUG_MSG("ERROR: Fragment Shader Compilation Error");
	}

	DEBUG_MSG("Setting Up and Linking Shader");
	progID = glCreateProgram();	//Create program in GPU
	glAttachShader(progID, vsid); //Attach Vertex Shader to Program
	glAttachShader(progID, fsid); //Attach Fragment Shader to Program
	glLinkProgram(progID);

	//Check is Shader Linked
	glGetProgramiv(progID, GL_LINK_STATUS, &isLinked);

	if (isLinked == 1) {
		DEBUG_MSG("Shader Linked");
	}
	else
	{
		DEBUG_MSG("ERROR: Shader Link Error");
	}

	// Use Progam on GPU
	// https://www.opengl.org/sdk/docs/man/html/glUseProgram.xhtml
	glUseProgram(progID);

	img_data = stbi_load(filename.c_str(), &width, &height, &comp_count, 4);

	if (img_data == NULL)
	{
		DEBUG_MSG("ERROR: Texture not loaded");
	}
	
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &to);
	glBindTexture(GL_TEXTURE_2D, to);

	//Wrap around
	//https://www.khronos.org/opengles/sdk/docs/man/xhtml/glTexParameter.xml
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	//Filtering
	//https://www.khronos.org/opengles/sdk/docs/man/xhtml/glTexParameter.xml
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);


	//Bind to OpenGL
	//https://www.khronos.org/opengles/sdk/docs/man/xhtml/glTexImage2D.xml
	glTexImage2D(
		GL_TEXTURE_2D, //2D Texture Image
		0, //Mipmapping Level 
		GL_RGBA, //GL_RED, GL_GREEN, GL_BLUE, GL_ALPHA, GL_RGB, GL_BGR, GL_RGBA 
		width, //Width
		height, //Height
		0, //Border
		GL_RGBA, //Bitmap
		GL_UNSIGNED_BYTE, 
		img_data);

	// Find variables in the shader
	//https://www.khronos.org/opengles/sdk/docs/man/xhtml/glGetAttribLocation.xml
	positionID = glGetAttribLocation(progID, "sv_position");
	colorID = glGetAttribLocation(progID, "sv_color");
	texelID = glGetAttribLocation(progID, "sv_texel");
	textureID = glGetUniformLocation(progID, "f_texture");


}

void Game::update()
{
	elapsed = clock.getElapsedTime();

	for (int i = 0; i < 8; i++)
	{
		MyVector3 rotate = MyVector3(vertex[i].coordinate[0], vertex[i].coordinate[1], vertex[i].coordinate[2] + 0.5f);
		Matrix3 emptyMat = Matrix3();
		rotate = emptyMat.rotVecX(rotate, rotationAngle);
		rotate = emptyMat.rotVecY(rotate, rotationAngle);
		vertex[i].coordinate[0] = rotate.getX();
		vertex[i].coordinate[1] = rotate.getY();
		vertex[i].coordinate[2] = rotate.getZ() - 0.5f;
	}

	if (elapsed.asSeconds() >= 1.0f)
	{
		clock.restart();

		if (!flip)
		{
			flip = true;
		}
		else
			flip = false;
	}

	//if (flip)
	//{
	//	rotationAngle += 0.005f;
	//
	//	if (rotationAngle > 360.0f)
	//	{
	//		rotationAngle -= 360.0f;
	//	}
	//}

	//Change vertex data
	//vertex[0].coordinate[0] += -0.0001f;
	//vertex[0].coordinate[1] += -0.0001f;
	//vertex[0].coordinate[2] += -0.0001f;
	//
	//vertex[1].coordinate[0] += -0.0001f;
	//vertex[1].coordinate[1] += -0.0001f;
	//vertex[1].coordinate[2] += -0.0001f;
	//
	//vertex[2].coordinate[0] += -0.0001f;
	//vertex[2].coordinate[1] += -0.0001f;
	//vertex[2].coordinate[2] += -0.0001f;

#if (DEBUG >= 2)
	DEBUG_MSG("Update up...");
#endif

	glCullFace(GL_BACK);
}

void Game::render()
{

#if (DEBUG >= 2)
	DEBUG_MSG("Drawing...");
#endif

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	glLoadIdentity();
	glOrtho(0, 100, 0, 100, -1, 1);
	glColor3f(1, 1, 1);
	glBegin(GL_TRIANGLE_STRIP);
	glTexCoord2f(0, 0);		glVertex2i(11, 31);
	glTexCoord2f(0, 1);		glVertex2i(37, 71);
	glTexCoord2f(1, 0);		glVertex2i(91, 38);
	glTexCoord2f(1, 1);		glVertex2i(65, 71);
	glEnd(); 
	glFlush();

	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index);

	/*	As the data positions will be updated by the this program on the
		CPU bind the updated data to the GPU for drawing	*/
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * 8, vertex, GL_STATIC_DRAW);

	/*	Draw Triangle from VBO	(set where to start from as VBO can contain
		model components that 'are' and 'are not' to be drawn )	*/

	//Set Active Texture .... 32
	glActiveTexture(GL_TEXTURE0);
	glUniform1i(textureID, 0);

	// Set pointers for each parameter
	// https://www.opengl.org/sdk/docs/man4/html/glVertexAttribPointer.xhtml
	glVertexAttribPointer(positionID, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	glVertexAttribPointer(colorID, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	glVertexAttribPointer(texelID, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);

	//Enable Arrays
	glEnableVertexAttribArray(positionID);
	glEnableVertexAttribArray(colorID);
	glEnableVertexAttribArray(texelID);

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, (char*)NULL + 0);

	window.display();

}

void Game::unload()
{
#if (DEBUG >= 2)
	DEBUG_MSG("Cleaning up...");
#endif
	glDeleteProgram(progID);
	glDeleteBuffers(1, vbo);
	stbi_image_free(img_data); //Free image
}

//GLuint createTexture(char const* Filename)
//{
//	gli::texture Texture = gli::load(Filename);
//}