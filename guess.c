#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>

//this struct stores the player's name as an array of 100 chars and an int for the amount of guesses a user has tried
struct playerInfo {
    char name[100];
    int guessCount;
};

//this defines the leaderboard as a struct to store the data of the top 5 players
struct leaderboard {
    struct playerInfo players[5];
};

//this function collects the user's guess and stores it as an int
int getGuess() {
    int guess;
    printf("Enter your guess: ");
    scanf("%d", &guess);
    return guess;
}

//this function provides the code for the actual game, like generating the random number, and checking if answer is correct or not
void playGuessingGame(struct playerInfo *playerInfo) {
    int num;
    double sqrtValue;
    int guess;
    int guessCount = 0; //declares starting guess count as 0

    num = (rand() % 91) + 10; //generates a random number and restricts it to only generate from 10-100
    sqrtValue = sqrt(num); //typecasts the square root of the number as a double bc many square roots of integers are not also integers
    printf("%.15lf is the square root of what number? \n", sqrtValue);

    while (1) {
        guess = getGuess();
        guessCount++; //count increases by 1 each guess
        playerInfo->guessCount++; //adds incremented guess count to playerInfo

        if (guess < num) { //runs the answer through these if-else statements to check if whether the answer is correct or not
            printf("Too low, guess again: \n");
        } else if (guess > num) {
            printf("Too high, guess again: \n");
        } else {
            printf("You got it, baby!\n");
            printf("Congratulations! You guessed the number in %d tries.\n", guessCount);
            break; //ends that if-else statement when the correct answer is input
                    // and displays the amount of times the player tried to guess
        }
    }
}

//this function saves leaderboard to text file called leaderboard.txt
void saveLeaderboard(struct leaderboard *leaderboard) {
    FILE *file = fopen("leaderboard.txt", "w"); //only initializes as a filename instead of a full path
    if (file == NULL) {
        printf("Error opening file for writing.\n"); //checks if the file exists or not
        return;
    }

    for (int i = 0; i < 5; i++) { //writes leaderboard data to the file
        fprintf(file, "%s %d\n", leaderboard->players[i].name, leaderboard->players[i].guessCount);
    }

    fclose(file); //closes file
}

//this function loads the leaderboard from that text file
void loadLeaderboard(struct leaderboard *leaderboard) {
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
            for (int j = i; j < 5; j++) { //initializes leaderboard if there's an error reading the data
                strcpy(leaderboard->players[j].name, "");
                leaderboard->players[j].guessCount = 0;
            }
            break;
        }
    }

    fclose(file); //closes file
}

//this main method is the method that builds the complete game off of the functions I made above
//it also runs the code to store the user's name and if they want to continue playing or quit
int main() {
    char c;
    struct playerInfo player;
    char name[100]; //char array to store name as string, name can be up to 100 characters
    srand(time(NULL)); //random number generator with current time

    printf("Welcome! Please enter your name: \n"); //prompts user for name
    scanf("%s", player.name);
    printf("Thank you, %s! Press 'q' to quit or any key to continue:\n", name);
    scanf(" %c", &c); //checks the user's key input to determine if the user wants to play or quit

    struct playerInfo leaderBoard[5]; //initializes leaderboard array
    for (int i = 0; i < 5; i++){ //sets guess count to 0 for all players
        strcpy(leaderBoard[i].name, ""); //copies the string name of the players
        leaderBoard[i].guessCount = 0;
    }

    struct leaderboard currentLeaderboard; //creates leaderboard and loads data from text file if it exists
    loadLeaderboard(&currentLeaderboard);

    //if the player presses any key besides q, they want to play, so this code runs
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
