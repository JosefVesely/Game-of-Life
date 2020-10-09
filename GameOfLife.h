#pragma once

#include <vector>
#include <cstdlib>
#include <ctime>

typedef std::vector<std::vector<bool>> _2DVector;


void generateGrid(_2DVector& grid, int rows, int cols)
{
	srand(time(0));

	for (int i = 0; i < cols; i++)
	{
		for (int j = 0; j < rows; j++)
		{
			grid[i][j] = rand() % 3;
		}
	}
}

// Passing the grid as a reference makes the function much faster
int countNeighbors(const _2DVector& grid, int rows, int cols, int x, int y)
{
	int neighbors = -grid[x][y];

	for (int i = -1; i <= 1; i++)
	{
		for (int j = -1; j <= 1; j++)
		{
			int col = (x + i + cols) % cols;
			int row = (y + j + rows) % rows;
			neighbors += grid[col][row];
		}
	}
	return neighbors;
}


void updateGrid(_2DVector& grid, _2DVector& nextGrid, int rows, int cols)
{
	for (int i = 0; i < cols; i++)
	{
		for (int j = 0; j < rows; j++)
		{
			int state = grid[i][j];
			int neighbors = countNeighbors(grid, rows, cols, i, j);

			if (state == 0 && neighbors == 3) {
				nextGrid[i][j] = 1;
			}
			else if ((state == 1 && neighbors < 2) || (state == 1 && neighbors > 3)) {
				nextGrid[i][j] = 0;
			}
			else {
				nextGrid[i][j] = state;
			}
		}
	}
	grid = nextGrid;
}


void drawGrid(sf::RenderWindow& window, _2DVector grid, int rows, int cols, float cellSize, sf::Color cellColor)
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			if (grid[i][j])
			{
				sf::RectangleShape square(sf::Vector2f(cellSize, cellSize));
				square.setPosition(i * cellSize, j * cellSize);
				square.setFillColor(cellColor);

				window.draw(square);
			}
		}
	}
}
