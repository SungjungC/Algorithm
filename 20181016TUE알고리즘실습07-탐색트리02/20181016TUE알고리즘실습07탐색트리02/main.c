//
//  main.c
//  20181016TUE알고리즘실습07탐색트리02
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
    int height;
    int key;
}node;

typedef struct AVLtree{
    struct node *root;
}tree;

void insert(tree *T, int key);
void searchAndFixAfterInsertion(node *w);
void updateHeight(node *w);
bool isBalanced(node *w);
bool restructure(node *x, node *y, node *z);
bool isInternal(node *w);
bool isExternal(node *w);
node* treeSearch(node *v,int key);
int removeElement(tree *T,int key);
void searchAndFixAfterRemoval(node *w);
node* reduceExternal(tree *T, node *z);
node* sibling (node *w);
node* inOrderSucc(node *w);

int main(int argc, const char * argv[]) {
    
    char op =' ';// 입력 연산의 종류
    int key;
    tree T =*(tree*)malloc(sizeof(tree));
    T.root =(node*)malloc(sizeof(node));
    
    T.root = NULL;
    
    while(op!='q'){
        //getchar(); // 공백 또는 개행문자 읽기
        scanf("%c", &op);// 연산 종류fd
        
        switch (op) {
                
            case 'i': // 삽입
                scanf("%d", &key);
       
                break;
            case 's': // 탐색
                scanf("%d", &key);
                break;
            case 'p': // 인쇄
                break;
            case 'q':// 종료
                break;
        }
    }
    
    return 0;
}


void insertItem(tree *T, int key){/*기존의 트리에 새 노드를 삽입하고, searchAndFixAfterInsertion() 함수를 이용하
                                   여 균형검사 및 수리를 수행*/
    
    node* w =(node*)malloc(sizeof(node));
    
    if(T->root == NULL){ //아무것도 없으면
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
        expandExternal(w);
        searchAndFixAfterInsertion(w);
        return;
    }
}
node* treeSearch(node *v,int key){ //트리에서 원하는 키 값을 찾았는지를 출력
    
    if(isExternal(v)) return v;
    
    if(v->key == key) return v;
    
    else if(key <  v->key) return treeSearch(v->lChild, key);
    
    else //k > v.key
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
    
    node* w =treeSearch(T->root, key);
    node *zs;
    
    if(isExternal(w)) return printf("X");
    
    node *z = w->lChild;
    
    if(!isExternal(z)) z=w->rChild;
    
    if(isExternal(z)) {
        zs =reduceExternal(T,z);
    }
    
    else{
        node *y = inOrderSucc(w);
        z=y->lChild;
        w->key = y->key;
        zs =reduceExternal(T, z);
    }
    
    searchAndFixAfterRemoval(zs->parent);
    
    return key;
    
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
bool isExternal(node *w){ //노드가 외부노드인지 여부를 확인
    
    if(w->key == 0 )
        return true;
    else
        return false;
}
node* sibling (node *w){ //형제노드 반환
    
    if(w->parent->lChild == w)return w->parent->rChild;
    
    else //w.parent->rChild == w
        return w->parent->lChild;
}
node* inOrderSucc(node *w){ //중위순회 후계자를 찾아냄
    
    w =w->rChild;
    
    while(!isExternal(w)) w = w->lChild;
    
    return w;
    
}



void searchAndFixAfterInsertion(node  *w){/*균형검사를 수행하고 불균형이 있으면 개조를 통해 높이균형 속성을 회복*/
    
}




bool restructure(node *x, node *y, node *z){ /*3-노드 개조를 수행한 후 (갱신된) 3-노드의 루트를 반환*/
    return true;
}
void updateHeight(node *w){ /*노드의 높이를 갱신한 후 갱신 여부를 반환*/
    
}
bool isBalanced(node *w){ /*노드의 좌우자식 높이균형 여부 반환*/
    return true;
}



void searchAndFixAfterRemoval(node *w){
    
}
