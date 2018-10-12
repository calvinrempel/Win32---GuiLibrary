#ifndef _GUI_PROGRESS_BAR_H_
#define _GUI_PROGRESS_BAR_H_

#include "GuiComponent.h"

class GuiProgressBar : public GuiComponent
{
public:
	GuiProgressBar(HINSTANCE hInstance, GuiComponent *parent)
		: GuiComponent(hInstance, parent){};

	void setCompletion(int position);
	virtual HWND create(HINSTANCE hInstance, HWND parent);
};

#endif