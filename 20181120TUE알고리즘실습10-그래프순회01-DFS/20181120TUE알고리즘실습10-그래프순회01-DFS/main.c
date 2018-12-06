//
//  main.c
//  20181120TUE알고리즘실습10-그래프순회01-DFS
//
//  Created by 최성정 on 17/11/2018.
//  Copyright © 2018 최성정. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

typedef struct graph {
    struct vertax * vertices;
    struct edge *edges;
}graph;

typedef struct vertex{
    int nameVertax;
    struct node * head;
}vertex;

typedef struct node{
    struct node * next;
    int indice;
}node;

typedef struct edge{
    int vertexIndiceA;
    int vertexIndiceB;
    int visit;
}edge;

void makeVertexArray(vertex *vertices, int vertexsize);
void makeList2(int num, int vindex, int v2index, edge *edges,vertex *vertices);
void makeEdge(edge *edges, int num, int a, int b );
void makeList(int num, edge *edges,vertex *vertices, int vertexsize, int edgesize);
void dfs(vertex *vertices, edge *edges, int s, int *arr);
void makevisited(edge * edges, node *p);
void freegraph(edge *edges, vertex *vertices, int* arr, int vertexsize);

int main() {
    
    int edgesize;
    int vertexsize;
    int S;
    
    scanf("%d %d %d",&vertexsize,&edgesize,&S); //정점 간선 출발정점번호
    
    vertexsize = vertexsize+1;
    
    vertex *vertices =(vertex*)malloc(sizeof(vertex)*vertexsize);
    edge *edges =(edge*)malloc(sizeof(edge)*edgesize);
    int *arr =(int*)malloc(sizeof(int)*vertexsize);
    
    for(int i=1; i<vertexsize;i++){
        arr[i]=0;
    }
    
    makeVertexArray(vertices,vertexsize); // Vertex 넣기
    
    for(int i=0;i<vertexsize;i++){ //헤더노드 연결
        node *header = (node*)malloc(sizeof(node));
        vertices[i].head =header;
        header->next = NULL;
    }
    
    int i=0;
    
    while(i<edgesize){
        
        makeList(i, edges, vertices, vertexsize, edgesize); // 리스트를 vertices 연결시키기
        
        i++;
    }
    
    printf("%d\n",S);
    
    arr[S]=1;
    
    
    dfs(vertices, edges, S, arr);
    
    
    freegraph(edges, vertices, arr, vertexsize); // 메모리해제
    
    return 0;
}


void makeVertexArray(vertex *vertices, int vertexsize){ // 정점 초기화 함수
    
    /* vertex 넣기*/
    for(int i=1; i<vertexsize;i++)  // 정점에 정점숫자 넣기 (정점인덱스번호 = 정점숫자)
    {
        vertices[i].nameVertax = i;
        vertices[i].head =NULL; // 헤더에는 일단 NULL로 초기화
    }
    
}
void makeEdge(edge *edges, int num, int a, int b ){
    
    edges[num].vertexIndiceA = a;
    edges[num].vertexIndiceB = b;
    edges[num].visit =0; // 방문안한 노드 0 으로 초기화
    
}
void makeList2(int num, int vindex, int v2index, edge *edges,vertex *vertices){
    
    node *p =vertices[vindex].head; // head를 가리키게 함
    node *pre =p;
    
    
    node * newnode =(node*)malloc(sizeof(node));
    newnode->indice = num;
    
    while(p!=NULL){
        // 넣을 위치 탐색해야함
        if(p->next == NULL){ //  노드 연결 마지막일때
            p->next = newnode;
            newnode->next = NULL;
            return;
        }
        
        else{           //중간에 넣을 때
            pre =p;
            p = p->next;
            
            int compareindex = p->indice;
            
            int comp = edges[compareindex].vertexIndiceA == vindex ?
            edges[compareindex].vertexIndiceB : edges[compareindex].vertexIndiceA;
            
            if(comp > v2index){ //이전꺼가 입력한것보다 크면
                pre->next =newnode;
                newnode->next = p;
                return;
            }
            
        }
    }
    
    pre->next = newnode;
    newnode->next = p;
    
}
void makeList(int num, edge *edges,vertex *vertices, int vertexsize, int edgesize){ // 리스트 연결하는 함수
    
    int a, b;
    
    scanf("%d %d",&a,&b);
    
    makeEdge(edges, num, a, b);
    
    makeList2(num, a, b, edges,vertices);
    makeList2(num, b, a, edges,vertices);
    
}
void dfs(vertex *vertices, edge *edges, int s, int *arr){
    
    node * p = vertices[s].head->next;
    
    while(p){
        int adnode;
        int index=p->indice; // edge의 인덱스 값 저장
        
        adnode = (edges[index].vertexIndiceA==s) ?
        (edges[index].vertexIndiceB) : (edges[index].vertexIndiceA); // 인접 정점을 넣음
        
        if(arr[adnode]==0){
            printf("%d \n", adnode);
            
            arr[adnode]=1;
            dfs(vertices, edges, adnode, arr);
        }
        edges[index].visit = 1;
        
          p = p->next;
    }
  
}
void freegraph(edge *edges, vertex *vertices, int* arr, int vertexsize){ // 그래프 메모리 해제
    
    for(int i=0; i<vertexsize;i++){
        
        node *p = vertices[i].head;
        node *temp;
        
        while(p!=NULL){
            temp = p->next;
            free(p);
            p = temp;
        }
    }
    
    free(edges);
    free(arr);
    free(vertices);
    
}
