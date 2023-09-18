#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define NUM_ROWS 6
#define NUM_COLS 7

int GetColumn(char player) {
    int column;
    printf("%s to play. Pick a column (1-7):", player=='R' ? //prompts player to pick token color
                                               "Red":"Yellow");
    int num_values = scanf("%d", &column);
    while (getchar() != '\n'); //clears buffer of newline
    while (num_values != 1 || column < 1 || column > NUM_COLS) {
        printf("Make sure the column is between 1 and 7: \n");
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
        int col = GetColumn(player); //player chooses column
        int row = GetEmptyRow(board, col); //finds next available row
        board[row][col] = player; //puts players token in the available row of the column

        player = (player == 'R' ? 'Y' : 'R');
        PrintBoard(board); //prints the updated board each turn
        if (winner != ' ') { //checks for winner
            game_over = true;
            printf("%c wins!", winner);
        }
        else if (CheckBoardFull(board)) { //checks if board is full
            game_over = true;
            printf("It's a tie!");
        }
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
