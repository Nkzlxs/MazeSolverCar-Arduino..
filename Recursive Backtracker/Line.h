#pragma once

#include <SFML\Graphics.hpp>

#define null 0

class Line
{
public:

	sf::RectangleShape m_self;
	
	int isClear = 1;

	Line(float xpos, float ypos, float xLength, sf::Color c,int isHorizontal);
	Line(float xpos, float ypos, float xLength, float yLength, sf::Color c, int isHorizontal);
	~Line();


	friend bool operator==(const Line &l1, const int stat) {
		return (l1.isClear == stat);
	}

	friend bool operator!=(const Line &l1, const int stat) {
		return !(l1 == stat);
	}
	Line operator =(const int x) {
		isClear = x;
		return *this;
	}
};

