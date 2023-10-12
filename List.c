
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<assert.h>
#include<stdbool.h>
#include "List.h"


// structs --------------------------------------------------------------------

// private Node type


typedef struct NodeObj* Node;

// private NodeObj type
typedef struct NodeObj{
   ListElement data;
   Node next;
   Node prev;
} NodeObj;

void printNode(Node n){

  if (n!= NULL){
    printf("Data:(c:%d,v:%f)   ", n->data->col,n->data->val);

    if (n->prev != NULL){
      printf("Prev:(c:%d,v:%f)", n->data->col,n->data->val);
    }

    if (n->next != NULL){
      printf("Next:(c:%d,v:%f)", n->data->col,n->data->val);
    }
    printf("\n");
  }
}


// private ListObj type
typedef struct ListObj{
   Node front;
   Node back;

   Node sent_front;
   Node sent_back;

   int length;
   int cursor;
   Node cursNode;
} ListObj;
/*
void printFULL(List L){

  Node current = L->sent_front;
  printf("f L:%d C:%d :", L->length, L->cursor);
  while(current != NULL){
    printf("%d ", current->data);
    current = current->next;
  }
  printf("\n");

}
*/
// Constructors-Destructors ---------------------------------------------------

// newNode()
// Returns reference to new Node object. Initializes next and data fields.
Node newNode(ListElement data){
   Node N = malloc(sizeof(NodeObj));
   assert( N!=NULL );
   N->data = data;
   N->next = NULL;
   N->prev = NULL;
   return(N);
}

// freeNode()
// Frees heap memory pointed to by *pN, sets *pN to NULL.
void freeNode(Node* pN){
   if( pN!=NULL && *pN!=NULL ){
      
      //printf("freeing data\n");
      free((*pN)->data);
      free(*pN);
      *pN = NULL;
   }
}

// newList()
// Returns reference to new empty List object.
List newList(){
   List Q;
   Q = malloc(sizeof(ListObj));
   assert( Q!=NULL );
  
   Q->length = 0;
   Q->cursor = -1;

   Node SentinelFront = newNode(NULL);
   Node SentinelBack = newNode(NULL);

   SentinelFront->next = SentinelBack;
   SentinelFront->prev = NULL;

   SentinelBack->prev = SentinelFront;
   SentinelBack->next = NULL;

   Q->front = SentinelFront;
   Q->back = SentinelBack;

   Q->sent_back = SentinelBack;
   Q->sent_front = SentinelFront;

   Q->cursNode=NULL;

   return(Q);
}

// freeList()
// Frees all heap memory associated with List *pQ, and sets *pQ to NULL.
void freeList(List* pL){
    //printFULL(*pL);
    Node start = (*pL)->sent_front;
    Node next = start->next;
    while(start != NULL){
      
      if(start->data != NULL){
      //printf("Freeing Node :%f\n", start->data->val);
      }else{
      //printf("deletingNode\n");
      }
      next = start->next;
      freeNode(&start);
      start = next;
    }
  free(*pL);
  *pL = NULL;
}

// Access functions -----------------------------------------------------------

// getLength()
// Returns the length of Q.
int length(List Q){
   if( Q==NULL ){
      printf("List Error: calling length() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   return(Q->length);
}


// Returns index of cursor element if defined, -1 otherwise.
int index(List Q){
   if( Q==NULL ){
      printf("List Error: calling index() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   return(Q->cursor);
}


// Returns front element of L. Pre: length()>0
void* front(List L){
  if( L==NULL ){
      printf("List Error: calling front() on NULL List reference\n");
      exit(EXIT_FAILURE);
  }

  if(L->length == 0){
    printf("List Error: calling front() on List with length 0\n");
    exit(EXIT_FAILURE);
  } 
  
  return L->front->data;
}

// Returns back element of L. Pre: length()>0
void* back(List L){
  if( L==NULL ){
      printf("List Error: calling back() on NULL List reference\n");
      exit(EXIT_FAILURE);
  }
  
  if(L->length == 0){
    printf("List Error: calling back() on List with length 0\n");
    exit(EXIT_FAILURE);
  } 


  return L->back->data;
}


// Returns cursor element of L. Pre: length()>0, index()>=0
void* get(List L){
  
  if(L==NULL){
    printf("List Error: calling get() on NULL List reference\n");
      exit(EXIT_FAILURE);
  }
  if(L->length == 0){
    printf("List Error: calling get() on List with length 0\n");
    exit(EXIT_FAILURE);
  }
  if(L->cursor < 0){
    printf("List Error: calling get() on List with undefined cursor (cursor == -1)\n");
    exit(EXIT_FAILURE);
  } 
  
  //printf("c:%d\n",L->cursor);

  if(L->cursor == -1){
    printf("List Error: calling get() on cursor of -1\n");
    exit(EXIT_FAILURE);
  }

  //int c = 0;
  /*
  Node curr = L->front;
  while (c != L->cursor){
    c++;
    curr = curr->next;

  }
  */
 return L->cursNode->data;
}

// Manipulation procedures -------------------------
//Personal function, returns the node at the current cursors position PRE: List exists
static Node getCursorNode(List L){
  if (L->cursor == -1){
    return NULL;

  }
  //int c = 0;
  //Node currNode = L->front;
  //Finding cursor node
  //printFULL(L);
  //printf("c:%d\n",L->cursor);
  /*
  while ((c != L->cursor)){

    currNode = currNode->next;
    c++;
    if (currNode == NULL){
      printf("List Error: getCursorNode() next node is NULL\n");
      exit(EXIT_FAILURE);

    }
  }
  */
  return L->cursNode;

}

// Returns true iff Lists A and B are in same
 // state, and returns false otherwise.
 /*
bool equals(List A, List B){
  //printFULL(A);
  //printFULL(B);
   if( A==NULL || B==NULL ){
      printf("List Error: calling equals() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }

   bool eq;
   Node N, M;

   eq = ( A->length == B->length );
   N = A->front;
   M = B->front;
   while( eq && N!=NULL){
      eq = ( N->data==M->data );
      N = N->next;
      M = M->next;
   }
   return eq;
}
*/
// Resets L to its original empty state.
void clear(List L){
  if(L==NULL){
    printf("List Error: calling clear() on NULL List reference\n");
    exit(EXIT_FAILURE);
  }

    int c = 0;
    Node curr = L->front;
    //printf("length:%d\n", L->length);
    Node next;
    //printf("2\n");
    while(c < (L->length)){
      //printf(".\n");
      next = curr->next;
      //printf("..\n");
      //printf("freeing:%d\n", curr->data);
     
      freeNode(&curr);
      curr = next;
      c++;
    }
    
    //printf("3\n");
    L->front = L->sent_front;
    L->sent_front->next = L->sent_back;
    L->sent_back->prev = L->sent_front;
    L->back = L->sent_back;
    L->cursor = -1;
    L->cursNode = NULL;
    L->length = 0;

    
  return;
}

// Overwrites the cursor element’s data with x.
// Pre: length()>0, index()>=0
void set(List L, void* x){
  if(L==NULL){
    printf("List Error: calling set() on NULL List reference\n");
      exit(EXIT_FAILURE);
  }

  if(L->length == 0){
    printf("List Error: calling set() on List of size 0.\n");
      exit(EXIT_FAILURE);
  }
  if(L->cursor < 0){
    printf("List Error: calling set() on List with undefined cursor\n");
      exit(EXIT_FAILURE);
  }

  Node cursNode = getCursorNode(L);
  cursNode->data = x;
  return;
}

 // If L is non-empty, sets cursor under the front element,
 // otherwise does nothing.
void moveFront(List L){
   if(L==NULL){
    printf("List Error: calling moveFront() on NULL List reference\n");
      exit(EXIT_FAILURE);
  }

  if(L->length > 0){
    L->cursor = 0;
    L->cursNode = L->front;
  }
  return;
}

// If L is non-empty, sets cursor under the back element,
 // otherwise does nothing.
void moveBack(List L){
   if(L==NULL){
    printf("List Error: calling moveBack() on NULL List reference\n");
      exit(EXIT_FAILURE);
  }

  if(L->length > 0){
    L->cursor = L->length - 1;
    L->cursNode = L->back;
  }
  return;
}



// If cursor is defined and not at back, move cursor one
// step toward the back of L; if cursor is defined and at
// back, cursor becomes undefined; if cursor is undefined
// do nothing
void moveNext(List L){
   if(L==NULL){
    printf("List Error: calling moveFront() on NULL List reference\n");
      exit(EXIT_FAILURE);
  }
  if (L->cursor == -1){
    return;
  }
  L->cursor = L->cursor +1; 
  //printf("c:%d L:%d\n", L->cursor, L->length);
  if (L->cursor >= L->length){
    L->cursor = -1;
    L->cursNode = NULL;
  }else{
    L->cursNode = L->cursNode->next;
  }
  
  return;
}

// If cursor is defined and not at front, move cursor one
// step toward the front of L; if cursor is defined and at
// front, cursor becomes undefined; if cursor is undefined
// do nothing
void movePrev(List L){
  if(L==NULL){
    printf("List Error: calling movePrev() on NULL List reference\n");
    exit(EXIT_FAILURE);
  }
  if (L->cursor == -1){
    return;
  }
  L->cursor = L->cursor -1; 
  if (L->cursor < 0){
    L->cursor = -1;
    L->cursNode = NULL;
  }else{
    L->cursNode = L->cursNode->prev;
  }

  return;

}
// Insert new element into L. If L is non-empty,
 // insertion takes place before front element.
void prepend(List L, void* x){

  if(L == NULL){
    printf("List Error: calling apend() on NULL List reference\n");
      exit(EXIT_FAILURE);
  }
 


  Node new1 = newNode(x);

  Node sent_front=L->sent_front;
  Node next = sent_front->next;

  next->prev = new1;
  new1->next = next;
  new1->prev = sent_front;
  sent_front->next = new1;

  L->length++;
  L->front = new1;
  moveNext(L);
  if(L->cursor >= 0){
  L->cursNode = L->cursNode->prev;
  }
  if (L->length == 1){
    L->back = new1;
  }
}

// Insert new element into L. If L is non-empty,
// insertion takes place after back element.
void append(List L, void* x){
  if(L == NULL){
    printf("List Error: calling apend() on NULL List reference\n");
      exit(EXIT_FAILURE);
  }
 

   //printFULL(L);

  Node currNode = L->sent_back;
  Node prevNode = currNode->prev;
  Node newN = newNode(x);

  prevNode->next = newN;
  newN->prev = prevNode;

  currNode->prev = newN;
  newN->next = currNode;


  L->length++;
  L->back = newN;

  if (L->length == 1){
    L->front = newN;
  }
}

// Insert new element before cursor.
 // Pre: length()>0, index()>=0
void insertBefore(List L, void* x){

  if(L == NULL){
    printf("List Error: calling insertBefore() on NULL List reference\n");
      exit(EXIT_FAILURE);
  }
  
  if(L->length == 0){
    printf("List Error: calling insertBefore() on List of length 0\n");
      exit(EXIT_FAILURE);
  }
  if(L->cursor < 0){
    printf("List Error: calling insertBefore() on List with undefined cursor\n");
      exit(EXIT_FAILURE);
  }
  
  if (L->cursor == 0){
    prepend(L, x);
    return;
  }
  if(index(L) == length(L)){
    
    append(L,x);
    return;
  }
  
  Node currNode = getCursorNode(L);
  
  //printf("cursor: %d  data:%d\n", get(L),currNode->data);
  

  Node prevNode = currNode->prev;

  Node newN = newNode(x);

  prevNode->next = newN;
  newN->prev = prevNode;

  currNode->prev = newN;
  newN->next = currNode;

  L->length++;
  if(L->length == 1){

    L->front = newN;
    L->back = newN;
  }
  moveNext(L);
  if(L->cursor >= 0){
    L->cursNode = L->cursNode->prev;
  }
}

// Insert new element after cursor.
 // Pre: length()>0, index()>=0
void insertAfter(List L, void* x){

  if(L == NULL){
    printf("List Error: calling insertAfter() on NULL List reference\n");
      exit(EXIT_FAILURE);
  }
  if(L->length == 0){
    printf("List Error: calling insertAfter() on List of length 0\n");
      exit(EXIT_FAILURE);
  }
  if(L->cursor < 0){
    printf("List Error: calling insertAfter() on List with undefined cursor\n");
      exit(EXIT_FAILURE);
  }

  //printf("I:%d L:%d\n", index(L), length(L));
  if(index(L) + 1 == length(L)){
    //printf("appending\n\n");
    append(L,x);
    return;
  }

  Node currNode = getCursorNode(L);
  
  //printf("cursor: %d  data:%d\n", get(L),currNode->data);
  

  Node nextNode = currNode->next;

  Node newN = newNode(x);

  nextNode->prev = newN;
  newN->next = nextNode;

  currNode->next = newN;
  newN->prev = currNode;

  L->length++;
  if(L->length == 1){

    L->front = newN;
    L->back = newN;
  }
}
// Delete the front element. Pre: length()>0
void deleteFront(List L){

  if(L->length == 0){
    printf("List Error: calling deleteFront() on empty List\n");
      exit(EXIT_FAILURE);
  }

  if(L == NULL){
    printf("List Error: calling deleteFront() on NULL List reference\n");
      exit(EXIT_FAILURE);
  }

  Node front = L->front;
  Node next = front->next;
  freeNode(&front);

  if (next!= NULL){
    next->prev = L->sent_front;
    L->front = next;
    L->sent_front->next=next;
  }

  movePrev(L);
  if(L->cursor >= 0){
    L->cursNode = L->cursNode->next;
  }
  L->length--;
  if(L->length == 1){
    L->front = L->back;
  }
}

// Delete the back element. Pre: length()>0
void deleteBack(List L){
  //printf("Before\n");
  //printFULL(L);
  if(L->length == 0){
    printf("List Error: calling deleteBack() on empty List\n");
      exit(EXIT_FAILURE);
  }

  if(L == NULL){
    printf("List Error: calling deleteBack() on NULL List reference\n");
      exit(EXIT_FAILURE);
  }
  
  //printf("in delete back\n");
  //printList(stdout,L);

  Node current = L->back;
  //printf("BD:%d\n", current->data);
  Node prev = current->prev;
  Node next = current->next;
  freeNode(&current);

  if (prev != NULL){
    prev->next = next;
    next->prev = prev;
    L->back = prev;
    
  }
  //printFULL(L);
  //printf("---------\n");
  L->length--;
  if(L->length == 0){
      L->back = L->sent_back;
  }

  //printFULL(L);
  //printf("\nL:%d C:%d\n", L->length, L->cursor);
  if(L->length == L->cursor){
    L->cursor = -1;
  }
  //printFULL(L);
}

// Delete cursor element, making cursor undefined.
 // Pre: length()>0, index()>=0
void delete(List L){
  if(L == NULL){
    printf("List Error: calling delete() on NULL List reference\n");
      exit(EXIT_FAILURE);
  }

  if (L->length == 0){
    printf("List Error: calling delete() on empty List\n");
      exit(EXIT_FAILURE);
  }
  if (L->cursor < 0){
    printf("List Error: calling delete() on undefined cursor\n");
      exit(EXIT_FAILURE);
  }


  Node cursor = getCursorNode(L);
  //printList(stdout, L);
  //printf("Curs:%d data:%d\n",L->cursor, cursor->data);
  
  Node prev = cursor->prev;
  Node next = cursor->next;
  //printFULL(L);
  if(L->cursor == 0){
   // printf("front\n");
    deleteFront(L);
    //printFULL(L);
    L->cursNode = NULL;
    return;
  }
  if(L->cursor + 1 == (L->length)){
    //printf("back\n");
    deleteBack(L);
    //printFULL(L);
    L->cursNode = NULL;
    return;
  }
  //printf("through\n");
  if(prev !=NULL){

    prev->next = next;
  }
  if(next != NULL){
    next->prev = prev;
  }
  freeNode(&cursor);
  L->cursor = -1;
  L->length--;
  L->cursNode = NULL;
  //printFULL(L);
}




// Other Functions ------------------------------------------------------------

// Prints to the file pointed to by out, a
 // string representation of L consisting
 // of a space separated sequence of integers,
// with front on left.
void printList(FILE *out, List L){
  
  //printf("\n\n1\n");
  Node curr = L->front;

  int length = 0;
  //printf("2\n");
  while(length < L->length){
    fprintf(out, " (c:%d,v:%f)", curr->data->col,curr->data->val);
    curr = curr->next;
    length++;
  }
  
  //printing out single space if list is empty
  if(L->length == 0){
    fprintf(out, " ");
  }
    fprintf(out, "\n");
}

// Returns a new List representing the same integer
// sequence as L. The cursor in the new list is undefined,
// regardless of the state of the cursor in L. The state
// of L is unchanged.
List copyList(List L){
  List ret = newList();

  if(L->length == 0){
    return ret;
  }

  Node current = L->front;
  while(current->next != NULL){
    append(ret, current->data);
    current = current->next;
  }
  ret->cursor = -1;
  return ret;
}



