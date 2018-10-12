/*-----------------------------------------------------------------------------
-- SOURCE FILE: GuiTextBox.h - This file provides a specialized GUI element
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

#ifndef _GUI_TEXT_BOX_H_
#define _GUI_TEXT_BOX_H_

#include "GuiComponent.h"

class GuiTextBox : public GuiComponent
{
public:
	GuiTextBox(HINSTANCE hInstance, GuiComponent *parent, bool multiline);
	virtual ~GuiTextBox();

	void setEditable(bool editable);
	void setText(LPWSTR text);
	void appendText(LPWSTR text);
	LPWSTR getText();
	int getTextLength();
	virtual HWND create(HINSTANCE hInstance, HWND parent);

private:
	bool editable;
	LPWSTR buffer;
	int bufferLength;
};

#endif
