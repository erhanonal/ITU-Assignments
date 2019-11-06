//Erhan Önal 06.05.2018

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#define MAX_LINES 10000
#define MAX_LENGTH 200

/**
        Structure for holding instructions
        @step Line number
        @index Word number
*/

struct instruction_s {
  int step;
  int index;
};

/**
        Finds nth word on a given line
        @param s Pointer for the line
        @param n Word number
        @return Pointer for the beginning of the word

*/
char *get_word(char *s, int n) {
  int index = 0;
  int word_number = 1;
  while (word_number != n) {
    if (*(s + index) == ' ' && *(s + index + 1) != ' ') {
      word_number++;
    }
    index++;
  }
  return s + index;
}

/**
        Finds the secret message according to instructions and saves it in a
   character array
        @param lines Pointer to the 2D array containing the text
        @param instructions Pointer to the array containing the instruction
   structures
        @param n_instructions Number of instructions
        @param sentence Pointer to the array that stores the message
*/

void get_sentence(char **lines, struct instruction_s *instructions,
                  int n_instructions, char *sentence) {
  int sentence_index = 0;
  for (int i = 0; i < n_instructions; i++) {
    char *word_begin =
        get_word(lines[instructions[i].step - 1], instructions[i].index);
    int j = 0;
    while (*(word_begin + j) != ' ' &&
           !(*(word_begin + j) == '\n' || *(word_begin + j) == '\r')) {
      if (!ispunct(*(word_begin + j))) {
        *(sentence + sentence_index) = tolower(*(word_begin + j));
        sentence_index++;
      }
      j++;
    }
    *(sentence + sentence_index) = ' ';
    sentence_index++;
  }
  *(sentence + sentence_index) = '\0';
}

int main(int argc, char *argv[]) {

  FILE *textPtr;
  FILE *instructionsPtr;
  if (argc != 3) {
    puts("2 arguments expected");
    return EXIT_FAILURE;
  }

  textPtr = fopen(argv[1], "r");
  if (textPtr == NULL) {
    puts("Couldn't open the text");
    return EXIT_FAILURE;
  }

  instructionsPtr = fopen(argv[2], "r");
  if (textPtr == NULL) {
    puts("Couldn't open the instructions");
    return EXIT_FAILURE;
  }

  char sentence[MAX_LENGTH];
  // Saving the instructions on an array
  struct instruction_s instructions[MAX_LINES];
  fscanf(instructionsPtr, "%d %d", &instructions[0].step,
         &instructions[0].index);
  int n_instructions = 1;
  int step;
  int index;
  while (fscanf(instructionsPtr, "%d %d", &step, &index) == 2) {
    instructions[n_instructions].index = index;
    instructions[n_instructions].step =
        instructions[n_instructions - 1].step + step;
    n_instructions++;
  }
  // Saving the text on an array
  char *text[MAX_LINES];
  for (int i = 0; i < MAX_LINES; i++) {
    text[i] = (char *)malloc(MAX_LENGTH * sizeof(char));
  }
  int j = 0;
  while (!feof(textPtr)) {
    fgets(text[j], MAX_LENGTH + 1, textPtr);
    j++;
  }

  get_sentence(text, instructions, n_instructions, sentence);
  puts(sentence);
  for (int i = 0; i < MAX_LINES; i++) {
    free(text[i]);
  }
  fclose(instructionsPtr);
  fclose(textPtr);
  return EXIT_SUCCESS;
}
