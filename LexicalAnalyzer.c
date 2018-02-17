/*
chrisME1320
A01223255

This lexical analyzer must be able to analyze a file for all its tokens and point out an error if a word couldn't be identified.

The things it must identify are:
  -Reserved identifiers [IMPLEMENTED]
  -Logic operators [IMPLEMENTED]
  -identifiers [IMPLEMENTED]

  -natural numbers
  -octal numbers
  -hex numbers
  -float point numbers
  
  -comments (ignore them)
  -Delimitators (won't check if they're complete)
  -Arithmetic signs
  -Relationship operators
  -punctuation
  -assign operator
  -blank spaces (ignore them)

  It must display the results.
*/


#include <stdio.h>
#include <string.h>

const char ALPHABET[53] =
{
  'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z',
  'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','_'
};
const char HEX[24]={'0','1','2','3','4','5','6','7','8','9','a','b','c','d','e','f','A','B','C','D','E','F','x','X'};

const char KEYWORDS[10][8] = {"program","var","begin","end","if","then","else","and","or","not"};

const char ARITHMETICS[4] = { '+','-','*','/'};
/*
since the second character will always be = if there is one
I simplified it for what I have in mind for my solution
*/
const char RELATIONAL[6][2] = {'=','!','<','>'};
const char PUNCTUATION[3] = {'.',',',';'};
const char DELIMITATORS[4] = {'(',')','[',']'};

const char UNDERSCORE = '_';

void printToken(char sentence[])
{
  printf("%s\n",sentence);
}

int checkForLetter(char letter)
{
  for(int i=0;i<53;i++)
  {
    if(ALPHABET[i]==letter)
    {
      return 1;
    }
  }
  return 0;
}

int checkForDecimalDigit(char digit)
{
  for(int i=0;i<10;i++)
  {
    if(HEX[i]==digit)
    {
      return 1;
    }
  }
  return 0;
}

int checkForOctalDigit(char digit)
{
  for(int i=0;i<8;i++)
  {
    if(HEX[i]==digit)
    {
      return 1;
    }
  }
  return 0;
}

int checkForHexDigit(char digit)
{
  for(int i=0;i<22;i++)
  {
    if(HEX[i]==digit)
    {
      return 1;
    }
  }
  return 0;
}
int isKeyword(char word[])
{
  for(int i=0;i<10;i++)
  {
    if(strcmp(KEYWORDS[i],word)==0)
    {
      if(i>6)
      {
        char sentence[50];
        strcpy(sentence, "Logic Operator [");
        strcat(sentence, KEYWORDS[i]);
        strcat(sentence, "]");
        printToken(sentence);
      }
      else
      {
        char sentence[50];
        strcpy(sentence, "Reserved Identifier [");
        strcat(sentence, KEYWORDS[i]);
        strcat(sentence, "]");
        printToken(sentence);
      }
      return 1;
    }
  }
  return 0;
}

int isIdentifier(char word[])
{
  if(checkForLetter(word[0]))
  {
    char sentence[50];
    strcpy(sentence, "Identifier [");
    strcat(sentence, word);
    strcat(sentence, "]");
    printToken(sentence);
    return 1;
  }
  
  return 0;
}

int isDecimalNumber(char word[], int length)
{
  if(!checkForDecimalDigit(word[0])||word[0]==HEX[0])
  {
    return 0;
  }
  else
  {
    for(int i=1;i<length;i++)
    {
      if(!checkForDecimalDigit(word[i]))
      {
        return 0;
      }
    }
    char sentence[50];
    strcpy(sentence, "Decimal Number [");
    strcat(sentence, word);
    strcat(sentence, "]");
    printToken(sentence);
    return 1;
  }
}

int isOctalNumber(char word[], int length)
{
  if(word[0]==HEX[0])
  {
    for(int i=1;i<length;i++)
    {
      if(!checkForOctalDigit(word[i]))
      {
        return 0;
      }
    }
    char sentence[50];
    strcpy(sentence, "Octal Number [");
    strcat(sentence, word);
    strcat(sentence, "]");
    printToken(sentence);
    return 1;
  }
  else
  {
    return 0;
  }
}

int isHexNumber(char word[], int length)
{
  if(word[0]==HEX[0]&&(word[1]==HEX[23]||word[1]==HEX[22]))
  {
    for(int i=2;i<length;i++)
    {
      if(!checkForHexDigit(word[i]))
      {
        return 0;
      }
    }
    char sentence[50];
    strcpy(sentence, "Hexadecimal Number [");
    strcat(sentence, word);
    strcat(sentence, "]");
    printToken(sentence);
    return 1;
  }
  else
  {
    return 0;
  }
}

int main (int argc, char **argv){

  int result=0;
  result = isKeyword(argv[1]);
  if(result)
  {
    //next word
  }
  result = isIdentifier(argv[1]);
  if(result)
  {
    //next word
  }
  result = isDecimalNumber(argv[1],3);
  if(result)
  {
    //next word
  }
  result = isOctalNumber(argv[1],3);
  if(result)
  {
    //next word
  }
  result = isHexNumber(argv[1],5);
  if(result)
  {
    //next word
  }

  return 0;
}