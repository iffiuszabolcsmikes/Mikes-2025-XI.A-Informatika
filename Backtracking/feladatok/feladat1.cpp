#include <iostream>

using namespace std;

//verem merete
const int N = 100;
char verem[N];

//megoldas halmaz
int MH = 4;
//lehetseges esetek szama
int LE = 5;

int k = 1;

char betuk[10] = "01234";
int ossz(int szint)
{
    int sum=0;
    for(int i=0; i<=szint;i++)
    {
        sum+=verem[i]-'0';
    }
    return sum;
}

bool megoldas(int szint)
{
     if(ossz(szint - 1)==4)
        return true;
    return false;
}


bool jo(int szint)
{
    if(verem[0]=='0')
        return false;
    if(ossz(szint)>4)
        return false;
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
