#pragma once

#include <iostream>
#include <chrono> 
#include <thread>

#include "Board.h"
#include "SupportFuctions.h"

class UI
{
private:
	Board* m_board;

public:
	UI();
	void startGame();
	~UI();

private:
	void autoPlay();
	void manualPlay();
	void printGame();
};
