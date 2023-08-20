#include <stdio.h>
int subseq(int a[],int size){
    int iguais =0;
    int subconjuntos = 0;
    for (int i = 1; i < size-1; i++)
    {
       if (a[i]==a[i+1] && a[i]== a[i-1] && a[i-1] == a[i+1])
       {
           subconjuntos++;
       }   
    }
    return subconjuntos;
    
}

int main(void){
    int a[] = {2,2,2,2,2,6,7,3,3,8};
    printf("%d",subseq(a,10));
}

