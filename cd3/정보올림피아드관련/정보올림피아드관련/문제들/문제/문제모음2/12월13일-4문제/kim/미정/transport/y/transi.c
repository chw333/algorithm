#include <stdio.h> 
#include <math.h> 
#include <ctype.h> 
 
#define MAXR 60 
#define MAXC 10 
#define MT   600 /* MT = MAXR * MAXC */ 
 
int    NOSUP, //공급지의 수
       NODEM, //수요지의 수
	   CP,    // NOSUP+NODEM-1
	   CT,
	   INIT,  //초기 가능해 선택
	   IPR,   //출력형태 선택
	   N9,IPR,IT, 
       MOVEX[MT],MOVEY[MT],OPT,MINI,MINJ,NOWI,NOWJ,INDIC; 
double C[MAXR][MAXC], //파일에서 읽은 공급지에서 수요지의 비용
       FLOW[MAXR][MAXC], 
       SUPPLY[MAXR], S1[MAXR], //각 공급지의 공급량
	   DEMAND[MAXC], D1[MAXC], //각 수요지의 수요량
	   BC[MAXR][MAXC], 
       U[MAXR], V[MAXC], EC[MAXR+1][MAXC+1]; 
double TCOST,CMIN,XMIN; 
char  SW; 
FILE *fp; 
 
int IERROR; 
char ERR_MSG[100]; 


#define INFILE "transi3.in"
#define OUTFILE "transi3.out"


//-------------------- 
//    파일 Input 
//--------------------
void FILEMODE()  
{ 
    int i, j; 
    FILE *fin; 
    fin=fopen(INFILE,"rt");
    fscanf(fin, "%d %d", &NOSUP,&NODEM);
	INIT=1; //초기 가능해 선택
	IPR=1;  //인쇄 형태 선택
    for (i=1 ; i <= NOSUP ; i++) {
        for (j=1 ; j <= NODEM ; j++) 
             fscanf(fin, "%lf", &C[i][j]); 
    } 
    for (i=1 ; i <= NOSUP ; i++) 
         fscanf(fin, "%lf", &SUPPLY[i]); 
    for (j=1 ; j <= NODEM ; j++) 
         fscanf(fin, "%lf", &DEMAND[j]); 

    fclose(fin); 

	//읽어 온 내용 출력.
    if ( IPR > 1 ){ 
       printf("NOSUP = %d\n", NOSUP); 
       printf("NODEM = %d\n", NODEM); 
       printf("INIT = %d\n", INIT); 
       printf("IPR = %d\n", IPR); 
       for (i=1 ; i <= NOSUP ; i++) 
          for (j=1 ; j <= NODEM ; j++) 
             printf("C[%d][%d] = %lf\n", i,j,C[i][j]); 
          for (i=1 ; i <= NOSUP ; i++) 
             printf("SUPPLY[%d] = %lf\n",i,SUPPLY[i]); 
          for (j=1 ; j <= NODEM ; j++) 
             printf("DEMAND[%d] = %lf\n",j,DEMAND[j]); 
    } 
} 
 
 

//-------------------- 
//    BALANCE = 총 공급량과 총 수요량을 일치시킴.
//--------------------
void BALANCE() 
{ 
     double ss,ds,diff; 
     int i,j; 
 
	 //ss는 총 공급량
	 //ds는 총 수요량
     ss=0.0; ds=0.0; 
     for(i=1 ; i<=NOSUP ; i++) ss+=SUPPLY[i]; 
     for(j=1 ; j<=NODEM ; j++) ds+=DEMAND[j]; 

	 //총 공급량과 총 수요량을 일치하는지 검사.
     N9=NODEM; 
     diff=ss-ds; 
     if(diff == 0.0) return; 

     if(diff < 0.0){ 
        printf(" The total SUPPLY must be greater than the total DEMAND.\n"); 
        printf(" So this problem is infeasible.\n"); 
        printf(" Check the DATA.\n"); 
        sprintf(ERR_MSG," The total SUPPLY must be greater than the total DEMAND."); 
        IERROR=3; return; 
     } 
     NODEM+=1; 
     for(i=1;i<=NOSUP;i++) C[i][NODEM] = 1E+20; 
     DEMAND[NODEM]=diff; 
     if (IPR > 1 ){ 
        if (diff == 0) printf("\n The original problem is balanced."); 
        if (diff > 0) printf("\n The unbalnced problem is now balanced."); 
     } 
} 
 

/************ 
    NORTH = 북서코너법.
 ************/ 
void NORTH()
{ 
    int i,j; 
 
    for (i=1;i<=NOSUP;i++ ) 
       for (j=1;j<=NODEM;j++) 
          FLOW[i][j] = 0; 

    for (i=1;i<=NOSUP;i++ ) S1[i] = SUPPLY[i]; 
    for (j=1;j<=NODEM;j++ ) D1[j] = DEMAND[j]; 
    for (i=1;i<=NOSUP;i++ ){ 
       if ( fabs(S1[i]) < 0.00001 ) continue; 
       for (j=1;j<=NODEM;j++){ 
          if (fabs(D1[j]) < 0.00001 ) continue; 
          if (fabs(S1[i]-D1[j])<0.0001){ 
             FLOW[i][j] = S1[i];
			 S1[i] = 0;
			 D1[j] = 0; 
          } 
          else if (S1[i] < D1[j]){ 
             FLOW[i][j] = S1[i];
			 D1[j] -= S1[i];
			 S1[i] = 0; 
          } 
          else { 
             FLOW[i][j] = D1[j];
			 S1[i] -= D1[j];
			 D1[j] = 0; 
          } 
       } 
    } 

    if(IPR > 1) 
       printf("\n** INITIAL BASIC SOLUTION BY NORTH-WEST METHOD\n"); 
} 
 

 
/************ 
    INISOL 
 ************/ 
void INISOL()   /* function INISOL */ 
{ 
    int  i,j; 
 
    for (i=1;i<=NOSUP;i++) 
        for (j=1;j<=NODEM;j++) EC[i][j] = 0; 
    
	//초기해 구하기.
	NORTH();
     
	IT = 0;    /* Initialize Number of Iteration */ 
    TCOST = 0.0; 
    for(i=1 ; i <= NOSUP ; i++) 
		for(j=1 ; j <= NODEM ; j++){ 
			if (FLOW[i][j] == 0) continue; 
			EC[i][j] = 1; CT++; 
			TCOST = TCOST + C[i][j] * FLOW[i][j]; 
		} 
    
	//중간값 출력.
	if ( IPR >  1 ){ 
		//CT는 현재 FLOW에 값이 있는 것의 개수
		//즉, 공급에서 수요로 가는 비용으로 할당된 것의 개수
        if (CT < CP) printf(" \nThe initial solution is degenerate."); 
        else printf(" \nThe initial solution is non-degenerate."); 
        printf("\n\n SUPPLY ----  DEMAND        FLOW\n"); 
        for(i=1 ; i <= NOSUP ; i++) 
            for(j=1 ; j <= NODEM ; j++){ 
               if(EC[i][j] == 0) continue; 
               printf("\n  SUPPLY(%d)  ----   DEMAND(%d)         %lf",i,j,FLOW[i][j]); 
            } 
        printf("\n\n     TOTAL COST = %lf\n", TCOST); 
    } 
} 
 
/************ 
    DEGEN 
 ************/ 
void DEGEN() 
{ 
    int i,j,k; 
    double diff1,diff2; 
 
    for(i = 1 ; i <= NOSUP ; i++){ U[i] = NODEM; S1[i] = SUPPLY[i]; } 
    for(j = 1 ; j <= NODEM ; j++){ V[j] = NOSUP; D1[j] = DEMAND[j]; } 
    for(i = 1 ; i <= NOSUP ; i++) 
       for(j = 1 ; j <= NODEM ; j++) EC[i][j] = 0; 
    for(i = 1 ; i <= NOSUP ; i++) 
       for(j = 1 ; j <= NODEM ; j++){ 
          if(FLOW[i][j] == 0.0) continue; 
          EC[i][j] = 1; 
          diff1 = S1[i] - FLOW[i][j]; diff2 = D1[j] - FLOW[i][j]; 
          if (diff1 > 0 && diff2 > 0){ 
             S1[i] = diff1; D1[j] = diff2; 
          } 
          else if (diff1 > diff2){ 
             S1[i] = diff1; D1[j] = 0; V[j] = 0; 
             for (k=1;k<=NOSUP;k++) 
                if (U[k] != 0) U[k]--; 
          } 
          else if (diff1 < diff2){ 
             S1[i] = 0; D1[j] = diff2; U[i] = 0; 
             for (k=1;k<=NODEM;k++) 
                if (V[k] != 0) V[k]--; 
          } 
          else 
             if (V[j] > 1){ 
             S1[i] = 0; D1[j] = 0; U[i] = 0; 
             for (k=1;k<=NODEM;k++) 
                if (V[k] != 0) V[k]--; 
             } 
             else{ 
                S1[i] = 0; D1[j] = 0; V[j] = 0; 
                for (k=1;k<=NOSUP;k++) 
                   if (U[k] != 0) U[k]--; 
             } 
          } 
     for (i=1; i<=NOSUP;i++){ 
        if (U[i] == 0) continue; 
        for (j=1;j<=NODEM;j++) 
           if (U[i] != 0 && V[j] != 0){ 
              EC[i][j] = 1; U[i] = 0; V[j] = 0; EC[i][j] = 1; CT++; 
           } 
    } 
    if(IPR > 1) { 
       printf("\n** DEGEN **\n"); 
       printf("\n SUPPLY ----  DEMAND        FLOW\n"); 
       for(i=1 ; i <= NOSUP ; i++) 
          for(j=1 ; j <= NODEM ; j++) 
             if(EC[i][j] == 1) 
                printf("\n  SUPPLY(%d)  ----   DEMAND(%d)         %lf",i,j,FLOW[i][j]); 
             printf("\n\n     TOTAL COST = %lf\n", TCOST); 
    } 
} 
 
/********** 
    LOOP 
 **********/ 
void LOOP() 
{ 
    int  i,j,NEWI,NEWJ,BC[MAXR][MAXC]; 
    int  RC[MAXR],  /*  Row basic cell Counter             */ 
         CC[MAXC];  /*  Colomn basic cell Counter          */ 
    int  FOUND,     /*  1 if found a basic cell            */ 
         SUCCESS;   /*  1 if cycle constructed             */ 
 
    for(i=1;i<=NOSUP;i++) RC[i]=0; 
    for(j=1;j<=NODEM;j++) CC[j]=0; 

    for(i=1;i<=NOSUP;i++) 
        for(j=1;j<=NODEM;j++) 
            if (EC[i][j]==1) {
				BC[i][j] = 1;
				RC[i]++;
				CC[j]++;
            } else {
                BC[i][j]=0; 
			}
    MOVEX[1] = NOWI; 
    MOVEY[1] = NOWJ; 
    INDIC=1; 
    do{ 
        FOUND = 0; 
        SUCCESS = 0; 
        NEWI = MOVEX[INDIC]; 
        NEWJ = MOVEY[INDIC]; 
        if (INDIC%2 ==1) { 
			/* if(INDIC-INDIC/2*2 ==1)*/ 
		    if(RC[NEWI]>0) {
				for(j=1;j<=NODEM;j++) {
					if(BC[NEWI][j] && CC[j]>0){ 
						FOUND=1; 
						if(NOWJ==j) SUCCESS=1; 
						NEWJ=j; 
						break; 
					} 
				}
			}
        } 
        else { 
			if(CC[NEWJ]>0) {
				for(i=1;i<=NOSUP;i++){ 
					if( BC[i][NEWJ] && RC[i]>0 ){ 
						FOUND = 1; 
						if (NOWI==i) SUCCESS=1; 
						NEWI = i; 
						break; 
					} 
				} 
			}
        } 
        if (FOUND){ 
			(INDIC)++; 
			MOVEX[INDIC]=NEWI; 
			MOVEY[INDIC]=NEWJ; 
			BC[NEWI][NEWJ]=0; 
			RC[NEWI]--; 
			CC[NEWJ]--; 
        } 
        else {
			INDIC--; 
		}
    } while(!SUCCESS); 

    if (IPR>1){ 
        printf("\n\n** LOOP **\n"); 
        printf("\nNOWI,NOWJ =  %d  %d",NOWI,NOWJ); 
        if (INDIC == 1){ 
			printf("\n\n New loop can not be found."); 
        } 
        if (INDIC > 1) { 
            printf("\n\n New loop is "); 
            for (i=1; i<=INDIC;i++) 
				printf("\n %d    %d",MOVEX[i], MOVEY[i]); 
			printf("\n INDIC = %d",INDIC); 
		} 
    } 
} 
 
/************ 
    CCBAR 
 ************/ 
void CCBAR() 
{ 
    int last,i1,j1,k; 
    double CBAR; 
 
    if (IPR > 1) 
		printf("\n\n ** START OF CCBAR **"); 

	//디딤돌법에 의해 문제 품.
    last = 0; 
    OPT = 0; //기회 비용이 있음.
    CMIN = 1E+20;
    MINI = 0;
    MINJ = 0; 
    for (i1=1; i1<=NOSUP; i1++) 
		for (j1=1; j1<=NODEM; j1++) 
			if (EC[i1][j1] == 0) { 
				last += 1;
				NOWI = i1;
				NOWJ = j1; 
				LOOP(); 
				CBAR = 0; 
				for ( k=1; k<=INDIC; k+=2){ 
					//C[]배열은 파일에서 읽은 공급지에서 수요지의 비용
					CBAR += C[MOVEX[k]][MOVEY[k]]; 
					CBAR -= C[MOVEX[k+1]][MOVEY[k+1]]; 
				} 
				if (CMIN > CBAR){ 
					CMIN = CBAR;
					MINI = i1;
					MINJ = j1; 
				} 
			} 
    if (CMIN >= 0)  OPT = 1; 

    if (IPR > 1) { 
        printf("\n\n CMIN, MINI, MINJ = %lf  %d  %d",CMIN,MINI,MINJ); 
        printf(" No of nonbasic cells = %d",last); 
        printf("\n\n ** END OF CCBAR **"); 
    } 
} 
 
/************ 
    NEWSOL 
 ************/ 
void NEWSOL() 
{ 
    int i,j,dropi,dropj; 
 
    if (IPR > 1) 
       printf("\n\n ** START OF NEWSOL **"); 
    NOWI = MINI; NOWJ = MINJ; XMIN = 1E+20; 
    LOOP(); 
    for (i=2;i<=INDIC;i+=2) 
       if (FLOW[MOVEX[i]][MOVEY[i]] < XMIN){ 
          XMIN = FLOW[MOVEX[i]][MOVEY[i]]; 
          dropi = MOVEX[i]; 
          dropj = MOVEY[i]; 
       } 
    for (i=1;i<=INDIC;i+=2){ 
       FLOW[MOVEX[i]][MOVEY[i]] += XMIN; 
       FLOW[MOVEX[i+1]][MOVEY[i+1]] -= XMIN; 
    } 
    EC[MINI][MINJ] = 1; 
    EC[dropi][dropj] = 0; 
    TCOST = TCOST + CMIN*XMIN; 
    if (IPR >1){ 
       printf("\n     SUPPLY   ----  DEMAND       FLOW\n"); 
       for (i=1 ; i <= NOSUP ; i++) 
          for(j=1 ; j <= NODEM ; j++){ 
             if(FLOW[i][j] == 0.0) continue; 
             printf("\n      SUPPLY(%d)    ----   DEMAND(%d)        %lf",i,j,FLOW[i][j]); 
          } 
       printf("\n\n     TOTAL COST = %lf\n", TCOST); 
       printf("\n\n     NUMBER OF ITERATION = %d\n", IT); 
       printf("\n\n ** END OF NEWSOL **"); 
    } 
} 
 
/************ 
    OPTSOL 
 ************/ 
void OPTSOL() 
{ 
     int i,j; 
 
     fp =fopen(OUTFILE,"wt"); 
     printf("\n\n *** OPTIMAL SOLUTION *** \n"); 
     printf("\n       SUPPLY      ----    DEMAND            FLOW\n"); 
     fprintf(fp,"\n\n *** OPTIMAL SOLUTION *** \n"); 
     fprintf(fp,"\n       SUPPLY      ----    DEMAND            FLOW\n"); 
     for(i=1 ; i <= NOSUP ; i++) 
        for(j=1 ; j <= NODEM ; j++){ 
           if(FLOW[i][j] == 0.0) continue; 
           printf("\n      SUPPLY(%d)    ----   DEMAND(%d)        %lf",i,j,FLOW[i][j]); 
           fprintf(fp,"\n      SUPPLY(%d)    ----   DEMAND(%d)        %lf",i,j,FLOW[i][j]); 
        } 
     printf("\n\n     TOTAL COST = %lf\n", TCOST); 
     printf("\n     NUMBER OF ITERATION = %d\n", IT); 
     fprintf(fp,"\n\n     TOTAL COST = %lf\n", TCOST); 
     fprintf(fp,"\n     NUMBER OF ITERATION = %d\n", IT); 
     fclose(fp); 
} 
 
/************ 
 ERROR_HANDLE 
*************/ 
void error_handle() 
{ 
    /************************************/ 
    /* Error Code                       */ 
    /************************************/ 
    /* IERROR=0  No Error               */ 
    /* IERROR=1  Normal Exit            */ 
    /* IERROR=2  File Open Error        */ 
    /* IERROR=3  problem is infeasible  */ 
    /************************************/ 
 
    if (IERROR==0) return; 
    else { 
   		printf("\n%s\n",ERR_MSG); 
   		fprintf(fp,"\n%s\n",ERR_MSG); 
   		fclose(fp);
		exit(0); 
    } 
    return;
} 
 
/********** 
    MAIN 
 **********/ 
main () 
{ 
	FILEMODE();
    CP = NOSUP + NODEM - 1; CT = 0; 
    BALANCE(); 
    INISOL(); 
	//CT는 현재 FLOW에 값이 있는 것의 개수
	//즉, 공급에서 수요로 가는 비용으로 할당된 것의 개수
    if (CT < CP) DEGEN(); 
    CCBAR(); 
    while (OPT == 0){ 
        NEWSOL(); 
        IT ++; 
        CCBAR(); 
    } 
    OPTSOL(); 
	IERROR=1;
	error_handle(); 
} 
