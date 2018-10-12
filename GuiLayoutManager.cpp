/*-----------------------------------------------------------------------------
-- SOURCE FILE: GuiLayoutManager.cpp - This file provides an interface
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

#include "GuiLayoutManager.h"
#include "GuiResizable.h"

void GuiLayoutManager::addExternalComponent(GuiResizable *guiComponent)
{
	externalComponents.insert(guiComponent);
}

void GuiLayoutManager::resizeExternalComponents()
{
	set<GuiResizable*>::iterator itr;

	for (itr = externalComponents.begin(); itr != externalComponents.end(); itr++)
	{
		(*itr)->resize();
	}
}