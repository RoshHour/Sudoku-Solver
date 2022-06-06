#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void printGrid(int**, int[2]);
int calcGrid(int**, int, int, int);
int scanGrid(int**, int[2]);
int checkGrid(int**, int, int, int, int[2]);
int fillGrid(int**, int, int, int[2]);

int main(int argc, char* argv[])
{
    FILE* file = fopen(argv[1], "r");

    int boxSize = 3;
    int gridSize[2] = {boxSize, boxSize * boxSize};
    int** grid = (int**)malloc(gridSize[1] * sizeof(int*));
    for (int i = 0; i < gridSize[1]; i++)
        grid[i] = (int*)malloc(gridSize[1] * sizeof(int));

    for (int row = 0; row < gridSize[1]; row++)
        for (int column = 0; column < gridSize[1]; column++)
        {
            int val = -1;
            fscanf(file, "%d", &val);
            grid[row][column] = val;
        }

    scanGrid(grid, gridSize);
    printGrid(grid, gridSize);

    return EXIT_SUCCESS;
}

void printGrid(int** grid, int gridSize[2])
{
    for (int row = 0; row < gridSize[1]; row++)
    {
        for (int column = 0; column < gridSize[1]; column++)
        {
            int val = grid[row][column];

            if (val == -1)
                printf("-\t");
            else
                printf("%d\t", val);
        }

        printf("\n");
    }
}

int calcGrid(int** grid, int guess, int row, int column)
{
    return grid[row][column] == guess && grid[row][column] > -1;
}

int scanGrid(int** grid, int gridSize[1])
{
    for (int row = 0; row < gridSize[1]; row++)
        for (int column = 0; column < gridSize[1]; column++)
            if (grid[row][column] < 0)
                return fillGrid(grid, row, column, gridSize);

    return 1;
}

int checkGrid(int** grid, int guess, int row, int column, int gridSize[2])
{
    for (int attempt = 0; attempt < gridSize[1]; attempt++)
    {
        int tempRow = ((row / gridSize[0]) * gridSize[0]) + (attempt / gridSize[0]);
        int tempColumn = ((column / gridSize[0]) * gridSize[0]) + (attempt % gridSize[0]);
        if (calcGrid(grid, guess, tempRow, tempColumn) ||
            calcGrid(grid, guess, row, attempt) ||
            calcGrid(grid, guess, attempt, column))
            return 0;
    }
	
    return 1;
}

int fillGrid(int** grid, int row, int column, int gridSize[2])
{
    for (int guess = 1; guess <= gridSize[1]; guess++)
        if (checkGrid(grid, guess, row, column, gridSize))
        {
            grid[row][column] = guess;

            if (scanGrid(grid, gridSize))
                return 1;

            grid[row][column] = -1;
        }

    return 0;
}