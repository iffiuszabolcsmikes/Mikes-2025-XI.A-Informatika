#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>

using namespace std;

void csere(int &x, int &y)
{
    int tmp = x;
    x = y;
    y = tmp;
}

void kiirTomb(int tomb[], int n)
{
    for(int i = 0; i < n; i++)
        cout << setw(2) << i << ". ";
    cout << endl;
    for(int i = 0; i < n; i++)
        cout << setw(3) << tomb[i] << " ";
    cout << endl;
}

void kupacolFel(int kupac[], int i)
{
    int szulo = (i - 1) / 2;
    while(kupac[i] > kupac[szulo])
    {
        csere(kupac[i], kupac[szulo]);
        i = szulo;
        szulo = (i - 1) / 2;
    }
}

void kupacolLe(int kupac[], int i, int n)
{
    int bal = i * 2 + 1;
    int jobb = i * 2 + 2;
    int nagyobb = i;

    if(bal < n && kupac[bal] > kupac[nagyobb])
        nagyobb = bal;
    if(jobb < n && kupac[jobb] > kupac[nagyobb])
        nagyobb = jobb;

    while(nagyobb != i)
    {
        csere(kupac[i], kupac[nagyobb]);
        i = nagyobb;
        bal = i * 2 + 1;
        jobb = i * 2 + 2;
        if(bal < n && kupac[bal] > kupac[nagyobb])
            nagyobb = bal;
        if(jobb < n && kupac[jobb] > kupac[nagyobb])
            nagyobb = jobb;
    }
}

void heapSort(int tomb[], int n)
{
    //kupac felepitese
    for(int i = 0; i < n; i++)
    {
        kupacolFel(tomb, i);
    }
    //toroljuk a gyokeret amig el nem fogy a kupac
    for(int i = n - 1; i > 0; i--)
    {
        csere(tomb[0], tomb[i]);
        kupacolLe(tomb, 0, i);
    }
}

int main()
{
    int tomb[100];
    int n = 20;

    srand(time(0));
    for(int i = 0; i < n; i++)
    {
        tomb[i] = rand() % 100;
    }

    kiirTomb(tomb, n);
    heapSort(tomb, n);
    kiirTomb(tomb, n);

    return 0;
}
