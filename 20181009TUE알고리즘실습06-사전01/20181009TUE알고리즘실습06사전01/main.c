//
//  main.c
//  20181009TUE알고리즘실습06사전01
//
//  Created by 최성정 on 2018. 10. 3..
//  Copyright © 2018년 최성정. All rights reserved.
//


///// 함수에서는 계산만 하고 return 값줘서 main에서 print

#include <stdio.h>
#include <stdlib.h>


void rFE(int k, int l, int r, int* arr );

int main() {
    
    int N; // 사전의 키 개수
    int K; //탐색 키
    
    scanf("%d", &N);
    scanf("%d", &K);
    
    int *arr = (int*)malloc(sizeof(int) * N); // 키 저장할 배열 동적할당
    
    for (int i = 0; i < N; i++)  // 키 개수 입력받은만큼 for문 돌면서 키 저장
    {
        scanf("%d",&arr[i]);
    }
    
    if( K < arr[0]) { // 정렬되어있는 정수키의 가장 작은 수보다 K가 작으면 -1 출력
        printf("-1"); return 0;
    }
    
    rFE(K, 0, N-1, arr); // 키값, 시작인덱스, 마지막인덱스, 전체배열
    
    free(arr); // 동적할당 해제
    
    return 0;
    
}

void rFE(int k, int l, int r, int* arr ){
    
    int mid;
    
    mid = (l + r)/2; // 중간 값
    
    /* l==r 일때 찾는 값이 중간값보다 같거나 작지않으면 else 로 들어가서 -> l > r */
    if (l > r){ printf("%d",r); return; }
    
    if (k == arr[mid]) { //찾는 키값과 중간값이 같으면 출력
        printf("%d",mid);
        return;
    }
    
    else if(k < arr[mid]) // 찾는 키값이 중간값보다 작으면 마지막인덱스에 mid-1
        rFE(k, l, mid-1, arr);
    
    else // (k >arr[mid]) // 찾는 키값이 중간값보다 크면 시작인덱스에 mid+1
        rFE(k, mid + 1, r, arr);
    
}
