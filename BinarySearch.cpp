#include <iostream>
using namespace std;

bool doExist(int num, int *arr, int len)
{
    int l = 0, r = len - 1, m = 0;
    while (l<=r)
    {
        m = (l + r) / 2;
        if (num > arr[m]) l = m + 1;
        else if (num < arr[m]) r = m - 1;
        else return true;
    }
    return false;
}

// 左右最值坐标问题类似

int main()
{
    int lst[] = { 1, 4, 6, 8, 10, 12, 15, 16, 18 }; // 任意有序数组
    int len = sizeof(lst)/sizeof(lst[0]);
    cout << doExist(6, lst, len) << endl;
    return 0;
}