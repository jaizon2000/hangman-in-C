
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <ctype.h>

#define MAX_WORD_SIZE (80+1)
#define ALPHABET_SIZE 26

// ------------------- 
// to_str_lower:
// make all the char of str lowercase
// -------------------
void to_str_lower(char *string) {
  for (int i = 0; i != strlen(string); i++) {
    string[i] = tolower(string[i]); 
  }
}

// ------------------- 
// is_guess_word:
// 
// -------------------
bool is_guess_word(char *string) {
  return strlen(string) > 1;
}

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
  if (p != NULL) {
    *p = '\0';
  }

  // 5. Make all letters lower case
  to_str_lower(word);

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

  // Find ' ' or '\n' and change to a null char '\0'
  char *p = strchr(guess, ' ') != NULL ? strchr(guess, ' ') : strchr(guess, '\n');
  if (p != NULL) {
    *p = '\0';
  }

  to_str_lower(guess);
  return guess;
}

// ------------------- 
// put_underlines:
// 
// -------------------
char *put_underlines(char *word, char array[]) {
  static char letters_guessed[MAX_WORD_SIZE];
  for (int i = 0; i < strlen(word); i++) {
    printf("%c ", word[i]);
    if (isalpha(word[i])) {
      letters_guessed[i] = '_';
     
    }
    else {
      letters_guessed[i] = word[i];
    }
  }
  printf("\n");
  return letters_guessed;
}

// ******* MAKE 2 functions?
// ------------------- 
// add_guess_to_letters_guessed:
// 
// -------------------
void add_guess_to_letters_guessed(char *word, char letters_guessed[], char *user_guess) {
  for (int i = 0; i < strlen(word); i++) {
    if (isalpha(word[i])) {
      // A. CHARACTER GUESSED
      if (!is_guess_word(user_guess) && word[i] == *user_guess) {
        letters_guessed[*user_guess - 'a'] = *user_guess;
      }

      // B. WHOLE WORD GUESSED
      else if (is_guess_word(user_guess) && strcmp(word, user_guess) == 0) {
        letters_guessed[word[i]-'a'] = word[i];
      }
    }    
  }
}

// ------------------- 
// is_guess_in_word:
// 
// -------------------
bool is_guess_in_word(char *word, char *letters_guessed, char *user_guess) {
  if (is_guess_word(user_guess)) {
    return strstr(word, user_guess) != NULL && strlen(user_guess) == strlen(word) ? true : false;
  }
  else if (!is_guess_word(user_guess)) {
    return strchr(word,  *user_guess) != NULL ? true : false;
  }
  return false;
}
// ------------------- 
// main:
// the goods
// -------------------
int main() {
  // 0. USER STATS
  int lives = 6;

  
  // 1. GET WORD
  char *random_word = get_random_word();
  printf("word: %s\nword length: %ld\n", random_word, strlen(random_word));
  
  char letters_guessed[ALPHABET_SIZE] = {0};
  
  char *underlines = put_underlines(random_word, letters_guessed);
  
  
  do {
    printf("%s\n", underlines);
    
    // 2. GUESS LETTER/WORD
    char *user_guess = get_guess();
    
    // Add guessed letters to letters_guessed
    add_guess_to_letters_guessed(random_word, letters_guessed, user_guess);

    // Prints Guessed Letters
    for (int i = 0; i < ALPHABET_SIZE; i++)
      printf("%c ", letters_guessed[i]);

    //If guess not in the word, --lives
    if (!is_guess_in_word(random_word, letters_guessed, user_guess)) {
	--lives;
    }
    printf("\nlives: %d\n", lives);
    
  } while (lives > 0);

  return 0;
}
