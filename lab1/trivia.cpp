#include <stdio.h> 
#include <stdlib.h>
#include <time.h>

int main(int argc, char* argv[])
{   
    int n, k;


    n=5;
    k=30;
    /*printf("podaj n\n");
    scanf("%i",&n);
    printf("podaj k\n");
    scanf("%i",&k);*/

    srand(time(NULL));
    
    int s = rand() % k;
    printf("Wygenerowany sekret to: %i\n",s);

    int S[n];
    S[n-1]=s;
    for(int i=0;i<n-1;i++)
    {
        S[i]=rand() % k;
        printf("S(%i) =%i  ",S[i]);
        S[n-1]-=S[i];
    }
    printf("\n");
    S[n-1]%=k;

    printf("ostatni wyraz S(n-1): %i\n\n\n",S[n-1]);

    s=0;
    for(int i=0; i<n ;i++)
    {
        s+=S[i];
    }
    s%=k;
    printf("odzyskujemy sekret: s= %i\n",s);

    return 0;
}