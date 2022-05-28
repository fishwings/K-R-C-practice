#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAXOP 100
#define NUMBER '0'

int getop(char []);
void push (double);
double pop (void);

/* reverse Polish calculator*/
int main() 
{
    int type;
    double op2;
    char s[MAXOP];
    while ((type = getop(s)) != EOF)
    {
        switch (type)
        {
        case NUMBER:
            push(atof(s));
            break;
        case '+':
            push(pop() + pop());
            break;
        case '*':
            push(pop() * pop());
            break;
        case '-':
            op2 = pop();
            push(pop() - op2);
            break;
        case '/':
            op2= pop();
            if (op2 != 0.0)
            {
                push(pop() / op2);
            } else 
            {
                printf("error: zero divisor\n");
            }
            break;
        case '\n' :
            printf("\t%.8g\n", pop());
            break;
        default:
            printf("error: unknow command %s\n", s);
            break;
        }
    }
    return 0;
}

#define MAXVAL 100 /* maximum depth of val stack*/
int sp = 0; /* next free stack position */
double val[MAXVAL]; /* value stack */

/* push: push f onto value stack */
void push (double f)
{
    if (sp < MAXVAL)
    {
        val[sp++] = f;
    } else 
    {
        printf("error: stack full, can't push %g\n", f);
    }
    
}

/* pop: pop and return top value from stack */
double pop(void) 
{
    if (sp > 0)
    {
        return val[--sp];
    } else
    {
        printf("error: stack empty \n");
        return 0.0;
    }
    
}

int getch(void);
void ungetch(int);

/* getop: get next character or numeric operand */
int getop(char s[])
{
    int i, c;
    while ((s[0] = c = getch()) == ' ' || c == '\t')  ;
    s[1] = '\0';
    if (!isdigit(c) && c != '.')
    {
        return c;
    }
    i = 0;
    if (isdigit(c)) /* collect integer part*/
    {
        while (isdigit(s[++i] = c = getch()))
            ;
    }
    if (c == '.')
    {
        while(isdigit(s[++i] = c = getch()))
        ;
    }
    s[i] = '\0';
    if (c != EOF)
    {
        ungetch(c);
    }
    return NUMBER;
    
}