#include <iostream>
using namespace std;

int arr[] = { 18, 9, 7, 15, 3, 17, 16, 4, 20, 11, 19, 5 };
int len = sizeof(arr) / sizeof(arr[0]);

void swap(int& a, int& b)
{
	int temp = a;
	a = b;
	b = temp;
}

void newBubble(int* arr, int len)
{
	for (int end = len - 1; end > 0; --end)
	{
		for (int i = 0; i < end; ++i)
		{
			if (arr[i] > arr[i + 1])
			{
				swap(arr[i], arr[i + 1]);
			}
		}
	}
}

void oldBubble(int* arr, int len)
{
	for (int i = 0; i < len; i++)
	{
		for (int j = 0; j < len - 1; j++)
		{
			if (arr[j] > arr[j + 1])
			{
				swap(arr[j], arr[j + 1]);
			}
		}
	}
}

void selectionsort(int* arr, int len)
{
	int minIndex;
	for (int i = 0; i < len - 1; ++i)
	{
		minIndex = i;
		for (int j = i + 1; j < len; ++j)
		{
			if (arr[j] < arr[minIndex])
			{
				minIndex = j;
			}
		}
		swap(arr[i], arr[minIndex]);
	}
}

void insertionsort(int* arr, int len)
{
	for (int i = 1; i < len; ++i)
	{
		for (int j = i - 1; j >= 0 && arr[j] > arr[j + 1]; --j)
		{
			swap(arr[j], arr[j + 1]);
		}
	}
}

int main()
{
	for (int i : arr)
	{
		cout << i << " ";
	}
	cout << endl;

	insertionsort(arr, len);

	for (int i : arr)
	{
		cout << i << " ";
	}
	cout << endl;
	return 0;
}