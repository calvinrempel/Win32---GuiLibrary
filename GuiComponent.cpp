/*-----------------------------------------------------------------------------
-- SOURCE FILE: GuiComponent.cpp - This file provides a base Gui Element that
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

#include "GuiComponent.h"
#include "GuiListener.h"
#include "GuiLayoutManager.h"

GuiComponent::GuiComponent(HINSTANCE hInstance)
{
	hInst = hInstance;
	parent = NULL;
	initialized = false;
	enforceMinSize = true;

	enforceMaxSize = false;
	preferredHeight = 0;
	preferredWidth = 0;
}

GuiComponent::GuiComponent(HINSTANCE hInstance, GuiLayoutComponent *parent)
{
	hInst = hInstance;
	this->parent = parent;
	initialized = false;
	enforceMinSize = true;
	enforceMaxSize = false;
	preferredHeight = 0;
	preferredWidth = 0;
}

GuiComponent::~GuiComponent()
{
	// Do Nothing
}

void GuiComponent::setup(LPCWSTR winClass, LPCWSTR menuClass, DWORD winStyle)
{
	if (initialized)
	{
		#ifdef DEBUG
		MessageBox(NULL, L"Component already initialized.", L"Internal Error", MB_ICONERROR);
		#endif
		return;
	}

	drawCustom = false;
	backgroundBrush = (HBRUSH) GetStockObject(WHITE_BRUSH);
	borderPen = (HPEN)GetStockObject(WHITE_PEN);
	this->windowClass = winClass;
	this->menuClass = menuClass;
	this->windowStyles = winStyle;
}

void GuiComponent::setStyles(DWORD winStyles)
{
	if (initialized)
	{
		#ifdef DEBUG
		MessageBox(NULL, L"Component already initialized.", L"Internal Error", MB_ICONERROR);
		#endif
		return;
	}

	windowStyles = winStyles;
}

void GuiComponent::init()
{
	if (initialized)
		return;

	HWND parentHWND = NULL;

	if (parent != NULL && parent->getHWND() != NULL)
		parentHWND = parent->getHWND();

	hwnd = create(hInst, parentHWND);

	if (hwnd != NULL)
	{
		// Associate the Window with this class
		SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)this);
		addMessageListener(WM_PAINT, GuiComponent::drawBackground, this);
		initialized = true;
		onCreate();
	}
}

bool GuiComponent::isInitialized()
{
	return initialized;
}

bool GuiComponent::isClassRegistered()
{
	WNDCLASSEXW wcx;
	return (bool) GetClassInfoEx(hInst, windowClass, &wcx);
}

void GuiComponent::addMessageListener(int message, GuiListener listener, GuiComponent *registrar)
{
	GuiListenerContainer container;
	container.listener = listener;
	container.registrar = registrar;

	messageListeners[message].push_back(container);
}

void GuiComponent::addCommandListener(int command, GuiListener listener, GuiComponent *registrar)
{
	GuiListenerContainer container;
	container.listener = listener;
	container.registrar = registrar;

	commandListeners[command].push_back(container);
}


void GuiComponent::clearMessageListeners(int message)
{
	messageListeners[message].clear();
}

void GuiComponent::clearCommandListeners(int command)
{
	commandListeners[command].clear();
}

bool GuiComponent::triggerMessage(int message, WPARAM wParam, LPARAM lParam, INT_PTR *retval)
{
	map<int, list<GuiListenerContainer>>::iterator handlers = messageListeners.find(message);
	bool fired = false;

	if (handlers != messageListeners.end())
	{
		list<GuiListenerContainer> listeners = handlers->second;
		list<GuiListenerContainer>::iterator itr;

		for (itr = listeners.begin(); itr != listeners.end(); itr++)
		{
			// Allow NULL handlers to prevent propogation
			if ((*itr).listener == NULL)
			{
				fired = true;
			}
			else
			{
				fired = (*itr).listener((*itr).registrar, message, 0, wParam, lParam, retval);
			}

			if (fired)
				return true;
		}
	}

	return false;
}

void GuiComponent::triggerCommand(UINT command, UINT id, LPARAM lParam, INT_PTR *retval)
{
	map<int, list<GuiListenerContainer>>::iterator handlers = commandListeners.find(command);

	if (handlers != commandListeners.end())
	{
		list<GuiListenerContainer> listeners = handlers->second;
		list<GuiListenerContainer>::iterator itr;

		for (itr = listeners.begin(); itr != listeners.end(); itr++)
		{
			(*itr).listener((*itr).registrar, command, id, 0, lParam, retval);
		}
	}
}

void GuiComponent::setVisible(bool visible)
{
	if (visible)
		ShowWindow(hwnd, SW_SHOW);
	else
		ShowWindow(hwnd, SW_HIDE);

	this->visible = visible;
}

void GuiComponent::setEnabled(bool enabled)
{
	EnableWindow(hwnd, enabled);
}

void GuiComponent::enforceMinimumSize(bool enforce)
{
	enforceMinSize = enforce;
}

void GuiComponent::enforceMaximumSize(bool enforce)
{
	enforceMaxSize = enforce;
}

void GuiComponent::enableCustomDrawing(bool enable)
{
	drawCustom = enable;
}

void GuiComponent::setBackgroundBrush(HBRUSH brush)
{
	backgroundBrush = brush;
}

void GuiComponent::setBorderPen(HPEN pen)
{
	borderPen = pen;
}

HBRUSH GuiComponent::getBackgroundBrush()
{
	return backgroundBrush;
}

HPEN GuiComponent::getBorderPen()
{
	return borderPen;
}

void GuiComponent::setPreferredSize(int width, int height)
{
	preferredWidth = width;
	preferredHeight = height;
}

void GuiComponent::setMiniumSize(int width, int height)
{
	minHeight = height;
	minWidth = width;
}

void GuiComponent::setMaximumSize(int width, int height)
{
	maxHeight = height;
	maxWidth = width;
}

void GuiComponent::setSize(int width, int height)
{
	RECT window;
	
	GetClientRect(hwnd, &window);
	MoveWindow(hwnd, window.left, window.top, window.left + width, window.top + height, true);
}

void GuiComponent::setPosition(int x, int y)
{
	RECT window;

	GetClientRect(hwnd, &window);
	MoveWindow(hwnd, x, y, window.right - window.left, window.bottom - window.top, true);
}

int GuiComponent::getX()
{
	RECT rect;
	GetClientRect(hwnd, &rect);

	return rect.left;
}

int GuiComponent::getY()
{
	RECT rect;
	GetClientRect(hwnd, &rect);

	return rect.top;
}

int GuiComponent::getWidth()
{
	RECT rect;
	GetClientRect(hwnd, &rect);

	return rect.right - rect.left;
}

int GuiComponent::getHeight()
{
	RECT rect;
	GetClientRect(hwnd, &rect);

	return rect.bottom - rect.top;
}


int GuiComponent::getPreferredWidth()
{
	return preferredWidth;
}

int GuiComponent::getPreferredHeight()
{
	return preferredHeight;
}

int GuiComponent::getMaxWidth()
{
	return maxWidth;
}

int GuiComponent::getMaxHeight()
{
	return maxHeight;
}

int GuiComponent::getMinWidth()
{
	return minWidth;
}

int GuiComponent::getMinHeight()
{
	return minHeight;
}

void GuiComponent::lpwstrToChar(LPWSTR input, char *output)
{
    size_t useless;
	wcstombs_s(&useless, output, lstrlenW(input)+1, input, lstrlenW(input));
}

void GuiComponent::onSetParent()
{
	HWND parentHWND = NULL;

	if (parent != NULL)
		parentHWND = parent->getHWND();

	SetParent(hwnd, parentHWND);
}

LRESULT CALLBACK GuiComponent::WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	// Get the pointer to the GuiComponent from the Window.
	GuiComponent *pThis = (GuiComponent*) GetWindowLongPtr(hwnd, GWLP_USERDATA);

	// If the GuiComponent isn't set, call the default WndProc
	if (pThis == NULL)
	{
		return DefWindowProc(hwnd, message, wParam, lParam);
	}
	else
	{
		// Dispatch Messages to appropriate handlers
		switch (message)
		{
			// Handle exit specially
			case WM_DESTROY:
				pThis->onExit();
				break;

			case WM_GETMINMAXINFO:
				{
					MINMAXINFO* mmi = (MINMAXINFO*)lParam;

					if (pThis->enforceMaxSize) {
						mmi->ptMaxTrackSize.x = pThis->maxWidth;
						mmi->ptMaxTrackSize.y = pThis->maxHeight;
					}

					if (pThis->enforceMinSize) {
						mmi->ptMinTrackSize.x = pThis->minWidth;
						mmi->ptMinTrackSize.y = pThis->minHeight;
					}
					return 0;
				}
			case WM_SIZE:
			case WM_SIZING:
				pThis->resize();
				break;

			// Process all WM_COMMAND messages through the commandListeners
			case WM_COMMAND:
				{
					INT_PTR retval = 0;
					pThis->triggerCommand(HIWORD(wParam), LOWORD(wParam), lParam, &retval);
					return retval;
				}
				break;

			// Process all other messages through the messageListeners
			default:
				{
					INT_PTR retval = 0;
					if (!pThis->triggerMessage(message, wParam, lParam, &retval))
						return DefWindowProc(hwnd, message, wParam, lParam);
					else
						return retval;
				}
		}
	}

	return 0;
}

bool GuiComponent::drawBackground(GuiComponent *pThis, UINT command, UINT id, WPARAM wParam, LPARAM lParam, INT_PTR *retval)
{
	GuiComponent *component = (GuiComponent*)pThis;

	if (component->drawCustom)
	{
		PAINTSTRUCT ps;
		RECT windowSize, clientRect;
		HDC hdc;

		GetClientRect(component->getHWND(), &clientRect);
		hdc = BeginPaint(component->getHWND(), &ps);

		SelectObject(hdc, component->backgroundBrush);
		SelectObject(hdc, component->borderPen);
		Rectangle(hdc, clientRect.left, clientRect.top, clientRect.right + 1, clientRect.bottom + 1);

		EndPaint(component->getHWND(), &ps);

		return true;
	}

	return false;
}

bool GuiComponent::returnOne(GuiComponent *pThis, UINT command, UINT id, WPARAM wParam, LPARAM lParam, INT_PTR *retval)
{
	*retval = 1;
	return true;
}