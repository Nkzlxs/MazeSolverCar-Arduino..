#pragma once

#include <SFML\Graphics.hpp>
#include "Line.h"
#include <vector>
#include "defines.h"

class Cell
{

public:
	sf::RectangleShape a; //a rectangleshape of this cell
	float m_xpos;// x position of this cell
	float m_ypos;// y position of this cell

	
	std::vector<Line> m_sides; //The "sides" of this cell
	
	
	//top left right btm
	bool m_neighbours[4]{ false,false,false,false };//this cell's surrounding neighbours
	
	bool isVisited = false;
	
	bool m_status[4]{ true ,true ,true ,true };//the status of this cell's "side"



	Cell(float xpos, float ypos);
	~Cell();
	void drawRect(sf::Vector2f size);
	void drawRect(sf::Vector2f size, sf::Color c);
	void addNeighbours(bool t, bool l, bool r, bool b);
	void display(sf::RenderWindow &window1);
};

