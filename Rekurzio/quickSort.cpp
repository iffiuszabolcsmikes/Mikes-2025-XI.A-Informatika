#include <iostream>
#include <ctime>
#include <cstdlib>

#define N 30

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
        cout << tomb[i] << " ";
    }
    cout << endl;
}

int particio(int tomb[], int bal, int jobb)
{
    int pivot = tomb[bal];
    bal--;
    jobb++;
    while(true)
    {
        do
        {
            bal++;
        }
        while(tomb[bal] < pivot);
        do
        {
            jobb--;
        }
        while(tomb[jobb] > pivot);
        if(bal >= jobb)
        {
            return jobb;
        }
        //csere
        int tmp = tomb[bal];
        tomb[bal] = tomb[jobb];
        tomb[jobb] = tmp;
    }
}

void quickSort(int tomb[], int bal, int jobb)
{
    if(bal < jobb)
    {
        int pivot = particio(tomb, bal, jobb);
        quickSort(tomb, bal, pivot);
        quickSort(tomb, pivot + 1, jobb);
    }
}

int main()
{
    int n = N;
    int tomb[N];
    srand(time(0));
    feltolt(tomb, n);
    kiir(tomb, n);
    quickSort(tomb, 0, n - 1);
    kiir(tomb, n);
    return 0;
}
