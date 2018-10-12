/*-----------------------------------------------------------------------------
-- SOURCE FILE: GuiLabel.cpp - This file provides a static window that displays
-- text.
--
-- REVISIONS:
--
-- DESIGNER: Calvin Rempel
--
-- PROGRAMMER: Calvin Rempel
--
-- NOTES:
-----------------------------------------------------------------------------*/

#include "GuiLabel.h"

const LPCWSTR GuiLabel::DEFAULT_WINDOW_CLASS = L"STATIC";

GuiLabel::GuiLabel(HINSTANCE hInstance, GuiComponent *parent)
	: GuiComponent(hInstance, parent)
{
	parent->addMessageListener(WM_CTLCOLORSTATIC, GuiLabel::handleCTLCOLORSTATIC, this);
	setup(DEFAULT_WINDOW_CLASS, L"", WS_CHILD | WS_VISIBLE);
}


void GuiLabel::setText(LPWSTR text)
{
	SetWindowText(hwnd, text);

	SIZE labelSize;

	// Resize the label to fit the text
	HDC hdc = GetDC(hwnd);
	GetTextExtentPoint32(hdc, text, wcslen(text), &labelSize);
	setPreferredSize(labelSize.cx, labelSize.cy);
	ReleaseDC(hwnd, hdc);
}

HWND GuiLabel::create(HINSTANCE hInstance, HWND parent)
{
	// Attempt to Create the new Window
	return CreateWindow(windowClass,
		L"",
		windowStyles,
		0, 0,
		0, 0,
		parent, NULL, hInstance, NULL);
}

bool GuiLabel::handleCTLCOLORSTATIC(GuiComponent *pThis, UINT command, UINT id, WPARAM wParam, LPARAM lParam, INT_PTR *retval)
{
	*retval = (INT_PTR)pThis->getBackgroundBrush();

	return true;
}