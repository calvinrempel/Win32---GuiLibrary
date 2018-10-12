#include "GuiPanel.h"


const LPCWSTR GuiPanel::DEFAULT_WIN_CLASS = L"GUI_PANEL_CLASS";

GuiPanel::GuiPanel(HINSTANCE hInstance, GuiComponent *parent)
	: GuiComponent(hInstance, parent)
{
	setup(DEFAULT_WIN_CLASS, L"", WS_CHILD | WS_VISIBLE | SS_NOTIFY);
	addMessageListener(WM_CTLCOLORSTATIC, GuiPanel::handleCTLCOLORSTATIC, this);
}

HWND GuiPanel::create(HINSTANCE hInstance, HWND parent)
{
	// If the Windows Class is not registered, end with error
	if (!registerWindowsClass(hInstance))
		return NULL;

	// Attempt to Create the new Window
	return CreateWindowEx(WS_EX_COMPOSITED, 
					      windowClass,
						  L"",
						  windowStyles,
						  0, 0,
						  0, 0,
						  parent, NULL, hInstance, NULL);
}

bool GuiPanel::registerWindowsClass(HINSTANCE hInstance)
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
	Wcl.hbrBackground = CreateSolidBrush(RGB(240, 240, 240)); //white background
	Wcl.lpszClassName = windowClass; // user defined menu

	Wcl.lpszMenuName = menuClass; // user defined menu 
	Wcl.cbClsExtra = 0;      // no extra memory needed
	Wcl.cbWndExtra = 0;

	// Register the class
	if (!RegisterClassEx(&Wcl))
		return false;

	return true;
}

bool GuiPanel::handleCTLCOLORSTATIC(GuiComponent *pThis, UINT command, UINT id, WPARAM wParam, LPARAM lParam, INT_PTR *retval)
{
	*retval = (INT_PTR) pThis->getBackgroundBrush();

	return true;
}