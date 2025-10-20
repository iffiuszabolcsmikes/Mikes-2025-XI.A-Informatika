#include <iostream>
#include<cstdlib>
#include<ctime>

#define N 100

using namespace std;

void feltolt(int tomb[N], int n)
{
    srand(time(0));
    for(int i = 0; i < n; i++)
    {
        tomb[i] = rand() % 100;
    }
}

void kiir(int tomb[N], int n)
{
    for(int i = 0; i < n; i++)
    {
        cout << tomb[i] << " ";
    }
    cout << endl;
}

void csere(int *x, int *y)
{
    int tmp = *x;
    *x = *y;
    *y = tmp;
}

void rendezKivalaszt(int tomb[], int n)
{
    for(int i = 0; i < n; i++)
    {
        int mini = i;
        for(int j = i + 1; j < n; j++)
        {
            if(tomb[j] < tomb[mini])
            {
                mini = j;
            }
        }
       csere(&tomb[i], &tomb[mini]);
    }
}

int maximum(int tomb[], int n)
{
    int maxi = 0;
    for(int i = 0; i < n; i++)
    {
        if(tomb[i] > tomb[maxi])
        {
            maxi = i;
        }
    }
    return maxi;
}

int osszeg(int tomb[], int n)
{
    int ossz = 0;
    for(int i = 0; i < n; i++)
    {
        ossz = ossz + tomb[i];
    }
    return ossz;
}

float atlag(int tomb[], int n)
{
    return (float)osszeg(tomb, n) / n;
}

int main()
{
    int tomb[N];
    int n = 30;
    feltolt(tomb, n);
    kiir(tomb, n);

    cout << tomb[maximum(tomb, n)] << " a legnagyobb szam "<<endl;
    cout << osszeg(tomb, n) << " a szamok osszege "<<endl;
    cout << atlag(tomb, n) << " a szamok atlaga"<<endl;

    cout << "redezve:" << endl;
    rendezKivalaszt(tomb, n);
    kiir(tomb, n);

    return 0;
}
