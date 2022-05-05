#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#define N 256 // 1行の最大文字数(バイト数)
#define ROW 150 // 読み込むファイルのデータの行数
#define SIZE_OF_ARRAY(array)    (sizeof(array)/sizeof(array[0]))
#define K 1  // kの数
#define T 1 //tの値

// １．パラメータの設定：データ数，クラス数，特徴空間の次元数，k-最近傍法の k の値など 
// 1列目の項目名と2列目以降のデータを格納する配列をメンバにもつ構造体
typedef struct iris {
	float iris_data[4];
  int iris_label;
	float distance;
} data;

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

float compar(const void* a, const void* b) {
    if (((data*)a)->distance > ((data*)b)->distance) { //aより距離が小さければ入れ替え
        return 1;
    } else {
        return -1;
    }
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
	printf("a-1");
  int label_counter[3];
  printf("a");
	for(int i=0;i<150;i++){
		data[i].distance = (data[i].iris_data[0]-x)*(data[i].iris_data[0]-x) + (data[i].iris_data[1]-y)*(data[i].iris_data[1]-y);
  }

  printf("b");
  qsort(data,150,sizeof(data),compar);
  int most_label;
  printf("c");
  for ( int i = 0; i < K; i++){
    label_counter[data[i].iris_label]++;
    
    if (i=0||label_counter[most_label]<label_counter[data[i].iris_label])
    {
      most_label=data[i].iris_label;
    }
  }
  printf("d");
  printf("たぶん%d",most_label);

}