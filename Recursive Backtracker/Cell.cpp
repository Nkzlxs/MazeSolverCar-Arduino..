#include "Cell.h"

#include "Line.h"
#include <iostream>

Cell::Cell(float xpos, float ypos):m_xpos(xpos),m_ypos(ypos)
{
	this->isVisited = false;
	/*top
	  left
	  right
	  btm
	*/
	if (this->m_status[0])  this->m_sides.push_back(Line(xpos, ypos, w, sf::Color::Black, 1));

	if (this->m_status[1])  this->m_sides.push_back(Line(xpos, ypos, w, sf::Color::Black, 0));

	if (this->m_status[2])  this->m_sides.push_back(Line(xpos + w, ypos, w, sf::Color::Black, 0));

	if (this->m_status[3])  this->m_sides.push_back(Line(xpos, ypos + w, w, sf::Color::Black, 1));

}

Cell::~Cell()
{
}

void Cell::drawRect(sf::Vector2f size)
{
	a.setPosition(sf::Vector2f(m_xpos, m_ypos));
	a.setSize(size);
}

void Cell::drawRect(sf::Vector2f size, sf::Color c)
{
	a.setPosition(sf::Vector2f(m_xpos, m_ypos));
	a.setFillColor(c);
	a.setSize(size);
}

void Cell::addNeighbours(bool t, bool l, bool r, bool b)
{
	
	if (t)
		this->m_neighbours[0] = true;
	if (l)
		this->m_neighbours[1] = true;
	if (r)
		this->m_neighbours[2] = true;
	if (b)
		this->m_neighbours[3] = true;
}

void Cell::display(sf::RenderWindow & window1)
{
	for (int i = 0;i < 4; i++) {
		if (!m_status[i])
			m_sides[i] = null; //setting Line isClear = 0
	}
	for (Line side : m_sides) {
		if (side != null) //if Line isClear = 1 , draw it
			window1.draw(side.m_self);
	}
	window1.draw(a);
}
