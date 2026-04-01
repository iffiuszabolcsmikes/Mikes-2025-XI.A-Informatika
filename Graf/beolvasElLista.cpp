#include <iostream>
#include <fstream>

#define N 100
using namespace std;

int beolvasElLista(int graf[][N],char fileName[])
{
    int n = 0;//csomopontok szama
    int sor, oszlop;
    ifstream f;
    f.open(fileName);
    if(!f)
    {
        cout << "Hiba nem sikerult megnyitni: " << fileName << endl;
        return 0;
    }
    f >> n;
    for(int i = 0; i < n; i++)
    {
        f >> sor;
        while(f.peek() != '\n' && f >> oszlop)
        {
            graf[sor][oszlop] = 1;
            graf[oszlop][sor] = 1;
        }
    }

    f.close();
    return n;
}
void kiirSzomszedsagiMatrix(int graf[][N], int n)
{
    cout << "Szomszedsagi matrix:" << endl;
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            cout << graf[i][j] << " ";
        }
        cout << endl;
    }
}
void kiirSzomszedsagiLista(int graf[][N], int n)
{
    cout << "Szomszedsagi lista:" << endl;
    for(int i = 0; i < n; i++)
    {
        cout << i << ": ";
        for(int j = 0; j < n; j++)
        {
            if(graf[i][j] == 1)
                cout << j << ", ";
        }
        cout << endl;
    }
}
void kiirElLista(int graf[][N], int n)
{
    cout << "El lista:" << endl;
    cout << n << endl;
    for(int i = 0; i < n; i++)
    {
        for(int j = i + 1; j < n; j++)
        {
            if(graf[i][j])
                 cout << i << " " << j << endl;
        }
    }
}

int main()
{
    cout << "graf" << endl;
    int graf[N][N]={0};
    int n;
    n = beolvasElLista(graf,"graf.txt");
    kiirSzomszedsagiMatrix(graf,n);
    kiirSzomszedsagiLista(graf, n);
    kiirElLista(graf, n);
    return 0;
}
/*
6
0 3 4
1 2 3
2 1 3 4
3 0 1 2 5
4 0 2
5 3
*/
