//
//  main.c
//  20181106TUE알고리즘실습08-해시테이블-03이중해싱
//
//  Created by 최성정 on 06/11/2018.
//  Copyright © 2018 최성정. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


void insertItem(int x, int M,int* H, int q);
int Hash(int x, int M);
int HashP(int x, int q);
int getNextBucket(int v,int i, int x, int M, int q);
void print(int *H, int M);
bool isEmpty(int b);
void initBucketArray(int *H,int M);
int findElement(int x, int M, int *H, int q);


int main(int argc, const char * argv[]) {
    
    int M,N,q, x;
    char op=' ';
    scanf("%d",&M); //해시테이블크기
    scanf("%d",&N); //최대 삽입 개수
    scanf("%d",&q); // (M보다 작은 소수)
    getchar();
    
    int *H =(int*)malloc(sizeof(int)*M); //배열 동적할당
    
    initBucketArray(H,M); //초기화

    while (op !='e'){
        scanf("%c", &op);
        
        switch (op) {
            case 'i':
                scanf("%d", &x); //키값입력받아서
                insertItem(x,M,H,q);          // 삽입
                break;
            case 's':
                scanf("%d", &x);
                findElement(x,M,H,q); //  탐색
                break;
            case 'p':
                print(H,M);
                break;
        }
    }
    
    print(H,M);
    
    free(H);
}

void initBucketArray(int *H,int M){ //배열 초기화 함수
    
    for(int i=0; i<M; i++){
        H[i]=0;
    }

}
int Hash(int x, int M){ //해쉬함수 
    
    return x % M;
    
}

int HashP(int x, int q){ //두번째 해쉬함수
    int hashp = q - (x % q);
    return hashp;
}

int getNextBucket(int v,int i, int x, int M, int q){ // 배열 인덱스 얻어오는 함수
    
    int hashp =HashP(x,q);
    
    return (v + i*hashp ) % M;
    
}
void insertItem(int x, int M,int* H, int q){ //삽입함수
    
    int v =Hash(x, M); //해쉬함수로 값얻어와서 v 에 저장
    int i =0;
    int b;
    
    while(i<M){
        b=getNextBucket(v,i,x,M,q); // 두번째 해시함수에 넣어서 배열 인덱스 얻어옴
        if(isEmpty(H[b])){  //비어있으면
            H[b]=x; //삽입
            printf("%d\n",b); //주소값 출력
            return;
        }
        else  {  //충돌
            printf("C");
            i++;
        }
    }
    
    return;
    
}
int findElement(int x, int M, int *H, int q){ //찾는 함수
    
    int v =Hash(x, M); //해시함수 넣어서 값 저장
    int i =0;
    int b;
    
    while(i<M){
        b =getNextBucket(v,i,x, M, q); // 인덱스 얻어옴
       
        if(isEmpty(H[b])){  //비어있으면
            return printf("-1\n");
        }
        else if(x ==H[b]){ // 찾으면
            return printf("%d %d\n",b,H[b]);
        }
        else i++;   //못찾으면
    }
    return printf("-1\n"); // 못찾으면
}
void print(int *H, int M){
    
    for(int i=0;i<M;i++){
        printf(" %d",H[i]);
    }
    
    printf("\n");
}
bool isEmpty(int b){
    if(b ==0) return true;
    else return false;
}


