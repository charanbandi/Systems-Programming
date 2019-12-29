/*
 * Name: Venkat Sai Charan Bandi
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "clock.h"
#include "structs.h"
#include "constants.h"


int schedule_count(Process *list) {
  int i=1;//initializing variable since function entered
  Process *counter = list;
  if(counter == NULL)//checkng if list is empty
    {
      return 0;
    }
  while(counter->next != NULL)//iterating over the list and incrementing each value for each occurence of node
    {
      i++;
      counter = counter->next;
    }
  return (i);
}


void schedule_insert(Process **list, Process *node) {
  if(*list == NULL)//checking if list is empty at the start of function
    {
     *list = node;//assigning head for the double pointer
     return;
    }
 Process *head = *list;//using a temp head to compare a double pointer that returns head address with a current node
  if(node->pid < head->pid)//adding new node at head
    {
      node->next = head;
      *list = node;
      return;
    }
  Process *walker = *list;
  while(walker->next != NULL)
    {
      if(walker->next->pid >= node->pid)//adding new node in the begenning just after a previous node
        {
        node->next = walker->next;
        walker->next = node;
        return;
        }
      walker = walker->next;
    }
  walker->next=node;

  if(walker->next == NULL)//adding new node at the end
    {
    node = walker->next;
  }
return;
}


void schedule_terminate(Process *node) {
  Process *reap = NULL;
  reap = node;
  free(reap);//freeing memory of node
  return;
}


Process *schedule_generate(const char *name, int pid, int time_remaining, int time_last_run) {
	Process *new = malloc(sizeof(Process));//allocation memory for the struct node
	if(new == NULL)//malloc returns NULL on memory errors
	 {
	   return NULL;
	 }
	strncpy(new->name,name,strlen("name")+1);//+1  for temination character
	new->pid = pid;
	new->time_remaining = time_remaining;
	new->time_last_run = time_last_run;
	new->next = NULL;

  return (new);//returning the generated node
}


Process *schedule_select(Process **list) {
if(*list == NULL)//returning NULL if list is empty
  {
    return NULL;
  }
  Process *walker = *list;
  Process *temp = NULL;
  for(walker = *list; walker != NULL; walker = walker->next)//loop to compare the value with lowest time time_remaining
    {
      if(temp==NULL)
      {
        temp=walker;
      }
      else
      {
        Process *select = NULL;//defining node we select at the end
        if(temp->time_remaining < walker->time_remaining)
          {
            select = temp;
          }
        else if(walker->time_remaining < temp->time_remaining)
          {
            select= walker;
          }
        else
          {
            select =( walker->pid < temp->pid)? walker: temp;
          }
      temp = select;//assigning select to a variable out of block
    }
  }

  for(walker = *list; walker != NULL; walker = walker->next)//loop to compare if the starvation applies to any node
    {
      int x = clock_get_time();//func returns count to timer
      int prevy = x - (temp->time_last_run);
      int prevz = x - (walker->time_last_run);
      Process *select = temp;
      if(( prevy >= TIME_STARVATION) && (prevz >= TIME_STARVATION))
        {
          select = (walker->pid < temp->pid) ? walker: temp;
        }
      else if(prevy >= TIME_STARVATION)
        {
          select = temp;
        }
      else if(prevz >= TIME_STARVATION)
        {
          select = walker;
        }
      temp = select;//assigning select to a variable out of block
    }

  Process *shift = NULL;
  for(walker = *list; walker != NULL; walker = walker->next)//loop to adjust the positions of nodes
    {
  	if( walker->pid == temp->pid)
      {
            if(shift == NULL)
              {
  			        *list = walker->next;//changing head node
              }
            else if(walker->next != NULL)
              {
                shift->next = walker->next;//inserting between node
              }
            else if(walker->next == NULL)//inserting at end
              {
                shift->next = NULL;
              }
            walker->next = NULL;
      }
    else
      {
        shift = walker;
      }
   }
  return temp;//finally returning any selecting node to participate in process
}
