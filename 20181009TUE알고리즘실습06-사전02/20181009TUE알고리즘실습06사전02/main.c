//
//  main.c
//  20181009TUE알고리즘실습06사전02
//
//  Created by 최성정 on 2018. 10. 3..
//  Copyright © 2018년 최성정. All rights reserved.
//
//// while문 조건문으로 해서 밖에서 print 하게


#include<stdio.h>
#include<stdlib.h>

//이진탐색 반복문

int main(void) {
    
    int N; // 사전의 키 개수
    int K; //탐색 키
    
    scanf("%d", &N);
    scanf("%d", &K);
    
    int *arr = (int*)malloc(sizeof(int) * N); // 키 저장할 배열 동적할당
    int mid;
    int start, end;
    
    for (int i = 0; i < N; i++) // 키 개수 입력받은만큼 for문 돌면서 키 저장
    {
        scanf("%d",&arr[i]);
    }
    
    if( K > arr[N-1]) { // 사전에서 마지막키 보다 K 가 크면 마지막 인덱스 출력
        printf("%d",N); return 0;
    }
    
    start =0; //시작 인덱스
    end =N-1; // 끝 인덱스
    
    while (1){
        mid = (start + end)/2; // 중간 값
        
        /*end == start == mid 다음에도 k가 중간값과 같지않고
         k가 중간값보다 작으면 end = mid -1 이 들어가서 end < start = mid 가 됨*/
        if (end < start){ printf("%d",start); return 0; }
        
        if (K == arr[mid]){ break;} // 같은 값 찾으면 while문 벗어나서 프린트
        
        (K < arr[mid]) ? (end = mid - 1) : (start = mid + 1) ;
        /*K가 중간 값보다 작으면  end 인덱스가 mid-1 로 while문 실행 //
         크면 start 인덱스가 mid +1 로 실행 */
    }
    
    printf("%d ", mid);//몇번째인지 인덱스 출력 (같은 값일 때)
    
    free(arr);
   
    return 0;
}
