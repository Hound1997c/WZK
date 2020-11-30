#include <stdio.h> 
#include <stdlib.h>
#include <time.h>
#include <math.h>  
#include <iostream>
#include<iomanip>

using namespace std;

void erastoteres(bool * tab, int n)
{
    for(int i=2;i*i<=n;i++)
    {
        if(tab[i]==true)
        {
            for(int j=i*i;j<=n;j+=i)
            {
                tab[j]=false;
            }
        }
    }
}

int find_primary_p_or_q(bool * tab, int n, int num)
{   
    if(num>n) return -1;
    for(int i=num;i>=2;i--)
    {
        if(tab[i]==true && i%4==3) return i;
    }
    return 2;
}

int find_x(long N, int p, int q)
{
    srand(time(NULL));

    int x = rand() % N + N;
    while(x%p==0 || x%q==0)
    {
        x++;
    }
    return x;
}

void generate_serie(bool * dest_tab, int n, int x, int N)
{
    for(int i=0;i<n;i++)
    {
        x = x*x % N;
        dest_tab[i] = x%2;
    }
}

bool long_serie_test(bool * array, int n, int number)
{
    int ones = 0;
    int zeros = 0;

    if(array[0]==0) zeros++;
    else ones++;
    for(int i=1;i<n;i++)
    {
        if(array[i]==0)
        {
            if(array[i-1]==1) ones=0;
            zeros++;
            if(zeros>=number) return false;
        }
        else
        {
            if(array[i-1]==0) zeros=0;
            ones++;
            if(ones>=number) return false;
        }
    }
    return true;
}


bool lonely_bit_test(bool * array, int n)
{
    int ones;
    for(int i=0;i<n;i++)
    {
        if(array[i]==1) ones++;
    }
    if(ones < 10275 && ones > 9725)
    {
        return true;
    }
    return false;
}

bool serie_test(bool * array, int n)
{
    int zeros_array[7]={0,0,0,0,0,0,0};
    int ones_array[7]={0,0,0,0,0,0,0};

    int zeros=0;
    int ones=0;

    if(array[0]==0) zeros++;
    else ones++;
    for(int i=0; i<n; i++)
    {
        if(array[i]==0)
        {
            if(array[i-1]==1)
            {   
                if(ones>=6) ones_array[6]++;
                else ones_array[ones]++;
                ones=0;
            }
            zeros++;
        }
        else
        {
            if(array[i-1]==0)
            {
                if(zeros>=6) zeros_array[6]++;
                else zeros_array[zeros]++;
                zeros=0;
            }
            ones++;
        }
    }

    int zeros_ok_interval=0;
    int ones_ok_interval=0;

    if(zeros_array[1]<=2685 && zeros_array[1]>=2315) zeros_ok_interval++;
    if(ones_array [1]<=2685 && ones_array [1]>=2315) ones_ok_interval++;
    if(zeros_array[2]<=1386 && zeros_array[2]>=1114) zeros_ok_interval++;
    if(ones_array [2]<=1386 && ones_array [2]>=1114) ones_ok_interval++;
    if(zeros_array[3]<=723 && zeros_array[3]>=527) zeros_ok_interval++;
    if(ones_array [3]<=723 && ones_array [3]>=527) ones_ok_interval++;
    if(zeros_array[4]<=384 && zeros_array[4]>=240) zeros_ok_interval++;
    if(ones_array [4]<=384 && ones_array [4]>=240) ones_ok_interval++;
    if(zeros_array[5]<=209 && zeros_array[5]>=103) zeros_ok_interval++;
    if(ones_array [5]<=209 && ones_array [5]>=103) ones_ok_interval++;
    if(zeros_array[6]<=209 && zeros_array[6]>=103) zeros_ok_interval++;
    if(ones_array [6]<=209 && ones_array [6]>=103) ones_ok_interval++;

    if (zeros_ok_interval==6 || ones_ok_interval==6) return true;
    return false;
}
int main(int argc, char* argv[])
{   
    int p=500;
    int q=800;

    bool * primary_numbers = new bool [q+1];
    primary_numbers[0]=false;
    primary_numbers[1]=false;
    for(int i=2;i<=q;i++)
    {
        primary_numbers[i]=true;
    }

    erastoteres(primary_numbers,q);

    //for(int i=0;i<=q;i++) cout<<i<<": "<<primary_numbers[i]<<endl;

    q=find_primary_p_or_q(primary_numbers,q,q);
    p=find_primary_p_or_q(primary_numbers,q,p);
    delete [] primary_numbers;
    long N = p*q;
    cout<<"p: "<<p<<endl;
    cout<<"q: "<<q<<endl;
    cout<<"N: "<<N<<endl;
    long x = find_x(N,p,q);
    cout<<"x: "<<x<<endl;

    bool * bit_serie = new bool [20000];

    generate_serie(bit_serie,20000,x,N);

    //for(int i=0;i<20000;i++) cout<<i<<": "<<bit_serie[i]<<endl;
    
    cout<<"wynik testu długiej serii:\n";
    cout<<long_serie_test(bit_serie,20000,26)<<endl;
    cout<<"wynik testu pojedynczego bitu:\n";
    cout<<lonely_bit_test(bit_serie,20000)<<endl;
    cout<<"wynik testu serii:\n";
    cout<<serie_test(bit_serie,20000)<<endl;
    delete [] bit_serie;

     

    return 0;
}