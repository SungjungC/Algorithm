//
//  main.c
//  과제1-2다시
//
//  Created by 최성정 on 2018. 9. 17..
//  Copyright © 2018년 최성정. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {

    int n , s;
    
    scanf("%d",&n);   // 입력 노드 개수
    
   
    int *binary = malloc(sizeof(int)*n);
    
    int k=1;        // 2*k-1 : 전체 노드 개수
    
    for(int i=1; i<=n; i++){  //// 노드 입력 연산 반복.                 // 노드 입력 연산
        
        int x,y,z;
        
        scanf("%d %d %d",&x,&y,&z); //

            for(int j=1 ; j<=2*k-1 ; j++){
                // if(k == n) break;
                
                if(k==1){ // 첫번째
                binary[k] =x;
                binary[2*k] =y; //왼쪽 짝수
                binary[2*k+1]=z; //오른쪽 홀수
                     k++;
                    break;
                    }
                
                else{               // 첫번째아닐때
                    if(binary[j] == x){
                          binary[j*2]=y;
                        binary[j*2+1]=z;
                         k++;
                        break;
                    }
                }
            }
    }
    
    getchar();
    scanf("%d",&s);
    char searcharr[100] ={};
    
    for(int i=0; i<s; i++){  //// 연산 반복                         //// 탐색연산

            scanf("%s",searcharr);

        int j =0, num=1;
        
        printf("%d ",binary[num]);
        
        while(searcharr[j]){
            
            if(searcharr[j] =='L'){ ////왼쪽일때
                 num=num*2;
                printf("%d ",binary[num]);
               
            }
            else{       // 오른쪽일때
                num= num*2+1 ;
                printf("%d ",binary[num]);
               
                }
            j++;
        }
        printf("\n");
    }

    free(binary);
    return 0;

}

