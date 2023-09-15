// Created by Home on 9/14/23.

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

void PrintBoard() { //this allows the board to display
    char board[NUM_ROWS][NUM_COLS];
    printf("%s", *board); //asterisk changes pointer from char to string
}

void PlayConnectFour() { //this runs the actual game
    bool game_over; //TODO: instantiate game_over and make sure it works. this is just a placeholder for now
    char player; //TODO: instantiate player variable and make sure it works. this is just a placeholder for now
    char board[NUM_ROWS][NUM_COLS]; //creates empty board
    // . . .
    PrintBoard(board); //prints the board
    //. . .
    //TODO: Allow players to pick a column for their token
    while (!game_over) {
        int col = GetColumn(player);
        //. . .
        player = (player == 'R' ? 'Y' : 'R');
    }
    printf("%s wins!", &player);
}

char CheckWinner(char board[][NUM_COLS]) { //checks for the winner of the game
    //TODO: check rows for four sequential tokens, returns winner or ' '
    return ' ';
}

bool CheckBoardFull(char board[][NUM_COLS]) { //can only use bool if you #include <stdbool.h>
    // . . .
    return true; //if the board is full, this returns true
}

// TODO: Check for the next available row for given column
int GetEmptyRow(char board[][NUM_COLS], int col) {
    return true; //TODO: Add return statement; this is a placeholder
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
