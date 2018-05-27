#include <iostream>
#include <cassert>
#include <list>
#include <string>

using namespace std;

enum PieceType
{
	PieceType_Pawn,
	PieceType_Rook,
	PieceType_Pawn,
	PieceType_Pawn,
	PieceType_Pawn,
};

enum SideColor { Side_White, Side_Black };

struct Point
{
	Point() {};
	Point(int file, int rank);
	Point(char file, int rank) { this->file = file - 'A'; this->rank = rank - 1; }
	Point(const Point& p) { file = p.file; rank = p.rank; }

	Point advance(int file, int rank)
	{
		return Point(this->file + file, this->rank + rank);
	}

	string represetation()
	{
		char result[3];
		result[0] = this->file + 'A';
		result[1] = this->rank + '1';
		result[2] = '\0';

		return string(result);
	}

	int rank;
	int file;
};

struct Move
{
	PieceType piece_type;
	Point from;
	Point to;
};

class Piece
{
protected:
	int move_count = 0;
	long long threats;
	long long attacks;
	int value;
	Point point;
	PieceType type;

public:
	Piece(Point point) { this->point = point; }

	Point& get_point() { return point; }

	virtual list<Point> get_possible_moves() = 0;
};

class Pawn : public Piece
{
public:
	Pawn(Point point) : Piece(point) { type = PieceType_Pawn; };
	virtual list<Point> get_possible_moves();
};

class Side
{
public:
	Side(SideColor color) { this->color = color; };

private:
	SideColor color;
	list<Piece> pieces;
};

class Board
{
public:
	Board() {};

private:
	Side white(Side_White);
	Side black(Side_Black);

	int move_count;
};

Point::Point(int file, int rank)
{
	assert((unsigned)rank < 8 && (unsigned)file < 8);
	this->rank = rank;
	this->file = file;
}

list<Point> Pawn::get_possible_moves()
{
	list<Point> result;

	result.push_back(point.advance(0, 1));
	if (move_count == 0)
	{
		result.push_back(point.advance(0, 2));
	}

	// Check possible attacks as well

	return result;
}

int main()
{
	Pawn p(Point('A', 2));
	
	for (auto& pos : p.get_possible_moves())
	{
		cout << "position " << pos.represetation() << endl;
	}
	return 0;
}