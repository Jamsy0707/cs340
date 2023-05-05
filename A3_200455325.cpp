// James Sieben 200455325
// g++ assign3jls273.cpp -o run
// To execute the program, simply enter a value for N and then for K

#include <iostream>
#include <cstdlib> 
#include <ctime>
#include <chrono>
using namespace std;

// Introduce the functions
void InsertSort (int arr[], int low, int n);
void MergeSort (int arr[], int begin, int end);
void Merge (int array[], int const left, int const mid, int const right);
void QuickSort (int arr[], int low, int high);
int Partition (int arr[], int low, int high);
void Swap(int* a, int* b);
void QuickInsertSort (int arr[], int low, int high, int K);
void PrintArray (int arr[], int N);

// Timer is used to time the functions
class Timer
{
private:
	// Type aliases to make accessing nested type easier
	using clock_type = std::chrono::steady_clock;
	using second_type = std::chrono::duration<double, std::ratio<1> >;

	std::chrono::time_point<clock_type> m_beg { clock_type::now() };

public:
	void reset()
	{
		m_beg = clock_type::now();
	}

	double elapsed() const
	{
		return std::chrono::duration_cast<second_type>(clock_type::now() - m_beg).count();
	}
};

int main() 
{
	// Determine values of N and K
    int N, K;
	cout << "What is N? ";
	cin >> N;
	cout << endl << "What is K? ";
	cin >> K;

	if (K > N)
		cout << "Warning! Your K value should be smaller than N." << endl;

	srand((unsigned)time(0)); 

	// Declare arrays
	int insArr[N];
	int merArr[N];
	int quiArr[N];
	int quiInsArr[N];

	// Give arrays all the same random values for consistent testing
	for (int i = 0; i < N; i++)
		insArr[i] = rand() % 1000;

	for (int i = 0; i < N; i++)
		merArr[i] = insArr[i];

	for (int i = 0; i < N; i++)
		quiArr[i] = insArr[i];

	for (int i = 0; i < N; i++)
		quiInsArr[i] = insArr[i];

	// Run and print each sort individually with corresponding time
	cout << endl << "Insert Sort:" << endl;
	Timer a;
	InsertSort(insArr, 0, N);
	cout << "Run time: " << a.elapsed() << " seconds\n";
    PrintArray(insArr, N);

	cout << endl << "Merge Sort:" << endl;
	Timer b;
	MergeSort(merArr, 0, N-1);
	cout << "Run time: " << b.elapsed() << " seconds\n";
    PrintArray(merArr, N);

	cout << endl << "Quick Sort:" << endl;
	Timer c;
	QuickSort(quiArr, 0, N-1);
	cout << "Run time: " << c.elapsed() << " seconds\n";
    PrintArray(quiArr, N);

	cout << endl << "Hybrid Quick Sort:" << endl;
	Timer d;
	QuickInsertSort(quiInsArr, 0, N-1, K);
	cout << "Run time: " << d.elapsed() << " seconds\n";
    PrintArray(quiInsArr, N);

	cout << endl << endl;

	return 0;
}

void InsertSort (int arr[], int low, int n)
{
	int key, j;
    for (int i = low+1; i < n+1; i++)
    {
        key = arr[i];
        j = i;

		// Move elements greater than key to one position forward
        while (j >= low && arr[j-1] > key)
        {
            arr[j] = arr[j-1];
            j -= 1;
        }
        arr[j] = key;
    }
}

void MergeSort (int arr[], int begin, int end)
{
	if (begin >= end)
    	return; // Returns recursively
  
    auto mid = begin + (end - begin) / 2;
    MergeSort(arr, begin, mid);
    MergeSort(arr, mid + 1, end);
    Merge(arr, begin, mid, end);
}

// Used to merge two subarrays together
void Merge(int array[], int const left, int const mid, int const right)
{
    auto const subArrayOne = mid - left + 1;
    auto const subArrayTwo = right - mid;

	// Create temp arrays
    auto *leftArray = new int[subArrayOne],
         *rightArray = new int[subArrayTwo];

	// Copy old array to new arrays
    for (auto i = 0; i < subArrayOne; i++)
        leftArray[i] = array[left + i];
    for (auto j = 0; j < subArrayTwo; j++)
        rightArray[j] = array[mid + 1 + j];
  
    auto indexOfSubArrayOne = 0, // Indexes of sub arrays to start
        indexOfSubArrayTwo = 0;
    int indexOfMergedArray = left; // Index of merged array to start

	// Merges the sub arrays back together
    while (indexOfSubArrayOne < subArrayOne && indexOfSubArrayTwo < subArrayTwo) {
        if (leftArray[indexOfSubArrayOne] <= rightArray[indexOfSubArrayTwo]) {
            array[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
            indexOfSubArrayOne++;
        }
        else {
            array[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
            indexOfSubArrayTwo++;
        }
        indexOfMergedArray++;
    }

	// Copy remaining elements of left sub array
    while (indexOfSubArrayOne < subArrayOne) {
        array[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
        indexOfSubArrayOne++;
        indexOfMergedArray++;
    }

	// Copy remaining elemens of right sub array
    while (indexOfSubArrayTwo < subArrayTwo) {
        array[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
        indexOfSubArrayTwo++;
        indexOfMergedArray++;
    }
}

void QuickSort (int arr[], int low, int high)
{
	if (low < high)
    {
		// pi is the partitioning index
        int pi = Partition(arr, low, high);

		// Sort the elements before the partition
        QuickSort(arr, low, pi - 1);
		// Sort the elements after the partition
        QuickSort(arr, pi + 1, high);
    }
}

// Used with quicksort to sort elements into a group smaller than
// the partition and a group bigger than the partition
int Partition (int arr[], int low, int high)
{
    int pivot = arr[high]; 
    int i = (low - 1); 
 
    for (int j = low; j <= high - 1; j++)
    {
		// When the current element is smaller than the pivot,
		// increment the index of the smaller element
        if (arr[j] < pivot)
        {
            i++;
            Swap(&arr[i], &arr[j]);
        }
    }
    Swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

// Used with quicksort to swap two elements
void Swap(int* a, int* b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

// Similar to quicksort but when a subarray is smaller than or equal
// to K it switches to insert sort
void QuickInsertSort (int arr[], int low, int high, int K)
{
	while (low < high)
	{
		// If subarray is <= K use insert
		if (high-low+1 <= K)
		{
			InsertSort(arr, low, high);
			break;
		}
		
		else
    	{
			// Create a partition for quicksort
        	int pi = Partition(arr, low, high);

			// Sort the left side of the partition recursively
			if (pi-low < high-pi)
			{
       			QuickInsertSort(arr, low, pi - 1, K);
        		low = pi + 1;
			}
			// Sort the right side of the partition recursively
			else
			{
				QuickInsertSort(arr, pi + 1, high, K);
				high = pi - 1;
			}
    	}
	}
}

// Used for printing arrays
void PrintArray(int arr[], int N)
{
    int i;
    for (i = 0; i < N; i++)
        cout << arr[i] << " ";
    cout << endl;
}