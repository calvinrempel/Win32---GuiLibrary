/*-----------------------------------------------------------------------------
-- SOURCE FILE: GuiWindow.cpp - This file provides a specialized GUI element
-- that displays a Window.
--
-- REVISIONS:
--
-- DESIGNER: Calvin Rempel
--
-- PROGRAMMER: Calvin Rempel
--
-- NOTES:
-----------------------------------------------------------------------------*/

#include "GuiWindow.h"

const LPCWSTR GuiWindow::DEFAULT_WIN_CLASS = L"GUI_WINDOW_CPP";

GuiWindow::GuiWindow(HINSTANCE hInstance)
	: GuiComponent(hInstance)
{
	setup(GuiWindow::DEFAULT_WIN_CLASS,
		  L"",
		  WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_BORDER | WS_VISIBLE);

	exitOnClose = true;
}

GuiWindow::GuiWindow(HINSTANCE hInstance, GuiComponent *parent)
	: GuiComponent(hInstance, parent)
{
	setup(GuiWindow::DEFAULT_WIN_CLASS, L"", WS_TILEDWINDOW);

	exitOnClose = true;
}

void GuiWindow::setExitOnClose(bool exitOnClose)
{
	this->exitOnClose = exitOnClose;
}

void GuiWindow::setTitle(LPCWSTR title)
{
	SetWindowText(hwnd, title);
}

HWND GuiWindow::create(HINSTANCE hInstance, HWND parent)
{
	// If the Windows Class is not registered, end with error
	if (!registerWindowsClass(hInstance))
		return NULL;

	// Attempt to Create the new Window
	return CreateWindowEx(WS_EX_COMPOSITED,
						  windowClass,
						  L"GuiWindow",
						  windowStyles,
						  CW_USEDEFAULT, 0,
						  0, 0,
						  NULL, NULL, hInstance, NULL);
}

void GuiWindow::onExit()
{
	if (exitOnClose)
	{
		PostQuitMessage(0);
	}
}

bool GuiWindow::registerWindowsClass(HINSTANCE hInstance)
{
	// If the class is already registered, short circuit
	if (isClassRegistered())
		return true;

	// Register the Windows Class
	WNDCLASSEX Wcl;

	Wcl.cbSize = sizeof(WNDCLASSEX);
	Wcl.style = CS_HREDRAW | CS_VREDRAW;
	Wcl.hIcon = LoadIcon(NULL, IDI_APPLICATION); // large icon 
	Wcl.hIconSm = NULL; // use small version of large icon
	Wcl.hCursor = LoadCursor(NULL, IDC_ARROW);  // cursor style

	Wcl.lpfnWndProc = WndProc;
	Wcl.hInstance = hInstance;
	Wcl.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); //white background
	Wcl.lpszClassName = windowClass; // user defined menu

	Wcl.lpszMenuName = menuClass; // user defined menu 
	Wcl.cbClsExtra = 0;      // no extra memory needed
	Wcl.cbWndExtra = 0;

	// Register the class
	if (!RegisterClassEx(&Wcl))
		return false;

	return true;
}