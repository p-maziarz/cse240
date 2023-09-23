#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
//fixed code so it was fully functional as it wasn't 100% functional last time i submitted

/* TODO:
- keep an array of 5 structs to store the current leaders
- when the user quits, the current leaders should be saved to a text file
- when the game is started, the file should be read, if it exists
 */

struct playerInfo {
    char name[100];
    int guessCount;
};

struct scoreBoard {
    char scores[5];
    int highScore;
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
    printf("%.15lf is the square root of what number? ", sqrtValue);

    while (1) {
        guess = getGuess();
        guessCount++; //count increases by 1 each guess
        playerInfo->guessCount++; //adds incremented guess count to playerInfo

        if (guess < num) {
            printf("Too low, guess again: ");
        } else if (guess > num) {
            printf("Too high, guess again: ");
        } else {
            printf("You got it, baby!\n");
            printf("Congratulations! You guessed the number in %d tries.\n", guessCount);
            break;
        }
    }
}

int main() {
    char c;
    struct playerInfo player;
    char name[100]; //char array to store name as string, name can be up to 100 characters
    srand(time(NULL)); //random number generator with current time
    printf("Welcome! Please enter your name: "); //prompts user for name
    scanf("%s", player.name); //scans for name input
    printf("Thank you, %s! Press 'q' to quit or any key to continue:\n", name);
    scanf(" %c", &c);
    while (c != 'q') {
        playGuessingGame(&player);
        printf("Press 'q' to quit or any key to continue:\n");
        scanf(" %c", &c);
    }
    printf("Bye-bye, %s!\n", name);
    return 0;
}
