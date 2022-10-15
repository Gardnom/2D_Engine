#include "Window.h"
#include <stdio.h>


LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	Window* pWnd = reinterpret_cast<Window*>(GetWindowLongPtrW(hWnd, 0)); // Retrieve window pointer

	if (uMsg == WM_DESTROY) {
		pWnd->m_ShouldClose = true;
		PostQuitMessage(0);
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

Window::Window(HINSTANCE hInstance, LPSTR windowName) {
	m_Hinstance = hInstance;
}

bool Window::ShouldClose() {
	return m_ShouldClose;
}

const bool Window::ShouldDraw() {
	return m_ShouldDraw;
}

WNDPROC CreateWndProc(Window* wP) {
	return [](HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) -> LRESULT {
		if (uMsg == WM_DESTROY) {
			PostQuitMessage(0);
			//wP->m_ShouldClose = true;
			
		}
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	};
}

const HWND Window::GetHWnd() {
	return m_HWnd;
}

std::tuple<bool, std::string> Window::InitWindow() {
	DWORD windowStyle = WS_OVERLAPPEDWINDOW;
	HWND hWnd;
	WNDCLASS wnd;
	ZeroMemory(&wnd, sizeof(WNDCLASS));
	
	wnd.lpfnWndProc = WindowProc;
	wnd.lpszClassName = L"MainWindow";
	wnd.hInstance = m_Hinstance;
	wnd.style = CS_HREDRAW | CS_VREDRAW;
	wnd.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wnd.cbWndExtra = sizeof(Window*); // Store extra data

	RegisterClass(&wnd);

	
	RECT rect = { 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT };
	BOOL ok = AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);
	if (!ok) {
		return { false, "Failed to adjust window size" };
	}

	int windowWidth = rect.right - rect.left;
	int windowHeight = rect.bottom - rect.top;
	hWnd = CreateWindowA("MainWindow", "Main window", windowStyle, 0, 0, windowWidth, windowHeight, NULL, NULL, NULL, NULL);
	if (hWnd == NULL) {
		printf("Failed to create window");
		return { false, "Failed to create window"};
	}
	
	SetWindowLongPtrW(hWnd, 0, reinterpret_cast<LONG_PTR>(this)); // Store pointer to this class;

	ShowWindow(hWnd, SW_SHOW);

	m_HWnd = hWnd;
	return { true, "" };
}

void Window::PollEvents() {
	MSG message;
	message.message = WM_NULL;
	if (PeekMessage(&message, m_HWnd, 0, 0, PM_REMOVE)) {
		DispatchMessage(&message);
	}
	//GetMessage(&message, NULL, 0, 0);
	
}