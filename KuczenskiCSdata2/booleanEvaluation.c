#include <stdio.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

#include "stack.h"
#include "booleanEvaluation.h"
#include "booleanWithError.h"


typedef Stack* Stk;

LLNode *tokenizeString( char *str );
typedef LLNode *Node;
/* evaluatePostfix
 * input: a postfix expression
 * output: T, F, or E
 *
 * Uses a stack to evaluates the postfix expression and returns the result as a string where "T" denotes true and "F" denotes false.
 * If the postfix expression is invalid it returns "E" to denote an error has occurred.
 */
char *evaluatePostfix( char *str )
{

    Stk Stack;
    Stack = createStack();
    Node head = tokenizeString(str); //start of linked list head.
    Node foot = head;
    
    for (; foot != NULL; foot = foot ->next)
    {
        if (strcmp(foot -> data, "T") == 0 || strcmp(foot ->data, "F") == 0) {
            char *t = "T";
            char *f = "F";
            if(strcmp(foot -> data, "T")==0)
                push(Stack, t);
            else if(strcmp(foot -> data, "F")==0)
                push(Stack, f);
        }
        else if (strcmp(foot -> data, "NOT") == 0)
        {
            if (top(Stack)==NULL) {
                char *err = booleanToString(ERROR);
                
                freeStackElements(Stack);
                freeStack(Stack);
                r(head);
                return err;
            }
            push(Stack, booleanToString(!stringToBoolean(pop(Stack))));
        }
        else if (strcmp(foot -> data, "AND")==0 || strcmp (foot -> data, "NAND")==0 || strcmp(foot -> data, "OR")==0 || strcmp(foot -> data, "NOR") == 0 || strcmp(foot -> data, "NOR")==0 || strcmp(foot -> data, "XOR")==0 || strcmp(foot -> data, "COND")==0 || strcmp(foot -> data, "BICOND")==0)
        {
            char *x = foot -> data;
            char *y;
            char *v;
            if ((y = pop(Stack)) == NULL || (v = pop(Stack)) == NULL){
                char *err = booleanToString(ERROR);
                
                free(y);
                free(v);
                freeStackElements(Stack);
                freeStack(Stack);
                r(head);
                return err;
            }
            if (strcmp(x, "AND")==0){
                boolean j,k;
                j = stringToBoolean(y);
                k = stringToBoolean(v);
                push(Stack, booleanToString((j && k)));}
            else if (strcmp(x, "NAND")==0){
                boolean j,k;
                j = stringToBoolean(y);
                k = stringToBoolean(v);
                push(Stack, booleanToString(!(j&&k)));}
            else if (strcmp(x, "OR")==0){
                boolean j,k;
                j = stringToBoolean(y);
                k = stringToBoolean(v);
                push(Stack, booleanToString((j||k)));}
            else if (strcmp(x, "NOR")==0){
                boolean j,k;
                j = stringToBoolean(y);
                k = stringToBoolean(v);
                push(Stack, booleanToString(!(j||k)));}
            else if (strcmp(x, "XOR")==0){
                boolean j,k;
                j = stringToBoolean(y);
                k = stringToBoolean(v);
                push(Stack, booleanToString((j != k)));}
            else if (strcmp(x, "COND")==0){
                boolean j,k;
                j = stringToBoolean(y);
                k = stringToBoolean(v);
                push(Stack, booleanToString((!j||k)));}
            else if (strcmp(x, "BICOND")==0){
                boolean j,k;
                j = stringToBoolean(y);
                k = stringToBoolean(v);
                push(Stack, booleanToString((j==k)));}
        }
    }
    char *pepsi = top(Stack);
    boolean cut = Stack -> top >= 1;
    if (cut)
    {
        freeStackElements(Stack);
        freeStack(Stack);
        r(head);
        return booleanToString( ERROR );
        
    }
    boolean coke = stringToBoolean(pepsi);
    
    freeStackElements(Stack);
    freeStack(Stack);
    r(head);
    return booleanToString( coke );
    
}

/* postfixToInfix
 * input: a postfix expression
 * output: the equivalent infix expression
 *
 * Uses a stack to convert str to its equivalent expression in infix.
 * You can assume that the postfix expression is valid
 */

// next function postfix to intfix

char *postfixToInfix( char *str )
{
    Stk Stack;
    Stack = createStack();
    Node head = tokenizeString(str); //start of linked list head.
    Node foot = head;
    
    
    for (; foot != NULL; foot = foot ->next)
    {
        if (strcmp(foot -> data, "T") == 0 || strcmp(foot ->data, "F") == 0) {
            char *t = "T";
            char *f = "F";
            if(strcmp(foot -> data, "T")==0)
                push(Stack, t);
            else if(strcmp(foot -> data, "F")==0)
                push(Stack, f);
        }
        else if (strcmp(foot -> data, "NOT") == 0)
        {
            char *n = malloc(100);
            char *d = pop(Stack);
            n [0] = '(';
            strcat(n, " NOT ");
            strcat(n, d);
            strcat(n, " )");
            push(Stack ,n);
            free (d);
        }
        else if (strcmp(foot -> data, "AND")==0 || strcmp (foot -> data, "NAND")==0 || strcmp(foot -> data, "OR")==0 || strcmp(foot -> data, "NOR") == 0 || strcmp(foot -> data, "NOR")==0 || strcmp(foot -> data, "XOR")==0 || strcmp(foot -> data, "COND")==0 || strcmp(foot -> data, "BICOND")==0)
        {
            char *x = foot -> data;
            char *y;
            char *v;
            
            if (strcmp(x, "AND")==0){
                char *n = malloc(100);
                v = pop(Stack);
                y = pop(Stack);
                strcat (n, "( ");
                strcat (n, y);
                strcat (n,  " " );
                strcat (n, foot -> data);
                strcat(n, " " );
                strcat (n, v);
                strcat(n, " )");
                push (Stack, n);
                free(y);
                free(v);
               }
            else if (strcmp(x, "NAND")==0){
                char *n = malloc(100);
                v = pop(Stack);
                y = pop(Stack);
                strcat (n, "( ");
                strcat (n, y);
                strcat (n,  " " );
                strcat (n, foot -> data);
                strcat(n, " " );
                strcat (n, v);
                strcat(n, " )");
                push (Stack, n);
                free(y);
                free(v);
            }
            else if (strcmp(x, "OR")==0){
                char *n = malloc(100);
                v = pop(Stack);
                y = pop(Stack);
                strcat (n, "( ");
                strcat (n, y);
                strcat (n,  " " );
                strcat (n, foot -> data);
                strcat(n, " " );
                strcat (n, v);
                strcat(n, " )");
                push (Stack, n);
                free(y);
                free(v);
            }
            else if (strcmp(x, "NOR")==0){
                char *n = malloc(100);
                v = pop(Stack);
                y = pop(Stack);
                strcat (n, "( ");
                strcat (n, y);
                strcat (n,  " " );
                strcat (n, foot -> data);
                strcat(n, " " );
                strcat (n, v);
                strcat(n, " )");
                push (Stack, n);
                free(y);
                free(v);
            }
            else if (strcmp(x, "XOR")==0){
                char *n = malloc(100);
                v = pop(Stack);
                y = pop(Stack);
                strcat (n, "( ");
                strcat (n, y);
                strcat (n,  " " );
                strcat (n, foot -> data);
                strcat(n, " " );
                strcat (n, v);
                strcat(n, " )");
                push (Stack, n);
                free(y);
                free(v);
            }
            else if (strcmp(x, "COND")==0){
                char *n = malloc(100);
                v = pop(Stack);
                y = pop(Stack);
                strcat (n, "( ");
                strcat (n, y);
                strcat (n,  " " );
                strcat (n, foot -> data);
                strcat(n, " " );
                strcat (n, v);
                strcat(n, " )");
                push (Stack, n);
                free(y);
                free(v);
            }
            else if (strcmp(x, "BICOND")==0){
                char *n = malloc(100);
                v = pop(Stack);
                y = pop(Stack);
                strcat (n, "( ");
                strcat (n, y);
                strcat (n,  " " );
                strcat (n, foot -> data);
                strcat(n, " " );
                strcat (n, v);
                strcat(n, " )");
                push (Stack, n);
                free(y);
                free(v);
            }
        }
    }
    char *pepsi = pop(Stack);
    boolean cut = Stack -> top >= 1;
    if (cut)
    {
        freeStackElements(Stack);
        freeStack(Stack);
        r(head);
        return booleanToString( ERROR );
        
    }
    freeStackElements(Stack);
    freeStack(Stack);
    r(head);
    return pepsi;
   
}
// start function definition
LLNode *tokenizeString( char *str ){
    int i = 0;
    int j;
    LLNode *head = (LLNode *) malloc( sizeof (LLNode) );
    head -> next = NULL;
    LLNode *newNode = head;
    LLNode *precedes = head;
    
    while( i < strlen (str) )
    {
        newNode = head -> next;
        newNode = (LLNode *) malloc( sizeof (LLNode) );
        newNode -> next = NULL;
        precedes -> next = newNode;
        
        for (j = 0; j < 100 && str [i] != '\0' && !isspace(str[i]); j++)
        {
            newNode -> data [j] = str [i];
            i++;
        }
        
        newNode -> data [j] = '\0';
        
        while(i < strlen(str) && isspace(str [i]))
        {
            i++;
        }
        
        precedes = newNode;
    }
    
    return  head;
    
}

// new function

void r(LLNode* fall){

    while (fall != NULL){
        LLNode *temp = fall -> next;
        free(fall);
        fall = temp;
    }
}
