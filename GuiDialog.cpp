/*-----------------------------------------------------------------------------
-- SOURCE FILE: GuiDialog.cpp - This file provides a modal window that acts
-- as a dialog box.
--
-- REVISIONS:
--
-- DESIGNER: Calvin Rempel
--
-- PROGRAMMER: Calvin Rempel
--
-- NOTES:
-----------------------------------------------------------------------------*/

#include "GuiDialog.h"

const LPCWSTR GuiDialog::DEFAULT_WIN_CLASS = L"GUI_WINDOW_CPP";

GuiDialog::GuiDialog(HINSTANCE hInstance)
	: GuiComponent(hInstance)
{
	setup(GuiDialog::DEFAULT_WIN_CLASS, L"", WS_DLGFRAME);
}

GuiDialog::GuiDialog(HINSTANCE hInstance, GuiComponent *parent)
	: GuiComponent(hInstance, parent)
{
	setup(GuiDialog::DEFAULT_WIN_CLASS, L"", WS_CAPTION | WS_POPUP | WS_SYSMENU);
}

void GuiDialog::setTitle(LPCWSTR title)
{
	SetWindowText(hwnd, title);
}

HWND GuiDialog::create(HINSTANCE hInstance, HWND parent)
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

void GuiDialog::onExit()
{
	// Do Nothing
}

bool GuiDialog::registerWindowsClass(HINSTANCE hInstance)
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