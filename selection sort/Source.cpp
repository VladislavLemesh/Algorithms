#include <iostream>
using namespace std;

void selectionSort(int* arr, const int ARRAY_SIZE) {
	int indexMinKey;
	bool minKeyIsExist;

	for (int i = 0; i < ARRAY_SIZE; i++) {
		indexMinKey = i;
		minKeyIsExist = false;

		for (int j = i + 1; j < ARRAY_SIZE; j++) {
			if (arr[j] < arr[indexMinKey]) {
				indexMinKey = j;
				minKeyIsExist = true;
			}
		}

		if (minKeyIsExist) {
			swap(arr[i], arr[indexMinKey]);
		}
	}
}

int main() {
	const int ARRAY_SIZE = 15;
	int a[ARRAY_SIZE];

	for (int i = 0; i < ARRAY_SIZE; i++) {
		a[i] = rand() % 100;
		cout << a[i] << " ";
	}

	cout << endl;

	selectionSort(a, ARRAY_SIZE);

	for (int i = 0; i < ARRAY_SIZE; i++) {
		cout << a[i] << " ";
	}

	return 0;
}