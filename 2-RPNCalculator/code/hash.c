/*
 * Name: Venkat Sai Charan Bandi
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "node.h"
#include "hash.h"

Symtab *hash_initialize() {
  Symtab *tab = malloc(sizeof(Symtab));//allocation of memory for a symtab
  if(tab == NULL){
    return NULL;//returning NUll on malloc memory allocation errors
  }
  else{
    tab->size = 0;//setting value as zero since only intializing with zero values in hash
    tab->capacity = (HASH_TABLE_INITIAL);//setting the capacity as hash_initialize i.t global variable
    tab->table = malloc((HASH_TABLE_INITIAL)*(sizeof(Symbol *)));//allocating enough memomry by multiplying the total number of array indexes we plan on the table
    if(tab->table == NULL){
      return NULL;//returning NULL on any memory fails or erros
    }
    else{
      for(int i=0;i<HASH_TABLE_INITIAL;i++){
        tab->table[i] = NULL;//intializing all values to NULL to get the table ready for lookups
      }
      return tab;//returning the table
    }
  }
}

void hash_destroy(Symtab *symtab) {
  //we use two node pointer variables, one to traverse and one to temporary hold the next values
  Symbol *p = malloc(sizeof(Symbol));
  Symbol *q = malloc(sizeof(Symbol));
  for(int x=0;x<symtab->capacity;x++){
    p = symtab->table[x];
    while (p != NULL)
      {
       q = p;
       p = p->next;//traversing along all the linked lists if any
       free(q);//freeing each symbol
     }
   }
  free(p);//freeing the array index
  return;
}

int hash_get_capacity(Symtab *symtab) {
  if(symtab != NULL){
    return (symtab->capacity);//returning the containing path for capacity
  }
return -1;//returning-1 if symtab NULL
}


int hash_get_size(Symtab *symtab) {
  if(symtab != NULL){
    return (symtab->size);//returning the containing path for size
  }
return -1;return -1;//returning-1 if symtab NULL
}

int hash_put(Symtab *symtab, char *var, int val) {
  if(symtab!=NULL){
    float load = (float)(hash_get_size(symtab))/(hash_get_capacity(symtab));//load is calculated by size/capacity
    int c = (hash_code(var))%(hash_get_capacity(symtab));//this is mod func to get array index
    if(symtab->table[c] != NULL){//if the index element of the table isnt NULL
      long int temp = hash_code(var);//hash_code returns and saves the long as temp
      if((hash_code(symtab->table[c]->variable)) == temp){//if the variable name already exists in symbol tab just changing the value
        symtab->table[c]->val = val;
        return 0;
      }
      //after this we will travers the netire linked list to each array
      Symbol *walkerx = malloc(sizeof(Symbol));//allocation a walker symbol to traverse the list
      walkerx = symtab->table[c];// assigning the address of the table index
      while(walkerx->next != NULL){//traversing the whole linked list to check for any mathces in variable name
        if((hash_code(walkerx->variable)) == hash_code(var)){//checking if a variable already exists in the list
          walkerx->val = val;//changing value if the variable name matches
          free(walkerx);//freeing the memory of the walker
          return 0;
        }
        walkerx = walkerx->next;//traversing until the linked list reaches next node NULL
      }
    }

      Symbol *sym = malloc(sizeof(Symbol));//allocation a symbol to save a element on the list
      sym = symbol_create(var,val);//creating a new symbol to store in table
      if(load >= 2.0){//if the load reaches 2 or more with floating point precision we rehash
        hash_rehash(symtab,(2*hash_get_capacity(symtab)));//rehashing function with double the current capacity
      }
      c = (hash_code(var))%(hash_get_capacity(symtab));////hash index
      int size = hash_get_size(symtab);
      if(symtab->table[c] == NULL){
        sym = symbol_create(var,val);//creates a new symbol and places on the table
        symtab->table[c]=sym;
        symtab->size = ++size;//we increment the size of the table
        }
      else{//creating linked list if the index is already full
        Symbol *walker = malloc(sizeof(Symbol));//using walker symbol struct temporaryily traverse through the linked list
        walker = symtab->table[c];// assigning the address of the table index
        while(walker->next != NULL){
          walker = walker->next;//traversing until the linked list reaches next node NULL
        }
        walker->next = sym;
        symtab->size = ++size;//we increment the size of the table
      }
      return 0;
    }
  return -1;
}

Symbol *hash_get(Symtab *symtab, char *var) {

  int index_check = (hash_code(var))%(hash_get_capacity(symtab));//calculating index if the variableis present
  long int check = hash_code(var);
  long int check1 = hash_code(symtab->table[index_check]->variable);
  if(check == check1){//if the hash matches
    return (symbol_copy(symtab->table[index_check]));//we return the variable with the variable using a symbol copy function
  }
  else{
    Symbol *walkery = malloc(sizeof(Symbol));//using walker symbol struct temporarily traverse through the linked list
    walkery = symtab->table[index_check];// assigning the address of the table index
    while(walkery->next != NULL){
      if(hash_code(walkery->variable) == check){
        return(symbol_copy(walkery));
      }
      walkery = walkery->next;//traversing until the linked list reaches next node NULL
    }
  }
  return NULL;//return NULL only if not found
}

void hash_rehash(Symtab *symtab, int new_capacity) {
  Symtab *retab = malloc(sizeof(Symtab));//new table after hashing
  Symbol *resym = malloc(sizeof(Symbol));//temporary symbol storage
  Symbol *rewalker = malloc(sizeof(Symbol));//traversal of the new hash Table
  Symbol *rewalker1 = malloc(sizeof(Symbol));//traversal of the old hash Table
  retab->table = malloc((new_capacity)*(sizeof(Symbol *)));//creating the memory for the new table
  if(symtab == NULL || retab == NULL || retab->table == NULL){
        return; // returning if on any malloc or empty elements
      }
  else{
    retab->size = 0;
    retab->capacity = new_capacity;//setting new capacity
    int size = 0;//setting initial size as zero
    for(int x=0;x<new_capacity;x++){
      retab->table[x] = NULL;//initializingall elements of the new table as NULL
    }
    int reindex = NULL;
    for(int i = 0;i<(retab->capacity);i++){//table traversal of the new hash table checking for any index matching elements in the old table
      for(int j=0;j<(symtab->capacity);j++){
        rewalker = symtab->table[j];
        while(rewalker != NULL)
          {
            reindex = (hash_code(rewalker->variable))%new_capacity;
            if(i == reindex){//if index is available
              rewalker1 = retab->table[i];
            if(retab->table[i] == NULL){
              resym = symbol_create((rewalker->variable),(rewalker->val));
              retab->table[i] = resym;
              retab->size = ++size;
            }
            else if(retab->table[i] != NULL){//the memory of index is already filled
              rewalker1 = retab->table[i];
              while(rewalker1->next != NULL){
                rewalker1 = rewalker1->next;
              }
              resym = symbol_create((rewalker->variable),(rewalker->val));//create a new symbol with the respective values and store in a temporary symbol
              rewalker1->next = resym;//assigning symbol at appropriate index and place
              retab->size = ++size;//incrementing size of the new table
            }
            }
            rewalker = rewalker->next;
          }
      }
    }

    // below performs the assignment of new symtab in place of the old table
    Symtab *temp_sym = malloc(sizeof(Symtab));
    temp_sym = symtab;
    hash_destroy(temp_sym);//destroy and free the old table with the destro y function
    symtab->table = retab->table;
    symtab->capacity = retab->capacity;
    symtab->size = retab->size;

    //freeing memory and returning
    free(retab);
    resym = NULL;
    free(resym);
    free(rewalker);
    free(rewalker1);
    return;
  }
}

void hash_print_symtab(Symtab *symtab) {
  if(symtab == NULL) {
    return;
  }
  printf("|-----Symbol Table [%d size/%d cap]\n", symtab->size, symtab->capacity);

  int i = 0;
  Symbol *walker = NULL;

  /* Iterate every index, looking for symbols to print */
  for(i = 0; i < symtab->capacity; i++) {
    walker = symtab->table[i];
    /* For each found linked list, print every symbol therein */
    while(walker != NULL) {
      printf("| %10s: %d \n", walker->variable, walker->val);
      walker = walker->next;
    }
  }
  //free (walker);
  return;
}

long hash_code(char *var) {
  long code = 0;
  int i;
  int size = strlen(var);

  for(i = 0; i < size; i++) {
    code = (code + var[i]);
    if(size == 1 || i < (size - 1)) {
      code *= 128;
    }
  }

  return code;
}
