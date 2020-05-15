#ifndef _booleanEvaluation_h
#define _booleanEvaluation_h

#include <stdio.h>
#include <string.h>
#include "stack.h"
#include "booleanWithError.h"

char *evaluatePostfix( char *str );
char *postfixToInfix( char *str );

typedef struct LLNode
{
    char data[50]; //string in the linked list node
    struct LLNode *next; //next node in linked list
} LLNode;

void r(LLNode* );

#endif
