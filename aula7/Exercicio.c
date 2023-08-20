#include<stdio.h>
#include <math.h>

unsigned int F_recursiva(int n);
unsigned int F_iterativa(int n);

static unsigned int mult_recursiva;
static unsigned int mult_iterativa;

int main(void){

    
    printf("n\tF_recur(n)\tMult(n)\tF_iterat\tMult(n)");
    int i = 0;
    int fim = 25;
    while(i<=fim){
        
        
        mult_recursiva =0;
        mult_iterativa =0;
        printf("\n%d\t%d",i,F_recursiva(i));
        printf("\t\t%d",mult_recursiva);
        printf("\t%d",F_iterativa(i));
        printf("\t\t%d",mult_iterativa);
        
        i++;
    } 

    


}

unsigned int F_recursiva(int n){

    if(n<=2){
        
        return 1;
    }
    else{
        int aux =0;
        for (int k = 0; k < n-2 ; k++)
        {
            mult_recursiva = mult_recursiva + 1;
            aux = aux + F_recursiva(k) * F_recursiva(n-3-k);
        }
        
        return F_recursiva(n-1) + F_recursiva(n-2) + aux;
        
    }
}


unsigned int F_iterativa(int n){

    int array[n+1];
    array[0] = 1;
    array[1] = 1;
    array[2] = 1;
    
    for (int i = 3; i <= n ; i++)
    {
        int aux=0;
        array[i] = array[i-1] + array[i-2];
        for (int k = 0; k < i-2; k++)
        {
            mult_iterativa++;
            aux = aux + array[k]*array[i-3-k] ;
        }
        array[i] = array[i]+ aux;
        
        
        
    }

    return array[n];
    
}

