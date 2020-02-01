#pragma once
#include <vector>
#include "Rectangle.h"
#include "Shapes.h"
class Menu
{
public:
	std::vector<mahSpace::Rectangle> buttons;

	void addButton( mahSpace::Rectangle button )
	{
		buttons.push_back( button );
	}

	void initMenu()
	{
		for ( int i = 0; i < buttons.size(); i++ )
		{
			buttons[i].initalizeRectangle();
		}
	}

};

