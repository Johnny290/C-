// Binary searching / Bubble sort
#include <iostream>
#include <chrono>
#include <ctime>
using namespace std;

void fillA(int* pole, int sz)
{
	for (int i = 0; i < sz; i++)
	{
		pole[i] = -50 + rand() % 101;
	}
}

void writeA(int* pole, int sz)
{
	for (int i = 0; i < sz; i++)
	{
		cout << pole[i] << " ";
	}

	cout << endl;
}

void swap(int* p1, int* p2)
{
	int tmp = *p1;
	*p1 = *p2;
	*p2 = tmp;
}

void bubbleSort(int* pole, int sz)
{
	for (int i = 0; i < sz - 1; i++)
	{
		if (pole[i] > pole[i + 1])
		{
			swap(pole[i], pole[i + 1]);
		}

		for (int j = sz - 1; j > 0; j--)
		{
			if (pole[j] < pole[j - 1])
			{
				swap(pole[j], pole[j - 1]);
			}
		}
	}
}

int binarySearching(int *pole, int left, int right, int num)
{
	int middle;
	while (left <= right)
	{
		middle = (left + right) / 2;

		if (pole[middle] == num)
		{
			return middle;
		}
		else
		{
			if (num < pole[middle])
			{
				right = middle - 1;
			}
			else
			{
				left = middle + 1;
			}
		}
	}
	return -1;
}




int main3()
{
	time_t tim = chrono::system_clock::to_time_t(chrono::system_clock::now());
	srand((unsigned int)tim);

	int sz = 100;
	int* pole = new int[sz];

	fillA(pole, sz);
	writeA(pole, sz);

	bubbleSort(pole, sz);
	writeA(pole, sz);

	int num = -50 + rand() % 101;
	int index = binarySearching(pole, 0, sz - 1, num);

	if (index != -1)
	{
		cout << "Desired number is: " << num << " on index " << index << "." << endl;
	}
	else
	{
		cout << "Number: "<< num << " Not found" << endl;
	}

	delete[] pole;

	return 0;
}
