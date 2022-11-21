#include <iostream>
#include <time.h>
using namespace std;

/*
Quick Sort Algorithm (inplace sorting)
Best			Average				Worst
Ω(nlog(n))     Θ(nlog(n))  		   O(n^2)
APPLICATIONS: used when there is space constrain

Step 1 − Make any element as pivot
Step 2 − Partition the array on the basis of pivot
Step 3 − Apply quick sort on left partition recursively
Step 4 − Apply quick sort on right partition recursively
*/

int Partition(int arr[],int s,int e) {
	int pivot = arr[e];     // pick pivot as last element
	int pIndex = s;         // partition index
	for(int i=s; i<e; i++) {
		if(arr[i] < pivot) {
            swap(arr[i], arr[pIndex]);
			pIndex++;
		}
	}
    swap(arr[e], arr[pIndex]);
	return pIndex;
}

int partition_r(int arr[], int low, int high)
{
    // Generate a random number in between low .. high
    srand(time(NULL));
    int random = low + rand() % (high - low);
    // Swap A[random] with A[high]
    swap(arr[random], arr[high]);
    return Partition(arr, low, high);
}

void QuickSort(int arr[], int s, int e) { //start index, end index 
	if(s<e) {
		int p = Partition(arr, s, e);
		QuickSort(arr, s, p-1); //recursive QS call for left sort
		QuickSort(arr, p+1, e); //recursive QS call for right sort
	}
}

int main() {
    int n = 5;
	int arr[n] = {4,1,3,2,5};
	QuickSort(arr, 0, n-1);

	for(int i=0;i<n;i++){
		cout << arr[i] << " ";
	}
	return 0;
}
