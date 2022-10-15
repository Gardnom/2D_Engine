#pragma once
#include <Windows.h>
#include "Window.h"
#include "Direct2DInterface.h"
#include <vector>
#include "EngineCore.h"
#include <memory>

class App {
public:
	App(HINSTANCE hInstance);
	void Run();
	void Update(f32 deltaT);
	void Setup();

private:
	std::shared_ptr<Window> m_PWindow;
	std::shared_ptr<IGraphicsApi> m_PGraphicsApi;
	std::shared_ptr<EngineCore> m_PEngineCore;

	HINSTANCE m_HInstance;
};