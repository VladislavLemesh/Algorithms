#include <iostream>
#include <chrono>
#include <time.h>
#include <stack>

using namespace std;
using namespace chrono;

void quick_sort(int* arr, int n, float& s, float& c, float& d)
{
    int base, left, right, i, j;
    stack<int> steck;
    bool h = false;
    c = 0, s = 0;
    auto t3 = high_resolution_clock::now();
    steck.push(n - 1);
    steck.push(0);
    do {
        left = steck.top();
        steck.pop();
        right = steck.top();
        steck.pop();
        c++;
        if (((right - left) == 1) && (arr[left] > arr[right]))
        {
            s++;
            swap(arr[left], arr[right]);
        }
        else {
            base = arr[(left + right) / 2];
            i = left;
            j = right;
            do {
                while ((base > arr[i]))
                {
                    ++i;
                    c++;
                }
                while (arr[j] > base)
                {
                    --j;
                    c++;
                }
                if (i <= j)
                {
                    if ((arr[i] == arr[j]) && (i != j))
                    {
                        h = true;
                    }
                    s++;
                    swap(arr[i++], arr[j--]);
                }
            } while (i <= j);
        }
        if (left < j) {
            steck.push(j);
            steck.push(left);
        }
        if (i < right) {
            steck.push(right);
            steck.push(i);
        }
    } while (!(steck.empty()));
    auto t4 = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(t4 - t3).count();
    if (h)
    {
        cout << "быстрая сортировка неустойчива";
    }
    cout << endl;
    cout << "количество сравнений: " << c;
    cout << endl;
    cout << "количество перестановок: " << s;
    cout << endl;
    cout << "время работы алгоритма: " << duration << " микросекунд" << endl;
    d = duration;
}

int main()
{
    setlocale(LC_ALL, "rus");
    const int N = 100;
    int b[N];
    float s, c, d, sr2 = 0, cr2 = 0, dr2 = 0;
    srand(time(NULL));
    for (int k = 0; k < 50; k++)
    {
        for (int i = 0; i < N; i++)
        {
            b[i] = rand() % 10;
        }
        cout << "быстрая сортировка:" << endl;
        cout << "исходный массив: " << endl;
        for (int j = 0; j < N; j++)
        {
            cout << b[j] << " ";
        }
        cout << endl;
        quick_sort(b, N, s, c, d);
        cout << "отсортированный массив: " << endl;
        for (int i = 0; i < N; i++)
        {
            cout << b[i] << " ";
        }
        cout << endl << endl;
        sr2 = sr2 + s;
        cr2 = cr2 + c;
        dr2 = dr2 + d;
    }
    sr2 = sr2 / 50;
    cr2 = cr2 / 50;
    dr2 = dr2 / 50;
    cout << endl;
    cout << "среднее количество перестановок в быстрой сортировке = " << sr2 << endl;
    cout << "среднее количество сравнений в быстрой сортировке = " << cr2 << endl;
    cout << "среднее время работы быстрой сортировки = " << dr2 << " микросекунд" << endl;
}