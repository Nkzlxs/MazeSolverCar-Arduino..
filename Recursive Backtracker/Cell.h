#pragma once

#include <SFML\Graphics.hpp>
#include "Line.h"
#include <vector>
#include "defines.h"

class Cell
{

public:
	sf::RectangleShape a;
	float m_xpos;
	float m_ypos;

	//top left right btm
	std::vector<Line> m_sides;
	short isCorner = 5;
	bool m_neighbours[4]{ false,false,false,false };
	bool isVisited = false;
	bool m_status[4]{ true ,true ,true ,true };



	Cell(float xpos, float ypos);
	~Cell();
	void drawRect(sf::Vector2f size) {
		a.setPosition(sf::Vector2f(m_xpos, m_ypos));
		a.setSize(size);
	}
	void drawRect(sf::Vector2f size,sf::Color c) {
		a.setPosition(sf::Vector2f(m_xpos, m_ypos));
		a.setFillColor(c);
		a.setSize(size);
	}
	void addNeighbours(bool t, bool l, bool r, bool b);

	void display(sf::RenderWindow &window1) {
		for (int i = 0;i < 4; i++) {
			if (!m_status[i])
				m_sides[i] = null;
		}
		for (Line side : m_sides) {
			if (side != null)
				window1.draw(side.m_self);
		}
		window1.draw(a);
	}
};

