//
//  main.c
//  20181127TUE알고리즘실습12-방향그래프
//
//  Created by 최성정 on 24/11/2018.
//  Copyright © 2018 최성정. All rights reserved.
//

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>

typedef struct node{
    struct node *next;
    int element;
}node;

typedef struct vertex{
    char nameVertax;
    int inDegree;
    struct node *outEdges;
    struct node *inEdges;
}vertex;

typedef struct G{
    struct vertex * vertices;
    struct edge * edges;
}G;

typedef struct edge{
    int origin;
    int destination;
}edge;

int n; //정점
int m; //간선

//in[]
int *topOrder; //크기 n+1 배열

int *Q; // 정점들의 대기열
int front = -1;
int rear = -1;

struct G buildGraph(void);
int funcindex(char vName, G graph);
struct G insertVertex(char vName,int i,G graph);
struct G insertDirectedEdge(char uName, char wName, int i, G graph);
void insertFirst(node *H, int i);
int* topologicalSort(int *topOrder, G graph);
bool isEmpty(int *Q);
void enqueue(int v, int *Q);
int dequeue(int *Q);
void freegraph(G graph);



int main(int argc, const char * argv[]) { //방향그래프 정보로부터 그래프를 구축한 후 위상순서를 구하거나, 방향 싸이클 존재를 보고한 후 종료
    
    
    G graph = buildGraph();
    
    topOrder =(int*)malloc(sizeof(int)*n);
    
    topologicalSort(topOrder, graph); // graph 위상정렬
    
    if(topOrder[0] == 0) // 방향사이클 존재
        printf("0");
    
    else{
        for(int i=1; i<n+1; i++){
            printf("%c ",graph.vertices[topOrder[i]].nameVertax);
        }
    }
    
    freegraph(graph);
    //free(topOrder);
    //free(Q);
    
    return 0;
}

struct G buildGraph(){ //표준 입력으로부터 방향그래프 정보를 읽어 들여 그래프 G에 저장
    
    scanf("%d",&n);
    getchar();
    G graph;
    
    vertex *vertices =(vertex*)malloc(sizeof(vertex)*n);
    
    graph.vertices =vertices;
    
    for(int i=0; i<n;i++){
        char vName;
        scanf("%c",&vName);
        getchar();
        insertVertex(vName, i, graph);
    }
    
    scanf("%d",&m);
    getchar();
    
    edge *edges =(edge*)malloc(sizeof(edge)*m);
    graph.edges = edges;
    
    for(int i=0; i<m; i++){
        char uName, wName;
        scanf("%c %c",&uName, &wName);
        getchar();
        insertDirectedEdge(uName, wName, i, graph);
    }
    
    return graph;
}
int funcindex(char vName, G graph){ // vName에 해당하는 정점의 인덱스를 찾아 반환
    
    for(int i =0; i<n;i++){
        if(graph.vertices[i].nameVertax == vName)
            return i ;
    }
    
    return -1;
    
}
struct G insertVertex(char vName,int i,G graph){ //vName 정점 i를 G의 정점리스트에 삽입하고 i의 진입차수를 초기화
    
    graph.vertices[i].nameVertax =vName; //정점 i의 이름 저장
    
    node * outheader =(node*)malloc(sizeof(node));
    node * inheader =(node*)malloc(sizeof(node));
    
    outheader->next = inheader->next = NULL;
    
    outheader->element = inheader->element = -1;
    
    graph.vertices[i].inEdges = inheader;
    graph.vertices[i].outEdges = outheader;
    graph.vertices[i].inDegree =0; //정점의 진입차수 초기화
    
    return graph;
}
struct G insertDirectedEdge(char uName, char wName, int i, G graph){
    
    /*uName 정점 u를 시점으로, wName 정점 w를 종점으로 하는 방향간선 i를, G의 간선리스트, u의 진출간선리스트, 그리고 w의 진입간선리스트에 각각 삽입하고 w의 진입차수를 갱신*/
    
    int u= funcindex(uName, graph); // uName 정점 배열 인덱스
    int w= funcindex(wName, graph); // wName 정점 배열 인덱스
    
    graph.edges[i].origin = u; //간선 i 시점으로 u 저장
    graph.edges[i].destination = w; //간선 i 종점으로 w 저장
    
    insertFirst(graph.vertices[u].outEdges, i);  //정점 u의 진출부착간선리스트에 i 삽입
    insertFirst(graph.vertices[w].inEdges, i); // 정점 w의 진입부착간선리스트에 i삽입
    
    graph.vertices[w].inDegree++;
    
    return graph;
}
void insertFirst(node *H, int i){ //H의 첫 노드 위치에 정수 i를 원소로 하는 노드를 삽입
    
    node * newnode = (node*)malloc(sizeof(node));
    
    newnode->element =i; //node 원소로 i 저장
    
   
        newnode->next =H->next; // 기존연결리스트를 newnode뒤에 연결
    
    H->next = newnode; //newnode를 H 첫 노드로
    
}
int* topologicalSort(int *topOrder, G graph){
    
    Q = (int*)malloc(sizeof(int)*n); //q 초기화
    int in[n];
    
    for(int i=0; i<n; i++){
        in[i] = graph.vertices[i].inDegree; //진입차수 0인 정점 큐에삽입
        
        if(in[i] ==0) //진입차수 0이면 큐에 삽입
            enqueue(i, Q);
    }
    
    int t = 1;
    
    while(!isEmpty(Q)){
        int u = dequeue(Q);
        topOrder[t] = u;
        t++;
        
        
        node *p = graph.vertices[u].outEdges->next;
        
        while(p){
            int e =p->element;
            int w =graph.edges[e].destination; // 간선 e의 종점
            in[w] = in[w]-1;
            if(in[w] == 0)
                enqueue(w, Q);
            p = p->next;
        }
    }
    
    if(t<=n) // 아직 위상순서 안매겨진 정점 존재하면
        topOrder[0] = 0; // non-DAG
    else
        topOrder[0] = 1; // DAG
    
    return topOrder;
}
bool isEmpty(int *Q){ //Q가 비어 있으면 True, 아니면 False를 반환
    
    if(front == rear)
        return true;
    else
        return false;
}
void enqueue(int v, int *Q){
    rear = rear + 1;
    Q[rear] = v;
    
}
int dequeue(int *Q){
    
    front = front + 1;
    return Q[front];
    
}
void freegraph(G graph){
    
    for(int i=0; i<n; i++){
        
        node *p =graph.vertices[i].inEdges;
        
        while(p!=NULL){
            
            node * temp =p->next;
            free(p);
            p = temp;
        }
        
        p =graph.vertices[i].outEdges;
        
        while(p!=NULL){
            
            node * temp =p->next;
            free(p);
            p = temp;
        }
        
    }
    
    free(graph.vertices);
    free(graph.edges);
   
}
