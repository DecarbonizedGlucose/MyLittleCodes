#include <iostream>
using namespace std;

int arr[] = { 1, 5, 7, 9, 3, 5, 10, 20, 25, 19, 17, 15, 2, 10, 6, 13, 17, 27, 23 };
int length = sizeof(arr) / sizeof(arr[0]);

void swap(int& a, int& b)
{
	int temp = a;
	a = b;
	b = temp;
}

void quickSort(int *a, int l, int r) // l = 1, r = len - 1
{
	int begin = l, end = r, key = arr[l - 1];
	while (begin < end)
	{
		for (; a[end] >= key && begin < end; --end);
		for (; a[begin <= key] && begin < end; ++begin);
		swap(a[begin], a[end]);
	}
	if (key > a[end]) swap(a[l - 1], a[end]);
	if (r - end) quickSort(a, end + 1, r);
	if (begin - l)quickSort(a, l, end - 1);
}

int main()
{
	//quickSort(arr, 1, length - 1);
	for (int i : arr) cout << i << " ";
	cout << endl;
	return 0;
}