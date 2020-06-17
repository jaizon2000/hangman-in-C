#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <ctype.h>

#define WORD_SIZE (80+1)
#define ALPHABET_SIZE 26

char *get_random_word() {
  // 1. OPEN FILE
  FILE *f = fopen("/usr/share/dict/words", "r");
  if (f == NULL) {
    fprintf(stderr, "Error fgets returned NULL");
    exit(EXIT_FAILURE);
  }
   
  // 2. GETTING THE WORD
  static char word[WORD_SIZE];
  // Count how many words in file
  int total_words;
  for (total_words = 0; fgets(word, WORD_SIZE, f) != NULL; total_words++);

  // Set srand & get random integer
  srand((unsigned) time(NULL));
  unsigned long int rand_num = (rand() % total_words);

  // Go back to beginning of file and find the word
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

char *get_guess() {
  static char guess[WORD_SIZE];
  fgets(guess, WORD_SIZE, stdin);
  char *p = strchr(guess, ' ') != NULL ? strchr(guess, ' '): strchr(guess, '\n');
  *p = '\0';
    
  return guess;
}

int main() {
  printf("Guess a letter/word: ");
  printf("guess: %s\n", get_guess());

  printf("word: %s\n", get_random_word());
  return 0;
}
