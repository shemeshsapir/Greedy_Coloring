/*Graph Theory - assignment 2, Date: 19/01/2020
development environment - Visual Studio 2017
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>


typedef struct Interval
{
	int left;
	int right;
	int degree;
	int color;
}interval;

//function declaration
void GreedyColoring();
void sort(interval *arr, int size);
void swap(interval *a, interval *b);
void print(interval *arr, int size);
void optionalColoring(interval *arr, int size, int maxColor);
void calEdgesAndDegrees(interval *arr, int size, int *edges, int *minDeg, int *maxDeg);
int findMaxColor(interval *arr, int size);
void countColors(interval *arr, int size);
interval *input(int size);

void main()
{
	GreedyColoring(); //calling the Greedy coloring function
}

void GreedyColoring()
{
	int k, edges, minDeg, maxDeg, maxColor;
	interval *arr;

	//calling the function to calculate each variable
	printf("Please enter the number of Intervals for input: ");
	scanf("%d", &k);
	minDeg = k - 1;
	arr = input(k);
	print(arr, k);
	sort(arr, k);
	calEdgesAndDegrees(arr, k, &edges, &minDeg, &maxDeg);
	countColors(arr, k);
	maxColor = findMaxColor(arr, k);
	printf("G Edges = %d\n", edges);
	printf("Maximum Degree of G = %d \n", maxDeg);
	printf("Minimum Degree of G = %d \n", minDeg);
	printf("Chromatic Number of G = %d \n", maxColor);
	printf("G's Complement Edges = %d \n", (k*(k - 1)) / 2 - edges);
	printf("Maximum Degree of G's Complement = %d \n", k - 1 - minDeg);
	printf("Minimum Degree of G's Complement = %d \n", k - 1 - maxDeg);
	optionalColoring(arr, k, maxColor);
}

//The function gets array of intervals + its size, and sort it
void sort(interval *arr, int size)
{
	int i, j;
	int tempL, tempR;
	for (i = 0; i < size - 1; i++)
	{
		for (j = 0; j < size - i - 1; j++)
		{
			if (arr[j].left > arr[j + 1].left)
			{
				swap(&arr[j], &arr[j + 1]);
			}
			else if (arr[j].left == arr[j + 1].left)
			{
				if (arr[j].right > arr[j + 1].right)
				{
					swap(&arr[j], &arr[j + 1]);
				}
			}
		}
	}
}

//function swapping between two intervals elements
void swap(interval *a, interval *b)
{
	interval temp = *a;
	*a = *b;
	*b = temp;
}

//printing the family of intervals
void print(interval *arr, int size)
{
	int i;

	printf("The Intervals family is:\n");
	for (i = 0; i < size - 1; i++)
	{
		printf("[%d,%d],", arr[i].left, arr[i].right);
	}
	printf("[%d,%d]\n", arr[i].left, arr[i].right);
}

//gets input from user, and return new interval family
interval *input(int size)
{
	interval *arr = (interval*)malloc(size * sizeof(interval));
	int i;

	printf("You will now be asked to insert a family of %d intervals:\n", size);
	for (i = 0; i < size; i++)
	{
		printf("%dth Interval: ", i + 1);
		scanf("%d%d", &arr[i].left, &arr[i].right);
		arr[i].degree = 0;
		arr[i].color = 1;
	}
	return arr;
}

//calcultating the optional coloring for each vertex in the graph
void optionalColoring(interval *arr, int size, int maxColor)
{
	int i, j;
	printf("Optional Coloring: ");
	for (i = 1; i <= maxColor; i++)
	{
		printf("{");
		for (j = 0; j < size; j++)
		{
			while (arr[j].color != i)
			{
				j++;
			}
			printf("[%d,%d]", arr[j].left, arr[j].right);
			j++;
			for (; j < size; j++)
			{
				if (arr[j].color == i)
				{
					printf(",[%d,%d]", arr[j].left, arr[j].right);
				}
			}
		}
		i == maxColor ? printf("} = %d ", i) : printf("} = %d, ", i);
	}
}

//retuning the maximum color in the graph
int findMaxColor(interval *arr, int size)
{
	int i, maxColor = 1;
	for (i = 0; i < size; i++)
	{
		if (arr[i].color > maxColor)
			maxColor = arr[i].color;
	}
	return maxColor;
}

//giving each vertex color, according to relation with other vertex
void countColors(interval *arr, int size)
{
	int i, j, s;
	for (i = 0; i < size - 1; i++)
	{
		for (j = i + 1; j < size; j++)
		{
			if (arr[j].left <= arr[i].right)
			{
				if (arr[j].color == arr[i].color)
				{
					arr[j].color++;
					for (s = 0; s < j; s++)
					{
						if (arr[j].left <= arr[s].right)
						{
							if (arr[j].color == arr[s].color)
							{
								arr[j].color++;
							}
						}
					}
				}
			}
		}
	}
}

//calculating edges, minimum degree and maximum degree of each interval family
void calEdgesAndDegrees(interval *arr, int size, int *edges, int *minDeg, int *maxDeg)
{
	int i, j;
	*edges = 0, *minDeg = size - 1, *maxDeg = 0;
	for (i = 0; i < size - 1; i++)
	{
		for (j = i + 1; j < size; j++)
		{
			if (arr[j].left <= arr[i].right)
			{
				(*edges)++;
				arr[i].degree++;
				arr[j].degree++;
			}
		}
		*minDeg = (arr[i].degree < *minDeg) ? arr[i].degree : *minDeg;
		*maxDeg = (arr[i].degree > *maxDeg) ? arr[i].degree : *maxDeg;
	}
}
