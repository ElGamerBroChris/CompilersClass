/*
chrisME1320
A01223255
SyntaxAnalyzer

Makes sure that the written snippet follows the Tiny grammar.
*/

#include <stdio.h>
#include <string.h>

char tokens[100][10];
char keywords[10][10] = { "if","then","end","else","repeat","until","read","write",";"};
char operands[4][2] = {"*","/","+","-"};
char factor[4][7] = {"(",")","id","number"};
char compare[5][3] = {"<","=",">","<=",">="};
int index = 0,
	max = -1;

int isOperand(int index)
{
	for(int i=0;i<4;i++)
	{
		if(strcmp(tokens[index],operands[i])==0)
		{
			return 1;
		}
	}
	return 0;
}
int isCompare(int index)
{
	for(int i=0;i<5;i++)
	{
		if(strcmp(tokens[index],compare[i])==0)
		{
			return 1;
		}
	}
	return 0;
}

int isKeyword(int index)
{
	for(int i=0;i<10;i++)
	{
		if(strcmp(tokens[index],keywords[i])==0)
		{
			return 1;
		}
	}
	return 0;
}

int isFactor(int index)
{
	for(int i=0;i<4;i++)
	{
		if(strcmp(tokens[index],factor[i])==0)
		{
			return 1;
		}
	}
	return 0;
}

int sentIf()
{
	printf("%s ", tokens[index]);
	if(!checkExpression())
	{
		return 0;
	}
	index++;
	if(strcmp(tokens[index],"then")==0)
	{
		printf("%s ", tokens[index]);
		index++;
		while(sentence())
		{
			index++;
		}
		index--;
		if(strcmp(tokens[index],"end")==0)
		{
			printf("%s ", tokens[index]);
			return 1;
		}
		else if(strcmp(tokens[index] , "else") == 0)
		{
			printf("%s ", tokens[index]);
			index++;
			while(sentence())
			{
				index++;
			}
			index--;
			if(strcmp(tokens[index],"end")==0)
			{
				printf("%s ", tokens[index]);
				return 1;
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
	else
	{
		return 0;
	}
}
int sentRepeat()
{
	printf("%s ", tokens[index]);
	index++;
	while(sentence())
	{
		index++;
	}
	index--;
	if(strcmp(tokens[index],"until")==0)
	{
		printf("%s ", tokens[index]);
		return checkExpression();
	}
	else
	{
		return 0;
	}
	return 1;
}
int sentAssign()
{
	printf("%s ", tokens[index]);
	index++;
	
	if(strcmp(tokens[index],":=")==0)
	{
		printf("%s ", tokens[index]);
		return checkExpression();
	}
	else
	{
		return 0;
	}
}
int sentRead()
{
	printf("%s ", tokens[index]);
	index++;
	if(strcmp(tokens[index],"id")==0)
	{
		printf("%s ", tokens[index]);
		return 1;
	}
	return 0;
}
int sentWrite()
{
	printf("%s ", tokens[index]);
	return checkExpression();
}
int checkExpression()
{
	index++;
	
	int number = 0,
		parentheses = 0;

	while(!isKeyword(index))
	{
		if(number == 0 && isFactor(index))
		{
			if(strcmp(tokens[index],"number")==0 || strcmp(tokens[index],"id")==0)
			{
				number++;
			}
			else if(strcmp(tokens[index],"(")==0)
			{
				parentheses++;
			}
			else
			{
				return 0;
			}
		}
		else if(number == 1 && (isCompare(index) || isOperand(index) || (strcmp(tokens[index],")")==0 && parentheses>0)))
		{
			if((strcmp(tokens[index],")")==0 && parentheses>0))
			{
				parentheses--;
			}
			else
			{
				number--;
			}
		}
		else
		{
			return 0;
		}
		printf("%s ", tokens[index]);
		index++;
	}
	index--;
	return parentheses == 0;
}

int sentence()
{
	int result = 0;
	char token[10];
	strcpy(token,tokens[index]);

	if(strcmp(token,"if")==0)
	{
		result=sentIf();
	}
	else if(strcmp(token,"repeat")==0)
	{
		result=sentRepeat();
	}
	else if(strcmp(token,"id")==0)
	{
		result=sentAssign();
	}
	else if(strcmp(token,"read")==0)
	{
		result=sentRead();
	}
	else if(strcmp(token,"write")==0)
	{
		result=sentWrite();
	}
	index++;
	if(strcmp(tokens[index],";")==0&&result!=0)
	{
		printf("%s ", tokens[index]);
	}
	else
	{
		result = 0;
	}

	return result;
}

int load()
{
	FILE *fp;
	char line[1000];
	char * token;

	fp = fopen("testForSyntax.txt", "r");
	if (fp == NULL)
	{
		printf("Could not open file testForSyntax.txt");

	    return 0;
	}
	  
	fgets(line, 1000, fp);

	token = strtok(line," ");
	while(token != NULL)
	{
		strcpy(tokens[index],token);
		index++;
		max++;
		token = strtok(NULL," ");	
	}
	fclose(fp);
	index = 0;
	return 1;
}

int program()
{
	int result = 0;
	if(load())
	{
		result = sentence();
	}
	return result;
}

int main ()
{
	if(program())
	{
		printf("\nThe program passed the syntax analysis\n");
	}
	else
	{
		printf("\nThe program failed the syntax analysis\n");
	}
	return 0;
}