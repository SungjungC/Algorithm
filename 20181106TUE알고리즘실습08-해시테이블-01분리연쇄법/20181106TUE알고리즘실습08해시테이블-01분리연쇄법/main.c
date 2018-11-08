//
//  main.c
//  20181106TUE알고리즘실습08해시테이블-01분리연쇄법
//
//  Created by 최성정 on 30/10/2018.
//  Copyright © 2018 최성정. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

typedef struct bucket{
    struct node* B;
}bucket;


typedef struct node{
    struct node* next;
    int element;
}node;

void initBucketArray(bucket *h,int M);
int hashfunction(int x, int M);
void insertItem(bucket *h, int x, int M);
void print(bucket *h, int M);
int search(bucket *h, int x, int M);
int delete(bucket *h, int x, int M);
void freebucket(bucket *h, int M);

int main(int argc, const char * argv[]) {
    
    int M, x; //배열크기 / 키값
    
    scanf("%d",&M);
    getchar();
    
    bucket *h=(bucket*)malloc(sizeof(bucket)*M);
    
    initBucketArray(h,M);
    
    char op =' ';
    
    while(op!='e'){
        
        scanf("%c",&op);
        
        switch (op) {
            case 'i':       //삽입
                scanf("%d",&x);
                insertItem(h,x,M);
                break;
            case 's':       //탐색
                scanf("%d",&x);
                search(h,x,M);
                break;
            case 'd':       //삭제
                scanf("%d",&x);
                delete(h, x, M);
                break;
            case 'p':       //출력
                print(h,M);
                break;
        }
        
    }
    
    freebucket(h,M);        //리스트 메모리해제
    
    free(h);        //배열 메모리해제
    
    return 0;
}
void initBucketArray(bucket *h,int M){ //초기화 함수
    
    for(int i=0; i<M; i++){
        h[i].B =NULL;
    }
}
int hashfunction(int x, int M){ //해쉬함수
    
    int h = x % M;
    
    return h;
    
}
void insertItem(bucket *h, int x, int M){
    
    int hx = hashfunction(x,M); //해쉬함수로 부터 해쉬값 얻어옴
    
    node *newnode =(node*)malloc(sizeof(node)); // 노드 동적할당
    
    newnode->element=x;
    newnode->next =NULL;
    
        node *p;    //다음 값 가리키는 포인터
        p = h[hx].B; //다음값 저장
        newnode->next = p; // newnode -> next에 다음 값
        h[hx].B =newnode; // newnode 를 배열에 넣어줌
    
}
void print(bucket *h, int M){
    
    node *p;
    
    for(int i=0;i<M; i++){  //배열 0부터 M-1까지 돌면서 출력
        
        p =h[i].B;
        
        while(p!=NULL){ // 값이 있으면
            printf(" %d",p->element); //출력
            p =p->next; //다음리스트 넣어주기
        }
    }
    
    printf("\n");
    
}
int search(bucket *h, int x, int M){
    
    int v =hashfunction(x, M);
    
    int k=1; // 위치가리키는 변수
    
    node *p =h[v].B;
    while(p){
        if(p->element == x)
            return printf("%d\n",k);
            
        else {
            k++;
            p = p->next;
        }
        
    }
    
    return printf("0\n"); //없으면 0 출력
}

int delete(bucket *h, int x, int M){
    
    int v =hashfunction(x, M);
    
    int k=1; //위치 출력할 변수
    
    node *p =h[v].B;
    node *pre =p;
    
    while(p){
        
       if(h[v].B->element == x){ //첫번째이면
            h[v].B = p->next;
            p = NULL;
            return printf("%d\n",k);
        }
        else if (p->element == x){
            pre->next =p->next;
            p= NULL;
            return printf("%d\n",k);
        }
        
        else {
            k++;
            pre =p;
            p = p->next;
        }
        
    }
    
    
    return printf("0\n"); //없으면 0 출력
    
}
void freebucket(bucket *h, int M){
    
    node *p, *temp; // 해제할 노드 p  , p 해제하고 p 다음값 저장할 temp
    
    for(int i=0; i<M; i++){
        
        if(h[i].B){    //메모리 해제할 값이 있을때
            p = h[i].B;
            
            while(p){ //p가 NULL이 아닐때까지
                temp = p->next; //p 다음 노드
                
                    free(p); //메모리해제하고
            
                p = temp; // p에 다시 다음 노드 temp넣어줌
            }
        }
    }
    
}
