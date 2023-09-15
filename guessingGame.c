
﻿#include <stdio.h>
#include <stdlib.h>
#include <math.h>


int GetGuess(int num) {
   int guess;
   printf("Enter your guess: ");
   scanf("%d", &guess);
   return guess;
}


void PlayGuessingGame() {
   int num;
   double sqrtValue;
   int guess;
   num = (rand() % 91) + 10;
   sqrtValue = sqrt(num);
   printf("%.15lf is the square root of what number? ", sqrtValue);
   guess = GetGuess(num);


   if (guess < num) {
       printf("Too low, guess again: ");
   } else if (guess > num) {
       printf("Too high, guess again: ");
   } else {
       printf("You got it, baby!\n");
   }
}


int main() {
   char c;
   printf("Welcome! Press 'q' to quit or any key to continue:\n");
   scanf(" %c", &c);
   while (c != 'q') {
       PlayGuessingGame();
   }
   printf("Bye Bye!\n");
   return 0;
}
