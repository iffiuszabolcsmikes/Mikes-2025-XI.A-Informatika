#include <iostream>

using namespace std;

//verem merete
const int N = 100;

int sakk[N][N]={0};
//megoldas halmaz
int MH = 8;
//lehetseges esetek szama
int LE = 8;

int k = 1;

bool megoldas(int szint)
{
    return true;
}

bool jo(int i, int j)
{
    for(int k = 0; k < LE; k++)
    {
        //oszlopok
        if(k != i && sakk[k][j] == 1)
        {
            return false;
        }
        //bal felso atlo
        if(k>0 && i-k>=0 && j-k>=0 && sakk[i-k][j-k]==1)
        {
            return false;
        }
        //jobb felso atlo
        if(k>0 && i-k>=0 && j+k<LE && sakk[i-k][j+k]==1)
        {
            return false;
        }
    }
    return true;
}

void kiir(int szint)
{
    cout << k << ". " << endl;
    k++;
    for(int i = 0; i < szint; i++)
    {
         for(int j=0; j < LE; j++)
         {
             cout << sakk[i][j] << " ";
         }
         cout << endl;
    }
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
            sakk[szint][i] = 1;
            if(jo(szint, i))
                backtracking(szint + 1);
            sakk[szint][i] = 0;
    }
}

int main()
{
    backtracking(0);
    return 0;
}
