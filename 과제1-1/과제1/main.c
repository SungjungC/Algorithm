//
//  main.c
//  과제1
//
//  Created by 최성정 on 2018. 9. 13..
//  Copyright © 2018년 최성정. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    char elem;
    struct Node *prev;
    struct Node *next; }Node; // 노드 정의
typedef struct List
{
    Node* header;
    Node* trailer;

}List;

void init_list(List *list); //초기화
void add(List list, int position,char item); //삽입
void delete(List list, int position); //삭제
void get_entry(List list,int position); //참조
void print(List list); //출력
void free_list(List *list); //메모리해제

int main(){
    List list;      // 리스트 선언
    
    char op, item;// 입력 연산의 종류, 아이템
    int position; // 입력 위치
    int num_op; // 연산의 개수
    
    init_list(&list);// 리스트 초기화 (헤더, 트레일러 노드 할당 및 초기화)
    
    scanf("%d", &num_op); // 연산 개수 입력
    
    for( int i=0; i < num_op; ++i ){
        getchar(); // 공백 또는 개행문자 읽기
        scanf("%c", &op);// 연산 종류
        
        switch (op) {
                
            case 'A': // 삽입
                scanf("%d %c", &position, &item);
                add(list, position, item);
                break;
            case 'D': // 삭제
                scanf("%d", &position);
                delete(list, position);
                break;
            case 'G': // 참조
                scanf("%d", &position);
                get_entry(list, position);
                break;
            case 'P':
                print(list); // 출력
                break;
                
        }
    }
    free_list(&list); // 리스트의 노드 해제
    
    return 0;
}

void init_list(List *list){ //리스트 초기화 (헤더, 트레일러 노드 할당 및 초기화)
    
    list->header = (Node*)malloc(sizeof(Node)); //헤더 할당
    list->trailer = (Node*)malloc(sizeof(Node));    //트레일러 할당
    
    list->header->next =list->trailer; // 헤더의 next에 트래일러 주소
    list->trailer->prev = list->header; // 트레일러의 prev에 헤더 주소
    list->trailer->next = NULL;
    
    
}

void add(List list, int position,char item){ //삽입
    struct Node * newnode = NULL; // NULL로 초기화
    
    int ind = 0;
    struct Node * pivotNode = list.header;
    
    while(pivotNode){
        ind++;
        // pivotNode는 헤더 바로 다음 노드
        pivotNode = pivotNode->next;
        
        
        if(position == ind){   // ind와 position이 같을 때
            newnode = malloc(sizeof(struct Node));
            newnode->elem = item;
            newnode->prev = pivotNode->prev;
            pivotNode->prev->next = newnode;
            
            if( pivotNode == list.trailer ) {// trailer 일 때
                list.trailer->prev = newnode;
                newnode->next = list.trailer;
            } else {
                pivotNode->prev = newnode;
                newnode->next = pivotNode;
            }
            break;
        }
        
    }
    
    if( newnode == NULL ) {
        printf("invalid position \n");
    }
    
}

void delete(List list, int position) { //삭제
    
    int ind = 0;
    struct Node * pivotNode = list.header;
    
    while(pivotNode) {
        ind++;
        // pivotNode는 헤더 바로 다음 노드
        pivotNode = pivotNode->next;
        
        if( pivotNode == list.trailer ) { // pivotNode가 trailer 일 때
            printf("invalid position \n");
            break;
        }
        
        if(position == ind){   // ind와 position이 같을 때
            
            pivotNode->prev->next = pivotNode->next;
            pivotNode->next->prev = pivotNode->prev;
            
            break;
        }
    }
    
}

void get_entry(List list,int position) { //참조
    
    Node* pivot = list.header; //참조할 노드
    
    int ind = 0;
    
    while(1) {
        ind++;
        pivot = pivot->next;
        if ( pivot == list.trailer){       // position이 노드 갯수보다 클때
            printf("invalid position \n");
            break;
        }
        if (position == ind){   // ind와 position이 같을 때
            printf("%c \n",pivot->elem);   // 값 참조
            break;
        }
        
        
    }
}

void print(List list){ //출력
    
    Node* pivot = list.header;
    int ind = 0;
    
    while(pivot) {
        pivot = pivot->next;
        if ( pivot == list.trailer ) { break;}
        ind++;
        printf("%c",pivot->elem);
        
    }
    
    printf("\n");
}

void free_list(List* list){  //리스트 노드 해제
    
    Node* pivot = list->header;
    
    while(pivot) {
        Node* temp = pivot->next; // 그 다음주소를 저장
        
        if( pivot != NULL ) {
            free(pivot);
            pivot = NULL;
        }
        
        if( temp == NULL ) { // is trailer.
            break;
        }
        
        pivot = temp;
    }
}

