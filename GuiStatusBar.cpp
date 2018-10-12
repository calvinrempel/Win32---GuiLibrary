#include "GuiStatusBar.h"
#include <CommCtrl.h>

void GuiStatusBar::setParts(int numParts, int *partSizes)
{
	SendMessage(hwnd, SB_SETPARTS, (WPARAM)numParts, (LPARAM)partSizes);
}

void GuiStatusBar::setText(int partIndex, LPWSTR text)
{
	SendMessage(hwnd, SB_SETTEXT, MAKEWPARAM(partIndex, 0), (LPARAM)text);
}

HWND GuiStatusBar::create(HINSTANCE hInstance, HWND parent)
{
	return CreateWindowEx(0,
						  STATUSCLASSNAME,
						  NULL,
						  WS_CHILD | WS_VISIBLE | SBARS_SIZEGRIP,
						  0, 0, 0, 0,
						  parent, NULL,
						  hInstance, NULL);
}


void GuiStatusBar::resize()
{
	SendMessage(hwnd, WM_SIZE, 0, 0);
}