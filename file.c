#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <ctype.h>

#define WORD_SIZE (80+1)

char *get_random_word() {  
  // OPEN FILE - Check for failure
  FILE *f = fopen("/usr/share/dict/words", "r");
  if (f == NULL) {
    exit(EXIT_FAILURE);
  }
  
  static char word[WORD_SIZE]; // max 80 char in 1 word
  int count = 0;
  while (fgets(word, WORD_SIZE, f) != NULL) {
    count++;
  }

  srand((unsigned) time(NULL)); // randomizing  rand()
  long int rand_num = (rand() % count);
  
  rewind(f);
  for (int i = 0; i < rand_num; i++) {
    if (fgets(word, WORD_SIZE, f) == NULL) {
      fprintf(stderr, "Error fgets returned NULL");
      exit(EXIT_FAILURE);
    } 
  }
  fclose(f);
  
  return word;
}



char *getguess() {
  static char guess[WORD_SIZE];
  printf("Guess a letter or the word: ");
  scanf("%s", guess);
  return guess;
}



bool checkguess(char word[WORD_SIZE], char guess[WORD_SIZE]) {
  printf("%s", word);
  /* printf("%s", guess); */
  
  for (int i = 0; word[i] != '\0'; i++) {
    // Guess is a letter
    if (strlen(guess) == (size_t) 1) {
      if (tolower(word[i]) == tolower(guess[0])) {   
	printf("%c, %c\n", word[i], guess[0]);
      }
    }

    // Guess is a word
    else {
      if (tolower(word[i]) != tolower(guess[i])) {
	return false;
      }
      printf("%c, %c\n", word[i], guess[0]);
    }
  }
  return true;
}



int main() {
  char *word = get_random_word();
  /* printf("%s", word); */
  
  char *guess = getguess();
  /* printf("%s\n", guess); */

  checkguess(word, guess);
  
  return 0;
}
