//
//  main.c
//  제출
//
//  Created by 최성정 on 2018. 9. 17..
//  Copyright © 2018년 최성정. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;

typedef struct Node
{
    struct Node* left;
    struct Node* right;
    ElementType data;
} Node;

Node* CreateRootNode(ElementType rootnum, ElementType leftnum, ElementType rightnum);
void CreateNode(Node* node, ElementType leftnum, ElementType rightnum);
void DestroyNode(Node* node);
void DestroyTree(Node* root);
void PreOrderPrintTree(Node* node, ElementType rootnum, ElementType leftnum, ElementType rightnum);
int showleft(Node* node);
int showright(Node* node);

int main()
{
    int n , s;
    
    scanf("%d",&n);   // 입력 노드 개수
    
    int x,y,z;
    
    scanf("%d %d %d",&x,&y,&z);
    
    Node* rootnode = CreateRootNode(x, y, z);
    
    for(int i=2; i<=n; i++){  //// 노드 입력 연산 반복               // 노드 입력 연산
        
        scanf("%d %d %d",&x,&y,&z);
        
        PreOrderPrintTree(rootnode,x,y,z);
        
    }
    
    getchar();
    scanf("%d",&s);
    char searcharr[100] ={};
    
    for(int i=0; i<s; i++){  //// 연산 반복                         //// 탐색연산
        
        scanf("%s",searcharr); //탐색 값
        
        int j=0;
        printf("%d ",rootnode->data);
        
        Node *showingnode =rootnode;
        
        while (searcharr[j]) {
            
            if(searcharr[j]=='L'){
                
                int showing =showleft(showingnode);
                printf("%d ",showing);
                showingnode =showingnode->left;
            }
            
            else{
                int showing =showright(showingnode);
                printf("%d ",showing);
                showingnode=showingnode->right;
                
            }
            
            
            j++;
        }
        printf("\n");
        
    }
    
    // 메모리 해제
    DestroyTree(rootnode);
    
    return 0;
}


/* 루트 생성 */
Node* CreateRootNode(ElementType rootnum, ElementType leftnum, ElementType rightnum)
{
    // 노드를 위한 메모리 할당
    Node* newNode = (Node*) malloc(sizeof(Node));
    newNode->left = (Node*) malloc(sizeof(Node));
    newNode->right = (Node*) malloc(sizeof(Node));
    
    if(leftnum !=0)newNode->left->data = leftnum;
    else newNode->left = NULL;
    
    if(rightnum !=0)newNode->right->data = rightnum;
    else newNode->right = NULL;
    
    newNode->data = rootnum;
    
    return newNode;
    
}
/* 노드 생성 */
void CreateNode(Node* node, ElementType leftnum, ElementType rightnum)
{
    
    node->left =(Node*) malloc(sizeof(Node));
    node->right=(Node*) malloc(sizeof(Node));
    
    if(leftnum !=0)node->left->data = leftnum;
    else node->left = NULL;
    
    if(rightnum !=0)node->right->data = rightnum;
    else node->right = NULL;
    
    
}
/* 노드 파괴 */
void DestroyNode(Node* node)
{
    free(node);
}

/* 트리 파괴(후위 순회 활용) */
void DestroyTree(Node* root)
{
    if(root == NULL)
        return;
    
    // 왼쪽 하위 트리 소멸
    DestroyTree(root->left);
    
    // 오른쪽 하위 트리 소멸
    DestroyTree(root->right);
    
    // 루트 노드 소멸
    DestroyNode(root);
}

/* 전위 순회 순서로 넣을자리 찾기 */
void PreOrderPrintTree(Node* node, ElementType rootnum, ElementType leftnum, ElementType rightnum)
{
    if(node == NULL)
        return;
    
    if(node->data == rootnum) {// x값을 트리에서 찾으면 노드 생성
        CreateNode(node, leftnum, rightnum);
    }
    
    // 왼쪽 하위 트리로 순회
    PreOrderPrintTree(node->left, rootnum, leftnum, rightnum);
    
    // 오른쪽 하위 트리 출력
    PreOrderPrintTree(node->right, rootnum, leftnum, rightnum);
}

/* 왼쪽 값*/
int showleft(Node* node){
    
    return node->left->data;
    
}
/* 오른쪽 값*/
int showright(Node* node){
    
    return node->right->data;
}
