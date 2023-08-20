// NMEC: 98266
// NICK: Gonçalo Aguiar

// Complete the functions (marked by ...)
// so that it passes all tests in Tests.

#include "PersonSet.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "SortedList.h"

// NOTE THAT:
// - Field capacity was eliminated.
// - Field size was eliminated, because size==ListGetSize(...).

// Definition of the structure
struct _PersonSet_ {
  List *persons;  // points to a SortedList of Person pointers
};

// Comparison function to be used in generic SortedList.
// Comparison is based on Person ID
static int cmpP(const void *a, const void *b) {
  Person *p1 = (Person *)a;
  Person *p2 = (Person *)b;
  int d = p1->id - p2->id;
  return (d > 0) - (d < 0);
}

// Create a PersonSet.
PersonSet *PersonSetCreate() {
  // You must allocate space for the struct and create an empty persons list!
  PersonSet* p = (PersonSet*) malloc(sizeof(*p));
  if(p == NULL){
    perror("PersonCreate");
    return NULL;
  }
  p -> persons = ListCreate(cmpP);
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
  ListDestroy(&((*pps) -> persons));
  free(*pps);
  *pps = NULL;
  
}

int PersonSetSize(const PersonSet *ps) { return ListGetSize(ps->persons); }

int PersonSetIsEmpty(const PersonSet *ps) { return ListIsEmpty(ps->persons); }

void PersonSetPrint(const PersonSet *ps) {
  printf("{\n");
  for (ListMoveToHead(ps->persons); ListCurrentIsInside(ps->persons);
       ListMoveToNext(ps->persons)) {
    Person *p = (Person *)ListGetCurrentItem(ps->persons);
    PersonPrintf(p, ";\n");
  }
  printf("}(size=%d)\n", PersonSetSize(ps));
  ListTestInvariants(ps->persons);
}

// Find node in list ps->persons of person with given id.
// (INTERNAL function.)
static int search(const PersonSet *ps, int id) {
  Person dummyperson;
  dummyperson.id = id;
  return ListSearch(ps->persons, &dummyperson);
}

// Add person *p to *ps.
// Do nothing if *ps already contains a person with the same id.
void PersonSetAdd(PersonSet *ps, Person *p) {
  int aux = search(ps,p->id);
  if(aux == -1){
    ListInsert(ps->persons,p);
  } 

}

// Pop one person out of *ps.
Person *PersonSetPop(PersonSet *ps) {
  assert(!PersonSetIsEmpty(ps));
  // It is easiest to pop and return the person in the first position!
  Person* aux = ListRemoveHead(ps->persons);
  return aux;
}

// Remove the person with given id from *ps, and return it.
// If no such person is found, return NULL and leave set untouched.
Person *PersonSetRemove(PersonSet *ps, int id) {
  // You may call search here!
  int aux = search(ps,id);
  if(aux == 0){
    Person* aux = ListGetCurrentItem(ps->persons);
    ListRemoveCurrent(ps->persons);
    return aux;
  } 
  return NULL;
  
}

// Get the person with given id of *ps.
// return NULL if it is not in the set.
Person *PersonSetGet(const PersonSet *ps, int id) {
  // You may call search here!
  int aux = search(ps,id);
  if(aux == 0){
    Person* aux = ListGetCurrentItem(ps->persons);
    return aux;
  } 
  return NULL;
  
}

// Return true (!= 0) if set contains person wiht given id, false otherwise.
int PersonSetContains(const PersonSet *ps, int id) {
  return search(ps, id) >= 0;
}

// Return a NEW PersonSet with the union of *ps1 and *ps2.
// NOTE: memory is allocated.  Client must call PersonSetDestroy!
PersonSet *PersonSetUnion(const PersonSet *ps1, const PersonSet *ps2) {
  PersonSet *ps = PersonSetCreate();
  // Merge the two sorted lists (similar to mergesort).
  for(ListMoveToHead(ps1->persons);ListCurrentIsInside(ps1->persons);ListMoveToNext(ps1->persons)){
    PersonSetAdd(ps,ListGetCurrentItem(ps1->persons));
  }
  for(ListMoveToHead(ps2->persons);ListCurrentIsInside(ps2->persons);ListMoveToNext(ps2->persons)){
    PersonSetAdd(ps,ListGetCurrentItem(ps2->persons));
  }
  return ps;
}

// Return a NEW PersonSet with the intersection of *ps1 and *ps2.
// NOTE: memory is allocated.  Client must call PersonSetDestroy!
PersonSet *PersonSetIntersection(const PersonSet *ps1, const PersonSet *ps2) {
  PersonSet *ps = PersonSetCreate();
  for(ListMoveToHead(ps1->persons);ListCurrentIsInside(ps1->persons);ListMoveToNext(ps1->persons)){
    Person* aux = ListGetCurrentItem(ps1->persons);
    if (PersonSetContains(ps2,aux->id) != 0)
    {
      PersonSetAdd(ps,aux);
    }
  }
  return ps;
}

// Return a NEW PersonSet with the set difference of *ps1 and *ps2.
// NOTE: memory is allocated.  Client must call PersonSetDestroy!
PersonSet *PersonSetDifference(const PersonSet *ps1, const PersonSet *ps2) {
  PersonSet *ps = PersonSetCreate();
  for(ListMoveToHead(ps1->persons);ListCurrentIsInside(ps1->persons);ListMoveToNext(ps1->persons)){
    Person* aux = ListGetCurrentItem(ps1->persons);
    if (PersonSetContains(ps2,aux->id) == 0)
    {
      PersonSetAdd(ps,aux);
    }
  }
  
  return ps;
}

// Return true iff *ps1 is a subset of *ps2.
int PersonSetIsSubset(const PersonSet *ps1, const PersonSet *ps2) {
  for (ListMoveToHead(ps1->persons);ListCurrentIsInside(ps1->persons);ListMoveToNext(ps1->persons))
  {
    Person* aux = ListGetCurrentItem(ps1->persons);
    if (PersonSetContains(ps2,aux->id) == 0)
    {
      return 0;
    }
  }
  return 1;
  
}

// Return true if the two sets contain exactly the same elements.
int PersonSetEquals(const PersonSet *ps1, const PersonSet *ps2) {
  // You may call PersonSetIsSubset here!
  if(PersonSetIsSubset(ps1,ps2) && PersonSetIsSubset(ps2,ps1) ){
    return 1;
  }
  else return 0;
  
}
