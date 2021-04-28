#include "Board.h"

Board::Board(int height, int width) : m_height{ height }, m_width{ width }, m_board{ nullptr }
{
}

void Board::init()
{
	int size = m_height * m_width;
	m_board = new Cell[size];
	for (int i = 0; i < size; i++)
	{
		m_board[i].neighbors = 0;
		m_board[i].alive = false;
	}
}

void Board::print()
{
	for (int i = 0; i < m_height * m_width; i++)
	{
		if (i % m_width == 0) {
			std::cout << '\n';
		}
		if (m_board[i].alive)
			std::cout << 'X';
		else
			std::cout << '-';
	}
}

void Board::refresh()
{
	for (int i = 0; i < m_height * m_width; i++)
	{
		if(m_board[i].alive) 
		{
			setCells(i);
		}
	}
	setNewBoardState();
}

void Board::setCells(int index)
{

	if (index - 1 > -1) {                                         //cheking bounds and notifying neigboring cells
		m_board[index - 1].neighbors++;
		if (index - m_width + 1 > -1) {
			m_board[index - m_width + 1].neighbors++;
			if (index - m_width > -1) {
				m_board[index - m_width].neighbors++;
				if (index - m_width - 1 > -1) {
					m_board[index - m_width - 1].neighbors++;
				}
			}
		}
	}

	if (index + 1 < m_width * m_height) {
		m_board[index + 1].neighbors++;
		if (index + m_width - 1 < m_width * m_height) {
			m_board[index + m_width - 1].neighbors++;
			if (index + m_width < m_width * m_height) {
				m_board[index + m_width].neighbors++;
				if (index + m_width + 1 < m_width * m_height) {
					m_board[index + m_width + 1].neighbors++;
				}
			}
		}
	}
}

void Board::setNewBoardState()
{
	for (int i = 0; i < m_height * m_width; i++) {
		if (m_board[i].neighbors == 3 || (m_board[i].alive && m_board[i].neighbors == 2))
		{
			m_board[i].alive = true;
		}
		else
		{
			m_board[i].alive = false;
		}
	}
	for (int i = 0; i < m_height * m_width; i++)
	{
		m_board[i].neighbors = 0;
	}
}

void Board::setCell(int x, int y)
{
	m_board[x + m_height * y].alive = !m_board[x + m_height * y].alive;
}

Board::~Board()
{
	delete[] m_board;
	m_board = nullptr;
}