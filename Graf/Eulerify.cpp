#include <iostream>
#include <fstream>
#include <stack>
#include <queue>

#define N 100

using namespace std;

int fokszam[N];

int beolvas(int graf[][N],char fileName[])
{
    int n = 0;//csomopontok szama
    int i, j;
    ifstream f;
    f.open(fileName);
    if(!f)
    {
        cout << "Hiba nem sikerult megnyitni: " << fileName << endl;
        return 0;
    }
    f >> n;
    while(f >> i >> j)
    {
        graf[i][j] = 1;
        graf[j][i] = 1;
    }
    f.close();
    return n;
}
void kiir(int graf[][N], int n)
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
void feltoltFokszam(int graf[][N], int n)
{
    for(int i = 0; i < n; i++)
    {
        fokszam[i] = 0;
        for(int j = 0; j < n; j++)
        {
            if(graf[i][j]!=0)
            {
                fokszam[i]++;
            }
        }
    }
}
void kiirFokszam(int graf[][N], int n)
{
    cout << "Fokszam" << endl;
    for(int i = 0; i < n; i++)
    {
        cout << i << ": " << fokszam[i] << endl;
    }
}

int Eulerify(int graf[][N], int n)
{
    int paratlanok[N];
    int p = 0;
    int elSzam = 0;

    feltoltFokszam(graf, n);

    // paratlan fokszamu csucsok
    for(int i = 0; i < n; i++)
    {
        if(fokszam[i] % 2 == 1)
        {
            if(fokszam[i] == n - 1)
                return -1; //nem kotheto uj elhez

            paratlanok[p] = i;
            p++;
        }
    }

    // parositas
    for(int i = 0; i < p; i += 2)
    {
        int u = paratlanok[i];
        int v = paratlanok[i + 1];

        // ha nincs el kozottuk hozzaadjuk
        if(graf[u][v] == 0)
        {
            graf[u][v] = graf[v][u] = 1;
            fokszam[u]++;
            fokszam[v]++;
            elSzam++;
        }
        else
        {
            // ha mar szomszedok keresunk koztes csucsot
            bool talalt = false;

            for(int k = 0; k < n; k++)
            {
                if(k != u && k != v &&
                   graf[u][k] == 0 &&
                   graf[v][k] == 0)
                {
                    graf[u][k] = graf[k][u] = 1;
                    graf[v][k] = graf[k][v] = 1;

                    fokszam[u]++;
                    fokszam[v]++;
                    fokszam[k] += 2;

                    elSzam += 2;
                    talalt = true;
                    break;
                }
            }

            if(!talalt)
                return -1; // nem lehet megoldani
        }
    }
    return elSzam;
}

int main()
{
    int graf[N][N]={0};
    int n;
    n = beolvas(graf,"graf.txt");
    kiir(graf,n);
    int e = Eulerify(graf, n);
    if(e == -1)
    {
        cout << "Nem lehet elek hozzaadasaval Euler graffa alakitani!" << endl;
    }
    else if(e == 0)
    {
        cout << "Mar Euler graf!" << endl;
    }
    else
    {
        cout << e << " elt kell hozzaadni a grafhoz hogy Euler graf legyen" << endl;
        kiir(graf,n);
    }

    return 0;
}

/*
5
0 1
0 3
1 2
1 3
2 3
2 4
3 4
*/
