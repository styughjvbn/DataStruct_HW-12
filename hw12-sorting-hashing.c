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

/* �ʿ信 ���� �Լ� �߰� ���� */
int initialize(int **a);
int freeArray(int *a);
void printArray(int *a);

int selectionSort(int *a);
int insertionSort(int *a);
int bubbleSort(int *a);
int shellSort(int *a);
/* recursive function���� ���� */
int quickSort(int *a, int n);


/* hash code generator, key % MAX_HASH_TABLE_SIZE */
int hashCode(int key);

/* array a���� �� hash table�� �����. */
int hashing(int *a, int **ht);

/* hash table���� key�� ã�� hash table�� index return */
int search(int *ht, int key);


int main()
{
	char command;
	int *array = NULL;
	int *hashtable = NULL;
	int key = -1;
	int index = -1;

	srand(time(NULL));

	printf("-----------------------[2018038031 ������]------------------------------\n");
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

int initialize(int** a)//�迭 ���� �� �ʱ�ȭ
{
	int *temp = NULL;

	/* array�� NULL�� ��� �޸� �Ҵ� */
	if(*a == NULL) {
		temp = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);
		*a = temp;  /* �Ҵ�� �޸��� �ּҸ� ���� --> main���� �迭�� control �Ҽ� �ֵ��� ��*/
	} else
		temp = *a;

	/* �������� �迭�� ������ ���� */
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		temp[i] = rand() % MAX_ARRAY_SIZE;

	return 0;
}

int freeArray(int *a)//�迭�� �����Ѵ�.
{
	if(a != NULL)
		free(a);
	return 0;
}

void printArray(int *a)//�迭�� ����Ѵ�.
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


int selectionSort(int *a)//���� ����
{
	int min;
	int minindex;
	int i, j;

	printf("Selection Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);//�����ϱ� �� �迭 ���

	for (i = 0; i < MAX_ARRAY_SIZE; i++)//�迭�� ������ �ݺ��Ѵ�.
	{
		minindex = i;//���Ƿ� i�ε����� ���� �ּҰ����� �����Ѵ�.
		min = a[i];
		for(j = i+1; j < MAX_ARRAY_SIZE; j++)//i�ε��� ���� �ε����� ������ �迭�� ������ �ݺ��Ѵ�.
		{
			if (min > a[j])//�ּҰ��� ã�´�.
			{
				min = a[j];
				minindex = j;
			}
		}
		a[minindex] = a[i];//�ּҰ��� ������ �ε����� i�ε��� ���� �ִ´�.
		a[i] = min;//i�ε����� �ּҰ��� �ִ´�. �̷��� 0�� �ε������� ������������ ������ �ȴ�.
	}

	printf("----------------------------------------------------------------\n");
	printArray(a);//���� �� �迭 ���
	return 0;
}

int insertionSort(int *a)//���� ����
{
	int i, j, t;

	printf("Insertion Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);

	for(i = 1; i < MAX_ARRAY_SIZE; i++)//�迭�� 2��° ������ �����Ѵ�.
	{
		t = a[i];//�˸��� ���� ������ ���� �����Ѵ�.
		j = i;//������ ���� �ε����� �����Ѵ�.
		while (a[j-1] > t && j > 0)//���Ե� ������ ū ������ �ڷ� ��ĭ�� �з�����.
		{
			a[j] = a[j-1];//
			j--;
		}
		a[j] = t;//���Ե� ������ ���� ���� ������ �ε����� �ڿ��� �ݺ��� ���߰� �ڿ� ������ �ȴ�.
	}

	printf("----------------------------------------------------------------\n");
	printArray(a);

	return 0;
}

int bubbleSort(int *a)//���� ����
{
	int i, j, t;

	printf("Bubble Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);

	for(i = 0; i < MAX_ARRAY_SIZE; i++)//ó������ ������ �ݺ��Ѵ�.
	{
		for (j = 1; j < MAX_ARRAY_SIZE; j++)//�ι�° ������ ������ �ݺ��Ѵ�.
		{
			if (a[j-1] > a[j])//�ش� �ε����� ���� �� �ε����� ������ �۴ٸ� ���� ���� �ٲ۴�.
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

int shellSort(int *a)//�� ����
{
	int i, j, k, h, v;

	printf("Shell Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);

	for (h = MAX_ARRAY_SIZE/2; h > 0; h /= 2)//���� ������ ���Ѵ�. 12���� �����̶�� 6->3->1�� ������ ���Ѵ�.
	{
		for (i = 0; i < h; i++)//���� �迭�� ���̰� 12�� ���ذ����� 6�̶�� (0,6)->(1,7)->(2,8)->(3,9)->(4,10)->(5,11)->(6,12)���� ������ �ǰ� �Ѵ�. ���� ������ ���ĵǰ� �Ѵ�.
		{
			for(j = i + h; j < MAX_ARRAY_SIZE; j += h)//�������İ� ����. �� �ε����� ���� �ڽź��� ũ�ٸ� �ڸ��� �ٲٸ� ���ư��� �� �ε����� ���� �ڽź��� �۴ٸ� �����.
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

int quickSort(int *a, int n)//�� ����
{
	int v, t;
	int i, j;

	if (n > 1)
	{
		v = a[n-1];//������ ������ ���Ҹ� �Ǻ����� ��´�.

		i = -1;//�Ǻ����� ū ���� ������ �ε����� �����Ѵ�.
		j = n - 1;//�Ǻ����� ���� ���� ������ �ε����� �����Ѵ�.

		while(1)
		{
			while(a[++i] < v);//�Ǻ����� ū ���� ������ �ε����� ã�´�.
			while(a[--j] > v);//�Ǻ����� ���� ���� ������ �ε����� ã�´�.

			if (i >= j) break;//ã�� ������ �ε����߿� ū ���� ������ �ε����� ���� ���� ������ �ε������� ũ�ٸ� �ݺ��� �����Ѵ�.
			t = a[i];//������ �ε����� ���� ��ȯ�Ѵ�.
			a[i] = a[j];
			a[j] = t;
		}
		t = a[i];//�ݺ��� ����Ǹ� �Ǻ��� ū���� ������ �ε����� ���� ��ȯ�Ѵ�.
		a[i] = a[n-1];
		a[n-1] = t;
		//�� ����Ŭ�� ����Ǹ� �Ǻ��� ���������� �Ǻ����� ū ������ ������ ������ ������ �Ǻ����� ���� ���� ������.
		quickSort(a, i);//������ ������ ������ �Լ��� ȣ���Ѵ�.
		quickSort(a+i+1, n-i-1);//���� ������ ������ �Լ��� ȣ���Ѵ�.
	}


	return 0;
}

int hashCode(int key) {//�ؽ��Լ��̴�
   return key % MAX_HASH_TABLE_SIZE;
}

int hashing(int *a, int **ht)
{
	int *hashtable = NULL;

	/* hash table�� NULL�� ��� �޸� �Ҵ� */
	if(*ht == NULL) {
		hashtable = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);
		*ht = hashtable;  /* �Ҵ�� �޸��� �ּҸ� ���� --> main���� �迭�� control �Ҽ� �ֵ��� ��*/
	} else {
		hashtable = *ht;	/* hash table�� NULL�� �ƴѰ��, table ��Ȱ��, reset to -1 */
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
