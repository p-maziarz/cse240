#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h> // Include the library for usleep function

// Include the linked list header
#include "slist.h"

#define NUM_ROWS 6
#define NUM_COLS 7

int GetColumn(char player, char board[][NUM_COLS]) {
    int column;
    printf("%s to play. Pick a column (1-7):", player == 'R' ? "Red" : "Yellow");
    int num_values = scanf("%d", &column);
    while (getchar() != '\n'); // Clears buffer of newline
    while (num_values != 1 || column < 1 || column > NUM_COLS || board[0][column - 1] != ' ') {
        if (board[0][column - 1] != ' ') { // Prevents player from playing after winning
            printf("Column is full. Choose another column: \n");
        } else {
            printf("Make sure the column is between 1 and 7: \n");
        }
        num_values = scanf("%d", &column);
        while (getchar() != '\n');
    }
    return column - 1;
}

int GetEmptyRow(char board[][NUM_COLS], int col) {
    for (int row = NUM_ROWS - 1; row >= 0; row--) {
        if (board[row][col] == ' ') {
            return row; // Checks for the next empty row and returns it
        }
    }
    return -1; // Returns -1 if there are no empty rows available
}
//dsdsdsdsds
bool CheckBoardFull(char board[][NUM_COLS]) {
    for (int row = 0; row < NUM_ROWS; row++) {
        for (int col = 0; col < NUM_COLS; col++) {
            if (board[row][col] == ' ') {
                return false; // If empty spaces are found, the board isn't full, and therefore, return false
            }
        }
    }
    return true; // If the board is full, return true
}

void PrintBoard(char board[][NUM_COLS]) {
    printf("%s", *board); // Asterisk changes pointer from char to string
    for (int r = 0; r < NUM_ROWS; r++) {
        for (int c = 0; c < NUM_COLS; c++) {
            printf("%c", board[r][c]); // Loops and prints each char in the rows and columns
        }
        printf("\n");
    }
}

char CheckWinner(char board[][NUM_COLS], int row, int col) {
    for (int row = 0; row < NUM_ROWS; row++) {
        for (int col = 0; col < NUM_COLS - 3; col++) {
            char token = board[row][col];
            if (token != ' ' &&
                token == board[row][col + 1] &&
                token == board[row][col + 2] &&
                token == board[row][col + 3]) {
                return token; // Returns the winner
            }
        }
    }
    for (int col = 0; col < NUM_COLS; col++) {
        for (int row = 0; row < NUM_ROWS - 3; row++) {
            char token = board[row][col];
            if (token != ' ' &&
                token == board[row + 1][col] &&
                token == board[row + 2][col] &&
                token == board[row + 3][col]) {
                return token; // Returns the winner
            }
        }
    }
    for (int row = 0; row < NUM_ROWS - 3; row++) {
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
    for (int row = 0; row < NUM_ROWS - 3; row++) {
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
    return ' '; // Returns ' ' if no winner is found, indicating the game is over
}

// Include the linked list header
#include "slist.h"

// Function to ask for replay or quit
char askForReplay() {
    char choice;
    printf("Press 'r' to replay or 'q' to quit:\n");
    scanf(" %c", &choice);
    return choice;
}

// Function to replay the moves with a delay
void ReplayMoves(ListNode* head, char board[][NUM_COLS]) {
    ListNode* current = head;

    while (current != NULL) {
        int col = current->column;
        int row = GetEmptyRow(board, col);

        if (row != -1) {
            board[row][col] = current->player;
            PrintBoard(board);

            // Delay for 1 second
            usleep(1000000); // Adjust the delay duration for slower replay
        }

        current = current->next;
    }
}

void PlayConnectFour() {
    bool game_over = false;
    char player = 'R';
    char board[NUM_ROWS][NUM_COLS];

    for (int r = 0; r < NUM_ROWS; r++) {
        for (int c = 0; c < NUM_COLS; c++) {
            board[r][c] = ' ';
        }
    }

    char winner = ' ';

    // Initialize the linked list head
    ListNode* head = NULL;

    PrintBoard(board);

    while (!game_over) {
        int col = GetColumn(player, board);
        int row = GetEmptyRow(board, col);

        if (row != -1) {
            board[row][col] = player;

            // Record the move in the linked list
            insertNode(&head, player, col);

            PrintBoard(board);
            winner = CheckWinner(board, row, col);
        }

        if (winner != ' ') {
            game_over = true;
            printf("\n%c wins!", winner);

            // Ask the winning player if they want to replay
            char replayChoice;
            printf("\n%c, press 'r' to replay your winning moves or 'q' to quit:\n", winner);
            scanf(" %c", &replayChoice);

            if (replayChoice == 'r') {
                ReplayMoves(head, board);
                freeList(head);
            }
        } else if (CheckBoardFull(board)) {
            game_over = true;
            printf("It's a tie!");
        } else if (row == -1) {
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

