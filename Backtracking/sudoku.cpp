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


int k = 1;

void backtracking()
{
    if(megoldas())
    {
        cout<<"megoldas"<<endl;
        kiir();
        return;
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

void backtracking2(int sor = 0, int oszlop = 0)
{
    // Ha elértuk a 9. sort, a tabla teljesen es helyesen megtelt
    if (sor == 9)
    {
        cout<<k<<". megoldas"<<endl;
        k++;
        //kiir();
        return;
    }

    // Ha a sor vegere ertunk, ugras a kovetkezo sor elso oszlopara
    if (oszlop == 9)
    {
        backtracking2(sor + 1, 0);
        return;
    }

    // Ha a cella mar adott (nem 0), ugrunk a kovetkezo oszlopra
    if (a[sor][oszlop] != 0)
    {
        backtracking2(sor, oszlop + 1);
        return;
    }

    // Kiprobaljuk a szamokat 1-tal 9-ig
    for (int szam = 1; szam <= 9; szam++)
    {
        a[sor][oszlop] = szam;
        if (jo(sor, oszlop))
        {
            // Ha a lepes jo, megyunk tovabb. Ha True-val ter vissza, keszen vagyunk.
            backtracking2(sor, oszlop + 1);
        }
    }

    // Backtrack: ha egyik szam sem volt jo, visszaallítjuk 0-ra
    a[sor][oszlop] = 0;
}

int main()
{
    beolvas();
    kiir();
    backtracking(); // A (0,0) celláról indulunk
    //backtracking2(0, 0); // A (0,0) celláról indulunk
    return 0;
}
/* nagyon nehez
0 6 1 0 0 7 0 0 3
0 9 2 0 0 3 0 0 0
0 0 0 0 0 0 0 0 0
0 0 8 5 3 0 0 0 0
0 0 0 0 0 0 5 0 4
5 0 0 0 0 8 0 0 0
0 4 0 0 0 0 0 0 1
0 0 0 1 6 0 8 0 0
6 0 0 0 0 0 0 0 0
*/
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
