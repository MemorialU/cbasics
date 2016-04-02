/*
* A basic reverse polish-notation calculator
*/

//TODO: Consider implementing this using GMP (GNU Muliple Precision Aritmetic Library
//TODO: Provide Stirling's Approximation for large factorials

#include <ctype.h>
#include <float.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXOP   100 // Maximum size of operand and operators
#define MAXVARS  26 // Maximum number of variables (26 letters)
#define NUMBER  '0' // Signal for a NUMBER
#define NAME    'n' // Signal for a NAME

// External declarations

char   getop(char[]);
void   dapush(double);
double dapop(void);
double dapeek(void);
size_t dasize(void);
void   dadup(void);
void   daswap(void);
void   dalist(void);
void   daclear(void);

// Handle Math functions

static void mathfun(char s[]) {

	double operand; // Temporary operand

	if (strcmp(s, "sin") == 0)           // sin
		if (dasize() > 0)
			dapush(sin(dapop()));
		else
			printf("Stack is empty\n");
	else if (strcmp(s, "cos") == 0)      // cos
		if (dasize() > 0)
			dapush(cos(dapop()));
		else
			printf("Stack is empty\n");
	else if (strcmp(s, "acos") == 0)      // acos
		if (dasize() > 0)
			dapush(acos(dapop()));
		else
			printf("Stack is empty\n");
	else if (strcmp(s, "asin") == 0)      // asin
		if (dasize() > 0)
			dapush(asin(dapop()));
		else
			printf("Stack is empty\n");
	else if (strcmp(s, "atan2") == 0)      // atan2
		if (dasize() > 1) {
			operand = dapop();
			dapush(atan2(dapop(), operand));
		} else
			printf("Less than two items are on the stack\n");
	else if (strcmp(s, "atan") == 0)      // atan
		if (dasize() > 0)
			dapush(atan(dapop()));
		else
			printf("Stack is empty\n");
	else if (strcmp(s, "ceil") == 0)      // ceil
		if (dasize() > 0)
			dapush(ceil(dapop()));
		else
			printf("Stack is empty\n");
	else if (strcmp(s, "cosh") == 0)      // cosh
		if (dasize() > 0)
			dapush(cosh(dapop()));
		else
			printf("Stack is empty\n");
	else if (strcmp(s, "floor") == 0)      // floor
		if (dasize() > 0)
			dapush(floor(dapop()));
		else
			printf("Stack is empty\n");
	else if (strcmp(s, "log") == 0)      // log
		if (dasize() > 0)
			dapush(log(dapop()));
		else
			printf("Stack is empty\n");
	else if (strcmp(s, "log10") == 0)      // log10
		if (dasize() > 0)
			dapush(log10(dapop()));
		else
			printf("Stack is empty\n");
	else if (strcmp(s, "sinh") == 0)      // sinh
		if (dasize() > 0)
			dapush(sinh(dapop()));
		else
			printf("Stack is empty\n");
	else if (strcmp(s, "sqrt") == 0)      // sqrt
		if (dasize() > 0)
			dapush(sqrt(dapop()));
		else
			printf("Stack is empty\n");
	else if (strcmp(s, "tan") == 0)      // tan
		if (dasize() > 0)
			dapush(tan(dapop()));
		else
			printf("Stack is empty\n");
	else if (strcmp(s, "tanh") == 0)      // tanh
		if (dasize() > 0)
			dapush(tanh(dapop()));
		else
			printf("Stack is empty\n");
	else if (strcmp(s, "exp") == 0)      // exp
		if (dasize() > 0)
			dapush(exp(dapop()));
		else
			printf("Stack is empty\n");
	else if (strcmp(s, "pi") == 0)      // pi (constant)
		dapush(3.14159265L);
	else if (strcmp(s, "phi") == 0)     // phi (constant)
		dapush(1.61803399L);
	else if (strcmp(s, "quit") == 0)    // quit
		exit(EXIT_SUCCESS);
	else if (strcmp(s, "pow") == 0) {   // pow
		if (dasize() > 1) {
			operand = dapop();
			dapush(pow(dapop(), operand));
		} else
			printf("Less than two items are on the stack\n");
	} else
		printf("Error: Unknown function name '%s'\n", s);
}

// Reverse Polish Notation calculator

int main() {

	double vars[MAXVARS];        // Variables
	size_t i;                    // Array indexes
	char   operator[MAXOP] = ""; // Operator
	char   optype;               // Operator type
	double operand;              // Temporary operand
	double lastvalue = 0;        // Last calculated value
	char   lastop = '\0';        // Last operand

	// Clear variables

	for(i = 0; i < MAXVARS; i++)
		vars[i] = 0.0L;

	// Display title and initial prompt

	printf("RPN Calculator (use 'Ctrl-D' or enter \"quit\" to exit)\n\n");
	printf("> ");

	// Start the REPL (read, evaluate, and print loop)

	while ((optype = getop(operator)) != (char)EOF) {
		switch(optype) {
			case NUMBER:
				dapush(atof(operator));
				break;
			case NAME:
				mathfun(operator);
				break;
			case '+':
				if (dasize() < 2)
					printf("Less than two items are on the stack\n");
				else
					dapush(dapop() + dapop());
				break;
			case '-':
				if (dasize() < 1)
					printf("Empty stack\n");
				else if (dasize() < 2)
					dapush(-dapop());
				else {
					operand = dapop();
					dapush(dapop() - operand);
				}
				break;
			case '*':
				if (dasize() < 2)
					printf("Less than two items are on the stack\n");
				else
					dapush(dapop() * dapop());
				break;
			case '/':
				if (dasize() < 2)
					printf("Less than two items are on the stack\n");
				else {
					//TODO: Check floating-point library state
					if (fabs(dapeek() - 0) < DBL_EPSILON)
						printf("Error: Attempted to divide by zero.\n");
					else {
						operand = dapop();
						dapush(dapop() / operand);
					}
				}
				break;
			case '%':
				if (dasize() < 2)
					printf("Less than two items are on the stack\n");
				else {
					//TODO: Check floating-point library state
					if (fabs(dapeek() - 0) < DBL_EPSILON)
						printf("Error: Attempted to divide by zero.\n");
					else {
						operand = dapop();
						dapush(fmod(dapop(), operand));
					}
				}
				break;
			case 'e':
				dapush(2.71828183L);
				break;
			case 'p':
				if (dasize() > 0)
					printf("%.8g\n", dapeek());
				break;
			case 'd':
				dadup();
				break;
			case 's':
				daswap();
				break;
			case 'l':
				dalist();
				break;
			case 'c':
				daclear();
				break;
			case '\n':
				lastvalue = dapeek();
				if (lastop != 'p' && lastop != 'l' && dasize() > 0)
					printf("%.8g\n", lastvalue);
				printf("> ");
				break;
			case '=':
				(void)dapop();  // gets rid of extra push on the stack
				if (isupper(lastop))
					vars[(size_t)(lastop - 'A')] = dapop();
				else
					printf("No variable name on stack\n");
				break;
			case 'v':
				dapush(lastvalue);
				break;
			default:
				if (isupper(optype))
					// the value we push will be immediately popped if the next command is '='
					dapush(vars[(size_t)(optype - 'A')]);
				else
					printf("Error: Unknown command '%s'\n", operator);
		} // switch
		lastop = optype;
	} // while

	exit(EXIT_SUCCESS);
}