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
