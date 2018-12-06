//
//  main.c
//  과제5-2
//
//  Created by 최성정 on 30/11/2018.
//  Copyright © 2018 최성정. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>



void putweight(int **matrix, int vertexS,int vertexB, int weight, int vertexsize){
    // 그래프 가중치 삽입하는 함수
    
    matrix[vertexB][vertexS] =weight;
    matrix[vertexS][vertexB] =weight;
    
}


void makeMatrix(int vertexsize, int** matrix){
    // 그래프 초기화 하는 함수
    
    
    for(int k=1; k<vertexsize; k++){
        for(int l=1; l<vertexsize; l++){
            
            matrix[k][l] = 0;
        
        }
    }
    
}


void nodenumber(int num, int vertexsize, int **matrix){ // 인접노드 + 가중치 출력
    
    if(num<1 || num>=vertexsize) {  // 범위 벗어나면 -1 출력
        printf("-1\n");
        return;
    }
    
    for(int i=1; i<vertexsize; i++){
        int weight = matrix[num][i];
        
        if(weight!=0){  // 간선이 연결되어있으면 (0이 아니면)
            printf(" %d %d",i,weight);  // 인접노드와 가중치 출력
        }
    }
    
    printf("\n");
    
}


void changeweight(int a,int b,int w, int vertexsize, int** matrix){
    //  가중치 변경하는 함수
    
    if(a<1 || b<1 || a>=vertexsize || b>=vertexsize) { // 범위벗어나면 -1 출력
        printf("-1\n");
        return;
    }
    
    // 가중치변경 + 0이면 가중치 넣기 + 가중치있을때 0으로 만들기
    matrix[a][b] = w;
    matrix[b][a] = w;
    
}


void freegraph(int vertexsize, int **matrix){
    
    // 메모리해제하는 함수
    
    for(int i=0; i<vertexsize;i++){
        free(matrix[i]);
    }
    free(matrix);
    
}


int main() {
    
    char op;    // 명령어 a / m / q
    int num;    // 출력할 노드 number
    
    
    int vertexsize =7; //  정점개수 + 1 (0 사용안하므로)
    
    scanf("%c",&op);
    
    int **matrix;
    matrix = (int**)malloc(sizeof(int*) * vertexsize ); // 행렬 만들기위해 동적할당
    
    for(int i=0; i<vertexsize; i++){
        matrix[i] = (int*) malloc ( sizeof(int) * vertexsize ); // 2차원배열로 동적할당
    }
    
    
    makeMatrix(vertexsize,matrix); // 행렬 초기화
    
    
    // 그래프 만들기
    putweight(matrix, 1, 2, 1, vertexsize);
    putweight(matrix, 1, 3, 1, vertexsize);
    putweight(matrix, 1, 4, 1, vertexsize);
    putweight(matrix, 1, 6, 2, vertexsize);
    putweight(matrix, 2, 3, 1, vertexsize);
    putweight(matrix, 3, 5, 4, vertexsize);
    putweight(matrix, 5, 5, 4, vertexsize);
    putweight(matrix, 5, 6, 3, vertexsize);
   
    int a, b, w;
    
    while(op!='q'){
        
        switch (op) {
            case 'a': // 인접한 노드와 가중치 출력
                scanf("%d",&num);
                nodenumber(num,vertexsize, matrix);
                break;
            case 'm':   // 정점 a b 와  w 받아서 변경(삽입) or 삭제
                scanf("%d %d %d",&a,&b,&w);
                getchar();
                changeweight(a, b, w, vertexsize, matrix);
                break;
        }
        scanf("%c",&op);
    }
    
    freegraph(vertexsize, matrix); // 메모리해제
    
    
    
    
    getchar();
    getchar();
    getchar();
    
    return 0;
}
