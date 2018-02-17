/* functionality: generates passwords and remembers for you.*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


#define PASSWORD_LENGTH  10
#define LABEL_LENGTH 10

char * randomData();
void generatePassword(char *fName, char *label);
void listPasswords(char *fName);


struct Entry {
  char password[PASSWORD_LENGTH + 1];
  char madeTime[26];
  char label[LABEL_LENGTH];
};

int main(int argc, char **argv)
{
  char fileName[] = "password.bin";

  // check if extra arguments are passed
  if(argc == 1) {
    printf("No Extra arguments are passed so the program is gonna terminate");
    exit(EXIT_FAILURE);
  }

  // chdir to home
  chdir(getenv("HOME"));

  // check the what action user want
  if(strcmp(argv[1], "generate") == 0) {

    // rand() needs to reset the seed of the generator and srand() does that
    // calling once on main instead of calling srand() each randomData() gets called
    srand(time(0));

    // check if label is passed
    if(!argv[2]) {

      // assign the label to default value
      argv[2] = "No Label";

    }

    generatePassword(fileName, argv[2]);

  } else if(strcmp(argv[1], "list") == 0){

    listPasswords(fileName);

  } else {

    printf("Unknown option\n");
    exit(EXIT_FAILURE);

  }

  return EXIT_SUCCESS;

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
    exit(EXIT_FAILURE);
  }

  return randomString;
}

void generatePassword(char *fName, char *label)
{

  // current time
  time_t currentTime;
  time(&currentTime);
  char *strTime = ctime(&currentTime);

  struct Entry record;
  char *password = randomData();

  // assign the values

  strncpy(record.password, password, PASSWORD_LENGTH + 1);
  strncpy(record.madeTime, strTime, 26);
  strncpy(record.label, label, LABEL_LENGTH);

  FILE *fw;

  fw = fopen(fName, "a+b");


  if(!fw) {
    printf("Error has happened while opening the file\n");
    exit(EXIT_FAILURE);
  }

  // write to the file
  fwrite(&record, sizeof(struct Entry), 1, fw);

  printf("password: %s, madetime: %s, description: %s \n", record.password, record.madeTime, record.label);

  // close the file
  fclose(fw);

  printf("done.\n");

}


void listPasswords(char *fName)
{
  FILE *fr = fopen(fName, "rb");

  if(!fr) {
    printf("Error has happened while opening the file\n");
    exit(EXIT_FAILURE);
  }

  struct Entry line;
  size_t rc;

  while( ( rc = fread(&line, sizeof(struct Entry), 1, fr) ) ) {
    printf("password : %s, made time: %s, description: %s \n", line.password, line.madeTime, line.label);
  }

  fclose(fr);
}
