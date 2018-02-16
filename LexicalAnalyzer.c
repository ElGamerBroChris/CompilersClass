#include<iostream>
#include<fstream>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

const char ALPHABET[52] =
{
  'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z',
  'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'
};
const char NUMBERS[10] = {'0','1','2','3','4','5','6','7','8','9'};
const char OCTAL[8] = {'0','1','2','3','4','5','6','7'};
const char HEX[24]={'0','1','2','3','4','5','6','7','8','9','a','b','c','d','e','f','A','B','C','D','E','F','x','X'};

const char KEYWORDS[7][7] = {"program","var","begin","end","if","then","else"};
const char ARITHMETICS[4] = { '+','-','*','/'};
const char LOGIC[3][3] = {"and","or","not"};
const char RELATIONAL[6][2] = {"==","!=","<",">","<=",">="};
const char PUNCTUATION[3] = {'.',',',';'};

const char ASSIGN_OPERATOR = '=';
const char UNDERSCORE = '_';

/*
The other things needed to be identified are:
  comments
  space, tab, breakline
*/