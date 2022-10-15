#pragma once
#include <d2d1.h>
#include "CoreTypes.h"
#include "IGraphicsApi.h"
#include "glm/glm.hpp"

class Direct2DInterface : public IGraphicsApi{
public:
	Direct2DInterface();
	~Direct2DInterface();
	
	FAILABLE_PROCEDURE Init(HWND hWnd);
	void BeginDraw();
	void EndDraw();
	void DrawLine(Point2D p1, Point2D p2);
	void ClearScreen(RGBA_COL clearColor);
	ID2D1SolidColorBrush* CreateBrush(RGBA_COL color);
	void DrawPoints(std::vector<Point3D> drawPoints);
	

private:
	ID2D1Factory* m_Factory;
	ID2D1HwndRenderTarget* m_PRenderTarget;
	ID2D1SolidColorBrush* m_pWhiteBrush;
};