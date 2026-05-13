#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <omp.h>

using namespace std;

int main()
{
    int n;

    cout << "Enter the number of elements in the list: ";
    cin >> n;

    vector<int> arr(n);

    srand(time(0));

    // Generate Random Numbers
    for(int i = 0; i < n; i++)
    {
        arr[i] = rand() % 100 + 1;
    }

    cout << "\nGenerated list of "
         << n
         << " elements:\n";

    for(int i = 0; i < n; i++)
    {
        cout << arr[i] << " ";
    }

    cout << endl;

    int min_val = arr[0];
    int max_val = arr[0];
    int sum = 0;
    double avg;

    // Min Operation
    clock_t start = clock();

    #pragma omp parallel for reduction(min:min_val)
    for(int i = 0; i < n; i++)
    {
        if(arr[i] < min_val)
        {
            min_val = arr[i];
        }
    }

    clock_t end = clock();

    cout << "\nPerforming Min operation using Parallel Reduction...\n";

    cout << "Min result: "
         << min_val << endl;

    cout << "Execution Time: "
         << (double)(end - start) / CLOCKS_PER_SEC
         << " seconds\n";

    // Max Operation
    start = clock();

    #pragma omp parallel for reduction(max:max_val)
    for(int i = 0; i < n; i++)
    {
        if(arr[i] > max_val)
        {
            max_val = arr[i];
        }
    }

    end = clock();

    cout << "\nPerforming Max operation using Parallel Reduction...\n";

    cout << "Max result: "
         << max_val << endl;

    cout << "Execution Time: "
         << (double)(end - start) / CLOCKS_PER_SEC
         << " seconds\n";

    // Sum Operation
    start = clock();

    #pragma omp parallel for reduction(+:sum)
    for(int i = 0; i < n; i++)
    {
        sum += arr[i];
    }

    end = clock();

    cout << "\nPerforming Sum operation using Parallel Reduction...\n";

    cout << "Sum result: "
         << sum << endl;

    cout << "Execution Time: "
         << (double)(end - start) / CLOCKS_PER_SEC
         << " seconds\n";

    // Average Operation
    start = clock();

    avg = (double)sum / n;

    end = clock();

    cout << "\nPerforming Average operation using Parallel Reduction...\n";

    cout << "Average result: "
         << avg << endl;

    cout << "Execution Time: "
         << (double)(end - start) / CLOCKS_PER_SEC
         << " seconds\n";

    return 0;
}
