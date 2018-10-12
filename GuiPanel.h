#ifndef _GUI_PANEL_H_
#define _GUI_PANEL_H_

#include "GuiComponent.h"

class GuiPanel : public GuiComponent
{
public:
	GuiPanel(HINSTANCE hInstance, GuiComponent *parent);
	virtual HWND create(HINSTANCE hInstance, HWND parent);

private:
	static const LPCWSTR DEFAULT_WIN_CLASS;
	static bool handleCTLCOLORSTATIC(GuiComponent *pThis, UINT command, UINT id, WPARAM wParam, LPARAM lParam, INT_PTR *retval);

	bool registerWindowsClass(HINSTANCE hInstance);
};

#endif