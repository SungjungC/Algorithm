//
//  main.c
//  과제5
//
//  Created by 최성정 on 27/11/2018.
//  Copyright © 2018 최성정. All rights reserved.
//
#include<stdio.h>
#include <stdlib.h>




typedef struct node{
    int connectvertex;
    int weight;
    struct node * next;
}node;

void makevertex(node *vertices, int vertexsize);
void makegraph(node *vertices, int a, int b, int weight);
void printWandN(node *vertices, int num, int vertexsize);
void changeWeight(node *vertices, int a, int b, int weight, int vertexsize);
void putgraph(node * vertices);
void freegraph(node * vertices, int vertexsize);
int main() {
    
    int vertexsize =7; //정점 개수 + 1 (0 사용 X)
    
    char op;    // 명령어 a / m / q
    int num;    // 출력할 노드 number
    
    scanf("%c",&op);
    
    node *vertices =(node*)malloc(sizeof(node)*vertexsize); // 노드 포인터 배열 동적할당
    
    makevertex(vertices, vertexsize); // 정점초기화
    
    putgraph(vertices); //그래프 만들기
    
    int a, b, w; // 정점 a b 와 가중치 w
    
    while(op!='q'){
        
        switch (op) {
            case 'a': // 인접한 노드와 가중치 출력
                scanf("%d",&num);
                printWandN(vertices, num, vertexsize);
                break;
            case 'm':   // 정점 a b 와 가중치 w 받아서 변경(삽입) or 삭제
                scanf("%d %d %d",&a,&b,&w);
                
                if(a>=vertexsize || a<1 || b>=vertexsize || b<1 ){ // 예외일때 -1 출력
                    printf("-1\n");
                    break;
                }
                
                changeWeight(vertices, a, b, w, vertexsize);
                changeWeight(vertices, b, a, w, vertexsize);
                getchar();
                
        }
        scanf("%c",&op);
    }
    
    freegraph(vertices, vertexsize); // 메모리해제

    
    return 0;
}


void makevertex(node *vertices, int vertexsize){ // (정점) 노드 포인터배열 초기화하는 함수
    
    for(int i=1;i<vertexsize;i++){
        vertices[i].next = NULL;    // 노드 포인터배열 next NULL로 초기화
    }
    
}

void putgraph(node * vertices){     // 그래프 간선과 가중치 입력하는 함수
    
    makegraph(vertices,1,2,1);
    makegraph(vertices, 2, 1, 1);
    makegraph(vertices,1,4,1);
    makegraph(vertices, 4, 1, 1);
    makegraph(vertices, 3, 1, 1);
    makegraph(vertices, 1, 3, 1);
    makegraph(vertices,1,6,2);
    makegraph(vertices, 6, 1, 2);
    makegraph(vertices,2,3,1);
    makegraph(vertices, 3, 2, 1);
    makegraph(vertices,3,5,4);
    makegraph(vertices, 5, 3, 4);
    makegraph(vertices,5,5,4);
    makegraph(vertices,5,6,3);
    makegraph(vertices, 6, 5, 3);
    
}


void makegraph(node *vertices, int a, int b, int weight){ // 그래프 만드는 함수
    
    node * newnode = (node*)malloc(sizeof(node)); // 새로운 노드할당
    
    newnode->weight =weight;    // 새로운 노드에 가중치 넣기
    newnode->connectvertex =b;  // 새로운 노드에 인접노드 넣기
    
    // 첫노드가 null일때 그냥 바로넣기
    if(vertices[a].next==NULL){
        vertices[a].next =newnode;  // vertices[a].next 에 바로 연결
        newnode->next = NULL;
    }
    
    else{ // 첫노드가 null 아니면
        
        node * p = vertices[a].next;    // 위치찾는 pivot노드
        node * temp =&vertices[a];  // 이전위치기억하는 temp 노드
        
        while(p!=NULL && b > p->connectvertex){
            // 인접노드 정점 값 b보다 크거나 null 아니면 다음노드로
            temp = p;
            p = p->next;
        }
        
        temp->next =newnode;    // 이전노드 next에 newnode 삽입
        newnode->next = p;      // newnode next에 p 삽입
        
    }
    
}


void printWandN(node *vertices, int num, int vertexsize){
    //  가중치와 인접노드 출력하는 함수
    
    if(num>=vertexsize || num<1){   // 범위 벗어나면 -1 출력
        printf("-1\n");
        return;
    }
    
    node *p =vertices[num].next; // 리스트 탐색하는 노드
    
    while(p){ // null일때까지 반복
        printf(" %d %d",p->connectvertex,p->weight);    // 인접노드와 가중치 출력
        p =p->next;
    }
    printf("\n");
    
}


void changeWeight(node *vertices, int a, int b, int weight, int vertexsize){
    // 가중치 변경하는 함수
    
    node *p =vertices[a].next;  // 탐색하는 노드
    node * temp =&vertices[a];  // 이전노드
    
    
    if(weight ==0){ // 있는거 없앨때
        
        while(p && p->connectvertex !=b){   // null이 아니고 b 찾을때까지
            temp = p;
            p =p->next;
        }
        
        if(temp->next !=NULL)   // 이전노드 temp -> next (p) 가 NULL 이 아니면
            temp->next = p->next;
        //이전노드 temp ->next에 없애는 노드 p->next 저장

        free(p);    // 없앤 노드 free 해주기
        
    }
    
    else{
        
        while (p && p->connectvertex !=b) { // NULL일때까지 or 바꾸는 인접노드 찾을때까지
            temp = p;
            p =p->next;     // 탐색
        }
        
        if(p){ // 이미 있는 인접노드의 가중치만 바꿀때
            
            p->weight =weight;  //
            
        }
        else{  // 없는거 만들때
            
            makegraph(vertices, a, b, weight);
            
        }
        
    }
}


void freegraph(node * vertices, int vertexsize){ //메모리해제
    
    
    for(int i=1; i<vertexsize; i++){
        
        node *p =vertices[i].next;  // 리스트탐색하는 노드 p
        
        
        while(p){
            node *temp =p->next;    // 다음리스트 주소 가지고 있는 temp
            free(p);    // p 메모리해제
            p = temp;   // 다음리스트주소 다시 p에 넣고 메모리해제
        }
    }
    
    free(vertices); // 노드 포인터 배열 메모리해제
    
}
