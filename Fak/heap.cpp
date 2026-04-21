#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>

using namespace std;

int kupac[100];
int n = 0;

void printHeap(int i = 0, string prefix = "", bool isLast = true, bool isRoot = true)
{
    if(i >= n) return;

    cout << prefix;

    if(!isRoot)
        cout << (isLast ? "\xc0\xc4\xc4" : "\xc3\xc4\xc4");

    cout << kupac[i] << endl;

    if(!isRoot)
        prefix += (isLast ? "   " : "\xb3  ");

    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if(left < n)
        printHeap(left, prefix, right >= n, false);

    if(right < n)
        printHeap(right, prefix, true, false);
}

void csere(int &x, int &y)
{
    int tmp = x;
    x = y;
    y = tmp;
}

void kiirTomb()
{
    for(int i = 0; i < n; i++)
        cout << setw(2) << i << ". ";
    cout << endl;
    for(int i = 0; i < n; i++)
        cout << setw(3) << kupac[i] << " ";
    cout << endl;
}

void kupacolFel(int i)
{
    int szulo = (i - 1) / 2;
    while(kupac[i] > kupac[szulo])
    {
        csere(kupac[i], kupac[szulo]);
        i = szulo;
        szulo = (i - 1) / 2;
    }
}

void kupacolLe(int i)
{
    int bal = i * 2 + 1;
    int jobb = i * 2 + 2;
    int nagyobb = i;

    if(bal < n && kupac[bal] > kupac[nagyobb])
        nagyobb = bal;
    if(jobb < n && kupac[jobb] > kupac[nagyobb])
        nagyobb = jobb;

    while(nagyobb != i)
    {
        csere(kupac[i], kupac[nagyobb]);
        i = nagyobb;
        bal = i * 2 + 1;
        jobb = i * 2 + 2;
        if(bal < n && kupac[bal] > kupac[nagyobb])
            nagyobb = bal;
        if(jobb < n && kupac[jobb] > kupac[nagyobb])
            nagyobb = jobb;
    }
}

void beszur(int x)
{
    kupac[n] = x;
    kupacolFel(n);
    n++;
}

//felulirja a kupacban az i-edik indexen levo elemet x-el
void felulir(int i, int x )
{
    kupac[i] = x;
    int szulo = (i - 1) / 2;
    if(kupac[i] > kupac[szulo])
    {
        kupacolFel(i);
    }
    else
    {
        kupacolLe(i);
    }
}

void torol(int i)
{
    if(i >= n)
        return;

    felulir(i, kupac[0] + 1);
    n--;
    felulir(0, kupac[n]);
}

int main()
{
    srand(time(0));
    for(int i = 0; i < 10; i++)
    {
        int x = rand() % 100;
        cout << "#" << i << " beszurjuk: " << x << endl;
        beszur(x);
        printHeap();
    }

    kiirTomb();
    felulir(8, 99);
    printHeap();
    felulir(1, 1);
    torol(3);
    printHeap();
    return 0;
}
