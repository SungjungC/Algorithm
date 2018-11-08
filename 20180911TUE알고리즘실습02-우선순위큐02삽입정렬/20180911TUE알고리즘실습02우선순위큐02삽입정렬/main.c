//
//  main.c
//  20180911TUE알고리즘실습02-우선순위큐-삽입정렬
//
//  Created by 최성정 on 2018. 10. 9..
//  Copyright © 2018년 최성정. All rights reserved.
//
#include <stdio.h>
#include <stdlib.h>

int main(){
    int* arr;
    int N;
    int save, j;
    scanf("%d",&N);
    
    
    arr =(int *)malloc(sizeof(int)*N);
    
    for(int i=0; i<N; i++){
        scanf("%d", &arr[i]);
    }
  //////////////
    for(int i=1;i<N; i++){
        save =arr[i]; // 원래 자리의 수?를 save에 저장
        j =i-1; //바로전 숫자 비교위한 인덱스
        while(j>=0 && arr[j]>save){
            arr[j+1]=arr[j];            //큰수를 인덱스 j 에 복사 한칸씩 뒤로땡기는작업
            j--;
        }
        arr[j+1]=save;      //앞에 인덱스에 삽입!
    }
    
    for(int i=0; i<N; i++){
        printf("%d ", arr[i]);
    }
    
    free(arr);
    
    return 0;
}
