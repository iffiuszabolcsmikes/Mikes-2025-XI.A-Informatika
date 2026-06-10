#include <iostream>

using namespace std;

//verem merete
const int N = 100;
char verem[N];

//megoldas halmaz
int MH = 3;
//lehetseges esetek szama
int LE = 3;

int k = 1;

char betuk[10] = "abc";


bool megoldas(int szint)
{
    return true;
}

bool jo(int szint)
{
    return true;
}

void kiir(int szint)
{
    verem[szint] = 0;
    cout << k << ". " << verem << endl;
    k++;
}

void backtracking(int szint)
{
    if(szint == MH)
    {
        if(megoldas(szint))
            kiir(szint);
        return;
    }
    for(int i = 0; i < LE; i++)
    {
        verem[szint] = betuk[i];
        if(jo(szint))
            backtracking(szint + 1);
    }
}


int main()
{
    backtracking(0);
    return 0;
}
