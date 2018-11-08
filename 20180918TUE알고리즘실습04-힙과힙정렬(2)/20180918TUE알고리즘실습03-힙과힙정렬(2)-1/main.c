//
//  main.c
//  20180918TUE알고리즘실습03-힙과힙정렬(2)-1
//
//  Created by 최성정 on 2018. 9. 18..
//  Copyright © 2018년 최성정. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>


int H[100];  // 힙
int n;  //힙의 크기
int heapsizeforprint;

void downHeap(int index);
void printArray();
void inPlaceheapSort();
void insertItem(int key);
void upHeap(int index);

int main() {
    
    int num;
    
    scanf("%d",&num);
    
    getchar();
    
    int key;
    
    for(int i=1;i<=num; i++){
        scanf("%d",&key);
        insertItem(key);
    }
    inPlaceheapSort();
    

    printArray();   //정렬리스트
    
    return 0;
}

/* 키를 힙에 삽입*/
void insertItem(int key){   // 키를 힙에 삽입하고 0을 인쇄
    
    n++;
    H[n]=key;
    upHeap(n);
    
}

/*키를 정렬 (삽입시) upHeap*/
void upHeap(int index){
    
    int parentindex = index/2; //부모인덱스 선언 -> index/2
    
    if(index==1) return; //키 개수가 1개면 리턴
    
    if(H[index] <= H[parentindex] ) return; //부모노드가 삽입노드보다 크면 리턴
    
    int parent =H[parentindex]; // 부모인덱스의 값 parent 에 저장
    
    H[parentindex] =H[index];
    H[index] =parent;
    index =parentindex;
    upHeap(index);
    
}

/*키를 정렬 downHeap*/
void downHeap(int index){
    int left = 2*index;
    int right =2*index+1;
    
    if(left>n) return;
    
    int bigger = H[left];
    
    if(right <= n){
        if(bigger <H[right]){
            bigger =H[right];
        }
    }
    
    if(H[index]>=bigger) return;
    
    if(H[left] ==bigger){ //왼쪽이면
        H[left] =H[index];
        H[index] = bigger;
        index=left;
    }
    else{
        H[right] =H[index];
        H[index] = bigger;
        index=right;
    }
    
    downHeap(index);
}

/*배열에 저장된 키 인쇄*/
void printArray(){
    
    for(int i=1;i<=heapsizeforprint;i++){
        printf("%d ",H[i]);
    }
    printf("\n");
}

void inPlaceheapSort(){ // 제자리 정렬
    

    heapsizeforprint=n;
    for(int i=n; i>=2; i--){
        
        int big =H[1];
        H[1] = H[i];
        H[i] = big;
        n--;
        
        downHeap(1);
        
    }
}
