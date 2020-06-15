#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
  FILE *f;
  
  // OPEN FILE - Check for failure
  f = fopen("/usr/share/dict/words", "r");
  if (f == NULL) {
    exit(EXIT_FAILURE);
  }
  
  char word[80]; // max 80 char in 1 word
  int count = 0;
  srand((unsigned) time(NULL)); // randomizing  rand()
  
 
  while (fgets(word, 80, f) != NULL) {
    /* printf("\nftell: %ld\n", ftell(f)); */
    /* printf("%s", s); */
    count++;
  }
  
  long int rand_num = (rand() % count);
  printf("\nCOUNT: %d | RAND NUM: %ld\n", count,  rand_num);
  fseek(f, rand_num, SEEK_SET);
  
  fgets(word, 80, f);
  fgets(word, 80, f);
  printf("ftell: %ld\n", ftell(f));
  printf("%s", word);
  
  int word_len = sizeof(word)/sizeof(word[0]);
  char *p = &word[word_len];
    
  fclose(f);
  
  return 0;
}
