//
//  main.c
//
//  우선순위큐 - 선택정렬
//
//  Created by 최성정 on 2018. 9. 10..
//  Copyright © 2018년 최성정. All rights reserved.
//
#include <stdio.h>
#include <stdlib.h>

int main() {
    
    int *arr;
    
    int N, max, maxloc;
    
    scanf("%d",&N);     // 배열 크기
    
    arr=(int*)malloc(sizeof(int)*N);    // 크기 N 배열 동적할당
    
    for(int i=0; i<N; i++){
        scanf("%d",&arr[i]);    //배열값 입력
    }
    
///////

    for(int i=N-1; i>0 ; i--){      //배열 0 부터 시작이니까  마지막 -> N-1 !!!
        
        maxloc= i;
        
        for(int j=i-1; j>=0; j--){
            
            if(arr[j]>arr[maxloc])maxloc=j;
        }
        
        max = arr[maxloc];
        arr[maxloc]=arr[i];
        arr[i]=max;
    }
    
    for(int i =0; i<N ; i++){
        printf("%d ", arr[i] );
    }
    
    free(arr);
    
    return 0;
}
