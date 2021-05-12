#include <SFML\Graphics.hpp>
#include <Windows.h>
#include "GameOfLife.h"


int main()
{
	// Hide console
	//ShowWindow(GetConsoleWindow(), SW_HIDE);

	const int rows = 64;
	const int cols = 64;
	const float cell_size = 8.0f;

	const sf::Color	cell_color = sf::Color::White;
	const sf::Color bg_color = sf::Color::Black;
	
	// Create window
	const int window_height = cols * cell_size;
	const int window_width = rows * cell_size;

	sf::RenderWindow window(sf::VideoMode(window_height, window_width), "Conway's Game Of Life", sf::Style::Close);
	window.setFramerateLimit(30);

	// Create grid
	grid_t grid(cols, std::vector<bool>(rows, 0));
	grid_t next_grid = grid;
	generate_grid(grid, rows, cols);

	// Main loop
	while (window.isOpen())
	{
		sf::Event evnt;
		while (window.pollEvent(evnt))
		{
			if (evnt.type == sf::Event::Closed)
				window.close();
		}
		window.clear(bg_color);

		update_grid(grid, next_grid);
		draw_grid(window, grid, cell_size, cell_color);

		window.display();
	}
}