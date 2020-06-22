#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <ctype.h>

#define MAX_WORD_SIZE (80+1)
#define ALPHABET_SIZE

// ------------------- 
// get_random_word:
// get and returnd a random word from `words` file
// -------------------
char *get_random_word() {
  // 1. OPEN FILE
  FILE *f = fopen("/usr/share/dict/words", "r");
  if (f == NULL) {
    fprintf(stderr, "Error fgets returned NULL");
    exit(EXIT_FAILURE);
  }
   
  // 2. GETTING THE WORD
  static char word[MAX_WORD_SIZE];
  // Count how many words in file
  int total_words;
  for (total_words = 0; fgets(word, MAX_WORD_SIZE, f) != NULL; total_words++);

  // Set srand & get random integer
  srand((unsigned) time(NULL));
  unsigned long int rand_num = (rand() % total_words);

  // Go back to beginning of file and find the word
  rewind(f);
  for (int i = 0; i < rand_num; i++) {
    if (fgets(word, (80 + 1), f) == NULL) {
      fprintf(stderr, "Error fgets returned NULL");
      exit(EXIT_FAILURE);
    }
  }
  // 3. CLOSE FILE
  fclose(f);

  // 4. Replace '\n' with '\0'
  char *p = strchr(word, '\n');
  *p = '\0';
  return word;
}


// ------------------- 
// get_guess:
// asks user for input and cleans it up
// -------------------
char *get_guess() {
  static char guess[MAX_WORD_SIZE];

  printf("Guess a letter/word: ");
  fgets(guess, MAX_WORD_SIZE, stdin);
  
  char *p = strchr(guess, ' ') != NULL ?
    strchr(guess, ' ') : strchr(guess, '\n');
  
  *p = '\0';
  
  return guess;
}


// -------------------
// check_user_guess:
//
// -------------------
bool check_user_guess(char *random_word, char *user_guess) {
  // A. USER GUESSES A WORD
  if (strlen(user_guess) > (size_t) 1) {
    // Guessed the word correctly
    if (strcmp(random_word, user_guess) == 0) {
      printf("Word guessed correctly!\n");
      exit(EXIT_SUCCESS);
    }
    // Guessed word incorrectly
    else {
      return false;
    }
  }
  
  // B. USER GUESSES A LETTER
  else {
    // Point to where the letter matches in random_word
    // If ch not found, return true; else return false
    char *matching_ch = strchr(random_word, *user_guess);
    if (matching_ch != NULL) {
      return true;
    }
    else {
      return false;
    }
    
    printf("matching_ch: %c\n", *matching_ch);
  }
}


char *put_underlines(char *word, int word_len, char *user_guess) {
  static char letters_guessed[MAX_WORD_SIZE];
  for (int i = 0; i < word_len; i++) {
    printf("%c ", word[i]);
    if (isalpha(word[i])) {
      letters_guessed[i] = '_';
      if (strncmp(word, user_guess, (size_t) 1) == 0) {
	if (strcmp(word,user_guess) == 0) {
	  printf("Guessed the whole word\n");
	}
	letters_guessed[i] = word[i];
      }
    }
    else {
      letters_guessed[i] = word[i];
    }
  }
  printf("\n");
  return letters_guessed;
}



// ------------------- 
// main:
// the goods
// -------------------
int main() {
  // 0. USER STATS
  int lives = 6;
  bool check = false;
  
  // 1. GET WORD
  char *random_word = get_random_word();
  int word_len = strlen(random_word);
  printf("word: %s\nword length: %d\n", random_word, word_len);
  char *letters_guessed = put_underlines(random_word, word_len, NULL);
  
  
  
  do {
    
    printf("%s\n", letters_guessed);
    // 2. GUESS LETTER/WORD
    char *user_guess = get_guess();
    letters_guessed = put_underlines(random_word, word_len, user_guess);

    // 3. CHECK USER_GUESS
    printf("\nCheck User Guess \n-----------\n");
    check = check_user_guess(random_word, user_guess);
  
    printf("char found?: %s\n", check ==  true ? "true" : "false");

    // 4. UPDATE USER STATS
    if (check == true) {
      
    }
    else {
      --lives;
    }
    printf("lives: %d\n", lives);
  } while (lives > 0);

  return 0;
}
