#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>

#define N 20

using namespace std;

void feltolt(int tomb[], int n)
{
    for(int i = 0; i < n; i++)
    {
        tomb[i] = rand()%100;
    }
}

void kiir(int tomb[], int n)
{
    for(int i = 0; i < n; i++)
    {
        cout << setw(3) << i << ".";
    }
    cout << endl;
    for(int i = 0; i < n; i++)
    {
        cout << setw(3) << tomb[i] << " ";
    }
    cout << endl;
}

int binarisKereses_rekurziv(int tomb[], int keresettElem, int eleje, int vege)
{
    int pivot = (eleje + vege) / 2;
    if(tomb[pivot] == keresettElem)
    {
        return pivot;
    }
    if(eleje == vege)
    {
        return -1;
    }
    if(tomb[pivot] > keresettElem)
    {
        return binarisKereses_rekurziv(tomb, keresettElem, eleje, pivot - 1);
    }
    else
    {
        return binarisKereses_rekurziv(tomb, keresettElem, pivot + 1, vege);
    }
}

void rendez_kivalaszt(int tomb[], int n)
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
        if(mini != i)
        {
            int tmp = tomb[mini];
            tomb[mini] = tomb[i];
            tomb[i] = tmp;
        }
    }
}

int main()
{
    srand(time(0));
    int n = N;
    int tomb[N];

    feltolt(tomb, n);
    kiir(tomb, n);
    int keresettElem = tomb[0];
    rendez_kivalaszt(tomb, n);
    cout<< "rendezve:" << endl;
    kiir(tomb, n);
    cout << "A keresett elem " << keresettElem
        << " indexe: " << binarisKereses_rekurziv(tomb, keresettElem, 0, n-1);
    return 0;
}
