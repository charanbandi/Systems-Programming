/*
 * Name: Venkat Sai Charan Bandi
 */
#include <stdio.h>
#include <stdlib.h>

#include "node.h"
#include "stack.h"


Stack_head *stack_initialize() {
  Stack_head *new = malloc(sizeof(Stack_head));//allocating memory for a stackhead
  if(new == NULL){
    return NULL;//returning NULL on memory allocation erros
  }
  else{
  new->count = 0;
  new->top = NULL;//assigning initial values to the stack head
  return new;
  }
}

void stack_destroy(Stack_head *head) {
//we use two node pointer variables, one to traverse and one to temporary hold the next values
  Node *nextnode = malloc(sizeof(Node));
  Node *TempNode = malloc(sizeof(Node));
  nextnode = head->top;
  while (nextnode != NULL)
   {
      TempNode = nextnode;//to hold the temporary address
      nextnode = nextnode->next;// to travers along the chain
      token_free(TempNode->tok);//both the tokens and the nodes and freed
      free(TempNode);
   }
 free(nextnode);
  return;
}

int stack_push(Stack_head *stack, Token *tok) {
  int check = stack_is_empty(stack);
  if(tok == NULL){
    return -1;//returning -1 on any tok passing erros
  }
  else if(check == 1){
    stack->top = node_create(tok);//creating and initializing a new stack head because it is empty
    (stack->count)++;//incrementing count as per the no of nodes on the stack
    return 0;
  }
  else{
    void *p = (stack->top);//this void pointer holds the address of the stack top
    stack->top = node_create(tok);//we create node using the node_create function by passing tok
    stack->top->next = p;//getting the address from the pointer variable
    (stack->count)++;//incrementing count as per the no of nodes on the stack
    return 0;
  }
}

Token *stack_pop(Stack_head *stack) {
  if(stack == NULL || stack->count == 0){
    stack_destroy(stack);//if stack is empty after the final operation we destroy the stack
    return NULL; // returning NULL if stack empty;
  }
  else{
    Token *temp = malloc(sizeof(Token));
    temp = stack->top->tok;
    void *p = stack->top->next;//assigning next node to top of stack, performing a basic pop operation
    node_free(stack->top);//freeing the nodes
  stack->top = p;//setting the new top after
  (stack->count)--;//decrementing value of stack count after pop
  return temp;//returning the popped token
  }
}

Token *stack_peek(Stack_head *stack) {
  if(stack != NULL){
    Token *peek = malloc(sizeof(Token));//memory allocation for a token
    peek = stack->top->tok;//retrieving and assigning the top o the stack to the token
    return (peek);//returning the token
  }
  return NULL;
}

int stack_is_empty(Stack_head *stack) {
  /*if(stack == NULL){
    return NULL; //Documentation says to return NULL but the return type is int, poses a warning
  }*/
  if(stack->count == 0){
    return 1;//returning 1 since stack is empty
  }
  else{
    return 0;//returning zero since stack is not empty
  }
}

static void print_node(Node *node) {
  if(node == NULL) {
    return;
  }
  token_print(node->tok);
  print_node(node->next);
  return;
}

/* This is implemented for you.
 * Setup function for the recursive calls.  Starts printing with stack->top
 */
void stack_print(Stack_head *stack) {
  if(stack == NULL) {
    return;
  }
  printf("|-----Program Stack\n");
  printf("| ");
  print_node(stack->top);
  printf("\n");
  return;
}
