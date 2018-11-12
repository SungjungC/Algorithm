//
//  main.c
//  20181113TUE알고리즘실습09-그래프표현01(리스트)
//
//  Created by 최성정 on 12/11/2018.
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
    int vertexIndiceSmall;
    int vertexIndiceBig;
    int weight;
}edge;


int edgesize =21;
int vertexsize =7;

void makeVertexArray(vertex *vertices);
void putweight(edge *edges, int vertexS, int vertexB, int weight);
void putEdge(edge *edges);
void makeList(edge *edges,vertex *vertices);
void nodenumber(int num, edge *edges, vertex *vertices);
void changeweight(int a, int b, int w, edge *edges, vertex *vertices);
void freegraph(edge *edges, vertex *vertices);


int main() {
    
    char op;
    int num;
    
    scanf("%c",&op);
    
    edge *edges =(edge*)malloc(sizeof(edge)*edgesize);
    vertex *vertices =(vertex*)malloc(sizeof(vertex)*vertexsize);
    
    
    makeVertexArray(vertices); // Vertex 넣기
    
    putEdge(edges); // edge에 정점번호 넣기
    
    
    putweight(edges, 1, 2, 1);
    putweight(edges, 1, 3, 1);
    putweight(edges, 1, 4, 1);
    putweight(edges, 1, 6, 2);
    putweight(edges, 2, 3, 1);
    putweight(edges, 3, 5, 4);
    putweight(edges, 5, 5, 4);
    putweight(edges, 5, 6, 3);
    
    
    makeList(edges, vertices);
    
    int a, b, w;
    
    while(op!='q'){
        
        switch (op) {
            case 'a': // 인접한 노드번호 가중치 노드번호 가중치
                scanf("%d",&num);
                nodenumber(num, edges, vertices);
                break;
            case 'm':
                scanf("%d %d %d",&a,&b,&w);
                getchar();
                changeweight(a, b, w, edges,vertices);
                break;
        }
        scanf("%c",&op);
    }
    
    freegraph(edges, vertices);
    
    return 0;
}
void makeVertexArray(vertex *vertices){
    
    /* vertex 넣기*/
    for(int i=1; i<vertexsize;i++)
    {
        vertices[i].nameVertax = i;
        vertices[i].head =NULL;
    }
    
}
void putweight(edge *edges, int vertexS,int vertexB, int weight){
    
    for(int i=0;i<edgesize;i++){
        
        for(int j=1;j<vertexsize;j++){
            for(int k=j;k<vertexsize;k++){
                
                if(edges[i].vertexIndiceBig==vertexB && edges[i].vertexIndiceSmall==vertexS)
                    edges[i].weight =weight;
            }
        }
    }
    
}
void putEdge(edge *edges){
    
    int i=0;
    while(i<edgesize){
        for(int j=1;j<vertexsize;j++){
            for(int k=j;k<vertexsize;k++){
                
                edges[i].vertexIndiceSmall = j;
                edges[i].vertexIndiceBig = k;
                edges[i].weight =0;
                i++;
            }
        }
    }
}
void makeList(edge *edges,vertex *vertices){
    
    for(int i=0;i<vertexsize;i++){ //헤더노드
        node *header = (node*)malloc(sizeof(node));
        vertices[i].head =header;
        header->next = NULL;
    }
    
    for(int j=1; j<vertexsize; j++){
        
        node *p =vertices[j].head;
        
        for(int i=0;i<edgesize;i++){
            
            if((edges[i].vertexIndiceSmall ==j || edges[i].vertexIndiceBig == j) && edges[i].weight !=0){
                
                node * newnode =(node*)malloc(sizeof(node));
                newnode->indice = i;
                p->next = newnode;
                p =p->next;
            }
        }
        
        p=NULL;
        
    }
}
void nodenumber(int num, edge *edges, vertex *vertices){ // 인접노드 + 가중치 출력
    
    if(num<1 || num>=vertexsize) {
        printf("-1\n");
        return;
    }
    
    node *p =vertices[num].head->next;
    
    while(p){
        
        int index=p->indice;
        int adnode = (edges[index].vertexIndiceBig==num) ?
        (edges[index].vertexIndiceSmall) : (edges[index].vertexIndiceBig);
        
        
        printf(" %d %d",adnode,edges[index].weight);
        
        p = p->next;
    }
    
    printf("\n");
    
}
void changeweight(int a,int b,int w,edge *edges,vertex *vertices){
    
    if(a<1 || b<1 || a>=vertexsize || b>=vertexsize) {
        printf("-1\n");
        return;
    }
    
    int big = a>b ? a : b;
    int small = a>b ? b : a;
    int index, ori;
    
    for(int i=0; i<edgesize; i++)
        if(edges[i].vertexIndiceSmall == small && edges[i].vertexIndiceBig == big) {
            ori = edges[i].weight;
            edges[i].weight = w;
            index =i;
        }
    
    makeList(edges, vertices);
    
}
void freegraph(edge *edges, vertex *vertices){
    
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
    free(vertices);
    
}
