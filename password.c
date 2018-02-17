/* functionality: generates passwords and remembers for you.*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


#define PASSWORD_LENGTH  10

char * randomData();
void generatePassword(char *fName, char *desc);
void listPasswords(char *fName);


struct Entry {
  char password[PASSWORD_LENGTH + 1];
  char madeTime[26];
  char description[100];
};

int main(int argc, char **argv)
{
  char fileName[] = "password.bin";

  // check if extra arguments are passed
  if(argc == 1) {
    printf("No Extra arguments are passed so the program is gonna terminate");
    exit(1);
  }

  // check the what action user want
  if(strcmp(argv[1], "generate") == 0) {

    // rand() needs to reset the seed of the generator and srand() does that
    // calling once on main instead of calling srand() each randomData() gets called
    srand(time(0));

    generatePassword(fileName, argv[2]);

  } else if(strcmp(argv[1], "list") == 0){

    listPasswords(fileName);

  } else {

    printf("Unknown option\n");
    exit(1);

  }

  return 0;

}


char * randomData()
{
  char characters[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789#$@?!";

  // Allocate memory for the random string
  char *randomString = (char *) malloc((PASSWORD_LENGTH + 1) * sizeof(char));

  if(randomString){

    // elements in the characters string
    int charsLen = (int) (sizeof(characters) - 1);

    int i;

    for(i = 0; i < PASSWORD_LENGTH; i++) {

      // calculate random number based on charsLen
      int randIndex = rand() % charsLen;

      randomString[i] = characters[randIndex];

    }

    // add the null character
    randomString[i] = '\0';

  } else {
    printf("Something went wrong \n");
    exit(1);
  }

  return randomString;
}

void generatePassword(char *fName, char *desc)
{
   // chdir to home
  chdir(getenv("HOME"));

  // current time
  time_t currentTime;
  time(&currentTime);
  char *strTime = ctime(&currentTime);

  struct Entry record;

  char *password = randomData();
  int len = strlen(password), i, j, x;
  int timeLen = strlen(strTime), descLen = strlen(desc);

  for(i = 0; i < len; i++) {
    record.password[i] = password[i];
  }
  record.password[i] = '\0';

  for(j = 0; j < timeLen; j++) {
    record.madeTime[j] = strTime[j];
  }

  record.madeTime[j] = '\0';

  for(x = 0; x < descLen; x++){
    record.description[x] = desc[x];
  }

  record.description[x] = '\0';

  FILE *fw;

  fw = fopen(fName, "a+b");


  if(!fw) {
    printf("Error has happened while opening the file\n");
  }

  // write to the file
  fwrite(&record, sizeof(struct Entry), 1, fw);

  printf("password: %s, madetime: %s, description: %s \n", record.password, record.madeTime, record.description);

  // close the file
  fclose(fw);

  printf("done.\n");

}


void listPasswords(char *fName)
{
   // chdir to home
  chdir(getenv("HOME"));

  FILE *fr = fopen(fName, "rb");

  if(!fr) {
    printf("Error has happened while opening the file\n");
    exit(1);
  }

  struct Entry line;
  size_t rc;

  while( ( rc = fread(&line, sizeof(struct Entry), 1, fr) ) ) {
    printf("password : %s, made time: %s, description: %s \n", line.password, line.madeTime, line.description);
  }

  fclose(fr);
}
