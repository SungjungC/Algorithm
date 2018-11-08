//
//  main.c
//  20180911TUE알고리즘실습02-우선순위큐03
//
//  Created by 최성정 on 2018. 10. 9..
//  Copyright © 2018년 최성정. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int* selectArray(int* arrselect, int N );
int* insertArray(int* arrinsert, int N );

int main(){
    int *arrselect, *arrinsert, *arrReverse;
    int N;
    time_t startTime=0, endTime=0;
    float gapS,gapI, gapSarr, gapIarr, gapSR, gapIR;
    
    scanf("%d",&N);
    
    arrselect =(int*)malloc(sizeof(int)*N);
    arrinsert =(int*)malloc(sizeof(int)*N);
    arrReverse =(int*)malloc(sizeof(int)*N);
    
    for(int i=0; i<N; i++){
        arrselect[i]=rand();
    }
    
    for(int i=0; i<N; i++){
        arrinsert[i]=rand();
    }
    
    //선택정렬
    startTime=clock();
    *arrselect =*selectArray(arrselect,N);
    endTime=clock();
    gapS =(float)(endTime-startTime);
    
    //삽입정렬
    startTime=clock();
    *arrinsert=*insertArray(arrinsert,N);
    endTime=clock();
    gapI =(float)(endTime-startTime);
    
    // 선택정렬 정렬데이터
    startTime=clock(); //시간 측정시작
    *arrselect =*selectArray(arrselect,N);
    endTime=clock();   //시간 측정 끝
    gapSarr =(float)(endTime-startTime);
    
    // 삽입정렬 정렬데이터
    startTime=clock(); //시간 측정시작
    *arrinsert=*insertArray(arrinsert,N);
    endTime=clock();   //시간 측정끝
    gapIarr =(float)(endTime-startTime);
    
    // 역순정렬
    for(int i=0; i<N; i++){
        arrReverse[i]=arrinsert[N-i-1];
    }
    
    // 선택정렬 역순
    startTime=clock();
    *arrReverse =*selectArray(arrReverse,N);
    endTime=clock();
    gapSR =(float)(endTime-startTime);
    
    //다시 역순정렬
    for(int i=0; i<N; i++){
        arrReverse[i]=arrinsert[N-i-1];
    }
    
    //삽입정렬 역순
    startTime=clock();
    *arrReverse=*insertArray(arrReverse,N);
    endTime=clock();
    gapIR =(float)(endTime-startTime);
    
    printf("선택정렬 랜덤데이터 :%.2f \n",gapS);
    printf("선택정렬 정렬데이터 :%.2f \n",gapSarr);
    printf("선택정렬 역순데이터 :%.2f \n", gapSR);
    
    printf("삽입정렬 랜덤데이터 :%.2f \n",gapI);
    printf("삽입정렬 정렬데이터 :%.2f \n", gapIarr);
    printf("삽입정렬 역순데이터 :%.2f\n", gapIR);
    
    free(arrReverse);
    free(arrinsert);
    free(arrselect);
    
    return 0;
}

/*선택정렬*/
int* selectArray(int* arrselect, int N ){
    
    int savelocS, saveS;        //선택정렬 위치 저장 변수 / 값 저장 변수
    
    for(int i=N-1; i>=0;i--){
        savelocS =i;
        
        for(int j=i-1;j>=0;j--){
            if(arrselect[j]>arrselect[savelocS])savelocS = j;
        }
        
        saveS=arrselect[savelocS];
        arrselect[savelocS]=arrselect[i];
        arrselect[i]=saveS;
    }
    
    return arrselect;
    
}

/*삽입정렬*/
int* insertArray(int* arrinsert, int N ){
    
    int saveI, insertJ;
    for(int i=1; i<N; i++){
        saveI = arrinsert[i];
        insertJ = i-1;
        while(insertJ>=0 && arrinsert[insertJ]>saveI){
            arrinsert[insertJ+1]=arrinsert[insertJ];
            insertJ--;
        }
        arrinsert[insertJ+1]=saveI;
    }
    
    return arrinsert;
    
}
