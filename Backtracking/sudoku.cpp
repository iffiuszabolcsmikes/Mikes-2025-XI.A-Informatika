#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;

int a[9][9];

void kiir()
{
    for(int i = 0; i < 9; i++)
    {
        for(int j = 0; j < 9; j++)
            cout << setw(2) << a[i][j];
        cout << endl;
    }
}

void beolvas()
{
    ifstream f("sudoku.in");
    for(int i = 0; i < 9; i++)
        for(int j = 0; j < 9; j++)
            f >> a[i][j];
}

bool jo(int sor, int oszlop)
{
    for(int i=0; i<9; i++)
    {
        if(i!=oszlop && a[sor][i] == a[sor][oszlop])
            return false;
        if(i!=sor && a[i][oszlop] == a[sor][oszlop])
            return false;
    }

    for(int i=sor/3*3; i<sor/3*3+3; i++)
        for(int j=oszlop/3*3; j<oszlop/3*3+3; j++)
            if((j!=oszlop || i!=sor) && a[i][j] == a[sor][oszlop])
                return false;
    return true;
}

bool megoldas()
{
    for(int i = 0; i < 9; i++)
        for(int j = 0; j < 9; j++)
            if(a[i][j]==0)
                return false;
    return true;
}

void backtracking()
{
    if(megoldas())
    {
        cout<<"megoldas"<<endl;
        kiir();
    }
    for(int i = 0; i < 9; i++)
    {
        for(int j = 0; j < 9; j++)
        {
            if (a[i][j] == 0)
            {
                for(int szam = 1; szam <= 9 ; szam++)
                {
                    a[i][j]=szam;
                    if (jo(i , j))
                    {
                        backtracking();
                    }
                }
                a[i][j]=0;
                return;
            }
        }
    }
}

int main()
{
    beolvas();
    kiir();
    backtracking();

    return 0;
}

/* nehez
8 0 0 0 0 0 0 0 0
0 0 3 6 0 0 0 0 0
0 7 0 0 9 0 2 0 0
0 5 0 0 0 7 0 0 0
0 0 0 0 4 5 7 0 0
0 0 0 1 0 0 0 3 0
0 0 1 0 0 0 0 6 8
0 0 8 5 0 0 0 1 0
0 9 0 0 0 0 4 0 0
*/
/* konnyu
5 3 0 0 7 0 0 0 0
6 0 0 1 9 5 0 0 0
0 9 8 0 0 0 0 6 0
8 0 0 0 6 0 0 0 3
4 0 0 8 0 3 0 0 1
7 0 0 0 2 0 0 0 6
0 6 0 0 0 0 2 8 0
0 0 0 4 1 9 0 0 5
0 0 0 0 8 0 0 7 9
*/
