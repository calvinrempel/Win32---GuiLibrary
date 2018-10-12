#ifndef _GUI_SCROLL_LIST_PANE_H_
#define _GUI_SCROLL_LIST_PANE_H_

#include "GuiPanel.h"

#include "../common.h"
#include <vector>

class GuiScrollListItem;

class GuiScrollListPane : public GuiPanel
{
public:
	GuiScrollListPane(HINSTANCE hInstance, GuiComponent *parent);
	virtual ~GuiScrollListPane();

	void setVisibleRegion(double top, double bottom);
	void addItem(GuiScrollListItem *item);
	int getTotalHeight();

private:
	static bool overrideEraseBckgnd(GuiComponent *pThis, UINT command, UINT id, WPARAM wParam, LPARAM lParam, INT_PTR *retval);
	static bool paint(GuiComponent *pThis, UINT command, UINT id, WPARAM wParam, LPARAM lParam, INT_PTR *retval);
	static bool onClick(GuiComponent *pThis, UINT command, UINT id, WPARAM wParam, LPARAM lParam, INT_PTR *retval);
	static bool onClickUp(GuiComponent *pThis, UINT command, UINT id, WPARAM wParam, LPARAM lParam, INT_PTR *retval);
	static bool onMouseMove(GuiComponent *pThis, UINT command, UINT id, WPARAM wParam, LPARAM lParam, INT_PTR *retval);

	int getIndexOfFirstInRegion();

	double top;
	double bottom;
	int lastInsertY;
	int totalHeight;
	std::vector<GuiScrollListItem*> items;
};

#endif

