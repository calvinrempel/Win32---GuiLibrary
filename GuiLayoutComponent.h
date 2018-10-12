/*-----------------------------------------------------------------------------
-- SOURCE FILE: GuiLayoutComponent.h - This file provides an interface
-- for components that are able to be resized and laid out in another.
--
-- REVISIONS:
--
-- DESIGNER: Calvin Rempel
--
-- PROGRAMMER: Calvin Rempel
--
-- NOTES:
-----------------------------------------------------------------------------*/

#ifndef _GUI_LAYOUT_COMPONENT_H_
#define _GUI_LAYOUT_COMPONENT_H_

#include "GuiResizable.h"

#include "../common.h"
#include <set>

class GuiLayoutComponent : public GuiResizable
{
public:
	GuiLayoutComponent();
	virtual ~GuiLayoutComponent();

	virtual void setSize(int width, int height);
	virtual void setPosition(int x, int y);

	virtual int getWidth();
	virtual int getHeight();
	virtual int getX();
	virtual int getY();

	virtual void onSetParent(){};

	void addChild(GuiLayoutComponent *component);
	void removeChild(GuiLayoutComponent*component);

	HWND getHWND();

protected:
	int x;
	int y;
	int width;
	int height;
	HWND hwnd;
	GuiLayoutComponent *parent;
	std::set<GuiLayoutComponent*> components;
};

#endif
