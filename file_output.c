#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NUM 4

int main(){
  FILE *fp;
  char *fname = "sample1.csv";
  int ret,i=0;
  char buf[4][10];
  int data[4];

  struct score {
    int number;
    int japanese;
    int math;
    int english;
  };

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
    // printf("%d\t%d\t%d\t%d\n", data[0], data[1], data[2], data[3]);
  }
  printf("\n");

   int s,t,tmp;
    for(s=0 ; s<NUM-1 ; s++){
        for(t=s+1;t<NUM;t++){
            if(scores[t].japanese>scores[s].japanese){
                tmp = scores[t].japanese;
                scores[t].japanese = scores[s].japanese;
                scores[s].japanese = tmp;

                tmp = scores[t].math;
                scores[t].math = scores[s].math;
                scores[s].math = tmp;
                
                tmp = scores[t].english;
                scores[t].english = scores[s].english;
                scores[s].english = tmp;

                tmp = scores[t].number;
                scores[t].number = scores[s].number;
                scores[s].number = tmp;
            }
        }
    }



  for ( i = 0; i < 4; i++){
    printf("%d\t",scores[i].number);
    printf("%d\t",scores[i].japanese );
    printf("%d\t",scores[i].math );
    printf("%d\t\n",scores[i].english );
  }

  fclose( fp );
}
