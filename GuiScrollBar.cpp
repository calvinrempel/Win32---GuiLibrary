#include "GuiScrollBar.h"


GuiScrollBar::GuiScrollBar(HINSTANCE hInstance, GuiComponent *parent)
	: GuiPanel(hInstance, parent)
{
	inactivePen = (HPEN)GetStockObject(WHITE_PEN);
	activePen = (HPEN)GetStockObject(BLACK_PEN);
	inactiveBrush = (HBRUSH)GetStockObject(DKGRAY_BRUSH);
	activeBrush = (HBRUSH)GetStockObject(LTGRAY_BRUSH);
	active = false;
	listener = NULL;
	enableCustomDrawing(true);

	this->addMessageListener(WM_ERASEBKGND, GuiScrollBar::overrideEraseBckgnd, this);
	this->addMessageListener(WM_PAINT, GuiScrollBar::paint, this);
	this->addMessageListener(WM_LBUTTONDOWN, GuiScrollBar::onClick, this);
	this->addMessageListener(WM_LBUTTONUP, GuiScrollBar::onClickUp, this);
	this->addMessageListener(WM_MOUSEMOVE, GuiScrollBar::onMouseMove, this);
	this->addMessageListener(WM_MOUSELEAVE, GuiScrollBar::onMouseLeave, this);
}

GuiScrollBar::~GuiScrollBar()
{
}

void GuiScrollBar::setColours(HPEN inactiveBorder, HBRUSH inactive, HPEN activeBorder, HBRUSH active)
{
	inactivePen = (inactiveBorder == NULL) ? inactivePen : inactiveBorder;
	activePen = (activeBorder == NULL) ? activePen : activeBorder;
	inactiveBrush = (inactive == NULL) ? inactiveBrush : inactive;
	activeBrush = (active == NULL) ? activeBrush : active;
}

void GuiScrollBar::setHorizontal(bool isHorizontal)
{
	horizontal = isHorizontal;
}

void GuiScrollBar::setTrackPosition(double percent)
{
	currentPosition = percent;

	// Call callback if set
	if (listener)
	{
		listener->onScroll(percent);
	}
}

void GuiScrollBar::setContentSize(double size)
{
	contentSize = size;
	InvalidateRect(getHWND(), NULL, FALSE);
}

void GuiScrollBar::setListener(IGuiScrollBarListener *listener)
{
	this->listener = listener;
}

double GuiScrollBar::getContentSize()
{
	return contentSize;
}

double GuiScrollBar::getCurrentPosition()
{
	return currentPosition;
}

bool GuiScrollBar::overrideEraseBckgnd(GuiComponent *pThis, UINT command, UINT id, WPARAM wParam, LPARAM lParam, INT_PTR *retval)
{
	*retval = 1;
	return true;
}

bool GuiScrollBar::paint(GuiComponent *pThis, UINT command, UINT id, WPARAM wParam, LPARAM lParam, INT_PTR *retval)
{
	PAINTSTRUCT ps;
	HDC hdc = BeginPaint(pThis->getHWND(), &ps);

	GuiScrollBar *scrollbar = (GuiScrollBar*)pThis;
	scrollbar->calculateTrackerSize();

	// Draw Background
	SelectObject(hdc, scrollbar->backgroundBrush);
	SelectObject(hdc, scrollbar->borderPen);
	Rectangle(hdc, 0, 0, scrollbar->getWidth(), scrollbar->getHeight());

	if (!(scrollbar->trackerRect.top <= 0 && scrollbar->trackerRect.bottom >= scrollbar->getHeight()))
	{
		// Select correct colours
		if (scrollbar->active)
		{
			SelectObject(hdc, scrollbar->activeBrush);
			SelectObject(hdc, scrollbar->activePen);
		}
		else
		{
			SelectObject(hdc, scrollbar->inactiveBrush);
			SelectObject(hdc, scrollbar->inactivePen);
		}

		// Draw the correct trackers
		LPRECT rect = &scrollbar->trackerRect;
		Rectangle(hdc, rect->left, rect->top, rect->right, rect->bottom);
	}

	EndPaint(pThis->getHWND(), &ps);

	return true;
}

bool GuiScrollBar::onClick(GuiComponent *pThis, UINT command, UINT id, WPARAM wParam, LPARAM lParam, INT_PTR *retval)
{
	GuiScrollBar *scrollbar = (GuiScrollBar*)pThis;
	scrollbar->active = true;

	if (scrollbar->horizontal)
	{
		scrollbar->clickOffset = scrollbar->trackerRect.left - LOWORD(lParam);
	}
	else
	{
		scrollbar->clickOffset = scrollbar->trackerRect.top - HIWORD(lParam);
	}

	InvalidateRect(scrollbar->getHWND(), NULL, FALSE);

	return true;
}

bool GuiScrollBar::onClickUp(GuiComponent *pThis, UINT command, UINT id, WPARAM wParam, LPARAM lParam, INT_PTR *retval)
{
	GuiScrollBar *scrollbar = (GuiScrollBar*)pThis;
	scrollbar->active = false;
	InvalidateRect(scrollbar->getHWND(), NULL, FALSE);

	return true;
}

bool GuiScrollBar::onMouseMove(GuiComponent *pThis, UINT command, UINT id, WPARAM wParam, LPARAM lParam, INT_PTR *retval)
{
	GuiScrollBar *scrollbar = (GuiScrollBar*)pThis;
	double percent;
	LPRECT rect = &scrollbar->trackerRect;

	if (scrollbar->active)
	{
		if (scrollbar->horizontal)
		{
			int x = LOWORD(lParam) + scrollbar->clickOffset;
			percent = ((double) x) / (scrollbar->getWidth() - (rect->right - (rect->left)));
		}
		else
		{
			int y = HIWORD(lParam) + scrollbar->clickOffset;
			int offset = rect->top - y;
			percent = ((double) y) / (scrollbar->getHeight() - (rect->bottom - rect->top));
		}

		// Constrain the tracker to the scroll bar.
		percent = (percent < 0) ? 0 : percent;
		percent = (percent > 1) ? 1 : percent;

		scrollbar->setTrackPosition(percent);
		InvalidateRect(scrollbar->getHWND(), NULL, FALSE);
	}

	return false;
}

bool GuiScrollBar::onMouseLeave(GuiComponent *pThis, UINT command, UINT id, WPARAM wParam, LPARAM lParam, INT_PTR *retval)
{
	return true;
}

void GuiScrollBar::calculateTrackerSize()
{
	double percentageSize;
	double pixelSize;
	
	if (contentSize == 0)
		return;

	if (horizontal)
	{
		percentageSize = 1 - (getWidth() / contentSize);
		trackerRect.left = (getWidth() - (percentageSize * getWidth())) * currentPosition;
		trackerRect.right = trackerRect.left + percentageSize * getWidth();
		trackerRect.top = 0;
		trackerRect.bottom = getHeight();
	}
	else
	{
		percentageSize = (getHeight() / contentSize);
		pixelSize = percentageSize * getHeight();
		trackerRect.left = 0;
		trackerRect.right = getWidth();
		trackerRect.top = (getHeight() - (percentageSize * getHeight())) * currentPosition;
		trackerRect.bottom = trackerRect.top + pixelSize;
	}

	if (percentageSize >= 1)
		setPreferredSize(1, 0);
	else
		setPreferredSize(16, 0);
}