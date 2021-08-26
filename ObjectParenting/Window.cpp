
#include "Window.h"
#include <iostream>
#include <string>
#include "UIManager.h"
//Window* window=nullptr;

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
Window::Window()
{
	
}


KeyboardClass keyboard;
LRESULT CALLBACK WndProc(HWND hwnd,UINT msg, WPARAM wparam, LPARAM lparam)
{
	if(ImGui_ImplWin32_WndProcHandler(hwnd,msg,wparam,lparam))
	{
		return true;
	}
	switch (msg)
	{
	case WM_CREATE:
	{
		// Event fired when the window is created
		// collected here..
		Window* window = (Window*)((LPCREATESTRUCT)lparam)->lpCreateParams;
		// .. and then stored for later lookup
		SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)window);
		window->setHWND(hwnd);
		

			
		window->onCreate();
		break;
	}
	case WM_SETFOCUS:
	{
		// Event fired when the window get focus
		Window* window = (Window*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
		window->onFocus();
		break;
	}
	case WM_KILLFOCUS:
	{
		// Event fired when the window lost focus
		Window* window = (Window*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
		window->onKillFocus();
		break;
	}

	case WM_DESTROY:
	{
		// Event fired when the window is destroyed
		Window* window =(Window*) GetWindowLongPtr(hwnd, GWLP_USERDATA);
		window->onDestroy();
		::PostQuitMessage(0);
		break;
	}

		
	

	default:
		return ::DefWindowProc(hwnd, msg, wparam, lparam);
	}

	return NULL;

	
}


bool Window::init()
{


	//Setting up WNDCLASSEX object
	WNDCLASSEX wc;
	wc.cbClsExtra = NULL;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.cbWndExtra = NULL;
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wc.hInstance = NULL;
	wc.lpszClassName = "MyWindowClass";
	wc.lpszMenuName = "";
	wc.style = NULL;
	wc.lpfnWndProc = &WndProc;

	if (!::RegisterClassEx(&wc)) // If the registration of class will fail, the function will return false
		return false;

	/*if (!window)
		window = this;*/

	//Creation of the window
	m_hwnd=::CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, "MyWindowClass", "DirectX Application", 
		WS_CAPTION|WS_SYSMENU, CW_USEDEFAULT, CW_USEDEFAULT, 1024, 768,
		NULL, NULL, NULL, this);

	//if the creation fail return false
	if (!m_hwnd) 
		return false;
	



	//show up the window
	::ShowWindow(m_hwnd, SW_SHOW);
	::UpdateWindow(m_hwnd);

	EngineTime::initialize();
	
	
	//set this flag to true to indicate that the window is initialized and running
	m_is_run = true;



	return true;
}

bool Window::broadcast()
{
	MSG msg;
	EngineTime::LogFrameStart();
	this->onUpdate();

	while (::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	Sleep(1);
	EngineTime::LogFrameEnd();
	return true;
}


bool Window::release()
{
	//Destroy the window
	if (!::DestroyWindow(m_hwnd))
		return false;

	return true;
}

bool Window::isRun()
{
	return m_is_run;
}

RECT Window::getClientWindowRect()
{
	RECT rc;
	::GetClientRect(this->m_hwnd, &rc);
	return rc;
}

void Window::setHWND(HWND hwnd)
{
	this->m_hwnd = hwnd;
}

HWND Window::getHWND()
{
	return this->m_hwnd;
}

char Window::getKey()
{
	char retChar = NULL;
	if(keyboard.KeyIsPressed('W'))
	{
		 retChar = 'W';
		// std::cout << retChar << std::endl;
	}

	if (keyboard.KeyIsPressed('A'))
	{
		retChar = 'A';
		//std::cout << retChar << std::endl;
	}
	
	if (keyboard.KeyIsPressed('S'))
	{
		retChar = 'S';
		//std::cout << retChar << std::endl;
	}
	
	if (keyboard.KeyIsPressed('D'))
	{
		retChar = 'D';
		//std::cout << retChar << std::endl;
	}
	return retChar;
}

void Window::onCreate()
{
}

void Window::onUpdate()
{
	/*
	while (!keyboard.CharBufferIsEmpty())
	{
		unsigned char ch = keyboard.ReadChar();
		std::string outmsg = "Char: ";
		outmsg += ch;
		outmsg += "\n";
		OutputDebugStringA(outmsg.c_str());

		std::cout << "Char = " << outmsg.c_str() << std::endl;
	}

	while (!keyboard.KeyBufferIsEmpty())
	{
		KeyboardEvent kbe = keyboard.ReadKey();
		unsigned char keycode = kbe.GetKeyCode();
		std::string outmsg = "";
		if (kbe.IsPress())
		{
			outmsg += "key pressed: ";
			std::cout << "keypressed" << std::endl;
		}
		if (kbe.IsRelease())
		{
			outmsg += "key release: ";
			std::cout << "keyrelease" << std::endl;
		}
		outmsg += keycode;
		outmsg += "\n";
		OutputDebugStringA(outmsg.c_str());
	}
	*/
}

void Window::onFocus()
{
}

void Window::onKillFocus()
{
}

void Window::onDestroy()
{
	m_is_run = false;
}

Window::~Window()
{
}