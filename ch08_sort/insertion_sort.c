/*
	author:		Jung,JaeJoon(rgbi3307@nate.com, http://www.kernel.bz/)
	comments:	정렬, insertion sort
*/

/*
INSERTION-SORT(A) 
1  for j ← 2 to length[A] 
2       do key ← A[j] 
3          ▹ Insert A[j] into the sorted sequence A[1  j - 1]. 
4          i ← j - 1 
5          while i > 0 and A[i] > key 
6              do A[i + 1] ← A[i] 
7                 i ← i - 1 
8          A[i + 1] ← key 
*/

#include <stdio.h>
#include <conio.h>

void array_print (char *str, int *A, int num)
{
	int	i;
	printf ("%s: ", str);
	for (i = 0; i < num-1; i++)
		printf ("%d, ", A[i]);
	printf ("%d\n", A[i]);
}

int insertion_sort (int *A, int num)
{
	int	i, j, key, ncnt=0;

	for (i = 1; i < num; i++) {
		key = A[i];
		j = i - 1;
		while ((j >= 0) && (A[j] > key)) {
			A[j+1] = A[j];  //key보다 큰것은 오른쪽으로 이동
			j--;
			ncnt++;
		}
		A[j+1] = key;  //삽입
	}
	return ncnt;
}

int main (void)
{
	int A[] = {2, 9, 4, 7, 1, 5, 8, 3}; //n = 8
	//int A[] = {1, 2, 3, 4, 5, 7, 8, 9}; //이미 정렬된 자료(오름차순) <-- 최선
	//int A[] = {9, 8, 7, 5, 4, 3, 2, 1}; //이미 정렬된 자료(내림차순) <-- 최악
	int n = sizeof(A) / sizeof(A[0]);
	int *pA, ncnt;
	
	pA = A;
	array_print (" Input", pA, n);
	ncnt = insertion_sort (pA, n);
	array_print ("Output", pA, n);

	printf("Iteration = %d\n", ncnt);

	printf ("Press any key to end...");
	getchar();
	return 0;
}
