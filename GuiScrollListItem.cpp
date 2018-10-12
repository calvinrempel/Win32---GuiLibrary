#include "GuiScrollListItem.h"

#include "GuiScrollList.h"

GuiScrollListItem::GuiScrollListItem(GuiScrollList *parent)
	: list(parent)
{
	yPos = 0;
	height = 0;
}

GuiScrollListItem::~GuiScrollListItem()
{

}

void GuiScrollListItem::move(int newY)
{
	yPos = newY;
}

void GuiScrollListItem::setHeight(int newHeight)
{
	height = newHeight;
}

int GuiScrollListItem::getY()
{
	return yPos;
}

int GuiScrollListItem::getHeight()
{
	return height;
}