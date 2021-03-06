/*
	Introduction to Algorithms
	Chapter 8: Sorting in Linear Time
	-----------------------------------------------------------------------------------------------
	8.2 Counting sort 
	Counting sort assumes that each of the n input elements is an integer in the range 0 to k, for 
	some integer k. When k = O(n), the sort runs in Θ(n) time. 

	COUNTING-SORT(A, B, k) 
	 1  for i ← 0 to k 
	 2     do C[i] ← 0 
	 3  for j ← 1 to length[A] 
	 4     do C[A[j]] ← C[A[j]] + 1 
	 5  ▹ C[i] now contains the number of elements equal to i. 
	 6  for i ← 1 to k 
	 7     do C[i] ← C[i] + C[i - 1] 
	 8  ▹ C[i] now contains the number of elements less than or equal to i. 
	 9  for j ← length[A] downto 1 
	10     do B[C[A[j]]] ← A[j] 
	11        C[A[j]] ← C[A[j]] - 1 

	-----------------------------------------------------------------------------------------------
	Coding in C: Jung,JaeJoon(rgbi3307@nate.com, http://www.kernel.bz/)
*/

#include <stdio.h>

#define nCNT 16  //n: 배열크기가 미리 알려져야 함

//A[]: 입력배열
//B[]: 출력배열(정렬결과)
//k: Counting 배열 크기
void counting_sort (int A[], int B[], int k)
{
	int i, j, C[nCNT]; //nCNT = k

	for (i = 0; i <= k; i++)
		C[i] = 0;

	for (j = 1; j < nCNT; j++)
		C[A[j]] = C[A[j]] + 1;  //입력배열 A[]의 요소개수 계산

	for (i = 1; i <= k; i++)
		C[i] = C[i] + C[i-1];	//C[] 배열의 요소 개수를 더함

	for (j = nCNT-1; j >= 0; j--) {
		B[C[A[j]]] = A[j];
		C[A[j]] = C[A[j]]  - 1;
	}
}

int main ()
{
	//A[0]=0, C언어는 배열 인덱스가 0부터 시작하므로
	int A[] = {0, 2, 9, 4, 7, 6, 7, 5, 8, 3, 1, 2, 9, 4, 7, 6}; //n = 16
	int B[nCNT];
	int i, k;

	k = 0;
	for (i = 0; i < nCNT; i++)
		if (A[i] > k) k = A[i];  //가장 큰 배열요소(k < n)

	counting_sort (A, B, k);

	//정렬 결과 출력
	for (i = 0; i < nCNT; i++)
		printf ("%d, ", B[i]);

	printf ("\nPress any key to end...");
	getchar();
	return 0;
}
