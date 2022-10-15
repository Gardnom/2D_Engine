#pragma once
#include "CoreTypes.h"
#include "Window.h"
#include <vector>

class IGraphicsApi {
public:
	virtual FAILABLE_PROCEDURE Init(HWND hWnd) = 0;
	virtual void BeginDraw() = 0;
	virtual void EndDraw() = 0;
	virtual void DrawLine(Point2D p1, Point2D p2) = 0;
	virtual void ClearScreen(RGBA_COL clearColor) = 0;
	virtual void DrawPoints(std::vector<Point3D> drawPoints) = 0;
};