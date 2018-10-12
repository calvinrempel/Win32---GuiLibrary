#ifndef _GUI_LISTBOX_H_
#define _GUI_LISTBOX_H_

#include "GuiComponent.h"

class GuiListBox : public GuiComponent
{
public:
	GuiListBox(HINSTANCE hInstance, GuiComponent *parent);

	virtual HWND create(HINSTANCE hInstance, HWND parent);

	void addItem(LPWSTR text, int position);
	void removeItem(int n);
};

#endif