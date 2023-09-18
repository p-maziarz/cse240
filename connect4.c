#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define NUM_ROWS 6
#define NUM_COLS 7

int GetColumn(char player, char board[][NUM_COLS]) {
    int column;
    printf("%s to play. Pick a column (1-7):", player=='R' ? //prompts player to pick token color
                                               "Red":"Yellow");
    int num_values = scanf("%d", &column);
    while (getchar() != '\n'); //clears buffer of newline
    while (num_values != 1 || column < 1 || column > NUM_COLS || board[0][column - 1] != ' ') {
        if (board[0][column-1] != ' ') { //prevents player from playing after winning
            printf("Column is full. Choose another column: \n");
        } else {
            printf("Make sure the column is between 1 and 7: \n");
        }
        num_values = scanf("%d", &column);
        while (getchar() != '\n');
    }
    return column-1;
}

int GetEmptyRow(char board[][NUM_COLS], int col) {
    for (int row = NUM_ROWS - 1; row >= 0; row--) {
        if (board[row][col] == ' ') {
            return row; //checks for the next empty row and returns it
        }
    }
    return -1; //returns -1 if there are no empty rows available
}

bool CheckBoardFull(char board[][NUM_COLS]) { //can only use bool if you #include <stdbool.h>
    for (int row = 0; row < NUM_ROWS; row++) {
        for (int col = 0; col < NUM_COLS; col++) {
            if (board[row][col] == ' ') {
                return false; //if empty spaces are found, the board isnt full and therefore returns false
            }
        }
    }
    return true; //if the board is full, this returns true
}

void PrintBoard(char board[][NUM_COLS]) { //this allows the board to display
    printf("%s", *board); //asterisk changes pointer from char to string
    for (int r = 0; r < NUM_ROWS; r++) {
        for (int c = 0; c < NUM_COLS; c++) {
            printf("%c", board[r][c]); //loops and prints each char in the rows and columns
        }
        printf("\n");
    }
}

char CheckWinner(char board[][NUM_COLS], int row, int col) { //checks for winner
    for (int row = 0; row < NUM_ROWS; row++) { //checks the horizontal rows for winner
        for (int col = 0; col < NUM_COLS - 3; col++) {
            char token = board[row][col];
            if (token != ' ' &&
                token == board[row][col + 1] &&
                token == board[row][col + 2] &&
                token == board[row][col + 3]) {
                return token; //returns the winner
            }
        }
    }
    for (int col = 0; col < NUM_COLS; col++) { //checks the vertical columns
        for (int row = 0; row < NUM_ROWS - 3; row++) {
            char token = board[row][col];
            if (token != ' ' &&
                token == board[row + 1][col] &&
                token == board[row + 2][col] &&
                token == board[row + 3][col]) {
                return token; //returns the winner
            }
        }
    }
    for (int row = 0; row < NUM_ROWS - 3; row++) { //checks diagonally (top-left to bottom-right)
        for (int col = 3; col < NUM_COLS; col++) {
            char token = board[row][col];
            if (token != ' ' &&
                token == board[row + 1][col - 1] &&
                token == board[row + 2][col - 2] &&
                token == board[row + 3][col - 3]) {
                return token; // We have a winner
            }
        }
    }
    for (int row = 0; row < NUM_ROWS - 3; row++) { //checks diagonally (top-right to bottom left)
        for (int col = 3; col < NUM_COLS; col++) {
            char token = board[row][col];
            if (token != ' ' &&
                token == board[row + 1][col - 1] &&
                token == board[row + 2][col - 2] &&
                token == board[row + 3][col - 3]) {
                return token; // Return the winning player's token
            }
        }
    }
    return ' '; //returns ' ' if no winner is found, indicates game is over
}

void PlayConnectFour() { //this runs the actual game
    bool game_over = false; //sets game_over to false so we can create a while loop with it
    char player = 'R'; //sets starting player as red, uses single quotes to instantiate the char type
    char board[NUM_ROWS][NUM_COLS]; //declares board

    for (int r = 0; r < NUM_ROWS; r++) { //creates board with empty spaces
        for (int c = 0; c < NUM_COLS; c++) {
            board[r][c] = ' ';
        }
    }

    char winner = ' ';

    PrintBoard(board); //prints the board

    while (!game_over) {
        int col = GetColumn(player, board); //player chooses column
        int row = GetEmptyRow(board, col); //finds next available row

        if (row != -1) {
            board[row][col] = player; //puts players token in the available row of the column
            PrintBoard(board); //prints updated board

            winner = CheckWinner(board, row, col); //checks for winner
        }

        if (winner != ' ') { //displays winner
            game_over = true;
            printf("\n%c wins!", winner);
        }
        else if (CheckBoardFull(board)) { //checks if board is full
            game_over = true;
            printf("It's a tie!");
        }
        else if (row == -1) { //checks if column is full
            printf("Column is full. Choose another column.\n");
        }
        player = (player == 'R' ? 'Y' : 'R');
    }
}

int main() {
    char c;
    printf("Welcome! Press 'q' to quit or any key to continue:\n");
    scanf(" %c", &c);
    while (c != 'q') {
        PlayConnectFour();
    }
    printf("Bye Bye!\n");
    return 0;
}
