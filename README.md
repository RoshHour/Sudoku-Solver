# Sudoku Solver

Uses a recursive trial and error algorithm in order to "bruteforce" the answer.

## How it works
It tries a value and checks the sudoku rules (in the 3 by 3 square, vertically and horizontally) to ensure everything is valid. If not then it will undo the guess and try again with another number.