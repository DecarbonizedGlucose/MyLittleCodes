#include <iostream>
#include <algorithm> // std::swap(a, b)
using namespace std;

int arr[] = { 1, 5, 7, 9, 3, 5, 10, 20, 25, 19, 17, 15, 2, 10, 6, 13, 17, 27, 23 };
int length = sizeof(arr) / sizeof(arr[0]);

void quickSort(int* array, int l, int r)
{
	if (l > r) return;
	int begin = l, end = r, key = l - 1;
	while (begin < end)
	{
		while (begin < end && array[begin] <= array[key]) // 写成<=是为了应对同一元素出现多次的情况
			++begin;
		while (begin < end && array[end] >= array[key])
			--end;
		swap(array[begin], array[end]);
	}
	if (array[begin] < array[key]) swap(array[begin], array[key]);
	quickSort(array, l, begin - 1);
	quickSort(array, end + 1, r);
}

void qsort(int *arr, int l, int r) // 二分快排
{
	if (l > r) return;

	int begin = l, end = r;
	int mid = arr[(l + r) / 2];
	while (begin <= end)
	{
		while (arr[begin] < mid) ++begin;
		while (arr[end] > mid) --end;
		if (begin <= end)
		{
			swap(arr[begin], arr[end]);
			++begin, --end;
		}
	}
	qsort(arr, l, end);
	qsort(arr, begin, r);
}

//希尔排序
void shellSort(int *arr, int n)
{
    int gap = 1;
    while (gap < n / 3)
    {
        gap = 3 * gap + 1;
    }
    while (gap >= 1)
    {
        for (int i = gap; i < n; i++)
        {
            for (int j = i; j >= gap && arr[j] < arr[j - gap]; j -= gap)
            {
                std::swap(arr[j], arr[j - gap]);
            }
        }
        gap /= 3;
    }
}

int main()
{
	quickSort(arr, 1, length - 1);
	for (int i : arr) cout << i << " ";
	cout << endl;
	return 0;
}