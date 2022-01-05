//Quick sort

#include <iostream>
#include <ctime>
#include <chrono>
#include <cstdlib>
#include <cstdio>
using namespace std;


void swap(int *p1, int *p2)
{
	int tmp = *p1;
	*p1 = *p2;
	*p2 = tmp;
}



int devide(int *pole, int left, int right)
{
	int pivot = pole[left];
	int i = left;
	int j = right;

	while (i < j)
	{
		do
		{
			i++;
		} while (pole[i] >= pivot);

		do
		{
			j--;
		} while (pole[j] < pivot);

		if (i < j)
		{
			swap(pole[i], pole[j]);
		}
		
	}

	swap(pole[left], pole[j]);

	return j;
}

void quickSort(int* pole, int left, int right)
{
	int j;
	if (left < right)
	{
		j = devide(pole, left, right);
		quickSort(pole, left, j);
		quickSort(pole, j + 1, right);
	}
}

void fillArray(int* pole, unsigned int sz)
{
	for (unsigned int i = 0; i < sz; i++)
	{
		pole[i] = -50 + rand() % 101;
	}
}

void printA(int* pole, int sz)
{
	for(int i = 0; i < sz; i++)
	{
		cout << pole[i] << " ";
	}
}

int main()
{
	std::time_t tim = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	srand((int)tim);

	int sz = 100;
	int *pole = new int[sz];
	fillArray(pole, sz);
	printA(pole, sz);

	auto start = chrono::system_clock::now();
	quickSort(pole, 0, sz);
	auto end = chrono::system_clock::now();
	cout << endl;
	printA(pole, sz);

	chrono::duration<double, micro> dDuration = end - start;

	cout << endl;
	cout << "Time elapsed: " << dDuration.count() << endl;

	return 0;
}
