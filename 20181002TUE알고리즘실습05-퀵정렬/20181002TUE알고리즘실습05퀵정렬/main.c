//
//  main.c
//  20181002TUE알고리즘실습05퀵정렬
//
//  Created by 최성정 on 2018. 10. 2..
//  Copyright © 2018년 최성정. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

typedef struct ab{
    int a;
    int b;
}ab;

void inPlaceQuickSort(int arr[],int left,int right);
ab inPlacePartition(int arr[], int left, int right, int k);
int find_pivot_index(int* arr, int left, int right);
int N;

int main() {
    
    int *arr;
    
    scanf("%d",&N);
    
    arr=(int*)malloc(sizeof(int)*N);
    
    for(int i=0;i<N;i++){
        scanf("%d",&arr[i]);
    }
    
    inPlaceQuickSort(arr,0,N-1);
    

    for(int i = 0 ; i < N ; i++)
        printf("%d ", arr[i]);

    
    return 0;
    
}

void inPlaceQuickSort(int arr[],int left,int right){
    
    if(left >= right)return;
    
    ab abvalue;
    
    
    int k =find_pivot_index(arr, left, right);
    
    abvalue = inPlacePartition(arr, left, right, k); // 둘로 나누어서
    
    inPlaceQuickSort(arr, left, abvalue.a - 1); // 작은 것
    
    inPlaceQuickSort(arr, abvalue.b + 1, right); // 큰 것
    
}

ab inPlacePartition(int arr[], int left, int right, int k)
{
    int pivot = arr[k]; // 기준원소
    
    int temp = arr[k];  // 기준원소와 마지막원소 교환
    arr[k] = arr[right];
    arr[right] = temp;
    
    int i = left;
    int j = right -1;
    
    ab abvalue; //반환할 쌍 선언
    
    while (i <= j) // 교차되기 전까지 반복
    {
        while (arr[i] <= pivot  && i <= j) // pivot보다 큰 값 찾기
            i++; // i를 오른쪽
        
        while (pivot <= arr[j] && i <= j ) // pivot보다 작은 값 찾기
            j--; // j를 왼쪽
        
        if (i < j)// 교차되거나 같지 않은 상태이면 교환
        {
            temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    
    temp = arr[i]; // pivot과 i가 가리키는 대상을 교환
    arr[i] = arr[right];
    arr[right] = temp;
    
    abvalue.b = j;  //기준원소보다 작은 쪽 마지막 값 a
    abvalue.a = i;  //기준원소보다 큰 쪽 처음 값 b
    
    return abvalue; //a와 b 반환
}


int find_pivot_index(int* arr,int left, int right){
    
    int mid;
    
    int A =rand() % (right - left +1) + left;
    int B =rand() % (right - left +1) + left;
    int C =rand() % (right - left +1) + left;
    
    if(arr[A]<arr[B]){
        if(arr[C]<arr[A])mid=A;
        
        else if(arr[A]<arr[C] && arr[C]<arr[B])mid=C;
        
        else mid=B;
    }
    else{        
        if(arr[B]>arr[C])mid=B;
        
        else if(arr[B]<arr[C] && arr[C]<arr[A])mid=C;
        
        else mid =A;
    }
    
    return mid;
}
