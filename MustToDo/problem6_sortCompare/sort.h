#ifndef SORT_H
#define SORT_H

#include <iostream>
#include <time.h>

using namespace std;

class Sort{
	public:
		int startTime;
		int endTime;
		int num;
		int *a;
		int *origin;
		int len;
		//int min;
	public:
		Sort (int *array,int numArr): origin(array),num(numArr),len(numArr){
		}
		void ShowSort(int info = -1);
		void copyArr();  //ÿ������ǰ�ĳ�ʼ�� 
		void StraightInsertionSort();
		void ShellSort();
		void SimpleSelectionSort();
		void HeapSort();
		void HeapMax(int start,int end);//����ѣ�ά���ѵĺ��� 
		void BubbleSort();
		int NumberOfThree(int low,int high);//���Ÿ������� 
		void QuickSort(int left,int right);
		int QuickSortNonRecursive(int low,int high); //���ŵĸ������� 
		void MergeSort();	//2·�鲢�ǵݹ� 
		void Merge(int low,int mid,int high);//�鲢���� 
		void MSort(int T_len);		//2·�鲢�ķǵݹ���� 
		void RadixSort();
		int maxbit ();	//��������ĸ������������������ݵ����λ�� 
};

#endif
