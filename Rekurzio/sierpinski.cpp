#include <iostream>
#include <cmath>

using namespace std;

int matrix[1024][2048] = {0};

void kiirMatrix(int height, int width)
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
           cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

//feltolti a matrixot
void sierpinski(int sor, int oszlop, int meret)
{
    if(meret == 1)
    {
        matrix[sor][oszlop] = 1;
    }
    else
    {
        int fele = meret / 2;
        sierpinski(sor, oszlop, fele);
        sierpinski(sor + fele, oszlop - fele, fele);
        sierpinski(sor + fele, oszlop + fele, fele);
    }
}

// ^
void kirajzol_sierpinski(int height, int width)
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (matrix[i][j])
                cout << "^";
            else
                cout << " ";
        }
        cout << endl;
    }
}

int main()
{
    int n;
    cout << "Add meg a haromszog meretet (pl. 4): ";
    cin >> n;

    int height = pow(2, n);
    int width = 2 * height - 1;

    sierpinski(0, width / 2, height);
    //kiirMatrix(height, width);
    kirajzol_sierpinski(height, width);
    return 0;
}
