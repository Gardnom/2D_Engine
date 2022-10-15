#include "App.h"
#include <chrono>

App::App(HINSTANCE hInstance) {
	m_HInstance = hInstance;
}

void App::Setup() {
	m_PWindow = std::make_shared<Window>(m_HInstance, (LPSTR)"Main window");
	auto [winOk, winErr] = m_PWindow->InitWindow();
	if (!winOk) {

	}

	//std::tuple<int, std::string> myTupel(43, std::string("Hej"));
	//auto&[x, y] = myTupel;
	m_PGraphicsApi = std::make_shared<Direct2DInterface>();
	auto[ok, errStr] = m_PGraphicsApi->Init(m_PWindow->GetHWnd());
	if (!ok) {
		// Should handle error here
		
	}

	m_PEngineCore = std::make_shared<EngineCore>();
	auto [eningeOk, engineErr] = m_PEngineCore->Init();


}

void App::Run() {
	f32 deltaT = 0; // Time elapsed in ms
	UINT32 framesCount = 0;
	auto startOfProgram = std::chrono::high_resolution_clock::now();
	while (!m_PWindow->ShouldClose()) {
		auto start = std::chrono::high_resolution_clock::now();
		Update(deltaT);
		auto elapsed = std::chrono::high_resolution_clock::now() - start;
		long long microSecondsElapsed = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
		deltaT = (f32)microSecondsElapsed * 0.001;
		
		framesCount++;
		UINT32 fps = 1000 / deltaT;

		char windowNameBuf[40];
		sprintf_s(windowNameBuf, "FPS: %u", fps);
		SetWindowTextA(m_PWindow->GetHWnd(), windowNameBuf);
	}
}

void App::Update(f32 deltaT) {
	RGBA_COL clearColor = { 0, 0, 0, 1 };

	std::vector<glm::vec3> points;
	points.reserve(8);
	points.push_back(Point3D(-200, -200, -200));
	points.push_back(Point3D(-200, 200, -200));
	points.push_back(Point3D(200, 200, -200));
	points.push_back(Point3D(200, -200, -200));
	points.push_back(Point3D(-200, -200, 200));
	points.push_back(Point3D(-200, 200, 200));
	points.push_back(Point3D(200, 200, 200));
	points.push_back(Point3D(200, -200, 200));




	m_PWindow->PollEvents();
	std::vector<glm::vec3> renderPoints;
	renderPoints.reserve(8);
	for (int i = 0; i < points.size(); i++) {
		Point3D renderPoint;
		renderPoint = m_PEngineCore->ApplyPerspective(points[i]);
		renderPoint = m_PEngineCore->CenterScreen(renderPoint);
		renderPoints.push_back(renderPoint);
	}
	m_PGraphicsApi->BeginDraw();
	m_PGraphicsApi->ClearScreen(clearColor);
	m_PGraphicsApi->DrawPoints(renderPoints);
	//m_PGraphicsApi->DrawLine(p1, p2);
	m_PGraphicsApi->EndDraw();
}