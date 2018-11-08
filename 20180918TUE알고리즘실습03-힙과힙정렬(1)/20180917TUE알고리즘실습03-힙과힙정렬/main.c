//
//  main.c
//  20180917TUE알고리즘실습03-힙과힙정렬
//
//  Created by 최성정 on 2018. 9. 17..
//  Copyright © 2018년 최성정. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

int H[100];  // 힙
int n;  //힙의 크기

void insertItem(int key);
int removeMax();
void upHeap(int index);
void downHeap(int index);
void printHeap();

int main() {        // 반복적으로 i, d, p 명령에 따라 insertItem, removeMax, printHeap 함수를 각각 호출 수행 / q 명령 입력 시 종료
    
    int key;
 
    char op;
    
    while(1){
        scanf("%c",&op);
        
        switch (op) {
            case 'i':
                scanf("%d",&key);
                insertItem(key);
                break;
            case 'd':
                printf("%d\n",removeMax());
                break;
            case 'p':
                printHeap();
                break;
            case 'q':
                exit(0);
        }
    }
    return 0;
}

/* 키를 힙에 삽입*/
void insertItem(int key){   // 키를 힙에 삽입하고 0을 인쇄
   
        H[++n]=key;
        upHeap(n);
    
    printf("0\n");
}

/*키를 힙에서 삭제*/
int removeMax(){ // 힙에서 루트 키를 삭제하고 반환된 키를 인쇄
    
    int rootkey=H[1];
    
    H[1]=H[n];
    H[n]=0;
    n=n-1;
    downHeap(1);
    
    return rootkey;
}

/*키를 정렬 (삽입시) upHeap*/
void upHeap(int index){
    
    if(index==1) return;
   
    if(H[index] <= H[index/2] ) return;      //부모노드가 삽입노드보다 크면 return
    
    int parent =H[index/2];
    
    H[index/2] =H[index];
    H[index] =parent;
    
    index=index/2;
    
    upHeap(index);
    
}
/*키를 정렬 (삭제시) downHeap*/
void downHeap(int index){
    
    int left = 2*index;
    int right = left+1;
    
    if(H[left]==0 && H[right]==0) return; //양쪽 자식노드가 없으면
    
    int bigger = H[left];   //왼쪽을 넣고
    
    if(H[right]){       //오른쪽 노드가있으면
        if(bigger <H[right]){       // 오른쪽이 왼쪽보다 클때
            bigger =H[right];
        }
    }
    
    if(H[index]>bigger) return; // 부모노드가 자식노드(bigger)보다 크면
    
    if(H[left] ==bigger){ //왼쪽이면
        H[left] =H[index];
        H[index] = bigger;
        index=left;
    }
    else{       // 오른쪽이면
        H[right] =H[index];
        H[index] = bigger;
        index=right;
    }
    
    downHeap(index);
    
}

/*힙의 내용 인쇄*/
void printHeap(){
    
    for(int i=1;i<=n;i++){
        printf("%d ",H[i]);
    }
     printf("\n");
}
