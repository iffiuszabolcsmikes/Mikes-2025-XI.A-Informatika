#include <iostream>
#include <iomanip>
#include <fstream>
#define N 3

using namespace std;

int A[N] = {0}, B[N] = {0}, C[N] = {0}, a = N, b = 0, c = 0;

void kiir(ostream &out)
{
    int n = N;
    out << setw(n+2) << right << 'A' << setw(n+1) << ' ';
    out << setw(n+2) << right << 'B' << setw(n+1) << ' ';
    out << setw(n+2) << right << 'C' << setw(n+1) << ' ' << endl;
    for(int i = 0; i < n; i++)
    {
        char korong[N+1];
        int j;
        for(j = 0; j < A[i]; j++)
            korong[j] = '#';
        korong[j] = 0;
        out << setw(n+1) << right << korong << A[i] << setw(n+1) << left << korong;
        for(j = 0; j < B[i]; j++)
            korong[j] = '#';
        korong[j] = 0;
        out << setw(n+1) << right << korong << B[i] << setw(n+1) << left << korong;
        for(j = 0; j < C[i]; j++)
            korong[j] = '#';
        korong[j] = 0;
        out << setw(n+1) << right << korong << C[i] << setw(n+1) << left << korong;
        out << endl;
    }
}

void feltoltRud(int rud[], int n)
{
    for(int i = 0; i < n; i++)
        rud[i] = n - i;
}

int nr = 0; // lépések száma

void hanoi(int from[], int &n1, int via[], int &n2, int to[], int &n3, int k, ostream &out)
{
    if(k == 1)
    {
        to[n3] = from[n1-1];
        from[n1-1] = 0;
        n3++;
        n1--;
        nr++;
        out << nr << ". lepes:------------------------------" << endl;
        kiir(out);
    }
    else
    {
        hanoi(from, n1, to, n3, via, n2, k - 1, out);
        hanoi(from, n1, via, n2, to, n3, 1, out);
        hanoi(via, n2, from, n1, to, n3, k - 1, out);
    }
}

int main()
{
    ofstream f("hanoi.txt");
    int n = N;
    feltoltRud(A, n);
    //Ha a cout jelyett f-et teszel a megoldas a hanoi.txt fajlban lesz
    kiir(cout);
    hanoi(A, a, B, b, C, c, n, cout);
    cout << "megoldas -> Hanoi.txt" << endl;
    f.close();
    return 0;
}
