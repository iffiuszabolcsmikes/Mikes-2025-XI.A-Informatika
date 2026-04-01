#include <iostream>
#include <fstream>
#include <stack>
#include <queue>

#define N 100

using namespace std;

bool visited[N];
int fokszam[N];
//szulo vektor
//minden csomopont eseten szamontatartjuk, hogy ki a szuloje
int p[N];

//tavolsag vektor
//minden csomopont eseten szamontartjuk, hogy milyen tavolsagra van a start csomoponttol
int d[N];

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
bool teljes(int graf[][N], int n)
{
    feltoltFokszam(graf, n);
    for(int i = 0; i < n; i++)
    {
        if(fokszam[i] != n - 1)
            return false;
    }
    return true;
}
bool tartalmazIzPontot(int graf[][N], int n)
{
    feltoltFokszam(graf, n);
    for(int i = 0; i < n; i++)
    {
        if(fokszam[i] == 0)
            return true;
    }
    return false;
}
void init(int n)
{
    for(int i = 0; i < n; i++)
    {
        visited[i] = false;
        d[i] = -1;
        p[i] = -1;
    }
}
void DFS(int graf[][N], int n, int start)
{
    cout << "DFS sorrend:" << endl;
    stack<int> verem;
    verem.push(start);
    while(!verem.empty())
    {
        int u = verem.top();
        verem.pop();
        ///meg nem volt meglatogatva
        if(visited[u] == false)
        {
            visited[u] = true;
            cout << u << " ";
            for(int i = 0; i < n; i++)
            {
                ///i nem volt meglatogatva es van el i es u kozott
                if(visited[i] == false && graf[u][i] == 1)
                {
                    verem.push(i);
                }
            }
        }
    }
    cout << endl;
}
void BFS(int graf[][N], int n, int start)
{
    cout << "BFS sorrend:" << endl;
    queue<int> sor;
    sor.push(start);
    while(!sor.empty())
    {
        int u = sor.front();
        sor.pop();
        ///meg nem volt meglatogatva
        if(visited[u] == false)
        {
            visited[u] = true;
            cout << u << " ";
            for(int i = 0; i < n; i++)
            {
                ///i nem volt meglatogatva es van el i es u kozott
                if(visited[i] == false && graf[u][i] == 1)
                {
                    sor.push(i);
                }
            }
        }
    }
    cout << endl;
}
//BFS-en alapul
//megadja minden csomopont tavolsagat a start csomoponttol
void MooreTavolsag(int graf[][N], int n, int start)
{
    for(int i = 0; i < n; i++)
    {
        p[i] = -1;
        d[i] = -1;
    }

    d[start] = 0;

    queue<int> sor;
    sor.push(start);
    while(!sor.empty())
    {
        int u = sor.front();
        sor.pop();
        for(int i = 0; i < n; i++)
        {
            ///i meg mindig vegtelen tavolsagra van es van el u es i kozt
            if(d[i] == -1 && graf[u][i] == 1)
            {
                d[i] = d[u] + 1;
                p[i] = u;
                sor.push(i);
            }
        }
    }
}
bool osszefuggo(int graf[][N], int n)
{
    init(n);
    BFS(graf, n, 0);
    for(int i = 0; i < n; i++)
    {
        //ide nem jutott el
        if(visited[i] == false)
            return false;
    }
    return true;
}
int komponensekSzama(int graf[][N], int n)
{
    int db = 0;
    init(n);
    for(int i = 0; i < n; i++)
    {
        if(visited[i] == false)
        {
            BFS(graf, n, i);
            db++;
        }
    }
    return db;
}
int izolaltPontokSzama(int graf[][N], int n)
{
    int db = 0;
    init(n);
    for(int i = 0; i < n; i++)
    {
        int fokszam = 0;
        for(int j=0; j < n; j++)
        if(visited[i] == false)
        {
           if(graf[i][j] != 0)
            fokszam++;
        }
        if(fokszam == 0)
            db++;
    }
    return db;
}
void komplementer(int graf1[][N], int n, int graf2[][N])
{
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            if(graf1[i][j] == 1 || i == j)
                graf2[i][j] = 0;
            else
                graf2[i][j] = 1;
        }
    }
}
void kiirTavolsagok(int n)
{
    cout << "Moore tavolsagok:" << endl;
    for(int i = 0; i< n; i++)
    {
        cout << i << " : " << d[i] << endl;
    }
}
void kiirSzulok(int n)
{
    cout << "Szulok:" << endl;
    for(int i = 0; i < n; i++)
    {
        cout << i << " : " << p[i] << endl;
    }
}
void kiirUtvonal(int hova)
{
    if(p[hova] == -1)
        cout << hova << "->";
    else
    {
        kiirUtvonal(p[hova]);
        cout << hova << "->";
    }
}
void DFS_rekurziv(int graf[][N], int n, int start)
{
    //meglatogatas
    visited[start] = true;
    cout << start << ", ";

    //minden szomszedjara
    for(int i = n - 1; i > 0; i--)
    {
        //meg nem latogattam meg i-t es van el start es is kozott
        if(visited[i] == false && graf[start][i])
        {
            DFS_rekurziv(graf, n, i);
        }
    }
}
bool kormentesKomponens(int graf[][N], int n, int start)
{
    init(n);
    stack<int> verem;
    verem.push(start);

    while(!verem.empty())
    {
        int u = verem.top();
        verem.pop();
        ///meg nem volt meglatogatva
        if(visited[u] == false)
        {
            visited[u] = true;
            for(int i = 0; i < n; i++)
            {
                ///i nem volt meglatogatva es van el i es u kozott
                if(visited[i] == false && graf[u][i] == 1)
                {
                    if(p[i] != -1) return false;
                    p[i] = u;
                    verem.push(i);
                }
            }
        }
    }
    return true;
}
bool fa(int graf[][N], int n)
{
    init(n);
    return osszefuggo(graf, n) && kormentesKomponens(graf, n, 0);
}
bool erdo(int graf[][N], int n)
{
    init(n);
    int db = 0;
    for(int i = 0; i < n; i++)
    {
        if(visited[i] == false)
        {
            BFS(graf,n,i);
            if(kormentesKomponens(graf, n, i) == false)
                return false;
        }
    }
    return true;
}
void szomszedsagiLista(int graf[][N], int n)
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
bool EulerGraf(int graf[][N], int n)
{
    for(int i=0;i<n;i++)
    {
        int b=0;
        for(int j=0;j<n;j++)
        {
           if(graf[i][j]==1)
           {
               b++;
           }
        }
        if(b%2!=0)
        {
           return false;
        }
    }
    return true;
}
int main()
{
    cout << "graf" << endl;
    int graf[N][N]={0};
    int n;
    n = beolvas(graf,"graf.txt");
    kiir(graf,n);
    feltoltFokszam(graf, n);
    kiirFokszam(graf,n);
    if(teljes(graf,n))
    {
        cout<<"teljes graf"<<endl;
    }
    else cout<<"nem teljes graf"<<endl;
    if(tartalmazIzPontot(graf,n))
    {
        cout<<"tartalmaz izolalt pontot"<<endl;
    }
    else cout<<"nem tartalmaz izolalt pontot"<<endl;
    init(n);
    DFS(graf, n, 0);
    init(n);
    BFS(graf, n, 0);
    if(osszefuggo(graf,n))
    {
        cout<<"osszefuggo"<<endl;
    }
    else
    {
        cout<<"nem osszefuggo"<<endl;
    }
    cout << "Komponensek szama: " << komponensekSzama(graf,n)<<endl;
    cout << "Izolalt pontok szama: " << izolaltPontokSzama(graf,n)<<endl;
    cout << "Komplementer" << endl;
    int grafKomplementer[N][N];
    komplementer(graf,n,grafKomplementer);
    kiir(grafKomplementer,n);

    MooreTavolsag(graf, n, 3);
    cout << "Start = 3" << endl;
    kiirTavolsagok(n);
    kiirSzulok(n);
    kiirUtvonal(0);

    init(n);
    cout << endl << "DFS rekurziv: ";
    DFS_rekurziv(graf, n, 0);

    cout << endl;

    init(n);
    if(kormentesKomponens(graf,n, 0))
    {
        cout<<"Kormentes komponensben van a 0 csomopont"<<endl;
    }
    else
    {
        cout<<"Nem kormentes komponensben van a 0 csomopont"<<endl;
    }

    if(osszefuggo(graf,n))
    {
        cout<<"Osszefuggo"<<endl;
    }
    else
    {
        cout<<"NEM osszefuggo"<<endl;
    }

    if(fa(graf,n))
    {
        cout<<"Fa"<<endl;
    }
    else
    {
        cout<<"NEM Fa"<<endl;
    }
    if(erdo(graf,n))
    {
        cout<<"Erdo"<<endl;
    }
    else
    {
        cout<<"NEM erdo"<<endl;
    }
    szomszedsagiLista(graf, n);
    return 0;
}
