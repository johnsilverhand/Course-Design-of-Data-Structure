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
		void copyArr();  //每种排序前的初始化 
		void StraightInsertionSort();
		void ShellSort();
		void SimpleSelectionSort();
		void HeapSort();
		void HeapMax(int start,int end);//大根堆，维护堆的函数 
		void BubbleSort();
		int NumberOfThree(int low,int high);//快排辅助函数 
		void QuickSort(int left,int right);
		int QuickSortNonRecursive(int low,int high); //快排的辅助函数 
		void MergeSort();	//2路归并非递归 
		void Merge(int low,int mid,int high);//归并过程 
		void MSort(int T_len);		//2路归并的非递归调用 
		void RadixSort();
		int maxbit ();	//基数排序的辅助函数，用于求数据的最大位数 
};

#endif
