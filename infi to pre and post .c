/* This program converts infix expression to postfix expression.
 * This program assume that there are Five operators: (*, /, +, -,^)
	in infix expression and operands can be of single-digit only.
 * This program will not work for fractional numbers.
 * Further this program does not check whether infix expression is
 valid or not in terms of number of operators and operands.*/

#include<stdio.h>
#include <conio.h>
#include<stdlib.h>      /* for exit() */
#include<ctype.h>     /* for isdigit(char ) */
#include<string.h>

#define MAX 100


/* declared here as global variable because stack[]
* is used by more than one fucntions */
struct infix
{
	char target[MAX] ;
	char stack[MAX] ;
	char *s, *t ;
	int top, l ;
} ;

void initinfix ( struct infix * ) ;
void setexpr ( struct infix *, char * ) ;
void push ( struct infix *, char ) ;
char pop ( struct infix * ) ;
void convert ( struct infix * ) ;
int priority ( char c ) ;
void show ( struct infix ) ;





char stack[MAX];
int top = -1;

/* define push operation */

void push1(char item)
{
	if(top >= MAX-1)
	{
		printf("\nStack Overflow.");
	}
	else
	{
		top = top+1;
		stack[top] = item;
	}
}

/* define pop operation */
char pop1()
{
	char item ;

	if(top <0)
	{
		printf("stack under flow: invalid infix expression");
		getchar();
		/* underflow may occur for invalid expression */
		/* where ( and ) are not matched */
		exit(1);
	}
	else
	{
		item = stack[top];
		top = top-1;
		return(item);
	}
}

/* define function that is used to determine whether any symbol is operator or not
(that is symbol is operand)
* this fucntion returns 1 if symbol is opreator else return 0 */

int is_operator(char symbol)
{
	if(symbol == '^' || symbol == '*' || symbol == '/' || symbol == '+' || symbol =='-')
	{
		return 1;
	}
	else
	{
	return 0;
	}
}

/* define fucntion that is used to assign precendence to operator.
* Here ^ denotes exponent operator.
* In this fucntion we assume that higher integer value
* means higher precendence */

int precedence(char symbol)
{
	if(symbol == '^')/* exponent operator, highest precedence*/
	{
		return(3);
	}
	else if(symbol == '*' || symbol == '/')
	{
		return(2);
	}
	else if(symbol == '+' || symbol == '-')          /* lowest precedence */
	{
		return(1);
	}
	else
	{
		return(0);
	}
}

void InfixToPostfix(char infix_exp[], char postfix_exp[])
{
	int i, j;
	char item;
	char x;

	push1('(');                               /* push '(' onto stack */
	strcat(infix_exp,")");                  /* add ')' to infix expression */

	i=0;
	j=0;
	item=infix_exp[i];         /* initialize before loop*/

	while(item != '\0')        /* run loop till end of infix expression */
	{
		if(item == '(')
		{
			push1(item);
		}
		else if( isdigit(item) || isalpha(item))
		{
			postfix_exp[j] = item;              /* add operand symbol to postfix expr */
			j++;
		}
		else if(is_operator(item) == 1)        /* means symbol is operator */
		{
			x=pop1();
			while(is_operator(x) == 1 && precedence(x)>= precedence(item))
			{
				postfix_exp[j] = x;                  /* so pop all higher precendence operator and */
				j++;
				x = pop1();                       /* add them to postfix expresion */
			}
			push1(x);
			/* because just above while loop will terminate we have
			oppped one extra item
			for which condition fails and loop terminates, so that one*/

			push1(item);                 /* push current oprerator symbol onto stack */
		}
		else if(item == ')')         /* if current symbol is ')' then */
		{
			x = pop1();                   /* pop and keep popping until */
			while(x != '(')                /* '(' encounterd */
			{
				postfix_exp[j] = x;
				j++;
				x = pop1();
			}
		}
		else
		{ /* if current symbol is neither operand not '(' nor ')' and nor
			operator */
			printf("\nInvalid infix Expression.\n");        /* the it is illegeal  symbol */
			getchar();
			exit(1);
		}
		i++;


		item = infix_exp[i]; /* go to next symbol of infix expression */
	} /* while loop ends here */
	if(top>0)
	{
		printf("\nInvalid infix Expression.\n");        /* the it is illegeal  symbol */
		getchar();
		exit(1);
	}
	if(top>0)
	{
		printf("\nInvalid infix Expression.\n");        /* the it is illegeal  symbol */
		getchar();
		exit(1);
	}


	postfix_exp[j] = '\0'; /* add sentinel else puts() fucntion */
	/* will print entire postfix[] array upto SIZE */

}

/* main function begins */
int main()
{
    int choice=0;

	struct infix q ;
	char expr[MAX], postfix[MAX];         /* declare infix string and postfix string */

	initinfix ( &q ) ;

    printf ( "\n\n --- Welcome to POSTFIX and PREFIX Calculator --- \n" );    //(A+B)/(C/D)

	printf("\n[ASSUMPTION: The Infix expression contains single letter variables and single digit constants only.]\n");
    printf("\n Enter your valid Infix expression : ");
    gets(expr);

        printf("\n\nChose one from the below options...\n");
        printf("\n1. Infix to Postfix.\n2. Infix to Prefix. \n");
        printf("\nEnter your choice: ");
        scanf("%d",&choice);
if(choice==1){

	InfixToPostfix(expr,postfix);                   /* call to convert */
	printf("\n Postfix Expression: ");
	puts(postfix);

    }
    else if (choice==2){



	setexpr ( &q, expr ) ;
	convert ( &q ) ;
	printf ( "\n The Prefix expression is: " ) ;
	show ( q ) ;
	getch( ) ;
    }
    else return 0;


   }

   /* initializes elements of structure variable */
void initinfix ( struct infix *pq )
{
	pq -> top = -1 ;
	strcpy ( pq -> target, "" ) ;
	strcpy ( pq -> stack, "" ) ;
	pq -> l = 0 ;
}
/* reverses the given expression */
void setexpr ( struct infix *pq, char *str )
{
	pq -> s = str ;
	strrev ( pq -> s ) ;
	pq -> l = strlen ( pq -> s ) ;
	*( pq -> target + pq -> l ) = '\0' ;
	pq -> t = pq -> target + ( pq -> l - 1 ) ;
}
/* adds operator to the stack */
void push ( struct infix *pq, char c )
{
	if ( pq -> top == MAX - 1 )
		printf ( "\nStack is full.\n" ) ;
	else
	{
		pq -> top++ ;
		pq -> stack[pq -> top] = c ;
	}
}
/* pops an operator from the stack */
char pop ( struct infix *pq )
{
	if ( pq -> top == -1 )
	{
		//printf ( "Stack is empty\n" ) ;
		return -1 ;
	}
	else
	{
		char item = pq -> stack[pq -> top] ;
		pq -> top-- ;
		return item ;
	}
}
/* converts the infix expr. to prefix form */
void convert ( struct infix *pq )
{
	char opr ;
	while ( *( pq -> s ) )
	{
		if ( *( pq -> s ) == ' ' || *( pq -> s ) == '\t' )
		{
			pq -> s++ ;
			continue ;
		}
		if ( isdigit ( *( pq -> s ) ) || isalpha ( *( pq -> s ) ) )
		{
			while ( isdigit ( *( pq -> s ) ) || isalpha ( *( pq -> s ) ) )
			{
				*( pq -> t ) = *( pq -> s ) ;
				pq -> s++ ;
				pq -> t-- ;
			}
		}
		if ( *( pq -> s ) == ')' )
		{
			push ( pq, *( pq -> s ) ) ;
			pq -> s++ ;
		}
		if ( *( pq -> s ) == '*' || *( pq -> s ) == '+' || *( pq -> s ) == '/' || *( pq -> s ) == '%' || *( pq -> s ) == '-' || *( pq -> s ) == '$' )
		{
			if ( pq -> top != -1 )
			{
				opr = pop ( pq ) ;
				while ( priority ( opr ) > priority ( *( pq -> s ) ) )
				{
					*( pq -> t ) = opr ;
					pq -> t-- ;
					opr = pop ( pq ) ;
				}
				push ( pq, opr ) ;
				push ( pq, *( pq -> s ) ) ;
			}
			else
				push ( pq, *( pq -> s ) ) ;
				pq -> s++ ;
		}
		if ( *( pq -> s ) == '(' )
		{
			opr = pop ( pq ) ;
			while ( opr != ')' )
			{
				*( pq -> t ) = opr ;
				pq -> t-- ;
				opr = pop ( pq ) ;
			}
			pq -> s++ ;
		}
	}
	while ( pq -> top != -1 )
	{
		opr = pop ( pq ) ;
		*( pq -> t ) = opr ;
		pq -> t-- ;
	}
	pq -> t++ ;
}
/* returns the priotity of the operator */
int priority ( char c )
{
	if ( c == '$' )
		return 3 ;
	if ( c == '*' || c == '/' || c == '%' )
		return 2 ;
	else
	{
		if ( c == '+' || c == '-' )
			return 1 ;
		else
			return 0 ;
	}
}
/* displays the prefix form of given expr. */
void show ( struct infix pq )
{
	while ( *( pq.t ) )
	{
		printf ( " %c", *( pq.t ) ) ;
		pq.t++ ;
	}
}




