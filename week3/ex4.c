#include <stdio.h>
#include <stdlib.h> 


void swap(int* a, int* b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}


int partition(int array[], int from, int to)
{
	int pivot = array[to];
	int i = from - 1;

	for (int j = from; j <= to - 1; j++)
	{
		if (array[j] < pivot)
		{
			++i;
			swap(&array[i], &array[j]);
		}
	}
	swap(&array[i + 1], &array[to]);

	return (i + 1);
}

void quick_sort(int array[], int from, int to)
{
	if (from < to)
	{
		int pivot = partition(array, from, to);

		quick_sort(array, from, pivot - 1);
		quick_sort(array, pivot + 1, to);
	}
}

int main()
{
	int storage[] = { 1, 31415, 2, 666, 4, 69, 42 };
	quick_sort(storage, 0, sizeof(storage) / sizeof(storage[0]) - 1);
	for (int i = 0; i < sizeof(storage) / sizeof(storage[0]); ++i)
	{
		printf("%d ", storage[i]);
	}
	printf("\n");

	return 0;
}