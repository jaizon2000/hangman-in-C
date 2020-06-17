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
  printf("word: %s", word);
  
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
      
      // printf("%c, %c\n", word[i], guess[0]);
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

  for (int i = 0; i < 7; i++) {
    printf("%s\n", hangman[i]);
    }
}



bool find(char guess, char *array) {
  printf("%d", guess - 97);
  return array[guess - 'z'] != 0;
}



void print_array(char *array) {
  for (int i = 0; i < sizeof(array) ; i++) {
    printf("%c", array[i]);
  }
  printf("\n\n");
}			    



void print_stats(int lives, char *letters_guessed) {
  printf("Lives: %d\n", lives);
  print_hangman(lives);

  printf("Letters guessed: \n");
  print_array(letters_guessed);

}



void blank_array(int word_length, char *guessed, char *word) {
  for (int i = 0; i < word_length - 1; i++) {
    if (isalpha(word[i])) {
      guessed[i] = '_';
    }
    else {
      guessed[i] = word[i];
    }
  }  
}

int main() {
  int lives = 6;
  char letters_guessed[ALPHABET_SIZE] = {0};
  
  char *word = get_random_word();

  char user_guess[WORD_SIZE] = {0};
  blank_array(strlen(word), user_guess, word);

  
    
  // START
  //  print_stats(lives, letters_guessed);

  // GET GUESS
  char *guess = getguess();
  if (!checkguess(word, guess)) { // if guess not correct
    --lives;
  }
  
  // FIND LETTER IN LETTER_GUESSED ARRAY
  if (letters_guessed[*guess-97] != *guess) {
    printf("ascii: %d \n", *guess-97);
    letters_guessed[*guess-97] = *guess;
  }
  for (int i = 0; i < ALPHABET_SIZE; i++) {
    if (isalpha(letters_guessed[i])) {
      printf("%c ", letters_guessed[i]);
    }
  }
  printf("\n");
  
    /*if (!find(tolower(*guess), letters_guessed)) { // if not found in array
    letters_guessed[*guess-97] = *guess;
    }*/
  
  //  print_stats(lives, letters_guessed);
print_array(user_guess);
    
  
    
  return 0;
}
