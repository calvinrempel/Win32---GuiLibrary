#ifndef _GUI_STATUS_BAR_H_
#define _GUI_STATUS_BAR_H_

#include "GuiComponent.h"

class GuiStatusBar : public GuiComponent
{
public:
	GuiStatusBar(HINSTANCE hInstance, GuiComponent *parent)
		: GuiComponent(hInstance, parent){};

	void setParts(int numParts, int *partSizes);
	void setText(int partIndex, LPWSTR text);
	virtual HWND create(HINSTANCE hInstance, HWND parent);
	virtual void resize();
};

#endif