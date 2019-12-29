/*
 * Name: Venkat Sai Charan Bandi
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stack.h"
#include "token.h"
#include "hash.h"

/* Local Function Declarations (that you need to finish implementing) */
static int read_file(char *filename, char *line);
static int parse_token(Symtab *symtab, Stack_head *stack, Token *tok);

/* Pre-Written Local Function Declarations */
static void print_header(char *filename, int step);
static void print_step_header(int step);
static void print_step_footer(Symtab *symtab, Stack_head *stack);
static void print_step_output(int val);

/* Defines the largest line that can be read from a file */
#define MAX_LINE_LEN 255


int rpn(Stack_head *stack, Symtab *symtab, char *filename) {
  int step = 0; /* Used to track the program steps */
  int ret = 0;
  char line[MAX_LINE_LEN];
  Token *tok = NULL;

  ret = read_file(filename, line);
  if(ret != 0) {
    printf("Error: Cannot Read File %s.  Exiting\n", filename);
    exit(-1);
  }

  /* Pass the line into the tokenizer to initialize that system */
  token_read_line(line, strlen(line));

  /* Prints out the nice program output header */
  print_header(filename, step);

  /* Iterate through all tokens */
  while(token_has_next()) {
    /* Begin the next step of execution and print out the step header */
    step++; /* Begin the next step of execution */
    print_step_header(step);

    /* Get the next token */
    tok = token_get_next();
    /* Complete the implementation of this function later in this file. */
    ret = parse_token(symtab, stack, tok);
    if(ret != 0) {
      printf("Critical Error in Parsing.  Exiting Program!\n");
      exit(-1);
    }

    /* Prints out the end of step information */
    print_step_footer(symtab, stack);
  }

  return 0;
}


static int read_file(char *filename, char *line) {
  FILE *fp;//file pointer declaration
  fp = fopen(filename, "r");//opening file in read mode with specified pointer name
  if(fp == NULL){
    return(-1);// return -1 on empty file
  }
  else{
    while(feof(fp) == 0)// Running until End Of File
    {
      fgets(line, MAX_LINE_LEN, fp); // Get one line from file
    }
    fclose(fp);//closing file
    return (0);//exit on return
  }
  return(-1); // return -1 on any errors
}

static int parse_token(Symtab *symtab, Stack_head *stack, Token *tok) {

  if(tok->type == 0){//Assignment Type operator
    Token *sta1 = malloc(sizeof(Token));
    Token *sta2 = malloc(sizeof(Token));
    sta1 = stack_pop(stack);//popping one from top
    sta2 = stack_pop(stack);//popping second from top
    int check = hash_put(symtab,(sta2->variable),(sta1->value));//passing the two popped tokens into the hash put function
    if(check==0){
      free(sta1);//freeing tokens after use
      free(sta2);
      return 0;//if hash_put worked returning zero
    }
    free(sta1);//freeing tokens after use
    free(sta2);
    return -1;//if hash_put goes wrong returning -1
  }
  else if(tok->type == 1){//Operator Type
    printf("Entered the operator func\n");
    Token *val1 = malloc(sizeof(Token));
    Token *val2 = malloc(sizeof(Token));
    val1 = stack_pop(stack);//popping two tokens off stack to perform the mathematical calc
    val2 = stack_pop(stack);
    int val_oper = NULL;
    if(val1->type == 2 || val2->type == 2){//if any of the both tokens are of the type variables to get from hash table
      Symbol *s1 = malloc(sizeof(Symbol));
      Symbol *s2 = malloc(sizeof(Symbol));
      if(val1->type == 2){
        s1= hash_get(symtab,val1->variable);
        val1->value = s1->val;
      }
      if(val2->type == 2){
        s2= hash_get(symtab,val2->variable);
        val2->value = s2->val;
      }
      free(s1);//freeing symbols after use
      free(s2);
    }
    if(tok->oper == 0){//once the values are set we perform operations on the two values
      val_oper = (val2->value) + (val1->value);
    }
    else if(tok->oper == 1){
      val_oper = (val2->value) - (val1->value);
    }
    else if(tok->oper == 2){
      val_oper = (val2->value) * (val1->value);
    }
    else if(tok->oper == 3){
      val_oper = (val2->value) / (val1->value);
    }
    Token *push_val = malloc(sizeof(Token));
    push_val->type = 3;
    push_val->value = val_oper;
    stack_push(stack, push_val);//we push the resultant value into the stack after calculation is done
    free(val1);//freeing tokens after use
    free(val2);
  }
  else if(tok->type == 2){//Variable Type Operator
    stack_push(stack,tok);//pushing the variable onto the stack
  }
  else if(tok->type == 3){//Value Type Operator
    stack_push(stack, tok);//pushing the value onto the stack
  }
  else if(tok->type == 4){//Print Operation
    Token *print_tok = malloc(sizeof(Token));
    print_tok = stack->top->tok;
    stack_pop(stack);
    int xyz=NULL;
    if(print_tok->type == 2){//if the type of the value on stack is variable we ge thte value from hash table
      Symbol *print_sym = malloc(sizeof(Symbol));
      print_sym = hash_get(symtab,print_tok->variable);
      xyz = print_sym->val;
      print_step_output(xyz);
      return 0;
    }
    xyz = print_tok->value;
    print_step_output(xyz);//using step output function to parse the value
    free(print_tok);//freeing token after use
  }
  return 0;
}

static void print_header(char *filename, int step) {
  printf("######### Beginning Program (%s) ###########\n", filename);
  printf("\n.-------------------\n");
  printf("| Program Step = %2d\n", step);
  token_print_remaining();
  printf("o-------------------\n");
}


static void print_step_header(int step) {
  printf("\n.-------------------\n");
  printf("| Program Step = %2d\n", step++);
}


static void print_step_output(int val) {
  printf("|-----Program Output\n");
  printf("| %d\n", val);
}


static void print_step_footer(Symtab *symtab, Stack_head *stack) {
  hash_print_symtab(symtab);
  stack_print(stack);
  token_print_remaining();
  printf("o-------------------\n");
}
