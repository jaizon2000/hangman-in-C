
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
// Is the given string a word?
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
// asks user for input and cleans it up and returns it
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
// print_underlines:
// print the letters in the user guessed correctly
// -------------------
void print_underlines(const char *word, const char letters_guessed[]) {
  char underlines[MAX_WORD_SIZE];
  strcpy(underlines, word);
  
  for (int i = 0; i < strlen(underlines); i++) {
    if (!isalpha(underlines[i])) {
    }
    else if (strchr(letters_guessed, underlines[i]) == NULL) {
      underlines[i] = '_';
    }
  }
  puts(underlines);
}

// ------------------- 
// put_guess_in_letters_guessed:
// puts all the guessed letters into an array
// -------------------
void put_guess_in_letters_guessed(char letters_guessed[], char *user_guess) {
  for (int i = 0; i < strlen(user_guess); i++) {
    if (isalpha(user_guess[i])) {
      if (!is_guess_word(user_guess)) {
	letters_guessed[user_guess[i] - 'a'] = user_guess[i];
      }
    }
  }
}

// ------------------- 
// is_guess_in_word:
// Is the guess (letter/word) in the random_word?
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
// is_word_guessed:
// Is the word guessed?
// -------------------
bool is_word_guessed(const char *word, const char letters_guessed[], char *user_guess) {
  char alpha_word[strlen(word)];
  if (strcmp(word, user_guess) == 0)
    return true;
  
  for (int i = 0; i < strlen(word); i++) {
    if (isalpha(word[i]))
      alpha_word[i] = word[i];
  }
  
  for (int i = 0; i < strlen(word); i++) {
    if (strchr(letters_guessed, alpha_word[i]) == NULL) {
      return false;
    }
  }
  return true;
}

void print_hangman(int lives) {
  char *hangman[6];
  hangman[0] = "\n  +---+";
  hangman[1] = "  |   |";
  hangman[6] = "=========\0";
  switch (lives) {
  case 6:
    hangman[2] = "      |";
    hangman[3] = "      |";
    hangman[4] = "      |";
    hangman[5] = "      |";
    break;
  case 5:
    hangman[2] = "  O   |";
    hangman[3] = "      |";
    hangman[4] = "      |";
    hangman[5] = "      |";
    break;
  case 4:
    hangman[2] = "  O   |";
    hangman[3] = "  |   |";
    hangman[4] = "      |";
    hangman[5] = "      |";
    break;
  case 3:
    hangman[2] = "  O   |";
    hangman[3] = " /|   |";
    hangman[4] = "      |";
    hangman[5] = "      |";
    break;
  case 2:
    hangman[2] = "  O   |";
    hangman[3] = " /|\\  |";
    hangman[4] = "      |";
    hangman[5] = "      |";
    break;
    case 1:
    hangman[2] = "  O   |";
    hangman[3] = " /|\\  |";
    hangman[4] = " /    |";
    hangman[5] = "      |";
    break;
  case 0:
    hangman[2] = "  O   |";
    hangman[3] = " /|\\  |";
    hangman[4] = " / \\  |";
    hangman[5] = "      |";
    break;
  }

  for (int i = 0; i < 7; i++) {
    printf("%s\n", hangman[i]);
    }
  }

// ------------------- 
// main:
// Runs the program
// -------------------
int main() {
  puts("--- HANGMAN ---");
  // 0. USER STATS
  int lives = 6;

  // 1. GET WORD
  char *random_word = get_random_word();
  //  printf("word: %s\nword length: %ld\n", random_word, strlen(random_word));
  
  char letters_guessed[ALPHABET_SIZE + 1] = {0};
  memset(letters_guessed, ' ', ALPHABET_SIZE);
  
  do {
    // Print Hangman
    print_hangman(lives);
    // printf("lives: %d\n", lives);
    
    print_underlines(random_word, letters_guessed);
    
    // 2. GUESS LETTER/WORD
    char *user_guess = get_guess();

    // Add guessed letters to letters_guessed
    put_guess_in_letters_guessed(letters_guessed, user_guess);

    // Check if word is guessed correctly
    if (is_word_guessed(random_word, letters_guessed, user_guess)) {
      fputs("Correctly guessed!\n", stdout);
      exit(EXIT_SUCCESS);
    }
    
    //If guess not in the word, --lives
    if (!is_guess_in_word(random_word, letters_guessed, user_guess)) {
	--lives;
    }
   
    // Prints Guessed Letters
    puts("letters guessed:");
    for (int i = 0; i < ALPHABET_SIZE; i++)
      printf("%c ", letters_guessed[i]);
    printf("\n");
   
  } while (lives > 0);
  printf("\nThe word was: %s\n", random_word);
  exit(EXIT_FAILURE);
}
