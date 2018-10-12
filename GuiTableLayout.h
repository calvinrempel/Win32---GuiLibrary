#ifndef _GUI_TABLE_LAYOUT_H_
#define _GUI_TABLE_LAYOUT_H_

#include "GuiLayoutManager.h"

#include <list>

class GuiTableLayout : public GuiLayoutManager
{
public:
	GuiTableLayout(GuiResizable *guiContainer, int cols);
	virtual ~GuiTableLayout(){};

	void setCellPadding(int horizontal, int vertical);
	void recalculateColumnWidths();
	virtual void resize();

	virtual void addComponent(GuiResizable *guiComponent);
	virtual void removeComponent(GuiResizable *guiComponent);
	virtual void transferComponents(GuiLayoutManager *layoutManager);

private:
	int cols;
	int verticalMargin;
	int horizontalMargin;
	int *colWidths;
	std::list<GuiResizable*> components;
};

#endif