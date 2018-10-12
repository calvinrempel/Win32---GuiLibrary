/*-----------------------------------------------------------------------------
-- SOURCE FILE: GuiLayoutManager.cpp - This file provides a layout manager
-- that arranges all children in a line, horizontally or vertically.
--
-- REVISIONS:
--
-- DESIGNER: Calvin Rempel
--
-- PROGRAMMER: Calvin Rempel
--
-- NOTES:
-----------------------------------------------------------------------------*/

#include "GuiLinearLayout.h"

#include "GuiResizable.h"

void GuiLinearLayout::setHorizontal(bool horizontal)
{
	this->horizontal = horizontal;
}

void GuiLinearLayout::zeroProperties(GuiLinearLayout::Properties *properties)
{
	properties->weight = 0;
	properties->topMargin = 0;
	properties->bottomMargin = 0;
	properties->leftMargin = 0;
	properties->rightMargin = 0;
}

void GuiLinearLayout::resize()
{
	double totalWeights = 0;
	int containerWidth = container->getWidth();
	int containerHeight = container->getHeight();
	std::list<GuiLinearLayout::Properties>::iterator itr;

	// Resize components that don't affect or aren't affected by the container components
	resizeExternalComponents();

	// Calculate the total weights of all components
	for (itr = components.begin(); itr != components.end(); itr++)
	{
		// If the component is invisible, don't calculate it
		if (!(*itr).resizable->isVisible())
			continue;

		// If the layout is horizontal and a preffered width is set, shrink the layout space
		if (horizontal && (*itr).resizable->getPreferredWidth() != 0)
		{
			containerWidth -= (*itr).resizable->getPreferredWidth();
		}
		// If the layout is vertical and a preffered height is set, shrink the layout space
		else if (!horizontal && (*itr).resizable->getPreferredHeight() != 0)
		{
			containerHeight -= (*itr).resizable->getPreferredHeight();
		}
		// If no preferred size is set, add to weights
		else
		{
			totalWeights += (*itr).weight;
		}
	}

	int x, y, width, height, totalRequestedSize;
	int offsetAccumulator = 0;
	GuiLinearLayout::Properties *props;

	// Resize each component proprtionally to their weight
	for (itr = components.begin(); itr != components.end(); itr++)
	{
		// If the component is invisible, don't calculate it
		if (!(*itr).resizable->isVisible())
			continue;

		props = &(*itr);

		if (horizontal)
		{
			if (props->resizable->getPreferredWidth() != 0)
			{
				totalRequestedSize = props->resizable->getPreferredWidth();
			}
			else
			{
				totalRequestedSize = containerWidth * (props->weight / totalWeights);
			}

			width = totalRequestedSize - (props->leftMargin + props->rightMargin);
			height = containerHeight - (props->topMargin + props->bottomMargin);
			x = offsetAccumulator + props->leftMargin;
			y = props->topMargin;

			offsetAccumulator += totalRequestedSize;
		}
		else
		{
			if (props->resizable->getPreferredHeight() != 0)
			{
				totalRequestedSize = props->resizable->getPreferredHeight();
			}
			else
			{
				totalRequestedSize = containerHeight * (props->weight / totalWeights);
			}

			width = containerWidth - (props->leftMargin + props->rightMargin);
			height = totalRequestedSize - (props->topMargin + props->bottomMargin);
			x = props->leftMargin;
			y = offsetAccumulator + props->topMargin;

			offsetAccumulator += totalRequestedSize;
		}

		props->resizable->setSize(width, height);
		props->resizable->setPosition(x, y);
		props->resizable->resize();
	}
}

void GuiLinearLayout::addComponent(GuiResizable *guiComponent)
{
	GuiLinearLayout::Properties props;
	props.weight = 1;
	props.leftMargin = 0;
	props.rightMargin = 0;
	props.topMargin = 0;
	props.bottomMargin = 0;

	this->addComponent(guiComponent, &props);
}

void GuiLinearLayout::addComponent(GuiResizable *guiComponent, GuiLinearLayout::Properties *props)
{
	GuiLinearLayout::Properties properties;
	properties.resizable = guiComponent;
	properties.weight = props->weight;
	properties.leftMargin = props->leftMargin;
	properties.rightMargin = props->rightMargin;
	properties.topMargin = props->topMargin;
	properties.bottomMargin = props->bottomMargin;

	components.push_back(properties);
}

void GuiLinearLayout::removeComponent(GuiResizable *guiComponent)
{
	std::list<GuiLinearLayout::Properties>::iterator itr;

	itr = components.begin();
	while (itr != components.end())
	{
		if ((*itr).resizable == guiComponent)
		{
			components.erase(itr);
			break;
		}

		itr++;
	}
}

void GuiLinearLayout::transferComponents(GuiLayoutManager *layoutManager)
{
	std::list<GuiLinearLayout::Properties>::iterator itr;

	for (itr = components.begin(); itr != components.end(); itr++)
	{
		layoutManager->addComponent((*itr).resizable);
	}
}