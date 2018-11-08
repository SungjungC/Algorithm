//
//  main.c
//  20181106TUE알고리즘실습08-해시테이블-02선형조사법
//
//  Created by 최성정 on 05/11/2018.
//  Copyright © 2018 최성정. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int Hash(int x, int M);
bool isEmpty(int b);
int getNextBucket(int v,int i, int M);
void insertItem(int k, int M,int* H);
void initBucketArray(int *H,int M);
int findElement(int k, int M, int *H);

int main(int argc, const char * argv[]) {
    
    int M, N, x; // 해시테이블 크기 M, x 갯수,x
    char op=' ';
    scanf("%d",&M);
    scanf("%d",&N);
    getchar();
    
    int *H =(int*)malloc(sizeof(int)*M); //해시테이블 동적할당
    
    initBucketArray(H,M); //초기화
    
    while (op != 'e'){
        
        scanf("%c", &op);
        
        switch (op) {
            case 'i':
                scanf("%d", &x);
                insertItem(x,M,H);          // 삽입
                break;
            case 's':
                scanf("%d", &x);
                findElement(x,M,H);         // 탐색
                break;
            case 'e':
                break;
        }
    }
    free(H);
}

int Hash(int x, int M){
    
    return x % M;
    
}
void initBucketArray(int *H,int M){ // 버켓배열 초기화하는 함수
    
    for(int i=0; i<M; i++){
        H[i]=0; //0으로 초기화
    }
    
}
bool isEmpty(int b){
    if(b ==0) return true;
    else return false;
}


int getNextBucket(int v,int i, int M){
    return (v+i) % M;
}

void insertItem(int k, int M,int* H){
    
    int v =Hash(k, M); //해시함수 넣고 얻은 값 v에 저장
    
    int i = 0;
    
    int b;
    
    while(i<M){ //해시테이블 크기보다 작을 때까지
        
        b=getNextBucket(v,i,M); //다음 버켓 찾아서 b
        
        if(isEmpty(H[b])){  //비어있으면
            H[b]=k;
            printf("%d\n",b);
            return;
        }
        else    //충돌
            printf("C");
        i++;
    }
    
    return;
    
}

int findElement(int k, int M, int *H){  //탐색
    
    int v =Hash(k, M); //해시함수 넣고 얻은 값
    int i =0;
    
    while(i<M){
        int b =getNextBucket(v, i, M); //다음 버켓
        
        if(isEmpty(H[b])){  //비어있으면
            return printf("-1\n");
        }
        else if(k ==H[b]){ // 찾으면
            return printf("%d %d\n",b,H[b]);
        }
        else i++; // 못찾으면
    }
    return printf("-1\n");
}
