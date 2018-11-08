//
//  main.c
//  20181016TUE알고리즘실습07탐색트리01
//
//  Created by 최성정 on 15/10/2018.
//  Copyright © 2018 최성정. All rights reserved.
//

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct node{
    struct node *lChild;
    struct node *rChild;
    struct node *parent;
    int key;
}node;

typedef struct tree{
    struct node *root;
}tree;

bool isExternal(node *w);
bool isInternal(node *w);
void findElement(tree *T,int key);
void insert(tree *T, int key);
int removeElement(tree *T,int key);
node* inOrderSucc(node *w);
node* sibling (node *w);
node leftChild(node *w);
node rightChild(node *w);
node* treeSearch(node *v, int key);
void expendExternal(node *w);
node* reduceExternal(tree *T, node *z);
void preorderprint(node *N);

int main() {
    
    char op =' ';// 입력 연산의 종류
    int key;
    tree *T = (tree*)malloc(sizeof(tree));
    T->root = NULL;
    
    
    while(op!='q'){
        //getchar(); // 공백 또는 개행문자 읽기
        scanf("%c", &op);// 연산 종류fd
        
        switch (op) {
                
            case 'i': // 삽입
                scanf("%d", &key);
                insert(T, key);
                break;
            case 'd': // 삭제
                scanf("%d", &key);
                removeElement(T,key);
                break;
            case 's': // 탐색
                scanf("%d", &key);
                findElement(T,key);
                break;
            case 'p': // 인쇄
                preorderprint(T->root);
                printf("\n");
                break;
            case 'q':// 종료
                break;
        }
    }
    
    free(T);
    
    return 0;
}

void insert(tree *T, int key){ //기존의 트리에 새 노드를 삽입
    
    node* w =(node*)malloc(sizeof(node));
    
    if(T->root == NULL){
        T->root = (node*)malloc(sizeof(node));
        T->root->lChild =(node*)malloc(sizeof(node));
        T->root->rChild =(node*)malloc(sizeof(node));
        T->root->key =key;
        T->root->parent = NULL;
        T->root->lChild->parent = T->root->rChild->parent =T->root;
        T->root->lChild->key =T->root->rChild->key =0;
        
        return;
    }
    
    w = treeSearch(T->root, key);
    
    if(isInternal(w)) return; //내부노드이면
    
    else{
        w->key = key;
        expendExternal(w);
    }
}

node* treeSearch(node *v,int key){ //트리에서 원하는 키 값을 찾았는지를 출력
    
    if(isExternal(v)) return v; // 노드가 외부노드이면 그대로 반환
    
    if(v->key ==key) return v; // 트리에 키값이 있으면 반환
    
    else if(key <  v->key) return treeSearch(v->lChild, key); //키값이 현재노드보다 작으면 왼쪽
    
    else //k > v.key // 키값이 현재 노드보다 크면 오른쪽
        return treeSearch(v->rChild,key);
}

bool isInternal(node *w){ //노드가 내부노드인지 여부를 확인
    
    if(w->key != 0 )
        return true;
    
    else return false;
}

void expendExternal(node *w){ //외부노드 확장
    
    node *l =(node*)malloc(sizeof(node));
    node *r =(node*)malloc(sizeof(node));
    l->key = r->key =0;
    l->lChild = l->rChild =r->lChild =r->rChild =NULL;
    l->parent = r->parent =w;
    w->lChild =l;
    w->rChild =r;
}

int removeElement(tree *T,int key){ //기존의 트리에서 노드를 삭제한 후 원소를 반환
    
    node *w = treeSearch(T->root, key); //노드위치 찾아서 w 저장
    
    if(isExternal(w)) return printf("X\n"); // NoSuchKey
    
    node *z = w->lChild;
    
    if(!isExternal(z)) z =w->rChild; //왼쪽자식이 외부노드 아니면 오른쪽노드 저장
    
    if(isExternal(z)) reduceExternal(T,z); // z가 외부노드이면 외부노드 감소
    
    else{ //외부노드이면
        z = inOrderSucc(w); //중위순회로 후계자 자식 찾아서 z에 저장
        node *y = z->parent; // y에 외부노드 z의 부모저장 (후계자)
        
        //삭제한 원소 위치에 후계자 복사
        w->key = y->key;
    
        reduceExternal(T, z); // 외부노드 z 감소
    }
    return printf("%d\n",key);
}

bool isExternal(node *w){ //노드가 외부노드인지 여부를 확인
    
    if(w->key == 0 )
        return true;
    else
        return false;
}

node* inOrderSucc(node *w){ //중위순회 후계자를 찾아냄
    
    w =w->rChild;
    
    while(!isExternal(w)) w = w->lChild;
    
    return w;
    
}

node* reduceExternal(tree *T, node *z){ //외부노드 감소
    
    node *w =z->parent;
    node *zs = sibling(z);
    
    if(w == T->root){
        T->root =zs;
        zs->parent = NULL;
    }
    else{
        node *g = w->parent;
        zs->parent = g;
        if(w == g->lChild)
            g->lChild = zs;
        else // w == g.right
            g->rChild = zs;
    }
    return zs;
}

node* sibling (node *w){ // 형제노드 반환
    
    if(w->parent->lChild == w)return w->parent->rChild;
    
    else //w.parent->rChild == w
        return w->parent->lChild;
}

void findElement(tree *T,int key){ // 키값을 찾기위해 트리탐색
    
    if(T->root ==NULL) {
        printf("X\n");
        return;
    }
    
    node *w =treeSearch(T->root,key);
    
    if(isExternal(w)){
        
        printf("X\n"); //// NoSuchKey
        return;
    }
    
    else printf("%d\n",w->key);
}

//전위순회
void preorderprint(node *N){
    if(N->key != 0)
    {
        printf("%d ", N->key);  // 노드 방문
        preorderprint(N->lChild);            // 왼쪽 서브트리 순회
        preorderprint(N->rChild);           // 오른쪽 서브트리 순회
    }
}

