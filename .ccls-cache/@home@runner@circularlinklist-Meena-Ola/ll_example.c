// Fig. 12.3: fig12_03.c
// Inserting and deleting nodes in a list
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// self-referential structure                       
struct Node {                                      
  int ID; // each listNode contains a character
  char iname[30];
  struct Node *nextPtr; // pointer to next node
  struct Node *pPtr; // pointer to next node
}; // end structure listNode                        

typedef struct Node LLnode; // synonym for struct listNode
typedef LLnode *LLPtr; // synonym for ListNode*

// prototypes

int deletes( LLPtr *sPtr, int value );
int isEmpty( LLPtr sPtr );
void insert( LLPtr *sPtr, int value , char name[20]); // Change in ID; therefore use star pointer
void printList( LLPtr currentPtr ); // No change in ID; therefore no star
void reverseList( LLPtr currentPtr );
void instructions( void );

int main( void )
{ 
  LLPtr startPtr = NULL; // initially there are no nodes
  unsigned int choice; // user's choice
  int item; // char entered by user
  
  instructions(); // display the menu
  printf( "%s", "? " );
  scanf( "%u", &choice );

  // loop while user does not choose 3
  while ( choice != 3 ) { 

    switch ( choice ) { 
      case 1:
        printf( "%s", "Enter your ID: " );
        scanf( "%d", &item );
        printf("%s","Enter your name: ");
        char name[30];
        fflush(stdin);
        scanf("%s", name);
        // printf("%d %s",item,name);
        insert( &startPtr, item , name); // insert item in list
        printList( startPtr );
        reverseList(startPtr);
        break;
      case 2: // delete an element
        // if list is not empty
        if ( !isEmpty( startPtr ) ) { 
          printf( "%s", "Enter an ID to be deleted: " );
          scanf( "%d", &item );

          // if character is found, remove it
          if ( deletes( &startPtr, item ) ) { // remove item
            printf( "%d deleted.\n", item );
            printList( startPtr );
            reverseList(startPtr);
          } // end if
          else {
            printf( "%d not found.\n\n", item );
          } // end else
        } // end if
        else {
          puts( "List is empty.\n" );
        } // end else

        break;
      default:
        puts( "Invalid choice.\n" );
        instructions();
        break;
    } // end switch

    printf( "%s", "? " );
    scanf( "%u", &choice );
  } // end while
  /* Clear all nodes at the end of nodes*/
  LLPtr tempPtr;
  tempPtr=startPtr;
  while(tempPtr!=NULL){
    startPtr=tempPtr->nextPtr;
    printf("Deleting %d %s...\n",tempPtr->ID,tempPtr->iname);
    free(tempPtr);
    tempPtr=startPtr;
  }
  puts( "End of run." );
} // end main

// display program instructions to user
void instructions( void )
{ 
  puts( "Enter your choice:\n"
      "   1 to insert an element into the list.\n"
      "   2 to delete an element from the list.\n"
      "   3 to end." );
} // end function instructions

// insert a new value into the list in sorted order
void insert( LLPtr *sPtr, int value , char name[20])
{ 
  LLPtr newPtr; // pointer to new node
  LLPtr previousPtr; // pointer to previous node in list
  LLPtr currentPtr; // pointer to current node in list

  newPtr =(LLPtr) malloc( sizeof( LLnode ) ); // create node

  if ( newPtr != NULL ) { // is space available
    newPtr->ID = value; // place value in node
    newPtr->nextPtr = NULL; // node does not link to another node
    newPtr->pPtr=NULL;
    strcpy(newPtr->iname,name);
    previousPtr = NULL;
    currentPtr = *sPtr;

    // loop to find the correct location in the list       
    while ( currentPtr != NULL && value > currentPtr->ID ) {
      previousPtr = currentPtr; // walk to ...               
      currentPtr = currentPtr->nextPtr; // ... next node 
    } // end while                                         

    // insert new node at beginning of list
    if ( previousPtr == NULL ) { 
      newPtr->nextPtr = *sPtr;
      if(currentPtr!=NULL) currentPtr->pPtr=newPtr;
      *sPtr = newPtr;
        
    } // end if
    else { // insert new node between previousPtr and currentPtr
      previousPtr->nextPtr = newPtr;
   
          
      newPtr->nextPtr = currentPtr;
      if(currentPtr!=NULL) currentPtr->pPtr=newPtr;
      newPtr->pPtr=previousPtr;
         
    } // end else
    //printf("%s",newPtr->name);
  } // end if
  else {
    printf( "%d not inserted. No memory available.\n", value );
  } // end else
} // end function insert

// delete a list element
int deletes( LLPtr *sPtr, int value )
{ 
  LLPtr previousPtr; // pointer to previous node in list
  LLPtr currentPtr; // pointer to current node in list
  LLPtr tempPtr; // temporary node pointer

  // delete first node
  if ( value == ( *sPtr )->ID ) { 
    tempPtr = *sPtr; // hold onto node being removed
    *sPtr = ( *sPtr )->nextPtr; // de-thread the node
    if((*sPtr)!=NULL)(*sPtr)->pPtr=NULL;
    free( tempPtr ); // free the de-threaded node
    return value;
  } // end if
  else { 
    previousPtr = *sPtr;
    currentPtr = ( *sPtr )->nextPtr;

    // loop to find the correct location in the list
    while ( currentPtr != NULL && currentPtr->ID != value ) { 
      previousPtr = currentPtr; // walk to ...  
      currentPtr = currentPtr->nextPtr; // ... next node  
    } // end while

    // delete node at currentPtr
    if ( currentPtr != NULL ) { 
      tempPtr = currentPtr;
      previousPtr->nextPtr = currentPtr->nextPtr;
      if(currentPtr->nextPtr!=NULL) currentPtr->nextPtr->pPtr=previousPtr;
      free( tempPtr );
      return value;
    } // end if
  } // end else

  return '\0';
} // end function delete

// return 1 if the list is empty, 0 otherwise
int isEmpty( LLPtr sPtr )
{ 
  return sPtr == NULL;
} // end function isEmpty

// print the list
void printList( LLPtr currentPtr )
{ 
  // if list is empty
  if ( isEmpty( currentPtr ) ) {
    puts( "List is empty." );
  } // end if
  else { 
    puts( "The list is:" );
    // while not the end of the list
    while ( currentPtr->nextPtr!= NULL ) {
      printf( "%d %s --> ", currentPtr->ID, currentPtr->iname );
      currentPtr = currentPtr->nextPtr;   
    } // end while

    printf( "%d %s --> NULL\n",currentPtr->ID, currentPtr->iname );
       

     
       
  } // end else
} // end function printList
void reverseList( LLPtr currentPtr )
{ 
  // if list is empty
  if ( isEmpty( currentPtr ) ) {
    puts( "List is empty." );
  } // end if
  else { 
    puts( "The reversed list is:" );

    // while not the end of the list
    while ( currentPtr->nextPtr!= NULL ) {
      currentPtr = currentPtr->nextPtr;   
    } // end while
    while ( currentPtr->pPtr!= NULL ) {
      printf( "%d %s --> ", currentPtr->ID ,currentPtr->iname);
      currentPtr = currentPtr->pPtr;   
    } // end while

    printf( "%d %s --> NULL\n",currentPtr->ID , currentPtr->iname);
       

     
       
  } // end else
} // end function reverseList