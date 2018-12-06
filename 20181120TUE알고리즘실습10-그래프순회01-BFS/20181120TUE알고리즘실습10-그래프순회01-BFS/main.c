//
//  main.c
//  20181120TUE알고리즘실습10-그래프순회01-BFS
//
//  Created by 최성정 on 21/11/2018.
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
    int visit;
}edge;



void makeVertexArray(vertex *vertices, int vertexsize);
void putEdge(edge *edges, int a, int b, int num);
void makeMatrix(int num, edge *edges, int** matrix, int vertexsize, int edgesize);
void freegraph(edge *edges, vertex *vertices, int **matrix, int vertexsize, int *arr);

void bfs(int **matrix, edge *edges, int s, int *arr, int vertexsize);
int main() {
    
    
    int edgesize;
    int vertexsize;
    int S;
    
    scanf("%d %d %d",&vertexsize,&edgesize,&S);
    

     vertexsize = vertexsize+1;
    
    edge *edges =(edge*)malloc(sizeof(edge)*edgesize);
    vertex *vertices =(vertex*)malloc(sizeof(vertex)*vertexsize);
    int *arr =(int*)malloc(sizeof(int)*vertexsize);
    
    for(int i=1; i<vertexsize;i++){
        arr[i]=0;
    }
    
    int **matrix;
    matrix = (int**)malloc(sizeof(int*) * vertexsize );
    
    for(int i=0; i<vertexsize; i++){
        matrix[i] = (int*) malloc ( sizeof(int) * vertexsize );
    }
    
    makeVertexArray(vertices, vertexsize); // Vertex 넣기

    int i =0;
    
    for(int k=1; k<vertexsize; k++)
        for(int l=1; l<vertexsize; l++){
            matrix[k][l] = -1;
        }
    
    
    while(i<edgesize){
        
        makeMatrix(i, edges, matrix, vertexsize, edgesize);
        
        i++;
    }
    
    bfs(matrix, edges, S, arr, vertexsize);
    
    
    freegraph(edges, vertices, matrix, vertexsize, arr); // 메모리해제
    
    
    return 0;
}

void makeVertexArray(vertex *vertices, int vertexsize){
    
    /* vertex 넣기*/
    for(int i=1; i<vertexsize;i++)
    {
        vertices[i].nameVertax = i;
        vertices[i].head =NULL;
    }
    
}
void putEdge(edge *edges, int a, int b, int num){
    
    edges[num].vertexIndiceSmall = a;
    edges[num].vertexIndiceBig = b;
    edges[num].visit =0; // 방문안한 노드 0 으로 초기화
    
    
}
void makeMatrix(int num, edge *edges, int** matrix, int vertexsize, int edgesize){
    
    int a, b;
    
    scanf("%d %d",&a,&b);
    putEdge(edges, a, b, num);
    
    
    matrix[a][b] = num;
    matrix[b][a] = num;
    
}
void freegraph(edge *edges, vertex *vertices, int **matrix, int vertexsize, int *arr){
    
    for(int i=0; i<vertexsize;i++){
        
        free(matrix[i]);
    }
    free(matrix);
    free(edges);
    free(vertices);
    
}

void bfs(int **matrix, edge *edges, int s, int *arr, int vertexsize){

    int front =0, rear =0, pop;
    int *visit =(int*)malloc(sizeof(int)*vertexsize);
    
    for(int i=0; i<vertexsize; i++){
        visit[i]=0;
    }
    printf("%d ", s);
    
    arr[0] = s;
    rear++;
    visit[s]=1;
    
    while(front<rear){
        pop=arr[front];
        front++;
        
        for(int i=1; i<vertexsize;i++){
            if(matrix[pop][i] != -1 && visit[i]==0){
                printf("%d\n",i);
                arr[rear]=i;
                rear++;
                visit[i]=1;
            }
        }
    }
    
    
    free(visit);
   
    
}
