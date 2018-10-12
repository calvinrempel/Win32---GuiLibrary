#include "GuiResizable.h"
#include "GuiLinearLayout.h"

GuiResizable::GuiResizable()
{
	layoutManager = new GuiLinearLayout(this);
}

GuiResizable::~GuiResizable()
{
	delete layoutManager;
}

void GuiResizable::resize()
{
	if (layoutManager && visible)
	{
		layoutManager->resize();
	}
}

void GuiResizable::setLayoutManager(GuiLayoutManager *newLayoutManager)
{
	if (layoutManager)
	{
		layoutManager->transferComponents(newLayoutManager);
		delete layoutManager;
	}

	layoutManager = newLayoutManager;
}

GuiLayoutManager *GuiResizable::getLayoutManager()
{
	return layoutManager;
}

bool GuiResizable::isVisible()
{
	return visible;
}

void GuiResizable::setVisible(bool isVisible)
{
	visible = isVisible;
}