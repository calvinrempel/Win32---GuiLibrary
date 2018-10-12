#include "GuiProgressBar.h"
#include <CommCtrl.h>

void GuiProgressBar::setCompletion(int position)
{
	SendMessage(hwnd, PBM_SETPOS, (WPARAM) position, 0);
}

HWND GuiProgressBar::create(HINSTANCE hInstance, HWND parent)
{
	return CreateWindowEx(WS_EX_CLIENTEDGE,
						  PROGRESS_CLASS,
						  NULL,
						  WS_CHILD | WS_VISIBLE | WS_BORDER | PBS_SMOOTH,
						  0, 0, 0, 0,
						  parent, NULL,
						  hInstance, NULL);
}
