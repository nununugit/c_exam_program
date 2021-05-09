#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NUM 13
   struct score {
    int number; //受験番号
    int japanese_score; //国語のテスト点
    int math_score; //数学のテスト点
    int english_score; //英語のテスト点

    int japanese_grade; //国語の成績
    int ss_grade; // 社会の成績(social studies)
    int math_grade; //数学の成績
    int science_grade; //理科の成績
    int music_grade; //音楽の成績
    int art_grade; //美術の成績
    int pe_grade; //体育の成績
    int helt_grade; //技術家庭 (home economics life technique)
    int english_grade; //英語の成績

    int total_score; //テスト点数の合計
    int total_grade; //内申点の合計
    float base_score; //記録換算点(内申点を点数化したもの)

    float score; //全てを考慮した点数

    int result; //合否
    int rank; //順位
  };

void score_sort(struct score scores[],int ninzu){
   int s,t;
   struct score tmp;
    for(s=0 ; s<ninzu-1 ; s++){
        for(t=s+1;t<ninzu;t++){
            if(scores[t].score>scores[s].score){
                tmp = scores[t];
                scores[t] = scores[s];
                scores[s] = tmp;
                //bubble sort sort の安定性が高いため採用
            }
        }
    }
}

int avg_score(struct score scores[],int ninzu){
  int i;
  float avg;
  for(i=0;i<ninzu;i++){
    avg += scores[i].score;
  }
  avg = avg/i;
  return avg;
}

int main(int argc, char *argv[]){
  FILE *fp;
  FILE *fp_out;

  char *fname = "input.csv";
  int ret , i=0 ,avg,num,flg=0;
  char buf[NUM][100];
  int data[NUM];
  char fname_out[24];
  num = atoi(argv[1]);
    
  //ファイルを開く
  fp = fopen( fname, "r" );
  if( fp == NULL ){
    printf( "%sファイルが開けません\n", fname );
    return -1;
  }

  
  fscanf(fp, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%s",
  buf[0], buf[1], buf[2], buf[3],buf[4],buf[5],buf[6],buf[7],buf[8],buf[9],buf[10],buf[11],buf[12]);
  
  struct score scores[500];

  while((ret=fscanf(fp, "%d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d ,%d", 
  &data[0], &data[1], &data[2], &data[3], &data[4], &data[5], &data[6],
  &data[7], &data[8], &data[9], &data[10], &data[11], &data[12])) != EOF){
    scores[i].number =data[0];
    scores[i].japanese_score =data[1];
    scores[i].math_score = data[2];
    scores[i].english_score =data[3];

    scores[i].japanese_grade =data[4];
    scores[i].ss_grade =data[5];
    scores[i].math_grade =data[6];
    scores[i].science_grade =data[7];
    scores[i].music_grade =data[8];
    scores[i].art_grade =data[9];
    scores[i].pe_grade =data[10];
    scores[i].helt_grade =data[11];
    scores[i].english_grade =data[12];

    scores[i].total_score = data[1]+data[2]+data[3];
    scores[i].total_grade =data[4]+data[5]+data[6]+data[7]+data[8]+data[9]+data[10]+data[11]+data[12];
    scores[i].base_score =700*((data[4]+data[5]+(data[6]*1.4)+data[7]+data[8]+data[9]+data[10]+data[11]+(data[12]*1.4))/49);
    
    scores[i].score = scores[i].total_score + scores[i].base_score;
    ++i;
  }

  int ninzu = i;
  
  avg = avg_score(scores,ninzu);
  score_sort(scores,ninzu);

  //ファイル出力
  int year = 2021 ,month = 4;
  sprintf( fname_out, "%04d%02dresult.csv", year, month);
  
  // ファイルのオープン
  if( (fp_out = fopen( fname_out, "w" )) == NULL ) {
      printf( "結果ファイルがオープンできませんでした\n");
      exit( 1 );
  }
  
  // ヘッダ行を出力する
  fprintf( fp_out, 
  "number , japanese_score , math_score,English_score, japanese_grade,ss_grade,math_grade, science_grade, music_grade , art_grade , pe_grade , helt_grade, english_grade , total_score , total_grade , base_score, score , result,rank\n"
  );
  
  // 各データをカンマ区切りで出力する
   for( i = 0; i < ninzu; i++ ) {
     if(scores[i].score>=avg){
         scores[i].result = 1;
     }else{
         scores[i].result = 0;
     }
        scores[i].rank = i+1;

        if(scores[i].number==num){
           printf("%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%4.0f,%4.0f,%d,%d\n",
         scores[i].number, 
         scores[i].japanese_score, 
         scores[i].math_score, 
         scores[i].english_score,
         scores[i].japanese_grade,
         scores[i].ss_grade,
         scores[i].math_grade,
         scores[i].science_grade,
         scores[i].music_grade,
         scores[i].art_grade,
         scores[i].pe_grade,
         scores[i].helt_grade,
         scores[i].english_grade,
         scores[i].total_score,
         scores[i].total_grade,
         scores[i].base_score,
         scores[i].score,
         scores[i].result,
         scores[i].rank
         );
         }

       fprintf( fp_out, "%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%4.0f,%4.0f,%d,%d\n",
         scores[i].number, 
         scores[i].japanese_score, 
         scores[i].math_score, 
         scores[i].english_score,
         scores[i].japanese_grade,
         scores[i].ss_grade,
         scores[i].math_grade,
         scores[i].science_grade,
         scores[i].music_grade,
         scores[i].art_grade,
         scores[i].pe_grade,
         scores[i].helt_grade,
         scores[i].english_grade,
         scores[i].total_score,
         scores[i].total_grade,
         scores[i].base_score,
         scores[i].score,
         scores[i].result,
         scores[i].rank
         );

   }

  printf( "%s に結果が出力されました\n", fname_out );

  printf("%d",avg_score(scores,ninzu));
  fclose( fp_out );
}
