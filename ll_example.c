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

int deletes( LLPtr *headPtr, LLPtr *tailPtr, int value );
int isEmpty( LLPtr sPtr );
void insert( LLPtr *headPtr, LLPtr *tailPtr, int value , char name[30]); // Change in ID; therefore use star pointer
void printList( LLPtr currentPtr, LLPtr tailPtr ); // No change in ID; therefore no star
void reverseList( LLPtr currentPtr, LLPtr tailPtr );
void instructions( void );

int main( void )
{ 
  LLPtr startPtr = NULL; // initially there are no nodes
  LLPtr tailPtr=NULL;
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
        insert( &startPtr,&tailPtr, item , name); // insert item in list
        printList( startPtr, tailPtr );
        reverseList(startPtr, tailPtr);
        break;
      case 2: // delete an element
        // if list is not empty
        if ( !isEmpty( startPtr ) ) { 
          printf( "%s", "Enter an ID to be deleted: " );
          scanf( "%d", &item );

          // if character is found, remove it
          if ( deletes( &startPtr,&tailPtr, item ) ) { // remove item
            printf( "%d deleted.\n", item );
            printList( startPtr , tailPtr);
            reverseList(startPtr,tailPtr);
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
  while(tempPtr!=tailPtr){
    startPtr = ( startPtr )->nextPtr; // de-thread the node
    //printf("Deleting %d %s\n", tempPtr->id, tempPtr->name);
    free(tempPtr);
    tempPtr = startPtr; // hold onto next node being removed
  } // end while
  if (tempPtr) {
    //printf("Deleting %d %s\n", tempPtr->id, tempPtr->name);
    free(tempPtr);
    startPtr = tailPtr = NULL;
    //printf("Deletion completed\n");
     }
  else {
     printf("Node is not initialized\n");
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
void insert( LLPtr *headPtr, LLPtr *tailPtr, int value , char name[30])
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
    currentPtr = *headPtr;
    if(currentPtr==NULL) { // Insert the first node
      *headPtr = newPtr;
      *tailPtr = newPtr;
      newPtr->nextPtr = newPtr;
      newPtr->pPtr = newPtr;
    }
    else if (*headPtr == *tailPtr) { //Check if only the first node is inserted (Insert the second node)
      if (newPtr->ID > currentPtr->ID){ 
        *tailPtr = newPtr;
        newPtr->pPtr = currentPtr;
        newPtr->nextPtr = *headPtr;
        currentPtr->nextPtr = newPtr;
      } //end if
      else { 
        *headPtr = newPtr;
        newPtr->pPtr = *tailPtr;
        newPtr->nextPtr = currentPtr;
        currentPtr->pPtr = newPtr;
        (*tailPtr)->nextPtr = newPtr;
      } //end else
    // loop to find the correct location in the list
    } //end if
    else {
      while ( currentPtr != NULL && value > currentPtr->ID ) {
        previousPtr = currentPtr; // walk to ...  
        currentPtr = currentPtr->nextPtr; // ... next node 
      } // end while       

      // insert new node at beginning of list
      if ( previousPtr == NULL ) { 
        *headPtr=newPtr;
        newPtr->nextPtr = currentPtr;
        if(currentPtr!=NULL) currentPtr->pPtr=newPtr;
        (*tailPtr)->nextPtr = newPtr;
        newPtr->pPtr = *tailPtr;
      } // end if
      else if (currentPtr != *tailPtr || newPtr->ID <= currentPtr->ID) { // insert new node between previousPtr and currentPtr
        *tailPtr = newPtr;
        newPtr->nextPtr = currentPtr;
        if(currentPtr!=NULL) currentPtr->pPtr=newPtr;
        newPtr->pPtr=*headPtr;
        (*headPtr)->pPtr = newPtr; 
      } // end else if
      else { //insert new node at the end
          *tailPtr = newPtr;
          if(currentPtr!=NULL) currentPtr->nextPtr = newPtr;
          newPtr-> pPtr = currentPtr;
          newPtr-> nextPtr = *headPtr;
          (*headPtr)->pPtr = newPtr;
      }
    }
    //printf("%s",newPtr->name);
  } // end if
  else {
    printf("%d not inserted. No memory available.\n", value );
  } // end else
} // end function insert

// delete a list element
int deletes( LLPtr *headPtr, LLPtr *tailPtr, int value )
{ 
  LLPtr previousPtr; // pointer to previous node in list
  LLPtr currentPtr; // pointer to current node in list
  LLPtr tempPtr; // temporary node pointer

  // delete first node
  if ( value == ( *headPtr )->ID ) { 
    tempPtr = *headPtr; // hold onto node being removed
    if(( *headPtr ) != *tailPtr) {
        *headPtr = ( *headPtr )->nextPtr; // de-thread the node
        (*headPtr)->pPtr = *tailPtr;
        (*tailPtr)->nextPtr = *headPtr;
    } //end if
    else *headPtr = *tailPtr = NULL;
    free( tempPtr ); // free the de-threaded node
    return value;
  } // end if
  else {
    previousPtr = *headPtr;
    currentPtr = ( *headPtr )->nextPtr;
    // loop to find the correct location in the list
    while (  currentPtr->ID != value && currentPtr != *tailPtr ) { 
      previousPtr = currentPtr; // walk to ...  
      currentPtr = currentPtr->nextPtr; // ... next node  
    } // end while

    // delete node at currentPtr
    if ( currentPtr != *tailPtr ) { 
      tempPtr = currentPtr;
      previousPtr->nextPtr = currentPtr->nextPtr;
      if(currentPtr->nextPtr!=NULL) currentPtr->nextPtr->pPtr=tempPtr->pPtr;
      free( tempPtr );
      return value;
    } // end if
    else if (currentPtr->ID == value ) {
      tempPtr = currentPtr;
      previousPtr->nextPtr = currentPtr->nextPtr;
      currentPtr = currentPtr->nextPtr;
      currentPtr->pPtr = tempPtr->pPtr;
      *tailPtr = (*tailPtr)->pPtr;
      free( tempPtr );
      return value;
    } // end else if
  } // end else

  return '\0';
} // end function delete

// return 1 if the list is empty, 0 otherwise
int isEmpty( LLPtr sPtr )
{ 
  return sPtr == NULL;
} // end function isEmpty

// print the list
void printList( LLPtr currentPtr , LLPtr tailPtr)
{ 
  // if list is empty
  if ( isEmpty( currentPtr ) ) {
    puts( "List is empty." );
  } // end if
  else { 
    puts( "The list is:" );
    // while not the end of the list
    while ( currentPtr != tailPtr ) {
      printf( "%d %s --> ", currentPtr->ID, currentPtr->iname );
      currentPtr = currentPtr->nextPtr;   
    } // end while

    printf( "%d %s --> NULL\n",currentPtr->ID, currentPtr->iname );
       

     
       
  } // end else
} // end function printList
void reverseList( LLPtr currentPtr , LLPtr tailPtr)
{ 
  
  LLPtr tempPtr=currentPtr;
  // if list is empty
  if ( isEmpty( currentPtr ) ) {
    puts( "List is empty." );
  } // end if
  else { 
    puts( "The reversed list is:" );

    // while not the end of the list
    while ( currentPtr != tailPtr ) {
      currentPtr = currentPtr->nextPtr;   
    } // end while
    while ( currentPtr != tempPtr ) {
      printf( "%d %s --> ", currentPtr->ID ,currentPtr->iname);
      currentPtr = currentPtr->pPtr;   
    } // end while

    printf( "%d %s --> NULL\n",currentPtr->ID , currentPtr->iname);       
  } // end else
} // end function reverseList