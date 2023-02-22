// TrainingFramework.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../Utilities/utilities.h" // if you use STL, please include this line AFTER all other include
#include "Vertex.h"
#include "Globals.h"
#include <conio.h>
#include "SceneMgr.h"

int keypress = 0;

int Init ( ESContext *esContext )
{
	glClearColor ( 0.0f, 0.0f, 0.0f, 1.0f );
	glEnable(GL_DEPTH_TEST);

	//Creation of Scene Manager
	SceneMgr::CreateSceneMgr();
	SceneMgr::GetSceneMgr()->Init("../Resources/SceneManager.txt", Globals::screenWidth, Globals::screenHeight);

	return 0;
}

void Draw ( ESContext *esContext )
{
	SceneMgr::GetSceneMgr()->Draw(esContext);
}

void Update ( ESContext *esContext, float deltaTime )
{
	SceneMgr::GetSceneMgr()->Update(esContext, deltaTime, keypress);
}

void Key ( ESContext *esContext, unsigned char key, bool bIsPressed)
{
	if (bIsPressed == false)
	{
		switch (key)
		{
		case 'A':
			keypress &= ~(1 << 0);
			break;
		case 'D':
			keypress &= ~(1 << 1);
			break;
		case 'W':
			keypress &= ~(1 << 2);
			break;
		case 'S':
			keypress &= ~(1 << 3);
			break;
		case (VK_LEFT):
			keypress &= ~(1 << 4);
			break;
		case (VK_RIGHT):
			keypress &= ~(1 << 5);
			break;
		case (VK_UP):
			keypress &= ~(1 << 6);
			break;
		case (VK_DOWN):
			keypress &= ~(1 << 7);
			break;
		default:
			break;
		}
	}
	if (bIsPressed == true)
	{
		switch (key)
		{
		case 'A':
			keypress |= 1 << 0;
			break;
		case 'D':
			keypress |= 1 << 1;
			break;
		case 'W':
			keypress |= 1 << 2;
			break;
		case 'S':
			keypress |= 1 << 3;
			break;
		case (VK_LEFT):
			keypress |= 1 << 4;
			break;
		case (VK_RIGHT):
			keypress |= 1 << 5;
			break;
		case (VK_UP):
			keypress |= 1 << 6;
			break;
		case (VK_DOWN):
			keypress |= 1 << 7;
			break;
		default:
			break;
		}
	}
}

void CleanUp()
{
	SceneMgr::DestroySceneMgr();
}

int _tmain(int argc, _TCHAR* argv[])
{
	ESContext esContext;

    esInitContext ( &esContext );

	esCreateWindow ( &esContext, "Hello Triangle", Globals::screenWidth, Globals::screenHeight, ES_WINDOW_RGB | ES_WINDOW_DEPTH);

	if ( Init ( &esContext ) != 0 )
		return 0;

	esRegisterDrawFunc ( &esContext, Draw );
	esRegisterUpdateFunc ( &esContext, Update );
	esRegisterKeyFunc ( &esContext, Key);

	esMainLoop ( &esContext );

	//releasing OpenGL resources
	CleanUp();

	//identifying memory leaks
	MemoryDump();
	printf("Press any key...\n");
	_getch();

	return 0;
}

