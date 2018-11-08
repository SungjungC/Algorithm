//
//  main.c
//  과제2
//
//  Created by 최성정 on 2018. 9. 27..
//  Copyright © 2018년 최성정. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int* selectArray(int* arrselect, int N, int* num);
int* insertArray(int* arrinsert, int N, int* num);


int main(){
    int *arrselect, *arrinsert, *arrReverse;    //배열 선언
    int N;
    time_t startTime=0, endTime=0;  //시간측정 시작시간 & 끝나는 시간
    
    /*실험 1 변수 : 데이터 값에 따른 걸리는 시간*/
    float gapS, gapI, gapSarr, gapIarr, gapSR, gapIR;
    
    /* 실험 2 변수 : 데이터값에 따른 반복문 도는 횟수 */
    int NUMS=0, NUMI=0, NUMSARR=0, NUMIARR=0, NUMSR=0, NUMIR=0;
    
    scanf("%d", &N);
    
    arrselect =(int*)malloc(sizeof(int)*N); //배열 메모리 할당
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
    *arrselect =*selectArray(arrselect, N, &NUMS);
    endTime=clock();
    gapS =(float)(endTime-startTime);
    
    //삽입정렬
    startTime=clock();
    *arrinsert=*insertArray(arrinsert, N, &NUMI);
    endTime=clock();
    gapI =(float)(endTime-startTime);
    
    // 선택정렬 정렬데이터
    startTime=clock();
    *arrselect =*selectArray(arrselect, N, &NUMSARR);
    endTime=clock();
    gapSarr =(float)(endTime-startTime);
    
    // 삽입정렬 정렬데이터
    startTime=clock();
    *arrinsert=*insertArray(arrinsert, N, &NUMIARR);
    endTime=clock();
    gapIarr =(float)(endTime-startTime);
    
    // 역순정렬
    for(int i=0; i<N; i++){
        arrReverse[i]=arrinsert[N-i-1];
    }
    
    // 선택정렬 역순
    startTime=clock();
    *arrReverse =*selectArray(arrReverse, N,  &NUMSR);
    endTime=clock();
    gapSR =(float)(endTime-startTime);
    
    //다시 역순정렬
    for(int i=0; i<N; i++){
        arrReverse[i]=arrinsert[N-i-1];
    }
    
    //삽입정렬 역순
    startTime=clock();
    *arrReverse=*insertArray(arrReverse, N, &NUMIR);
    endTime=clock();
    gapIR =(float)(endTime-startTime);
    /*실험 1*/
    printf("선택정렬 랜덤데이터 :%.2f \n",gapS);
    printf("선택정렬 정렬데이터 :%.2f \n",gapSarr);
    printf("선택정렬 역순데이터 :%.2f \n", gapSR);
    printf("삽입정렬 랜덤데이터 :%.2f \n",gapI);
    printf("삽입정렬 정렬데이터 :%.2f \n", gapIarr);
    printf("삽입정렬 역순데이터 :%.2f\n", gapIR);
     /*실험 2*/
    printf("선택정렬 랜덤데이터 :%d \n",NUMS);
    printf("선택정렬 정렬데이터 :%d \n",NUMSARR);
    printf("선택정렬 역순데이터 :%d \n", NUMSR);
    printf("삽입정렬 랜덤데이터 :%d \n",NUMI);
    printf("삽입정렬 정렬데이터 :%d \n", NUMIARR);
    printf("삽입정렬 역순데이터 :%d \n", NUMIR);
    
    /*배열 메모리 해제*/
    free(arrReverse);
    free(arrinsert);
    free(arrselect);
    
    return 0;
}

/*선택정렬*/
int* selectArray(int* arrselect, int N, int* num ){
    
    int savelocS, saveS;        //큰 값의 위치 저장변수 ,  값 저장 변수
    
    for(int i=N-1;i>=0;i--){
        savelocS =i;
        
        for(int j=i-1;j>=0;j--){
            /*값이 크면 값을 교환할 위치저장*/
            if(arrselect[j]>arrselect[savelocS])savelocS = j;
            (*num)++;
        }
        
        /* 값 교환 */
        saveS=arrselect[savelocS];
        arrselect[savelocS]=arrselect[i];
        arrselect[i]=saveS;
    }
    
    return arrselect;
    
}

/*삽입정렬*/
int* insertArray(int* arrinsert, int N, int* num ){
    
    int saveI, insertJ;
    for(int i=1; i<N; i++){
        saveI = arrinsert[i];   /// 원래 자리의 수를 save에 저장
        insertJ = i-1;          //바로전 숫자 비교위한 인덱스
        while(insertJ>=0 && arrinsert[insertJ]>saveI){
            arrinsert[insertJ+1]=arrinsert[insertJ]; //큰수를 복사
            insertJ--;
            (*num)++;
        }
        arrinsert[insertJ+1]=saveI; //앞에 인덱스에 삽입
    }
    
    return arrinsert;
    
}
