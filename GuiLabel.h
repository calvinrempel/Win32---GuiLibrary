/*-----------------------------------------------------------------------------
-- SOURCE FILE: GuiLabel.h - This file provides a static window that displays
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

#ifndef _GUI_LABEL_H_
#define _GUI_LABEL_H_

#include "GuiComponent.h"

class GuiLabel : public GuiComponent
{
public:
	GuiLabel(HINSTANCE hInstance, GuiComponent *parent);

	void setText(LPWSTR text);
	void setFontSize(int fontSize);
	virtual HWND create(HINSTANCE hInstance, HWND parent);

private:
	static const LPCWSTR DEFAULT_WINDOW_CLASS;
	static bool handleCTLCOLORSTATIC(GuiComponent *pThis, UINT command, UINT id, WPARAM wParam, LPARAM lParam, INT_PTR *retval);
};


#endif