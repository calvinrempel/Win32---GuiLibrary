#ifndef _GUI_SCROLL_LIST_H_
#define _GUI_SCROLL_LIST_H_

#include "GuiPanel.h"
#include "GuiScrollBar.h"
#include <vector>

class GuiScrollListItem;
class GuiScrollListPane;

class GuiScrollList : public GuiPanel, IGuiScrollBarListener
{
public:
	GuiScrollList(HINSTANCE hInstance, GuiComponent *parent);
	virtual ~GuiScrollList();

	virtual void onCreate();
	virtual void onScroll(double percent);
	void addItem(GuiScrollListItem *item);

	virtual void setBackgroundBrush(HBRUSH brush);
	virtual void setBorderPen(HPEN pen);
	
	GuiScrollBar *getScrollBar();
	virtual void resize();

private:
	static bool overrideEraseBckgnd(GuiComponent *pThis, UINT command, UINT id, WPARAM wParam, LPARAM lParam, INT_PTR *retval);
	static bool paint(GuiComponent *pThis, UINT command, UINT id, WPARAM wParam, LPARAM lParam, INT_PTR *retval);

	GuiScrollBar *scrollbar;
	GuiScrollListPane *contentPanel;
};

#endif