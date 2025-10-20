#include <iostream>
#include <cstdlib>
#include <ctime>

#define N 10
using namespace std;

int hivasokSzama = 0;

int faktorialis_r(int n)
{
    if(n == 0)
    {
        return 1;
    }
    else
    {
        return  n * faktorialis_r(n - 1);
    }
}

int faktorialis(int n)
{
    int prod = 1;
    for(int i = 1; i <= n; i++)
    {
        prod = prod * i;
    }
    return prod;
}

int hatvany_r(int alap, int kitevo)
{
    if(kitevo == 0)
    {
        return 1;
    }
    else
    {
        return alap * hatvany_r(alap, kitevo - 1);
    }
}

int hatvany(int alap, int kitevo)
{
    int prod = 1;
    for(int i = 1; i <= kitevo; i++)
    {
        prod = prod * alap;
    }
    return prod;
}

int fibonacci_r(int n)
{
    hivasokSzama++;
    if(n == 0)
    {
        return 0;
    }
    if(n==1)
    {
        return 1;
    }
    return fibonacci_r(n - 1) + fibonacci_r(n - 2);
}

int fibonacci(int n)
{
    int fib_2=0;
    int fib_1=1;
    int fib_akt=1;
    for(int i = 2; i <= n; i++)
    {
        fib_akt = fib_1 + fib_2;
        fib_2 = fib_1;
        fib_1 = fib_akt;
    }
    return fib_akt;
}

void kiir_rekurziv_elol(int tomb[N], int n, int i)
{
    if(i == n)
    {
        cout << endl;
        return;
    }
    else
    {
        cout << tomb[i] << " ";
        kiir_rekurziv_elol(tomb, n, i + 1);
    }
}

void kiir_rekurziv_hatul(int tomb[N], int n, int i)
{
    if(i == n)
    {
        return;
    }
    else
    {

        kiir_rekurziv_hatul(tomb, n, i + 1);
        cout<< tomb[i] << " ";
    }
}

int legnagyobbSzamjegy_r(int szam)
{
    if(szam < 10)
    {
        return szam;
    }
    else
    {
        int maxi = legnagyobbSzamjegy_r(szam / 10);
        if(maxi < szam % 10)
        {
            maxi = szam % 10;
        }
        return maxi;
    }
}

int legnagyobbSzamjegy(int szam)
{
    int maxi = 0;
    while(szam != 0)
    {
        if(szam % 10 > maxi)
        {
            maxi = szam % 10;
        }
        szam = szam / 10;
    }
    return maxi;
}

int forditott_r(int szam, int forditottSzam = 0) //alapertelmezett ertek 0 ha nem volt mas megadva
{
    if(szam == 0)
    {
        return forditottSzam;
    }
    else
    {
        return forditott_r(szam / 10, forditottSzam * 10 + szam % 10);
    }
}

int forditott(int szam)
{
    int forditottSzam = 0;
    while(szam != 0)
    {
        forditottSzam = forditottSzam * 10 + szam % 10;
        szam = szam / 10;
    }
    return forditottSzam;
}

bool tukorSzam(int szam)
{
    return szam == forditott_r(szam);
}

int szamjegySzam(int szam)
{
    int szamjegyekszam = 0;
    while(szam > 0)
    {
        szam = szam / 10;
        szamjegyekszam++;
    }
    return szamjegyekszam;
}

int szamjegySzam_r(int szam)
{
    if(szam < 10)
    {
        return 1;
    }
    else
    {
        return szamjegySzam_r(szam / 10) + 1;
    }
}

int szamokOsszege_r(int n)
{
    if(n == 1) return 1;
    return szamokOsszege_r(n - 1) + n;
}

int szamokNegyzetenekOsszege_r(int n)
{
    if(n == 1) return 1;
    return szamokNegyzetenekOsszege_r(n - 1) + n * n;
}

int lnko_r(int a, int b)
{
    if(b == 0) return a;
    return lnko_r(b, a% b);
}

int lnko(int a, int b)
{
    while(b != 0)
    {
        int tmp = a % b;
        a = b;
        b = tmp;
    }
    return a;
}

void csillag_r(int szam) //kiir szam darab *-ot
{
    if(szam == 0) {
            cout << endl;
            return;
    }
    cout << "*";
    csillag_r(szam - 1);
}

int hangaSorozat_r(int n)
{
    if(n==1) return 5;
    return 50 + hangaSorozat_r(n - 1) * n;
}

int gyorsHatvany_r(int alap, int kitevo)
{
    if(kitevo == 0) return 1;

    if(kitevo % 2 == 0) //paros
        return gyorsHatvany_r(alap * alap, kitevo / 2);
    else    //paratlan
        return alap * gyorsHatvany_r(alap, kitevo - 1);
}

int main()
{
    srand(time(0));
    cout << "REKURZIO" << endl;
    cout << "faktorialis rekurzio: " << faktorialis_r(5) << endl;
    cout << "faktorialis: " << faktorialis(5) << endl;
    cout << "hatvany rekurzio: " << hatvany_r(5,3) << endl;
    cout << "hatvany: " << hatvany(5,3) << endl;
    cout << "fibonacci rekurziv: " << fibonacci_r(7) << endl;
    cout << "meghivasok szama: " << hivasokSzama << endl;
    cout << "fibonacci: " << fibonacci(7) << endl;
    cout << "legnagyobb szamjegy rekurzio: " << legnagyobbSzamjegy_r(4359536) << endl;
    cout << "legnagyobb szamjegy: " << legnagyobbSzamjegy(4359536) << endl;
    cout << "forditott szamjegy: " << forditott_r(1234) << endl;;
    cout << "forditott szam: " << forditott(1234) << endl;
    cout << "szamjegyszam: " << szamjegySzam_r(43675) << endl;
    cout << "rekurziv szamjegyszam: " << szamjegySzam(43675) << endl;
    cout << "rekurziv szamok osszege: " << szamokOsszege_r(15) << endl;
    cout << "rekurziv szamok negyzetenek osszege: " << szamokNegyzetenekOsszege_r(5) << endl;
    cout << "rekurziv lnko: " << lnko_r(32, 48) << endl;
    cout << "lnko: " << lnko(32, 48) << endl;
    cout << "csillag rekurziv: ";
    csillag_r(10);
    cout << "rekurziv hanga sorozat: " <<hangaSorozat_r(4) << endl;
    cout << "gyorshatvany: " << gyorsHatvany_r(2, 10) << endl;

    int tomb[N];

    for(int i = 0; i < N; i++)
    {
        tomb[i] = rand()%100;
    }

    cout << "Kiir elol." << endl;
    kiir_rekurziv_elol(tomb, N, 0);
    cout << "Kiir hatul." << endl;
    kiir_rekurziv_hatul(tomb, N, 0);
    return 0;
}
