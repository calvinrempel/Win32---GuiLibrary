#include "GuiScrollListPane.h"

#include "GuiScrollListItem.h"


GuiScrollListPane::GuiScrollListPane(HINSTANCE hInstance, GuiComponent *parent)
	: GuiPanel(hInstance, parent)
{
	this->addMessageListener(WM_ERASEBKGND, GuiScrollListPane::overrideEraseBckgnd, this);
	this->addMessageListener(WM_PAINT, GuiScrollListPane::paint, this);
	this->addMessageListener(WM_LBUTTONUP, GuiScrollListPane::onClickUp, this);
	this->addMessageListener(WM_MOUSEMOVE, GuiScrollListPane::onMouseMove, this);
}

GuiScrollListPane::~GuiScrollListPane()
{
	for (int i = 0; i < items.size(); i++)
	{
		delete items[i];
	}
}

void GuiScrollListPane::setVisibleRegion(double top, double bottom)
{
	this->top = top;
	this->bottom = bottom;
	InvalidateRect(getHWND(), NULL, false);
}

void GuiScrollListPane::addItem(GuiScrollListItem *item)
{
	if (items.empty())
	{
		items.push_back(item);
		totalHeight = item->getHeight();
		lastInsertY = totalHeight;
		item->move(0);
	}
	else
	{
		items.push_back(item);
		totalHeight += item->getHeight();
		lastInsertY += totalHeight;
		item->move(totalHeight - item->getHeight());
	}
}

int GuiScrollListPane::getTotalHeight()
{
	return totalHeight;
}

bool GuiScrollListPane::onClickUp(GuiComponent *pThis, UINT command, UINT id, WPARAM wParam, LPARAM lParam, INT_PTR *retval)
{
	GuiScrollListPane *pane = (GuiScrollListPane*)pThis;

	int x = LOWORD(lParam);
	int y = HIWORD(lParam);

	// Find the item that was clicked
	int first = pane->getIndexOfFirstInRegion();
	RECT rect;
	rect.left = 0;
	rect.right = pane->getWidth();

	for (int i = 0; i < pane->items.size(); i++)
	{
		// Calculate the item rectangle
		rect.top = pane->items[i]->getY() - pane->top;
		rect.bottom = rect.top + pane->items[i]->getHeight();

		// If clicked inside this item send click message
		if (y > rect.top && y < rect.bottom)
		{
			// Get translated y
			y = y - rect.top;

			pane->items[i]->onClick(x, y);
			break;
		}

		// If we are past the end of the list, stop drawing.
		if (rect.top >= pane->bottom)
		{
			break;
		}
	}

	return true;
}

bool GuiScrollListPane::onMouseMove(GuiComponent *pThis, UINT command, UINT id, WPARAM wParam, LPARAM lParam, INT_PTR *retval)
{
	GuiScrollListPane *pane = (GuiScrollListPane*)pThis;

	int x = LOWORD(lParam);
	int y = HIWORD(lParam);

	// Find the item that was clicked
	int first = pane->getIndexOfFirstInRegion();
	RECT rect;
	rect.left = 0;
	rect.right = pane->getWidth();

	for (int i = 0; i < pane->items.size(); i++)
	{
		// Calculate the item rectangle
		rect.top = pane->items[i]->getY() - pane->top;
		rect.bottom = rect.top + pane->items[i]->getHeight();

		// If clicked inside this item send click message
		if (y > rect.top && y < rect.bottom)
		{
			// Get translated y
			y = y - rect.top;

			pane->items[i]->onMouseMove(x, y);
			break;
		}

		// If we are past the end of the list, stop drawing.
		if (rect.top >= pane->bottom)
		{
			break;
		}
	}

	return false;
}


bool GuiScrollListPane::overrideEraseBckgnd(GuiComponent *pThis, UINT command, UINT id, WPARAM wParam, LPARAM lParam, INT_PTR *retval)
{
	*retval = 1;
	return true;
}

bool GuiScrollListPane::paint(GuiComponent *pThis, UINT command, UINT id, WPARAM wParam, LPARAM lParam, INT_PTR *retval)
{
	PAINTSTRUCT ps;
	HDC hdc = BeginPaint(pThis->getHWND(), &ps);

	GuiScrollListPane *pane = (GuiScrollListPane*)pThis;

	// Draw Background
	SelectObject(hdc, pThis->getBackgroundBrush());
	SelectObject(hdc, pThis->getBorderPen());
	Rectangle(hdc, 0, 0, pThis->getWidth(), pThis->getHeight());


	// Draw Visible Region
	int first = pane->getIndexOfFirstInRegion();
	RECT rect;
	rect.left = 0;
	rect.right = pane->getWidth();

	for (int i = 0; i < pane->items.size(); i++)
	{
		// Calculate the drawable rectangle
		rect.top = pane->items[i]->getY() - pane->top;
		rect.bottom = rect.top + pane->items[i]->getHeight();

		// If we are past the end of the list, stop drawing.
		if (rect.top >= pane->bottom)
		{
			break;
		}

		pane->items[i]->paint(hdc, &rect);
	}

	EndPaint(pThis->getHWND(), &ps);

	return true;
}

int GuiScrollListPane::getIndexOfFirstInRegion()
{
	GuiScrollListItem *item;
	int y1, y2;

	for (int i = 0; i < items.size(); i++)
	{
		item = items[i];
		y1 = item->getY();
		y2 = y1 + item->getHeight();

		if ((y1 < top && y2 > top) || (y1 >= top && y1 < bottom))
		{
			return i;
		}
	}

	return -1;
}