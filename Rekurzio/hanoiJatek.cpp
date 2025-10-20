#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <cstring>
#define N 3

using namespace std;

int A[N] = {0}, B[N] = {0}, C[N] = {0}, a = N, b = 0, c = 0;

void kiir()
{
    int n = N;
    cout << setw(n+2) << right << 'A' << setw(n+1) << ' ';
    cout << setw(n+2) << right << 'B' << setw(n+1) << ' ';
    cout << setw(n+2) << right << 'C' << setw(n+1) << ' ' << endl;
    for(int i = 0; i < n; i++)
    {
        char korong[N+1];
        int j;
        for(j = 0; j < A[i]; j++)
        {
            korong[j] = '#';
        }
        korong[j] = 0;
        cout << setw(n+1) << right << korong << A[i] << setw(n+1) << left << korong;
        for(j = 0; j < B[i]; j++)
        {
            korong[j] = '#';
        }
        korong[j] = 0;
        cout << setw(n+1) << right << korong << B[i] << setw(n+1) << left << korong;
        for(j = 0; j < C[i]; j++)
        {
            korong[j] = '#';
        }
        korong[j] = 0;
        cout << setw(n+1) << right << korong << C[i] << setw(n+1) << left << korong;
        cout << endl;
    }
}

void feltoltRud(int n)
{
    for(int i = 0; i < n; i++)
    {
        A[i] = n-i ;
        B[i] = 0;
        C[i] = 0;
    }
    a = n;
    b = 0;
    c = 0;
}

int lepes = 0; //lepesek szam

bool nyertel()
{
    if(c == N)
        return true;
    else
        return false;
}

char uzenet[100];

void atpakol(char c1, char c2)
{
    if(c1 == c2) return;
    int *from, *to, *fromSize, *toSize;
    switch(c1)
    {
        case 'a': from = A; fromSize = &a; break;
        case 'b': from = B; fromSize = &b; break;
        case 'c': from = C; fromSize = &c; break;
        case 'r': return;
        default: strcpy(uzenet, "Nem megfelelo betu"); return;
    }
    switch(c2)
    {
        case 'a': to = A; toSize = &a; break;
        case 'b': to = B; toSize = &b; break;
        case 'c': to = C; toSize = &c; break;
        default: strcpy(uzenet, "Nem megfelelo betu"); return;
    }
    if(*fromSize == 0)
    {
        strcpy(uzenet, "A rudon nincs korong amit at lehetne pakolni.");
    }
    else if(*toSize != 0 && to[*toSize - 1] < from[*fromSize - 1])
    {
        strcpy(uzenet, "Nagyobb korongot nem lehet kisebbre tenni.");
    }
    else
    {
        to[*toSize] = from[*fromSize - 1];
        from[*fromSize - 1] = 0;
        (*toSize)++;
        (*fromSize)--;
        strcpy(uzenet, ""); // Üzenet törlése
    }
}

void init(int n)
{
    feltoltRud(n);
    strcpy(uzenet, "");
}

int main()
{
    int n = N;
    char c1, c2;

    init(n);

    do
    {
        system("cls");

        cout << "Hanoi tornyai:" << endl << "x - Kilepes" << "R - reset" << endl;
        kiir();
        cout << "Irj be a tornyoknak megfelelo betuket (a, b, c) az atpakolashoz." << endl;
        cout << uzenet << endl;;
        cout << "Honnan: ";
        cin >> c1;
        if(c1 == 'x')
        {
            cout << "Kilepes"<< endl;
            break;
        }
        if(c1 == 'r')
        {
            init(n);
            continue;
        }
        cout << "Hova: ";
        cin >> c2;

        atpakol(c1, c2);
    }while(!nyertel());

    if(nyertel())
    {
        system("cls");
        cout << "Hanoi tornyai:" << endl;
        kiir();
        cout << "Gratulalok, megnyerted a jatekot!" << endl;
    }

    return 0;
}
