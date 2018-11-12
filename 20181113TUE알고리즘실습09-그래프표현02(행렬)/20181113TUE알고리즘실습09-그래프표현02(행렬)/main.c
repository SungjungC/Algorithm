//
//  main.c
//  20181113TUE알고리즘실습09-그래프표현02(행렬)
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

typedef struct edge{
    int vertexIndiceSmall;
    int vertexIndiceBig;
    int weight;
}edge;


int edgesize =21;
int vertexsize =7;

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
void makeMatrix(edge *edges, int** matrix){
    
    
    for(int k=1; k<vertexsize; k++){
        for(int l=1; l<vertexsize; l++){
            
            matrix[k][l] = -1;
            
            
            for(int i=0;i<edgesize;i++){
                
                if((edges[i].weight!=0 && edges[i].vertexIndiceBig == k && edges[i].vertexIndiceSmall ==l) ||  (edges[i].weight!=0 && edges[i].vertexIndiceBig == l && edges[i].vertexIndiceSmall ==k)){
                    matrix[k][l] = i;
                }
            }
        }
    }
    
}
void nodenumber(int num, edge *edges, int **matrix){ // 인접노드 + 가중치 출력
    
    if(num<1 || num>=vertexsize) {
        printf("-1\n");
        return;
    }
    
    for(int i=1; i<vertexsize; i++){
        int index = matrix[num][i];
        
        if(index!=-1){
            printf(" %d %d",i,edges[index].weight);
        }
    }
    
    printf("\n");
    
}
void changeweight(int a,int b,int w,edge *edges, int** matrix){
    
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
    
    makeMatrix(edges, matrix);
    
}
void freegraph(edge *edges, vertex *vertices, int **matrix){
    
    for(int i=0; i<vertexsize;i++){
        
        free(matrix[i]);
    }
    free(matrix);
    free(edges);
    free(vertices);
    
}


int main() {
    
    char op;
    int num;
    
    scanf("%c",&op);
    
    edge *edges =(edge*)malloc(sizeof(edge)*edgesize);
    vertex *vertices =(vertex*)malloc(sizeof(vertex)*vertexsize);
    
    int **matrix;
    matrix = (int**)malloc(sizeof(int*) * vertexsize );
    
    for(int i=0; i<vertexsize; i++){
        matrix[i] = (int*) malloc ( sizeof(int) * vertexsize );
    }
    
    
    
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
    
    
    makeMatrix(edges, matrix);
    
    int a, b, w;
    
    while(op!='q'){
        
        switch (op) {
            case 'a': // 인접한 노드번호 가중치 노드번호 가중치
                scanf("%d",&num);
                nodenumber(num, edges, matrix);
                break;
            case 'm':
                scanf("%d %d %d",&a,&b,&w);
                getchar();
                changeweight(a, b, w, edges, matrix);
                break;
        }
        scanf("%c",&op);
    }
    
    freegraph(edges, vertices, matrix);
    
    return 0;
}
