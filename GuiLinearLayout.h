/*-----------------------------------------------------------------------------
-- SOURCE FILE: GuiLayoutManager.h - This file provides a layout manager
-- that arranges all children in a line, horizontally or vertically.
--
-- REVISIONS:
--
-- DESIGNER: Calvin Rempel
--
-- PROGRAMMER: Calvin Rempel
--
-- NOTES:
-----------------------------------------------------------------------------*/

#ifndef _GUI_LINEAR_LAYOUT_H_
#define _GUI_LINEAR_LAYOUT_H_

#include "GuiLayoutManager.h"

#include <list>

class GuiLinearLayout : public GuiLayoutManager
{
public:
	struct Properties {
		GuiResizable *resizable;
		float weight;
		int topMargin;
		int bottomMargin;
		int leftMargin;
		int rightMargin;
	};

	GuiLinearLayout(GuiResizable *guiContainer)
		: GuiLayoutManager(guiContainer), horizontal(true){};
	virtual ~GuiLinearLayout(){};

	void setHorizontal(bool horizontal);
	void zeroProperties(GuiLinearLayout::Properties *properties);

	virtual void resize();

	virtual void addComponent(GuiResizable *guiComponent);
	virtual void addComponent(GuiResizable *guiComponent, GuiLinearLayout::Properties *props);
	virtual void removeComponent(GuiResizable *guiComponent);
	virtual void transferComponents(GuiLayoutManager *layoutManager);

private:
	std::list<GuiLinearLayout::Properties> components;
	bool horizontal;
};

#endif