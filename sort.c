#include <time.h>
#include <stdlib.h>
#include <stdio.h> 
#include <string.h>

int extraMemoryAllocated;

//this function is used in order to swap the values in the heap
void swap(int *a, int *b) 
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

void heapify(int arr[], int n, int i)
{
	//establishes largest value in the tree
	int largest = i;

//how we find left child from root
	int leftChild = 2 * i + 1;

//how we find right child from root
	int rightChild = 2 * i + 2;

//sets the left child as the larger number
	if(leftChild < n && arr[leftChild] > arr[largest]){
		largest = leftChild;
	}

//if right child is in the array and larger than the value set to largest
	if(rightChild < n && arr[rightChild] > arr [largest]){
		largest = rightChild;
	}

//if largest is not equal to i, we swap largest and i so that i is set to the largest value
	if(largest != i){
		swap(&arr[largest], &arr[i]);
		heapify(arr, n, largest);
	}
		
}
// implements heap sort
// extraMemoryAllocated counts bytes of memory allocated
void heapSort(int arr[], int n)
{
	int i;
	//(n/2)-1 is the formula for the last non leaf node
for(i = n/2-1; i >= 0; i--)
{
	heapify(arr, n, i);
}
for (int i = n - 1; i >= 0; i--) {
 
        swap(&arr[0], &arr[i]);
 
       
        heapify(arr, i, 0);
    }

}

void merge(int pData[], int l, int m, int r)
{
int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;
  //create space for the 2 arrays
    int* L = (int*)malloc(n1 * sizeof(int));
    int* R = (int*)malloc(n2 * sizeof(int));
    extraMemoryAllocated += n1 * sizeof(int) + n2 * sizeof(int);
    for (i = 0; i < n1; i++) {
        L[i] = pData[l + i];
    }
    for (j = 0; j < n2; j++) {
        R[j] = pData[m + 1 + j];
    }
    i = 0;
    j = 0;
    k = l;
  //iterates through left and right arrays
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            pData[k] = L[i];
            i++;
        }
        else {
            pData[k] = R[j];
            j++;
        }
        k++;
    }
  //copies elements from left into new merged array
    while (i < n1) {
        pData[k] = L[i];
        i++;
        k++;
    }
  //copies elements from right into new merged array
    while (j < n2) {
        pData[k] = R[j];
        j++;
        k++;
    }
    free(L);
    free(R);
}

void mergeSortHelper(int pData[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSortHelper(pData, l, m);
        mergeSortHelper(pData, m + 1, r);
        merge(pData, l, m, r);
    }
}

// implement merge sort
// extraMemoryAllocated counts bytes of extra memory allocated
void mergeSort(int pData[], int l, int r)
{
	extraMemoryAllocated = 0;
    mergeSortHelper(pData, l, r);
}

// parses input file to an integer array
int parseData(char *inputFileName, int **ppData)
{
	FILE* inFile = fopen(inputFileName,"r");
	int dataSz = 0;
	int i, n, *data;
	*ppData = NULL;
	
	if (inFile)
	{
		fscanf(inFile,"%d\n",&dataSz);
		*ppData = (int *)malloc(sizeof(int) * dataSz);
		// Implement parse data block
		if (*ppData == NULL)
		{
			printf("Cannot allocate memory\n");
			exit(-1);
		}
		for (i=0;i<dataSz;++i)
		{
			fscanf(inFile, "%d ",&n);
			data = *ppData + i;
			*data = n;
		}

		fclose(inFile);
	}
	
	return dataSz;
}

// prints first and last 100 items in the data array
void printArray(int pData[], int dataSz)
{
	int i, sz = dataSz - 100;
	printf("\tData:\n\t");
	for (i=0;i<100;++i)
	{
		printf("%d ",pData[i]);
	}
	printf("\n\t");
	
	for (i=sz;i<dataSz;++i)
	{
		printf("%d ",pData[i]);
	}
	printf("\n\n");
}

int main(void)
{
	clock_t start, end;
	int i;
    double cpu_time_used;
	char* fileNames[] = { "input1.txt", "input2.txt", "input3.txt", "input4.txt" };
	
	for (i=0;i<4;++i)
	{
		int *pDataSrc, *pDataCopy;
		int dataSz = parseData(fileNames[i], &pDataSrc);
		
		if (dataSz <= 0)
			continue;
		
		pDataCopy = (int *)malloc(sizeof(int)*dataSz);
	
		printf("---------------------------\n");
		printf("Dataset Size : %d\n",dataSz);
		printf("---------------------------\n");
		
		printf("Heap Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		heapSort(pDataCopy, dataSz);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		printf("Merge Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		mergeSort(pDataCopy, 0, dataSz - 1);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		free(pDataCopy);
		free(pDataSrc);
	}
	
}
