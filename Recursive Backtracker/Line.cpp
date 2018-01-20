#include "Line.h"






Line::Line(float xpos, float ypos, float xLength,sf::Color c, int isHorizontal)
	:m_self(sf::Vector2f(xLength,static_cast<float>(2)))
{
	m_self.setPosition(sf::Vector2f(xpos, ypos));
	m_self.setFillColor(c);
	if (isHorizontal != 1) {
		m_self.setRotation(90);
	}
}
Line::Line(float xpos, float ypos, float xLength, float yLength, sf::Color c, int isHorizontal)
	: m_self(sf::Vector2f(xLength, yLength))
{
	m_self.setPosition(sf::Vector2f(xpos, ypos));
	m_self.setFillColor(c);
	if (isHorizontal != 1) {
		m_self.setRotation(90);;
	}
}

Line::~Line()
{
}
