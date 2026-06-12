#include <iostream>

using namespace std;

//verem merete
const int N = 100;
char verem[N];

//megoldas halmaz
int MH = 3;
//lehetseges esetek szama
int LE = 6;

int k = 1;

char betuk[10] = "abcuie";

int maganhangzokSzama(int szint)
{
    int db=0;
    for(int i = 0; i < szint; i++)
    {
        if(verem[i]== 'a' || verem[i]== 'u' || verem[i]== 'i' || verem[i]== 'e')
            db++;
    }
    return db;
}
bool megoldas(int szint)
{
    if(maganhangzokSzama(szint)==2)
        return true;
    return false;
}

bool jo(int szint)
{
    for(int i = 0; i < szint; i++)
        if(verem[i] == verem[szint])
            return false;
    if(maganhangzokSzama(szint+1)>2)
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
