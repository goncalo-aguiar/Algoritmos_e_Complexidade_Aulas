// NMEC: 98266
// NICK: Gonçalo Aguiar

// Complete the functions (marked by ...)
// so that it passes all tests in Tests.

#include "PersonSet.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "BSTree.h"

// NOTE THAT:
// - Field capacity was eliminated.
// - Field size was eliminated, because size==BSTreeGetNumberOfNodes(...).

// Definition of the structure
struct _PersonSet_ {
  BSTree *persons;  // points to a BSTree of Person pointers
};

// Comparison function to be used in generic BSTree.
// Comparison is based on Person ID
static int cmpP(const void *a, const void *b) {
  Person *p1 = (Person *)a;
  Person *p2 = (Person *)b;
  int d = p1->id - p2->id;
  return (d > 0) - (d < 0);
}

// Print function to be used in generic BSTree.
static void printP(void *p) { PersonPrintf((Person *)p, ""); }

// Create a PersonSet.
PersonSet *PersonSetCreate() {
  // You must allocate space for the struct and create an empty persons tree!
  PersonSet* p = (PersonSet*) malloc(sizeof(*p));
  if(p == NULL){
    perror("PersonCreate");
    return NULL;
  }
  p -> persons = BSTreeCreate(cmpP,printP);
  if(p-> persons == NULL){
    free(p);
    perror("PersonCreate");
    return NULL;
  }
  return p;
  
}

// Destroy PersonSet *pps
void PersonSetDestroy(PersonSet **pps) {
  assert(*pps != NULL);
  BSTreeDestroy(&((*pps) -> persons));
  free(*pps);
  *pps = NULL;
  
}

int PersonSetSize(const PersonSet *ps) {
  return BSTreeGetNumberOfNodes(ps->persons);
}

int PersonSetIsEmpty(const PersonSet *ps) { return BSTreeIsEmpty(ps->persons); }

// Print function to use in PersonSetPrint
static void printlnP(void *p) { PersonPrintf((Person *)p, ";\n"); }

void PersonSetPrint(const PersonSet *ps) {
  printf("{\n");
  BSTreeTraverseINOrder(ps->persons, printlnP);
  printf("}(size=%d)\n", PersonSetSize(ps));
}

// Find node in BSTree ps->persons of person with given id.
// Return a pointer to the stored Person instance.
// Or NULL, if it does not belong to the BSTree.
// (INTERNAL function.)
static Person *search(const PersonSet *ps, int id) {
  Person dummyPerson;
  dummyPerson.id = id;
  return BSTreeSearch(ps->persons, &dummyPerson);
}

// Add person *p to *ps.
// Do nothing if *ps already contains a person with the same id.
void PersonSetAdd(PersonSet *ps, Person *p) {
  Person *auxiliar = search(ps,p->id);
  if(auxiliar == NULL){
    BSTreeAdd(ps->persons,p);
  } 
  
}

// Pop one person out of *ps.
Person *PersonSetPop(PersonSet *ps) {
  assert(!PersonSetIsEmpty(ps));
  // It is easiest to pop and return the first person in the set!
  Person *auxiliar = BSTreeGetMin(ps->persons);
  BSTreeRemove(ps->persons,auxiliar);
  return auxiliar;
  
  
}

// Remove the person with given id from *ps, and return it.
// If no such person is found, return NULL and leave set untouched.
Person *PersonSetRemove(PersonSet *ps, int id) {
  // You may call search here!
  Person *auxiliar = search(ps,id);
  if(auxiliar != NULL){
    BSTreeRemove(ps->persons,auxiliar);
    return auxiliar;
  } 
  return NULL;
  
}

// Get the person with given id of *ps.
// return NULL if it is not in the set.
Person *PersonSetGet(const PersonSet *ps, int id) {
  // You may call search here!
  Person *auxiliar = search(ps,id);
  if(auxiliar != NULL){
    return auxiliar;
  } 
  return NULL;
  
}

// Return true (!= 0) if set contains person with given id, false otherwise.
int PersonSetContains(const PersonSet *ps, int id) {
  return search(ps, id) != NULL;
}

// Return a NEW PersonSet with the union of *ps1 and *ps2.
// NOTE: memory is allocated.  Client must call PersonSetDestroy!
PersonSet *PersonSetUnion(const PersonSet *ps1, const PersonSet *ps2) {
  PersonSet *ps = PersonSetCreate();
  Queue *fila1 = BSTreeGetItems(ps1->persons);
  while(QueueSize(fila1)>0){
    BSTreeAdd(ps->persons,QueueDequeue(fila1));
  }
  Queue *fila2 = BSTreeGetItems(ps2->persons);
  while(QueueSize(fila2)>0){
    BSTreeAdd(ps->persons,QueueDequeue(fila2));
  }
  QueueDestroy(&fila1);
  QueueDestroy(&fila2);
  return ps;
}

// Return a NEW PersonSet with the intersection of *ps1 and *ps2.
// NOTE: memory is allocated.  Client must call PersonSetDestroy!
PersonSet *PersonSetIntersection(const PersonSet *ps1, const PersonSet *ps2) {
  PersonSet *ps = PersonSetCreate();
  Queue *fila1 = BSTreeGetItems(ps1->persons);
  while(QueueSize(fila1)>0){
    Person *aux = QueuePeek(fila1);
    int id = aux ->id;
    if(search(ps2,id)!=NULL){
       BSTreeAdd(ps->persons,QueuePeek(fila1));
    }
    QueueDequeue(fila1);
  }
  
  QueueDestroy(&fila1);
 
  return ps;
}

// Return a NEW PersonSet with the set difference of *ps1 and *ps2.
// NOTE: memory is allocated.  Client must call PersonSetDestroy!
PersonSet *PersonSetDifference(const PersonSet *ps1, const PersonSet *ps2) {
  PersonSet *ps = PersonSetCreate();
  Queue *fila1 = BSTreeGetItems(ps1->persons);
  while(QueueSize(fila1)>0){
    Person *aux = QueuePeek(fila1);
    int id = aux ->id;
    if(search(ps2,id)==NULL){
       BSTreeAdd(ps->persons,QueuePeek(fila1));
    }
    QueueDequeue(fila1);
  }
  
  QueueDestroy(&fila1);
 
  return ps;
}

// Return true iff *ps1 is a subset of *ps2.
int PersonSetIsSubset(const PersonSet *ps1, const PersonSet *ps2) {
  
  Queue *fila1 = BSTreeGetItems(ps1->persons);
  while(QueueSize(fila1)>0){
    Person *aux = QueuePeek(fila1);
    int id = aux ->id;
    if(search(ps2,id)==NULL){
       return 0;
    }
    QueueDequeue(fila1);
  }
  
  QueueDestroy(&fila1);
 
  return 1;
  
}

// Return true if the two sets contain exactly the same elements.
int PersonSetEquals(const PersonSet *ps1, const PersonSet *ps2) {
  return PersonSetSize(ps1) == PersonSetSize(ps2) &&
         PersonSetIsSubset(ps1, ps2);
}
