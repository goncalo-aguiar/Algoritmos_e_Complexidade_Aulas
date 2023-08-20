#include <stdio.h>
int p(int n){
   if(n<=1){
       return 0;
   }
   else if(n>1){
       return n + p(n/3) + p((n+1)/3) + p((n+2)/3);
   }
}

int p_iterativa(int n){
    int a[n+1];
     a[0] =0;
     a[1] = 0;
    for (int i = 2; i <= n; i++)
    {
        a[i] = a[i/3] + a[(i+1)/3] + a[(i+2)/3];
    }

    return a[n];
    
}

int p_iterativa1(int n){
    
    for (int i = 0; i <= n; i++)
    {
        x = x
    }

    return a[n];
    
}
int main(void){
   printf("%d",p(4));
   printf("\n%d",p_iterativa(4));
}


