/*-----------------------------------------------------------------------------
-- SOURCE FILE: GuiComponent.h - This file provides a base Gui Element that
-- all others can build on.
--
-- REVISIONS:
--
-- DESIGNER: Calvin Rempel
--
-- PROGRAMMER: Calvin Rempel
--
-- NOTES:
-----------------------------------------------------------------------------*/

#ifndef _GUI_COMPONENT_H_
#define _GUI_COMPONENT_H_

#define WIN32_LEAN_AND_MEAN

#include "GuiLayoutComponent.h"
#include "GuiListener.h"

#include "../common.h"
#include <map>
#include <list>

using std::map;
using std::list;

class GuiLayoutManager;

class GuiComponent : public GuiLayoutComponent
{
public:
	GuiComponent(HINSTANCE hInstance);
	GuiComponent(HINSTANCE hInstance, GuiLayoutComponent *parent);
	virtual ~GuiComponent();

	void setup(LPCWSTR winClass, LPCWSTR menuClass, DWORD winStyle);
	void setStyles(DWORD winStyles);
	void init();
	bool isInitialized();
	bool isClassRegistered();

	virtual void onCreate(){};
	virtual void onExit(){};

	void addMessageListener(int message, GuiListener listener, GuiComponent *registrar);
	void addCommandListener(int command, GuiListener listener, GuiComponent *registrar);
	void clearMessageListeners(int message);
	void clearCommandListeners(int command);

	bool triggerMessage(int message, WPARAM wParam, LPARAM lParam, INT_PTR *retval);
	void triggerCommand(UINT command, UINT id, LPARAM lParam, INT_PTR *retval);

	void setVisible(bool isVisible);
	void setEnabled(bool enabled);
	void enforceMinimumSize(bool enforce);
	void enforceMaximumSize(bool enforce);

	void enableCustomDrawing(bool enable);
	virtual void setBackgroundBrush(HBRUSH brush);
	virtual void setBorderPen(HPEN pen);
	HBRUSH getBackgroundBrush();
	HPEN getBorderPen();

	void setPreferredSize(int width, int height);
	virtual void setMiniumSize(int width, int height);
	virtual void setMaximumSize(int width, int height);
	virtual void setSize(int width, int height);
	virtual void setPosition(int x, int y);
	virtual int getX();
	virtual int getY();
	virtual int getWidth();
	virtual int getHeight();
	virtual int getPreferredWidth();
	virtual int getPreferredHeight();
	int getMaxWidth();
	int getMaxHeight();
	int getMinWidth();
	int getMinHeight();

	virtual void onSetParent();
	virtual HWND create(HINSTANCE hInstance, HWND parent) = 0;

	static void lpwstrToChar(LPWSTR input, char *output);

	// Define GuiComponent::MENU_COMMAND for Command Listeners
	static const int MENU_COMMAND = 0;
protected:
	LRESULT static CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

	HINSTANCE hInst;
	LPCWSTR windowClass;
	LPCWSTR menuClass;
	DWORD windowStyles;
	int preferredWidth;
	int preferredHeight;
	int maxWidth;
	int maxHeight;
	int minWidth;
	int minHeight;
	bool enforceMinSize;
	bool enforceMaxSize;

	struct GuiListenerContainer {
		GuiListener listener;
		GuiComponent *registrar;
	};

	static bool drawBackground(GuiComponent *pThis, UINT command, UINT id, WPARAM wParam, LPARAM lParam, INT_PTR *retval);
	static bool returnOne(GuiComponent *pThis, UINT command, UINT id, WPARAM wParam, LPARAM lParam, INT_PTR *retval);

	bool initialized;
	bool drawCustom;
	HPEN borderPen;
	HBRUSH backgroundBrush;
	map<int, list<GuiListenerContainer>> messageListeners;
	map<int, list<GuiListenerContainer>> commandListeners;
};

#endif
