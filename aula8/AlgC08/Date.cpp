//NMEC: ...
//NICK: ...

// Complete the functions (marked by ...)
// so that it passes all tests in DateTest.

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include "Date.h"

const Date DateMIN = {0, 1, 1};
const Date DateMAX = {9999, 12, 31};

// Check if a yy,mm,dd tuple forms a valid date.
// (This would be a public static method in Java.)
int DateIsValid(int yy, int mm, int dd) {
  return (DateMIN.year)<=yy && yy<=(DateMAX.year) &&
         1<=mm && mm<=12 &&
         1<=dd && dd<=DateDaysInMonth(yy, mm);
}

// Function to test desired internal invariant for valid Date values:
// the Date should contain valid year,month,day fields.
static int invariant(Date* d) {
  return DateIsValid(d->year, d->month, d->day);
}

// Alocate and store a date given by yy, mm, dd integers.
// (yy, mm, dd) are required to form a valid date.
// Returns the pointer to the new date structure,
// or NULL if allocation fails.
Date* DateCreate(int yy, int mm, int dd) {
  assert( DateIsValid(yy, mm, dd) );
  if(d == null) return NULL;
  Date* d =(Date*)malloc(sizeof(Date));
  d -> year = yy;
  d -> month = mm;
  d-> day = dd;
  
  assert( invariant(d) );   // check invariant
  return d;
}

// Free the memory pointed to by *pd and invalidate *pd contents.
// Precondition: *pd must not be NULL.
// Postcondition: *pd is set to NULL.
void DateDestroy(Date* *pd) {
  assert(*pd != NULL);
  Date* s = *pd;
  free(s);
  *pd = NULL;
}

// table of month lengths in common and leap years
static const uint8_t monthLength[][12] = {
  {31,28,31,30,31,30,31,31,30,31,30,31},
  {31,29,31,30,31,30,31,31,30,31,30,31}
};

int DateDaysInMonth(int yy, int mm) {
  int isLeap = DateIsLeapYear(yy);
  return monthLength[isLeap][mm-1];
}

int DateIsLeapYear(int yy) {
  return (yy%4==0 && yy%100!=0) || yy%400==0;
}

static char* fmts[] = {
  (char*)"%04d-%02d-%02d",  // YMD
  (char*)"%3$02d/%2$02d/%1$04d", // DMY
  (char*)"%2$02d/%3$02d/%1$04d", // MDY
};

static char strBuffer[64];

// Return a formatted string representation of date d.
// Careful: the string buffer will be overwritten by the next call.
// You should strcpy or strdup the result if you need persistence!
char* DateFormat(const Date* d, int FMT) {
  if (d==NULL)
    snprintf(strBuffer, sizeof(strBuffer), "NULL");
  else
    snprintf(strBuffer, sizeof(strBuffer), fmts[FMT], d->year, d->month, d->day);
  return strBuffer;
}

// Parse str according to format and fill in *d.
// Return 1 and update *d if str contains a correctly formatted and valid date.
// Return 0 and leave *d untouched, otherwise.
int DateParse(Date *d, const char* str, int FMT) {
  int yy, mm, dd;
  int n = sscanf(str, fmts[FMT], &yy, &mm, &dd);
  if (!(n==3 && DateIsValid(yy, mm, dd)))
    return 0;
  d->year = yy;
  d->month = mm;
  d->day = dd;
  return 1;
}

// Compare dates a and b.
// Return an integer >0 if a>b, 0 if a==b and <0 if a<b.
int DateCompare(const Date* a, const Date* b) {
  if(a->year != b ->year) return a->year - b ->year;
  else{
     if(a->month != b ->month) return a->month != b ->month;
     else{
        if(a->day != b ->day) return a->day - b ->day;
        else return 0;
     }
  }
  
  
}

// Increment date.
// Precondition: d must precede DateMAX.
void DateIncr(Date* d) {
  assert( DateCompare(d, &DateMAX) < 0 );
  int ano = d -> year;
  int mes = d -> month;
  int dia = d -> day;
  if( dia == DateDaysInMonth(ano,mes)){
     dia = 1;
     if(mes == 12){
        mes = 1;
        ano++;
     }
     else{
        mes++;
     }
     
  }
  else {
     dia++;
  }
  d->year = ano;
  d->month = mes;
  d -> day = dia;
  
  assert( invariant(d) );   // check invariant
}

Decrement date.
Precondition: d must succeed DateMIN.
void DateDecr(Date* d) {
  assert( DateCompare(d, &DateMIN) > 0 );
  if(d->day == 1){
     if(d->month == 1){
        d->year = d->year - 1;
        d -> month = 12;
        d-> day = DateDaysInMonth(d->year, d -> month);
     }
     else{
        d -> month = d->month -1;
        d-> day = DateDaysInMonth(d->year, d -> month);
     }
  }
  else{
      d-> day = d-> day -1;
  }
  assert( invariant(d) );   // check invariant
}

