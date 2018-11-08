//
//  main.c
//  20180918TUE알고리즘실습03-힙과힙정렬2
//
//  Created by 최성정 on 2018. 9. 18..
//  Copyright © 2018년 최성정. All rights reserved.
//


#include <stdio.h>
#include <stdlib.h>


int H[100];  // 힙
int n;  //힙의 크기



void downHeap(int index);
void printHeap();
//void rBuildHeap(int index);
void buildHeap();

int main() {
    
    
    scanf("%d",&n);
    
    getchar();
    
    for(int i=1;i<=n; i++){
        scanf("%d",&H[i]);
    }
    
    //rBuildHeap(n);
    
    buildHeap();
    
    printHeap();

    return 0;
}


/*키를 정렬 (삭제시) downHeap*/
void downHeap(int index){
    
    if(H[2*index]==NULL && H[2*index+1]==NULL) return;
    
    int bigger = H[2*index];
    
    if(H[2*index+1]){
        if(bigger <H[2*index+1]){
            bigger =H[2*index+1];
        }
    }
    
    if(H[index]>bigger) return;
    
    if(H[2*index] ==bigger){ //왼쪽이면
        H[2*index] =H[index];
        H[index] = bigger;
        index=2*index;
    }
    else{
        H[2*index+1] =H[index];
        H[index] = bigger;
        index=2*index+1;
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


/*재귀 방식으로 상향식 힙 생성*/
/*void rBuildHeap(int index){
    
    
    
}
*/

/*비재귀 방식으로 상향식 힙 생성*/
void buildHeap(){
    
    int x=n;
    
    for(int i=(int)(x/2); i>=1; i--){
        downHeap(i);
    }

}
