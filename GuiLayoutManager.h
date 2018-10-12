/*-----------------------------------------------------------------------------
-- SOURCE FILE: GuiLayoutManager.h - This file provides an interface
-- for a generic object that arranges Windows in Windows.
--
-- REVISIONS:
--
-- DESIGNER: Calvin Rempel
--
-- PROGRAMMER: Calvin Rempel
--
-- NOTES:
-----------------------------------------------------------------------------*/

#ifndef _GUI_LAYOUT_MANAGER_H_
#define _GUI_LAYOUT_MANAGER_H_

#include <set>

using std::set;

class GuiResizable;

class GuiLayoutManager
{
public:
	GuiLayoutManager(GuiResizable *guiContainer) : container(guiContainer){};
	virtual ~GuiLayoutManager(){};

	virtual void resize() = 0;
	virtual void addComponent(GuiResizable *guiComponent) = 0;
	virtual void removeComponent(GuiResizable *guiComponent) = 0;
	virtual void transferComponents(GuiLayoutManager *layoutManager) = 0;

	void addExternalComponent(GuiResizable *guiComponent);
	void resizeExternalComponents();

protected:
	GuiResizable *container;
	set<GuiResizable*> externalComponents;
};

#endif