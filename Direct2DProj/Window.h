#pragma once

#include <Windows.h>
#include "CoreTypes.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600


class Window {
public:
	Window(HINSTANCE hInstance, LPSTR windowName);
	void PollEvents();
	PROCEDURE_RETURN InitWindow();
	bool ShouldClose();
	const HWND GetHWnd();
	const bool ShouldDraw();

	friend WNDPROC CreateWndProc(Window* wP);
	friend LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	bool m_ShouldDraw = false;
private:
	HINSTANCE m_Hinstance;
	HWND m_HWnd;
	bool m_ShouldClose = false;

	//WNDPROC CreateWndProc();
};