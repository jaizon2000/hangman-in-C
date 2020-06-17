#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <ctype.h>
#include <search.h>

#define WORD_SIZE (80+1)
#define ALPHABET_SIZE (25 + 1)

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
  
  bool letter_exists = false;
  
  for (int i = 0; word[i] != '\0'; i++) {
    // Guess is a letter
    if (strlen(guess) == (size_t) 1) {
      if (tolower(word[i]) == tolower(guess[0])) {   
	printf("%c, %c\n", word[i], guess[0]);
	letter_exists = true;
      }
    }

    // Guess is a word
    else {
      if (tolower(word[i]) != tolower(guess[i]))
	return false;
      
      printf("%c, %c\n", word[i], guess[0]);
    }
  }
  
  if (strlen(guess) == (size_t) 1) {
    if (letter_exists)
      return true;
    else
      return false;
  }
  // if all letters match
  return true;
  
}

void print_hangman(int life) {
  char *hangman[6];
  hangman[0] = "  +---+";
  hangman[1] = "  |   |";
  hangman[6] = "=========\0";
  switch (life) {
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
  
  /*for (char *p = hangman; p < hangman + 5; p++) {
    printf("%s\n", p);
    }*/

  for (int i = 0; i < 7; i++) {
    printf("%s\n", hangman[i]);
    }
}



bool find(char guess, char *array) {
  return array[guess - 'z'] != 0;
}



void print_array(char *array) {
  for (char *p = array; p < array + ALPHABET_SIZE; p++) {
    printf("%c ", *p);
  }
  printf("\n");
}			    



int main() {
  int lives = 6;
  char letters_guessed[ALPHABET_SIZE] = {0};
  
  char *word = get_random_word();
  
  char *guess = getguess();
  if (!checkguess(word, guess)) { // if guess not correct
    --lives;
  }
  
  print_hangman(lives);
  printf("lives: %d\n", lives);
  //lfind
  // if not found in array
  if (!find(tolower(*guess), letters_guessed)) {
    letters_guessed[*guess-97] = *guess;
  }
  print_array(letters_guessed);
  
  
    
  return 0;
}
