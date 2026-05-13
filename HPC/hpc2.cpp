#include <iostream>
#include <vector>
#include <omp.h>
#include <ctime>

using namespace std;

// Sequential Bubble Sort
void bubbleSort(vector<int>& arr)
{
    int n = arr.size();

    for(int i = 0; i < n - 1; i++)
    {
        for(int j = 0; j < n - i - 1; j++)
        {
            if(arr[j] > arr[j + 1])
            {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

// Parallel Bubble Sort
void parallelBubbleSort(vector<int>& arr)
{
    int n = arr.size();

    for(int i = 0; i < n; i++)
    {
        int first = i % 2;

        #pragma omp parallel for
        for(int j = first; j < n - 1; j += 2)
        {
            if(arr[j] > arr[j + 1])
            {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

// Merge Function
void merge(vector<int>& arr, int left, int mid, int right)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<int> L(n1), R(n2);

    for(int i = 0; i < n1; i++)
        L[i] = arr[left + i];

    for(int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0;
    int j = 0;
    int k = left;

    while(i < n1 && j < n2)
    {
        if(L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }

        k++;
    }

    while(i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }

    while(j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// Sequential Merge Sort
void mergeSort(vector<int>& arr, int left, int right)
{
    if(left < right)
    {
        int mid = (left + right) / 2;

        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        merge(arr, left, mid, right);
    }
}

// Parallel Merge Sort
void parallelMergeSort(vector<int>& arr, int left, int right)
{
    if(left < right)
    {
        int mid = (left + right) / 2;

        #pragma omp parallel sections
        {
            #pragma omp section
            {
                parallelMergeSort(arr, left, mid);
            }

            #pragma omp section
            {
                parallelMergeSort(arr, mid + 1, right);
            }
        }

        merge(arr, left, mid, right);
    }
}

// Print Array
void printArray(vector<int>& arr)
{
    cout << "[";

    for(int i = 0; i < arr.size(); i++)
    {
        cout << arr[i];

        if(i != arr.size() - 1)
        {
            cout << ", ";
        }
    }

    cout << "]" << endl;
}

int main()
{
    int n = 100;

    vector<int> arr;

    cout << "Total number of elements: "
         << n << endl;

    cout << "Storing elements in descending order...\n";

    for(int i = n; i >= 1; i--)
    {
        arr.push_back(i);
    }

    cout << "\nActual list:\n";
    printArray(arr);

    // Sequential Bubble Sort
    vector<int> bubbleArr = arr;

    cout << "\nRunning Sequential Bubble Sort...\n";

    clock_t start = clock();

    bubbleSort(bubbleArr);

    clock_t end = clock();

    cout << "Sorted list (Bubble Sort):\n";
    printArray(bubbleArr);

    cout << "Execution Time: "
         << (double)(end - start) / CLOCKS_PER_SEC
         << " seconds\n";

    // Parallel Bubble Sort
    vector<int> parallelBubbleArr = arr;

    cout << "\nRunning Parallel Bubble Sort...\n";

    start = clock();

    parallelBubbleSort(parallelBubbleArr);

    end = clock();

    cout << "Sorted list (Parallel Bubble Sort):\n";
    printArray(parallelBubbleArr);

    cout << "Execution Time: "
         << (double)(end - start) / CLOCKS_PER_SEC
         << " seconds\n";

    // Sequential Merge Sort
    vector<int> mergeArr = arr;

    cout << "\nRunning Sequential Merge Sort...\n";

    start = clock();

    mergeSort(mergeArr, 0, n - 1);

    end = clock();

    cout << "Sorted list (Merge Sort):\n";
    printArray(mergeArr);

    cout << "Execution Time: "
         << (double)(end - start) / CLOCKS_PER_SEC
         << " seconds\n";

    // Parallel Merge Sort
    vector<int> parallelMergeArr = arr;

    cout << "\nRunning Parallel Merge Sort...\n";

    start = clock();

    parallelMergeSort(parallelMergeArr, 0, n - 1);

    end = clock();

    cout << "Sorted list (Parallel Merge Sort):\n";
    printArray(parallelMergeArr);

    cout << "Execution Time: "
         << (double)(end - start) / CLOCKS_PER_SEC
         << " seconds\n";

    return 0;
}
