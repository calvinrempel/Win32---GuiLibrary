#ifndef _GUI_LISTENER_H_
#define _GUI_LISTENER_H_

#include "../common.h"

class GuiComponent;

typedef bool(*GuiListener)(GuiComponent *pThis,
						   UINT command,
						   UINT id,
						   WPARAM wParam,
						   LPARAM lParam,
						   INT_PTR *retval);

#endif
