#include "GuiListBox.h"


GuiListBox::GuiListBox(HINSTANCE hInstance, GuiComponent *parent)
	: GuiComponent(hInstance, parent)
{
	setup(L"", L"", 0);
}

HWND GuiListBox::create(HINSTANCE hInstance, HWND parent)
{
	return CreateWindowEx(WS_EX_COMPOSITED,
						  L"LISTBOX",
						  NULL,
						  WS_CHILD | WS_VISIBLE | ES_AUTOVSCROLL | WS_VSCROLL,
						  0, 0,
						  0, 0,
						  parent, NULL, hInstance, NULL);
}

void GuiListBox::addItem(LPWSTR text, int position)
{
    SendMessage(hwnd, LB_INSERTSTRING, (WPARAM) position, (LPARAM)text);
}

void GuiListBox::removeItem(int n)
{
	SendMessage(hwnd, LB_DELETESTRING, (WPARAM)n, NULL);
}