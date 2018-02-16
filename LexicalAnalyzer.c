/*
chrisME1320
A01223255

This lexical analyzer must be able to analyze a file for all its tokens and point out an error if a word couldn't be identified.

The things it must identify are:
  -identifiers [IN PROGRESS]
  -natural numbers
  -octal numbers
  -hex numbers
  -float point numbers
  -comments (ignore them)
  -Delimitators (won't check if they're complete)
  -Arithmetic signs
  -Logic operators
  -Relationship operators
  -punctuation
  -assign operator
  -Reserved identifiers [IMPLEMENTED]
  -blank spaces (ignore them)

  It must display the results.
*/


#include <stdio.h>
#include <string.h>

const char ALPHABET[52] =
{
  'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z',
  'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'
};
const char NUMBERS[10] = {'0','1','2','3','4','5','6','7','8','9'};
const char OCTAL[8] = {'0','1','2','3','4','5','6','7'};
const char HEX[24]={'0','1','2','3','4','5','6','7','8','9','a','b','c','d','e','f','A','B','C','D','E','F','x','X'};

const char KEYWORDS[7][8] = {"program","var","begin","end","if","then","else"};
const char ARITHMETICS[4] = { '+','-','*','/'};
const char LOGIC[3][3] = {"and","or","not"};
const char RELATIONAL[6][2] = {"==","!=","<",">","<=",">="};
const char PUNCTUATION[3] = {'.',',',';'};
const char DELIMITATORS[4] = {'(',')','[',']'};

const char ASSIGN_OPERATOR = '=';
const char UNDERSCORE = '_';

void printToken(char sentence[])
{
  printf("%s\n",sentence);
}
int checkInAlphabet(char letter)
{
  for(int i=0;i<52;i++)
  {
    if(ALPHABET[i]==letter)
    {
      return 1;
    }
  }
  return 0;
}
int isKeyword(char word[])
{
  for(int i=0;i<7;i++)
  {
    if(strcmp(KEYWORDS[i],word)==0)
    {
      char sentence[100];
      strcpy(sentence, "Reserved Identifier [");
      strcat(sentence, KEYWORDS[i]);
      strcat(sentence, "]");
      printToken(sentence);
      return 1;
    }
  }
  return 0;
}
int isIdentifier(char word[], int wordLength)
{
  if(checkInAlphabet(word[0],ALPHABET)||word[0]==UNDERSCORE)
  {
    return 1;
  }
  else
  {
    return 0;
  }
}

int main (int argc, char **argv){
  char word[8]="if";
  int result = isKeyword(word);

  return 0;
}