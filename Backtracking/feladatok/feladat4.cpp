#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>

using namespace std;

const int N=3;

int matrix[N][N];

void feltolt()
{
    for(int i=0;i<N;i++)
        for(int j=0;j<N;j++)
            matrix [i][j]=rand()%100;
}

void kiir()
{
    for(int i=0;i<N;i++)
    {
        for(int j=0;j<N;j++)
            cout << setw(3) << matrix[i][j];
        cout << endl;
    }
}

int verem[N];
int maxOsszeg = 0;
int maxVerem[N];

void megoldas(int szint)
{
    int ossz = 0;
    for(int i=0;i<N;i++)
        ossz += matrix[i][verem[i]];
    if(ossz > maxOsszeg)
    {
        maxOsszeg = ossz;
        for(int i=0;i<N;i++)
            maxVerem[i] = verem[i];
    }
}

bool jo(int szint)
{
    for(int i=0;i<szint;i++)
        if(verem[i]==verem[szint])
            return false;
    return true;
}

void kiirMegoldas(int szint)
{
    cout << "max osszeg: " << maxOsszeg << endl;
    for(int i=0;i<N;i++)
        cout << setw(3) << maxVerem[i];
    cout << endl;
}

void backtracking(int szint)
{
    if(szint == N)
    {
        megoldas(szint);
        return;
    }
    for(int i = 0; i < N; i++)
    {
        verem[szint] = i;
        if(jo(szint))
            backtracking(szint + 1);
    }
}

int main()
{
    srand(time(0));
    feltolt();
    kiir();
    backtracking(0);
    kiirMegoldas(N);
    return 0;
}
