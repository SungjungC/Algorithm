//
//  main.c
//  20181009TUE알고리즘실습06사전03
//
//  Created by 최성정 on 2018. 10. 7..
//  Copyright © 2018년 최성정. All rights reserved.
//

#include<stdio.h>
#include<stdlib.h>

int main(void) {

    int A, B, num; // 시작, 끝, Y/N 개수
    
    scanf("%d %d %d ", &A, &B, &num);
    
    char YN; // Yes인지No인지
    
    int M; // 중간값
    
    for(int i=0; i<num;i++){
        scanf("%c",&YN);
        
        M =(A+B)/2; // 중간 값 넣음
        
        if(YN=='N'){ // No일 때
            B = M;    // 끝이 중간값
        }
        else{ // Yes일때 YN == 'Y'일 때
            A= M+1; // 처음이 중간값+1
        }
    }
    
    printf("%d", A);
 
    return 0;
}
