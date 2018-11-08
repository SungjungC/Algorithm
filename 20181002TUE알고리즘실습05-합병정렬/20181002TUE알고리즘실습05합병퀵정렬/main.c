//
//  main.c
//  20181002TUE알고리즘실습05합병정렬
//
//  Created by 최성정 on 2018. 10. 1..
//  Copyright © 2018년 최성정. All rights reserved.
//
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct Node {
    struct Node *next;
    int key;
}Node;

Node *getnode() {
    Node *node;
    node = (Node*)malloc(sizeof(Node));
    node->next = NULL;
    return node;
    
}
void insert(Node *p, int n, int posi) {
    Node *q;
    int i;
    q = getnode();
    q->key = n;
    for (i = 0; i<posi; i++)
        p = p->next;
    p->next = q;
    
}
Node *merge(Node *list1, Node *list2) {
    Node *result = NULL;
    Node *q, *a = list1, *b = list2;
    
    a = list1;
    b = list2;
    
    if (a->key < b->key) {
        result = a;
        a = a->next;
    }
    else {
        result = b;
        b = b->next;
    }
    
    q = result;
    
    while (a != NULL && b != NULL) {
        if (a->key < b->key) {
            q->next = a;
            a = a->next;
            q = q->next;
        }
        else {
            q->next = b;
            b = b->next;
            q = q->next;
        }
    }
    
    if (a == NULL) {
        q->next = b;
        b = b->next;
    }
    else {
        q->next = a;
        a = a->next;
    }
    
    q = result;
    
    return result;
}

Node * mgpartition(Node *a, int num) {
    
    Node *head_b;
    Node *cur;
    int i;
    
    cur = a;
    
    for (i = 0; i<num - 1; i++) {
        cur = cur->next;
    }
    
    head_b = cur->next;
    cur->next = NULL;
    
    return head_b;
}

Node * mmergesort(Node *list) {
    int n = 0;
    Node *cnt;
    Node *b;
    Node * t1, *t2, *result = list;
    cnt = list;
    while (cnt != NULL) {
        n = n + 1;
        cnt = cnt->next;
    }
    if (n < 2) {
        return list;
    }
    
    b = mgpartition(list, n / 2);
    
    t1 = mmergesort(list);
    t2 = mmergesort(b);
    
    result = merge(t1, t2);
    
    return result;
}

int main(int argc, const char * argv[]) {
    int i, key, N;
    Node *p, *list;
    p = getnode();
    list = p;
    scanf("%d", &N);
    scanf("%d", &key);
    p->key = key;
    for (i = 0; i<N - 1; i++) {
        scanf("%d", &key);
        insert(p, key, i);
    }
    
    p = mmergesort(list);
    
    while (p != NULL) {
        printf(" %d", p->key);
        p = p->next;
    }
    printf("\n");
}
