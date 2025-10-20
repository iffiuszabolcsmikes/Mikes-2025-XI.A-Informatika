#include <iostream>

using namespace std;

int lnko(int x, int y)
{
    while (y != 0)
    {
        int tmp = x % y;
        x = y;
        y = tmp;
    }
    return x;
}

int lkkt(int x, int y)
{
    return x * y / lnko(x, y);
}

int szamjegyekSzama(int x)
{
    int db = 0;
    while(x != 0)
    {
        x = x / 10;
        db++;
    }
    return db;
}

int szamjegyekOsszege(int x)
{
    int ossz = 0;
    while (x != 0)
    {
        ossz = ossz + x % 10;
        x = x / 10;
    }
    return ossz;
}

int main()
{
    int x;
    int y;
    cout << "x=";
    cin >> x;
    cout << "y=";
    cin >> y;
    cout << "lnko: " << lnko(x, y) << endl;
    cout << "lkkt: " << lkkt(x, y) << endl;
    cout << "szamjegyek szama: " << szamjegyekSzama(x) << endl;
    cout << "szamjegyek osszege: " << szamjegyekOsszege(x) << endl;
    return 0;
}