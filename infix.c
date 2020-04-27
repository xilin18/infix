#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

typedef enum {lparen, rparen, plus, minus, times, divide, mod, eos, operand} precedence;
char expr[1111];
int stack[1111];
static int isp[] = { 0, 19, 12, 12, 13, 13, 13, 0 };
static int icp[] = { 20, 19, 12, 12, 13, 13, 13, 0 };

void printToken(precedence token,char** s);
precedence getToken(char* symbol, int* n);

void postfix(void);
void push(int* top, int token);
int pop(int* top);

int main(void)
{
	scanf("%s", expr);
	postfix();
	printf("%s\n", expr);
	return 0;
}
void postfix()
{
	precedence token;
	char symbol;
	int n=0;
	int top = 0;
	char temp[1111] = { 0, };
	char* s = temp;
	stack[0] = eos;

	for (token = getToken(&symbol, &n); token != eos; token = getToken(&symbol, &n))
	{
		if (token == operand)
		{
			*s++ = symbol;
		}
		else if(token == rparen)
		{
			while (stack[top] != lparen)
				printToken(pop(&top),&s);
			pop(&top);
		}
		else
		{
			while (isp[stack[top]] >= icp[token])
				printToken(pop(&top), &s);
			push(&top,token);
		}
	}
	while ((token = pop(&top)) != eos)
		printToken(token,&s);
	
	strcpy(expr, temp);
}
void printToken(precedence token, char** s)
{
	switch (token)
	{
	case plus: *(*s)++ = '+'; return;
	case minus: *(*s)++ = '-'; return;
	case times: *(*s)++ = '*'; return;
	case divide: *(*s)++ = '/'; return;
	case mod: *(*s)++ = '%'; return;
	case eos: return;
	default: return;
	}
}
precedence getToken(char* symbol, int* n)
{
	*symbol = expr[(*n)++];
	switch (*symbol)
	{
	case '(': return lparen;
	case ')': return rparen;
	case '+': return plus;
	case '-': return minus; 
	case '*': return times;
	case '/': return divide;
	case '%': return mod;
	case '\0': return eos;
	default: return operand;
	}
}
void push(int* top, int token)
{
	if ((*top) >= 1111) exit(1);
	stack[++(*top)] = token;
}
int pop(int* top)
{
	if ((*top) == -1) return eos;
	return stack[(*top)--];
}