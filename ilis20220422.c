#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#define N 256 // 1行の最大文字数(バイト数)
#define ROW 150 // 読み込むファイルのデータの行数
#define SIZE_OF_ARRAY(array)    (sizeof(array)/sizeof(array[0]))
#define K 1  // kの数

// １．パラメータの設定：データ数，クラス数，特徴空間の次元数，k-最近傍法の k の値など 
// 1列目の項目名と2列目以降のデータを格納する配列をメンバにもつ構造体
typedef struct iris {
	float iris_data[4];
    int iris_label;
} data;
 
typedef struct match {
	float distance[4];
    int label;
} match;

// ２．Iris.txt のデータの入力

int isDelimiter(char p, char delim){
  return p == delim;
}

int split(char *dst[], char *src, char delim){
  int count = 0;

  for(;;) {
    while (isDelimiter(*src, delim)){
      src++;
    }

    if (*src == '\0') break;

    dst[count++] = src;

    while (*src && !isDelimiter(*src, delim)) {
      src++;
    }

    if (*src == '\0') break;

    *src++ = '\0';
  }
  return count;
}


int main(void) {
	FILE *fp; // FILE型構造体
	char fname[] = "iris.txt";
	char line[N];
	char* tmp[32];
	data data[ROW];
 
	fp = fopen(fname, "r"); // ファイルを開く。失敗するとNULLを返す。
	if(fp == NULL) {
		printf("%s file not open!\n", fname);
		return -1;
	}
 
	int unchi=0;
	while(fgets(line, N, fp) != NULL) {
		int count;
		count = split(tmp, line, ',');
		for(int i = 0; i < count; i++){
			// printf("%s\n" ,tmp[i]);
			if(i==4){
				data[unchi].iris_label=atof(tmp);
			}else{
				data[unchi].iris_data[i]=atof(tmp);
			}
		}
		unchi=unchi+1;
	}
	fclose(fp); // ファイルを閉じる


// ３．Iris データの２つの特徴量の取りうる値の範囲を事前に求める 
	float xmax=5.0,xmin=1.0,ymax=8.0,ymin=4.0;//計算めんどいのでこれでいいや

// ４．３で求めた範囲内で，未知データの 2 成分をキーボード入力する 
	char coordinate[20];
	float x,y;
	do{
		printf("x,yのように座標を入力してね xは%f~%fの値,yは%f~%fまでの値が入力できるよ！\n",xmin,xmax,ymin,ymax);
		scanf("%s",coordinate);
		sscanf(coordinate,"%f,%f",&x,&y);
		printf("x=%f,y=%f\n",x,y);
	}while(x<xmin||x>xmax||y<ymin||y>ymax);

// ５．k-最近傍法のアルゴリズムで未知データのクラス番号（0,1,2 のいずれか）を決定して，出力する 
	// int class_counter[3]=0;
	match result[K];
	for(i=0;i<150;i++){
		l = (x1-x2)*(x1-x2) + (y1-y2)*(y1-y2);
	}
}