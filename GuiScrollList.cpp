#include "GuiScrollList.h"

#include "GuiScrollBar.h"
#include "GuiLinearLayout.h"
#include "GuiScrollListItem.h"
#include "GuiScrollListPane.h"

GuiScrollList::GuiScrollList(HINSTANCE hInstance, GuiComponent *parent)
	: GuiPanel(hInstance, parent)
{
	enableCustomDrawing(true);
}

GuiScrollList::~GuiScrollList()
{
	delete contentPanel;
	delete scrollbar;
}

void GuiScrollList::onCreate()
{
	GuiLinearLayout *layout = (GuiLinearLayout*)getLayoutManager();
	GuiLinearLayout::Properties props;
	layout->zeroProperties(&props);
	layout->setHorizontal(true);

	contentPanel = new GuiScrollListPane(hInst, this);
	contentPanel->init();
	contentPanel->enableCustomDrawing(true);
	contentPanel->setBackgroundBrush(this->getBackgroundBrush());
	contentPanel->setBorderPen(this->getBorderPen());

	scrollbar = new GuiScrollBar(hInst, this);
	scrollbar->init();
	scrollbar->setListener(this);
	scrollbar->setHorizontal(false);
	scrollbar->setContentSize(0);
	scrollbar->setTrackPosition(0);
	scrollbar->setPreferredSize(16,0);

	props.weight = 1;
	layout->addComponent(contentPanel, &props);
	layout->addComponent(scrollbar);
}

void GuiScrollList::onScroll(double percent)
{
	int top = this->getScrollBar()->getCurrentPosition() * (contentPanel->getTotalHeight() - getHeight());
	contentPanel->setVisibleRegion(top, top + getHeight());
}

void GuiScrollList::addItem(GuiScrollListItem *item)
{
	contentPanel->addItem(item);
	scrollbar->setContentSize(scrollbar->getContentSize() + item->getHeight());
}

void GuiScrollList::setBackgroundBrush(HBRUSH brush)
{
	this->backgroundBrush = brush;
	this->contentPanel->setBackgroundBrush(brush);
}

void GuiScrollList::setBorderPen(HPEN pen)
{
	this->borderPen = pen;
	this->contentPanel->setBorderPen(pen);
}

GuiScrollBar *GuiScrollList::getScrollBar()
{
	return scrollbar;
}

void GuiScrollList::resize()
{
	GuiPanel::resize();

	double scrollPos = this->getScrollBar()->getCurrentPosition();
	double contentHeight = contentPanel->getTotalHeight();
	double myHeight = getHeight();

	int top = this->getScrollBar()->getCurrentPosition() * (contentPanel->getTotalHeight() - getHeight());
	contentPanel->setVisibleRegion(top, top + getHeight());
}