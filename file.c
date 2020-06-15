#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
int main() {
  char *word = get_random_word();
  printf("%s", word);
  return 0;
}
