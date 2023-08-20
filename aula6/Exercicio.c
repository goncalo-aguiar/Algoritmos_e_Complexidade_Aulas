#include<stdio.h>
#include <math.h>

unsigned int T1(int n);
unsigned int T2(int n);
unsigned int T3(int n);
static unsigned int chamadas;

int main(void){

    int n =0;
    int inicio=0;
    int fim=29;
    printf("n\tT1(n)\tNum.Cha\tT2(n)\tNum.Cha\tT3(n)\tNum.Cha");
    while(n<fim){
        
        
        chamadas =0;
        printf("\n%d\t%d",n,T1(n));
        printf("\t%d",chamadas);
        chamadas =0;
        printf("\t%d",T2(n));
        printf("\t%d",chamadas);
        chamadas =0;
        printf("\t%d",T3(n));
        printf("\t%d",chamadas);
        n ++;
    }
        
        
    printf("\n");
    

    n =0;
    inicio=0;
    fim=20;
    printf("n\tT1(n)\tNum.Cha\tT2(n)\tNum.Cha\tT3(n)\tNum.Cha");
    while(inicio<fim){
        if(n==0){
            chamadas =0;
            printf("\n%d\t%d",n,T1(n));
            printf("\t%d",chamadas);
            chamadas =0;
            printf("\t%d",T2(n));
            printf("\t%d",chamadas);
            chamadas =0;
            printf("\t%d",T3(n));
            printf("\t%d",chamadas);
            n++;
        }
        else{
            chamadas =0;
            printf("\n%d\t%d",n,T1(n));
            printf("\t%d",chamadas);
            chamadas =0;
            printf("\t%d",T2(n));
            printf("\t%d",chamadas);
            chamadas =0;
            printf("\t%d",T3(n));
            printf("\t%d",chamadas);
            n = n*2;
        }
        
        inicio++;

    }
    
}

unsigned int T1(int n){
    chamadas++;
    if(n==0)return 0;
    else{
        
        return T1(n/4) + n;
    }

}

unsigned int T2(int n){
    chamadas++;
    if (n<=3){
      return n;  
    }
    else {
        
        return T2(n/4) + T2((n+3)/4) + n;
    }
}

unsigned int T3(int n){
    chamadas++;
    if (n<=3){
        return n;
    }
    else{
        
        if(n%4==0){
            return 2* T3(n/4) +n;
        }
        else{
             return  T3(n/4)+ T3((n+3)/4) +n;
        }
    }

}