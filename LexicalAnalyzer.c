/*
chrisME1320
A01223255
LexicalAnalyzer

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

#define MAXCHAR 1000

const char ALPHABET[53] =
{
  'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z',
  'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','_'
};
const char HEX[24]={'0','1','2','3','4','5','6','7','8','9','a','b','c','d','e','f','A','B','C','D','E','F','x','X'};

const char KEYWORDS[10][8] = {"program","var","begin","end","if","then","else","and","or","not"};

const char BLANKS[4]={' ','\t','\n'};
const char ARITHMETICS[4] = { '+','-','*','/'};
/*
since the second character will always be = if there is one
I simplified it for what I have in mind for my solution
*/
const char RELATIONAL[6] = {'=','!','<','>'};
const char PUNCTUATION[3] = {',',';','.'};
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

int checkForSymbol(char symbol)
{
  for(int i=0;i<3;i++)
  {
    if(symbol==BLANKS[i])
    {
      return 1;
    }
  }
  for(int i=0;i<4;i++)
  {
    if(symbol==ARITHMETICS[i])
    {
      return 2;
    }
  }
  for(int i=0;i<4;i++)
  {
    if(symbol==RELATIONAL[i])
    {
      return 3;
    }
  }
  for(int i=0;i<2;i++)
  {
    if(symbol==PUNCTUATION[i])
    {
      return 4;
    }
  }
  for(int i=0;i<4;i++)
  {
    if(symbol==DELIMITATORS[i])
    {
      return 5;
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

int isFloatNumber(char word[],int length)
{
  int period=0;
  int exponent=0;
  for(int i=0;i<length;i++)
  {
    if(checkForDecimalDigit(word[i])||word[i]=='.'||word[i]=='e'||word[i]=='+'||word[i]=='-')
    {
      if(word[i]=='.'&&!period)
      {
        i++;
        if(i<length)
        {
          if(!checkForDecimalDigit(word[i]))
          {
            return 0;
          }
          period++;
        }
        else
        {
          return 0;
        }
      }
      else if(word[i]=='.'&&period)
      {
        return 0;
      }
      if(word[i]=='e'&&!exponent)
      {
        i++;
        if(i<length)
        {
          if(!(word[i]=='+'||word[i]=='-'))
          {
            return 0;
          }
          i++;
          if(i<length)
          {
            if(!checkForDecimalDigit(word[i]))
            {
              return 0;
            }
            exponent++;
          }
          else
          {
            return 0;
          }
        }
        else
        {
          return 0;
        }
      }
      else if(word[i]=='e'&&exponent)
      {
        return 0;
      }
      if((word[i]=='+'||word[i]=='-')&&!exponent)
      {
        return 0;
      }
    }
    else
    {
      return 0;
    }
  }
  char sentence[50];
  strcpy(sentence, "Float Number [");
  strcat(sentence, word);
  strcat(sentence, "]");
  printToken(sentence);

  return 1;
}

int checkLexeme(char * word, int length, int * error)
{
  int result=0;
  if(word[0]=='\0')
  {
    return 1;
  }
  result = isKeyword(word);
  if(result)
  {
    *error=0;
    return 1;
  }
  result = isIdentifier(word);
  if(result)
  {
    *error=0;
    return 1;
  }
  result = isDecimalNumber(word,length);
  if(result)
  {
    *error=0;
    return 1;
  }
  result = isOctalNumber(word,length);
  if(result)
  {
    *error=0;
    return 1;
  }
  result = isHexNumber(word,length);
  if(result)
  {
    *error=0;
    return 1;
  }
  if(result)
  {
    *error=0;
    return 1;
  }
  *error=1;
  return 0;
}

int main (int argc, char **argv){
  FILE *fp;
  char line[MAXCHAR];
  char filename[100];
  char add[2];
  strcpy(filename,argv[1]);
  char word[20];
  int lineNumber=1;
  int InComment,error=0;

  add[1]='\0';
 
  fp = fopen(filename, "r");
  if (fp == NULL)
  {
    printf("Could not open file %s",filename);
    return 1;
  }
  
  while ((fgets(line, MAXCHAR, fp) != NULL)&&!error)
  {
    int result=0,begin=0,end=0;
    InComment=0;
    while(line[end]!='\n'&&!InComment&&!error)
    {
      if(end>0)
      {
        end++;
        begin=end;  
      }

      word[0]='\0';
      result=checkForSymbol(line[end]);
      while(!result)
      {
        add[0]=line[end];
        strcat(word, add);
        end++;
        result=checkForSymbol(line[end]);
      }
      switch(result)
      {
        case 1:
          checkLexeme(word,end-begin,&error);   
          break;

        case 2:
          checkLexeme(word,end-begin,&error);
          if(line[end]==ARITHMETICS[3]&&line[end+1]==ARITHMETICS[3])
          {
            InComment=1;
          }
          else
          {
            char sentence[50];
            add[0]=line[end];
            strcpy(sentence, "Arithmetic Identifier [");
            strcat(sentence, add);
            strcat(sentence, "]");
            printToken(sentence);
          }
          break;

        case 3:
          checkLexeme(word,end-begin,&error);
          if(line[end]==RELATIONAL[0]&&line[end+1]!=RELATIONAL[0])
          {
            char sentence[50];
            add[0]='=';
            strcpy(sentence, "Assignment [");
            strcat(sentence, add);
            strcat(sentence, "]");
            printToken(sentence);
          }
          else if(line[end]==RELATIONAL[0]&&line[end+1]==RELATIONAL[0])
          {
            char sentence[50];
            strcpy(sentence, "Equals Operator [==]");
            printToken(sentence);
            end++;
          }
          else if(line[end]==RELATIONAL[1])
          {
            if(line[end+1]!=RELATIONAL[0])
            {
              printf("Error in %d, couldn't identify %s\n",lineNumber,word);
              error=1;
            }
            else
            {
              char sentence[50];
              strcpy(sentence, "Not Equals Operator [!=]");
              printToken(sentence);
              end++;
            }
          }
          else if(line[end]==RELATIONAL[2])
          {
            if(line[end+1]!=RELATIONAL[0])
            {
              char sentence[50];
              strcpy(sentence, "Lesser Than Operator [<]");
              printToken(sentence);
            }
            else
            {
              char sentence[50];
              strcpy(sentence, "Lesser Or Equals Than Operator [<=]");
              printToken(sentence);
              end++;
            }
          }
          else if(line[end]==RELATIONAL[3])
          {
            if(line[end+1]!=RELATIONAL[0])
            {
              char sentence[50];
              strcpy(sentence, "Greater Than Operator [>]");
              printToken(sentence);
            }
            else
            {
              char sentence[50];
              strcpy(sentence, "Greater Or Equals Than Operator [>=]");
              printToken(sentence);
              end++;
            }
          }
          break;
        
        case 4:
          checkLexeme(word,end-begin,&error);
          if(line[end]==',')
          {
            printf("Coma [,]\n");
          }
          else if(line[end]==';')
          {
            printf("Semicolon [;]\n");
          }
          else if(line[end]=='.')
          {
            printf("Period [.]\n");
          }
          break;

        case 5:
          checkLexeme(word,end-begin,&error);
          if(line[end]=='(')
          {
            printf("Left Parenthesis [(]\n");
          }
          else if(line[end]==')')
          {
            printf("Right Parenthesis [)]\n");
          }
          if(line[end]=='[')
          {
            printf("Left Bracket [[]\n");
          }
          if(line[end]==']')
          {
            printf("Right Bracket []]\n");
          }
          break;
      }
      /*if(!checkLexeme(word,end-begin))
      {
        printf("end is: %d\n",end);
        printf("begin is: %d\n",begin);
      }*/
    }
    if(error)
    {
      printf("Error in line %d\n", lineNumber);
    }
    lineNumber++;
  }
  fclose(fp);

  return 0;
}