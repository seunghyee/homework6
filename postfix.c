/** 
 * postfix.c
 *
 * School of Computer Science, 
 * Chungbuk National University
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_STACK_SIZE 10
#define MAX_EXPRESSION_SIZE 20

/* stack 내에서 우선순위, lparen = 0 가장 낮음 */
typedef enum{
   lparen = 0,  /* ( 왼쪽 괄호 */
   rparen = 9,  /* ) 오른쪽 괄호*/
   times = 7,   /* * 곱셈 */
   divide = 6,  /* / 나눗셈 */
   plus = 5,    /* + 덧셈 */
   minus = 4,   /* - 뺄셈 */
   operand = 1 /* 피연산자 */
} precedence;

char infixExp[MAX_EXPRESSION_SIZE];      /* infix expression을 저장하는 배열 */
char postfixExp[MAX_EXPRESSION_SIZE];   /* postfix로 변경된 문자열을 저장하는 배열 */
char postfixStack[MAX_STACK_SIZE];   /* postfix로 변환을 위해 필요한 스택 */
int evalStack[MAX_STACK_SIZE];      /* 계산을 위해 필요한 스택 */

int postfixStackTop = -1;  /* postfixStack용 top */
int evalStackTop = -1;      /* evalStack용 top */

int evalResult = 0;      /* 계산 결과를 저장 */

void postfixPush(char x);
char postfixPop();
void evalPush(int x);
int evalPop();
void getInfix();
precedence getToken(char symbol);
precedence getPriority(char x);
void charCat(char* c);
void toPostfix();
void debug();
void reset();
void evaluation();

int main()
{
   printf("-----[sonseunghye][2023078010-----]\n");
   
   char command;

   do{
      printf("----------------------------------------------------------------\n");
      printf("               Infix to Postfix, then Evaluation               \n");
      printf("----------------------------------------------------------------\n");
      printf(" Infix=i,   Postfix=p,  Eval=e,   Debug=d,   Reset=r,   Quit=q \n");
      printf("----------------------------------------------------------------\n");

      printf("Command = ");
      scanf(" %c", &command);

      switch(command) {
      case 'i': case 'I':
         getInfix();
         break;
      case 'p': case 'P':
         toPostfix();
         break;
      case 'e': case 'E':
         evaluation();
         break;
      case 'd': case 'D':
         debug();
         break;
      case 'r': case 'R':
         reset();
         break;
      case 'q': case 'Q':
         break;
      default:
         printf("\n       >>>>>   Concentration!!   <<<<<     \n");
         break;
      }

   }while(command != 'q' && command != 'Q');

   return 1;
}

void postfixPush(char x)
{
    postfixStack[++postfixStackTop] = x;
}

char postfixPop()
{
    char x;
    if(postfixStackTop == -1)
        return '\0';
    else {
       x = postfixStack[postfixStackTop--];
    }
    return x;
}

void evalPush(int x)
{
    evalStack[++evalStackTop] = x;
}

int evalPop()
{
    if(evalStackTop == -1)
        return -1;
    else
        return evalStack[evalStackTop--];
}

void getInfix()
{
    printf("Type the expression >>> ");
    scanf("%s", infixExp);
}

precedence getToken(char symbol)
{
   switch(symbol) {
   case '(' : return lparen;
   case ')' : return rparen;
   case '+' : return plus;
   case '-' : return minus;
   case '/' : return divide;
   case '*' : return times;
   default : return operand;
   }
}

precedence getPriority(char x)
{
   return getToken(x);
}

void charCat(char* c)
{
   if (postfixExp[0] == '\0')
      strncpy(postfixExp, c, 1);
   else
      strncat(postfixExp, c, 1);
}

void toPostfix()
{
   char *exp = infixExp;
   char x;

   while(*exp != '\0')
   {
      if(getToken(*exp) == operand) // 피연산자인 경우
         charCat(exp); // 피연산자를 바로 postfixExp에 추가
      else // 연산자인 경우
      {
         if(*exp == '(') // 왼쪽 괄호인 경우
            postfixPush(*exp); // 스택에 넣음
         else if(*exp == ')') // 오른쪽 괄호인 경우
         {
            while(postfixStack[postfixStackTop] != '(') // 왼쪽 괄호를 만날 때까지
               charCat(&postfixStack[postfixStackTop--]); // 스택의 연산자를 postfixExp에 추가
            postfixPop(); // 왼쪽 괄호 제거
         }
         else // 연산자인 경우
         {
            while(getPriority(postfixStack[postfixStackTop]) >= getPriority(*exp)) // 스택의 연산자의 우선순위가 더 높거나 같은 경우
               charCat(&postfixStack[postfixStackTop--]); // 스택의 연산자를 postfixExp에 추가
            postfixPush(*exp); // 현재 연산자 스택에 넣음
         }
      }
      exp++; // 다음 문자로 이동
   }
   while(postfixStackTop != -1) // 스택이 비어있지 않을 때
      charCat(&postfixStack[postfixStackTop--]); // 스택의 모든 연산자를 postfixExp에 추가
}

void debug()
{
   printf("\n---DEBUG\n");
   printf("infixExp =  %s\n", infixExp);
   printf("postExp =  %s\n", postfixExp);
   printf("eval result = %d\n", evalResult);

   printf("postfixStack : ");
   for(int i = 0; i < MAX_STACK_SIZE; i++)
      printf("%c  ", postfixStack[i]);

   printf("\n");
}

void reset()
{
   infixExp[0] = '\0';
   postfixExp[0] = '\0';

   for(int i = 0; i < MAX_STACK_SIZE; i++)
      postfixStack[i] = '\0';

   postfixStackTop = -1;
   evalStackTop = -1;
   evalResult = 0;
}

void evaluation()
{
    char *exp = postfixExp;
    char x;
    int op1, op2;

    while (*exp != '\0')
    {
        if (getToken(*exp) == operand) // 피연산자인 경우
        {
            evalPush(*exp - '0'); // 문자를 숫자로 변환하여 스택에 푸시
        }
        else // 연산자인 경우
        {
            op2 = evalPop(); // 먼저 꺼낸 피연산자
            op1 = evalPop(); // 그 다음에 꺼낸 피연산자

            switch (*exp)
            {
            case '+':
                evalPush(op1 + op2);
                break;
            case '-':
                evalPush(op1 - op2);
                break;
            case '*':
                evalPush(op1 * op2);
                break;
            case '/':
                evalPush(op1 / op2);
                break;
            }

        }
        exp++; // 다음 문자로 이동
    }
    evalResult = evalPop(); // 최종 결과를 evalResult에 저장
}
