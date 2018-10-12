/*-----------------------------------------------------------------------------
-- SOURCE FILE: GuiDialog.h - This file provides a modal window that acts
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

#ifndef _GUI_DIALOG_H_
#define _GUI_DIALOG_H_

#define WIN32_LEAN_AND_MEAN

#include "GuiComponent.h"

#include "GuiListener.h"

class GuiDialog : public GuiComponent
{
public:
	GuiDialog(HINSTANCE hInstance);
	GuiDialog(HINSTANCE hInstance, GuiComponent *parent);

	void setTitle(LPCWSTR title);
	virtual HWND create(HINSTANCE hInstance, HWND parent);
	virtual void onExit();

private:
	static const LPCWSTR DEFAULT_WIN_CLASS;

	bool registerWindowsClass(HINSTANCE hInstance);
};

#endif