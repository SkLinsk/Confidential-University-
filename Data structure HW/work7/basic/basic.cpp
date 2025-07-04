#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>

// 结构体用于记录比较和移动次数
struct SortStatistics
{
    int comparisons = 0;
    int moves = 0;
};

// 直接插入排序函数
void insertionSort(std::vector<int> &arr, SortStatistics &stats)
{
    for (size_t i = 1; i < arr.size(); ++i)
    {
        int key = arr[i];
        int j = i - 1;
        stats.moves++; // 移动key
        while (j >= 0 && arr[j] > key)
        {
            stats.comparisons++;
            arr[j + 1] = arr[j];
            j--;
            stats.moves++; // 移动元素
        }
        arr[j + 1] = key;
        stats.moves++; // 移动key到位
    }
}

// 快速排序分区函数
int partition(std::vector<int> &arr, int left, int right, SortStatistics &stats)
{
    int pivot = arr[right];
    int i = left - 1;
    for (int j = left; j < right; ++j)
    {
        stats.comparisons++;
        if (arr[j] <= pivot)
        {
            ++i;
            std::swap(arr[i], arr[j]);
            stats.moves += 2; // 交换两个元素
        }
    }
    std::swap(arr[i + 1], arr[right]);
    stats.moves += 2; // 交换pivot
    return i + 1;
}

// 快速排序函数
void quickSort(std::vector<int> &arr, int left, int right, SortStatistics &stats)
{
    if (left < right)
    {
        int pivotIndex = partition(arr, left, right, stats);
        quickSort(arr, left, pivotIndex - 1, stats);
        quickSort(arr, pivotIndex + 1, right, stats);
    }
}

// 对外暴露的快速排序接口
void quickSortWrapper(std::vector<int> &arr, SortStatistics &stats)
{
    quickSort(arr, 0, arr.size() - 1, stats);
}

// 希尔排序函数
void shellSort(std::vector<int> &arr, SortStatistics &stats)
{
    for (size_t gap = arr.size() / 2; gap > 0; gap /= 2)
    {
        for (size_t i = gap; i < arr.size(); ++i)
        {
            int temp = arr[i];
            int j;
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap)
            {
                stats.comparisons++;
                arr[j] = arr[j - gap];
                stats.moves++; // 移动元素
            }
            arr[j] = temp;
            stats.moves++; // 移动temp到位（如果j != i，则这是额外的移动；如果j == i，则不增加总移动次数，但为了简化代码，我们仍然增加它）
        }
    }
}

// 直接选择排序函数
void selectionSort(std::vector<int> &arr, SortStatistics &stats)
{
    for (size_t i = 0; i < arr.size() - 1; ++i)
    {
        int minIndex = i;
        for (size_t j = i + 1; j < arr.size(); ++j)
        {
            stats.comparisons++;
            if (arr[j] < arr[minIndex])
            {
                minIndex = j;
            }
        }
        if (minIndex != i)
        {
            std::swap(arr[i], arr[minIndex]);
            stats.moves += 2; // 交换两个元素
        }
    }
}

// 堆排序的辅助函数：堆化
void heapify(std::vector<int> &arr, int n, int i, SortStatistics &stats)
{
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest])
    {
        largest = left;
        stats.comparisons++;
    }

    if (right < n && arr[right] > arr[largest])
    {
        largest = right;
        stats.comparisons++;
    }

    if (largest != i)
    {
        std::swap(arr[i], arr[largest]);
        stats.moves += 2; // 交换两个元素
        heapify(arr, n, largest, stats);
    }
}

// 堆排序函数
void heapSort(std::vector<int> &arr, SortStatistics &stats)
{
    int n = arr.size();

    // 建立最大堆
    for (int i = n / 2 - 1; i >= 0; i--)
    {
        heapify(arr, n, i, stats);
    }

    // 一个个从堆顶取出元素
    for (int i = n - 1; i > 0; i--)
    {
        std::swap(arr[0], arr[i]);
        stats.moves += 2; // 交换两个元素
        heapify(arr, i, 0, stats);
    }
}

// 归并排序的辅助函数：合并两个有序子数组
void merge(std::vector<int> &arr, int left, int mid, int right, SortStatistics &stats)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;

    std::vector<int> L(n1), R(n2);

    for (int i = 0; i < n1; ++i)
    {
        L[i] = arr[left + i];
    }
    for (int j = 0; j < n2; ++j)
    {
        R[j] = arr[mid + 1 + j];
    }

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2)
    {
        stats.comparisons++;
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            ++i;
        }
        else
        {
            arr[k] = R[j];
            ++j;
        }
        ++k;
        stats.moves++; // 移动元素到arr[k]
    }

    while (i < n1)
    {
        arr[k] = L[i];
        ++i;
        ++k;
        stats.moves++; // 移动元素到arr[k]
    }

    while (j < n2)
    {
        arr[k] = R[j];
        ++j;
        ++k;
        stats.moves++; // 移动元素到arr[k]
    }
}

// 归并排序函数
void mergeSort(std::vector<int> &arr, int left, int right, SortStatistics &stats)
{
    if (left < right)
    {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid, stats);
        mergeSort(arr, mid + 1, right, stats);
        merge(arr, left, mid, right, stats);
    }
}

// 对外暴露的归并排序接口
void mergeSortWrapper(std::vector<int> &arr, SortStatistics &stats)
{
    mergeSort(arr, 0, arr.size() - 1, stats);
}

int main()
{
    srand(static_cast<unsigned>(time(0)));
    const size_t dataSize = 1000;
    std::vector<int> data(dataSize);

    // 生成随机数据
    for (size_t i = 0; i < dataSize; ++i)
    {
        data[i] = rand() % 10000;
    }

    // 直接插入排序
    SortStatistics insertionStats;
    std::vector<int> insertionData = data;
    insertionSort(insertionData, insertionStats);
    std::cout << "insertionStats.comparisons = " << insertionStats.comparisons << ", insertionStats.moves = " << insertionStats.moves << std::endl;

    // 快速排序
    SortStatistics quickStats;
    std::vector<int> quickData = data;
    quickSortWrapper(quickData, quickStats);
    std::cout << "quickStats.comparisons = " << quickStats.comparisons << ", quickStats.moves = " << quickStats.moves << std::endl;

    // 希尔排序
    SortStatistics shellStats;
    std::vector<int> shellData = data;
    shellSort(shellData, shellStats);
    std::cout << "shellStats.comparisons = " << shellStats.comparisons << ", shellStats.moves = " << shellStats.moves << std::endl;

    // 直接选择排序
    SortStatistics selectionStats;
    std::vector<int> selectionData = data;
    selectionSort(selectionData, selectionStats);
    std::cout << "selectionStats.comparisons = " << selectionStats.comparisons << ", selectionStats.moves = " << selectionStats.moves << std::endl;

    // 堆排序
    SortStatistics heapStats;
    std::vector<int> heapData = data;
    heapSort(heapData, heapStats);
    std::cout << "heapStats.comparisons = " << heapStats.comparisons << ", heapStats.moves = " << heapStats.moves << std::endl;

    // 归并排序
    SortStatistics mergeStats;
    std::vector<int> mergeData = data;
    mergeSortWrapper(mergeData, mergeStats);
    std::cout << "mergeStats.comparisons = " << mergeStats.comparisons << ", mergeStats.moves = " << mergeStats.moves << std::endl;

    return 0;
}