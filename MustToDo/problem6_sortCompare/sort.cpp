#include<iostream>
#include"sort.h"
#include<time.h>
#include<stack>
using namespace std;

//冒泡 
void Sort::BubbleSort(){
	for (int i = 0;i < len - 1;i++){
		for (int j = 0;j < len - i -1;j++){
			if (a[j] > a[j+1]){
				int temp = a[j+1];
				a[j] = a[j+1];
				a[j+1] = temp;
			}
		}
	}
}
//选择 
void Sort::SimpleSelectionSort(){
	for (int i = 0;i < len - 1;i++){
		int min = i;
		for (int j = i+1;j < len;j++){
			if (a[j] < a[min])
				min = j;
		}
		int temp = a[i];
		a[i] = a[min];
		a[min] = temp;
	}
}
//插入 
void Sort::StraightInsertionSort(){
	for (int i = 1;i< len;i++){
		int key = a[i];
		int j = i-1;
		while((j>=0) && (key<a[j])){
                        a[j+1] = a[j];
                        j--;
                }
                a[j+1] = key;
	}
}
//希尔 
void Sort::ShellSort(){
	int h = 1;
    while (h < len / 3) {
        h = 3 * h + 1;
    }
    while (h >= 1) {
        for (int i = h; i < len; i++) {
            for (int j = i; j >= h && a[j] < a[j - h]; j -= h) {
	            int temp = a[j];
				a[j] = a[j-h];
				a[j-h] = temp;
            }
        }
        h = h / 3;
    }
}
//归并 
void Sort::Merge(int low,int mid,int high){
	int *T = new int[high - low + 1];
	int i = low,j = mid + 1,k = 0;
	while (i <= mid && j <= high){
		if ( a[i] <= a[j] ){
			T[k] = a[i]; i++; k++;
		}
		else {
			T[k] = a[j]; j++; k++;
		}
	}
	while ( i <= mid ){
		T[k] = a[j]; i++; k++;
	}
	while ( j <= high ){
		T[k] = a[j]; j++; k++;
	}
	for (k = 0,i = low; i<=high; k++,i++)
		a[i] = T[k];	
} 
void Sort::MSort(int T_len){
	int i = 1;
	while (i+2*T_len <= len){
		//归并两个子序列
		Merge(i,i+T_len-1,i+2*T_len-1);
		i = i+2*T_len; 
	}
	if (i + T_len <= len){
		Merge(i,i+T_len-1,len); //归并最后两个子序列 
	}
} 
void Sort::MergeSort(){
	for (int T_len = 1; T_len <= len; T_len = 2* T_len){
		MSort(T_len);
	} 
}
int Sort::NumberOfThree(int low,int high){
	int mid = low + ((high - low) >> 1);//右移相当于除以2
 
	if (a[mid] > a[high])
	{
		std::swap(a[mid],a[high]);
	}
	if (a[low] > a[high])
	{
		std::swap(a[low],a[high]);
	}
	if (a[mid] > a[low]) 
	{
		std::swap(a[mid],a[low]);
	}
	//此时，arr[mid] <= arr[low] <= arr[high]
	return a[low];
} 
//快排 
int Sort::QuickSortNonRecursive(int low,int high){
  int pivot = NumberOfThree(low, high);;
	while (low < high) {
	    while (low < high && a[high] >= pivot) {
	       --high;
	     }
	     a[low] = a[high];
	     while (low < high && a[low] <= pivot) {
	       ++low;
	     }
	     a[high] = a[low];
	}
   a[low] = pivot;
   return low;
} 
void Sort::QuickSort(int left,int right){
	//手动利用栈来存储每次快排的起始点
	//栈非空时循环获取中轴入栈
	stack<int> s;
	if( left<right )
	{
		int boundary = QuickSortNonRecursive(left,right);
		
		if( boundary-1>left ) //确保左分区存在 
		{
			//将左分区端点入栈 
			s.push(left);
			s.push(boundary-1);
		}
		if( boundary+1<right ) //确保右分区存在 
		{
			s.push(boundary+1);
			s.push(right);
		}
		
		while( !s.empty() )
		{
			//得到某分区的左右边界 
			int r = s.top();
			s.pop();  
			int l = s.top();
			s.pop();
			
			boundary = QuickSortNonRecursive(l,r);
			if( boundary-1>l ) //确保左分区存在 
		    { 
			    //将左分区端点入栈 
		    	s.push(l);
		    	s.push(boundary-1);
	    	}
		    if( boundary+1<r ) //确保右分区存在 
	     	{
	 	    	s.push(boundary+1);
	    		s.push(r);
	    	}
		}
	}

}
//堆排序 
void Sort::HeapMax(int start,int end){
	int parent = start;
	int child = parent * 2 + 1;
	//建立堆 
	while (child <= end){
		if (child + 1 <= end && a[child] < a[child + 1])
			child++;
		if (a[parent] > a[child])
			return; //维护完成 
		else{
			std::swap(a[parent],a[child]);
			parent = child;
			child = parent * 2 + 1; 
		} 
	}
} 
void Sort::HeapSort(){
	int i;
	//初始化
	for (i = len/2 - 1;i >= 0;i--)
		Sort::HeapMax(i,len-1);
	for (i = len -1;i > 0;i--){
		std::swap(a[0],a[i]);
		Sort::HeapMax(0,i-1);
	} 
}
//基数排序 
int Sort::maxbit(){
	int maxData = a[0];
	for (int i = 1;i < len; ++i){
		if (maxData < a[i])
			maxData = a[i];
	}
	int d = 1;
	int p = 10;
	while (maxData >= p){
		maxData /= 10;
		++d;
	}
	return d;
} 
void Sort::RadixSort(){
	int d = maxbit();
	int *tmp = new int[len];
	int *count = new int[10];//末位计数器
	int i,j,k;//循环变量
	int radix =  1;
	for (i = 1;i <= d;i++){
	    for(j = 0; j < 10; j++)
            count[j] = 0; //每次分配前清空计数器
        for(j = 0; j < len; j++){
            k = (a[j] / radix) % 10; //统计每个桶中的记录数
            count[k]++;
        }
        for(j = 1; j < 10; j++)
            count[j] = count[j - 1] + count[j]; //将tmp中的位置依次分配给每个桶
        for(j = len - 1; j >= 0; j--){ //将所有桶中记录依次收集到tmp中
            k = (a[j] / radix) % 10;
            tmp[count[k] - 1] = a[j];
            count[k]--;
        }
        for(j = 0; j < len; j++) //将临时数组的内容复制到data中
            a[j] = tmp[j];
        radix = radix * 10;	
	}
	delete []tmp;
	delete []count; 
} 
void Sort::copyArr(){
	a = (int*)malloc(sizeof(int)*num);
	for (int i = 0;i<len;i++){
		a[i] = origin[i];
	}
}
void Sort::ShowSort(int info){
	cout<<"第"<<info<<"个样本的排序用时如下:"<<endl;
	copyArr();
	cout<<"排序前数组初始化完成"<<endl;
	startTime = clock();
	BubbleSort();
	endTime = clock();
	cout<<"该样本冒泡排序用时："<<endTime - startTime<<" ms"<<endl;
	copyArr();
	startTime = clock();
	SimpleSelectionSort(); 
	endTime = clock();
	cout<<"该样本选择排序用时："<<endTime - startTime<<" ms"<<endl;
	copyArr();
	startTime = clock();
	StraightInsertionSort();
	endTime = clock();
	cout<<"该样本插入排序用时："<<endTime - startTime<<" ms"<<endl;
	copyArr();
	startTime = clock();
	ShellSort();
	endTime = clock();
	cout<<"该样本希尔排序用时："<<endTime - startTime<<" ms"<<endl;
	copyArr();
	startTime = clock();
	MergeSort();
	endTime = clock();
	cout<<"该样本归并排序用时："<<endTime - startTime<<" ms"<<endl;
	copyArr();
	startTime = clock();
	HeapSort();
	endTime = clock();
	cout<<"该样本堆排序用时："<<endTime - startTime<<" ms"<<endl;
	
	copyArr();
	startTime = clock();
	QuickSort(0,49999);
	endTime = clock();
	cout<<"该样本快速排序用时："<<endTime - startTime<<" ms"<<endl;
	
	copyArr();
	startTime = clock();
	RadixSort();
	endTime = clock();
	cout<<"该样本基数排序用时："<<endTime - startTime<<" ms"<<endl;
	
}
