#include <SFML\Graphics.hpp>
#include <Windows.h>
#include "GameOfLife.h"


int main()
{
	// hide console window
	ShowWindow(GetConsoleWindow(), SW_HIDE);

	constexpr int rows = 100;
	constexpr int cols = 100;
	constexpr float cellSize = 8.0f;
	const sf::Color	cellColor = sf::Color::White;
	const sf::Color backgroundColor = sf::Color::Black;

	_2DVector grid(cols, std::vector<bool>(rows, 0));
	_2DVector nextGrid(cols, std::vector<bool>(rows, 0));
	generateGrid(grid, rows, cols);
	

	sf::RenderWindow window(sf::VideoMode(cols * cellSize, rows * cellSize), "Conway's Game Of Life", sf::Style::Close);
	window.setFramerateLimit(6);

	// main loop
	while (window.isOpen())
	{
		sf::Event evnt;
		while (window.pollEvent(evnt))
		{
			if (evnt.type == sf::Event::Closed)
				window.close();
		}
		window.clear(backgroundColor);

		updateGrid(grid, nextGrid, rows, cols);
		drawGrid(window, grid, rows, cols, cellSize, cellColor);

		window.display();
	}
}