#include <iostream>
#include <omp.h>
#include <ctime>
#include <cstdlib>

using namespace std;

void sequentialBubble(int arr[], int n)
{
    for (int i = 0; i < n - 1; ++i)
    {
        for (int j = 0; j < n - i - 1; ++j)
        {
            if (arr[j] > arr[j + 1])
            {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

void parallelBubble(int arr[], int n)
{
#pragma omp parallel for shared(arr)
    for (int i = 0; i < n - 1; ++i)
    {
        // Each thread sorts a segment of the array
        for (int j = i % 2; j < n - 1; j += 2)
        {
            if (arr[j] > arr[j + 1])
            {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

void generateRandomArray(int arr[], int n)
{
    srand(time(NULL));
    for (int i = 0; i < n; i++)
    {
        arr[i] = rand() % 10000;
    }
}

void displayArray(int arr[], int n)
{
    for (int i = 0; i < n; ++i)
    {
        cout << arr[i] << " ";
    }

    cout << endl;
}

int main()
{
    const int size = 10000;
    int arr[size];

    // Generate random array
    generateRandomArray(arr, size);

    // Perform sequential bubble sort and measure performance
    clock_t startTime = clock();
    sequentialBubble(arr, size);
    clock_t endTime = clock();
    cout << "Sequential Bubble Sort Performance: " << double(endTime - startTime) / CLOCKS_PER_SEC << " seconds" << endl;

    // Generate random array again for parallel bubble sort
    generateRandomArray(arr, size);

    // Perform parallel bubble sort and measure performance
    startTime = clock();
    parallelBubble(arr, size);
    endTime = clock();
    cout << "Parallel Bubble Sort Performance: " << double(endTime - startTime) / CLOCKS_PER_SEC << " seconds" << endl;

    return 0;
}
