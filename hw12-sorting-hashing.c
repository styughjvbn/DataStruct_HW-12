/*
 * hw12-sorting-hashing.c
 *
 *  Created on: May 22, 2021
 *
 *  Homework 12: Sorting & Hashing
 *  Department of Computer Science at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_ARRAY_SIZE			13	/* prime number */
#define MAX_HASH_TABLE_SIZE 	MAX_ARRAY_SIZE

/* 필요에 따라 함수 추가 가능 */
int initialize(int **a);
int freeArray(int *a);
void printArray(int *a);

int selectionSort(int *a);
int insertionSort(int *a);
int bubbleSort(int *a);
int shellSort(int *a);
/* recursive function으로 구현 */
int quickSort(int *a, int n);


/* hash code generator, key % MAX_HASH_TABLE_SIZE */
int hashCode(int key);

/* array a에대 한 hash table을 만든다. */
int hashing(int *a, int **ht);

/* hash table에서 key를 찾아 hash table의 index return */
int search(int *ht, int key);


int main()
{
	char command;
	int *array = NULL;
	int *hashtable = NULL;
	int key = -1;
	int index = -1;

	srand(time(NULL));

	printf("-----------------------[2018038031 서종원]------------------------------\n");
	do{
		printf("----------------------------------------------------------------\n");
		printf("                        Sorting & Hashing                       \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize       = z           Quit             = q\n");
		printf(" Selection Sort   = s           Insertion Sort   = i\n");
		printf(" Bubble Sort      = b           Shell Sort       = l\n");
		printf(" Quick Sort       = k           Print Array      = p\n");
		printf(" Hashing          = h           Search(for Hash) = e\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		fflush(stdout);
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initialize(&array);
			break;
		case 'q': case 'Q':
			freeArray(array);
			break;
		case 's': case 'S':
			selectionSort(array);
			break;
		case 'i': case 'I':
			insertionSort(array);
			break;
		case 'b': case 'B':
			bubbleSort(array);
			break;
		case 'l': case 'L':
			shellSort(array);
			break;
		case 'k': case 'K':
			printf("Quick Sort: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array);
			quickSort(array, MAX_ARRAY_SIZE);
			printf("----------------------------------------------------------------\n");
			printArray(array);

			break;

		case 'h': case 'H':
			printf("Hashing: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array);
			hashing(array, &hashtable);
			printArray(hashtable);
			break;

		case 'e': case 'E':
			printf("Your Key = ");
			fflush(stdout);
			scanf("%d", &key);
			printArray(hashtable);
			index = search(hashtable, key);
			printf("key = %d, index = %d,  hashtable[%d] = %d\n", key, index, index, hashtable[index]);
			break;

		case 'p': case 'P':
			printArray(array);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

int initialize(int** a)//배열 생성 및 초기화
{
	int *temp = NULL;

	/* array가 NULL인 경우 메모리 할당 */
	if(*a == NULL) {
		temp = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);
		*a = temp;  /* 할당된 메모리의 주소를 복사 --> main에서 배열을 control 할수 있도록 함*/
	} else
		temp = *a;

	/* 랜덤값을 배열의 값으로 저장 */
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		temp[i] = rand() % MAX_ARRAY_SIZE;

	return 0;
}

int freeArray(int *a)//배열을 해제한다.
{
	if(a != NULL)
		free(a);
	return 0;
}

void printArray(int *a)//배열을 출력한다.
{
	if (a == NULL) {
		printf("nothing to print.\n");
		return;
	}
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		printf("a[%02d] ", i);
	printf("\n");
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		printf("%5d ", a[i]);
	printf("\n");
}


int selectionSort(int *a)//선택 정렬
{
	int min;
	int minindex;
	int i, j;

	printf("Selection Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);//정렬하기 전 배열 출력

	for (i = 0; i < MAX_ARRAY_SIZE; i++)//배열의 끝까지 반복한다.
	{
		minindex = i;//임의로 i인덱스의 값을 최소값으로 선택한다.
		min = a[i];
		for(j = i+1; j < MAX_ARRAY_SIZE; j++)//i인덱스 다음 인덱스의 값부터 배열의 끝까지 반복한다.
		{
			if (min > a[j])//최소값을 찾는다.
			{
				min = a[j];
				minindex = j;
			}
		}
		a[minindex] = a[i];//최소값을 가지는 인덱스에 i인덱스 값을 넣는다.
		a[i] = min;//i인덱스에 최소값을 넣는다. 이러면 0번 인덱스부터 오름차순으로 정렬이 된다.
	}

	printf("----------------------------------------------------------------\n");
	printArray(a);//정렬 후 배열 출력
	return 0;
}

int insertionSort(int *a)//삽입 정렬
{
	int i, j, t;

	printf("Insertion Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);

	for(i = 1; i < MAX_ARRAY_SIZE; i++)//배열의 2번째 값부터 정렬한다.
	{
		t = a[i];//알맞은 곳에 삽입할 값을 저장한다.
		j = i;//삽입할 값의 인덱스를 저장한다.
		while (a[j-1] > t && j > 0)//삽입될 값보다 큰 값들이 뒤로 한칸씩 밀려난다.
		{
			a[j] = a[j-1];//
			j--;
		}
		a[j] = t;//삽입될 값보다 작은 값을 가지는 인덱스의 뒤에서 반복이 멈추고 뒤에 삽입이 된다.
	}

	printf("----------------------------------------------------------------\n");
	printArray(a);

	return 0;
}

int bubbleSort(int *a)//버블 정렬
{
	int i, j, t;

	printf("Bubble Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);

	for(i = 0; i < MAX_ARRAY_SIZE; i++)//처음부터 끝까지 반복한다.
	{
		for (j = 1; j < MAX_ARRAY_SIZE; j++)//두번째 값부터 끝까지 반복한다.
		{
			if (a[j-1] > a[j])//해당 인덱스의 값이 전 인덱스의 값보다 작다면 둘의 값을 바꾼다.
			{
				t = a[j-1];
				a[j-1] = a[j];
				a[j] = t;
			}
		}
	}

	printf("----------------------------------------------------------------\n");
	printArray(a);

	return 0;
}

int shellSort(int *a)//셸 정렬
{
	int i, j, k, h, v;

	printf("Shell Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);

	for (h = MAX_ARRAY_SIZE/2; h > 0; h /= 2)//기준 간격을 정한다. 12부터 시작이라면 6->3->1로 간격이 변한다.
	{
		for (i = 0; i < h; i++)//만약 배열의 길이가 12고 기준간격이 6이라면 (0,6)->(1,7)->(2,8)->(3,9)->(4,10)->(5,11)->(6,12)끼리 정렬이 되게 한다. 다음 집합이 정렬되게 한다.
		{
			for(j = i + h; j < MAX_ARRAY_SIZE; j += h)//삽입정렬과 같다. 전 인덱스의 값이 자신보다 크다면 자리를 바꾸며 나아간다 전 인덱스의 값이 자신보다 작다면 멈춘다.
			{
				v = a[j];
				k = j;
				while (k > h-1 && a[k-h] > v)
				{
					a[k] = a[k-h];
					k -= h;
				}
				a[k] = v;
			}
		}
	}
	printf("----------------------------------------------------------------\n");
	printArray(a);

	return 0;
}

int quickSort(int *a, int n)//퀵 정렬
{
	int v, t;
	int i, j;

	if (n > 1)
	{
		v = a[n-1];//집합의 마지막 원소를 피봇으로 잡는다.

		i = -1;//피봇보다 큰 값을 가지는 인덱스를 저장한다.
		j = n - 1;//피봇보다 작은 값을 가지는 인덱스를 저장한다.

		while(1)
		{
			while(a[++i] < v);//피봇보다 큰 값을 가지는 인덱스를 찾는다.
			while(a[--j] > v);//피봇보다 작은 값을 가지는 인덱스를 찾는다.

			if (i >= j) break;//찾은 각각의 인덱스중에 큰 값을 가지는 인덱스가 작은 값을 가지는 인덱스보다 크다면 반복을 종료한다.
			t = a[i];//각각의 인덱스의 값을 교환한다.
			a[i] = a[j];
			a[j] = t;
		}
		t = a[i];//반복이 종료되면 피봇과 큰값을 가지는 인덱스의 값과 교환한다.
		a[i] = a[n-1];
		a[n-1] = t;
		//한 사이클이 종료되면 피봇의 왼쪽집합은 피봇보다 큰 값들을 가지고 오른쪽 집합은 피봇보다 작은 값을 가진다.
		quickSort(a, i);//오른쪽 집합을 가지고 함수를 호출한다.
		quickSort(a+i+1, n-i-1);//왼쪽 집합을 가지고 함수를 호출한다.
	}


	return 0;
}

int hashCode(int key) {//해쉬함수이다
   return key % MAX_HASH_TABLE_SIZE;
}

int hashing(int *a, int **ht)
{
	int *hashtable = NULL;

	/* hash table이 NULL인 경우 메모리 할당 */
	if(*ht == NULL) {
		hashtable = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);
		*ht = hashtable;  /* 할당된 메모리의 주소를 복사 --> main에서 배열을 control 할수 있도록 함*/
	} else {
		hashtable = *ht;	/* hash table이 NULL이 아닌경우, table 재활용, reset to -1 */
	}

	for(int i = 0; i < MAX_HASH_TABLE_SIZE; i++)
		hashtable[i] = -1;

	/*
	for(int i = 0; i < MAX_HASH_TABLE_SIZE; i++)
		printf("hashtable[%d] = %d\n", i, hashtable[i]);
	*/

	int key = -1;
	int hashcode = -1;
	int index = -1;
	for (int i = 0; i < MAX_ARRAY_SIZE; i++)
	{
		key = a[i];
		hashcode = hashCode(key);
		/*
		printf("key = %d, hashcode = %d, hashtable[%d]=%d\n", key, hashcode, hashcode, hashtable[hashcode]);
		*/
		if (hashtable[hashcode] == -1)
		{
			hashtable[hashcode] = key;
		} else 	{

			index = hashcode;

			while(hashtable[index] != -1)
			{
				index = (++index) % MAX_HASH_TABLE_SIZE;
				/*
				printf("index = %d\n", index);
				*/
			}
			hashtable[index] = key;
		}
	}

	return 0;
}

int search(int *ht, int key)
{
	int index = hashCode(key);

	if(ht[index] == key)
		return index;

	while(ht[++index] != key)
	{
		index = index % MAX_HASH_TABLE_SIZE;
	}
	return index;
}
