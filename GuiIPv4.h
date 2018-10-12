/*-----------------------------------------------------------------------------
-- SOURCE FILE: GuiIPv4.h - This file provides a text input that accepts
-- IPv4 addresses.
--
-- REVISIONS:
--
-- DESIGNER: Calvin Rempel
--
-- PROGRAMMER: Calvin Rempel
--
-- NOTES:
-----------------------------------------------------------------------------*/

#ifndef _GUI_IPV4_H_
#define _GUI_IPV4_H_

#include "GuiComponent.h"
class GuiIPv4 :
	public GuiComponent
{
public:
	GuiIPv4(HINSTANCE hInstance, GuiComponent *parent);
	~GuiIPv4();

	LPWSTR getText();
	bool isValidAddress();
	virtual HWND create(HINSTANCE hInstance, HWND parent);

private:
	static const int BUFFER_LENGTH;
	LPWSTR buffer;
};

#endif