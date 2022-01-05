// Bubble sort

#include <iostream>
#include <ctime>
#include <chrono>
using namespace std;

void FillArray(int *pole, int sz)
{
	for (int i = 0; i < sz; i++)
	{
		pole[i] = -50 + rand() % 101;
	}
}

void swap(int* p1, int* p2)
{
	int tmp = *p1;
	*p1 = *p2;
	*p2 = tmp;
}

void BubbleSort(int* pole, int sz)
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

void printA(int* pole, int sz)
{
	for (int i = 0; i < sz; i++)
	{
		cout << pole[i] << " ";
	}

	cout << endl;
}

int main()
{
	time_t tim = chrono::system_clock::to_time_t(chrono::system_clock::now());
	srand((unsigned int)tim);

	int sz = 10000;
	int* pole = new int[sz];

	FillArray(pole, sz);
	printA(pole, sz);

	BubbleSort(pole, sz);
	printA(pole, sz);

	return 0;
}
