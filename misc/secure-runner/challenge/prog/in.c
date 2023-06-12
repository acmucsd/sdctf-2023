#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#define NUM_GUESS 10

int main() {
	srand(time(NULL));
	unsigned int num_guesses = NUM_GUESS;
	unsigned int max = (unsigned int)pow(2, num_guesses) - 1;
	unsigned int secret = rand() % max;

	printf("Guess a number from 0 to %u in %u guesses:\n", max, num_guesses);
	
	while(num_guesses > 0) {
		if (num_guesses != NUM_GUESS) {
			printf("Next Guess (%u left):\n", num_guesses);
		}
		fflush(stdout);
		unsigned int guess = 0;
		scanf("%u",&guess);
		if (guess == secret) {
			printf("Congrats, you won!\n");
			return 0;
		}
		if (secret < guess) {
			printf("Number is lower! ");
		} else {
			printf("Number is higher! ");
		}
		fflush(stdout);
		num_guesses--;
	}
	printf("You ran out of guesses :(\n");
	return 0;
}