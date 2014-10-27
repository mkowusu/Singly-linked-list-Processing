/*****************************************************************
 * Michael Owusu                                                 *
 * Box:  4271                                                    *
 * Supplemental Problem 5 for CSC 161                            *
 * Assignment for Tuesday, May 6                                 *
 *****************************************************************/

/* ***************************************************************
 * Academic honesty certification:                               *
 *   Written/online sources used:                                *
 *  http://www.codingunit.com/c-tutorial-file-io-using-text-files*
 *  for help with file input and output                          *
 *                                                               *
 *  http://www.cs.bu.edu/teaching/c/file-io/intro/ for help with *
 *  file input and output                                        *
 *                                                               *
 *  http://stackoverflow.com/questions/1292586/char-array-in-a-  *
 *  struct-incompatible-assignment for help with troubleshooting *
 *  unassignable arrays                                          *
 *                                                               *
 *  http://www.geeksforgeeks.org/remove-duplicates-from-an-      *
 *  unsorted-linked-list/ for help removing duplications         *
 *                                                               *
 * for help duplicating nodes http://stackoverflow.com/questions *
 *  /13633182/c-program-to-make-a-second-copy-of-a-linked-list    *
 *                                                               *
 *   Help obtained                                               *
 *  Professor Walker for help removing newline at the end of     *
 *   each name read from a file                                  *
 *   My signature below confirms that the above list of sources  *
 *   is complete AND that I have not talked to anyone else       *
 *   [e.g., CSC 161 students] about the solution to this problem *
 *                                                               *
 *   Signature:                                                  *
 *****************************************************************/


/*
  Begin Singly-linked-list Processing
*/


/* A program shell  to maintain a linked list of names */

/* library for standard I/O */
#include <stdio.h>

/* library for memory allocation */
#include <stdlib.h>

#include "string.h"

/* Maximum length of names */
#define strMax 20

struct node
{
  char data [strMax];
  struct node * next;
};

/* function prototypes, listed in alphabetical order */

void addName(struct node ** firstPtr);
/* pre-condition:  firstPtr points to the pointer
   designating the head of a list
   post-condition:  a name is read and
   inserted into the list at a designated place
*/

void print(struct node * first);
/* pre-condition:  first designates the first node of a list
   post-condition:  The items on the list are printed from first to last
   the list itself is unchanged
*/

void addNamesFromFile (struct node ** first);
/* pre-condition:  first designates the first node of a list
   post-condition:  the program asks the user for a file name
   names from individual lines of the file are inserted
   at the beginning of the original list
*/

void removeDuplicates (struct node * first);
/* pre-condition:  first designates the first node of a list
   post-condition:  each name on the list appears only once (no duplicate names)
   when duplicates occur on the original list,
   only the first occurence remains after processing
*/

void duplicate (struct node * firstPtr);
/* pre-condition:  first designates the first node of a list
   post-condition:  each node is duplicated, with the new node inserted
   after the original node
*/

int main (void) {
  /* program to coordinate the menu options and calls the requested function */
    
  struct node * first = NULL;   /* pointer to the first list item */
  char option[strMax];          /* user response to menu selection */
    
  printf ("Program to Maintain a List of Names\n");
    
  while (1) {
    /* print menu options */
    printf ("Options available\n");
    printf ("I - Insert a name (from the keyboard) into the list\n");
    printf ("P - Print the names on the list\n");
    printf ("F - Read a sequence of names from a file onto the list\n");
    printf ("R - Remove duplicate names (leaving only the first occurence)\n");
    printf ("D - Duplicate each node\n");
    printf ("Q - Quit\n");
        
    /* determine user selection */
    printf ("Enter desired option: ");
    scanf ("%s", option);
        
    switch (option[0])
      { case 'I':
      case 'i':
        addName(&first);
        break;
      case 'P':
      case 'p':
        print(first);
        break;
      case 'F':
      case 'f':
        addNamesFromFile(&first);
        break;
      case 'R':
      case 'r':
        removeDuplicates(first);
        break;
      case 'D':
      case 'd':
        duplicate(first);
        break;
      case 'Q':
      case 'q':
        printf ("Program terminated\n");
        return 0;
        break;
      default: printf ("Invalid Option - Try Again!\n");
        continue;
      }
  }
}

void addName(struct node ** firstPtr) {
  /* pre-condition:  firstPtr points to the pointer designating the head of a list
     post-condition:  a name is read and
     inserted into the list at a designated place
  */
    
  char oldName [strMax];
  struct node * newNode = (struct node *)malloc(sizeof(struct node));
  struct node * listPtr;
  struct node * prevPtr;
    
  printf ("Enter name to be inserted into list: ");
  scanf ("%s", newNode->data);
  if (*firstPtr == NULL) {
    /* insert name's node at start of list */
    newNode->next = *firstPtr;
    *firstPtr = newNode;
  }
  else {
    printf ("Enter old name which new name should preceed, \n");
    printf ("or enter ? if new name should be placed last\n");
    scanf ("%s", oldName);
        
    if (strcmp (oldName, (*firstPtr)->data) == 0) {
      /* insert name's node at start of list */
      newNode->next = *firstPtr;
      *firstPtr = newNode;
    }
    else {
      /* insert name's node after start of the list */
      /* start at beginning of list */
      listPtr = (*firstPtr)->next;  /* the current node to search */
      prevPtr = *firstPtr;          /* the node behind listPtr */
            
      while (listPtr && (strcmp (oldName, listPtr->data) != 0)) {
        prevPtr = listPtr;
        listPtr = prevPtr->next;
      }
      newNode->next = prevPtr->next;
      prevPtr->next = newNode;
    }
  }
  printf ("%s inserted into the list\n\n", newNode->data);
}

void print(struct node * first){
  /* pre-condition:  first designates the first node of a list
     post-condition:  The items on the list are printed from first to last
     the list itself is unchanged
  */
  struct node * listElt = first;
  printf ("The names on the list are:\n\n");
    
  while (listElt) {
    printf ("%s\n", listElt->data);
    listElt = listElt->next;
  }
  printf ("\nEnd of List\n\n");
}

void addNamesFromFileHelper (char * name, struct node ** firstPtr){
  /* Helper to create new name nodes from loaded file */
  struct node * newNode = (struct node *)malloc(sizeof(struct node));
    
  strcpy(newNode->data, name);
    
  /* insert name's node at start of list */
  newNode->next = *firstPtr;
  *firstPtr = newNode;
  return;
}

void addNamesFromFile (struct node ** first){
  /* pre-condition:  first designates the first node of a list
     post-condition:  the program asks the user for a file name
     names from individual lines of the file are inserted
     at the beginning of the original list
  */
  FILE *ptr_file;
  char fileName [50];
  char name[strMax];
    
  printf ("Function to insert names from a file to the end of the list\n");
  printf ("  Enter file name:  ");
  scanf ("%s",fileName);
    
  /* Open file with names to be added to list */
  ptr_file = fopen(fileName, "r");
    
  if (!ptr_file){ /* Error if file is empty */
    printf("File contains no names to be added to the list\n");
  }
    
    
  else{ /* Print each line in file */
    while (fgets(name,strMax,ptr_file) != NULL) {
        
      /* Remove newline statement at the end of each entered name */
      if(name[strlen(name) -1] == '\n')
        name[strlen(name)-1] = '\0';
        
      addNamesFromFileHelper(name, first);
      printf("%s was added to the list\n",name);
    }
  }
    
  fclose(ptr_file);
  printf("The names from file have successfully been added to list\n");
  return;
}


void removeDuplicates (struct node * first) {
  /* pre-condition:  first designates the first node of a list
     post-condition:  each name on the list appears only once (no duplicate names)
     when duplicates occur on the original list,
     only the first occurence remains after processing
  */
    
  struct node *findPtr;
  struct node *comparePtr;
  struct node *temp;
    
  comparePtr = first;
    
  /* Pick elements one by one */
  while (comparePtr != NULL && comparePtr->next !=NULL){
    findPtr = comparePtr;
        
    /* Compare the picked element with rest of the elements */
    while(findPtr->next != NULL){
            
      /* If duplicate then delete it */
      if(strcmp(comparePtr->data, findPtr->next->data) == 0)
        {
          temp = findPtr->next;
          findPtr->next = findPtr->next->next;
          free(temp);
        }
      else
        {
          findPtr = findPtr->next;
        }
    }
    comparePtr = comparePtr->next;
  }
}

void duplicateHelper(struct node * listElt){
  /* Helper to create new node for duplicate functions */
  struct node * newNode=(struct node *) malloc(sizeof(struct node));
  strcpy(newNode->data,listElt->data);
  newNode->next =listElt->next;
  listElt->next = newNode;
}

void duplicate (struct node * first){
  /* pre-condition:  first designates the first node of a list
     post-condition:  each node is duplicated, with the new node inserted
     after the original node
  */
  struct node * listElt = first;
    
  while (listElt){
    duplicateHelper(listElt);
    listElt = listElt->next->next;
  }
}
