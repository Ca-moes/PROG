// Testes_Exame.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Position {
	int lin, col;
};
// =========================================
class Ship {
public:
	Ship(unsigned int identifier, char symbol, Position position, char direction, size_t size);
	unsigned int id() const; //returns identifier
	Position pos() const;    //returns position   
	char dir() const;        //returns direction  
	size_t size() const;     //returns size
	// ... OTHER METHODS
private:
	unsigned int identifier; // ship id number
	char symbol;
	Position position;
	char direction;
	size_t siz;
	// ... OTHER ATTRIBUTES AND/OR METHODS
};
Ship::Ship(unsigned int identifier, char symbol, Position position, char direction, size_t size) {
	this->identifier = identifier;
	this->symbol = symbol;
	this->position.col = position.col;
	this->position.lin = position.lin;
	this->direction = direction;
	this->siz = size;
}
unsigned int Ship::id() const {
	return identifier;
}
Position Ship::pos() const {
	return position;
}
char Ship::dir() const {
	return direction;
}
size_t Ship::size() const {
	return siz;
}

class Board {
public:
	Board(size_t numLines = 10, size_t numColumns = 10);
	bool putShip(const Ship& s); //add ship to board, if possible
	// ... OTHER METHODS
private:
	bool canPutShip(Position pos, char dir, size_t size);
	size_t numLines, numColumns;
	vector<vector<int>> board; // each element = ship id or ‐1   
	vector<Ship> ships;
	// ... OTHER ATTRIBUTES AND/OR METHODS
};
Board::Board(size_t numLines, size_t numColumns) {
	this->numLines = numLines;
	this->numColumns = numColumns;
	vector<int> vec(numLines, -1);
	vector<vector<int>> b(numColumns, vec);
	this->board = b;
	vector<Ship> s;
	this->ships = s;
}
bool Board::canPutShip(Position pos, char dir, size_t size) {
	switch (dir)
	{
	case 'H':
		if (size > numColumns)
			return false;
		if (pos.col > numColumns - size + 1)
			return false;
		for (size_t i = pos.col-1; i < pos.col + size - 1; i++)
		{
			if (board[pos.lin][i] != -1)
				return false;
		}
		break;
	case 'V':
		break;
	}
	return true;
}
bool Board::putShip(const Ship& s) {
	if (!canPutShip(s.pos(), s.dir(), s.size()))
		return false;
	else {
		switch (s.dir())
		{
		case 'H':
			for (size_t i = s.pos().col - 1; i < s.pos().col + s.size() - 1; i++)
				board[s.pos().lin][i] = s.id();
			ships.push_back(s);
			break;
		case 'V':
			for (size_t i = s.pos().lin - 1; i < s.pos().lin + s.size() - 1; i++)
				board[i][s.pos().col] = s.id();
			ships.push_back(s);
		}
		return true;
	}
}


int main() {
	char tau = 1;
	cout << tau << endl;
	int a = 5, b = 10, c;
	c = max(a, b);
	cout << "sup " << c <<  endl;
	return 1;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
