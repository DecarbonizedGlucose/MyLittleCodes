# 排序算法

冒泡，插入，选择，快排，桶排，堆排，归并，计数，希尔

代码仓库：https://github.com/DecarbonizedGlucose/LittleCodes/

代码中所有的`swap`是`<algorithm>`中的`std::swap`

## 三傻排序（冒泡，插入，选择）

冒泡：最大数字逐个向后，从后向前生长。

选择：第一个已有序，在有序基础上，最小数空降。

插入：前面有序，最小数缓降。

```cpp
void bubbleSort(int* arr, int len)
{
	for (int end = len - 1; end > 0; --end) // 直观的末位有序
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
```
```cpp
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
```
```cpp
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
```

## 快速排序(QuickSort)

在数组中随机挑选一个基准，命名为key。利用双指针，把所有小于（or小于等于）key的数移到key左边，大于（or大于等于）key的数移到key右边，然后递归两侧，最终使数组有序。

写过很多遍了，没啥好说的，直接上代码

以第一个数为基准的Quicksort:

```cpp
void quickSort(int* array, int l, int r)
{
	if (l > r) return;
	int begin = l, end = r, key = l - 1;
	while (begin < end)
	{
        // 写成<=是为了应对同一元素出现多次的情况
		while (begin < end && array[begin] <= array[key]) 
			++begin;
		while (begin < end && array[end] >= array[key])
			--end;
		swap(array[begin], array[end]);
	}
	if (array[begin] < array[key]) swap(array[begin], array[key]);
	quickSort(array, l, begin - 1);
	quickSort(array, end + 1, r);
}
```

以中间位置元素为基准的二分Quicksort，可扩展性高：

```cpp
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
```

## 希尔排序(ShellSort)

高效的插入排序，但是不稳定。

去一个数gap，把数组分为gap组，在每一组内进行插入排序，即预排序。最终gap=1，此时整体已经“大致有序”，再进行插入排序。

如

```
	[1, 1, 4, 5, 1, 4, 1, 9, 1, 9, 8, 1, 0]
分组：1  2  3  1  2  3  1  2  3  1  2  3  1
gap=3，同一标号的为一组。
```

代码：

```cpp
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
                swap(arr[j], arr[j - gap]);
            }
        }
        gap /= 3;
    }
}
```

## 计数排序

特点在于新开辟空间存放数据。

步骤：

- 找出待排序的数组中最大和最小的元素

- 统计数组中每个值为i的元素出现的次数，存入数组C[i]

- 对所有的计数累加，求出数组长度（不要求传参）

- 反向填充目标数组：将每个元素i放在新数组的第C[i]项，每放一个元素就将C[i]减去1
