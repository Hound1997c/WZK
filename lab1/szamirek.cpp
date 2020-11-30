#include <stdio.h> 
#include <stdlib.h>
#include <time.h>
#include <math.h>  
#include <iostream>
#include<iomanip>

using namespace std;

bool is_primary(int number)
{
    for(int i=2;i<sqrt(number);i+=2)
    {
        if(number%i==0) return false;
    }
    return true;
}

int get_primary(int the_smalest)
{
    printf("\nszukamy pierwszej\n");
    if (the_smalest % 2 == 0) the_smalest+=1;

    int primary_number = the_smalest;

    bool have_primary = false;

    for(int primary_number = the_smalest;have_primary==false;primary_number+=2)
    {
        printf("liczba: %i\n",primary_number);
        have_primary = is_primary(primary_number);
    } 
    return primary_number;
}

//https://www.bragitoff.com/2015/09/c-program-for-gauss-elimination-for-solving-a-system-of-linear-equations/
void gaus(float ** &matrix,int n)
{
    //int n,i,j,k;
    int i,j,k;
    cout.precision(4);        //set precision
    cout.setf(ios::fixed);
    cout<<"\nEnter the no. of equations\n";        
    //cin>>n;                //input the no. of equations
    //float matrix[n][n+1],x[n];        //declare an array to store the elements of augmented-matrix    
    for (i=0;i<n;i++)                    //Pivotisation
        for (k=i+1;k<n;k++)
            if (abs(matrix[i][i])<abs(matrix[k][i]))
                for (j=0;j<=n;j++)
                {
                    long long temp=matrix[i][j];
                    matrix[i][j]=matrix[k][j];
                    matrix[k][j]=temp;
                }
    cout<<"\nThe matrix after Pivotisation is:\n";
    for (i=0;i<n;i++)            //print the new matrix
    {
        for (j=0;j<=n;j++)
            cout<<matrix[i][j]<<setw(16);
        cout<<"\n";
    }    
    for (i=0;i<n-1;i++)            //loop to perform the gauss elimination
        for (k=i+1;k<n;k++)
            {
                double t=(double)(matrix[k][i]/matrix[i][i]);
                for (j=0;j<=n;j++)
                    matrix[k][j]=matrix[k][j]-t*matrix[i][j];    //make the elements below the pivot elements equal to zero or elimnate the variables
            }
     
    cout<<"\n\nThe matrix after gauss-elimination is as follows:\n";
    for (i=0;i<n;i++)            //print the new matrix
    {
        for (j=0;j<=n;j++)
            cout<<matrix[i][j]<<setw(16);
        cout<<"\n";
    }
    float x[n];
    for (i=n-1;i>=0;i--)                //back-substitution
    {                        //x is an array whose values correspond to the values of x,y,z..
        x[i]=matrix[i][n];                //make the variable to be calculated equal to the rhs of the last equation
        for (j=i+1;j<n;j++)
            if (j!=i)            //then subtract all the lhs values except the coefficient of the variable whose value                                   is being calculated
                x[i]=x[i]-matrix[i][j]*x[j];
        x[i]=x[i]/matrix[i][i];            //now finally divide the rhs by the coefficient of the variable to be calculated
    }
    cout<<"\nThe values of the variables are as follows:\n";
    for (i=0;i<n;i++)
        cout<<x[i]<<endl;            // Print the values of x, y,z,....    
}

int main(int argc, char* argv[])
{
    int p,s,n,t;

    s=27;
    n=33;
    t=5;

    long long A[t];
    long long S[n];

    //p = rand() % (2*(s+n)) + (n + s + 1);

    //cout<<say()<<endl;
    p = get_primary(n+s+1);
    printf("\np to: %i\n\n",p);

    printf("\n\nWspółczynniki: \n");
    A[0] = s;
    for(int i=1;i<t;i++)
    {
        A[i]=rand() % 100 +1;
        //printf("\nA(%i)=%l ",i,A[i]);
        cout<<"\nA("<<i<<")= "<<A[i];
    }

    printf("\n\nSekret: %i\n",s);

    printf("algorytm rozdzielajacy:\n\n\n");

    for(int i=0;i<n;i++)
    {
        S[i]=0;
        //int sumy=0;
        for(int j=0;j<t;j++)
        {
            S[i]+=( (long long)(A[j]*pow((double)i+1,(double)(j))));
        }
        //sumy%=p;
        //S[i]%=p;
       // S[i]+=sumy;
        //printf("\nS(%i)=%l ",i,S[i]);
        cout<<"\nS("<<i<<")= "<<S[i];
    }

    printf("\nalgorytm laczacy:\n\n\n");

    /*long long gaus_matrix = new * long long * [3];
    for(int i=0;i<3;i++)
    {
        gaus_matrix[i]= new long long [4];
    }*/
    
   
    
    float ** gaus_matrix = new float * [t];
    
    
    for(int i=0;i<t;i++)
    {
        gaus_matrix[i]= new float [t+1];
    } 

    for(int i=0;i<t;i++)
    {
        for(int j=0; j<t;j++)
        {
            gaus_matrix[i][j]=(int)pow((double)(i+1),(double)j);
        }
        gaus_matrix[i][t]=S[i];
    } 

    gaus(gaus_matrix,t);
    cout<<"after gaus\n";
    for(int i=0;i<t;i++)
    {
        delete [] gaus_matrix[i];
    }
    delete [] gaus_matrix;

    
    
    return 0;
}


void trash()
{
    /*int inter_x[t];
    int inter_y[t];
    double l_free[t];
    //double nointeger_rest = 0;

    for(int i=0;i<t;i++)
    {
        inter_x[i]=i+1;
        inter_y[i]=inter_x[i]*inter_x[i];
    }

    for(int i=0;i<t;i++)
    {
        int l_up=1;
        int l_down=1;
        for(int j=0;j<t;j++)
        {
            if(i!=j)
            {
                l_up*=inter_x[j];
                l_down*=(inter_x[i]-inter_x[j]);
            }
        }
        l_free[i]=l_up/l_down;
    }


    printf("liczenie sekretu:\n\n\n");

    int s_retrieve=0;
    for(int i=0;i<t;i++)
    {
        s_retrieve += ((int)(inter_y[i]*l_free[i]) % p);
    }

    printf("odzyskany sekret:%i\n",s_retrieve); */
}