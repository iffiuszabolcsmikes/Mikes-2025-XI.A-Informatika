#include <iostream>
#include <iomanip>
#include <algorithm>

using namespace std;

enum Szin { PIROS, ZOLD, FEHER, SARGA, KEK };
enum Nemzet { BRIT, SVED, DAN, NORVEG, NEMET };
enum Ital { TEA, KAVE, TEJ, SOR, VIZ };
enum Cigi { PALLMALL, DUNHILL, BLENDS, BLUEMASTER, PRINCE };
enum Allat { KUTYA, MADAR, MACSKA, LO, HAL };

string szinNev[] =
{
    "piros","zold","feher","sarga","kek"
};

string nemzetNev[] =
{
    "brit","sved","dan","norveg","nemet"
};

string italNev[] =
{
    "tea","kave","tej","sor","viz"
};

string cigiNev[] =
{
    "Pall Mall","Dunhill","Blends","Bluemaster","Prince"
};

string allatNev[] =
{
    "kutya","madar","macska","lo","hal"
};

int hol(int t[], int ertek)
{
    for(int i=0;i<5;i++)
        if(t[i]==ertek)
            return i;

    return -1;
}

void kiir(int szin[],
          int nemzet[],
          int ital[],
          int cigi[],
          int allat[])
{
    const int W = 15;

    cout << "\n";

    cout << "+" << string(12,'-');
    for(int i=0;i<5;i++)
        cout << "+" << string(W,'-');
    cout << "+\n";

    cout << "|" << setw(12) << left << "";

    for(int i=0;i<5;i++)
        cout << "|" << setw(W) << left << i+1;

    cout << "|\n";

    cout << "+" << string(12,'-');
    for(int i=0;i<5;i++)
        cout << "+" << string(W,'-');
    cout << "+\n";

    cout << "|" << setw(12) << left << "Szin";
    for(int i=0;i<5;i++)
        cout << "|" << setw(W) << left << szinNev[szin[i]];
    cout << "|\n";

    cout << "|" << setw(12) << left << "Nemzet";
    for(int i=0;i<5;i++)
        cout << "|" << setw(W) << left << nemzetNev[nemzet[i]];
    cout << "|\n";

    cout << "|" << setw(12) << left << "Ital";
    for(int i=0;i<5;i++)
        cout << "|" << setw(W) << left << italNev[ital[i]];
    cout << "|\n";

    cout << "|" << setw(12) << left << "Cigaretta";
    for(int i=0;i<5;i++)
        cout << "|" << setw(W) << left << cigiNev[cigi[i]];
    cout << "|\n";

    cout << "|" << setw(12) << left << "Allat";
    for(int i=0;i<5;i++)
        cout << "|" << setw(W) << left << allatNev[allat[i]];
    cout << "|\n";

    cout << "+" << string(12,'-');
    for(int i=0;i<5;i++)
        cout << "+" << string(W,'-');
    cout << "+\n";

    int halasHaz = hol(allat, HAL);

    cout << "\nA halat a "
         << nemzetNev[nemzet[halasHaz]]
         << " tartja.\n";
}

int main()
{
    int szin[]   = {0,1,2,3,4};
    int nemzet[] = {0,1,2,3,4};
    int ital[]   = {0,1,2,3,4};
    int cigi[]   = {0,1,2,3,4};
    int allat[]  = {0,1,2,3,4};

    do
    {
        int zold = hol(szin,ZOLD);
        int feher = hol(szin,FEHER);

        if(zold + 1 != feher)
            continue;

        int kek = hol(szin,KEK);

        do
        {
            if(hol(nemzet,NORVEG)!=0)
                continue;

            if(abs(hol(nemzet,NORVEG)-kek)!=1)
                continue;

            if(hol(nemzet,BRIT)!=hol(szin,PIROS))
                continue;

            do
            {
                if(hol(ital,TEJ)!=2)
                    continue;

                if(hol(nemzet,DAN)!=hol(ital,TEA))
                    continue;

                if(hol(szin,ZOLD)!=hol(ital,KAVE))
                    continue;

                do
                {
                    if(hol(szin,SARGA)!=hol(cigi,DUNHILL))
                        continue;

                    if(hol(cigi,BLUEMASTER)!=hol(ital,SOR))
                        continue;

                    if(hol(nemzet,NEMET)!=hol(cigi,PRINCE))
                        continue;

                    if(abs(hol(cigi,BLENDS)-hol(ital,VIZ))!=1)
                        continue;

                    do
                    {
                        if(hol(nemzet,SVED)!=hol(allat,KUTYA))
                            continue;

                        if(hol(cigi,PALLMALL)!=hol(allat,MADAR))
                            continue;

                        if(abs(hol(cigi,BLENDS)-hol(allat,MACSKA))!=1)
                            continue;

                        if(abs(hol(allat,LO)-hol(cigi,DUNHILL))!=1)
                            continue;

                        kiir(szin,nemzet,ital,cigi,allat);
                        return 0;

                    }
                    while(next_permutation(allat,allat+5));

                }
                while(next_permutation(cigi,cigi+5));

            }
            while(next_permutation(ital,ital+5));

        }
        while(next_permutation(nemzet,nemzet+5));

    }
    while(next_permutation(szin,szin+5));

    return 0;
}
