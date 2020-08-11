import time

board = [
    [0, 2, 0, 0, 0, 0, 0, 0, 0],
    [0, 0, 0, 6, 0, 0, 0, 0, 3],
    [0, 7, 4, 0, 8, 0, 0, 0, 0],
    [0, 0, 0, 0, 0, 3, 0, 0, 2],
    [0, 8, 0, 0, 4, 0, 0, 1, 0],
    [6, 0, 0, 5, 0, 0, 0, 0, 0],
    [0, 0, 0, 0, 1, 0, 7, 8, 0],
    [5, 0, 0, 0, 0, 9, 0, 0, 0],
    [0, 0, 0, 0, 0, 0, 0, 4, 0]
]
row_len = len(board)
col_len = len(board[0])
grid_height = 3
grid_width = 3
number_choices = [1, 2, 3, 4, 5, 6, 7, 8, 9]


def getUnfilledSquare(board):
    for row in range(row_len):
        for col in range(col_len):
            if board[row][col] == 0:
                return row, col
    return None


def printBoard(board):
    for row in range(row_len):
        if row % grid_height == 0 and row != 0:
            print("------+-------+------")
        for col in range(col_len):
            if col % grid_width == 0 and col != 0:
                print("|", end=" ")
            if col == col_len-1:
                print(board[row][col])
            else:
                print(board[row][col], end=" ")


def canNumberBeInserted(board, number, current_position):
    current_row, current_col = current_position
    for col in range(col_len):
        if number == board[current_row][col] and col != current_col:
            return False
    for row in range(row_len):
        if number == board[row][current_col] and row != current_row:
            return False
    grid_row_start = (current_row//3)*3
    grid_col_start = (current_col//3)*3
    for row in range(grid_row_start, grid_row_start+grid_height):
        for col in range(grid_col_start, grid_col_start+grid_width):
            if number == board[row][col] and (row, col) != (current_row, current_col):
                return False
    return True


def solve(board):
    empty_square_position = getUnfilledSquare(board)
    if not empty_square_position:  # if no square is empty it means board is solved
        return True
    row, col = empty_square_position
    for number in number_choices:
        if canNumberBeInserted(board, number, (row, col)):
            board[row][col] = number
            if(solve(board)):
                return True
            # the board was unable to be solved at some point so reset all values till last solved
            board[row][col] = 0
    return False


def sudokuSolver():
    print("\nBefore solving\n")
    printBoard(board)
    start_time = time.time()
    solve(board)
    end_time = time.time()
    print("\n\nAfter solving\n")
    printBoard(board)
    print("\nTime taken to solve: {} seconds".format(end_time-start_time))


if __name__ == '__main__':
    sudokuSolver()
