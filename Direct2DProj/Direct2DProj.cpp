#include <Windows.h>
#include <d2d1_1.h>
#include <stdio.h>

#include "Window.h"
#include "Direct2DInterface.h"
#include <vector>
#include "EngineCore.h"
#include "App.h"

#pragma comment(lib, "d2d1")

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	App app(hInstance);
	app.Setup();
	app.Run();
}

