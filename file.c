#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
  FILE *f;
    
  f = fopen("/usr/share/dict/words", "r");
  if (f == NULL) {
    exit(EXIT_FAILURE);
  }

  char s[80]; // max 80 char in one word
  int count = 0;

  srand((unsigned) time(NULL));
 
  while (fgets(s, 80, f) != NULL) {

    printf("\nftell: %ld\n", ftell(f));
    printf("%s", s);
    count++;
  }
  
  long int rand_num = 100000 + (rand() % (count-100000));
  printf("\ncount: %d | NUM: %ld\n", count,  rand_num);
  printf("fseek: %d\n", fseek(f, rand_num, SEEK_SET));
  fgets(s, 80, f);
  printf("%s", s);
  printf("\nftell: %ld\n", ftell(f));
  

  
  fclose(f);
  
  return 0;
}
