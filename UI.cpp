#include "UI.h"

UI::UI() : m_board{ nullptr }
{
}

void UI::startGame()
{
	std::cout << "Welcome to game of life\n";
	std::cout << "What is the height of your grid? ";
	int heigth = support::isInteger(3, 50);                        // Small grid size setup, no smaler than 3x3
	std::cout << "What is the width of your grid?  ";
	int width = support::isInteger(3, 50);
	m_board = new Board(heigth, width);
	m_board->init();
	std::cout << "Add Cels to game\n";
	while (true) {
		std::cout << "\nGive x cordinate or -1 to end setup -> ";
		int x = support::isInteger(-1, heigth - 1);
		if (x == -1)
			break;
		std::cout << "Give y cordinate or -1 to end setup -> ";
		int y = support::isInteger(-1, heigth - 1);
		if (y == -1)
			break;
		m_board->setCell(x, y);
		support::clearScreen();
		m_board->print();
	}
	std::cout << "Auto(1) or manual(2) play? ";
	int play = support::isInteger(1, 2);
	switch (play)
	{
	case 1:
		autoPlay();
		break;
	case 2:
		manualPlay();
		break;
	default:
		break;
	}
	support::clearScreen();
	std::cout << "Bye bye!\n";
}

UI::~UI()
{
	delete m_board;
	m_board = nullptr;
}

void UI::autoPlay()
{
	bool run{ true };
	while (run) {
		printGame();
		run = !support::keyIsPressed();
		std::this_thread::sleep_for(std::chrono::seconds(1));
	};
}

void UI::manualPlay()
{
	printGame();
	while (true) {
		std::cout << "\n\nEnter 'E' to console to terminate\nAnything else to move on -> ";  
		char end[256]{ };																		// longer inputs will crash
		std::cin >> end;
		if (end[0] == 'e' || end[0] == 'E')
			break;
		else
			printGame();
	}
}

void UI::printGame()
{
	support::clearScreen();
	m_board->print();
	m_board->refresh();
}

