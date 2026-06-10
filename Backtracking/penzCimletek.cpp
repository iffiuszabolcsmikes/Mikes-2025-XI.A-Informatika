#include <iostream>

using namespace std;

//verem merete
const int N = 100;
int verem[N];

//lehetseges esetek szama
int LE = 4;

int k = 1;

int cimletek[10] = {5, 10, 20, 50};


int osszeg(int szint)
{
    int sum = 0;
    for(int i = 0; i < szint; i++)
        sum += verem[i];
    return sum;
}

bool megoldas(int szint)
{
    return osszeg(szint ) == 75;
}

bool jo(int szint)
{
    for(int i = 0; i < szint; i++)
        if(verem[i] > verem[szint])
            return false;
    return true;
}

void kiir(int szint)
{
    verem[szint] = 0;
    cout << k << ". " << endl;
    for(int i = 0; i < szint; i++)
        cout << verem[i] << " ";
    cout << endl;
    k++;
}

void backtracking(int szint)
{
    if(szint > 10)
        return;
    if(megoldas(szint))
    {
        kiir(szint);
        return;
    }

    for(int i = 0; i < LE; i++)
    {
        verem[szint] = cimletek[i];
        if(jo(szint))
            backtracking(szint + 1);
    }
}


int main()
{
    backtracking(0);
    return 0;
}
