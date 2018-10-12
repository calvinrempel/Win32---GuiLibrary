#ifndef _GUI_RESIZABLE_H_
#define _GUI_RESIZABLE_H_

class GuiLayoutManager;

class GuiResizable
{
public:
	GuiResizable();
	virtual ~GuiResizable();

	virtual void setSize(int width, int height) = 0;
	virtual void setPosition(int x, int y) = 0;

	virtual int getWidth() = 0;
	virtual int getHeight() = 0;
	virtual int getX() = 0;
	virtual int getY() = 0;
	virtual int getPreferredWidth() = 0;
	virtual int getPreferredHeight() = 0;

	virtual void resize();
	virtual void setVisible(bool isVisible);
	void setLayoutManager(GuiLayoutManager *newLayoutManager);
	GuiLayoutManager *getLayoutManager();

	bool isVisible();

protected:
	GuiLayoutManager *layoutManager;
	bool visible;
};

#endif