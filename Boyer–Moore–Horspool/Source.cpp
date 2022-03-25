/*����� ������� 6
����� ��������� � ������
*/
#include <iostream>
#include <string>
#include <Windows.h>

using namespace std;

void HorspoolMatch(string T, string P)
{
    int n = T.length();
    int m = P.length();
    int c;
    int Slide[255];
    for (int i = 0; i < 255; i++)
        Slide[i] = m;
    for (int i = 0; i < m - 1; i++)
    {
        c = P[i];
        if (c < 0)
        {
            Slide[-c] = m - 1 - i;
        }
        else
        {
            Slide[c] = m - 1 - i;
        }
    }
    cout << "������� ������: " << endl;
    for (int i = 0; i < m; i++)
    {
        cout << P[i] << "\t";
    }
    cout << endl;
    for (int i = 0; i < m; i++)
    {
        c = P[i];
        if (c < 0)
        {
            cout << Slide[-c] << "\t";
        }
        else
        {
            cout << Slide[c] << "\t";
        }
    }
    cout << endl;
    int i = m - 1;

    while (i <= (n - 1))
    {
        int k = 0;
        while (k <= m - 1 && P[m - 1 - k] == T[i - k])
        {
            k = k + 1;
        }

        if (k == m)
        {
            cout << "������ ������� � ������� " << i - m + 1 << endl;
            return;
        }

        else
        {
            c = T[i];
            if (c < 0)
            {
                cout << "�������� �� " << Slide[-c] << " �������" << endl;
                i = i + Slide[-c];
            }
            else
            {
                cout << "�������� �� " << Slide[c] << " �������" << endl;
                i = i + Slide[c];
            }
        }
    }
    cout << "������ �� �������" << endl;
    return;
}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    string T;
    string P;
    int pos;
    cout << "������� �����" << endl;
    cin >> T;
    cout << endl;
    cout << "������� ���������" << endl;
    cin >> P;
    cout << endl;
    cout << endl;
    HorspoolMatch(T, P);
}