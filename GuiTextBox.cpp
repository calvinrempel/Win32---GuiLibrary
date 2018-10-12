/*-----------------------------------------------------------------------------
-- SOURCE FILE: GuiTextBox.cpp - This file provides a specialized GUI element
-- that draws a Text Input Field.
--
-- REVISIONS:
--
-- DESIGNER: Calvin Rempel
--
-- PROGRAMMER: Calvin Rempel
--
-- NOTES:
-----------------------------------------------------------------------------*/

#include "GuiTextBox.h"

GuiTextBox::~GuiTextBox()
{
	delete buffer;
}

GuiTextBox::GuiTextBox(HINSTANCE hInstance, GuiComponent *parent, bool multiline)
	: GuiComponent(hInstance, parent)
{
	editable = true;
	buffer = NULL;
	bufferLength = -1;
	DWORD style = WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL;

	if (multiline)
	{
		style = WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE
				| ES_AUTOVSCROLL | WS_VSCROLL;
	}

	setup(L"EDIT", L"", style);
}


void GuiTextBox::setEditable(bool editable)
{
	if (this->editable == editable)
		return;

	this->editable = editable;
	SendMessage(hwnd, EM_SETREADONLY, (WPARAM) !editable, NULL);
}

void GuiTextBox::setText(LPWSTR text)
{
	SendMessage(hwnd, WM_SETTEXT, NULL, (LPARAM) text);
}

void GuiTextBox::appendText(LPWSTR text)
{
	int index = GetWindowTextLength(hwnd);
	SendMessage(hwnd, EM_SETSEL, (WPARAM)index, (LPARAM)index);
	SendMessage(hwnd, EM_REPLACESEL, NULL, (LPARAM)text);
}

LPWSTR GuiTextBox::getText()
{
	int requiredLength = getTextLength() + 1;
	
	if (requiredLength > bufferLength)
	{
		if (buffer != NULL)
		{
			delete buffer;
		}

		buffer = new WCHAR[requiredLength];
		bufferLength = requiredLength;
	}

	GetWindowText(hwnd, buffer, bufferLength);

	return buffer;
}

int GuiTextBox::getTextLength()
{
	return GetWindowTextLength(hwnd);
}

HWND GuiTextBox::create(HINSTANCE hInstance, HWND parent)
{
	return CreateWindowEx(WS_EX_COMPOSITED,this->windowClass, NULL,
						this->windowStyles,
						0, 0, 0, 0, parent, NULL,
						hInstance, NULL);
}
