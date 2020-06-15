#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
  FILE *f;
    
  f = fopen("/usr/share/dict/words", "r");
  if (f == NULL) {
    exit(EXIT_FAILURE);
  }

  char s[80];
  while (fgets(s, 80, f) != NULL) {
    printf("%s", s);
  }
  
  fclose(f);
  
  return 0;
}
