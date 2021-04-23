#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NUM 7
#define DTCNT  ((sizeof res)/(sizeof(res_t)))
  
   struct score {
    int number;
    int japanese;
    int math;
    int english;
  };

void score_sort(struct score scores[]){
   int s,t;
   struct score tmp;
    for(s=0 ; s<NUM-1 ; s++){
        for(t=s+1;t<NUM;t++){
            if(scores[t].japanese>scores[s].japanese){
                tmp = scores[t];
                scores[t] = scores[s];
                scores[s] = tmp;
            }
        }
    }

    //aaaa
}

int main(){
  FILE *fp;
  FILE *fp_out;
  char *fname = "input_test.csv";
  int ret,i=0;
  char buf[NUM][10];
  int data[NUM];
  char fname_out[24];

  fp = fopen( fname, "r" );
  
  if( fp == NULL ){
    printf( "%sファイルが開けません\n", fname );
    return -1;
  }

  printf("\n");
  
  fscanf(fp, "%[^,],%[^,],%[^,],%s", buf[0], buf[1], buf[2], buf[3]);
  printf("%s %s %s %s \n",buf[0], buf[1], buf[2], buf[3]);

  struct score scores[NUM];
  while((ret=fscanf(fp, "%d, %d, %d, %d", &data[0], &data[1], &data[2], &data[3])) != EOF){
    scores[i].number =data[0];
    scores[i].japanese =data[1];
    scores[i].math = data[2];
    scores[i].english =data[3];
    ++i;
  }

    score_sort(scores);

  for ( i = 0; i < NUM; i++){
    printf("%d\t",scores[i].number);
    printf("%d\t",scores[i].japanese );
    printf("%d\t",scores[i].math );
    printf("%d\t\n",scores[i].english );
  }

  int year = 2021 ,month = 4;
  sprintf( fname_out, "%04d%02dresult.csv", year, month);
  
  // ファイルのオープン
  if( (fp_out = fopen( fname_out, "w" )) == NULL ) {
      printf( "結果ファイルがオープンできませんでした\n" );
      exit( 1 );
  }
  
  // ヘッダ行を出力する
  fprintf( fp_out, "number,japanese,math,English\n" );
  
  // 各データをカンマ区切りで出力する
  for( i = 0; i < NUM; i++ ) {
      fprintf( fp_out, "%d,%d,%d,%d\n",
          scores[i].number, scores[i].japanese, scores[i].math, scores[i].english );
  }

  printf( "%s に結果が出力されました\n", fname_out );
  fclose( fp_out );
}
