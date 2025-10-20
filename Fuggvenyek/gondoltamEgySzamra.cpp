#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int main()
{
    srand(time(0));
    int kitalalando = rand()%100 + 1, tippSzam = 0, tipp;
    cout << "Gondoltam egy szamra 1 es 100 kozott" << endl;
    do {
        cout << "Adj meg egy tippet!" << endl;
        cin >> tipp;
        tippSzam++;
        if(kitalalando > tipp) {
            cout << "Tippelj nagyobbat!" << endl;
        } else if(kitalalando < tipp) {
            cout << "Tippelj kisebbet!" << endl;
        }
    }while(kitalalando != tipp);
    cout << "Gratulalok kitalaltad " << tippSzam << " probalkozasbol!" << endl;
    return 0;
}
