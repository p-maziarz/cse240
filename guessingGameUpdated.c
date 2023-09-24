#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>

/* TODO:
- fix syntax and readability
 */

struct playerInfo {
    char name[100];
    int guessCount;
};

struct leaderboard { //defines leaderboard as a struct to store the leaderboard
    struct playerInfo players[5];
};

int getGuess() {
    int guess;
    printf("Enter your guess: ");
    scanf("%d", &guess);
    return guess;
}

void playGuessingGame(struct playerInfo *playerInfo) { //
    int num;
    double sqrtValue;
    int guess;
    int guessCount = 0; //declares guess count as 0 to start

    num = (rand() % 91) + 10;
    sqrtValue = sqrt(num);
    printf("%.15lf is the square root of what number? \n", sqrtValue);

    while (1) {
        guess = getGuess();
        guessCount++; //count increases by 1 each guess
        playerInfo->guessCount++; //adds incremented guess count to playerInfo

        if (guess < num) {
            printf("Too low, guess again: \n");
        } else if (guess > num) {
            printf("Too high, guess again: \n");
        } else {
            printf("You got it, baby!\n");
            printf("Congratulations! You guessed the number in %d tries.\n", guessCount);
            break;
        }
    }
}

void saveLeaderboard(struct leaderboard *leaderboard) { //saves leaderboard to text file
    FILE *file = fopen("leaderboard.txt", "w");
    if (file == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }

    for (int i = 0; i < 5; i++) {
        fprintf(file, "%s %d\n", leaderboard->players[i].name, leaderboard->players[i].guessCount);
    }

    fclose(file);
}

void loadLeaderboard(struct leaderboard *leaderboard) { //loads the leaderboard from a text file
    FILE *file = fopen("leaderboard.txt", "r");
    if (file == NULL) {
        for (int i = 0; i < 5; i++) {
            strcpy(leaderboard->players[i].name, "");
            leaderboard->players[i].guessCount = 0;
        }
        return;
    }

    for (int i = 0; i < 5; i++) { //reads leaderboard data from file
        if (fscanf(file, "%99s %d", leaderboard->players[i].name, &leaderboard->players[i].guessCount) != 2) {
            for (int j = i; j < 5; j++) { //error reading data, initalize leaderboard
                strcpy(leaderboard->players[j].name, "");
                leaderboard->players[j].guessCount = 0;
            }
            break;
        }
    }

    fclose(file);
}

int main() {
    char c;
    struct playerInfo player;
    char name[100]; //char array to store name as string, name can be up to 100 characters
    srand(time(NULL)); //random number generator with current time

    printf("Welcome! Please enter your name: \n"); //prompts user for name
    scanf("%s", player.name);
    printf("Thank you, %s! Press 'q' to quit or any key to continue:\n", name);
    scanf(" %c", &c);

    struct playerInfo leaderBoard[5]; //initializes leaderboard array
    for (int i = 0; i < 5; i++){ //sets guess count to 0 for all players
        strcpy(leaderBoard[i].name, ""); //copies the string name of the players
        leaderBoard[i].guessCount = 0;
    }

    struct leaderboard currentLeaderboard; //creates leaderboard and loads data from text file if it exists
    loadLeaderboard(&currentLeaderboard);

    while (c != 'q') {
        playGuessingGame(&player);

        for (int i = 0; i < 5; i++) { //updates the leaderboard
            if (player.guessCount < leaderBoard[i].guessCount) {
                for (int j = 4; j > i; j--) { //pushes other scores down
                    strcpy(leaderBoard[j].name, leaderBoard[j -1].name);
                    leaderBoard[j].guessCount = leaderBoard[j - 1].guessCount;
                }
                strcpy(leaderBoard[i].name, player.name); //stores players name and guess count in leaderboard
                leaderBoard[i].guessCount = player.guessCount;
                break; //exits loop after leaderboard is updated
            }
        }

        printf("Press 'q' to quit or any key to continue:\n");
        scanf(" %c", &c);
    }

    saveLeaderboard(&currentLeaderboard); //saves leaderboard to text file before quitting

    printf("Bye-bye, %s!\n", name);
    return 0;
}
