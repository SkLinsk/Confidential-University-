#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
using namespace std;

// 顺序查找函数
int linearSearch(const vector<int> &arr, int target, int &comparisonCount)
{
    comparisonCount = 0;
    for (size_t i = 0; i < arr.size(); ++i)
    {
        comparisonCount++;
        if (arr[i] == target)
        {
            return i;
        }
    }
    return -1; // 未找到
}

// 折半查找函数
int binarySearch(const vector<int> &arr, int target, int &comparisonCount)
{
    comparisonCount = 0;
    size_t left = 0, right = arr.size() - 1;
    while (left <= right)
    {
        size_t mid = left + (right - left) / 2;
        comparisonCount++;
        if (arr[mid] == target)
        {
            return mid;
        }
        else if (arr[mid] < target)
        {
            left = mid + 1;
        }
        else
        {
            right = mid - 1;
        }
    }
    return -1; // 未找到
}

int main()
{
    srand(static_cast<unsigned>(time(0))); // 设置随机数种子
    const size_t dataSize = 1000;
    const int numSearches = 100;
    vector<int> data(dataSize);

    // 生成随机数据
    for (size_t i = 0; i < dataSize; ++i)
    {
        data[i] = rand() % 10000; // 生成0到9999之间的随机数
    }

    // 对数据进行排序，以便使用折半查找
    sort(data.begin(), data.end());

    // 顺序查找统计
    int linearComparisonCountSum = 0;
    for (int i = 0; i < numSearches; ++i)
    {
        int target = rand() % 10000;
        int comparisonCount = 0;
        int index = linearSearch(data, target, comparisonCount);
        linearComparisonCountSum += comparisonCount;
    }
    double linearComparisonCountAvg = static_cast<double>(linearComparisonCountSum) / numSearches;

    // 折半查找统计
    int binaryComparisonCountSum = 0;
    for (int i = 0; i < numSearches; ++i)
    {
        int target = rand() % 10000;
        int comparisonCount = 0;
        int index = binarySearch(data, target, comparisonCount);
        binaryComparisonCountSum += comparisonCount;
    }
    double binaryComparisonCountAvg = static_cast<double>(binaryComparisonCountSum) / numSearches;

    // 输出结果
    cout << "linearComparisonCountAvg: " << linearComparisonCountAvg << endl;
    cout << "binaryComparisonCountAvg: " << binaryComparisonCountAvg << endl;

    return 0;
}