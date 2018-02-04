#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

char *getStr();

int main() {
  printf("Type long string to fold\n");

  char *str = getStr();
  int foldingLen = 10, idx = 10;
  int j = 0, len = strlen(str), tmpLen = len / foldingLen;

  char *tmp = (char *) malloc(tmpLen * sizeof(char));

  for(int i = 0; i < len; i++, j++) {
    tmp[j] = str[i];
    if(i == foldingLen) {
      if(str[i] != ' '){
	foldingLen++;
	continue;
      }
      j++;
      tmp[j] = '\n';
      foldingLen = foldingLen + idx;
    }
  }
  printf("%s \n", tmp);
  free(tmp);
}


char *getStr()
{
    char *str = NULL, *tmp = NULL;
    size_t size = 0, index = 0;
    int ch = EOF;
    int CHUNK = 1;

    while (ch) {
        ch = getc(stdin);

        /* Check if we need to stop. */
        if (ch == EOF || ch == '\n')
            ch = 0;

        /* Check if we need to expand. */
        if (size <= index) {
            size += CHUNK;
            tmp = realloc(str, size);
            if (!tmp) {
                free(str);
                str = NULL;
                break;
            }
            str = tmp;
        }

        /* Actually store the thing. */
        str[index++] = ch;
    }

    return str;
}
