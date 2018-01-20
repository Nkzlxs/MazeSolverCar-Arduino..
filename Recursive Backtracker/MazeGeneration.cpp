//Main Loop of the program Nkzlxs.19/1/2018
//Thanks to Daniel Shiffman Example using p5.js https://github.com/CodingTrain/Rainbow-Code/tree/master/CodingChallenges/CC_10_Maze_DFS_p5.js

#include <SFML\Graphics.hpp> //sfml
#include "Cell.h" //Cell class
#include <vector> //array
#include "defines.h" //make the variable "w" globally
#include <iostream> //text output
#include <time.h> //for time(0)
#include <random> //i think this cpp file didnt use this library
#include <fstream> //for debugging

std::vector <Cell> cells;
std::vector <int> stack;
std::ofstream myfile; //for debugging
Cell *current;
int initPos = 0;
int z = initPos;
enum Directions {
	top,
	left,
	right,
	btm
};
enum {
	tl = 0,  //top-left corner cell
	bl = 1,  //bottom-left corner cell
	tr = 2,  //top-right corner cell
	br = 3,  //bottom-right corner cell
	mt = 4,  //mid-top cells
	ml = 5,  //mid-left cells
	mr = 6,  //mid-right cells
	mb = 7,  //mid-btm cells
	m = 8    //mid cells
};
int width, height, numX, numY;
void displayNeighbours(int n);
Cell& getCell(int n, int a) {
	switch (a)
	{
	case 0: {

		return cells[n - 1];
		break;
	}
	case 1: {
		return cells[n - numY];
		break;
	}
	case 2: {
		return cells[n + numY];
		break;
	}
	case 3: {
		return cells[n + 1];
		break;
	}
	case 4: {
		return cells[n];
		break;
	}
	default:

		break;
	}
}
bool testforCell(int i, int part) { //tl bl tr br mt ml mr mb m
	switch (part) {
	case 0: {return i == 0;}
	case 1: {return i + 1 == numY;}
	case 2: {return i + numY == cells.size();}
	case 3: {return i + 1 == cells.size();}
	case 4: {return i % numY == 0 && i + numY < cells.size() && i - numY >= 0;}
	case 5: {return i - numY < 0 && i%numY != 0 && (i + 1) % numY != 0;}
	case 6: {return i + numY > cells.size() && i%numY != 0 && (i + 1) % numY != 0;}
	case 7: {return (i + 1) % numY == 0 && i + numY < cells.size() && i - numY>0;}
	case 8: {return i - numY > 0 && i + numY < cells.size() && i%numY != 0 && (i + 1) % numY != 0;}
	default:
		break;
	}
}
void addNeighbours(int numY) { //tl bl tr br mt ml mr mb m

	for (int n = 0;n < cells.size();n++) {
		if (testforCell(n, tl)) {
			cells[n].addNeighbours(0, 0, 1, 1);
			cells[n].isCorner = 0;

		}
		if (testforCell(n, bl)) {
			cells[n].addNeighbours(1, 0, 1, 0);
			cells[n].isCorner = 1;
		}
		if (testforCell(n, tr)) {
			cells[n].addNeighbours(0, 1, 0, 1);
			cells[n].isCorner = 2;
		}
		if (testforCell(n, br)) {
			cells[n].addNeighbours(1, 1, 0, 0);
			cells[n].isCorner = 3;
		}
		if (testforCell(n, mt)) {
			cells[n].addNeighbours(0, 1, 1, 1);
		}
		if (testforCell(n, ml)) {
			cells[n].addNeighbours(1, 0, 1, 1);

		}
		if (testforCell(n, mr)) {
			cells[n].addNeighbours(1, 1, 0, 1);
		}
		if (testforCell(n, mb)) {
			cells[n].addNeighbours(1, 1, 1, 0);
		}
		if (testforCell(n, m)) {
			cells[n].addNeighbours(1, 1, 1, 1);
		}
	}
}
//For Debugging uses------------------------------
void displayNeighbours(int n) {
	for (int i = 0;i < 4;i++) {
		if (cells[n].m_neighbours[0])
			cells[n - 1].m_sides[i].m_self.setFillColor(sf::Color::Blue);
		if (cells[n].m_neighbours[1])
			cells[n - numY].m_sides[i].m_self.setFillColor(sf::Color::Blue);
		if (cells[n].m_neighbours[2])
			cells[n + numY].m_sides[i].m_self.setFillColor(sf::Color::Blue);
		if (cells[n].m_neighbours[3])
			cells[n + 1].m_sides[i].m_self.setFillColor(sf::Color::Blue);
	}
}
//------------------------------------------------
//Copied from http://www.learncpp.com/cpp-tutorial/59-random-number-generation/
int random(int min, int max)
{
	static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);
	return min + static_cast<int>((max - min + 1) * (rand() * fraction));
}
//haha

//The Recursive backtracking 
void startMoving() {
	std::cout << "\n Pathseeker Moving!\n```Starting at: " << z << "\n";
	int x;
	current = &cells[z];

	int counter = 0;
	int counter2 = 0;
	int direction = 5;//0 1 2 3
	while (1) {

		current->isVisited = true;
		//getting the current cell direction
		switch (direction) {
		case Directions::top: {getCell(z, 3).m_status[Directions::top] = false;getCell(z, 4).m_status[Directions::btm] = false;std::cout << "Going Top!\n";break;}
		case Directions::left: {getCell(z, 2).m_status[Directions::left] = false;getCell(z, 4).m_status[Directions::right] = false;std::cout << "Going Left!\n";break;}
		case Directions::right: {getCell(z, 1).m_status[Directions::right] = false;getCell(z, 4).m_status[Directions::left] = false;std::cout << "Going Right!\n";break;}
		case Directions::btm: {getCell(z, 0).m_status[Directions::btm] = false;getCell(z, 4).m_status[Directions::top] = false;std::cout << "Going Bottom!\n";break;}
		default: {break;}
		}
		//if (counter >= 1)
		//	break;
		if (counter >= 1) {
			stack.pop_back();
			if (stack.size() == 0) {
				current = &cells[initPos];
				z = initPos;
				break;
			}
			current = &cells[(stack.back())];
			z = stack.back();
			counter = 0;
		}
		std::cout << "----------------------------t: " << counter2 << "----------------------------\n";
		counter2++;

		while (1) {
			//get random number between 0 to 3
			x = random(0, 3);
			std::cout << "new X: " << x << "\n";

			//Movement
			if (x == 0 && current->m_neighbours[0] && !cells[z - 1].isVisited) {
				z = z - 1;
				current = &cells[z];
				direction = Directions::top;
				std::cout << "next neighbour: " << z << " Directions: " << direction << "\n";
				stack.push_back(z);
				break;
			}
			else if (x == 1 && current->m_neighbours[1] && !cells[z - numY].isVisited) {
				z = z - numY;
				current = &cells[z];
				direction = Directions::left;
				std::cout << "next neighbour: " << z << " Directions: " << direction << "\n";
				stack.push_back(z);
				break;
			}
			else if (x == 2 && current->m_neighbours[2] && !cells[z + numY].isVisited) {
				z = z + numY;
				current = &cells[z];
				direction = Directions::right;
				std::cout << "next neighbour: " << z << " Directions: " << direction << "\n";
				stack.push_back(z);
				break;
			}
			else if (x == 3 && current->m_neighbours[3] && !cells[z + 1].isVisited) {
				z = z + 1;
				current = &cells[z];
				direction = Directions::btm;
				std::cout << "next neighbour: " << z << " Directions: " << direction << "\n";
				stack.push_back(z);
				break;
			}

			//Test for trap **means the surrounding neighbours were all visited
			else if (testforCell(z, m)) {
				if (getCell(z, 0).isVisited && getCell(z, 1).isVisited&& getCell(z, 2).isVisited&& getCell(z, 3).isVisited) {
					std::cout << "\nTrapped in mid,bcuz 4 neighbours visited\n";
					counter += 1;
					direction = 5;
					break;
				}
			}
			else if (testforCell(z, mt)) {
				if (getCell(z, 1).isVisited&& getCell(z, 2).isVisited&& getCell(z, 3).isVisited) {
					std::cout << "\nTrapped in midtop,bcuz 3 neighbours visited\n";
					counter += 1;
					direction = 5;
					break;
				}
			}
			else if (testforCell(z, ml)) {
				if (getCell(z, 0).isVisited &&  getCell(z, 2).isVisited&& getCell(z, 3).isVisited) {
					std::cout << "\nTrapped in midleft,bcuz 3 neighbours visited\n";
					counter += 1;
					direction = 5;
					break;

				}
			}
			else if (testforCell(z, mr)) {
				if (getCell(z, 0).isVisited && getCell(z, 1).isVisited &&  getCell(z, 3).isVisited) {
					std::cout << "\nTrapped in midright,bcuz 3 neighbours visited\n";
					counter += 1;
					direction = 5;
					break;
				}
			}
			else if (testforCell(z, mb)) {
				if (getCell(z, 0).isVisited && getCell(z, 1).isVisited&& getCell(z, 2).isVisited) {
					std::cout << "\nTrapped in midbtm,bcuz 3 neighbours visited\n";
					counter += 1;
					direction = 5;
					break;
				}
			}
			else if (testforCell(z, tl)) {
				if (getCell(z, 2).isVisited && getCell(z, 3).isVisited) {
					std::cout << "\nTrapped in topleft,bcuz 2 neighbours visited\n";
					counter += 1;
					direction = 5;
					break;
				}
			}
			else if (testforCell(z, bl)) {
				if (getCell(z, 0).isVisited && getCell(z, 2).isVisited) {
					std::cout << "\nTrapped in btmleft,bcuz 2 neighbours visited\n";
					counter += 1;
					direction = 5;
					break;
				}
			}
			else if (testforCell(z, tr)) {
				if (getCell(z, 1).isVisited && getCell(z, 3).isVisited) {
					std::cout << "\nTrapped in topright,bcuz 2 neighbours visited\n";
					counter += 1;
					direction = 5;
					break;
				}
			}
			else if (testforCell(z, br)) {
				if (getCell(z, 1).isVisited && getCell(z, 0).isVisited) {
					std::cout << "\nTrapped in btmright,bcuz 2 neighbours visited\n";
					counter += 1;
					direction = 5;
					break;
				}
			}
			else {
				std::cout << " INFINITE LOOP! \n";
			}
			//I think i didnt write the code above well...(Looks redundant)
		}
	}
	std::cout << "\nLOOP BROKE!\n";
	/*for (Cell &cell : cells) {
		if (cell.isVisited) {s
			cell.drawRect(sf::Vector2f(w, w), sf::Color::Blue);
		}
	}*/
	current->drawRect(sf::Vector2f(w, w), sf::Color::Red);
	
	myfile.open("Loops.txt");				//for debugging
	myfile <<"\nLooped "<< counter2 <<" times"<< "\n";      //for debugging
	myfile.close();						//for debugging
	//for (int i = 0;i < 4;i++)
	//	current->m_sides[i].m_self.setFillColor(sf::Color::Red);
}
//Let user choose their screen size
void getScreenSize() {
	do { std::cout << "Enter Width(px): ";std::cin >> width;if (std::cin.fail()||width<40) { std::cout << "Invalid Input\n";std::cin.clear();std::cin.ignore(32767, '\n');  } } while (width < 40);
	do { std::cout << "Enter Height(px): ";std::cin >> height;if (std::cin.fail() || height<40) { std::cout << "Invalid Input\n";std::cin.clear();std::cin.ignore(32767, '\n'); } } while (height < 40);
}
int main() {
	getScreenSize();
	//numX is how many cells on the x-axis,numY is how many cells on the y-axis
	numX = width / w, numY = height / w;
	srand(time(0));
	
	//generating the array and make each element a new Cell class
	for (int x = 0;x < numX;x++) {
		for (int y = 0;y < numY;y++) {
			cells.push_back(Cell(x*w, y*w));
			//pushback a Cell class with (x-position,y-position) as constructor.
		}
	}
	//for each cell, make its surrounding valid cell as neighbour
	addNeighbours(numY);
	//begin generating the maze
	startMoving();
	//create a RenderWindow named window1
	sf::RenderWindow window1(sf::VideoMode(width, height), "hi");
	while (window1.isOpen()) {
		sf::Event evt;
		while (window1.pollEvent(evt)) {
			int y = 0;
			if (evt.type == sf::Event::Closed) {
				window1.close();
			}
			if (evt.type == sf::Event::KeyPressed) {
				if (evt.key.code == sf::Keyboard::A&&y == 0) {

					z = random(0, cells.size());
					for (int n = 0;n < cells.size();n++) {
						cells[n].isVisited = false;
						cells[n].drawRect(sf::Vector2f(0, 0));
						for (int i = 0;i < 4;i++)
							cells[n].m_status[i] = true;
					}
					std::cout << "redoing" << std::endl;
					startMoving();
					y = 1;
				}

			}

		}
		for (Cell cell : cells) {
			/*		if (!cell.isVisited)*/
			cell.display(window1);
		}

		window1.display();
		window1.clear(sf::Color::Green);
	}




	return 0;
}
