#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#define N 256 // 1行の最大文字数(バイト数)
#define ROW 150 // 読み込むファイルのデータの行数
#define SIZE_OF_ARRAY(array)    (sizeof(array)/sizeof(array[0]))
 
// 1列目の項目名と2列目以降のデータを格納する配列をメンバにもつ構造体
// １．パラメータの設定：データ数，クラス数，特徴空間の次元数，k-最近傍法の k の値など 
typedef struct iris {
	float iris_data[4];
    int iris_label;
} data;
 
// ２．Iris.txt のデータの入力
/*
    文字列を分割する

    注意
        s の文字列内に、区切り文字が連続する箇所があるとき、その隙間は無視される。
        たとえば、s が "a//b"、separator が "/" のとき、分割結果は、
        "a" と "b" であり、戻り値は 2 を返す。

    引数
        s: 対象の文字列。書き換えが起こる。NULL不可
        separator: 区切り文字の並び。NULL不可
        result: 結果を格納する文字列配列。十分な要素数を確保すること
        result_size: 引数result の要素数

    戻り値
        分割後の文字列の個数
*/
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
	char f1[8], f2[8], f3[8], f4[8];
	char* tmp[32];
    int label;
	int unchi = 0;
 
	data data[ROW];
 
	fp = fopen(fname, "r"); // ファイルを開く。失敗するとNULLを返す。
	if(fp == NULL) {
		printf("%s file not open!\n", fname);
		return -1;
	}
 
	while(fgets(line, N, fp) != NULL) {
		int count;
		count = split(tmp, line, ',');
		for(int i = 0; i < count; i++){
			printf("%s\n" ,tmp[i]);
			data[unchi].iris_data[i]=tnp;
		}

	// 	float tmp[] = {f1, f2, f3, f4};
	// 	for(int j = 0; j  < 4; j++) {
	// 		data[i].iris_data[j] = tmp[j];
	// 	}//4つのデータを入力
		
    //     data[i].iris_label = label;//ラベルを入力
		
    //     i++;
	}
	

	fclose(fp); // ファイルを閉じる

// printf("%f,%f,%f,%f,%d\n",&data[1].iris_data[1], &data[1].iris_data[1], &data[1].iris_data[1], &data[1].iris_data[1], &data[1].iris_label);
// float ymax=5.0,ymin=1.0,xmax=8.0,xmin=4.0;

}

// ３．Iris データの２つの特徴量の取りうる値の範囲を事前に求める 

// ４．３で求めた範囲内で，未知データの 2 成分をキーボード入力する 

// ５．k-最近傍法のアルゴリズムで未知データのクラス番号（0,1,2 のいずれか）を決定して，出力する 
