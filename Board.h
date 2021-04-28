#pragma once

#include <iostream>
#include "Cell.h"

class Board
{
private:
	int m_height;
	int m_width;
	Cell* m_board;

public:
	Board(int height, int width);

	void init();
	void refresh();
	void print();
	void setCell(int x, int y);

	~Board();

private:
	void setCells(int index);
	void setNewBoardState();
};

