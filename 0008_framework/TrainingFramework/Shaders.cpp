#include "stdafx.h"
#include "Shaders.h"

int Shaders::Init(char * fileVertexShader, char * fileFragmentShader)
{
	vertexShader = esLoadShader(GL_VERTEX_SHADER, fileVertexShader);

	if ( vertexShader == 0 )
		return -1;

	fragmentShader = esLoadShader(GL_FRAGMENT_SHADER, fileFragmentShader);

	if ( fragmentShader == 0 )
	{
		glDeleteShader( vertexShader );
		return -2;
	}

	program = esLoadProgram(vertexShader, fragmentShader);

	//finding location of uniforms / attributes
	positionAttribute = glGetAttribLocation(program, "a_posL");
	normAttribute = glGetAttribLocation(program, "a_normL");
	uvAttribute = glGetAttribLocation(program, "a_uv");
	bitangentAttribute = glGetAttribLocation(program, "a_bitangentL");
	tangentAttribute = glGetAttribLocation(program, "a_tangentL");
	iCubeTexLoc = glGetUniformLocation(program, "u_enviroMap");
	iTextureLoc = glGetUniformLocation(program, "u_texture");
	iTextureLoc1 = glGetUniformLocation(program, "u_texture1");
	iTextureLoc2 = glGetUniformLocation(program, "u_texture2");
	iTextureLoc3 = glGetUniformLocation(program, "u_texture3");
	lightPos1 = glGetUniformLocation(program, "u_light1");
	lightColor1 = glGetUniformLocation(program, "u_color1");
	runTime = glGetUniformLocation(program, "u_time");
	cameraPos = glGetUniformLocation(program, "u_camerapos");
	wvpLoc = glGetUniformLocation(program, "u_mvpMatrix");
	worldLoc = glGetUniformLocation(program, "u_wMatrix");
	return 0;
}

Shaders::~Shaders()
{
	//printf("Shaders::~Shaders()");
	glDeleteProgram(program);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}