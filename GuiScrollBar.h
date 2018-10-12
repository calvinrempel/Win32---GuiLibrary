#ifndef _GUI_SCROLL_BAR_H_
#define _GUI_SCROLL_BAR_H_

#include "GuiPanel.h"

/*
 * A IGuiScrollBarListener implements behaviour that occurs when a ScrollBar is moved.
 */
class IGuiScrollBarListener
{
public:
	virtual void onScroll(double percent) = 0;
};

/*
 * A GuiScrollBar is a GuiComponent that acts as a scrollbar.
 */
class GuiScrollBar : public GuiPanel
{
public:
	GuiScrollBar(HINSTANCE hInstance, GuiComponent *parent);
	virtual ~GuiScrollBar();

	void setColours(HPEN inactiveBorder, HBRUSH inactive, HPEN activeBorder, HBRUSH active);
	void setHorizontal(bool isHorizontal);
	void setTrackPosition(double percent);
	void setContentSize(double size);
	void setListener(IGuiScrollBarListener *listener);
	double getContentSize();
	double getCurrentPosition();

private:
	static bool overrideEraseBckgnd(GuiComponent *pThis, UINT command, UINT id, WPARAM wParam, LPARAM lParam, INT_PTR *retval);
	static bool paint(GuiComponent *pThis, UINT command, UINT id, WPARAM wParam, LPARAM lParam, INT_PTR *retval);
	static bool onClick(GuiComponent *pThis, UINT command, UINT id, WPARAM wParam, LPARAM lParam, INT_PTR *retval);
	static bool onClickUp(GuiComponent *pThis, UINT command, UINT id, WPARAM wParam, LPARAM lParam, INT_PTR *retval);
	static bool onMouseMove(GuiComponent *pThis, UINT command, UINT id, WPARAM wParam, LPARAM lParam, INT_PTR *retval);
	static bool onMouseLeave(GuiComponent *pThis, UINT command, UINT id, WPARAM wParam, LPARAM lParam, INT_PTR *retval);

	void calculateTrackerSize();

	IGuiScrollBarListener *listener;
	bool active;
	bool horizontal;
	double contentSize;
	double currentPosition;
	int clickOffset;
	RECT trackerRect;
	HBRUSH inactiveBrush;
	HPEN inactivePen;
	HBRUSH activeBrush;
	HPEN activePen;
};

#endif