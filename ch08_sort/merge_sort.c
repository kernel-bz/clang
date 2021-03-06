/*
	author:		Jung,JaeJoon(rgbi3307@nate.com, http://www.kernel.bz/)
	comments:	정렬, merge sort
*/

/*
MERGE(A, p, q, r) 
 1  n1 ← q - p + 1 
 2  n2 ← r - q 
 3  //create arrays L[1  n1 + 1] and R[1  n2 + 1] 
 4  for i ← 1 to n1 
 5       do L[i] ← A[p + i - 1] 
 6  for j ← 1 to n2 
 7       do R[j] ← A[q + j] 
 8  L[n1 + 1] ← ∞ 
 9  R[n2 + 1] ← ∞ 
10  i ← 1 
11  j ← 1 
12  for k ← p to r 
13       do if L[i] ≤ R[j] 
14             then A[k] ← L[i] 
15                  i ← i + 1 
16             else A[k] ← R[j] 
17                  j ← j + 1 

MERGE-SORT(A, p, r) 
1 if p < r 
2   then q ← ⌊(p + r)/2⌋ 
3        MERGE-SORT(A, p, q) 
4        MERGE-SORT(A, q + 1, r) 
5        MERGE(A, p, q, r) 
*/

#include <stdio.h>

#define MAX 1 * 1024 * 1024 * 1024
#define nLENGTH	8	//merge 함수의 내부배열크기

void array_print (char *str, int *A, int num)
{
	int	i;
	printf ("%s: ", str);
	for (i = 0; i < num-1; i++)
		printf ("%d, ", A[i]);
	printf ("%d\n", A[i]);
}

//Divide and Combine
void merge (int *A, int p, int q, int r)
{
	int i, j, k;
	int n1 = q - p + 1;
	int n2 = r - q;
	int L[nLENGTH], R[nLENGTH];

	for (i = 0; i < n1; i++)
		L[i] = A[p + i];
	for (j = 0; j < n2; j++)
		R[j] = A[q + j + 1];

	L[n1] = MAX;
	R[n2] = MAX;

	i = 0;
	j = 0;
	for (k = p; k <= r; k++) {
		if (L[i] <= R[j]) {
			A[k] = L[i];
			i++;
		} else {
			A[k] = R[j];
			j++;
		}
	}
}

//Conquer
int merge_sort (int *A, int p, int r)
{
	int q;
	static int ncnt = 0;

	if (p < r) {
		q = (p + r) / 2;
		merge_sort (A, p, q);
		merge_sort (A, q+1, r);

		//printf ("(p, q, r)=(%d, %d, %d)\n", p, q, r);
		merge (A, p, q, r);

		ncnt++;
	}
	return ncnt;
}

int main (void)
{
	int A[] = {2, 9, 4, 7, 1, 5, 8, 3}; //n = 8
	int n = sizeof(A) / sizeof(A[0]);	//nLENGTH
	int *pA, ncnt;
		
	pA = A;
	array_print (" Input", pA, n);
	ncnt = merge_sort (pA, 0, n-1);
	array_print ("Output", pA, n);	

	printf("Iteration = %d\n", ncnt);

	printf ("Press any key to end...");
	getchar();
	return 0;
}

