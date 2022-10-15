#include "Direct2DInterface.h"


Direct2DInterface::Direct2DInterface() {
	
}

Direct2DInterface::~Direct2DInterface() {

}

FAILABLE_PROCEDURE Direct2DInterface::Init(HWND hWnd) {
	HRESULT res = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_Factory);
	if (res != S_OK) return {false, "Failed to set up RenderFactory"};

	RECT rect;
	GetClientRect(hWnd, &rect);

	res = m_Factory->CreateHwndRenderTarget(D2D1::RenderTargetProperties(),
		D2D1::HwndRenderTargetProperties(hWnd, D2D1::SizeU(rect.right, rect.bottom)),
		&m_PRenderTarget);
	if (res != S_OK) return { false, "Failed to set up render target" };
	m_pWhiteBrush = CreateBrush(RGBA_COL(255.0, 255.0, 255.0, 1.0));

	
	return {true, ""};
}

void Direct2DInterface::ClearScreen(RGBA_COL clearColor) {
	m_PRenderTarget->Clear(D2D1::ColorF(clearColor.r, clearColor.g, clearColor.b, clearColor.a));
}

void Direct2DInterface::DrawLine(Point2D p1, Point2D p2) {
	ID2D1SolidColorBrush* brush;
	m_PRenderTarget->CreateSolidColorBrush(D2D1::ColorF(255, 255, 255, 1.0), &brush);
	m_PRenderTarget->DrawLine(D2D1::Point2F(p1.x, p1.y), D2D1::Point2F(p2.x, p2.y), brush);
	brush->Release();
}

void Direct2DInterface::BeginDraw() {
	m_PRenderTarget->BeginDraw();
}

void Direct2DInterface::EndDraw() {
	m_PRenderTarget->EndDraw();
}

void Direct2DInterface::DrawPoints(std::vector<Point3D> drawPoints) {
	for (int i = 0; i < drawPoints.size(); i++) {
		m_PRenderTarget->DrawLine(D2D1::Point2F(drawPoints[0].x, drawPoints[0].y), D2D1::Point2F(drawPoints[1].x, drawPoints[1].y), m_pWhiteBrush, 4);
		m_PRenderTarget->DrawLine(D2D1::Point2F(drawPoints[1].x, drawPoints[1].y), D2D1::Point2F(drawPoints[2].x, drawPoints[2].y), m_pWhiteBrush, 4);
		m_PRenderTarget->DrawLine(D2D1::Point2F(drawPoints[2].x, drawPoints[2].y), D2D1::Point2F(drawPoints[3].x, drawPoints[3].y), m_pWhiteBrush, 4);
		m_PRenderTarget->DrawLine(D2D1::Point2F(drawPoints[3].x, drawPoints[3].y), D2D1::Point2F(drawPoints[0].x, drawPoints[0].y), m_pWhiteBrush, 4);

		m_PRenderTarget->DrawLine(D2D1::Point2F(drawPoints[4].x, drawPoints[4].y), D2D1::Point2F(drawPoints[5].x, drawPoints[5].y), m_pWhiteBrush, 4);
		m_PRenderTarget->DrawLine(D2D1::Point2F(drawPoints[5].x, drawPoints[5].y), D2D1::Point2F(drawPoints[6].x, drawPoints[6].y), m_pWhiteBrush, 4);
		m_PRenderTarget->DrawLine(D2D1::Point2F(drawPoints[6].x, drawPoints[6].y), D2D1::Point2F(drawPoints[7].x, drawPoints[7].y), m_pWhiteBrush, 4);
		m_PRenderTarget->DrawLine(D2D1::Point2F(drawPoints[7].x, drawPoints[7].y), D2D1::Point2F(drawPoints[4].x, drawPoints[4].y), m_pWhiteBrush, 4);

		m_PRenderTarget->DrawLine(D2D1::Point2F(drawPoints[0].x, drawPoints[0].y), D2D1::Point2F(drawPoints[4].x, drawPoints[4].y), m_pWhiteBrush, 4);
		m_PRenderTarget->DrawLine(D2D1::Point2F(drawPoints[1].x, drawPoints[1].y), D2D1::Point2F(drawPoints[5].x, drawPoints[5].y), m_pWhiteBrush, 4);
		m_PRenderTarget->DrawLine(D2D1::Point2F(drawPoints[2].x, drawPoints[2].y), D2D1::Point2F(drawPoints[6].x, drawPoints[6].y), m_pWhiteBrush, 4);
		m_PRenderTarget->DrawLine(D2D1::Point2F(drawPoints[3].x, drawPoints[3].y), D2D1::Point2F(drawPoints[7].x, drawPoints[7].y), m_pWhiteBrush, 4);
	}
}

ID2D1SolidColorBrush* Direct2DInterface::CreateBrush(RGBA_COL color) {
	ID2D1SolidColorBrush* brush;
	m_PRenderTarget->CreateSolidColorBrush(D2D1::ColorF(color.r, color.g, color.b, color.a), &brush);
	return brush;
}