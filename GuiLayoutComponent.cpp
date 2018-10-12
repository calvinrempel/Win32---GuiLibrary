/*-----------------------------------------------------------------------------
-- SOURCE FILE: GuiLayoutComponent.cpp - This file provides an interface
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

#include "GuiLayoutComponent.h"
#include "GuiLayoutManager.h"

GuiLayoutComponent::GuiLayoutComponent()
{
	width = 0;
	height = 0;
	x = 0;
	y = 0;
	parent = NULL;
	hwnd = NULL;
}

GuiLayoutComponent::~GuiLayoutComponent()
{
	// Nothing to do
}

void GuiLayoutComponent::setSize(int width, int height)
{
	this->width = width;
	this->height = height;
}

void GuiLayoutComponent::setPosition(int x, int y)
{
	this->x = x;
	this->y = y;
}

int GuiLayoutComponent::getWidth()
{
	return width;
}

int GuiLayoutComponent::getHeight()
{
	return height;
}

int GuiLayoutComponent::getX()
{
	return x;
}

int GuiLayoutComponent::getY()
{
	return y;
}

void GuiLayoutComponent::addChild(GuiLayoutComponent *component)
{
	if (component->parent != NULL)
	{
		component->parent->removeChild(component);
	}

	components.insert(component);
	component->parent = this;
	component->onSetParent();
}

void GuiLayoutComponent::removeChild(GuiLayoutComponent *component)
{
	std::set<GuiLayoutComponent*>::iterator c;
	c = components.find(component);

	if (c != components.end())
	{
		if ((*c)->parent != NULL && (*c)->parent == this)
		{
			(*c)->parent = NULL;
			(*c)->onSetParent();
		}

		components.erase(c);
	}
}

HWND GuiLayoutComponent::getHWND()
{
	return hwnd;
}
