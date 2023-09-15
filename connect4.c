// Created by Home on 9/14/23.

#include <stdio.h>
#include <stdlib.h>

//TODO: 1) Create board (6 rows long * 7 columns high) by using DEFINE command and creating 2D arrays of type double
#define NUM_ROWS 6
#define NUM_COLS 7
double boardName[NUM_ROWS][NUM_COLS];
//TODO (1a) Create int method "GetColumn" which takes a char "player" and prompts them to pick a column between 1-7
int GetColumn(char player) {
    int column;
    printf("%s to play. Pick a column (1-7):", player=='R' ? //Prompts player to pick token color
                                               "Red":"Yellow");
    int num_values = scanf("%d", &column);
    while (getchar() != '\n'); //clear buffer of newline
    //TODO: 1b) If play enters invalid answer, re-prompt and remind player to choose between 1-7
    while (num_values != 1 || column < 1 || column > NUM_COLS) {
        printf("Make sure the column is between 1 and 7: \n");
        num_values = scanf("%d", &column);
        while (getchar() != '\n');
    }
    return column-1;
}

/*
 * TODO 2) Check for winner (checks for four sequential tokens in a row/column)
 * TODO 2a) Create char method "CheckWinner" that takes char board[][NUM_COLS] array
 * TODO 2b) "CheckWinner" returns either the char for the winner or ' '
*/

/*
 * TODO 3) Check if the board is full (if all palces on board have been taken)
 * TODO 3a) Create boolean ("bool") method "CheckBoardFull" that takes char board[][NUM_COLS] array
 * TODO 3b) "CheckBoardFull" returns T (T means "true")
 * TODO 3c) If board is full, restart game
*/

/*
 * TODO 4) Check for the next available row for given column
*/

/*
 * TODO 5) Create void method called PlayConnectFour() that allows players to pick a column for their token
 * TODO 5a) Reuse some code from the guessing game program to set up the method
 * TODO 5b) When game is complete, announce the winner or a tie.
 * TODO 5b.a) Use if method: If game is over, create int "col" that calls GetColumn(player) and display that player's winning column
*/

void PlayConnectFour() {
    // create an empty board
    char board[NUM_ROWS][NUM_COLS];

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
