#include "GuiTableLayout.h"
#include "GuiResizable.h"

GuiTableLayout::GuiTableLayout(GuiResizable *guiContainer, int cols)
	: GuiLayoutManager(guiContainer)
{
	this->cols = cols;
	verticalMargin = 0;
	horizontalMargin = 0;
	colWidths = new int[cols];

	for (int i = 0; i < cols; i++)
	{
		colWidths[i] = 0;
	}
}

void GuiTableLayout::setCellPadding(int horizontal, int vertical)
{
	verticalMargin = vertical;
	horizontalMargin = horizontal;
}

void GuiTableLayout::recalculateColumnWidths()
{
	// Reset all Column Widths to 0
	for (int i = 0; i < cols; i++)
	{
		colWidths[i] = 0;
	}

	// Recalculate column widths
	int i = 0;
	std::list<GuiResizable*>::iterator itr;
	for (itr = components.begin(); itr != components.end(); itr++)
	{
		int column = (i % cols);

		if ( (*itr) != NULL && colWidths[column] < (*itr)->getPreferredWidth())
		{
			colWidths[column] = (*itr)->getPreferredWidth();
		}

		i++;
	}
}

void GuiTableLayout::resize()
{
	std::list<GuiResizable*>::iterator itr;
	int rowHeight = 0;
	int y = 0;
	int x = 0;
	int i;
	int column;

	// Resize components that don't affect or aren't affected by the container components
	resizeExternalComponents();

	// Resize all Components
	i = 0;
	for (itr = components.begin(); itr != components.end(); itr++)
	{
		column = (i % cols);

		// Reset row height and x-accumulator at beginning of each row.
		if (column == 0)
		{
			x = 0;
			y += rowHeight + verticalMargin;
			rowHeight = 0;
		}

		// If there is something in the cell, resize it
		if ((*itr) != NULL)
		{
			(*itr)->setSize((*itr)->getPreferredWidth(), (*itr)->getPreferredHeight());
			(*itr)->setPosition(x, y);
			(*itr)->resize();
			
			// Ensure the row is the same height all across
			if ((*itr)->getPreferredHeight() > rowHeight)
				rowHeight = (*itr)->getPreferredHeight();
		}

		// Move the x accumulator for the next cell
		x += colWidths[column] + horizontalMargin;

		i++;
	}
}

void GuiTableLayout::addComponent(GuiResizable *guiComponent)
{
	components.push_back(guiComponent);

	if (guiComponent == NULL)
		return;

	int column = ((components.size() - 1) % cols);

	if (colWidths[column] < guiComponent->getPreferredWidth())
	{
		colWidths[column] = guiComponent->getPreferredWidth();
	}
}

void GuiTableLayout::removeComponent(GuiResizable *guiComponent)
{
	components.remove(guiComponent);
	void recalculateColumnWidths();
}

void GuiTableLayout::transferComponents(GuiLayoutManager *layoutManager)
{
	std::list<GuiResizable*>::iterator itr;

	for (itr = components.begin(); itr != components.end(); itr++)
	{
		layoutManager->addComponent((*itr));
	}
}