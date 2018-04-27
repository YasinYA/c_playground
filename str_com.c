/* It compresses/shortenes a string. for example: yaaaasiiiin = ya4si4n */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void compress(char *data, char *writeFile);
char * repCounter(char *str);
char * removeDuplicates(char * str);


int main(int argc, char **argv)
{

  // check if extra arguments are passed
  if(argc == 1) {
    printf("No Extra arguments are passed so the program is gonna terminate");
    exit(EXIT_FAILURE);
  }

  // check test data file
  if(!argv[1] && !argv[2]) {
    printf("Files must be provided\n");
    exit(EXIT_FAILURE);
  }

  FILE *fr = fopen(argv[1], "r");

  if(!fr) {
    printf("File canot be opened\n");
    exit(EXIT_FAILURE);
  }

  int bufSize = 30000;
  char *buf = (char *)malloc(bufSize * sizeof(char));

  fgets(buf, bufSize, fr);

  int blen = strlen(buf);

  // Allocate the right space for the string.
  char *str = (char *)malloc((blen+1) * sizeof(char));

  // copy the buf to the str
  strcpy(str, buf);


  compress(str, argv[2]);
  fclose(fr);


  return EXIT_SUCCESS;

}


void compress(char *data, char *writeFile)
{

  char *str = repCounter(data);

  // open the file for writing
  FILE *fw = fopen(writeFile, "w");

  if(!fw) {
    printf("File canot be opened\n");
    exit(EXIT_FAILURE);
  }

  fprintf(fw, "%s", str);

  fclose(fw);

}


char *repCounter(char *str) {
  int slen = strlen(str);

  char *newStr = (char *)malloc((slen + 1) * sizeof(char));

  int idx = 0;
  char prevChar;
  int i, j = 0;

  for(i = 0; i < slen; i++) {

    if(i == 0) {
      prevChar = str[i];
    }

    prevChar = str[i - 1];
    newStr[j] = str[i];

    if(str[i] == prevChar) {
      idx = idx + 1;
      if(str[i+1] != prevChar) {
	if (idx > 9) {
	  sprintf(&newStr[j], "%d", idx);
	  j++;
	} else {
	  sprintf(&newStr[j], "%d", idx);
	}
      }
    }else {
      idx = 1;
    }

    //printf("perv char = %c, curr char = %c, and no of repetative =  %d \n", prevChar, str[i], idx);

    j++;

  }

  newStr[j] = '\0';
  printf("%s", removeDuplicates(newStr));
  return newStr;
}

char * removeDuplicates(char * str) {
  int i, j, len, len1;
  for(len=0; str[len]!='\0'; len++);
  len1 = 0;

  for(i=0; i<(len-len1);)
    {
        if(str[i]==str[i+1])
        {
            for(j=i;j<(len-len1);j++)
                str[j]=str[j+1];
            len1++;
        }
        else
        {
            i++;
        }
    }

  return str;
}
