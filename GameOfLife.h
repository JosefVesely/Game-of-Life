#pragma once

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using grid_t = std::vector<std::vector<bool>>;


void generate_grid(grid_t& grid, int rows, int cols)
{
	srand(time(0));

	for (int i = 0; i < cols; i++) {
		for (int j = 0; j < rows; j++)
		{
			grid[i][j] = rand() % 2;
		}
	}
}


int count_neighbors(const grid_t& grid, int x, int y)
{
	int rows = grid[0].size();
	int cols = grid.size();

	int neighbors = -grid[x][y];

	for (int i = -1; i <= 1; i++) {
		for (int j = -1; j <= 1; j++)
		{
			int col = (x + i + cols) % cols;
			int row = (y + j + rows) % rows;
			neighbors += grid[col][row];
		}
	}
	return neighbors;
}


void update_grid(grid_t& grid, grid_t& next_grid)
{
	int rows = grid[0].size();
	int cols = grid.size();

	for (int i = 0; i < cols; i++) {
		for (int j = 0; j < rows; j++)
		{
			int state = grid[i][j];
			int neighbors = count_neighbors(grid, i, j);

			if (state == 0 && neighbors == 3) {
				next_grid[i][j] = 1;
			}
			else if ((state == 1 && neighbors < 2) || (state == 1 && neighbors > 3)) {
				next_grid[i][j] = 0;
			}
			else
				next_grid[i][j] = state;
		}
	}
	grid = next_grid;
}


void draw_grid(sf::RenderWindow& window, const grid_t& grid, float cell_size, sf::Color cell_color)
{
	int rows = grid[0].size();
	int cols = grid.size();

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++)
		{
			if (grid[i][j])
			{
				sf::RectangleShape square(sf::Vector2f(cell_size, cell_size));
				square.setPosition(i * cell_size, j * cell_size);
				square.setFillColor(cell_color);

				window.draw(square);
			}
		}
	}
}